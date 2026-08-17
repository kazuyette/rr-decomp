# Section placement: solved

*Open question since the beginning of the project. `MAP_RRM_FORMAT.md`
listed it under "Not found: any per-section coordinate transform", and
`TRACK_SPINE_FORMAT.md` concluded that there was "nothing to place". Both
were wrong, and the answer was in a file that had been set aside.*

---

## The answer in one sentence

**`IDX.HED` is a 32 × 32 grid of cells of 2048 world units that maps each
cell to a section number in `MAP.RRM`.** The section is placed at the
origin of its cell; there is no rotation, only a translation.

## How we know

This is not an inference over the data. It is read in `func_800437AC`, the
real drawing body (the one behind the mirror-mode wrappers):

```
    lw   $v0, 0xC($a2)          ; section index
    bltz $v0, .next_section     ; -1 = empty cell
    lw   $t0, 0x0($a2)          ; \
    lw   $t1, 0x4($a2)          ;  > the translation
    lw   $t2, 0x8($a2)          ; /
    ...  neg $t0 if mirror
    ctc2 $t0, $5                ; TRX  \
    ctc2 $t1, $6                ; TRY   > GTE translation vector
    ctc2 $t2, $7                ; TRZ  /
    lw   $t0, 0x4($a1)          ; section table
    sll  $v1, $v0, 5            ; index * 32
    lh   $t3, 0xC($t2)          ; face count
    lw   $t1, 0x0($t2)          ; face pointer
```

The third argument is therefore an **array of 16-byte placements**:
`{s32 x, s32 y, s32 z, s32 index}`. And its builder, `func_80012C14`, says
where those four fields come from:

```
    cellX = (D_801D9068 + 0x400) >> 11      ; camera -> cell, step of 2048
    cellZ = (D_801D9070 + 0x400) >> 11
    dir   = (D_801D907C >> 8) & 0xF         ; 16 camera directions
    for i from 0 to 63:
        dx = (s8) D_8005944C[dir*256 + i*2]     ; traversal order table
        dz = (s8) D_8005944D[dir*256 + i*2]
        x = cellX + dx ; z = cellZ + dz
        if x >= 32 or z >= 32 (unsigned) -> index = -1
        if func_80015BC4(x, z, ...) == 0   -> index = -1     ; visibility test
        index = ((s16 *) D_801D82D0)[z*32 + 30 - x]
        D_801D82D8[z] |= 1 << x                              ; 32x32 bitmap of seen cells
        v = (x << 11 - camX_frac, -camY_frac, z << 11 - camZ_frac)
        ApplyMatrix(D_801E91F0, &v, &out)                    ; func_8004315C
        placement = (out.x << 2, out.y << 2, out.z << 2)
```

Sixty-four cells per frame, chosen around the camera in an order that
depends on its direction. `D_801D82D0` points to the table read from
`IDX.HED`.

## The verification

`IDX.HED` is 2048 bytes = **1024 `u16` = exactly 32 × 32**. It holds **258
non-`0xFFFF` entries**, and `MAP.RRM` holds **258 sections**. The cell ↔
section correspondence is a bijection: each of the 258 sections has exactly
one cell, none has zero or two.

Independent test: the 256 nodes of course 0's polyline, converted into
cells (`world >> 11`), land on **79 distinct cells, and all 79 are
occupied**. Zero exceptions. None of the five other indexing orientations
tried gets past 46 out of 79.

Visual test: placing each section at `cell × 2048` and drawing the type-B
quads seen from above, the road ribbon follows the course polyline. That is
the image `map_road_placed.png`.

## The scale

`MAP.RRM`'s local geometry is in **world units × 4**. The builder shifts the
translation left by 2 bits (`sll $v0, $v0, 2`) before writing it, so the
GTE's translation vector — and consequently the vertices added to it —
lives in a space four times finer than the polyline. A cell therefore
measures 8192 geometry units.

The first rendering attempt is what showed it: at scale 1, the sections
overlapped massively and the layout disappeared under the mass.

## A point of convention left open

The code computes the index with `z*32 + 30 - x`. Empirically, what aligns
the polyline with the grid is `z*32 + x`. The two reconcile if the camera's
X axis (`D_801D9068`) is stored in the opposite direction to the
polyline's, with `camera_x = 30 − polyline_x`. That would be consistent
with the other X inversions already met — `negate_rot_row0`, the
`0x800 − angle` of the road edges, the mirror mode's `D_801733A0` global —
but it has not yet been read in a function, so it remains a hypothesis.

## What this corrects in the existing documentation

`TRACK_SPINE_FORMAT.md` states that "MAP.RRM does not contain a placement
transform because there is nothing to place", the course being skinned
along the polyline. The first half is true — the transform is not in
`MAP.RRM` — the second is false: the sections are indeed placed, by
`IDX.HED`.

`MAP_RRM_FORMAT.md` raised the question under "Open items": "whether a
per-section world-space transform exists in a file not yet examined". Yes,
and it was `IDX.HED`.

Finally, the "spatial grid" hypothesis had been discarded in an earlier
session as "ruled out quantitatively". It was right. The elimination rested
on a reading of `MAP.RRM`'s data alone; the grid is not in there. This is
the third case in this project where reading the consumer function gives in
ten minutes what statistical analysis of the file had declared impossible.

---

# The three record types, and the holes

*Direct sequel to the above: the check image left black holes under the
course centreline, and `MAP_RRM_FORMAT.md` carried types A and C as
"candidate banked wall quads, unconfirmed".*

## The one-cell offset

First result, and it corrects the previous rendering. The local vertices
are not centred on the section's origin: X runs from −8192 to 0, Z from 0
to +8192 (medians −4211 and +3827, median width 9140 for a cell of 8192).
A section's origin is therefore the **+X/−Z corner of its cell**, not its
centre.

The prediction is checkable: the geometry has to be shifted by a whole cell
in X for it to line up with the polyline. Measured — coverage of the
centreline goes from **165/256 to 200/256**, and the optimum falls exactly
on `+8192`, the predicted value. This is not a free fit: the offset had
only one admissible value and that is the one.

## What the three types are

| type | n | sections | median ΔY | thin footprint in plan | tpages |
|---|---|---|---|---|---|
| A | 622 | 79 | 475 | 7 % | 8 |
| B | 5 420 | 207 | 116 | 12 % | 12 |
| C | 695 | 23 | 24 | 3 | 3 |

**None of the three is a wall.** The "banked walls" hypothesis carried by
`MAP_RRM_FORMAT.md` for type A is refuted: a vertical wall projects in plan
as a line, and only 7 % of type-A quads have a thin footprint. These are
sloping surfaces — median ΔY 475 against 116 for type B — hence embankments
and banking, not partitions.

Type C is the most localised element of the file: **23 sections out of 258,
three texture pages**, and a median ΔY of 24 that makes it the flattest of
the three. On the map it appears only at the corner exits of the north-west
quarter. A particular course element at that spot — run-off, sand, or the
tunnel surface — remains to be settled by reading `func_80034050`, the
second drawing pass, which takes the same placement array.

## And the holes

They are not what they looked like. After the offset correction, **199 of
the 256 nodes** of course 0's centreline land on a type-B quad. For the
remaining 57, the nearest quad is **9 % of a road half-width** away
(median, measured perpendicular to the node's heading).

That is decisive in a direction that was not the expected one: if the road
surface were not in `MAP.RRM` — if it were skinned along the polyline at
render time, as `TRACK_SPINE_FORMAT.md` supposed — the free corridor around
the centreline would be half a width wide, not nine per cent. **The holes
are point gaps, not a corridor.** The road surface really is in the file.

What remains to be explained is those 57 gaps themselves. The likeliest
lead is the X axis convention left open above: the code indexes with
`30 − x`, a **reflection**, where the empirical result gives `x`, a
translation. The two coincide over a limited range of X and diverge
elsewhere — which would produce exactly an excellent coverage over one half
of the map and a holed one over the other. A global reflection applied to
both data sets at once is unobservable by this test; it will have to be
read in the code that writes `D_801D9068`, not measured.

## A note on orientation, for the check renders

The first check images on this page were drawn with `+Z` towards the top of
the image. That is wrong, and it is a reflection, not a framing choice.

The PSX works with **Y downwards**: X to the right, Y down, Z forwards. A
top view looks along the `+Y` direction; putting screen-right on `+X`,
screen-up equals `Y × X = −Z`, so **`+Z` goes down the screen**. Drawing
`height − z` gives the map seen from below, i.e. its mirror image.

This changes none of the measurements on this page — a global reflection
preserves the bijection, the coverage and the distances — and it does not
settle the axis question left open, which is about X and not Z. But every
check image produced here must come out with `+Z` downwards, otherwise one
is comparing a map with its reflection.

## Correction: type C is a tunnel

The paragraph above described type C as "flat surfaces, a particular course
element to be settled". That was not enough, and it took reading the raw
quads rather than their statistics. Section 156, four records:

```
(-8195,-655,6763)(-6128,-655,6763)(-8195,-655,8930)(-6128,-655,8930)   Y constant -655
(-6128,   0,7857)(-6128,   0,6774)(-8195,   0,7857)(-8195,   0,6774)   Y constant 0
(-6148,-661,8930)(-6148,-661,6763)(-6148,   6,8930)(-6148,   6,6763)   X constant -6148
(-8175,-661,6763)(-8175,-661,8930)(-8175,   6,6763)(-8175,   6,8930)   X constant -8175
```

A floor, a ceiling 655 units higher, two vertical walls. **A box.** The 23
type-C sections form two corridors of contiguous cells — `x = 3..6` over
`z = 13..19`, and `x = 11..13` over `z = 13..16` — and the course
centreline crosses **16 of those 23 cells**. These are the tunnels.

Which also invalidates the sentence "none of the three is a wall" written
above: 10.8 % of type-C quads are vertical, against 6.2 % for B. The
thin-footprint-in-plan test was diluted by the 57.7 % of floors and
ceilings, which are horizontal by construction. A proportion aggregated
over a type that mixes three geometric roles measures nothing; it is by
reading four consecutive records of a single section that the structure
appears.

Type A still has no equivalent reading: 5.8 % vertical, 6.1 % horizontal,
so nearly everything is sloping. Embankments and banking remain the
hypothesis, this time with no refutation to set against it.

## What the one-cell offset means exactly

Two tests seemed to contradict each other: coverage of the centreline
prefers a `+8192` offset in X, while the membership of the tunnel cells in
the centreline prefers no offset at all (16 against 12). They are not about
the same thing, and they agree.

The `z*32 + x` indexing is correct **with no offset**: cell `(3,13)` really
is the one the centreline crosses. And the geometric origin of the section
assigned to that cell has to be placed at `(x+1) * 2048`, since its
vertices span `−8192` to `0` in X. The two statements say the same thing:
the section covers its own cell, its origin sitting on that cell's `+X`
edge.

## The placement is not exact yet — and the reflection is set aside

Outside observation: the layout is right, the placement of the geometry is
not. It is correct, and two measurements make it precise.

The instrument is the tunnel: a tunnel must be centred on the centreline.
Taking the centroids of the 695 type-C quads and their distance to the
polyline, with an effective road half-width of **503 world units**
(`hw*2 >> 4`):

| placement | median distance to the centreline |
|---|---|
| origin at `x_idx * 2048` | 990 |
| origin at `(x_idx + 1) * 2048` | 556 |
| best free fit `(+1536, +512)` | 260 |

So the one-cell offset in X goes in the right direction and cuts the error
by almost half, but a free fit does twice better still, on a value that is
a proper multiple of nothing. **The origin convention is therefore not
derived yet; it is fitted.** That is to be corrected in the previous
section, where I wrote that the offset "had only one admissible value":
that was true at the resolution of a cell, and false at the resolution we
can now measure at.

## The reflection in X is refuted

Same instrument, and this time the verdict is clear-cut:

| indexing | tunnels | all quads |
|---|---|---|
| `world_x = x_idx * 2048` | 990 | 1 384 |
| `world_x = (30 − x_idx) * 2048` | 15 813 | 3 889 |
| `world_x = (31 − x_idx) * 2048` | 17 854 | 4 298 |
| `world_x = (29 − x_idx) * 2048` | 13 775 | 3 601 |

Sixteen times worse. The hypothesis of a reflection in X between the grid
and the polyline, open for three sections of this page, is **false**:
`z*32 + x` really is the correspondence, with no mirror. The code's
`30 − x` is therefore explained by the camera being stored inverted in
`D_801D9068`, the reflection applying twice and cancelling out — which
remains to be read, but is no longer an open alternative for the placement.

## Where to look next

Not in a finer fit. The two candidates left are in the loading code:
`func_800125B4`, which builds the 32-bytes-per-section table at
`D_801D35F0`, and whatever writes `D_801D82D0`. If a per-section origin
exists, it is set there — and a constant offset that is a proper multiple
of nothing looks a great deal more like a field read from a file than like
a grid convention.

## The geometry is stored turned by a half-turn

Three readings and one measurement, in that order.

**`func_800125B4`, the loader, stores no origin.** Its 32-byte entry per
section is `{ptrA(0), ptrB(4), ptrC(8), cntA(0xC), cntB(0xE), cntC(0x10)}`
and nothing else. The offset being sought is therefore not in the file — it
is in the convention. (In passing: `func_800437AC` reads the pointer at
`0x0` and the count at `0xC`, so the drawing pass read above is the **type
A** one, not type B.)

**`func_80015CD4` gives the constant.** This init function writes
`D_801733A0 = 0xF000` — the global that `TRACK_SPINE_FORMAT.md` designated
as "the mirrored-course mechanism". And `0xF000 = 61440 = 30 × 2048`,
exactly the `30 −` of the indexing. The render frame is therefore the
polyline's frame reflected in X about `30 × 2048`.

**The composition cancels out, and it explains the rounding.** Setting
`X_rendu = 0xF000 − X_poly` and `X_poly = 2048q + r`:

```
cellX  = (0xF000 − X_poly + 0x400) >> 11 = 30 − q − [r > 1024]
index  = 30 − cellX                      = q + [r > 1024]
```

that is, `index = round(X_poly / 2048)`. The empirical correspondence
`z*32 + x` is therefore **derived**, not merely observed, and the `+0x400`
is not a detail: it places cell `k` on the interval
`[2048k − 1024, 2048k + 1024]`, centred on `2048k` and not aligned to it.

**The measurement remains.** Since the render frame is reflected, the local
coordinates have to be negated in order to be drawn in the polyline's
frame. Median distance from the tunnel centroids to the centreline, road
half-width 503:

| convention | tunnels | all quads |
|---|---|---|
| `origin + local` (what I was doing) | 990 | 1 384 |
| `origin − local` in X only | 650 | 1 129 |
| `origin − local` in X and Z, origin `+1024` | **300** | **860** |

Negating X **and** Z is a half-turn about Y, not a double reflection: the
winding order of the polygons is preserved, which is consistent with the
fact that the game flips the winding only in mirror mode. And the `+1024`
is exactly the half-step that the rounding above imposes.

The check image with this convention is the first where the beige ribbon
follows the centreline along its whole length, where the green tunnels are
**on** the road and not beside it, and where the district on the right
reads as a city with its viaducts.

The seam test between neighbouring sections, tried before this one, is
worthless and deserves to be noted as such: fewer than 0.4 % of the
vertices coincide from one section to the next in every configuration. The
sections are self-contained and tile their cell whatever the sign, so
internal continuity can settle nothing here.

## The polyline is not the centreline: it is a road edge

Outside observation, on three different stretches: the geometry is always
on the same side of the red line — above it on the two horizontal
straights, to the left on the vertical stretch. Request: flip it to the
other side.

The measurement says otherwise, and it is clear-cut. On the long southern
straight, the **353 type-B vertices near the line all fall within
`[−800, 0]`** in signed distance. Nothing, not one, on the other side. The
nodes' half-width there is 655.

Badly placed geometry would be offset; geometry cut clean on the line is
not. **The stored polyline is one edge of the road, not its centreline.** I
am the one who had been calling it the centreline from the start, and it is
that misreading that gave the impression of an offset.

This is confirmed by drawing the second edge at `2 × half-width` from the
first, on the side where the geometry is: on both straights and in the
tunnels, the road ribbon is **framed** by the two lines. The check render
`map_v4.png` shows it.

Which incidentally resets several figures on this page. All the distances
"to the centreline" measured above were in fact distances to an edge, hence
biased by a half-width — and that bias has to be removed from them before
comparing them with one another.

### A measurement flaw to flag

The table in the previous section (990 / 650 / 300) is wrong. The scoring
function divided the local coordinates by 16 instead of 4, shrinking the
geometry by a factor of four and reducing all the distances by as much. The
rendering, for its part, used the right factor — hence an image that kept
improving while the figures grew too good. Table redone, at the correct
scale, with the signed distance that ought to cancel out:

| convention | signed | absolute |
|---|---|---|
| `origin + local` | +331 | 1901 |
| `origin + local`, +1 cell in X | −52 | 813 |
| half-turn, origin `(+1024, +1024)` | −562 | 1011 |
| **half-turn, origin `(+0, +1024)`** | **−89** | **351** |
| X negated alone, origin `(+0, +1024)` | +59 | 606 |
| Z negated alone, origin `(+0, +1024)` | +273 | 1744 |

The convention retained is therefore the half-turn with the origin shifted
by `+1024` in Z only — and not `+1024` on both axes as written yesterday.

This is the second time on this page that a too-flattering figure came from
a scale factor and not from the subject under study. The safeguard that was
missing is simple: when an image and a metric diverge on the same object,
it is the metric that needs re-reading.

---

# The correct convention

```
world_x = cell_x * 2048  −  localX / 4
world_z = cell_z * 2048  +  localZ / 4
```

**X negated, Z not negated, no offset.** That is all.

The negated X comes from `D_801733A0 = 0xF000 = 30 × 2048` read in
`func_80015CD4`: the render frame is the polyline's reflected in X, and
nothing reflects Z. The derivation already said so; I lost it along the way
by negating Z as well, on the strength of a wrong metric.

## The proof

Interval occupied by the type-B vertices around the long southern straight,
in signed distance to the polyline, for a node half-width of 655:

| convention | n | band | median |
|---|---|---|---|
| `(−X, −Z)`, `+1024` offset in Z | 353 | `[−815 .. −65]` | −428 |
| `(+X, −Z)`, `+1024` offset in Z | 506 | `[−788 .. +514]` | −262 |
| `(+X, +Z)`, no offset | 532 | `[−1587 .. +885]` | +4 |
| **`(−X, +Z)`, no offset** | **352** | **`[−359 .. +392]`** | **+4** |

The right one is recognised by two things together: a zero median **and** a
narrow band. `(+X, +Z)` also has a zero median, but over a band three times
too wide — that is scenery spread symmetrically, not a road. Only
`(−X, +Z)` gives a centred band of 750 units, to be compared with the 1310
of road width: the road surface, centred on its axis.

## What this removes from this page

**The polyline really is the road's centreline**, not an edge. The previous
section concluded the opposite from an interval of `[−800, 0]` — that
interval was the artefact of the sign of Z. To be removed.

**The `+1024` offsets are artefacts** of the same error. There is no offset
at all.

**The half-turn is wrong**: it is a reflection in X alone.

Three successive conclusions invalidated by the same cause, and the cause
was found only by changing the question — no longer "which transform
minimises a distance", but "which interval does the road occupy around its
centreline". The first question has an optimum for any convention whatever;
the second has a narrow answer only for the right one.

The outside report that unblocked this — "the geometry is on the same side,
it needs mirroring" — covered three different stretches and was accurate.
None of my aggregate metrics saw it, because they averaged over scenery
spread on both sides.

## The detached cluster in the north-east

Flagged from outside as suspicious on the final render: a group of type-A
quads set apart, with no road or ground around them. These are eight
sections, and they fall into two clear groups.

| sections | cells | height (world) | distance to a track | depth bias |
|---|---|---|---|---|
| 72, 73, 93 | (19–21, 7–9) | −1221 .. +170 | 1 590 – 3 074 | 50 / 51 |
| 40, 41, 56, 57, 58 | (21–23, 5–6) | −642 .. +1 | 5 975 – 6 716 | 12 |

Each section is built the same way: a band of quads in tpage 23 and, just
above it, a band in tpage 28, the two sharing their Y edge exactly. And the
quads are **vertical** — the example one measures 994 wide by 937 high on a
footprint 285 deep.

Vertical walls 300 to 1 200 units high, textured as two stacked bands, one
to three cells from the track, with a depth bias of 50 where the file's
usual value is −8: this is **background scenery**, drawn far behind
everything else. The cliff and the relief seen across the bay from the
coastal section.

The absence of ground around them is therefore not a gap: between the road
and those walls there is the water, and water has no quads.

Which corrects for a third time the sentence "none of the three types is a
wall". Type A contains some, and large ones. The thin-footprint-in-plan
test missed them because they are as wide as they are tall — thin only in
the third dimension, the one the top view flattens.

---

# The visibility is written in ASCII

`func_80015BC4`, called by the placement builder to decide whether a cell
is drawn, does no frustum computation at all. It reads **one byte** and
decodes it as a hexadecimal digit:

```
    index = cellZ * 34 + 31 − cellX
    c     = table[index]                    ; lbu, one byte
    if 'a' <= c <= 'z' :  zone = c − 0x57   ; 'a' -> 10
    else if '0' <= c <= '9' : zone = c − 0x30
    if zone == camera_zone : visible
```

The `31 − cellX` is the third independent appearance of the reflection in
X.

The tables are at `0x80071D70`, `0x800721B0` and `0x800725F0`, spaced
**1088 bytes = 32 rows of 34** apart: 32 characters per row plus two null
bytes. One per course. And their contents read as they stand:

```
zzzzzzzz888888888877777zzzzzzzzz
zzzzzzzz8888888888777777zzzzzzzz
zzzzzz99888888888877777766zzzzzz
zzzz9999888888888877777766666zzz
zzzz9999998888888887766666666zzz
...
aaaaaabbbbbbccbbbbb555555544444z
aaaaaabbbbccccccbbbbb5554444333z
```

**It is ASCII art.** One character per cell, one hexadecimal digit per
zone, `z` for the rest. `D_80072A30` carries the zone count — 14, 14 and 20
for the three courses — and `D_801E9210` the current course index.

A potentially-visible set written by hand in a text editor, in 1994, and
compiled as such into the executable. There is nothing to decode: the
format *is* its own representation.

### The alignment, settled by the code and not by a fit

`func_80015AAC` does **exactly the same computation** as `func_80015BC4` —
same `z*34 + 31 − cellX` index, same decoding — and returns the zone
instead of comparing it. There is therefore no free offset to look for: the
`IDX.HED` grid is indexed with `z*32 + 30 − cellX`, the zone map with
`z*34 + 31 − cellX`. Same cell, column shifted by exactly one notch.

### The check that could not have come out by chance

With that `+1` column, crossing the three polylines with the three maps —
polyline cells having a zone, and the number of distinct zones:

| | map 0 | map 1 | map 2 |
|---|---|---|---|
| polyline 0 | 45/79 (9) | **79/79 (14)** | 79/79 (15) |
| polyline 1 | 46/80 (9) | **80/80 (14)** | 80/80 (15) |
| polyline 2 | 60/112 (10) | 81/112 (14) | **112/112 (20)** |

`D_80072A30` declares **14, 14 and 20** zones. The number of *distinct
zones actually crossed* is 14 on map 1 and 20 on map 2 — exactly the
declared values, which no step of the reasoning imposed. Two independent
counters land right first time: maps 1 and 2 are established.

### Map 0 is a leftover

The remaining point closes from both ends.

**By measurement.** An exhaustive search — two reflections × nine column
offsets × twenty-five row offsets, i.e. 450 alignments — finds *no*
position at all where map 0 entirely covers the cells of any one of the
three polylines. Zero out of 450, for all three courses.

**By the code.** `D_801E9210` is written six times in the game:

| value | sites | context |
|---|---|---|
| 1 | `0x8001362C`, `0x8003C7DC`, `0x8003D234`, and one branch of `0x80015138` | always with `D_801E90E0 = 0x100`, 256 nodes |
| 2 | `0x80013754`, and the other branch of `0x80015138` | with `D_801E90E0 = 0x170`, 368 nodes |
| 0 | `0x80013900` only | written *before* the node table is selected, never after |

The only site that sets 0 does so at the head of a function that then
chooses, according to `D_801733B8` and `D_8007C210`, one of the three node
tables — without ever rewriting the index. No path therefore establishes 0
as a value *used* at the same time as a world that would correspond to it.

The two readings agree: **the table at `0x80071D70` is a leftover**, an
earlier version of the zone map that stayed in the binary. This is not a
gap in the reverse-engineering, it is a property of the game.

### In passing, the course selection

The same function gives the complete logic:

```
if D_801733B8 == 0        -> g_track_nodes_1, 256 nodes
else if D_8007C210 < 3    -> g_track_nodes_0, 256 nodes
else                      -> g_track_nodes_2, 368 nodes
```

and the associated lap lengths, `D_80173368`: `0xC570` for the 256 nodes,
`0x13570` for the 368. The `D_8007C210 < 3` test is the same one read in
`func_80021BE0` several sessions ago, when nothing yet connected it to
anything else.
