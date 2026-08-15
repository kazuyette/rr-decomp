#!/usr/bin/env python3
"""Compare the bytes of converted functions against the original binary.

objdiff-cli does this properly and with a UI; this is the minimum needed to
answer one question from inside the toolchain image: for a function now
written in C, does the compiler emit exactly the bytes the retail EXE has?

It reads the two objects the Makefile already produces:
  build/asm/29E8.o  -- the disassembly reassembled, i.e. ground truth
  build/matched.o   -- everything built from src/

Debug labels emitted by -gcoff (LM1, LM2, ...) appear as symbols in the C
build and would otherwise cut functions short, so they are skipped.

Usage:
  python3 tools/verify.py                 # every function present in both
  python3 tools/verify.py func_80045718   # just these
"""
import re
import subprocess
import sys

OBJDUMP = "mipsel-linux-gnu-objdump"
TARGET = "build/asm/29E8.o"
BASE = "build/matched.o"

HEADER = re.compile(r"^[0-9a-f]+ <([^>]+)>:")
INSN = re.compile(r"^\s+[0-9a-f]+:\s+([0-9a-f]{8})\s")
LABEL = re.compile(r"^(LM\d+|\$L\w+|\.L\w+)$")


def disassemble(path):
    """{symbol: [instruction words]} from one object file."""
    out = subprocess.run([OBJDUMP, "-d", path],
                         capture_output=True, text=True, check=True).stdout
    funcs, cur = {}, None
    for line in out.splitlines():
        h = HEADER.match(line)
        if h:
            name = h.group(1)
            if LABEL.match(name):
                continue          # debug label, not a function boundary
            cur = funcs.setdefault(name, [])
            continue
        i = INSN.match(line)
        if i and cur is not None:
            cur.append(i.group(1))
    return funcs


def main():
    target, base = disassemble(TARGET), disassemble(BASE)
    wanted = sys.argv[1:] or sorted(set(target) & set(base))

    ok = bad = missing = 0
    for name in wanted:
        if name not in target or name not in base:
            print(f"  ?    {name}  (absent from {'target' if name not in target else 'base'})")
            missing += 1
            continue
        t, b = target[name], base[name][:len(target[name])]
        if t == b:
            ok += 1
            if len(sys.argv) > 1:
                print(f"  OK   {name}  ({len(t)} instructions)")
        else:
            bad += 1
            print(f"  DIFF {name}")
            for n, (x, y) in enumerate(zip(t, b)):
                if x != y:
                    print(f"         word {n}: target {x}  base {y}")
            if len(t) != len(b):
                print(f"         length: target {len(t)}, base {len(b)}")

    print(f"\n{ok} match, {bad} differ, {missing} unpaired "
          f"(of {len(wanted)} checked)")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
