#!/usr/bin/env python3
"""Banc d'essai du traducteur, deuxième version : entrées hors du source.

La première version écrivait les vecteurs d'essai en littéraux C. Pour douze
fonctions cela faisait déjà 276 Ko de source, et la compilation s'écroulait
bien avant d'atteindre l'échelle voulue -- six minutes quarante pour douze
fonctions, dont 0,2 seconde de calcul. Le reste était de l'attente.

La correction ne consiste pas à optimiser la génération mais à supprimer sa
cause : les entrées vivent dans un fichier binaire que les deux harnais lisent
à l'exécution. Le source redevient minuscule et constant, quel que soit le
nombre de vecteurs.

Le reste du protocole est inchangé, et c'est lui qui compte : la référence est
le vrai code du retail exécuté sous qemu-mipsel, pas une lecture de ce code.
"""
import random
import struct
import subprocess
import sys
import time

sys.path.insert(0, "/tmp/rrdecomp/tools")
import recomp

EXE = "/tmp/rr/files/PSX.EXE"
ASMS = ["/tmp/rrdecomp/asm/psyq.s", "/tmp/rrdecomp/asm/29E8.s"]
D = "/tmp/recomp"
BUF = 0x00100000   # meme adresse absolue des deux cotes : certaines fonctions
                   # calculent sur la valeur du pointeur, pas seulement sur ce
                   # qu'il designe
SIZE = 256
ROUNDS = 16
BASE = 0x00010000


def writes_v0(words):
    """Vrai si la fonction ecrit $v0 quelque part."""
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
    raise SystemExit("fonction introuvable : " + nm)


def make_vectors():
    rnd = random.Random(20260816)
    with open(D + "/vec.bin", "wb") as f:
        for _ in range(ROUNDS):
            f.write(bytes(rnd.randrange(256) for _ in range(SIZE)))
            # Pointeurs alignés sur 4 : le MIPS lève SIGBUS sur un lw désaligné,
            # exactement comme la console. Le banc ne doit poser que des
            # questions que le vrai matériel pouvait entendre.
            f.write(struct.pack("<4I", 4 * rnd.randrange(16), 4 * rnd.randrange(16),
                                rnd.randrange(0x100), rnd.randrange(0x100)))


HARNESS = r"""
/* Isolation par processus plutôt que par longjmp.

   La première version attrapait les fautes avec sigsetjmp/siglongjmp depuis un
   gestionnaire de signal. Deux choses l'ont mise en échec : glibc refuse un
   longjmp qui remonte vers un cadre de pile qu'il juge non initialisé
   (« longjmp causes uninitialized stack frame »), et une fonction partie en
   boucle sans fin -- func_80045334 sur un tampon quelconque -- n'était pas
   rattrapée du tout.

   Un fils par fonction, une alarme dans le fils, le père qui récolte : une
   fonction qui faute ou qui boucle tue son fils et rien d'autre. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
%(decl)s
%(bufdecl)s
struct vec { unsigned char b[%(size)d]; unsigned int a[4]; };
static struct vec V[%(rounds)d];
/* Six arguments : certaines fonctions lisent leur cinquieme parametre en
   0x10($sp), la ou l'appelant l'a depose. Avec quatre, elles lisaient de la
   pile non initialisee -- differente des deux cotes, et la comparaison
   echouait pour une raison qui n'a rien a voir avec la traduction. */
typedef unsigned int (*fn_t)(unsigned int, unsigned int, unsigned int, unsigned int,
                             unsigned int, unsigned int);
static const char *NAMES[] = { %(names)s };
static const fn_t FNS[] = { %(fns)s };
/* Une fonction qui n'ecrit jamais $v0 n'a pas de valeur de retour : ce que le
   contexte y avait laisse n'est pas comparable. On ne l'imprime que pour les
   fonctions dont le desassemblage montre une ecriture de ce registre. */
static const int RETS[] = { %(rets)s };
int main(void)
{
    FILE *f = fopen("%(dir)s/vec.bin", "rb");
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
                %(extra)s rv = FNS[j](%(a0)s, %(a1)s, V[k].a[2], V[k].a[3], V[k].a[2], V[k].a[3]);
                /* Un retour qui pointe dans le tampon est une adresse : elle
                   ne peut pas coincider entre les deux harnais, dont les
                   tampons vivent ailleurs. On l'imprime relative a sa base. */
                if (RETS[j]) {
                    unsigned int b = (unsigned int)(%(base)s);
                    if (rv >= b && rv < b + %(size)d) printf("%%s %%d rv=@+%%x", NAMES[j], k, rv - b);
                    else printf("%%s %%d rv=%%08x", NAMES[j], k, rv);
                }
                else printf("%%s %%d (sans retour)", NAMES[j], k);
                for (i = 0; i < %(size)d; i++) printf(" %%02x", %(peek)s);
                printf("\n");
            }
            fflush(stdout);
            _exit(0);
        }
        waitpid(pid, &st, 0);
        if (st != 0) printf("%%s ECARTEE\n", NAMES[j]);
        fflush(stdout);
    }
    return 0;
}
"""

def build_reference(funcs):
    words = {nm: (find(nm)[0], recomp.words_from_exe(EXE, *find(nm))) for nm in funcs}
    with open(D + "/ref_code.s", "w") as f:
        f.write('    .set noreorder\n    .section .psx,"ax",@progbits\n')
        for nm, (a, ws) in sorted(words.items(), key=lambda kv: kv[1][0]):
            # Les sauts absolus n'encodent que 28 bits : chaque fonction doit
            # retrouver son adresse d'origine masquée, sinon ses `j` partent
            # dans le vide.
            f.write(f"    .org 0x{(a & 0x0FFFFFFF) - BASE:X}\n")
            f.write(f"    .globl psx_{nm}\npsx_{nm}:\n")
            for w in ws:
                f.write(f"    .word 0x{w:08X}\n")
    src = HARNESS % dict(
        decl="\n".join("unsigned int psx_%s();" % n for n in funcs),
        bufdecl='static unsigned char buf[%d] __attribute__((section(".psxbuf"), aligned(16)));' % SIZE,
        size=SIZE, rounds=ROUNDS, dir=D,
        names=", ".join('"%s"' % n for n in funcs),
        fns=", ".join("psx_%s" % n for n in funcs),
        rets=", ".join("1" if writes_v0(recomp.words_from_exe(EXE, *find(n))) else "0" for n in funcs),
        setup="memcpy(buf, V[k].b, %d);" % SIZE,
        a0="(unsigned int)buf + V[k].a[0]", a1="(unsigned int)buf + V[k].a[1]",
        peek="buf[i]", base="buf", extra="")
    open(D + "/ref_main.c", "w").write(src)
    subprocess.run(["mipsel-linux-gnu-gcc", "-static", "-O1", "-o", D + "/ref",
                    "-Wl,--section-start=.psx=0x%08X" % BASE,
                    "-Wl,--section-start=.psxbuf=0x%08X" % BUF,
                    D + "/ref_main.c", D + "/ref_code.s"], check=True)
    return subprocess.run(["qemu-mipsel", D + "/ref"], capture_output=True,
                          text=True).stdout


def build_translated(funcs):
    parts = ['#include "rt.h"', "u8 RAM[0x200000];"]
    for nm in funcs:
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
        extra="SW(0x001FFF10, V[k].a[2]); SW(0x001FFF14, V[k].a[3]);")
    open(D + "/gen_main.c", "w").write(src)
    subprocess.run(["gcc", "-O1", "-w", "-I" + D, "-o", D + "/gen",
                    D + "/gen_main.c", D + "/gen.c"], check=True)
    return subprocess.run([D + "/gen"], capture_output=True, text=True).stdout


funcs = sys.argv[1:]
make_vectors()
t = time.time(); ref = build_reference(funcs).splitlines()
print("reference   : %5.1f s" % (time.time() - t), flush=True)
crashed = {l.split()[0] for l in ref if l.endswith("ECARTEE")}
surv = [f for f in funcs if f not in crashed]
ref = [l for l in ref if l.split()[0] in set(surv)]
t = time.time(); tr = build_translated(surv).splitlines()
print("traduction  : %5.1f s" % (time.time() - t), flush=True)
n = min(len(ref), len(tr))
bad = [i for i in range(n) if ref[i] != tr[i]]
print("%d fonctions demandees, %d ecartees (entrees invalides ou boucle sans fin)"
      % (len(funcs), len(crashed)))
print("%d cas compares sur %d fonctions" % (n, len(surv)))
if bad:
    print("%d DIVERGENCES. Premiere :" % len(bad))
    print("  vrai MIPS  :", ref[bad[0]][:120])
    print("  traduction :", tr[bad[0]][:120])
else:
    print("AUCUNE DIVERGENCE.")
