# rr-decomp

Decompilation project for **Ridge Racer** (PlayStation 1, Namco, 1994 - Japan release, `RIDGERACER` volume, build dated Nov. 1994).

This repository does **not** contain any copyrighted game data (disc image, executable, textures, audio). You need your own legally-owned copy of the game to build/verify against.

## Status

Very early stage - disc structure mapped, initial reverse-engineering of `PSX.EXE` underway in Ghidra. No matching build/CI yet.

See [`DISC_NOTES.md`](DISC_NOTES.md) for the disc layout and [`GHIDRA_PROGRESS.md`](GHIDRA_PROGRESS.md) for the reverse-engineering progress log (functions identified, open questions).

## Goals

- Full source-level decompilation of `PSX.EXE`, matched via objdiff (https://github.com/encounter/objdiff)
- Progress tracked on decomp.dev (https://decomp.dev) once CI produces reports
- Document the custom asset formats (`MAP.RRM`, `OBJ.RRO`, `TEX*.TMS`, `IDX.HED`)

## Notable findings so far

- The game natively supports the **neGcon** (Namco's twist/analog racing controller), alongside the standard digital pad.
- Custom sound engine driving the PS1 SPU's 24 hardware voices (bank files `RR.VH`/`RR.VB`, standard Sony VAB format).
- Graphics rendering goes through a small internal device-abstraction vtable rather than calling `libgpu` directly.

## Building

Not yet available - toolchain (MIPS PSX cross-compiler, linker script, `objdiff.json`) still to be set up.
