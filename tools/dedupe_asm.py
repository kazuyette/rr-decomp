#!/usr/bin/env python3
"""Drop INCLUDE_ASM entries that collide with hand-written C.

splat regenerates src/29E8.c with one INCLUDE_ASM per function in the segment,
including functions a hand-written unit already implements. Those collide at
link time. This asks nm what the built objects define -- the same notion of
truth the linker uses -- instead of a hand-maintained list that goes stale.

Run after a build has produced build/src/*.o (a link that failed on duplicate
symbols still leaves them), then build again.
"""
import glob, os, re, subprocess, sys

NM = os.environ.get("NM", "mipsel-linux-gnu-nm")
GENERATED = "src/29E8.c"
RE = re.compile(r'^\s*INCLUDE_ASM\("[^"]+",\s*(\w+)\);\s*$')

owned = set()
objs = [o for o in sorted(glob.glob("build/src/*.o"))
        if os.path.basename(o) != "29E8.o"]
if not objs:
    sys.exit("no build/src/*.o found -- run make first")

for obj in objs:
    out = subprocess.run([NM, "--defined-only", obj],
                         capture_output=True, text=True).stdout
    syms = {p[2] for p in (l.split() for l in out.splitlines())
            if len(p) == 3 and p[1] in ("T", "t")}
    if syms:
        print("  %-24s defines %d" % (os.path.basename(obj), len(syms)))
    owned |= syms

keep, drop = [], []
for line in open(GENERATED).read().split("\n"):
    m = RE.match(line)
    if m and m.group(1) in owned:
        drop.append(m.group(1))
    else:
        keep.append(line)

open(GENERATED, "w").write("\n".join(keep))
print("\n%d INCLUDE_ASM removed, %d remain"
      % (len(drop), sum(1 for l in keep if l.strip().startswith("INCLUDE_ASM"))))
