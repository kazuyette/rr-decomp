#!/usr/bin/env python3
"""Compile each hand-written unit under every known flag set and report,
per function, which ones produce the retail bytes.

Why this exists
---------------
The retail executable links units built with at least four different
compiler invocations. A conversion that is semantically perfect still
misses if it is compiled with the wrong one, and the miss looks exactly
like a bad conversion -- same red line in verify.py, completely different
cause. Guessing one flag set per batch wastes most of the batch.

So: build every candidate file five times, once per pipeline, and diff
each function against the target separately. A function that matches
under any pipeline is a real conversion; it just needs to be moved into
the file that is compiled that way. A function that matches under none is
the only kind that is actually wrong.

The five pipelines, and the two axes they vary:

  o2_plain   -O2, no -mmips-as, plain maspsx            (what src/globals.c uses)
  o2         -O2 -mmips-as, ASPSX 2.21 + epilogue swap
  o1         -O1 -mmips-as, ASPSX 2.21 + epilogue swap
  o1ndb      -O1 -mmips-as -fno-delayed-branch, idem
  c257       GCC 2.5.7, -O2 -mmips-as, idem

-mmips-as makes cc1 emit assembler macro forms instead of expanding them
itself, which changes $at usage and li expansion. The epilogue swap
reproduces the delay-slot move the real ASPSX reorderer performed. Those
two travel together: neither is meaningful without the other.

Usage:
  python3 tools/flag_sweep.py                  # every src/cand_*.c
  python3 tools/flag_sweep.py src/cand_x.c ... # named files only

Writes build/sweep.json:  {"func_8004xxxx": ["o1", "o2"], ...}
"""
import json
import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from verify import disassemble  # noqa: E402

BUILD = "build"
SWEEP = os.path.join(BUILD, "sweep")
TARGET = os.path.join(BUILD, "asm", "29E8.o")
INC_DIR = "include"
INC_STAGE = "/tmp/rr-include"

AS = "mipsel-linux-gnu-as"
AS_FLAGS = ["-EL", "-march=r3000", "-mtune=r3000", "-mabi=32", "-I" + INC_DIR]
GCC_DIR = os.environ.get("PSX_GCC_DIR", "/opt/psx-gcc")
GCC257_DIR = os.environ.get("PSX_GCC257_DIR", "/opt/psx-gcc257")

COMMON = ["-fno-builtin", "-fsigned-char", "-gcoff"]

# name -> (compiler_dir, cc_flags, use_aspsx_221_and_swap)
PIPELINES = {
    "o2_plain": (GCC_DIR, ["-O2", "-mrnames"] + COMMON, False),
    "o2":       (GCC_DIR, ["-O2", "-mrnames", "-mmips-as"] + COMMON, True),
    "o1":       (GCC_DIR, ["-O1", "-mrnames", "-mmips-as"] + COMMON, True),
    "o1ndb":    (GCC_DIR, ["-O1", "-mrnames", "-mmips-as",
                           "-fno-delayed-branch"] + COMMON, True),
    # 2.5.7 predates -mrnames; it would emit symbolic register names that
    # modern gas rejects.
    "c257":     (GCC257_DIR, ["-O2", "-mmips-as"] + COMMON, True),
}


def run(cmd):
    return subprocess.run(cmd, capture_output=True, text=True)


def build_one(src, pipeline):
    """Compile one .c under one pipeline. Returns the .o path, or None."""
    cc_dir, flags, aspsx = PIPELINES[pipeline]
    stem = os.path.basename(src)[:-2]
    s = os.path.join(SWEEP, f"{stem}.{pipeline}.s")
    o = os.path.join(SWEEP, f"{stem}.{pipeline}.o")

    r = run([os.path.join(cc_dir, "gcc"), "-B" + cc_dir + "/"] + flags +
            ["-I" + INC_STAGE, "-S", src, "-o", s])
    if r.returncode != 0 or not os.path.exists(s):
        return None, (r.stderr or "").strip().splitlines()[-1:] or ["cc failed"]

    asm_in = s
    if aspsx:
        swapped = s + ".swap"
        r = run(["python3", "tools/aspsx_epilogue_swap.py", s, swapped])
        if r.returncode != 0:
            return None, ["epilogue swap failed"]
        asm_in = swapped

    cmd = ["python3", "tools/maspsx/maspsx.py"]
    if aspsx:
        cmd += ["--aspsx-version", "2.21"]
    cmd += ["--run-assembler", "--gnu-as-path", AS, "-o", o] + AS_FLAGS + [asm_in]
    r = run(cmd)
    if r.returncode != 0 or not os.path.exists(o):
        return None, (r.stderr or "").strip().splitlines()[-1:] or ["as failed"]
    return o, None


def main():
    files = [a for a in sys.argv[1:] if a.endswith(".c")]
    if not files:
        files = sorted(f"src/{f}" for f in os.listdir("src")
                       if f.startswith("cand_"))
    if not os.path.exists(TARGET):
        print("build/asm/29E8.o missing -- run `make all` first")
        return 1
    # A stale target is worse than a missing one: the sweep still produces
    # a plausible-looking sweep.json, and apply_sweep then acts on it. If
    # `make all` failed, build/ can easily be left over from an earlier run.
    listing = os.path.join("asm", "29E8.s")
    if (os.path.exists(listing)
            and os.path.getmtime(listing) > os.path.getmtime(TARGET)):
        print(f"{TARGET} is older than {listing} -- the build did not "
              f"complete. Fix the build before sweeping.")
        return 1

    os.makedirs(SWEEP, exist_ok=True)
    os.makedirs(INC_STAGE, exist_ok=True)
    for h in os.listdir(INC_DIR):
        run(["cp", "-f", os.path.join(INC_DIR, h), INC_STAGE])

    target = disassemble(TARGET)
    wins = {}
    for src in files:
        line = [os.path.basename(src).ljust(28)]
        for pipeline in PIPELINES:
            o, err = build_one(src, pipeline)
            if o is None:
                line.append(f"{pipeline}: build failed ({err[0][:40]})")
                continue
            base = disassemble(o)
            n = 0
            for name, ins in base.items():
                if name in target and target[name] == ins:
                    wins.setdefault(name, []).append(pipeline)
                    n += 1
            line.append(f"{pipeline}:{n}")
        print("  ".join(line), flush=True)

    with open(os.path.join(BUILD, "sweep.json"), "w") as fh:
        json.dump(wins, fh, indent=1, sort_keys=True)

    print(f"\n{len(wins)} function(s) match under at least one flag set.")
    by = {}
    for name, pls in wins.items():
        by.setdefault(pls[0], []).append(name)
    for pl in PIPELINES:
        if pl in by:
            print(f"  {pl:9s} {len(by[pl])}")
    print("\nwritten to build/sweep.json -- that file is the answer:\n"
          "which functions are real conversions, and which pipeline each needs.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
