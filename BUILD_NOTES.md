# Build pipeline notes

Status: **infrastructure only, 0% decompiled.** No function has a C
reimplementation yet. This file documents how the current build works and
what a real matching-decomp contribution looks like next.

## What exists today

`asm/*.s` is splat's disassembly of `PSX.EXE` (not committed: the binary
itself, only the text listing). The `Makefile` reassembles it:

- `asm/header.s`, `asm/data/*.s` — plain data, assembled directly with
  `mipsel-linux-gnu-as`.
- `asm/29E8.s` — the code blob, routed through
  [maspsx](https://github.com/mkst/maspsx) (vendored in `tools/maspsx`,
  MIT license) so GNU `as` reproduces what PSY-Q's original `ASPSX.EXE`
  assembler would have produced.

Reassembling this disassembly as-is (zero C written) already reproduces
about **89% of the original `.text` bytes** — that's the normal starting
point for any matching-decomp project, not a milestone specific to this one.
The remaining ~11% is assembler-quirk mismatches and a few misdisassembled
regions (see splat's own "nonmatching" markers in `asm/29E8.s`) to iterate on
as real functions get reimplemented.

`objdiff.json` currently lists 4 units, each with only a `target_path` (the
reassembled object) and no `base_path` — meaning "nothing decompiled yet",
which `objdiff-cli report generate` reports honestly as 0% (not an error).

## CI

`.github/workflows/build.yaml` installs `binutils-mipsel-linux-gnu`, runs
`make all`, downloads `objdiff-cli` (a GitHub release binary, not a package),
and uploads `build/report.json` as artifact `PSX.EXE_report`. This is the
artifact decomp.dev's report ingestion expects. No C compiler is needed for
this stage — the target objects are pure disassembly.

## What's actually needed for real progress

1. A working PSX C cross-compiler — old GCC (2.5.7–2.95.2 era, PSY-Q used
   variants in that range) via
   [decompals/old-gcc](https://github.com/decompals/old-gcc) (Docker-buildable).
2. Pick one already-understood function (see `GHIDRA_PROGRESS.md`) and
   write a C reimplementation in `src/`.
3. Compile it, add its `base_path` to the matching unit in `objdiff.json`,
   and iterate with `objdiff-cli` (or the GUI) until it byte-matches.
4. Once at least one function matches, overall progress crosses decomp.dev's
   0.5% visibility threshold and the project appears in its public list
   (currently registered but hidden — https://decomp.dev/kazuyette/rr-decomp
   already shows real data on the direct URL).

## Known imperfections worth knowing about (not blockers)

- `asm/header.s`'s licence-string tail (offset ~0x4C onward) has a few
  genuinely non-ASCII garbage bytes in this early Nov. 1994 build; they're
  decoded with `errors="replace"`, which is lossy for those ~15 bytes
  specifically (not the whole header). Harmless — that region isn't code or
  meaningful data.
- Fixed locally (not yet upstreamed as a PR): splat's PSX header segment
  writer was missing an endianness reversal on the 5 "Reserved" header
  words, which only matters when those bytes are non-zero (this build has
  non-zero garbage there; most PS1 titles don't, which is why nobody hit
  this before).
