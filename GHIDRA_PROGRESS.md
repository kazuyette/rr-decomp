# Ghidra progress - reverse of PSX.EXE

Import: MIPS little-endian processor, Base Address 0x80010000, File Offset
0x800 (the PS-X EXE header is 2048 bytes long and must not be mapped into
memory), Length 0x67800, entry point 0x8003FA9C.

## Startup / main loop

- `_start` (0x8003fa9c): crt0 - clears the BSS, calls an A0h BIOS
  trampoline, then `main()`, then `trap(1)` (never reached in normal
  operation)
- `main` (0x80012360): inits, then an infinite loop - double buffering via
  the scratchpad (0x1f800000), state-machine dispatch (pointer table at
  0x80070ea4, index _DAT_801d34f8, not yet materialised in Ghidra), VSync
  wait, pad read, 3 render calls per frame
- FUN_800121f4: large system init - video, resetting of globals, writing of
  0xff/0x80 values into the scratchpad (probably pad/analogue calibration)

## Video / GPU

- `SetVideoMode` (0x80045440): video configuration through a `g_gpu_device`
  vtable, sends a GP1(08h) Display Mode command (NTSC/PAL)
- `g_gpu_device` (0x8007736c): pointer to a small abstraction/vtable for the
  GPU (+4 AddPrim, +0x10 send raw GP0 packet, +0x28 flags, +0x34 reset/mode)
  - rendering does not go through libgpu directly

## Pad

- `read_pad_input` (0x8002e778): decodes the pad input - ID 0x41 = standard
  digital pad, ID 0x23 = neGcon (Namco's wheel/twist controller), confirmed
  as natively supported

## Sound (SPU, 24 hardware voices)

- Sound event queue over 24 slots (0x8003aec0) -> dispatch to a voice
  handler (0x8004c74c) which compares the parameters against the voice
  already active on the slot (anti-retrigger)
- `SpuVoiceKeyOn` (0x8004a130): sets the slot's bit in a 24-bit KON mask
  spread over two 16-bit registers - matches exactly the hardware split of
  the PS1 SPU's KON registers
- Tied to the RR.VH/RR.VB disc files (VAB bank)

## BIOS / interrupts

- Two distinct idioms identified: A0h table trampolines (classic syscalls of
  the memcpy kind) and a B0h table trampoline (kernel - OpenEvent/EnableEvent,
  used here to arm timer interrupts, probably the audio sequencer's tick)

## Blockers / open leads

- Game state table (0x80070ea4): contents unreadable with the current MCP
  tooling (no raw memory read tool) - needs to be materialised by hand in
  Ghidra (create a pointer array at that address)
- FUN_80039fd4/FUN_80039d00: one-shot request/process mechanism whose exact
  role remains to be determined
- The SpuVoiceKeyOn/voice functions still need finer confirmation
  (provisional names based on strong correspondences with the SPU hardware,
  but not guaranteed 100%)
