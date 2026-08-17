# The renderer: what has been identified

*Read by hand, August 2026. Every point below is read out of the
instructions, not inferred from a resemblance.*

## Four named functions

| address | name | evidence |
|---|---|---|
| `0x8004617C` | `SetDrawMode` | writes `len = 2` into byte 3 of the tag, then two words: `_get_mode(dfe, dtd, tpage)` and `_get_tw(tw)`. Two GP0 commands, in that order, right before `SetDrawEnv`. |
| `0x80046430` | `_get_mode` | builds `0xE1……`: base `0xE1000200` or `0xE1000800` depending on `dtd`, masks the tpage with `0x1FF` or `0x27FF` depending on the global flag `D_80077378`, sets bit 10 or 12 depending on `dfe`. |
| `0x800465DC` | `_get_tw` | builds `0xE2……`: `(x>>3)<<10 | (y>>3)<<15 | ((-w & 0xFF)>>3) | (((-h & 0xFF)>>3)<<5)`, and returns 0 for a null `RECT *`. |
| `0x80043738` | `negate_rot_row0` | `cfc2` of control registers 0 and 1, negation of R11, R12 and R13 — and **not** R21 —, `ctc2` back. That is the first row of the rotation matrix, hence the X axis of the result. |

`SetDrawMode` had already been converted and matched (in `x_c257_00.c`):
what was missing was its name, and it holds for its 67 call sites.

## The mirror flag is at offset 0x24 of the render context

Two independent functions read the same field and draw the same
consequence from it:

`func_80033FBC` (and some fifteen others built on the same mould):

```
    lw   $v0, 0x24($s1)        ; s1 = 2nd argument = the context
    beqz $v0, no_mirror
    jal  negate_rot_row0       ; X negated in the current matrix
    jal  func_800437AC         ; the real work
    jal  negate_rot_row0       ; restore
```

`func_8004006C` (`rtpt` + `nclip`, the transform-and-cull):

```
    lw   $v0, 0x24($a1)
    bnez $v0, flipped
    mfc2 $v0, $24              ; MAC0 = signed area out of nclip
    bgtz $v0, keep             ; normal winding
flipped:
    mfc2 $v0, $24
    neg  $v0, $v0              ; reversed winding
    bgtz $v0, keep
```

A reflection along X reverses the winding order of the polygons; the
backface test therefore has to be reversed as well, or the whole scenery
turns inside out. The two halves of that consequence are written in two
separate functions, and they agree. This is the game's **mirror mode**.

Practical consequences:

- field `0x24` of the render context is called `mirror` and nothing else;
- for the port, this flag does not translate into a naive `scale(-1,1,1)`:
  the winding order has to be flipped too, exactly as it is here;
- `func_800437AC` is the real drawing body, called in both branches — that
  is the one to read next, not the nest of wrappers.

## What this does not say

Nothing about the placement of `MAP.RRM`'s sections. The cluster of four
contiguous functions (`0x8003486C`, `0x80034EFC`, `0x80035638`,
`0x80035EAC`) remains the best candidate, but the mirror pattern runs
through the whole region: half the calls met so far are wrappers of this
kind, and they have to be crossed before reaching the transform.

## Environment note

The toolchain (`/opt/psx-gcc`, `/opt/psx-gcc257`) does not survive
recycling of the container. Rebuilding it from source on a recent Ubuntu
takes two fixes that the `Dockerfile` (focal-based) has no need to carry:

- **GCC 2.7.2**: `xgcc` no longer links, `sys_nerr` having disappeared
  from glibc. Link with an extra object containing `int sys_nerr = 132;`.
- **GCC 2.5.7**: `cc1` no longer links, modern C being `-fno-common` by
  default (`local_vars_size`, `byte_mode`, `word_mode` defined twice).
  Link with `-Wl,--allow-multiple-definition`.

Both fixes touch only the host's link step, never code generation: the 944
matches came back identical after the rebuild.

## The block of libgpu primitive initialisers

Twenty-two contiguous functions from `0x80047B48` to `0x80047D1C`, each of
five or eight instructions, all built on the same gesture: write a length
into byte 3 of the tag and a GP0 command code into byte 7. That is the
signature of `setPolyF4` and its whole siblinghood, and a contiguous range
of functions doing exactly the same thing, bounded by code that does not,
is an **original translation unit** — the third identified by contiguity,
after the BIOS trampolines and the GTE wrappers.

| address | length | GP0 code | name |
|---|---|---|---|
| `0x80047B48` | 4 | `0x20` | `SetPolyF3` |
| `0x80047B5C` | 7 | `0x24` | `SetPolyFT3` |
| `0x80047B70` | 6 | `0x30` | `SetPolyG3` |
| `0x80047B84` | 9 | `0x34` | `SetPolyGT3` |
| `0x80047B98` | 5 | `0x28` | `SetPolyF4` |
| `0x80047BAC` | 9 | `0x2C` | `SetPolyFT4` |
| `0x80047BC0` | 8 | `0x38` | `SetPolyG4` |
| `0x80047BD4` | 12 | `0x3C` | `SetPolyGT4` |
| `0x80047BE8` | 3 | `0x74` | `SetSprt8` |
| `0x80047BFC` | 3 | `0x7C` | `SetSprt16` |
| `0x80047C10` | 4 | `0x64` | `SetSprt` |
| `0x80047C24` | 2 | `0x68` | `SetTile1` |
| `0x80047C38` | 2 | `0x70` | `SetTile8` |
| `0x80047C4C` | 2 | `0x78` | `SetTile16` |
| `0x80047C60` | 3 | `0x60` | `SetTile` |
| `0x80047C74` | 3 | `0x02` | `SetFill` |
| `0x80047C88` | 3 | `0x40` | `SetLineF2` |
| `0x80047C9C` | 4 | `0x50` | `SetLineG2` |
| `0x80047CB0` | 5 | `0x48` | `SetLineF3` |
| `0x80047CC4` | 7 | `0x58` | `SetLineG3` |
| `0x80047CE4` | 6 | `0x4C` | `SetLineF4` |
| `0x80047D04` | 9 | `0x5C` | `SetLineG4` |

The polygon, sprite and tile codes are the hardware's own and can be read
in any GPU documentation. The four line rows call for one step more:
`0x4C` and `0x5C` set bit `0x04`, **which the GPU ignores**. The hardware
knows only `0x48` for a flat polyline and `0x58` for a gouraud one; it is
libgpu that uses this free bit as an internal marker to tell the
three-point variant from the four-point one. The lengths confirm it
without ambiguity: 5 and 6 for the flat ones, 7 and 9 for the gouraud
ones, with the `0x55555555` terminator written at the corresponding word —
`0x18` for length 6, `0x1C` for 7, `0x24` for 9.

These twenty-two names are obtained without an SDK, by reading two
constants per function and a table of hardware commands.

## Thirteen more GTE accessors, read off the register numbers

The `0x8003FA94`–`0x8003FDEC` block — the one that starts exactly at the
game/library boundary — still held fourteen functions that `src/gte.c` did
not cover. Thirteen name themselves without the slightest ambiguity,
because the COP2 register number they touch *is* their definition:

| address | instructions | registers | role |
|---|---|---|---|
| `0x8003FB68` | `lwc2 $2, $3` | VXY1, VZ1 | `gte_ldv1` |
| `0x8003FB78` | `lwc2 $4, $5` | VXY2, VZ2 | `gte_ldv2` |
| `0x8003FB88` | `lwc2 $0..$5` | the three vertices | `gte_ldv3` |
| `0x8003FBA8` | `lwc2 $6` | RGB | `gte_ldrgb` |
| `0x8003FBB4` | `lwc2 $20, $21, $22` | RGB0, RGB1, RGB2 | `gte_ldrgb3` |
| `0x8003FCF0` | `swc2 $9, $10, $11` | IR1, IR2, IR3 | `gte_st_ir3` |
| `0x8003FD04` | `swc2 $19` | SZ3 | `gte_stsz` |
| `0x8003FD10` | `swc2 $17, $18, $19` | SZ1, SZ2, SZ3 | `gte_stsz3` |
| `0x8003FD24` | `swc2 $16..$19` | SZ0 to SZ3 | `gte_stsz4` |
| `0x8003FD3C` | `swc2 $12, $13, $14` | SXY0, SXY1, SXY2 | `gte_stsxy3` |
| `0x8003FD50` | `swc2 $20, $21, $22` | RGB0, RGB1, RGB2 | `gte_strgb3` |
| `0x8003FD70` | `swc2 $25, $26, $27` | MAC1, MAC2, MAC3 | `gte_st_mac3` |
| `0x8003FD84` | `mfc2 $29` then three masks | ORGB | `gte_st_orgb3` |

The last one deserves a word: it reads ORGB and cuts it into `& 0x1F`,
`(& 0x3E0) >> 5`, `(& 0x7C00) >> 10`, written to three consecutive words.
That is the unpacking of a 5-5-5 colour into three 32-bit components — the
reading is forced by the masks themselves.

The fourteenth, `func_8003FA94`, is a `jr $ra ; nop` — an empty function,
at the exact address of the boundary. It stays unnamed: an empty function
carries no evidence of what it was.

## Seven more, in the blocks already begun

A named neighbourhood strongly constrains what is left. The five
unidentified functions of the libgpu block and the two of the trampoline
block:

**`0x80047AE0` — `TermPrim`.** `p->tag |= 0x00FFFFFF`: the 24-bit address
field goes to its end-of-list value. That is the terminator of a display
list, and nothing else writes that particular constant in that particular
place.

**`0x80047AF8` — `SetSemiTrans`** and **`0x80047B20` — `SetShadeTex`.**
Two twin functions: depending on their second argument, they set or clear
a bit of the code byte at `0x7`. Bit `0x02` is ABE, semi-transparency; bit
`0x01` is the "texture without shading" flag. Both are GPU command bits,
documented at the hardware level.

**`0x80047D24` — `MargePrim`.** Adds the two lengths read at `0x3`, adds
one, refuses anything beyond `0x20` by returning `-1`, otherwise writes the
new length and zeroes the tag of the second. That is word for word the
contract of `MargePrim`: merge two contiguous primitives, or fail cleanly.

**`0x80049638` — `EnterCriticalSection`** and **`0x800497D8` —
`ExitCriticalSection`.** `a0 = 1 ; syscall` and `a0 = 2 ; syscall`. The
PSX kernel's system call numbers are written into the instruction.

**`0x80043C54` — `gte_dpcl`.** Loads IR1-3 from the first argument, RGB
from the second, IR0 from the third, runs `dpcl` and stores RGB2 into the
fourth. It is the **only** function in the binary to emit `dpcl` —
uniqueness amounts to identification.

The doubled `swc2 $22, 0x0($a3)` is not a misreading: the store is
repeated as such in the retail build. It works around a read hazard on the
coprocessor registers, present throughout the GTE code of that era.

### Left unnamed

`0x80047AB8` copies the 24-bit address field of one primitive into another
while preserving the length byte. The gesture is clear, the name is not:
it is the first half of `AddPrim` without its second, and I prefer an
address to a plausible name.
