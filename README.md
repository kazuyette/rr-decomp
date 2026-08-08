# rr-decomp

Decompilation project for **Ridge Racer** (PlayStation 1, Namco, 1994 — Japan release, `RIDGERACER` volume, build dated Nov. 1994).

This repository does **not** contain any copyrighted game data (disc image, executable, textures, audio). You need your own legally-owned copy of the game to build/verify against. The committed `asm/*.s` files are a disassembly listing (mnemonics + symbol names), not the binary itself — the same practice used by every other project on [decomp.dev](https://decomp.dev).

## Status

Early stage. Disc structure mapped, initial reverse-engineering of `PSX.EXE` underway in Ghidra (see [`GHIDRA_PROGRESS.md`](GHIDRA_PROGRESS.md)). The build pipeline (splat + GNU binutils + [maspsx](https://github.com/mkst/maspsx) + objdiff) is wired up and produces a valid progress report in CI, but **no function has a C reimplementation yet** — everything is still tracked as raw disassembly ("target" objects only). Reassembling that disassembly as-is already reproduces ~89% of the original code bytes, which is the normal starting point before any matching decomp work begins.

See [`DISC_NOTES.md`](DISC_NOTES.md) for the disc layout and [`GHIDRA_PROGRESS.md`](GHIDRA_PROGRESS.md) for the reverse-engineering progress log (functions identified, open questions).

## Goals

- Full source-level decompilation of `PSX.EXE`, matched via [objdiff](https://github.com/encounter/objdiff)
- Progress tracked on [decomp.dev](https://decomp.dev) once CI produces reports
- Document the custom asset formats (`MAP.RRM`, `OBJ.RRO`, `TEX*.TMS`, `IDX.HED`)

## Notable findings so far

- The game natively supports the **neGcon** (Namco's twist/analog racing controller), alongside the standard digital pad.
- Custom sound engine driving the PS1 SPU's 24 hardware voices (bank files `RR.VH`/`RR.VB`, standard Sony VAB format).
- Graphics rendering goes through a small internal device-abstraction vtable rather than calling `libgpu` directly.

## Building

Requires `binutils-mipsel-linux-gnu` and Python 3. With your own copy of `PSX.EXE` in place (not included, see above):

```sh
make all              # reassembles the disassembly into target objects
make report           # requires objdiff-cli: https://github.com/encounter/objdiff
```

CI runs the same steps on every push and uploads a progress report ([`.github/workflows/build.yaml`](.github/workflows/build.yaml)). A from-scratch C reimplementation (with matching, function by function, tracked via [objdiff](https://github.com/encounter/objdiff)) is the next phase — `objdiff.json` and the linker script (`psx.exe.ld`) are already in place for it.

Vendored third-party tool: [`tools/maspsx`](tools/maspsx) (MIT, © Mark Street) — post-processes GNU-as assembly to match PSY-Q's original ASPSX.EXE output byte-for-byte.
