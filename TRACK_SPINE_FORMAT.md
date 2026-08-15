# Track spine format (`D_8005A44C` / `D_8005B84C` / `D_8005CC4C`)

This page closes the gap flagged under **"Not found"** in [`MAP_RRM_FORMAT.md`](MAP_RRM_FORMAT.md):

> *Not found: any per-section coordinate transform (translation/rotation). Plotting raw `v0`
> corners top-down does not produce a closed track outline — each section's vectors appear to
> be in a local/section-relative frame.*

That observation was correct, and the reason is structural: **MAP.RRM does not contain a
placement transform because there is nothing to place.** The track is not an assembly of
positioned sections. It is a **centreline polyline stored in `PSX.EXE`**, and MAP.RRM's quads
are skinned along that ribbon at render time. The per-section frame is local because the
world transform is derived from the spine node the section is being drawn at.

As with every other format on this repo: no game data is committed here. Every address below
refers to the retail `PSX.EXE` (`RIDGERACER`, SLPS-00001), which you supply yourself.

---

## The 20-byte node record

Layout established by reading the consumer, not by inference over the data —
`func_800178A0` (already transcribed in `src/more_asm80.c`) dereferences every field:

```c
typedef struct {
    int32_t x;          /* 0x00  world X = x >> 14  (fixed point, 14 fractional bits) */
    int32_t z;          /* 0x04  world Z = z >> 14 */
    int16_t y;          /* 0x08  elevation                                            */
    int16_t angle;      /* 0x0A  heading; 4096 = full turn (rsin/rcos mask with 0xFFF)*/
    int16_t bank;       /* 0x0C  camber/banking; consumed shifted left by 3           */
    int16_t half_width; /* 0x0E  road half-width; full width = half_width * 2         */
    int16_t unk_10;     /* 0x10  open                                                 */
    int16_t unk_12;     /* 0x12  open                                                 */
} TrackNode;            /* 20 bytes — stride confirmed by the `* 0x14` in the indexing */
```

**Why the field widths are certain.** `func_800178A0` loads bytes 0x00 and 0x04 with `lw`
(32-bit) and arithmetic-shifts each right by 14, then loads 0x0A and 0x0E with `lh` (16-bit).
Reading 0x00/0x04 as pairs of `int16` instead — the natural first guess, and the one this
author made before reading the consumer — produces nonsense: apparent coordinates that jump
±32000 between adjacent nodes and a "track length" in the millions of world units.

**Indexing.** `func_80017DF4` (the surface query) computes the node address as
`(pos % D_801E90E0) * 0x14 + D_801733D8`, where `D_801733D8` is the current track's node
table and `D_801E90E0` is its node count. The car's `trackPos` field is divided by 256 first,
so one node spans 256 units of track progress.

**Edges.** For a node at heading `angle` and half-width `w`, `func_800178A0` emits the road
edge as roughly `edgeX = x + 2w·rcos(0x800 − angle) >> 12` and
`edgeZ = z − 2w·rsin(0x800 − angle) >> 12` (with the additional `>>4`, `>>1` rounding steps
present in the original). `D_801733A0` is subtracted from X before this — that global is the
**mirrored-course mechanism**.

Trig helpers, both already in the tree as `__asm__`:
`func_80044E2C` is even (`x < 0 → −x`) and is therefore **`rcos`**; `func_80044D0C` is odd
(negates the result for negative input) and is therefore **`rsin`**. Both mask the angle with
`0xFFF`, confirming 4096 = 360°. The quarter-wave lookup table lives at `D_800757A0`.

---

## The three tables

`func_80020524` is the track selector. It writes one of three base pointers into `D_801733D8`
together with a node count:

| condition | node table | count |
|---|---|---|
| `a0 + 0x9C == 0` | `D_8005B84C` | `0x100` (256) |
| else, `D_8007C210 < 3` | `D_8005A44C` | `0x100` (256) |
| else | `D_8005CC4C` | `0x170` (368) |

The tables are **contiguous**, which corroborates the 20-byte stride independently of the
consumer code:

```
0x8005A44C + 256*20 = 0x8005B84C      ✓ exactly the second table
0x8005B84C + 256*20 = 0x8005CC4C      ✓ exactly the third table
```

`St_Race_Main` (`func_80014C2C`) sets the same pairs when entering the finish phase.

### Verification

Decoding all three tables with the layout above and plotting `(x >> 14, z >> 14)` yields
**closed loops**:

| table | nodes | closure gap | mean node spacing | elevation range | half-width range |
|---|---|---|---|---|---|
| `D_8005A44C` | 256 | 523 | 524 | −393 … 2175 | 3898 … 5242 |
| `D_8005B84C` | 256 | 536 | 536 | −393 … 2175 | 3840 … 5369 |
| `D_8005CC4C` | 368 | 238 | 524 | −393 … 2218 | 3278 … 5242 |

The closure gap equals one mean node spacing — i.e. the polyline closes with exactly one
segment remaining, which is what a correctly-decoded closed circuit looks like. Decoding the
same bytes with any other field layout does not close.

The resulting outlines are recognisable as the shipped courses: the two 256-node tables share
the base layout (they differ only in a section of the middle), and the 368-node table extends
it with the additional eastern loop — matching the Novice / Intermediate / Advanced
progression, and consistent with all courses sharing one start/finish straight.

Elevation is essentially flat (~1983) along the start straight and rises to ~9300 at the
table's high point, so the `y` field is a real elevation profile rather than a constant.

---

## What this does *not* yet answer

- **How MAP.RRM's 258 sections bind to spine nodes.** The counts differ (258 sections vs
  256/256/368 nodes), so it is not a 1:1 mapping. `IDX.HED` is the strongest candidate for the
  indirection: it is 1024 `uint16` slots, `0xFFFF` = empty, holding exactly **258 valid entries
  with strictly increasing values 0..257**, occupying slots 42..657 in contiguous runs. The slot
  index space is unidentified. A spatial-grid interpretation (widths 16, 32, 64 tested) is
  ruled out — correlations between grid row/column and section centroid are 0.02–0.30, i.e. noise.
- **`unk_10` / `unk_12`.** Not dereferenced by `func_800178A0` or `func_80017DF4`.
  Candidates: per-node section id, surface/material flags, or AI racing-line data.
- **`bank` semantics.** Consumed as `<< 3` and interpolated between adjacent nodes, then
  wrapped at `0x1000` — so it is an angle, but whether it is camber, a wall angle, or a
  combined value is unconfirmed.

---

## Suggested symbol names

```
g_track_nodes        = 0x801733D8;  // TrackNode* — current course
g_track_node_count   = 0x801E90E0;
g_track_mirror_x     = 0x801733A0;
g_sin_table          = 0x800757A0;
rcos                 = 0x80044E2C;
rsin                 = 0x80044D0C;
rsin_quadrant        = 0x80044D70;
track_get_node_edge  = 0x800178A0;
track_side_of_seg    = 0x80017838;
track_query_surface  = 0x80017DF4;
track_select         = 0x80020524;
D_8005A44C           = 0x8005A44C;  // TrackNode[256]
D_8005B84C           = 0x8005B84C;  // TrackNode[256]
D_8005CC4C           = 0x8005CC4C;  // TrackNode[368]
```
