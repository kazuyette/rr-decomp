#!/usr/bin/env python3
"""Honest progress report for rr-decomp.

objdiff cannot answer "how much is decompiled": a function pulled in with
INCLUDE_ASM assembles to the original bytes, so it always matches. The real
question is a source-level one -- is this function written in C, or is it
still a reference to a disassembly listing?

The function list and the instruction counts come from build/asm/29E8.o,
the reassembled target. They used to come from the listings under
asm/nonmatchings/, which was wrong in a way that only showed once asm/
stopped being committed: splat writes a listing only for functions still
referenced by INCLUDE_ASM, so every function successfully converted
*disappeared from the denominator*. The report read 0 / 609 at the exact
moment it should have read 214 / 949.

Usage: python3 tools/progress.py [--json]   (needs `make all` first)
"""
import glob
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from verify import disassemble  # noqa: E402
from units import TARGETS  # noqa: E402

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
INCLUDE_ASM_RE = re.compile(r'^\s*INCLUDE_ASM\("([^"]+)",\s*(\w+)\);', re.M)
INSN_RE = re.compile(r'/\* \w+ [0-9A-Fa-f]{8} [0-9A-Fa-f]{8} \*/')


def asm_sizes():
    """Instruction count per function, from the reassembled targets."""
    out = {}
    for obj in TARGETS:
        path = os.path.join(ROOT, obj)
        if not os.path.exists(path):
            return {}
        out.update({n: len(ins) for n, ins in disassemble(path).items()})
    return out


ASM_DEF = re.compile(r'"\s*\.global\s+(\w+)\\n"')


def asm_definitions(text):
    """Functions written as a top-level __asm__ block naming their symbol.

    The COP2 accessors and the BIOS trampolines live this way because
    GCC 2.7.2 has no intrinsic for either, and PSY-Q's own headers wrapped
    the same instructions in macros. They are legitimately part of the
    tree -- but they are not recovered C, and counting them as such would
    repeat the mistake this repository was restarted to undo.

    They are reported separately and, crucially, kept in the denominator.
    Leaving them out of both sides would make the percentage rise every
    time one was written, which is progress measured by deleting the
    problem.
    """
    return set(ASM_DEF.findall(text))


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
    # Le garde-fou porte sur les tailles, pas sur le nombre de fonctions. Sans
    # les objets reassembles, `sizes` est vide : les deux ensembles se vident
    # par intersection, le total reste non nul grace aux seules references, et
    # la division par le nombre d'instructions eclatait. Un depot fraichement
    # clone tombait ainsi sur une trace d'exception la ou la premiere commande
    # du README l'envoyait.
    if not sizes:
        print("nothing to report -- build/asm/*.o missing, run `make all` first")
        return 1
    asm_refs, c_funcs, asm_funcs = set(), set(), set()
    for path in sorted(glob.glob(os.path.join(ROOT, "src", "*.c"))):
        text = open(path).read()
        refs = {name for _, name in INCLUDE_ASM_RE.findall(text)}
        asm_refs |= refs
        c_funcs |= c_definitions(text) - refs
        asm_funcs |= asm_definitions(text)

    # only count functions that correspond to a real disassembled function
    c_funcs &= set(sizes)
    asm_funcs = (asm_funcs & set(sizes)) - c_funcs
    total = len(asm_refs) + len(c_funcs) + len(asm_funcs)
    if not total:
        print("nothing to report -- build/asm/*.o missing, run `make all` first")
        return 1

    c_insns = sum(sizes.get(n, 0) for n in c_funcs)
    inline_insns = sum(sizes.get(n, 0) for n in asm_funcs)
    asm_insns = sum(sizes.get(n, 0) for n in asm_refs)
    tot_insns = c_insns + inline_insns + asm_insns

    if "--json" in sys.argv:
        print(json.dumps({
            "functions_total": total,
            "functions_c": len(c_funcs),
            "functions_inline_asm": len(asm_funcs),
            "instructions_total": tot_insns,
            "instructions_c": c_insns,
            "instructions_inline_asm": inline_insns,
        }, indent=2))
        return 0

    print(f"functions     {len(c_funcs):5d} / {total:5d}   "
          f"{100.0 * len(c_funcs) / total:5.1f}%  real C")
    print(f"instructions  {c_insns:5d} / {tot_insns:5d}   "
          f"{100.0 * c_insns / tot_insns:5.1f}%  real C")
    print(f"              {len(asm_funcs):5d} function(s) / {inline_insns} instruction(s) "
          f"are __asm__ blocks -- counted apart, kept in the denominator")
    print()
    print("Remaining largest functions still on INCLUDE_ASM:")
    for name in sorted(asm_refs, key=lambda n: -sizes.get(n, 0))[:10]:
        print(f"  {sizes.get(name, 0):5d}  {name}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
