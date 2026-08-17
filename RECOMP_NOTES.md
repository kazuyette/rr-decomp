# Static recompilation: the proof of principle

*Second worksite, opened 16 August 2026. The decompiler that matches remains
the source of truth; this is a test bench for native milestones that actually
start.*

## Why

Nine tenths of the game code is still assembly — `st_race_main`,
`car_simulate`, `func_800163E4` and their callees. A native milestone made of
our C functions plus stubs would therefore have no loop, no physics, no
rendering: it would compile and prove nothing.

Static recompilation turns the problem around. Every MIPS instruction is
mechanically translated into C, the whole game runs from the first day, and
each decompiled function then replaces its translated twin — the two being
comparable while running.

None of this is worth anything unless the translation is faithful. Hence this
bench.

## The method

Two executables, one single set of inputs.

**The reference**: the retail words copied as-is into a section of a mipsel
binary, called by a C harness, run under `qemu-mipsel`. No interpretation
comes into it — these are the original instructions on a processor that
understands them.

**The translation**: the C produced by `tools/recomp.py`, compiled for the
host.

Each one receives the same 256-byte buffer filled pseudo-randomly and the
same four argument registers, then prints the return value and the final
buffer. The texts are compared.

## Result

**1,120 cases — seventy functions, sixteen vectors each — and no
divergence.** (First measurement: 120 cases over five functions.) Of the 115
translatable functions, 45 are set aside because the reference itself cannot
run them on arbitrary inputs — invalid pointer or endless loop, which the
console would do too. The remaining 70 give back, byte for byte, what the
real code gives back, return value included.

The reference is not my reading of the code: it is its execution.

## What the bench caught

Two translation errors, and five defects in the bench itself. The distinction
matters: a bench that fails for its own reasons would condemn a correct
translator.

### In the translator

**Absolute jumps.** The `j` opcode encodes only the low 28 bits of its
target. My first version computed `(w & 0x3FFFFFF) << 2` and forgot the four
high bits of the program counter. On the reference side, the same oversight
moved the code and sent `MargePrim` into the void — hence loading the
functions at their original address masked to 28 bits.

**The delay slot.** The instruction that follows a branch executes before it,
taken or not. Emitted after the `goto`, it gives code that works everywhere
except where the slot modifies the register being tested. The translator
therefore moves it systematically ahead, after freezing the condition.

### In the bench

**Inputs the console would refuse.** The first vectors passed unaligned
pointers: immediate `SIGBUS`, just as on real hardware.

**Vectors as C literals.** Twelve functions already gave 276 KB of source and
six minutes forty of compilation, of which 0.2 second was computation. The
inputs now live in a binary file read at run time: 0.3 second for one hundred
and fifteen functions.

**The broken safety rail.** Catching faults by `siglongjmp` from a signal
handler fails: glibc refuses the return to a frame it judges uninitialized,
and a function gone into an endless loop was not caught at all. One child per
function with an alarm does it without fail.

**Functions with no return value.** Comparing `$v0` of a function that never
writes it is comparing noise — the empty function `func_8003FA94` gave a
clear example of that. The bench compares the return only if the disassembly
shows a write to that register.

**The buffer's absolute address.** `func_800409D4` adds `0x5D50AD` to its
argument and computes on the result: its output depends on the value of the
pointer, not only on what it designates. The buffer is therefore placed at
the same fixed address on both sides, by a linked section.

**The fifth argument.** `func_80048128` reads `0x10($sp)`, where the caller
deposits its fifth parameter. With four arguments it was reading
uninitialized stack. Both harnesses pass six, at the same locations.

## The state, honestly

Scaling up is not done. Of the 949 functions in the binary, 115 are
translatable as things stand — no GTE, no external call, no absolute global —
that is 1,346 instructions. The others are waiting on three things:

- **the GTE**: 101 functions touch it. Its forty opcodes call for a separate
  implementation, validated against the hardware documentation and not
  against qemu, which does not know this coprocessor. The translator refuses
  them explicitly rather than translating them halfway;
- **calls and globals**: 722 functions, which calls for a symbol table and a
  simulated memory space, not a change of principle;
The harness, for its part, now carries the load: 2.8 seconds to build and run
the reference on one hundred and fifteen functions, 1.2 seconds for the
translation.

---

# Step 2: calls and globals

## The change of method

The first bench copied each function to its masked address, one by one. As
long as they were isolated that was enough; as soon as they call one another
and read global variables, the whole program is needed.

The fix simplifies everything: **the complete image of the executable is
loaded** — 423,936 bytes at `0x80010000`, that is `0x00010000` once masked to
28 bits — into a section of the reference, and each function is declared as a
symbol at its address in that image. Calls and absolute addresses then come
out right without a single line of relocation, because they are already
right.

In passing, the header gives the entry point: **`0x8003FA9C`**, eight bytes
after `func_8003FA94`, the empty function at the game/library boundary. The
boundary computed several sessions ago from the call graph therefore falls
exactly on the start of the runtime.

## What the translator can do now

| | before | after |
|---|---|---|
| translatable functions | 115 | **836 of 948** |

Three additions made it possible:

**Calls.** `jal` becomes a C call to the corresponding translated function,
resolved by a symbol table built from the disassembly.

**The stack pointer as a global.** `$sp` cannot be a local variable: a callee
must see its caller's, otherwise the frames overlap and the arguments passed
beyond the fourth are read from nowhere. Making it a global makes nesting and
stack arguments correct with no special code — because that is exactly what
it is on the machine.

**Globals call for nothing.** The retail words already contain the absolute
addresses; the translation computes them and the accessors bring them back
into the RAM array. It is enough to have loaded the image into it.

112 functions remain: the GTE (109), two `syscall`s and one COP0 access.

## The result

**1,856 cases over 116 functions. 114 identical to the bit, 2 divergent.**

The 116 are not the 836: the bench sets aside 540 functions that the
reference itself cannot run on arbitrary inputs, and 180 that reach —
directly or transitively — a callee that is not translatable. The latter are
set aside by a fixed-point computation over the call graph, because a stub
must never pass for a verification.

## Four more defects, all in the bench

**Writes to `$zero`.** The retail contains some — `nop`s encoded otherwise,
results computed then abandoned. Translated as-is they give `0 = 0 & 0;`,
which C refuses. The register is hardwired to zero on the machine: the write
is thrown away.

**Stack arguments.** `func_80028A0C` reads up to `0x54($sp)`, `func_80029278`
up to `0x58($sp)` — the ninth argument. Each missing argument was read from
uninitialized stack, different on the two sides. The harness passes twelve.
That alone brought the divergences down from 160 to 32.

**Callees that are not translatable**, dealt with above.

**Section overlap**, trivial but instructive: the linker refused to place the
test buffer in the uninitialized area, which it was perfectly right to do.

## The two that remain

`func_80040690` and `rsin_quadrant` diverge on their return value, not on
memory. The first tests its argument against `0x400` — an angle quadrant —
and returns a value that the reference draws from a call which my detection
of `$v0` writes does not account for. These are two cases to look into, not
two established errors; and the fact that only two remain out of 116 says
where the translator stands.

---

# Step 3: the GTE

## What was implemented

Not the forty operations in the catalogue: **the twenty-two that this binary
actually uses**, surveyed by counting the encodings across the 948
functions. Twenty-nine distinct encodings, `mvmva` in the lead with
twenty-five occurrences, then `nclip`, `intpl`, `rtpt`, `avsz4`, `rtps`. The
rest raises a clean error rather than returning a wrong result.

With the registers and their quirks — the screen coordinate stack, the Z
stack, the color stack, the 5-5-5 unpacking of IRGB on write, the
leading-zero count of LZCS, the H register read back signed — and the
complete saturation with its nineteen flags.

The projection division reproduces the hardware's path: a 257-entry table and
two Newton-Raphson iterations, not an exact division. A division that is
correct in the mathematical sense would give screen coordinates off by one or
two — visible on the edges, invisible in a test that does not look for them.

## The translator, now

| | translatable functions |
|---|---|
| before calls and globals | 115 |
| after | 836 |
| **after the GTE** | **945 of 948** |

Only two `syscall`s and one COP0 access remain.

Transfers become calls to the accessors, commands a call with their raw
encoding. Decoding the `sf`, `lm`, `mx`, `v` and `cv` fields is done by the
implementation, not by the translator — so that the two remain separately
verifiable.

## The check, and what it is worth

qemu does not know COP2: the by-execution reference that validated whole
functions says nothing here. The only check available is to write the
operations **a second time**, in another language, from the same
documentation, then compare on register states drawn at random.

**11,600 comparisons — four hundred states, the twenty-nine encodings
surveyed in the binary — and no discrepancy, `FLAG` register included.**

The list: `mvmva` in four variants of matrix, vector and shift; `nclip`;
`avsz3` and `avsz4`; `sqr` and `op` in two shifts each; `rtps` and `rtpt`,
hence projection with its table division; `gpf`, `gpl`, `intpl`, `dpcs`,
`dpct`, `dcpl`; and the whole lighting family — `ncs`, `nct`, `nccs`,
`ncct`, `ncds`, `ncdt`, `cc`, `cdp`.

Each comparison covers the three accumulators, the three intermediate
registers, the color produced, and **the nineteen saturation and overflow
flags**.

What that is worth, precisely: two independent transcriptions do not go wrong
in the same place, unless the documentation itself is ambiguous. It catches
typos, inverted shifts, forgotten saturations — the bulk of what goes wrong
in this kind of code. **It does not catch a shared misreading.** The only
check that would is the console.

And the bench's loader itself produced a false failure before it was of any
use: writing the thirty-two registers in order destroys part of the state,
because writing IRGB unpacks a color into IR1-3 and writing SXYP pushes the
coordinate stack. Four hundred states diverged for that reason alone.

## The method paid off: two real bugs found

`gpf` and `gpl` agreed first time. `intpl` and `dpcs` diverged on all four
hundred states — and the error was in the C.

Interpolation toward the far color is written, in the specification:

```
IR  = ((FC SHL 12) - MAC) SAR (sf*12)
MAC = (IR * IR0 + MAC)    SAR (sf*12)
```

The starting `MAC` is **not** re-shifted. My first version shifted it by
`sf*12` in both places, which saturated the whole fog to white. No invariant
test would have seen it: the values stayed plausible, of the same order of
magnitude, simply wrong. The second transcription caught it on the first
state drawn.

The fix also touched the fog path of the lighting computations, which
compensated for the bug by pre-shifting its inputs — two errors that
half-cancelled each other.

**The second, in `ncs` and `nct`.** With no tinting by `RGBC`, the
specification keeps the MAC that comes out of the second matrix: *that* is
the result, and the color FIFO receives `MAC/16`. I was recomputing it from
`IR`, which divided it by 256 when `sf` was 1. Almost black colors —
plausible to the eye, wrong. The tinted variants (`nccs`, `ncct`, `ncds`,
`ncdt`) were correct, which made the error that much harder to suspect: it
touched only two operations out of eight in the same family.

Two bugs, both in scale handling, both invisible to an invariant test, both
caught on the first state drawn. That is exactly what the method exists for.

## What the flags revealed

Comparing `FLAG` brought out a third discrepancy — this time **in the Python
reference**, not in the C. `sqr` and `op` also write IR1-3 with saturation,
and therefore set flags; my transcription omitted that step. As long as only
the accumulators were compared, the omission was invisible: the values
compared were correct on both sides.

That is the check working in the other direction, and it is reassuring: a
method that never found a defect in itself would be suspect.

## What is not checked

The underlying limit does not move: two independent transcriptions do not
catch a shared misreading. If the documentation I followed is wrong, both my
versions are wrong together. Only the console would settle it — and that is
not a stylistic reservation: PSX emulators took years to converge on certain
corners of the GTE.

---

# M0: the game boots

## What runs

The image of `PSX.EXE` is loaded into RAM, execution starts at `0x8003FA9C`,
and `_start` calls `InitHeap` then `main`. The game configures the GPU — draw
mode, texture window, drawing area, offset, mask: the exact output of
`SetDrawEnv` — then enters its loop.

**946 functions translated, three stubs** (two `syscall`s and one COP0
access).

## The proof is not a counter

The BIOS `A0(3F)` is the kernel's `printf`. Implementing it costs ten lines
and gives the game back its own voice:

```
ResetCallback: _96_remove ..
CdlReset: timeout
NoIntr: 0
DataReady: 0
Complete: 0
Acknowledge: 0
DataEnd: 0
DiskError: 0
CdlSetloc: timeout
...
```

That is Ridge Racer's CD driver. It attempts `CdlReset`, waits for its
interrupt flags, receives none — since there is no drive — and prints its
diagnosis, exactly as it would on a console whose tray was empty.

No external metric would say that as well. The game runs its real code,
reaches its real driver, and reports its real failure.

## Three silent bugs found along the way

None of them would have prevented compilation.

**Indirect jumps.** `jr $ra` is a return; `jr` on any other register is a
computed jump — a branch table, or a BIOS trampoline. I was translating them
all as returns: **54 jumps** went the wrong way, silently.

**Indirect calls.** `jalr` was translated as a return too. **59 calls** were
never made. They now go through an address → function table, which also
serves to recognize the BIOS vectors `0xA0`, `0xB0`, `0xC0`.

**Branches to a delay slot.** Since the slot is moved ahead of its branch,
the address no longer carries a label. C refused the `goto`, which revealed
it — the only one of the three that the compiler caught. The fix puts the
label back after a jump over it, so as not to replay the instruction when
falling into it.

The first two existed only because nothing had counted them: the verification
bench, for its part, exercised no function that contained any.

## What M0 is not

There is no picture. The GPU logs instead of drawing, interrupts do not
exist, and the game therefore spins in its CD wait — `B0(03)` three hundred
million times in twenty seconds, which is very precisely what a wait loop
with no hardware must do.

Next is M1: the CD drive and interrupts so that the game gets past its
loading, then the GP0 stream to OpenGL. And for the latter, all the naming
work on libgpu — `SetPolyFT4`, the tpages, the CLUTs, 4-bit VRAM — is already
done.

---

# M1, first part: the hardware the game asks for

## The survey, rather than the grep

The CD driver goes through a global pointer, hence invisible to the
disassembly. I took it from the other end: a histogram of the hardware
addresses touched during execution.

| register | reads | writes | |
|---|---|---|---|
| `0x1F801814` | 63,432,514 | 7 | GPU status |
| `0x1F801800` | 33,554,437 | 3 | **CD drive** |
| `0x1F801D80`–`0x1F801DB8` | a few | ~50 | sound processor |
| `0x1F8010A8` | 6 | 3 | GPU DMA |

Thirty-three million reads on a single register: that is a wait loop, and it
says exactly where the game is stuck.

## What was built

**The CD controller** — index, parameter and response queues, interrupt
flags, and the startup commands. It works: the game sends `Init` once and
`Setloc` four times, and the controller answers.

**The BIOS event system** — `OpenEvent`, `EnableEvent`, `TestEvent`,
`DeliverEvent`. The game opens an event for class `0xF0000009` right at
startup.

**The BIOS call sequence**, traced in order. It reads like a boot log:
`InitHeap`, `SetMem(2)` for two megabytes, `_96_remove`, installing the
exception handler, `InitPAD2` and `StartPAD2` for the controllers, `InitCARD2`
and `StartCARD2` for the memory card, `_bu_init`, then opening the CD event.

## Where it stalls, precisely

`B0(19) HookEntryInt` installs **the game's** exception handler: it does not
poll the hardware, it waits to be called. But the address read from its
structure is zero, because `A0(13)` — which fills it in — is still a stub.

It is a link, not a wall: as long as the handler has no address, no interrupt
can be delivered to it, and the driver counts zero callbacks on its six
counters — `NoIntr`, `DataReady`, `Complete`, `Acknowledge`, `DataEnd`,
`DiskError` — before concluding a timeout. Exactly what it would do on a
console whose drive did not answer.

## A simplification that comes from the game itself

The drive serves at only two moments: **at the initial load**, and then **for
the audio tracks**. In between, everything is in memory — the game fits in
the two megabytes and never goes back to the disc.

That changes the order of the work. Emulating the drive at sector level, with
its table of contents and its ISO 9660, is not necessary in order to see a
picture: it is enough to serve the initial load. And audio playback, which
has nothing to do with data, is handled separately and later.

## The link repaired — and the next one

`A0(13)` is **`setjmp`**, already named in the repository. The pattern then
reads unambiguously in `func_800492B0`:

```
setjmp(&context);
if (v0 == 0) { HookEntryInt(&context); return; }
... handler body ...
```

The game is not installing a function: it is **saving a context**. On the
console, the BIOS comes back to it by `longjmp` at each interrupt, and
execution resumes just after the `setjmp`, with a non-zero value.

A per-function translation cannot jump into the middle of a dead frame — the
host's `longjmp` would aim at a stack that no longer exists. But it can
**call the function again, making the `setjmp` return 1**, which takes exactly
the same branch. That is what `deliver_irq` does.

Result: **70,265 interrupts delivered** in ten seconds, and four BIOS events
delivered. The game's handler runs.

But its six counters stay at zero. The next link is therefore in the
acknowledgment: the handler runs, reads the status, and does not yet
recognize the drive's interrupt as its own. That is where the work will
resume — and the next survey to make is of the registers the handler reads
*while* it is running, as opposed to those the main loop reads.

## Interrupts, for real

Three fixes, each of them found by instrumenting rather than by guessing.

**`I_STAT` was a constant.** I was returning a fixed value for the pending
sources, and I was losing the acknowledgments — writes to that register were
handled by no case at all. A flag that never clears makes the same source be
reprocessed endlessly, and the others never arrive. The register is now real:
writes clear the bits to zero, like the hardware.

**The mask, surveyed rather than assumed.** The game arms `0x0008` then
`0x000C` — DMA, then DMA and CD drive. So it does expect the drive's
interrupt, which rules out the hypothesis of a purely polling driver.

**The clock stopped at the wrong moment.** I was delivering interrupts paced
on GPU status reads. But the drive's wait loop reads only its own register,
thirty-three million times — never the GPU. In other words, my watch stopped
precisely while the game was waiting for an interrupt. Delivery is now paced
on any hardware read.

The handler's body reads easily enough, in fact, once you know where to look:
it loads `I_STAT` and `I_MASK` **through pointers**, stored at `D_80077440`
and `D_80077444`, combines them, and tests bit 3 first — the DMA — before
branching elsewhere for the rest.

## What still resists

Three million interrupts delivered, the handler runs, the mask is right, the
controller answers — and the driver's six counters stay at zero.

The main suspect is the `setjmp`/`longjmp` emulation. Calling the function
again with the `setjmp` returning 1 takes the right branch, but **does not
restore the registers saved** at the moment of the `setjmp`. If the handler's
body depends on one of them, it works on values that are not the ones the
hardware would have given it.

That is a limit of principle of per-function translation, not an oversight.
The clean way out would be to save and restore the persistent registers
explicitly in the context structure — which is what the real `setjmp` does —
and therefore to translate those two functions by hand rather than stub them.

## Do not replay: enter at the right place

The `setjmp` diagnosis was right in principle and wrong about the cause.

Calling `func_800492B0` again from its start did take the right branch — but
**replayed its whole prologue at each interrupt**. And that prologue re-arms
the mask, zeroes two arrays and calls `func_800495DC` again. In other words,
each interrupt erased the state the driver had just established. No sequence
could succeed.

The way out did not call for restoring registers: it called for **entering at
the right place**. The handler's body starts at `0x8004934C`, just after the
test that follows the `setjmp`. Translated as a function in its own right —
it accepts that without flinching, 141 instructions — it runs without
touching the prologue.

That is the right way to render a `longjmp` in a per-function translation: do
not replay, enter at the resumption point.

**Result: `Acknowledge: 1`.** The driver's first non-zero counter. The
handler reaches its CD branch, recognizes the drive's interrupt and
acknowledges it.

The controller also knows how to answer twice now — an acknowledgment `INT3`
then a completion `INT2` once the driver has picked up the first — which is
what the console does for `Init`, `Pause` and seeks.

## The state, without rounding

One counter out of six has moved, and once. The dialogue begins but does not
continue: the driver receives its acknowledgment, then falls back into
timeout. Something is still missing between the acknowledgment and the rest —
most likely the exact sequence that `CdlReset` expects, or a controller state
that I am getting wrong.

It is little, but it is the first time the driver recognizes something that
comes from us. Until now its six counters were at zero because no interrupt
reached it; now that one does reach it, what is left to fix is protocol
detail, not architecture.

## The dialogue, visible at last

Two fixes, then a complete trace.

**The time base.** The driver's wait loop reads no register: it counts down
turns while watching a flag in memory that the handler is supposed to set.
Delivering the interrupts on hardware reads therefore never reaches it —
`CdlReset: timeout` was printed **before** the response was read. A clock
paced on function calls was not enough either: between the command and the
expiry there are not two hundred and fifty-six calls.

The interrupt is now raised **on the spot**, when the command is written, as
the hardware does. The order is finally the right one: command, flags,
response, and only then the driver's verdict.

**What the trace shows.**

```
cd: index        00
cd: COMMAND      0A          <- Init
cd: index        01
cd: read flags   E3          <- INT3, the acknowledgment
cd: read reply   02          <- the drive status
CdlReset: timeout
cd: index        02
cd: write 1803   00          <- audio volumes
cd: index        03
cd: write 1801   80
cd: write 1803   20
```

The driver receives its acknowledgment and reads the response. Then it
declares the timeout and moves on to setting the volumes.

## What is missing, named precisely

**It never acknowledges.** No write at index 1 to `0x1F801803` — and that is
how an interrupt flag is cleared on this machine. And the survey of the
registers read *during* the handler confirms it: it touches only `I_STAT`,
`I_MASK` and the DMA control. **It never talks to the drive.**

The conclusion is unavoidable: the handling of the CD interrupt is not in the
body I wired up. There is a second level — a callback registered elsewhere,
which the general handler calls and which my translation does not yet reach.
That is the link to follow, and the trace now gives what is needed to do it:
we know the exact order of the exchanges and the precise place where the
chain breaks.

## The CD callback chain, mapped

By looking for the drive's address in the image rather than in the code — it
is stored at `0x800774D8` and `0x80077520` — the whole chain can be traced
back.

**`D_8005497C` is a function, not data.** Six hundred and twenty-one
instructions, labelled `D_` by splat for want of a direct reference, and it
manipulates the drive base, `I_STAT` and `I_MASK`. It is the game's CD
callback. It has in fact been at the top of the largest "functions" left in
assembly from the very beginning, under that misleading name.

**`func_80051CE4` is `CdSyncCallback`**: three instructions that store their
argument in `D_801E9170` and return the old one. The game calls it with
`D_8005497C` at startup, just after registering `func_80054664` through
`func_800490B0`.

**Five functions read `D_801E9170`** in order to invoke the callback:
`func_80052504`, `func_80052854`, `func_800532C8`, `func_80053390`, plus the
registrar itself.

Two more names along the way — and above all the certainty that the function
missing from the interrupt chain is identified, translated, and present in
the native binary. What remains is to understand by what path it ought to be
reached from the general handler, since that one never touches the drive.

## The link found: the game was counting on the BIOS

Reading the game's dispatcher, in `func_800492B0`, settles the question.

It loops over the bits of `I_STAT & I_MASK`, looks for a callback in
`D_800797A8[bit]`, calls it by `jalr`, then acknowledges by writing
`~(1 << bit)`. A second branch does the same thing for the DMA's seven
channels, with its own table `D_80079788`.

But **nobody registers a callback for bit 2**, the drive's. `func_800490B0`
does register `func_80054664`, but for **DMA channel 3** — the drive's DMA,
not its interrupt. The game therefore counts on the BIOS to read the
response, acknowledge, and call the function it installed through
`CdSyncCallback`.

That is exactly the service that needed rendering — not emulating a BIOS
image, but rewriting the function that this game calls. About twenty lines:
pick up the interrupt type and the response, acknowledge, chain on to the
completion if the command expects one, and call the callback with
`(type, result)`.

## The result: the boot sequence advances

```
CdlReset   -> CdlSetloc -> CdlSetmode -> CdlReadN
```

The driver now gets through four steps where it used to replay `CdlReset` in
a loop. It is the exact sequence of a boot from disc: reset, position, set
the mode, read.

It stumbles on the read, which is expected — no data is served to it yet. And
that is where the remark about the drive's two uses takes on its full value:
there is only one load to serve, once, before the game never needs the disc
again.

## The disc, served

The `data.iso` image is a **real ISO 9660 file system**, simply truncated:
`RIDGERACER`, 184,568 sectors announced of which we have the first 1,559 —
which is enough, because the volume descriptor is at sector 16, the path
table at 18 and the root at 22. Everything that describes the disc is there;
only the data is missing.

And the data, we have elsewhere. The directory gives each one's starting
sector:

| file | sector | size |
|---|---|---|
| `PSX.EXE` | 23 | 425,984 |
| `RR.VH` / `RR.VB` | 231 / 247 | sound |
| `TEX4` … `TEX3` | 487 … 1003 | textures |
| `MAP.RRM` | 1057 | 271,548 |
| `OBJ.RRO` | 1190 | 445,348 |
| `IDX.HED` | 1408 | 2,048 |

The serving layer is therefore simple: **the metadata comes from the image,
the data from the extracted files**, each at its declared sector. The game
sees no difference — it asks for a sector, it gets the bytes that are there.
No data is versioned: the table regenerates itself from your own image.

`Setloc` is decoded — minutes, seconds and frames in binary-coded decimal,
minus the 150 lead-in frames — and DMA channel 3 transfers one sector to RAM
then advances by one.

## Where the sequence stands

It gets longer with each fix:

```
CdlReset                                          (at the start)
CdlReset -> CdlSetloc -> CdlSetmode -> CdlReadN    (after the BIOS service)
... -> CdlReadN -> CdlPause -> CdlReadN            (now)
```

The driver now chains reading and pause, and starts again. But no sector is
requested yet: it does not reach the transfer, because its initialization
still expires before registering its synchronization function — which
therefore stays null, and the callback never called.

It is a circle that has to be opened from the right end: what the driver
lacks is not the data, it is the confirmation that its command succeeded. The
next work is there, on the `INT2` completion and not on the sectors — which,
for their part, are ready to be served the day it asks for them.

## The chain was complete — and I was breaking it

Tracing the driver's counters back, everything becomes clear.

`func_80052440` prints "*command*: timeout" then six counters read at
`D_80077610`, which it resets to zero. Those counters are incremented by
`func_80052504` — the driver's interrupt routine, the one that touches the
drive base and the synchronization callback. It is called by `D_80052820`,
another function labelled as data, whose address is handed to `func_80049140`,
which registers it… **for interrupt 2, the drive's.**

And at run time, the table is indeed filled in:

```
irq 2 -> 80052820        <-- CD drive
CD sync callback (D_801E9170): 800535C8
```

So the game was **not** counting on the BIOS for the drive: it has its own
handler, duly registered, and the dispatcher calls it by `jalr`.

My "BIOS CD service", written in the previous round, **was stealing its
interrupt**: it picked up the response and cleared the flag before the game's
handler could read them. It has been removed.

That is a lesson worth noting down as it stands: *rendering a service that
nobody asked for is a discreet way of breaking a chain that worked*. The
sequence had grown longer just after it was added, which had convinced me it
was helping — when it was growing longer for another reason, the time base
fixed at the same moment.

## What remains

The driver receives its `INT3` acknowledgment on each command, and **never
acknowledges** at the controller level: no write at index 1 to `0x1F801803`.
Yet without an acknowledgment, the hardware does not deliver the next
response — the `INT2` completion that the driver is waiting for to conclude.

Two possible readings, and they have to be told apart rather than chosen
between: either my model of the status register is wrong and the driver
acknowledges some other way, or its handler does not reach the code that
acknowledges. The access trace is in place; what is missing is to read it
from inside the game's handler rather than from the controller.

## M1 cleared: the game reads its disc and draws

Seven defects, found in this order, each one masking the next.

**1. The `jr` of a `switch` went nowhere.** The CD drive's interrupt handler
(0x80052504) sorts its six interrupt types through a jump table. The
translator sent every non-`$ra` `jr` to the global dispatcher, which knows
only function entries: the target, internal to the function, could not be
found. The counter was already saying so — "indirect jumps with no target :
8" — and I had not read it. Everything after the `switch` was lost, including
the acknowledgment. `tools/recomp.py` now gives a local switch to any
function that contains such a jump, with a fallback on the dispatcher.

**2. The controller answered too fast.** The second response (INT2, INT1) was
issued in the acknowledgment itself. The driver loops as long as a flag is
raised: it never came out. Six million sectors served, no progress.

**3. The time base stopped when you looked at it.** `CdSync` waits in a loop
that reads no register and calls no function — it watches a byte in RAM.
Pacing time on the hardware or on the calls amounted to stopping the watch
exactly during the wait. The clock now beats on memory accesses (`TICK()` in
`rt.h`): the one thing that running code cannot refrain from doing.

**4. The interrupt did not give the stack back.** `$sp` crept up at each
interrupt. After a few of them, buffers allocated on the stack fell beyond
the two megabytes and the writes were silently thrown away. The game then
read a null disc position and concluded "File not found" — after having read
its PVD correctly. `deliver_irq` saves and restores `$sp`, which the hardware
guarantees and the translation does not.

**5. `strcpy` did not exist.** The library replaces the string functions with
trampolines to `0xA0`. Not implemented, they return zero without copying
anything — and the defect shows up very far away. The sixteen string and
memory functions are written.

**6. `VSync` was waiting on an absent counter.** It does not count the frames
itself: it asks the BIOS for the difference since its last call
(`B0(03) GetRCnt`). With no answer, the difference is always zero.

**7. The display list was read wrong.** A null link was followed as an
address, and the texture data of an `A0` packet was counted as commands.
Hence a log full of impossible codes.

State: 907 sectors served, 1677 display lists walked, 99,541 GPU commands of
which 54,804 flat rectangles and 6,173 textured. The game prints its own
sound diagnosis (`ss_init error`). What remains is to port GP0 to OpenGL, in
order to see the picture rather than count it.

## M2: the picture

The GPU log is replaced by a real rasterizer (`tools/m0/gpu.c`): 1024×512
video memory, flat, gouraud and textured polygons, rectangles and sprites,
lines, transfers, 4- and 8-bit palettes, texture window, drawing area,
offset, semi-transparency in its four modes. Software and not OpenGL: what
we are trying to establish is fidelity, not speed, and it runs in a container
with no screen.

Four defects revealed themselves by looking at the picture rather than at the
counters.

**DMA 2 has three modes, not one.** `LoadImage` pushes the pixels in blocks.
Treating them as a linked list made the channel follow a link drawn from the
texture itself — hence a phantom 1024 by 256 transfer that smeared the whole
video memory.

**The texture window applies with the raw mask.** I was inverting it, and the
default value became "keep only three bits of the x coordinate": every texel
came from a single eight-pixel column. The glyphs were in the right place,
all identical.

**With no gouraud, the single color occupies the first word.** I was reading
the command word as a coordinate: every flat polygon landed somewhere else.

**An internal copy of zero size** is not "the whole video memory": following
it to the letter amounted to smearing the screen starting from a badly
aligned word.

Result: the loading screen (the Galaxian), then the complete title screen —
checkered flag, logo, legal notices, "PUSH START BUTTON" — then the demo,
where only the background draws. Two minutes of running without incident:
751,855 GPU commands, 4,104 display lists. The game does not crash; it is
still missing the track.

## M3: the track

Three defects, and the third one explains all the other symptoms.

**A DMA channel has a direction.** Bit 0 of the control register says who
feeds whom. I was always assuming "memory to GPU"; `StoreImage` does the
opposite. Result: the contents of the stack were pushed into the GPU, which
read them as commands — hence internal copies drawn from nowhere that smeared
the display buffer with texture.

**Drive commands that move the mechanism answer twice.** I had implemented a
few of them; `SetSession` was missing, and that is the one the game sends
just after loading its data, at the moment it moves on to the audio track.
The driver was waiting for a completion that never came and declared a
timeout — loading stopped there.

**`InitGeom` was a stub.** The function that arms the GTE in the system
coprocessor's status register also sets ZSF3 and ZSF4, the factors that
convert a depth into a display-list index. The translator refused the
function for its single COP0 instruction, and I had replaced it with a silent
stub — and without ZSF3/ZSF4, `avsz4` returned zero for every polygon. The
game, which discards whatever falls at index zero, was discarding the entire
track: only the sky was drawing. The translator now models COP0 as an array
of registers, and `syscall` as a call.

The lesson is the same as the previous chapter's: a silent stub does not
break where it is. This one showed up five functions away, in the form of a
picture with no road.

Result: the demo runs. The starting straight, the tunnel, the suspension
bridge, the cars. 908,064 GPU commands in ninety seconds, 3,236 frames, no
missing sector.

## M4: the controller

The BIOS does not read the controller on demand. `InitPAD` gives it the
address of two buffers, `StartPAD` arms the filling, and the game consults
those four bytes when it wants to: a status, a type, and sixteen active-low
buttons. Three more BIOS calls, and the game stops being a demo.

Input comes from a **script** written in advance rather than from a keyboard
— `PAD_SCRIPT="60000:start 63000: 90000:start 93000: 140000:start"` — so that
two runs give exactly the same picture. An interactive session will come with
the OpenGL port; in the meantime, a script is what makes a defect
reproducible, and therefore findable.

That particular script goes through the title screen, opens the menu
(`COURSE SELECT`, `MISSION SELECT`, `CAR SELECT`, `SOUND SELECT`) and starts
the race. The dashboard displays in full: lap, position, lap time, record,
total, the circuit map, the tachometer and the gear engaged.

## What remains

- **Sound.** `ss_init error / 3312 > 3264` is the game's own diagnosis: the
  SPU bench is not modeled at all, and the 24 voices are only registers being
  counted.
- **Speed.** The software rasterizer manages a few frames per second. The GP0
  stream is already exactly what needs to be given to OpenGL; it is the
  natural next step, and it will make the game interactive.
- **The decompiled functions.** That is where the point of all this lies:
  each byte-matched function replaces its translated twin in `table.c`, and
  the game keeps running at each replacement.

## M6: time counted rather than guessed

A static recompilation loses the one thing that gave the game its tempo: the
time each instruction took. This is not a disagreement between two rates,
like the 50/60 Hz of the PAL era — it is the **absence** of a rate. One has
to be manufactured, then, and the choice decides everything.

The clock first beat on memory accesses, for want of anything better. A
convenient and false substitute: time then had to be pushed by hand whenever
the game waited without reading anything, and the scan counter no longer
meant anything.

It now counts what the machine counted.

**The processor.** The translator charges for each straight-line block:
between two control transfers we know exactly how many instructions are going
to run, so one addition per block is enough — 16,518 `CYCLES(n)` for the 949
functions. The scan falls when a frame's budget is spent.

**Drawing.** The GPU filled about one pixel per cycle at 53.2 MHz, that is
887,000 pixels between two scans. The pixels written by the rasterizer are
converted into the same currency and subtracted from the budget. Without that
accounting, a busy scene costs the same time as an empty one, and the game
runs too fast exactly where it used to slow down.

**Waiting is charged for, it is not played out.** `VSync` runs the processor
idle until the next scan. Simulating that wait instruction by instruction
would be faithful and absurd: the clock is advanced to the deadline, which is
what those cycles would have done anyway. It is the same gesture as the
emulators' wait-loop detection, but it no longer manufactures a scan out of
nowhere — it records an expenditure.

### What the measurement answered

Two questions were still open, and the count settles them.

*Does the game aim at 30 or 60 frames per second?* The binary's fifteen calls
to `VSync` all pass **1**, never 2: the code asks for one scan per frame. And
the pixels confirm it — **73,000 per display list**, two lists per frame,
against the 887,000 that the hardware could sustain. Ridge Racer used less
than a quarter of the fill budget. The 30 frames per second it is credited
with are not what it was asking for.

*How fast does the translation run?* **1.7 billion instructions per second**,
about fifty times an R3000. That is why the 60 Hz cap on the window is not a
comfort but a necessity.

## M7: the music

The game never asked for `Play`, and I long believed the music was waiting
for a synthesizer. It was waiting for an answer: `GetTN` was announcing **a
single track**. As soon as it is told there are thirteen, it asks for `GetTD`
for each one, seeks with `SeekP`, and starts `Play`.

Because Ridge Racer's soundtrack is not synthesized. They are twelve ordinary
audio tracks, burned alongside the data, that the console read with the same
mechanism as any compact disc. So there was nothing to write in order to hear
it — only sectors to serve.

The format works out exactly: an audio sector is 2352 bytes, that is exactly
588 stereo frames of sixteen bits at 44,100 Hz. Neither conversion nor
resampling.

**Who sets the tempo.** The sound card, not our clock. As long as its queue
is full enough, no sector is read. Tuning the two rates to each other would
have required them to stay in agreement, which they never do for long — and
a drift of a few thousandths can be heard, where it cannot be seen.

`build.py` reads the `.cue` sheet and computes the absolute positions by
accumulating the file lengths, a raw sector being 2352 bytes. `INDEX 01`
gives the real start of each track, after the two seconds of silence its file
carries — forgetting them would shift the whole soundtrack.

The game asks for track 8 at the menu. The SPU remains, for the engine.

## M8: the SPU

`ss_init error` was accusing the SPU of being absent; it disappeared as soon
as the twenty-four voices existed. But first, what the game was saying had to
be untangled.

**`3312 > 3264` was not a defect.** Those two numbers come out of a `printf`
whose constants are frozen in the binary — `li a1,0xCF0`, `li a2,0xCC0` —
printed unconditionally, in a function that does nothing but initialize a
pointer. It is a developer warning that Namco shipped as-is to the serial
port that nobody plugs in. It prints on a console too. Only `ss_init error`,
which is conditional, was accusing us.

**The blockage was somewhere other than in the sound.** Once initialization
succeeded, the game got further and fell asleep on a DMA transfer completion
event that we were not delivering. The DMA control register carries the
enables in its bits 16 to 22 and the flags in bits 24 to 30; without it, the
event never arrives. The game did not crash — it waited, sixteen frames in
two minutes.

**What works**: the SPU's memory and its transfer (491,072 bytes in one go,
the whole bank), ADPCM decompression with its loops, pitch, volumes, key-on
and key-off. Peak measured at 35,574 on saturated material — the voices do
produce sound.

**What does not work yet, and is counted**: the game keys on its voices while
`SPUCNT` is zero. On the console that would produce nothing, so it would not
do it: the defect is ours, in a status register modeled halfway, from which
the driver derives the value it writes back. Rather than returning silence
while waiting to have understood, we mix and we count — 288 voices per minute
of play. That counter is the exact measure of what remains to be understood,
and it appears in the status report at every run.

### The discrepancy was not in the SPU

The counter of voices keyed on "SPU off" did its job faster than expected: it
pointed at the fault, which was not where the symptom was showing.

The driver does a perfectly clean read-modify-write on `SPUCNT` —
`lhu 0x1AA`, `andi`, `ori`, `sh 0x1AA`. The enable bit could only be lost if
the **read** returned something else. It returned something else:

```c
if (p >= 0x1F801000) return hw_read32(p & ~3u) >> (8 * (p & 2));
```

A sixteen-bit read is not a thirty-two-bit read from which you take one half.
Folding the address down to the lower word made it read the **neighboring**
register — `SPUCNT` at 0x1F801DAA returned the SPU's transfer queue, that is
to say zero. The driver lost the enable there on every pass.

Half of the SPU's registers are at an address congruent to 2 modulo 4, so
half of them were read wrong. A halfword read worthy of the name now serves
them as they are.

Two things are worth remembering. The first is that this defect had been
living in `rt.h` since the first day, invisible: nothing before the SPU read
a register by halfword at an address odd in words. The second is that the
counter was enough — putting a number on a discrepancy rather than describing
it gives you something to bring down to zero.

### The envelope, for real

One declared approximation remained: the envelope slopes. They now follow the
hardware. The principle is the same in all four phases — a shift gives the
period, a step gives the amplitude — but the pair is read at a different
place in the register depending on the phase, and two rules are added in
exponential mode: a rise slows by a factor of four past three quarters, a
fall is proportioned to the level reached. It is that second rule that gives
key-offs their trail, and a linear slope cannot imitate it.

Before writing it, a measurement ruled out the other approximation that was
lying around. The hardware volumes can be a fixed value or a sweep; we were
approximating the sweeps by their starting value. The counter says **20,343
simple volumes and zero sweeps**: this game never uses them. The
approximation remains, documented, but we now know that it costs nothing
here — and the counter will say so again if another game comes this way.

Counting before fixing avoided writing exact code for a dead path, just after
counting in order to find a wrong one.

### The effects, late

Symptom reported by ear: triggered sounds arrive after the gesture. The cause
was not in the SPU but in the sound card's queue, which I was filling **a
quarter of a second** ahead.

It is the kind of defect that no counter would have flagged, because nothing
was wrong: the samples were correct, in the right order, at the right rate.
They were merely computed too early. Everything already in the queue was
produced before the event that has just happened, and the sound therefore
goes out late by exactly the lead one has given oneself.

On music, it cannot be heard — a continuous stream has no "right moment". It
can be heard on anything that is triggered, because the ear compares it with
the picture.

The measurement gives a clean knee, by counting the times the queue is found
dry:

```
 20 ms -> 867 times dry
 30 ms ->   8
 40 ms ->   8
 60 ms ->   8
100 ms ->   8
```

The plateau at eight is structural — the track changes — and not a filling
defect. Forty milliseconds is therefore the first setting that costs nothing,
and it divides the lag by six. `LATENCY` lets you judge it by ear, which
remains the only instrument for this sort of thing.
