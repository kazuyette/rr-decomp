#!/usr/bin/env python3
"""Assemble la couverture de plusieurs exécutions.

Un seul scénario ne peut pas tout visiter : la démonstration montre ce que le
menu ne montre pas, et réciproquement. Chaque exécution lancée avec
`COUVERTURE=fichier` y ajoute les états qu'elle a traversés ; ce script en fait
la somme et dit surtout ce qui reste.

    COUVERTURE=/tmp/couv ./build/m0/m0 120 PSX.EXE
    COUVERTURE=/tmp/couv MANETTE="..." ./build/m0/m0 120 PSX.EXE
    python3 tools/m0/couverture.py /tmp/couv
"""
import sys
from collections import Counter

if len(sys.argv) < 2:
    sys.exit(__doc__)

total = Counter()
for chemin in sys.argv[1:]:
    for ligne in open(chemin):
        try:
            e, n = ligne.split()
            total[int(e)] += int(n)
        except ValueError:
            pass

vus = sorted(total)
print("%d etats sur 40 eprouves" % len(vus))
print("vus     :", " ".join(str(e) for e in vus))
print("restants:", " ".join(str(e) for e in range(40) if e not in total))
print()
for e in vus:
    print("   %2d  %9d images" % (e, total[e]))
