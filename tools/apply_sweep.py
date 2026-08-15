#!/usr/bin/env python3
"""Act on build/sweep.json: file each winning function under the pipeline
that reproduces the retail bytes, and send the rest back to INCLUDE_ASM.

tools/flag_sweep.py answers "which pipeline does this function need". This
applies that answer to the tree:

  * every function that matched under some pipeline P is moved into
    src/x_P_NN.c, which the Makefile compiles with exactly P;
  * every function that matched under none is deleted from the batch file
    and its INCLUDE_ASM line restored in src/29E8.c;
  * the candidate files (src/cand_*.c) are removed once emptied.

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

# Returned by compiles() when the compiler failed but the failure
# cannot be pinned on one function; the caller then shrinks the file
# instead of trusting it.
UNATTRIBUTED = "\x00unattributed"

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
    """{func: body} and {symbol: declaration}, over the batch files.

    Declarations are taken only from the head of each file -- the part
    before the first definition. Scanning the whole file instead picks up
    ordinary statements, which end in a semicolon exactly like a
    declaration does; `func_80045750(0);` then gets re-emitted at the top
    of a generated file, where it is a syntax error with no function to
    blame it on.
    """
    bodies, decls = {}, {}
    DEF = re.compile(r"^[A-Za-z_][\w \*]*?\b(\w+)\s*\([^;{]*\)\s*\{", re.M)
    for p in paths:
        text = open(p).read()
        first = DEF.search(text)
        head = text[:first.start()] if first else text
        for line in head.splitlines():
            s = line.strip()
            if not s.endswith(";") or s.startswith(("#", "/*", "*")):
                continue
            # A typedef is not a declaration to carry over: the generated
            # files include m2c_macros.h, which already defines s8..u32, and
            # re-emitting `typedef int s32;` next to it is a redefinition
            # error that belongs to no function.
            if s.startswith("typedef"):
                continue
            nm = re.findall(r"\b(\w+)\s*[\(;\[]", s)
            if nm:
                decls.setdefault(nm[0], s)
        for m in DEF.finditer(text):
            name = m.group(1)
            span = definition_span(text, name)
            if span:
                bodies[name] = text[span[0]:span[1]]
    return bodies, decls


def render(path, pipeline, names, bodies, decls):
    """Write the file; return {func: (first_line, last_line)}."""
    used = [decls[k] for k in sorted(decls) if k not in set(names)
            and any(re.search(r"\b" + re.escape(k) + r"\b", bodies[n])
                    for n in names)]
    head = HEADER % (os.path.basename(path), pipeline) + "\n".join(used) + "\n\n"
    text, spans, line = head, {}, head.count("\n") + 1
    for i, n in enumerate(names):
        body = bodies[n]
        spans[n] = (line, line + body.count("\n"))
        text += body + ("\n\n" if i + 1 < len(names) else "\n")
        line += body.count("\n") + 2
    open(path, "w").write(text)
    return spans


def compiles(path, pipeline, spans):
    """[] if the file builds; otherwise the functions to blame.

    Two error shapes have to be handled. GCC 2.7.2 prefixes a diagnostic
    inside a function body with "In function 'name':", which names the
    culprit outright. A parse error at top level -- which is what GCC
    2.5.7 reports for a construct it cannot handle at all -- carries only
    a line number, so the line is mapped back through the spans returned
    by render(). Missing the second shape silently reports the file as
    clean, which is how a file that does not build got written.
    """
    cc_dir, flags = CC_FLAGS[pipeline]
    r = subprocess.run([os.path.join(cc_dir, "gcc"), "-B" + cc_dir + "/"] + flags
                       + ["-I" + INC_STAGE, "-S", path, "-o", "/dev/null"],
                       capture_output=True, text=True,
                       env=dict(os.environ, LC_ALL="C"))
    if r.returncode == 0:
        return []
    bad = list(re.findall(r"In function .(\w+).:", r.stderr))
    for lineno in re.findall(re.escape(path) + r":(\d+)", r.stderr):
        lineno = int(lineno)
        for name, (a, b) in spans.items():
            if a <= lineno <= b:
                bad.append(name)
                break
    if not bad:
        errs = [l for l in r.stderr.splitlines()
                if " error" in l or "parse error" in l or "undeclared" in l]
        print(f"    {path}: error not attributable to a function")
        for l in (errs or r.stderr.strip().splitlines())[:3]:
            print("      " + l[:140])
        return [UNATTRIBUTED]
    return list(dict.fromkeys(bad))



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
    subprocess.run([sys.executable, "tools/setup.py"])


def main():
    dry = "--dry-run" in sys.argv
    if not os.path.exists(SWEEP):
        print(f"{SWEEP} missing -- run tools/flag_sweep.py first")
        return 1
    wins = json.load(open(SWEEP))
    batch = sorted("src/" + f for f in os.listdir("src")
                   if f.startswith("cand_"))
    if not batch:
        print("no batch files left to file")
        return 0
    # Refuse to act on a sweep that predates the candidates. This tool
    # deletes files and rewrites src/29E8.c; doing that from a stale
    # measurement silently throws away a whole batch, which is what
    # happened once already when `make setup` failed and build/ was left
    # over from the previous run.
    stale = [b for b in batch if os.path.getmtime(b) > os.path.getmtime(SWEEP)]
    if stale:
        print(f"{SWEEP} is older than {len(stale)} candidate file(s), "
              f"e.g. {stale[0]}.\nRe-run tools/flag_sweep.py; refusing to "
              f"act on a stale sweep.")
        return 1

    bodies, decls = harvest(batch)

    # A previous run leaves src/x_*.c behind. They are regenerated from
    # scratch here, and keeping the old ones would define every surviving
    # function twice.
    for stale in sorted(f for f in os.listdir("src") if f.startswith("x_")):
        os.remove(os.path.join("src", stale))

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

    # Fast path. A candidate file holding exactly one function needs no
    # regrouping at all: renaming it is enough, and it keeps the function
    # in the translation unit it was measured in. That matters -- GCC
    # 2.7.2 allocates registers across the whole unit, so a function moved
    # in beside others can stop matching, which is how batch 5 lost nine.
    solo = {}
    for path in batch:
        found = [n for n in bodies if f"src/cand_{n}.c" == path]
        if len(found) == 1 and found[0] in wins:
            solo[found[0]] = path
    for name, path in solo.items():
        pipeline = wins[name][0]
        dest = f"src/x_{TAG[pipeline]}_{name}.c"
        os.rename(path, dest)
        written.append(dest)
        batch.remove(path)
        chosen[pipeline].remove(name)
        if not chosen[pipeline]:
            del chosen[pipeline]

    for pipeline, names in list(chosen.items()):
        pending, idx = list(names), 0
        while pending:
            path = f"src/x_{TAG[pipeline]}_{idx:02d}.c"
            cur, rest = list(pending), []
            while cur:
                spans = render(path, pipeline, cur, bodies, decls)
                bad = compiles(path, pipeline, spans)
                if not bad:
                    break
                if bad == [UNATTRIBUTED]:
                    # Cannot tell which one; shed the last and try again.
                    bad = [cur[-1]]
                bad = [b for b in bad if b in cur]
                if not bad:
                    bad = [cur[-1]]
                for b in bad:
                    cur.remove(b)
                    rest.append(b)
            if not cur:
                # Every grouping failed. Fall back to one function per file:
                # a function that will not compile even alone is genuinely
                # unusable and goes back to INCLUDE_ASM, but it should not
                # take the rest of the pipeline down with it.
                solo = rest
                rest = []
                for name in solo:
                    spans = render(path, pipeline, [name], bodies, decls)
                    if compiles(path, pipeline, spans):
                        losers.append(name)
                        continue
                    written.append(path)
                    idx += 1
                    path = f"src/x_{TAG[pipeline]}_{idx:02d}.c"
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
    regenerate_missing_listings(losers)

    print(f"\nwrote {len(written)} file(s); removed {len(batch)} batch file(s).")
    print("Add the pipeline rules to the Makefile if they are not there yet, "
          "then rebuild and verify.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
