#!/usr/bin/env python3
"""Say *why* a function does not match, not just that it does not.

verify.py answers one bit per function. That is enough to decide whether a
conversion may be committed and useless for making a failing one pass: a
wrong condition, a register the compiler placed differently, and an
instruction emitted in another order all look identical from the outside.

This finds the first instruction where target and base part company, shows
the neighbourhood on both sides, and puts a name on the shape of the
disagreement. The names matter more than they look: the same cause
repeats across dozens of functions, so a fix found once usually applies
many times, and grouping by pattern turns a wall of failures into a work
queue sorted by what it would take to clear it.

Patterns it distinguishes:

  branch-inverted   the same test, taken the other way round -- a `<` that
                    should be `>=`, or an if/else written the wrong way up
  operands          same instruction, different registers or immediate:
                    usually the compiler allocating differently because an
                    expression was split or combined
  swapped-pair      two adjacent instructions in the other order, which is
                    normally a delay slot filled from elsewhere
  extra / missing   one side has an instruction the other does not
  length            the functions are not the same size at all: the C says
                    something structurally different
  relocation        the encodings agree but the symbol referenced does not

Usage:
  python3 tools/whydiff.py                  # every differing function
  python3 tools/whydiff.py --summary        # pattern counts only
  python3 tools/whydiff.py func_80012345    # one function, more context
  python3 tools/whydiff.py --context 12     # widen the neighbourhood
  python3 tools/whydiff.py --brief          # one line per function
"""
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from units import TARGETS  # noqa: E402

OBJDUMP = "mipsel-linux-gnu-objdump"
BASE = "build/matched.o"
KEEP_OUT = {"_start"}          # documented exception, see verify.py

HEADER = re.compile(r"^[0-9a-f]+ <([^>]+)>:")
INSN = re.compile(r"^\s+([0-9a-f]+):\s+([0-9a-f]{8})\s+(\S+)\s*(.*?)\s*$")
RELOC = re.compile(r"^\s+[0-9a-f]+:\s+(R_MIPS_\w+)\s+(\S+)")
DEBUG_LABEL = re.compile(r"^(LM\d+|\$L\w+|\.L\w+)$")

# What the linker owns, per relocation type -- masked out before comparing,
# exactly as verify.py does. Comparing raw words reports every function
# with a call as a mismatch.
MASK = {
    "R_MIPS_26": 0x03FFFFFF,
    "R_MIPS_HI16": 0x0000FFFF,
    "R_MIPS_LO16": 0x0000FFFF,
    "R_MIPS_GPREL16": 0x0000FFFF,
    "R_MIPS_PC16": 0x0000FFFF,
    "R_MIPS_GOT16": 0x0000FFFF,
    "R_MIPS_CALL16": 0x0000FFFF,
    "R_MIPS_32": 0xFFFFFFFF,
}

# Branches that test the opposite of one another.
INVERSE = {}
for _a, _b in (("beq", "bne"), ("beqz", "bnez"), ("blez", "bgtz"),
               ("bltz", "bgez"), ("bltzl", "bgezl"), ("beql", "bnel"),
               ("bc1t", "bc1f")):
    INVERSE[_a] = _b
    INVERSE[_b] = _a


class Insn:
    __slots__ = ("word", "mnem", "args", "rtype", "rsym")

    def __init__(self, word, mnem, args):
        self.word, self.mnem, self.args = word, mnem, args
        self.rtype = self.rsym = None

    def key(self):
        """What equality means here: encoding minus the linker's part."""
        return (self.word, self.rtype, self.rsym)

    def __str__(self):
        s = f"{self.mnem:10s} {self.args}".rstrip()
        if self.rtype:
            s += f"   [{self.rtype} {self.rsym}]"
        return s


def disassemble(path):
    out = subprocess.run([OBJDUMP, "-dr", path],
                         capture_output=True, text=True, check=True).stdout
    funcs, cur = {}, None
    for line in out.splitlines():
        h = HEADER.match(line)
        if h:
            name = h.group(1)
            # A -gcoff debug label (LM1, $L3, .L7) appears *inside* a
            # function. Treating it as a new symbol truncates everything
            # after it: the first version of this tool did, and reported
            # 189 length mismatches where verify.py -- which skips these
            # and keeps filling the enclosing function -- reported one.
            # When two tools disagree about the same objects, the newer
            # one is the suspect.
            if DEBUG_LABEL.match(name):
                continue
            cur = funcs.setdefault(name, [])
            continue
        r = RELOC.match(line)
        if r and cur:
            cur[-1].rtype, cur[-1].rsym = r.group(1), r.group(2)
            cur[-1].word &= ~MASK.get(r.group(1), 0)
            continue
        m = INSN.match(line)
        if m and cur is not None:
            cur.append(Insn(int(m.group(2), 16), m.group(3), m.group(4)))
    for ins in funcs.values():
        while len(ins) > 1 and ins[-1].word == 0 and ins[-1].rtype is None:
            ins.pop()
    return funcs



SAVED = re.compile(r"^s[0-8]$|^ra$|^fp$")
BRANCHY = re.compile(r"^(jal|jalr|jr|j|b|b\w+)$")


def strip_frame(ins):
    """(frame size, saved regs, body, index map).

    The prologue is not a clean prefix: GCC interleaves register saves with
    the first instructions of the body, so scanning until the first thing
    that is not a save stops far too early -- it reported VSync's base as
    still saving s1 while the target was five instructions into its work.

    So the prologue is collected as a *set* of instructions rather than a
    span: every stack adjustment and every callee-saved store, anywhere
    before the first branch or call. The epilogue is taken from the end,
    where interleaving does not happen.

    Both are removed because both are written by the compiler from what the
    body needs. What remains is what the C actually said.
    """
    size, saved, drop = None, set(), set()
    limit = len(ins)
    for i, a in enumerate(ins):
        if BRANCHY.match(a.mnem):
            limit = i
            break
    for i in range(limit):
        a = ins[i]
        m = re.match(r"sp,sp,(-\d+)$", a.args)
        if a.mnem == "addiu" and m:
            size = -int(m.group(1))
            drop.add(i)
            continue
        m = re.match(r"(\w+),\d+\(sp\)$", a.args)
        if a.mnem in ("sw", "swc1", "sdc1") and m and SAVED.match(m.group(1)):
            saved.add(m.group(1))
            drop.add(i)
    i = len(ins)
    while i > 0:
        a = ins[i - 1]
        m = re.match(r"(\w+),\d+\(sp\)$", a.args)
        if (a.mnem == "jr" and a.args == "ra") or a.mnem == "nop" \
                or (a.mnem == "addiu" and re.match(r"sp,sp,\d+$", a.args)) \
                or (a.mnem in ("lw", "lwc1", "ldc1") and m
                    and m.group(1) in saved):
            drop.add(i - 1)
            i -= 1
            continue
        break
    keep = [i for i in range(len(ins)) if i not in drop]
    return size, saved, [ins[i] for i in keep], keep


def classify(target, base, i, k=None):
    """Name the disagreement between target[i] and base[k].

    The two indices are separate because prologues of different lengths
    shift the bodies against each other; using one index for both sides
    reads past the end of the shorter one and reports every such case as a
    length mismatch.
    """
    k = i if k is None else k
    t = target[i] if i < len(target) else None
    b = base[k] if k < len(base) else None
    if t is None or b is None:
        return "length"
    if t.word == b.word and (t.rtype, t.rsym) != (b.rtype, b.rsym):
        return "relocation"
    if INVERSE.get(t.mnem) == b.mnem:
        return "branch-inverted"
    if (i + 1 < len(target) and k + 1 < len(base)
            and target[i].key() == base[k + 1].key()
            and target[i + 1].key() == base[k].key()):
        return "swapped-pair"
    # one side skipped an instruction the other kept
    if k + 1 < len(base) and t.key() == base[k + 1].key():
        return "extra"          # base emitted one instruction too many
    if i + 1 < len(target) and b.key() == target[i + 1].key():
        return "missing"        # base is short of one instruction
    if t.mnem == b.mnem:
        return "operands"
    if len(target) != len(base):
        return "length"
    return "other"


def first_divergence(target, base, skip_t=0, skip_b=0):
    """First index (relative to each side's start offset) that differs."""
    n = min(len(target) - skip_t, len(base) - skip_b)
    for i in range(n):
        if target[skip_t + i].key() != base[skip_b + i].key():
            return i
    if len(target) - skip_t != len(base) - skip_b:
        return n
    return None


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    summary = "--summary" in sys.argv
    brief = "--brief" in sys.argv
    ctx = 4
    if "--context" in sys.argv:
        ctx = int(sys.argv[sys.argv.index("--context") + 1])
    if args:
        ctx = max(ctx, 8)

    for obj in TARGETS + [BASE]:
        if not os.path.exists(obj):
            print(f"{obj} missing -- run `make all` first")
            return 1

    target = {}
    for obj in TARGETS:
        target.update(disassemble(obj))
    base = disassemble(BASE)

    names = args or sorted(set(target) & set(base))
    findings, counts = [], {}
    for name in names:
        if name in KEEP_OUT and not args:
            continue
        if name not in target or name not in base:
            continue
        t, b = target[name], base[name]
        ft, fb = strip_frame(t), strip_frame(b)
        prologue_differs = (ft[0], ft[1]) != (fb[0], fb[1])

        if prologue_differs:
            # Compare the bodies past the prologue. The prologue itself is
            # a summary of the body's needs, so the informative question is
            # where the bodies part company, not that the frames do.
            bt, bb = ft[2], fb[2]
            j = first_divergence(bt, bb)
            note = f"frame {ft[0]} vs {fb[0]}"
            extra = (ft[1] | fb[1]) - (ft[1] & fb[1])
            if extra:
                note += ", saved " + "/".join(sorted(extra))
            if j is None:
                kind = "frame-only"
                i = ft[3][0] if ft[3] else 0
                k = fb[3][0] if fb[3] else 0
                note += " -- bodies identical"
            else:
                kind = "frame+" + classify(bt, bb, j)
                i = ft[3][j] if j < len(ft[3]) else len(t) - 1
                k = fb[3][j] if j < len(fb[3]) else len(b) - 1
        else:
            i = k = first_divergence(t, b)
            if i is None:
                if args:
                    print(f"{name}: matches ({len(t)} instructions)")
                continue
            kind, note = classify(t, b, i), ""

        counts[kind] = counts.get(kind, 0) + 1
        findings.append((kind, name, i, k, t, b, note))

    if not findings:
        print("nothing differs")
        return 0

    if brief:
        # One line per function: the diverging pair and nothing else. The
        # point is to read forty of them at once and see whether the
        # dominant pattern has a dominant cause, instead of theorising
        # from three examples -- which has now produced one refuted rule.
        findings.sort(key=lambda f: (f[0], f[1]))
        for kind, name, i, k, t_, b_, note in findings:
            tv = str(t_[i]) if i < len(t_) else "(end)"
            bv = str(b_[k]) if k < len(b_) else "(end)"
            print(f"{kind:22s} {name:24s} {i:4d}  {tv:36s} | {bv:28s} {note}")
        print()
    elif not summary:
        findings.sort(key=lambda f: (f[0], f[1]))
        for kind, name, i, k, t, b, note in findings:
            print(f"\n=== {name}: {kind} at instruction {i} "
                  f"(target {len(t)}, base {len(b)})"
                  + (f"  [{note}]" if note else ""))
            shift = k - i
            for j in range(max(0, i - ctx), min(len(t), i + ctx + 1)):
                mark = ">>" if j == i else "  "
                jb = j + shift
                tv = str(t[j]) if j < len(t) else ""
                bv = str(b[jb]) if 0 <= jb < len(b) else ""
                flag = " " if (0 <= jb < len(b)
                               and t[j].key() == b[jb].key()) else "*"
                print(f" {mark}{flag} {j:4d}  {tv:44s} | {bv}")

    print("\npattern summary:")
    for kind, n in sorted(counts.items(), key=lambda kv: -kv[1]):
        print(f"  {n:4d}  {kind}")
    print(f"  {sum(counts.values()):4d}  total")
    return 0


if __name__ == "__main__":
    sys.exit(main())
