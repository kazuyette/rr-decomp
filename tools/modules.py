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

WHAT THIS TOOL FOUND, AND WHY IT IS KEPT ANYWAY
-----------------------------------------------
It found nothing. Over 407 game functions: 32 rodata anchors, 45 call-cut
minima, and not one boundary carrying two signals.

That could just mean the signals are too sparse to coincide, so the
agreement was measured against chance -- placing the same number of minima
at random and counting how often an anchor lands near one:

    tolerance   observed   expected by chance
      +-0           2           3.6
      +-1           7           9.6
      +-2           9          14.4
      +-3          13          18.0

Observed agreement is *below* chance at every tolerance. The two signals
are not merely failing to reinforce each other; they are mildly
anti-correlated. At least one of them is not measuring what it claims. The
likeliest culprit is the call cut: a local minimum in short-range calls
marks a stretch of large functions that call little, which has nothing to
do with where an object ended.

So the internal boundaries of the game code are NOT recoverable this way,
and the honest move is to record that rather than keep adding heuristics
until the answer comes out the way it was wanted.

Two things do survive, and they are worth keeping:

  * The rodata monotonicity itself -- 5 violations across 37 referencing
    functions -- is real. It is a constraint any proposed split must
    satisfy, even though it is far too sparse to *propose* one.
  * The pipeline signal is sound and merely starved: 19 of 214 converted
    functions discriminate today, because a short function matches under
    several pipelines. That number grows with every conversion. When a few
    hundred functions discriminate, this becomes a real partition of the
    address space, and no other signal is needed.

Which reverses the order of work. The module split is not a prerequisite
for converting functions; it is a consequence of having converted enough
of them.

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
    """{func: (address, callees, rodata refs)} for every function.

    Read from asm/<unit>.s, the whole unit disassembled, not from
    asm/nonmatchings/. splat writes a per-function listing only for
    functions still on INCLUDE_ASM, so reading those makes every function
    already converted to C vanish from the analysis -- 214 of them here,
    including their call edges, their rodata anchors and their pipeline.
    The evidence would then be missing for exactly the functions we have
    the most information about.

    This is the same mistake progress.py made, from the same assumption:
    that a listing exists for every function. It does, but only in the
    full unit dump.
    """
    out = {}
    for path in glob.glob(os.path.join("asm", "*.s")):
        if os.path.basename(path) in ("header.s",):
            continue
        name = None
        for line in open(path):
            g = re.match(r"^glabel (\w+)", line)
            if g:
                name = g.group(1)
                out.setdefault(name, [None, set(), set()])
                continue
            if name is None:
                continue
            m = re.match(r"\s*/\*\s*\w+\s+([0-9A-F]{8})\s+[0-9A-F]{8}\s*\*/\s*(\S+)(.*)",
                         line)
            if not m:
                continue
            if out[name][0] is None:
                out[name][0] = int(m.group(1), 16)
            if m.group(2) == "jal":
                callee = m.group(3).strip().split()[0] if m.group(3).strip() else ""
                if callee:
                    out[name][1].add(callee)
            for sym in re.findall(r"%(?:hi|lo)\((\w+)\)", m.group(3)):
                v = re.match(r"(?:D_|jtbl_|_)?([0-9A-F]{8})$", sym)
                if v and RO_LO <= int(v.group(1), 16) < RO_HI:
                    out[name][2].add(int(v.group(1), 16))
    return {n: tuple(v) for n, v in out.items() if v[0] is not None}


def main():
    funcs = load()
    if not funcs:
        print("no asm/<unit>.s -- run `make setup` first")
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

    source = ("from pipelines.json" if os.path.exists("pipelines.json")
              else "pipelines.json absent -- run tools/flag_sweep.py src/x_*.c")
    print(f"{len(game)} game functions, "
          f"{len(unique)} with a discriminating pipeline ({source})")
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
