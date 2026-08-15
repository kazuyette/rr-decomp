#!/usr/bin/env python3
"""Look for the original translation-unit boundaries in the game region.

The library seam at 0x8003FA94 was easy: a library object cannot call into
the game that links it, so there was one address above which no call went
downwards, and it was unique. Inside the game there is no such rule --
game objects call each other in both directions -- so no single test
settles it and the answer has to be triangulated.

Three independent signals, printed side by side so they can be compared
rather than blended into one number nobody can check:

1. Call locality. Within one object calls are dense; across objects they
   are sparser. For each gap between adjacent functions this counts the
   calls that step over it, ignoring long-range calls, which say nothing
   about local grouping. A real boundary shows up as a local minimum.

2. Rodata anchors. The linker lays out .text and .rodata of each object in
   the same order, so a function's rodata references advance monotonically
   with its address -- measured here at 5 violations in 37 referencing
   functions, i.e. the assumption holds. Each step in the rodata range is
   therefore a boundary, though only 37 of 407 functions reference rodata
   at all, so this signal is exact but sparse.

3. Compiler flags. One object is compiled with one set of flags, so two
   adjacent functions needing different pipelines cannot share an object.
   This is the strongest signal in principle and currently the weakest in
   practice: only functions matching under exactly ONE pipeline
   discriminate, and pipelines.json has to exist for any of it to be
   available. Short functions usually match under several and are dropped
   here rather than counted as evidence.

A boundary supported by two of the three is worth acting on. One alone is
a hypothesis.

Usage: python3 tools/modules.py [--json]
"""
import glob
import json
import os
import re
import sys

GAME_HI = 0x8003FA94        # the library seam; everything below is game code
RO_LO, RO_HI = 0x80010000, 0x800121F4
WINDOW = 30                 # calls longer than this are not local evidence


def load():
    """{func: (address, callees)} for every function with a listing."""
    out = {}
    for path in glob.glob(os.path.join("asm", "nonmatchings", "*", "*.s")):
        text = open(path).read()
        first = re.search(r"/\*\s*\w+\s+([0-9A-F]{8})", text)
        if not first:
            continue
        name = os.path.basename(path)[:-2]
        refs = set()
        for sym in re.findall(r"%(?:hi|lo)\((\w+)\)", text):
            m = re.match(r"(?:D_|jtbl_|_)?([0-9A-F]{8})$", sym)
            if m and RO_LO <= int(m.group(1), 16) < RO_HI:
                refs.add(int(m.group(1), 16))
        out[name] = (int(first.group(1), 16),
                     set(re.findall(r"\bjal\s+(\w+)", text)), refs)
    return out


def main():
    funcs = load()
    if not funcs:
        print("no listings -- run `make setup` first")
        return 1
    game = sorted((a, n, calls, refs) for n, (a, calls, refs) in funcs.items()
                  if a < GAME_HI)
    index = {n: i for i, (_a, n, _c, _r) in enumerate(game)}

    # 1. windowed call cut
    cut = [0] * (len(game) + 1)
    for _a, n, calls, _r in game:
        for callee in calls:
            if callee not in index:
                continue
            lo, hi = sorted((index[n], index[callee]))
            if hi - lo > WINDOW:
                continue
            for b in range(lo + 1, hi + 1):
                cut[b] += 1

    # 2. rodata anchors: a boundary sits where the referenced range steps up
    anchors = set()
    high = 0
    for i, (_a, _n, _c, refs) in enumerate(game):
        if refs and min(refs) > high:
            anchors.add(i)
        if refs:
            high = max(high, max(refs))

    # 3. discriminating pipelines
    unique = {}
    if os.path.exists("pipelines.json"):
        for name, pipes in json.load(open("pipelines.json")).items():
            if len(set(pipes)) == 1 and name in index:
                unique[index[name]] = pipes[0]
    flag_seams = {i for i in unique
                  if any(j in unique and unique[j] != unique[i]
                         for j in (i - 1, i + 1))}

    seams, prev = [], -9
    for b in range(WINDOW, len(game) - WINDOW):
        local = cut[max(0, b - 8):b + 8]
        support = (cut[b] == min(local) and cut[b] <= 2) + (b in anchors) \
            + (b in flag_seams)
        if support >= 1 and b - prev > 4:
            seams.append((b, support))
            prev = b

    if "--json" in sys.argv:
        print(json.dumps([{"address": game[b][0], "function": game[b][1],
                           "support": s} for b, s in seams], indent=1))
        return 0

    print(f"{len(game)} game functions, "
          f"{len(unique)} with a discriminating pipeline "
          f"({'pipelines.json missing' if not unique else 'from pipelines.json'})")
    print(f"\n{len(seams)} candidate boundaries "
          f"(support = how many of the three signals agree):\n")
    for b, s in seams:
        why = []
        if cut[b] <= 2:
            why.append(f"cut={cut[b]}")
        if b in anchors:
            why.append("rodata")
        if b in flag_seams:
            why.append(f"flags:{unique[b]}")
        print(f"  {s}  0x{game[b][0]:08X}  {game[b][1]:24s} {', '.join(why)}")
    print("\nTwo signals or more is worth acting on. One is a hypothesis.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
