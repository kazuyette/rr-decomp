# rr-decomp

Matching-reconstruction and (in-progress) decompilation project for **Ridge Racer** (PlayStation 1, Namco, 1994 — Japan release, `RIDGERACER` volume, build dated Nov. 1994).

This repository does **not** contain any copyrighted game data (disc image, executable, textures, audio). You need your own legally-owned copy of the game to build/verify against. The committed `asm/*.s` files are a disassembly listing (mnemonics + symbol names), not the binary itself — the same practice used by every other project on [decomp.dev](https://decomp.dev).

## Status

Two different numbers describe this repo, and they should not be conflated:

- **Byte-matching: complete.** The build reassembles/recompiles byte-identically against the entire original `PSX.EXE` — 949/949 functions, 290656/290656 code bytes, verified with `objdiff-cli` locally before every push. The last holdout, `_start` (the low-level boot stub — a splat `dlabel` data blob rather than a normal callable function, since it runs before `$gp`/the stack are set up), is transcribed as raw `.word` values copied verbatim from the disassembly (`src/start.c`).
- **Source-level decompilation: in progress — 101 of 949 functions are real C.** The remaining functions are **verbatim `__asm__` transcriptions**: the original MIPS instructions copied from the disassembly into compilable wrappers (see "Notable technique" below). In decomp-community terms this makes the repo a *fully matched reconstruction with a small decompiled core*, not a completed decompilation — for an `__asm__` block, byte-matching is by construction, not a recovered-source proof. Early press coverage that described this project as "100% decompiled" overstated it; the 100% figure measures byte-matching only. (Rounds 67-68 finding, while converting: the retail EXE links units built with at least four flag sets — `-O1 -mmips-as`, `-O1 -fno-delayed-branch`, `-O2`, and GCC 2.5.7 `-O2` (the toolchain image now builds both compilers, see `src/c_257.c`) — all expanded ASPSX-2.2x-style with the epilogue delay-slot swap the real ASPSX performed (see `src/c_o1.c`, `src/c_o1_ndb.c`, `src/c_o2.c`, `tools/aspsx_epilogue_swap.py`); a few functions in Sony-library regions match no available GCC at all, consistent with launch-window libraries built on Sony's pre-GCC toolchain.) Conversion of `__asm__` functions to portable, byte-verified real C continues through the companion project [rr-pc-port](https://github.com/kazuyette/rr-pc-port) (each converted function is checked byte-exact with the same objdiff pipeline before landing back here).

Progress is tracked on [decomp.dev](https://decomp.dev/kazuyette/rr-decomp) (PlayStation platform, "Ridge Racer"). Note that decomp.dev's displayed percentage can lag a push by a while — CI going green is not itself a match-percentage check (see [`BUILD_NOTES.md`](BUILD_NOTES.md)), the real number is computed locally with `objdiff-cli` before every push.

See [`DISC_NOTES.md`](DISC_NOTES.md) for the disc layout and [`GHIDRA_PROGRESS.md`](GHIDRA_PROGRESS.md) for the earlier reverse-engineering progress log.

## Goals

- Byte-matched reconstruction of `PSX.EXE` via [objdiff](https://github.com/encounter/objdiff) — **complete** (949/949 functions, see Status)
- Source-level decompilation to real C — **in progress** (101/949; each conversion re-verified byte-exact)
- Document the custom asset formats (`MAP.RRM`, `OBJ.RRO`, `TEX*.TMS`, `IDX.HED`)

## Transparency

This project is heavily AI-assisted: the splat/maspsx/objdiff tooling, the transcription batches and the C conversions are driven by Anthropic's Claude under human direction and review. Nothing about the numbers above requires trust — with your own legally-owned copy of the game, `make all` plus `objdiff-cli report generate` reproduces the match report locally.

## Notable findings so far

- The game natively supports the **neGcon** (Namco's twist/analog racing controller), alongside the standard digital pad.
- Custom sound engine driving the PS1 SPU's 24 hardware voices (bank files `RR.VH`/`RR.VB`, standard Sony VAB format).
- Graphics rendering goes through a small internal device-abstraction vtable rather than calling `libgpu` directly.

## Notable technique

Two things made the difference between the initial ~89% raw-disassembly baseline and the final 100%:

- **Verbatim `__asm__` transcription.** Rather than writing idiomatic C and hoping GCC 2.7.2 recompiles it byte-identically (unreliable for anything beyond the simplest functions), most functions are transcribed as inline assembly, copied straight from the splat disassembly into a standard MIPS function wrapper:
  `.globl NAME` / `.ent NAME` / `NAME:` / `.frame $sp,0,$ra` / `.mask 0x00000000,0` / `.fmask 0x00000000,0` / `.set noreorder` / *instructions* / `.set reorder` / `.end NAME`.
  The `.ent`/`.end` wrapper is required for a subtle reason: [maspsx](https://github.com/mkst/maspsx) silently ignores a user-written `.set noreorder`/`.set reorder` unless it appears inside an `.ent`/`.end` block, so without it the reordering-sensitive delay-slot behavior of the original PSY-Q assembler (`ASPSX.EXE`) never actually gets emulated and the reassembly mismatches. A handful of GTE/COP2 opcodes (`rtps`, `mflo`/`mfhi`, `break`, etc.) also have to be encoded as raw `.word` directives rather than left as text mnemonics, because maspsx's own quirk-emulation for those specific opcodes doesn't match the original assembler's encoding.
- **Splat segmentation/boundary fixes.** Two classes of fix in `symbol_addrs.txt`/`psx.exe.yaml` unlocked large batches of functions splat had merged or mis-scoped: explicit `type:func` declarations for functions only ever referenced by pointer (never called directly, so splat had no other way to know they were functions), and a single rodata/asm segment-boundary correction (`psx.exe.yaml`, `0x29E8` → `0x29F4`) that fixed a truncated debug string and, as a side effect, exposed 268 previously-hidden function boundaries in one pass — a large jump in matched-function count from one root-cause fix.

## Building

Requires `binutils-mipsel-linux-gnu` and Python 3. With your own copy of `PSX.EXE` in place (not included, see above):

```sh
make all              # reassembles/compiles everything into target + base objects
make report           # requires objdiff-cli: https://github.com/encounter/objdiff
```

`make all` builds two kinds of objects: the disassembly-derived "target" objects (ground-truth reassembly of the original binary) and the "base" objects compiled from `src/*.c` with the project's PSX cross-GCC (2.7.2), which is not vendored here — see the `Makefile` header comment and `docker/toolchain.Dockerfile` for how to obtain/build it, and point `PSX_GCC_DIR` at it. CI runs the same `make all` on every push ([`.github/workflows/build.yaml`](.github/workflows/build.yaml)); note CI alone does not check the match percentage, since the real `PSX.EXE` is never committed there.

Vendored third-party tool: [`tools/maspsx`](tools/maspsx) (MIT, © Mark Street) — post-processes GNU-as assembly to match PSY-Q's original `ASPSX.EXE` output byte-for-byte.

See [`BUILD_NOTES.md`](BUILD_NOTES.md) for the detailed pipeline writeup.
