#!/usr/bin/env python3
"""Assembles the coverage of several runs.

A single script cannot visit everything: the demo shows what the menu does not
show, and the other way round. Every run launched with `COVERAGE=file` adds
to it the states it went through; this script sums them and, above all, says
what is left.

    COVERAGE=/tmp/couv ./build/m0/m0 120 PSX.EXE
    COVERAGE=/tmp/couv PAD_SCRIPT="..." ./build/m0/m0 120 PSX.EXE
    python3 tools/m0/coverage.py /tmp/couv
"""
import sys
from collections import Counter

if len(sys.argv) < 2:
    sys.exit(__doc__)

total = Counter()
for path in sys.argv[1:]:
    for line in open(path):
        try:
            e, n = line.split()
            total[int(e)] += int(n)
        except ValueError:
            pass

seen = sorted(total)
print("%d states out of 40 exercised" % len(seen))
print("seen    :", " ".join(str(e) for e in seen))
print("left    :", " ".join(str(e) for e in range(40) if e not in total))
print()
for e in seen:
    print("   %2d  %9d frames" % (e, total[e]))
