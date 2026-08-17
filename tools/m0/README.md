# The native runtime

This directory holds the runtime for a **static recompilation** of Ridge
Racer: the game's MIPS code is translated to C mechanically by
`tools/recomp.py`, and runs against a model of the hardware written here. The
goal is not to build an emulator — it is to have a milestone that boots and
keeps working, in which each decompiled function can later replace its
translated twin, one at a time, without ever breaking the whole.

The game's own code is **generated** from your copy of `PSX.EXE` and is not
committed, exactly like the rest of the disassembly.

> **You need your own legally-owned copy of the game.** Nothing here ships game
> data, and nothing here works without a disc you own. The two files taken from
> it — `PSX.EXE` and an image of the data track — never leave your machine.

## Build and run

```sh
cp /path/to/PSX.EXE .
make setup                                          # splat -> asm/
python3 tools/m0/build.py PSX.EXE --iso data.iso --compile
./build/m0/m0 90 PSX.EXE
```

Two things come from your own disc: `PSX.EXE`, and an image of the **data
track** in 2048-byte sectors. If you start from a BIN/CUE image (2352 bytes per
sector, which is what the drive actually reads):

```sh
python3 tools/m0/bin2iso.py RidgeRacer.bin data.iso
```

`PSX.EXE` is then copied out of the mounted image, or extracted with any ISO
9660 tool. Without `--iso` the game starts and then stops at loading — it reads
its files from the disc, not from the executable.

### What you need installed

Python 3 and a C compiler, and nothing else: `tools/setup.py` installs splat
itself on first use. SDL2 is optional and gives you a window, sound and a
gamepad. On Windows, either build under WSL or cross-compile — see
[a Windows build](#a-windows-build).

`build.py` checks all of this before it starts, and names everything that is
missing at once:

```
2 things missing before this can build:

 * PSX.EXE cannot be found.
   This is your own copy of the game's executable, taken from your
   own disc (SLPS-00001). Nothing here replaces it.

 * the compiler gcc is not on the path.
   sudo apt install build-essential
```

Translating 949 functions takes about a minute; finding out afterwards that
there is no compiler, through a `command not found` from the shell, is a minute
wasted and a message that does not say what to do.

`build.py` recomputes the function list on every build from the disassembly —
nothing is frozen in a file that would go stale the first time a symbol is
renamed. It reports how many functions were translated and, if any remain, the
**stubs**, with the reason for each.

Frames are written as PPM, one every hundred display lists, into the `IMAGES`
directory (the current one by default):

```sh
IMAGES=/tmp/images ./build/m0/m0 90 PSX.EXE
python3 tools/m0/ppm2png.py /tmp/images/*.ppm
```

By default the output is a few lines: what the game prints itself, then a
summary at the end. `VERBOSE=1` adds the BIOS call log and the conversation
with the CD drive — a debugging tool, which served to find where booting
stopped. Now that it no longer stops, it only hides the rest.

## Time

A static recompilation has no clock. The translated code is paced by nothing:
it runs at the speed of the host, and no instruction is tied to a cycle. One
has to be manufactured, and the choice is not neutral.

It ticks here on **memory accesses** (`TICK()` in `rt.h`), because that is the
one thing running code cannot abstain from doing — a clock ticking on hardware
accesses or on calls stops precisely while a wait loop spins in memory.

One case remained uncovered: `VSync` waits by polling the BIOS counter, over
and over, doing nothing else. That wait barely advances a clock that ticks on
work — the game burned **3.2 billion calls in three minutes**. But asking for
the time in a loop is an admission of having nothing to do: so time advances on
every request. This is emulator wait-loop detection in its simplest form, the
one where the code says so itself. Ten times more frames per second, without
touching anything else in the time base.

## The files

| | |
|---|---|
| `rt.h` | Memory: 2 MB of RAM, the 1 KB scratchpad, the routing to hardware registers. And the time base, ticking on memory accesses. |
| `hw.c` | The CD drive, DMA channels 2, 3, 4 and 6, interrupts, the register log. |
| `gpu.c` | The rasteriser: 1024×512 video memory, flat, gouraud and textured polygons, rectangles and sprites, lines, transfers both ways, 4- and 8-bit CLUTs, texture window, semi-transparency in all four modes. Software, because what we are trying to establish is fidelity, not speed. |
| `gte.c` | The geometry coprocessor, checked against an independent second implementation (`gte_check.py`, 11 600 comparisons, 29 encodings). |
| `spu.c` | The 24 voices: ADPCM decoding and a real ADSR envelope. |
| `main.c` | The loader, indirect-call dispatch, the BIOS calls, the controller. |
| `video.c`, `audio.c`, `mods.c` | The window, the sound device, and the settings menu. All three are optional: without SDL2 the rest works exactly as before. |

## The window

If SDL2 is installed, `build.py` finds it and the game opens in a window, with
a live keyboard:

```sh
sudo apt install libsdl2-dev     # Debian, Ubuntu, WSL
python3 tools/m0/build.py PSX.EXE --iso data.iso --compile
./build/m0/m0 600 PSX.EXE
```

| keyboard | gamepad | PlayStation |
|---|---|---|
| arrows | d-pad, left stick | d-pad, twist |
| space or X | bottom button, right trigger | cross — accelerate |
| C | right button, left trigger | circle — brake |
| S, D | left, top | square, triangle |
| A, E | shoulder buttons | L1, R1 |
| enter | start | start |
| shift | back | select |
| F1 | back (menu open) | — opens the settings |
| escape | — | quit |

The gamepad layout follows button *position*, not name: the bottom button
accelerates and the right button brakes, whatever the pad calls them.

SDL recognises most gamepads and gives them a common layout, which saves
writing a table per model. The first one found is taken, and it may arrive or
leave mid-game — a pad you unplug and plug back in works again without
restarting.

The picture is presented when the game swaps its buffers, that is, at the exact
moment it declares a frame finished — not after a counter we chose.
`NO_WINDOW=1` returns to the frames-on-disk mode.

### A Windows build

`build.py --windows` cross-compiles a native `.exe` with MinGW. The code does
not change; only the compiler does.

```sh
sudo apt install gcc-mingw-w64-x86-64
curl -LO https://github.com/libsdl-org/SDL/releases/download/release-2.30.9/SDL2-devel-2.30.9-mingw.tar.gz
tar xzf SDL2-devel-2.30.9-mingw.tar.gz

python3 tools/m0/build.py PSX.EXE --iso data.iso --cue disc.cue \
        --windows --sdl SDL2-2.30.9/x86_64-w64-mingw32 --compile
```

`SDL2.dll` is copied next to the program: Windows does not look for libraries
in a system path, and without it the program does not start at all. Then, from
PowerShell:

```powershell
.\build\m0\m0.exe 100000 PSX.EXE
```

The disc and track paths are recorded absolute in the generated file, so the
program can be launched from anywhere. With `--windows` they are translated the
way WSL translates them — `/mnt/e/...` becomes `E:\...` — without which the
`.exe` would open a path Windows does not know, get back sectors of zeros, and
the game would complain "File not found": an exact complaint about a false
fact, which sends you looking at the far end of the chain. The program now says
so itself, once, where it still knows: `disc not found: <path>`.

Three things do not port as they are:

- the duration limit is a signal on Unix and a sleeping thread on Windows —
  which is what an alarm is, seen from inside the system;
- SDL diverts `main()` through a macro on Windows and wants its own startup
  library; `SDL_MAIN_HANDLED` and `SDL_SetMainReady()` say the `main` is
  already written, and the same code serves both sides;
- the translated code makes one object of 949 functions, and Windows' object
  format counts its sections in sixteen bits; `-Wa,-mbig-obj` lifts the limit.

SDL is also told to read gamepads through XInput rather than RAWINPUT. With
RAWINPUT, an Xbox pad came back half alive on Windows — axes answered, buttons
stayed at zero.

### The neGcon, or the analogue that was already there

Ridge Racer was designed alongside Namco's neGcon, a controller whose body
twists and whose I and II buttons measure how hard they are pressed. Reading it
is **in the 1994 game**: `read_pad_input`, at `0x8002E778`, tests the type byte
of the pad buffer and branches.

```
type 0x41  digital pad   4 bytes   the directions fabricate the steering
type 0x23  neGcon        8 bytes   twist, button I, button II, L trigger
```

In the neGcon branch, the twist (byte 4, `0x80` at rest) becomes the steering
angle directly, and buttons I and II become throttle and brake: the game clamps
them to `0x6A` then divides by `0x6A`, which gives a pedal with 106 steps
instead of two positions. It rebuilds the digital bits from them along the way
— right beyond `0xA3`, left below `0x5E`, pedal pressed beyond `0x36` — for the
rest of the code, which only looks at buttons.

So there was nothing to write on the game's side: announcing `0x23` and filling
four more bytes is all of it. The left stick gives the twist, the triggers give
the pedals; the d-pad and face buttons stay connected and push the same values
to their limits, so nothing is lost.

`CONTROLLER` in the `F1` menu switches between `NEGCON` and `DIGITAL` live —
the shortest way to hear what the analogue path changes. `PAD_DIGITAL=1`
forces the digital type without going through the menu.

### Frame rate

Nothing throttles the translated code: it produces frames as fast as the host
allows, and the car then accelerates several times too fast for a reason that
has nothing to do with the game. On the console the video scan sets the tempo —
sixty times a second in NTSC, which the Japanese release is.

The wait therefore happens in the buffer swap and nowhere else: the game
already blocks there by itself, so throttling the display throttles everything
else without touching the time base. Lateness does not accumulate — a frame
that took too long is not made up for on the next one.

```sh
HZ=30 ./build/m0/m0 600 PSX.EXE     # the rate the race holds on console
HZ=0  ./build/m0/m0 600 PSX.EXE     # no throttle, for measuring
```

**How to tell which is right**: the race timer counts down in seconds. Start a
race and watch `TIME` fall — in sixty real seconds, how many did the game
count? One unit per second, and the rate is right.

Without SDL2 nothing changes: frames on disk and a scripted controller, and
`build.py` says so instead of keeping quiet about it.

## The settings menu

`F1` opens a menu drawn over the game: frame rate, audio lead, draw cost,
music, effects, controller type, and the state display. The arrow keys navigate
and adjust; while it is open the pad returns "nothing pressed" to the game,
because one does not want to drive and adjust at the same time.

Why a menu of our own rather than an entry in the game's: adding a line to
Ridge Racer's OPTION menu would first require decompiling state 18, which is
still mechanically translated assembly — one would be editing code that is
regenerated on every build, and the edit would not survive. This menu also gets
to adjust things the console did not have.

It is drawn into the final frame, **after** video memory and not into it: the
game cannot erase it by redrawing, and we do not dirty what it produced. The
two stay separate, which matters on the day one compares a frame against a
reference.

## Sound

Ridge Racer's soundtrack is not synthesised: it is twelve ordinary audio
tracks, burned next to the data, which the console read with the same mechanism
as any compact disc. There is no synthesiser to write in order to hear it —
only sectors to serve at the right rate.

Give the `.cue` sheet to the build and keep the track files next to it:

```sh
python3 tools/m0/build.py PSX.EXE \
    --iso data.iso --cue "Ridge Racer (Japan).cue" --compile
```

The format lines up exactly: an audio sector is 2352 bytes, which is exactly
588 stereo frames of sixteen bits at 44 100 Hz. No conversion, no resampling.
The sound card sets the pace — as long as its queue is full enough we read no
sector; if our clock had to agree with it, one would drift from the other and
the sound would crackle.

`NO_SOUND=1` turns the sound off.

### The audio queue's lead

We keep the sound card filled a little ahead. It is a trade-off audible from
both sides: too short and it runs dry, and you hear gaps; too long and
everything already queued was computed **before** the event that just happened
— the crash sound starts after the crash, by exactly the lead.

It cannot be heard on the music, which is continuous. It is very audible on
triggered sounds, where the ear compares against the picture.

Measuring gives a sharp knee: at 20 ms the queue runs dry 867 times a minute,
at 40 it runs dry 8 times, and beyond that nothing is gained. **40 ms** is
therefore the setting, and `LATENCY=60` or `LATENCY=25` lets you judge for
yourself. The summary reports the lead and how many times the queue ran dry.

### The SPU

The rest of the sound — engine, tyre squeal, voice — comes from the SPU's
twenty-four voices: half a megabyte of separate memory, filled by DMA channel
4, from which each voice draws compressed samples at its own pitch and volume.
Everything is mixed with the music before being pushed to the sound card, as
the hardware did.

The envelope follows the hardware's four phases with their real slopes: a shift
gives the period, a step gives the amplitude, and in exponential mode a rise
slows past three quarters while a fall scales with the level reached — which is
what gives fade-outs their tail.

The summary reports two counters worth their weight in admission. Voices
sounding while the SPU claims to be off: **zero**, and it is that zero which
attests — it stood at 288 for as long as it took to understand that the fault
was not in the SPU but in the sixteen-bit read. And sweeping volumes, which we
approximate by their starting value: **zero** as well; this game never uses
them, so the approximation costs nothing here.

Reverb is not implemented: the game writes its registers, we accept them and
ignore them.

## The controller

The BIOS does not read the pad on demand: it fills a buffer the game consults
when it likes. We can feed that from a **script** written in advance, so that
two runs give the same frames:

```sh
PAD_SCRIPT="1200:start 1260: 1600:start 1660: 2200:cross" ./build/m0/m0 90 PSX.EXE
```

Each term is `moment:keys`, **the moment counted in frames drawn**; a moment
with no key releases everything. The names recognised: `start`, `select`, `up`,
`down`, `left`, `right`, `cross`, `circle`, `triangle`, `square`, `l1`, `r1`. That script crosses the title screen, opens the menu, starts the race and
holds the throttle.

The unit is the frame and not the video beat, because it does not depend on the
time base: retuning the clock shifts every beat, but a frame is still a frame.
A script written once keeps working.

`PAD_DEBUG=1` prints what the controller actually returns — the sixteen-bit
word, the announced type, the four analogue bytes, and the raw device state
underneath SDL's game-controller layer:

```
pad: FFFD  type 23  twist 80  I 6A  II 00  L 00
```

That line is what found the RAWINPUT defect above. If it changes when you press
something, SDL is reading and the game is ignoring; if it does not change,
there is no point looking at the game side.

## What has actually been exercised

The game dispatches on a table of forty states (`0x80070EA4`, index at
`0x801D34F8`). The summary lists them all and says how many frames each ran —
or that it was never reached. That is the only honest answer to "does it work":
**12 states out of 40** with a script that goes as far as the race, 17 when
played by hand, and the rest never seen running.

A defect only shows up in a state you execute. The others are not "probably
fine" — they are **unknown**.

To explore, `contact_sheet.py` assembles frames into a contact sheet:

```sh
IMAGES=/tmp/images NO_WINDOW=1 ./build/m0/m0 60 PSX.EXE
python3 tools/m0/contact_sheet.py /tmp/images/*.ppm -o sheet.png -c 6
```

Thirty frames at once reveal what a single frame does not: a screen that stops
changing, a colour that drifts, a step backwards you were not expecting.

## Where things stand

| milestone | state |
|---|---|
| M0 — the game boots and prints its own log | ✅ |
| M1 — it reads its disc and emits its primitives | ✅ |
| M2 — the picture: loading screen, title screen | ✅ |
| M3 — the track: the demo runs | ✅ |
| M4 — the controller: menu and race | ✅ |
| M5 — the window: the game is playable on a keyboard | ✅ |
| M6 — time counted, instructions and pixels | ✅ |
| M7 — music: the disc's audio tracks | ✅ |
| M8 — the SPU: engine and effects | ✅ (envelope approximated) |
| M9 — GP0 to the host GPU | ✗ |

M0 through M8 together make version **v0.1.0**: the game is playable. The
milestones measure what the runtime can do; the version says you can sit down
in front of it. Those are two different questions, and neither of them is the
decompilation percentage, which is counted elsewhere.

## What this runtime taught the rest of the project

The defects found here are documented one by one in
[`RECOMP_NOTES.md`](../../RECOMP_NOTES.md). The pattern that keeps recurring,
and that is worth keeping:

> **A silent stub does not break where it is.**

`InitGeom` was replaced by a stub because it contains a single COP0
instruction. It also sets ZSF3 and ZSF4, the factors that turn a depth into a
display-list index. Without them every polygon got depth zero, and the game —
which discards whatever lands at index zero — discarded the entire track. The
symptom, five functions away: a picture with no road.

The same pattern, in five more copies: a jump table's `jr` sent to the global
dispatcher, which cut the interrupt handler just before its acknowledge; an
unimplemented BIOS `strcpy`, which returned zero without copying anything and
made a game that had read its disc correctly conclude "File not found"; an
ignored DMA direction bit, which pushed the contents of the stack into the GPU;
a disc path that could not be opened, which returned sectors of zeros; and
SDL's RAWINPUT driver, which returned a controller with working axes and dead
buttons.

Each of them was found the same way: by putting a **number** on the deviation
and driving it to zero. Prose does not converge.
