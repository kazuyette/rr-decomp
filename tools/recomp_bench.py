#!/usr/bin/env python3
"""Test bench for the translator, second version: inputs kept out of the source.

The first version wrote the test vectors as C literals. For twelve functions
that already came to 276 KB of source, and compilation collapsed well before
reaching the intended scale -- six minutes forty for twelve functions, of which
0.2 second was computation. The rest was waiting.

The fix is not to optimise the generation but to remove its cause: the inputs
live in a binary file that both harnesses read at run time. The source becomes
tiny again, and constant, whatever the number of vectors.

The rest of the protocol is unchanged, and it is the part that matters: the
reference is the real retail code executed under qemu-mipsel, not a reading of
that code.
"""
import random
import struct
import subprocess
import sys
import time

sys.path.insert(0, "/tmp/rrdecomp/tools")
import recomp

recomp.load_symbols("/tmp/rrdecomp/asm/psyq.s", "/tmp/rrdecomp/asm/29E8.s")

EXE = "/tmp/rr/files/PSX.EXE"
ASMS = ["/tmp/rrdecomp/asm/psyq.s", "/tmp/rrdecomp/asm/29E8.s"]
D = "/tmp/recomp"
BUF = 0x00078000   # same absolute address on both sides: some functions compute
                   # on the value of the pointer, not only on what it
                   # designates
SIZE = 256
ROUNDS = 16
BASE = 0x00010000


def writes_v0(words):
    """True if the function writes $v0 anywhere."""
    for w in words:
        op = w >> 26
        if op == 0:
            fn = w & 63
            if fn in (0x10, 0x12) or (fn not in (0x08, 0x18, 0x19, 0x1A, 0x1B, 0x11, 0x13)):
                if ((w >> 11) & 31) == 2:
                    return True
            if fn in (0x10, 0x12) and ((w >> 11) & 31) == 2:
                return True
        elif op in (8, 9, 10, 11, 12, 13, 14, 15, 32, 33, 35, 36, 37):
            if ((w >> 16) & 31) == 2:
                return True
    return False


def find(nm):
    for a in ASMS:
        addr, cnt = recomp.func_length(a, nm)
        if addr is not None:
            return addr, cnt
    raise SystemExit("function not found: " + nm)


def make_vectors():
    rnd = random.Random(20260816)
    with open(D + "/vec.bin", "wb") as f:
        for _ in range(ROUNDS):
            f.write(bytes(rnd.randrange(256) for _ in range(SIZE)))
            # Pointers aligned on 4: MIPS raises SIGBUS on a misaligned lw,
            # exactly like the console. The bench must only ask questions the
            # real hardware could have heard.
            f.write(struct.pack("<4I", 4 * rnd.randrange(16), 4 * rnd.randrange(16),
                                rnd.randrange(0x100), rnd.randrange(0x100)))


HARNESS = r"""
/* Isolation by process rather than by longjmp.

   The first version caught the faults with sigsetjmp/siglongjmp from a
   signal handler. Two things defeated it: glibc refuses a longjmp that
   climbs back to a stack frame it judges uninitialised ("longjmp causes
   uninitialized stack frame"), and a function that had gone into an
   endless loop -- func_80045334 on some buffer or other -- was not
   caught at all.

   One child per function, an alarm in the child, the parent harvesting: a
   function that faults or loops kills its own child and nothing else. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
%(decl)s
%(bufdecl)s
struct vec { unsigned char b[%(size)d]; unsigned int a[4]; };
static struct vec V[%(rounds)d];
/* Six arguments: some functions read their fifth parameter at 0x10($sp),
   where the caller left it. With four, they were reading uninitialised stack
   -- different on the two sides, and the comparison failed for a reason that
   has nothing to do with the translation. */
/* Eight arguments. func_80028A0C reads as far as 0x54($sp), that is the
   eighth. Every missing argument is read out of uninitialised stack, different
   on the two sides -- and produces a divergence that has nothing to do with
   the translation. */
typedef unsigned int (*fn_t)(unsigned int, unsigned int, unsigned int, unsigned int,
                             unsigned int, unsigned int, unsigned int, unsigned int);
static const char *NAMES[] = { %(names)s };
static const fn_t FNS[] = { %(fns)s };
/* A function that never writes $v0 has no return value: whatever the context
   had left there is not comparable. It is printed only for the functions whose
   disassembly shows a write to that register. */
static const int RETS[] = { %(rets)s };
int main(void)
{
    FILE *f;
    %(preload)s
    f = fopen("%(dir)s/vec.bin", "rb");
    int nf = sizeof NAMES / sizeof *NAMES, i, k, j, st;
    pid_t pid;
    if (!f || fread(V, sizeof V, 1, f) != 1) { fprintf(stderr, "vec.bin\n"); return 1; }
    fclose(f);
    for (j = 0; j < nf; j++) {
        fflush(stdout);
        pid = fork();
        if (pid == 0) {
            alarm(5);
            for (k = 0; k < %(rounds)d; k++) {
                unsigned int rv;
                %(setup)s
                %(extra)s rv = FNS[j](%(a0)s, %(a1)s, V[k].a[2], V[k].a[3], V[k].a[2], V[k].a[3], V[k].a[0], V[k].a[1]);
                /* A return value that points into the buffer is an address: it
                   cannot coincide between the two harnesses, whose buffers
                   live elsewhere. It is printed relative to its base. */
                if (RETS[j]) {
                    unsigned int b = (unsigned int)(%(base)s);
                    if (rv >= b && rv < b + %(size)d) printf("%%s %%d rv=@+%%x", NAMES[j], k, rv - b);
                    else printf("%%s %%d rv=%%08x", NAMES[j], k, rv);
                }
                else printf("%%s %%d (no return value)", NAMES[j], k);
                for (i = 0; i < %(size)d; i++) printf(" %%02x", %(peek)s);
                printf("\n");
            }
            fflush(stdout);
            _exit(0);
        }
        waitpid(pid, &st, 0);
        if (st != 0) printf("%%s DROPPED\n", NAMES[j]);
        fflush(stdout);
    }
    return 0;
}
"""

def build_reference(funcs):
    """The whole image of the executable, at its address masked to 28 bits.

    Copying each function one by one worked as long as they were isolated. As
    soon as they call one another and read globals, the complete program is
    needed -- and laying it down in one block is simpler than cutting it up:
    the calls and the absolute addresses then fall out right on their own,
    without a single line of relocation.
    """
    with open(D + "/ref_code.s", "w") as f:
        f.write('    .section .psx,"ax",@progbits\n')
        f.write('    .incbin "%s/psx.img"\n' % D)
        for nm in funcs:
            a, _ = find(nm)
            f.write(f"    .globl psx_{nm}\n    .set psx_{nm}, 0x{a & 0x0FFFFFFF:08X}\n")
        # The memory beyond the image: the game's uninitialised variables live
        # there, and the reference must be able to touch them like the console.
        f.write('    .section .psxbss,"aw",@nobits\n    .space 0x180000\n')
    src = HARNESS % dict(
        decl="\n".join("unsigned int psx_%s();" % n for n in funcs),
        bufdecl='static unsigned char buf[%d] __attribute__((section(".psxbuf"), aligned(16)));' % SIZE,
        size=SIZE, rounds=ROUNDS, dir=D,
        names=", ".join('"%s"' % n for n in funcs),
        fns=", ".join("psx_%s" % n for n in funcs),
        rets=", ".join("1" if writes_v0(recomp.words_from_exe(EXE, *find(n))) else "0" for n in funcs),
        setup="memcpy(buf, V[k].b, %d);" % SIZE,
        a0="(unsigned int)buf + V[k].a[0]", a1="(unsigned int)buf + V[k].a[1]",
        peek="buf[i]", base="buf", extra="", preload="")
    open(D + "/ref_main.c", "w").write(src)
    subprocess.run(["mipsel-linux-gnu-gcc", "-static", "-O1", "-w", "-o", D + "/ref",
                    "-Wl,--section-start=.psx=0x00010000",
                    "-Wl,--section-start=.psxbss=0x00080000",
                    "-Wl,--section-start=.psxbuf=0x%08X" % BUF,
                    D + "/ref_main.c", D + "/ref_code.s"], check=True)
    return subprocess.run(["qemu-mipsel", D + "/ref"], capture_output=True,
                          text=True).stdout


def build_translated(funcs):
    # Every translatable function, not only the ones being compared: a function
    # under test may call others, and its callee has to exist.
    allf = open(D + "/list2.txt").read().split()
    called = set()
    for nm in allf:
        a, c = find(nm)
        ws = recomp.words_from_exe(EXE, a, c)
        for i, w in enumerate(ws):
            if (w >> 26) == 3:
                t = ((a + 4 * i) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                if t in recomp.SYMS:
                    called.add(recomp.SYMS[t])
    stubs = sorted(called - set(allf))
    parts = ['#include "rt.h"', "u8 RAM[0x200000];", "u32 g_sp;",
             "/* Stubs for the untranslatable callees -- the GTE, for the most",
             "   part. Any function that reaches one is dropped from the",
             "   comparison: see clean_set(). */"]
    parts += ["u32 psx_%s(u32 a, u32 b, u32 c, u32 d) { (void)a;(void)b;(void)c;(void)d; return 0; }" % n
              for n in stubs]
    for nm in allf:
        a, c = find(nm)
        parts.append(recomp.translate("psx_" + nm, a, recomp.words_from_exe(EXE, a, c)))
    open(D + "/gen.c", "w").write("\n".join(parts))
    src = HARNESS % dict(
        bufdecl="",
        decl='#include "rt.h"\nextern u8 RAM[0x200000];\n' +
             "\n".join("unsigned int psx_%s();" % n for n in funcs),
        size=SIZE, rounds=ROUNDS, dir=D,
        names=", ".join('"%s"' % n for n in funcs),
        fns=", ".join("psx_%s" % n for n in funcs),
        rets=", ".join("1" if writes_v0(recomp.words_from_exe(EXE, *find(n))) else "0" for n in funcs),
        setup="memcpy(RAM + %d, V[k].b, %d);" % (BUF, SIZE),
        a0="%d + V[k].a[0]" % BUF, a1="%d + V[k].a[1]" % BUF,
        peek="RAM[%d + i]" % BUF, base=str(BUF),
        preload='{ FILE *g = fopen("%s/psx.img","rb"); if (!g || fread(RAM + 0x10000, 423936, 1, g) != 1) return 1; fclose(g); }' % D,
        extra="g_sp = 0x001FFF00; SW(0x001FFF10, V[k].a[2]); SW(0x001FFF14, V[k].a[3]);"
              " SW(0x001FFF18, V[k].a[0]); SW(0x001FFF1C, V[k].a[1]);")
    open(D + "/gen_main.c", "w").write(src)
    subprocess.run(["gcc", "-O1", "-w", "-I" + D, "-o", D + "/gen",
                    D + "/gen_main.c", D + "/gen.c"], check=True)
    return subprocess.run([D + "/gen"], capture_output=True, text=True).stdout


def call_graph():
    """Who calls whom, to know what is verifiable end to end."""
    g = {}
    for a, nm in recomp.SYMS.items():
        _, c = find(nm)
        ws = recomp.words_from_exe(EXE, a, c)
        out = set()
        for i, w in enumerate(ws):
            if (w >> 26) == 3:
                t = ((a + 4 * i) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)
                if t in recomp.SYMS:
                    out.add(recomp.SYMS[t])
        g[nm] = out
    return g


def clean_set(translatable):
    """Translatable functions all of whose callees are too, transitively.

    A function that reaches a stub cannot be compared: the reference would
    execute the real callee, the translation a hole. Excluding them is the only
    way to keep the result meaning what it is taken to mean.
    """
    g = call_graph()
    ok = set(translatable)
    changed = True
    while changed:
        changed = False
        for nm in list(ok):
            if not g.get(nm, set()) <= ok:
                ok.discard(nm)
                changed = True
    return ok


funcs = sys.argv[1:]
_tr = set(open(D + "/list2.txt").read().split())
_clean = clean_set(_tr)
_dropped = [f for f in funcs if f not in _clean]
funcs = [f for f in funcs if f in _clean]
print("%d functions dropped because they reach an untranslatable callee"
      % len(_dropped), flush=True)
make_vectors()
t = time.time(); ref = build_reference(funcs).splitlines()
print("reference   : %5.1f s" % (time.time() - t), flush=True)
crashed = {l.split()[0] for l in ref if l.endswith("DROPPED")}
surv = [f for f in funcs if f not in crashed]
ref = [l for l in ref if l.split()[0] in set(surv)]
t = time.time(); tr = build_translated(surv).splitlines()
print("translation : %5.1f s" % (time.time() - t), flush=True)
n = min(len(ref), len(tr))
bad = [i for i in range(n) if ref[i] != tr[i]]
print("%d functions requested, %d dropped (invalid inputs or endless loop)"
      % (len(funcs), len(crashed)))
print("%d cases compared over %d functions" % (n, len(surv)))
if bad:
    print("%d DIVERGENCES. First one:" % len(bad))
    print("  real MIPS   :", ref[bad[0]][:120])
    print("  translation :", tr[bad[0]][:120])
else:
    print("NO DIVERGENCE.")
