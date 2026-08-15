#!/usr/bin/env python3
"""Move functions that fail verification back to INCLUDE_ASM.

This is what makes large speculative batches safe. Write fifty conversions,
build, verify; whatever does not match goes straight back to referencing the
disassembly, and the build stays green. A failed guess costs one line in the
generated file, not an evening of bisecting.

It runs tools/verify.py, collects the mismatching symbols, comments the
matching definitions out of the hand-written unit they were added to, and
restores their INCLUDE_ASM line in the generated unit.

Usage:
  python3 tools/revert_failed.py            # act
  python3 tools/revert_failed.py --dry-run  # just say what would move
"""
import os
import re
import subprocess
import sys

GENERATED = "src/29E8.c"
SEGMENT = "asm/nonmatchings/29E8"
# Every hand-written unit: a conversion can have landed in any of them, and
# tools/apply_sweep.py creates new ones (src/x_<pipeline>_NN.c) as it goes,
# so this is discovered rather than listed.
UNITS = sorted("src/" + f for f in os.listdir("src")
               if f.endswith(".c") and f != "29E8.c")
# never touch these: known, documented exceptions
KEEP = {"_start"}


def failing():
    out = subprocess.run([sys.executable, "tools/verify.py"],
                         capture_output=True, text=True).stdout
    return [n for n in re.findall(r"^  DIFF (\S+)", out, re.M) if n not in KEEP]


def definition_span(text, name):
    """(start, end) of a top-level `... name(...) { ... }` definition."""
    m = re.search(r"^[A-Za-z_][\w \*]*?\b" + re.escape(name) + r"\s*\([^;{]*\)\s*\{",
                  text, re.M)
    if not m:
        return None
    i, depth = m.end() - 1, 0
    while i < len(text):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return (m.start(), i + 1)
        i += 1
    return None



def regenerate_missing_listings(names):
    """Re-run splat if any restored function has no listing.

    splat writes asm/nonmatchings/<unit>/<func>.s only for functions the
    unit still references with INCLUDE_ASM. A function that was real C at
    `make setup` time therefore has no listing on disk -- and sending it
    back to INCLUDE_ASM points the build at a file that does not exist.
    That is not a hypothetical: it broke the build the first time a batch
    was reverted after a clean setup.
    """
    missing = [n for n in names
               if not os.path.exists(os.path.join(SEGMENT, n + ".s"))]
    if not missing:
        return
    print(f"{len(missing)} restored function(s) have no listing "
          f"(e.g. {missing[0]}); re-running tools/setup.py.")
    r = subprocess.run([sys.executable, "tools/setup.py"])
    if r.returncode != 0:
        # Not a warning. A half-written asm/29E8.s still assembles, so the
        # build stays green and every number afterwards is quietly wrong
        # -- the target shrinks, and functions that were converted look
        # like they never existed.
        print("\ntools/setup.py FAILED. asm/ may be incomplete; do not "
              "trust verify.py or progress.py until `make setup` succeeds.")
        sys.exit(r.returncode)


def main():
    dry = "--dry-run" in sys.argv
    names = failing()
    if not names:
        print("nothing failing -- all conversions match")
        return 0
    print(f"{len(names)} function(s) failing verification:")

    gen = open(GENERATED).read()
    moved = []
    for name in names:
        for unit in UNITS:
            try:
                text = open(unit).read()
            except FileNotFoundError:
                continue
            span = definition_span(text, name)
            if not span:
                continue
            body = text[span[0]:span[1]]
            note = (f"/* Did not match; reverted to INCLUDE_ASM.\n"
                    f" * Kept here as a starting point for the next attempt.\n")
            commented = note + " * " + body.replace("\n", "\n * ") + "\n */"
            if not dry:
                open(unit, "w").write(text[:span[0]] + commented + text[span[1]:])
            if f'INCLUDE_ASM("{SEGMENT}", {name});' not in gen:
                gen += f'\nINCLUDE_ASM("{SEGMENT}", {name});\n'
            moved.append((name, unit))
            break
        else:
            print(f"  ?    {name}: no definition found in the hand-written units")

    if not dry:
        open(GENERATED, "w").write(gen)
        regenerate_missing_listings([n for n, _ in moved])
    for name, unit in moved:
        print(f"  <--  {name}  (commented out in {unit})")
    print(f"\n{len(moved)} reverted{' (dry run, nothing written)' if dry else ''}."
          f" Rebuild and verify again.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
