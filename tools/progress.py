#!/usr/bin/env python3
"""Honest progress report for rr-decomp.

objdiff cannot answer "how much is decompiled": a function pulled in with
INCLUDE_ASM assembles to the original bytes, so it always matches. The real
question is a source-level one -- is this function written in C, or is it
still a reference to a disassembly listing? -- so it is answered here, by
reading src/*.c and asm/nonmatchings/.

Usage: python3 tools/progress.py [--json]
"""
import glob
import json
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INCLUDE_ASM_RE = re.compile(r'^\s*INCLUDE_ASM\("([^"]+)",\s*(\w+)\);', re.M)
INSN_RE = re.compile(r'/\* \w+ [0-9A-Fa-f]{8} [0-9A-Fa-f]{8} \*/')


def asm_sizes():
    """Instruction count per function, from the splat listings."""
    out = {}
    for path in glob.glob(os.path.join(ROOT, "asm", "nonmatchings", "**", "*.s"),
                          recursive=True):
        name = os.path.basename(path)[:-2]
        with open(path) as fh:
            out[name] = len(INSN_RE.findall(fh.read()))
    return out


def c_definitions(text):
    """Top-level function definitions in a translation unit."""
    stripped = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    stripped = re.sub(r"//[^\n]*", "", stripped)
    found, depth = set(), 0
    for m in re.finditer(r"[{}]|([A-Za-z_]\w*)\s*\(", stripped):
        if m.group(0) == "{":
            depth += 1
        elif m.group(0) == "}":
            depth -= 1
        elif depth == 0 and m.group(1):
            j, d = m.end() - 1, 0
            while j < len(stripped):
                if stripped[j] == "(":
                    d += 1
                elif stripped[j] == ")":
                    d -= 1
                    if d == 0:
                        break
                j += 1
            k = j + 1
            while k < len(stripped) and stripped[k] in " \t\r\n":
                k += 1
            if k < len(stripped) and stripped[k] == "{":
                found.add(m.group(1))
    return found


def main():
    sizes = asm_sizes()
    asm_refs, c_funcs = set(), set()
    for path in sorted(glob.glob(os.path.join(ROOT, "src", "*.c"))):
        text = open(path).read()
        refs = {name for _, name in INCLUDE_ASM_RE.findall(text)}
        asm_refs |= refs
        c_funcs |= c_definitions(text) - refs

    # only count C functions that correspond to a real disassembled function
    c_funcs &= set(sizes)
    total = len(asm_refs) + len(c_funcs)
    if not total:
        print("nothing to report -- run splat first")
        return 1

    c_insns = sum(sizes.get(n, 0) for n in c_funcs)
    asm_insns = sum(sizes.get(n, 0) for n in asm_refs)
    tot_insns = c_insns + asm_insns

    if "--json" in sys.argv:
        print(json.dumps({
            "functions_total": total,
            "functions_c": len(c_funcs),
            "instructions_total": tot_insns,
            "instructions_c": c_insns,
        }, indent=2))
        return 0

    print(f"functions     {len(c_funcs):5d} / {total:5d}   "
          f"{100.0 * len(c_funcs) / total:5.1f}%  real C")
    print(f"instructions  {c_insns:5d} / {tot_insns:5d}   "
          f"{100.0 * c_insns / tot_insns:5.1f}%  real C")
    print()
    print("Remaining largest functions still on INCLUDE_ASM:")
    for name in sorted(asm_refs, key=lambda n: -sizes.get(n, 0))[:10]:
        print(f"  {sizes.get(name, 0):5d}  {name}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
