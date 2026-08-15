#!/usr/bin/env python3
"""Compare converted functions against the original binary, byte for byte.

objdiff-cli does this properly and with a UI; this is the minimum needed to
answer one question from inside the toolchain image: for a function now
written in C, does the compiler emit the bytes the retail EXE has?

It diffs the two objects the build already produces:
  build/asm/29E8.o  -- the disassembly reassembled, i.e. ground truth
  build/matched.o   -- everything built from src/

Relocated fields are masked out before comparing. Neither object is linked,
so a jal target or a %hi/%lo pair holds a placeholder that legitimately
differs between the two -- comparing raw words reports every function with a
call as a mismatch. What is compared is the instruction encoding minus the
part the linker will fill in; the relocation entries themselves (type and
target symbol) are compared separately, which is what actually matters.

-gcoff emits debug labels (LM1, ...) that appear as symbols in the C build
and would cut functions short, so they are skipped. Trailing nop padding is
ignored.

Usage:
  python3 tools/verify.py                 # every function present in both
  python3 tools/verify.py func_80045718   # just these
  python3 tools/verify.py --verbose       # list matches too
"""
import re
import subprocess
import sys

OBJDUMP = "mipsel-linux-gnu-objdump"
TARGET = "build/asm/29E8.o"
BASE = "build/matched.o"

HEADER = re.compile(r"^[0-9a-f]+ <([^>]+)>:")
INSN = re.compile(r"^\s+([0-9a-f]+):\s+([0-9a-f]{8})\s")
RELOC = re.compile(r"^\s+[0-9a-f]+:\s+(R_MIPS_\w+)\s+(\S+)")

# How much of the instruction the linker owns, per relocation type.
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


def disassemble(path):
    """{symbol: [(masked_word, reloc_type, reloc_symbol), ...]}"""
    out = subprocess.run([OBJDUMP, "-dr", path],
                         capture_output=True, text=True, check=True).stdout
    funcs, cur = {}, None
    for line in out.splitlines():
        h = HEADER.match(line)
        if h:
            name = h.group(1)
            if re.match(r"^(LM\d+|\$L\w+|\.L\w+)$", name):
                continue
            cur = funcs.setdefault(name, [])
            continue
        r = RELOC.match(line)
        if r and cur:
            word, _, _ = cur[-1]
            rtype, rsym = r.group(1), r.group(2)
            cur[-1] = (word & ~MASK.get(rtype, 0), rtype, rsym)
            continue
        i = INSN.match(line)
        if i and cur is not None:
            cur.append((int(i.group(2), 16), None, None))
    # drop trailing nop padding
    for name, ins in funcs.items():
        while len(ins) > 1 and ins[-1] == (0, None, None):
            ins.pop()
    return funcs


def main():
    verbose = "--verbose" in sys.argv
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    target, base = disassemble(TARGET), disassemble(BASE)
    wanted = args or sorted(set(target) & set(base))

    ok = bad = missing = 0
    for name in wanted:
        if name not in target or name not in base:
            print(f"  ?    {name}  (absent from "
                  f"{'target' if name not in target else 'base'})")
            missing += 1
            continue
        t, b = target[name], base[name]
        if t == b:
            ok += 1
            if verbose or args:
                print(f"  OK   {name}  ({len(t)} instructions)")
            continue
        bad += 1
        print(f"  DIFF {name}")
        for n, (x, y) in enumerate(zip(t, b)):
            if x != y:
                what = "encoding" if x[0] != y[0] else "relocation"
                print(f"         word {n} ({what}): "
                      f"target {x[0]:08x} {x[1] or ''} {x[2] or ''} | "
                      f"base {y[0]:08x} {y[1] or ''} {y[2] or ''}")
        if len(t) != len(b):
            print(f"         length: target {len(t)}, base {len(b)}")

    print(f"\n{ok} match, {bad} differ, {missing} unpaired "
          f"(of {len(wanted)} checked)")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
