#!/usr/bin/env python3
"""Act on build/sweep.json: file each winning function under the pipeline
that reproduces the retail bytes, and send the rest back to INCLUDE_ASM.

tools/flag_sweep.py answers "which pipeline does this function need". This
applies that answer to the tree:

  * every function that matched under some pipeline P is moved into
    src/x_P_NN.c, which the Makefile compiles with exactly P;
  * every function that matched under none is deleted from the batch file
    and its INCLUDE_ASM line restored in src/29E8.c;
  * the batch files (src/b5_*.c, src/batch4.c) are removed once emptied.

The NN split exists for one reason: two functions can disagree about the
type of a global they share, or about a callee's signature, and then they
cannot sit in one translation unit. Files are filled greedily and a
function that breaks the compile is bumped to the next file. The check is
the real cross-compiler, not a host gcc, so what survives here compiles
in the build.

Usage:
  python3 tools/apply_sweep.py            # act
  python3 tools/apply_sweep.py --dry-run  # just count
"""
import json
import os
import re
import subprocess
import sys

SWEEP = "build/sweep.json"
GENERATED = "src/29E8.c"
SEGMENT = "asm/nonmatchings/29E8"
INC_STAGE = "/tmp/rr-include"
GCC_DIR = os.environ.get("PSX_GCC_DIR", "/opt/psx-gcc")
GCC257_DIR = os.environ.get("PSX_GCC257_DIR", "/opt/psx-gcc257")
COMMON = ["-fno-builtin", "-fsigned-char", "-gcoff"]

# Same table as flag_sweep.py, minus the assembler half: to decide whether
# a file compiles we only need the compiler.
CC_FLAGS = {
    "o2_plain": (GCC_DIR, ["-O2", "-mrnames"] + COMMON),
    "o2":       (GCC_DIR, ["-O2", "-mrnames", "-mmips-as"] + COMMON),
    "o1":       (GCC_DIR, ["-O1", "-mrnames", "-mmips-as"] + COMMON),
    "o1ndb":    (GCC_DIR, ["-O1", "-mrnames", "-mmips-as",
                           "-fno-delayed-branch"] + COMMON),
    "c257":     (GCC257_DIR, ["-O2", "-mmips-as"] + COMMON),
}

# File tag per pipeline. Deliberately chosen so that no tag is a prefix of
# another: make picks the pattern rule with the shortest stem, and
# "x_o1_%" would otherwise swallow "x_o1ndb_00" and compile it with the
# wrong flags.
TAG = {"o2_plain": "o2p", "o2": "o2m", "o1": "o1m", "o1ndb": "o1d",
       "c257": "c257"}

HEADER = """/* %s -- functions verified to reproduce the retail bytes under the
 * "%s" pipeline, filed here by tools/apply_sweep.py.
 *
 * Membership of this file is a measurement, not a judgement: each of
 * these was built under all five known pipelines and matched under this
 * one. The numbered split within a pipeline is mechanical -- two
 * functions that disagree about a shared global's type cannot share a
 * translation unit -- and carries no meaning. Regroup along real module
 * boundaries once the units are identified.
 */
#include "m2c_macros.h"

"""


def definition_span(text, name):
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


def harvest(paths):
    """{func: body} and {symbol: declaration}, over the batch files."""
    bodies, decls = {}, {}
    for p in paths:
        text = open(p).read()
        for line in text.splitlines():
            s = line.strip()
            if not s.endswith(";") or s.startswith(("#", "/*", "*")):
                continue
            nm = re.findall(r"\b(\w+)\s*[\(;\[]", s)
            if nm:
                decls.setdefault(nm[0], s)
        for m in re.finditer(r"^[A-Za-z_][\w \*]*?\b(\w+)\s*\([^;{]*\)\s*\{",
                             text, re.M):
            name = m.group(1)
            span = definition_span(text, name)
            if span:
                bodies[name] = text[span[0]:span[1]]
    return bodies, decls


def render(path, pipeline, names, bodies, decls):
    used = [decls[k] for k in sorted(decls) if k not in set(names)
            and any(re.search(r"\b" + re.escape(k) + r"\b", bodies[n])
                    for n in names)]
    open(path, "w").write(HEADER % (os.path.basename(path), pipeline)
                          + "\n".join(used) + "\n\n"
                          + "\n\n".join(bodies[n] for n in names) + "\n")


def compiles(path, pipeline):
    cc_dir, flags = CC_FLAGS[pipeline]
    r = subprocess.run([os.path.join(cc_dir, "gcc"), "-B" + cc_dir + "/"] + flags
                       + ["-I" + INC_STAGE, "-S", path, "-o", "/dev/null"],
                       capture_output=True, text=True,
                       env=dict(os.environ, LC_ALL="C"))
    if r.returncode == 0:
        return []
    return list(dict.fromkeys(re.findall(r"In function .(\w+).:", r.stderr)))


def main():
    dry = "--dry-run" in sys.argv
    wins = json.load(open(SWEEP))
    batch = sorted("src/" + f for f in os.listdir("src")
                   if f.startswith("b5_") or f == "batch4.c")
    if not batch:
        print("no batch files left to file")
        return 0
    bodies, decls = harvest(batch)

    chosen = {}
    for name, pipelines in wins.items():
        if name in bodies:
            chosen.setdefault(pipelines[0], []).append(name)
    kept = sum(len(v) for v in chosen.values())
    losers = [n for n in bodies if n not in wins]
    print(f"{kept} function(s) to file, {len(losers)} back to INCLUDE_ASM")
    for p in CC_FLAGS:
        if p in chosen:
            print(f"  {p:9s} {len(chosen[p])}")
    if dry:
        return 0

    os.makedirs(INC_STAGE, exist_ok=True)
    for h in os.listdir("include"):
        subprocess.run(["cp", "-f", os.path.join("include", h), INC_STAGE])

    written = []
    for pipeline, names in chosen.items():
        pending, idx = list(names), 0
        while pending:
            path = f"src/x_{TAG[pipeline]}_{idx:02d}.c"
            cur, rest = list(pending), []
            while cur:
                render(path, pipeline, cur, bodies, decls)
                bad = [b for b in compiles(path, pipeline) if b in cur]
                if not bad:
                    break
                for b in bad:
                    cur.remove(b)
                    rest.append(b)
            if not cur:
                print(f"  ! {pipeline}: {len(rest)} function(s) would not "
                      f"compile alone, left to INCLUDE_ASM")
                losers += rest
                if os.path.exists(path):
                    os.remove(path)
                break
            written.append(path)
            pending, idx = rest, idx + 1

    gen = open(GENERATED).read()
    for name in losers:
        line = f'INCLUDE_ASM("{SEGMENT}", {name});'
        if line not in gen:
            gen += "\n" + line + "\n"
    open(GENERATED, "w").write(gen)
    for p in batch:
        os.remove(p)

    print(f"\nwrote {len(written)} file(s); removed {len(batch)} batch file(s).")
    print("Add the pipeline rules to the Makefile if they are not there yet, "
          "then rebuild and verify.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
