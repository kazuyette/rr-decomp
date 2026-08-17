# Changelog

## v0.1.0 — the game is playable

> ### This release contains no game
>
> **There is no download that plays Ridge Racer.** No executable is published
> here, and none could be: the runtime is built from `PSX.EXE`, and it reads
> its data from the disc — the track, the cars, the textures, the music are all
> on the disc, none of them in this repository.
>
> To build and run it you need **your own legally-owned copy of Ridge Racer**
> (PlayStation, Japan, SLPS-00001), dumped to an image from your own disc.
> `tools/m0/README.md` explains how. Without it you can read the code and the
> notes, and that is the whole of what is offered.
>
> Nothing owned by Namco is committed here — no disc image, no executable, no
> textures, no audio, and no disassembly. `asm/` is regenerated on your machine
> from your own copy by `make setup`. This is the practice of every project on
> [decomp.dev](https://decomp.dev), and it is not a formality: it is the reason
> this work can exist in the open.

The native runtime boots from the disc, draws, sounds, and takes a controller.
This is not a milestone of the decompilation, which stands at 5.6 % of
instructions; it is a milestone of the second track — the static
recompilation described in [`README.md`](README.md#the-native-runtime) — which
now runs the whole game from your own copy of `PSX.EXE` and your own disc.

Nothing here is emulation of a PlayStation. There is no BIOS image: the sixteen
BIOS entry points this game actually calls are reimplemented. `PSX.EXE` is
translated to C ahead of time, function by function, and the hardware it talks
to is modelled in `tools/m0/`.

### It runs

- **Boot to race.** Loading screen, title, menu, and a race, from the disc
  image, with no manual extraction step: the ISO is served sector by sector,
  so the game finds its own volume descriptor, directory and files.
- **Picture.** A software rasteriser for the PSX GPU — polygons, rectangles,
  lines, 4- and 8-bit CLUTs, texture windows, semi-transparency.
- **Sound.** The twelve Red Book audio tracks play from the CUE sheet, and the
  SPU's twenty-four voices are synthesised — ADPCM decoding with real ADSR
  slopes, so the engine and the effects are the game's own samples.
- **Time.** The clock is driven by counted instructions and pixel cost rather
  than host wall time, and the display is paced at 60 Hz, which is what the
  Japanese NTSC release ran at.
- **Controller.** Keyboard, and any SDL-recognised gamepad.

### The neGcon

Ridge Racer was designed alongside Namco's neGcon, whose body twists and whose
I and II buttons measure how hard they are pressed. That support is *in the
1994 game*: `read_pad_input` at `0x8002E778` branches on the controller type
byte — `0x41` for the digital pad, `0x23` for the neGcon — and in the second
case takes the twist as the steering angle and the two buttons as pedals,
clamped to `0x6A` and divided by `0x6A`. A pedal with 106 steps instead of two
positions.

So there was nothing to write on the game's side: announcing `0x23` and filling
four more bytes is the whole of it. The left stick becomes the twist, the
triggers become the pedals, and the d-pad and face buttons still push the same
values to their limits, so nothing is lost. `CONTROLLER` in the F1 menu switches
between the two types live.

The digital branch, it turns out, *fabricates* a twist value from the
directions and feeds it to the same code. The whole game has steered by an
analogue value since 1994; the digital pad was always a simulated neGcon.

### Windows

`build.py --windows` cross-compiles a native `.exe` with MinGW. Three things do
not port as they are: the duration limit is a signal on Unix and a sleeping
thread on Windows; SDL diverts `main()` through a macro and wants its own
startup library, so `SDL_MAIN_HANDLED` says the `main` is already written; and
Windows' object format counts its sections in sixteen bits, which 949 functions
in one file overflow — hence `-Wa,-mbig-obj`.

Disc paths are translated the way WSL translates them, `/mnt/e` to `E:`.

### A settings menu

`F1` opens a menu drawn over the game — frame rate, audio lead, draw cost,
music, effects, controller type, and two diagnostics. It is drawn into the
final texture rather than into video memory, so the game cannot erase it and it
cannot dirty what the game produced. That separation matters on the day one
compares a frame against a reference.

### Defects worth naming

Each of these took longer to find than to fix, and each has the same shape: a
silent failure that broke somewhere other than where it was.

- `InitGeom` was a silent stub — one COP0 instruction. It also sets ZSF3 and
  ZSF4, so every polygon got an OTZ of 0 and the game discarded the entire
  track. Only the sky drew.
- Sixteen-bit reads were folded to thirty-two-bit boundaries, so `SPUCNT` at
  `0x1F801DAA` returned the SPU transfer queue — that is, zero. The driver's
  read-modify-write then lost the enable bit. This had been in `rt.h` since day
  one.
- `$sp` was not restored across interrupts. Stack buffers walked past 2 MB,
  writes were dropped in silence, and the game printed "File not found" after
  correctly reading its volume descriptor.
- A jump table's `jr` went to the global dispatcher and cut the CD interrupt
  handler before its acknowledge. A counter — "indirect jumps with no target" —
  had been reporting it all along.
- The disc image path was recorded absolute, which is right until a `.exe`
  built under WSL is launched by Windows. `fopen` failed, sectors came back as
  zeros, and the game complained "File not found": an exact complaint about a
  false fact, which sends you looking at the far end of the chain.
- SDL's RAWINPUT driver returned a half-alive controller on Windows — axes
  answered, buttons stayed at zero. Found by putting the sixteen-bit pad word
  on screen: it only ever changed on `FFFD`, the right trigger, read as an
  axis.

The last two are why the runtime now says `disc not found: <path>` when the
image will not open, and why `PAD_DEBUG=1` prints what the controller
actually returns. Putting a number on a deviation gives something to drive to
zero; prose does not.

### Verification carried over

- The translator was checked against qemu-mipsel: 114 of 116 functions
  bit-identical over 1856 cases.
- The GTE was checked against an independent second implementation: 11 600
  comparisons across 29 encodings.
- The recompilation is deterministic — the same `PSX.EXE` produces the same
  frames, byte for byte, on two different machines.

### Known gaps

- 23 of the game's 40 states are never reached: memory card, two-player, the
  other courses, replay. The RECORDS screen cannot be left.
- The SPU envelope is close, not exact.
- GP0 still goes to a software rasteriser, not to the host GPU.
