# MAP.RRM format

Track-data file from the RIDGERACER PS1 disc (271 548 bytes for the one course RR1 ships). Reverse-engineered and implemented in the companion project [rr-pc-port](https://github.com/kazuyette/rr-pc-port) (`tools/mapparse/map_rrm.c`/`.h`, `mapparse_main.c`); this page mirrors that writeup here since asset-format documentation is tracked as a repo goal. As with every asset format on this page: the file itself is never committed to either repo — you need your own legally-owned copy of the game to reproduce any of this.

## Confirmed structural layout

Verified byte-exact by replaying the original PS1 loader's own arithmetic (`func_800125B4`, see `asm/29E8.s`) against the real file: header + directory + `sum(counts) * 40` lands on exactly 271 548 bytes, with zero slack.

- **Header (4 bytes):** `uint16 LE` section count `N`, followed by 2 unused/padding bytes.
- **Section directory (`N * 8` bytes, immediately after the header):** `N` entries, each four `uint16 LE` counts `{count_a, count_b, count_c, count_d}`. `count_d` was 0 in all 258 observed entries — its purpose is unconfirmed (unused 4th record type for this course, or something else).
- **Bulk data (the remainder of the file, one linear stream):** for each of the `N` sections in directory order, `count_a` records of type A, then `count_b` of type B, then `count_c` of type C — chunked per section per type, not three separate global arrays. Every record is 40 bytes.

Load path traced from boot: the rodata string `"\MAP.RRM;1"` (`D_800106F0`) -> a 10-entry filename pointer table (`D_800747BC`..`D_800747E0`, MAP.RRM is entry 0) -> `func_80032A54` (loads all 8 CD-directory-resident data files at boot) -> `func_80032948` (CD-read-a-file-into-buffer-by-directory-entry) -> `func_800125B4` (the header/directory parser itself, which builds a 32-byte-per-section runtime table at `D_801D35F0`: 3 running byte offsets + the 3 raw counts per section).

## The 40-byte record

```c
typedef struct {
    int16_t v0[3];     /* bytes 0-5:   corner/vector 0 */
    int16_t v1[3];      /* bytes 6-11:  corner/vector 1 (often shares v0[1], height, on type-B records) */
    int16_t v2[3];     /* bytes 12-17: corner/vector 2 */
    int16_t v3[3];     /* bytes 18-23: corner/vector 3 (often shares v2[1] the same way) */
    int16_t unk_18;    /* bytes 24-25: texture u0,v0 (one byte each) */
    uint16_t heading;  /* bytes 26-27: CLUT id (not a heading -- see note below) */
    int16_t unk_1c;    /* bytes 28-29: texture u1,v1 */
    int16_t unk_1e;    /* bytes 30-31: TPAGE id */
    int16_t unk_20;    /* bytes 32-33: texture u2,v2 */
    uint16_t group_id; /* bytes 34-35: ordering-table depth bias (sort layering, e.g. bridges above roads) */
    int16_t unk_24;    /* bytes 36-37: texture u3,v3 */
    uint16_t flags;    /* bytes 38-39: still open -- candidate primitive-type marker */
} MapRrmRecord;
```

Bytes 0-23 (the four `int16[3]` vectors) decode cleanly in a +/-32000 range consistent with local-space coordinates, not the huge/noisy values you'd get reading the same bytes as `int32` -- strong signal the true field width is 16-bit. For most type-B records (the majority, ~5420 of 6737 total), `v0[1] == v1[1]` and `v2[1] == v3[1]`: the near-left/near-right, far-left/far-right corner-sharing signature of a road-surface quad. This pairing breaks at apparent junctions/branches and doesn't hold for type-A records at all (candidate: banked wall/collision quads, unconfirmed).

Bytes 24-39 were decoded by tracing the track renderer (`func_800163E4` -> its quad emitter `func_8003486C`), which copies these 16 bytes verbatim into `POLY_FT4` GPU packets -- so the field names above are legacy (kept for source stability in the parser) but the real mapping is: u/v texture coordinate pairs at bytes 24-25, 28-29, 32-33, 36-37; CLUT id at 26-27; TPAGE id at 30-31; ordering-table depth bias at 34-35. Validated against the real file: every TPAGE decodes to a valid 4bpp VRAM page where the TEX banks load, every CLUT id lands in the y=480..509 palette rows, and the UV pairs form clean axis-aligned rects (see `tools/texparse/psx_vram.{h,c}` in rr-pc-port for the VRAM recreation that renders them). Bytes 38-39 (`flags`) remain open: near-constant within a run (0x0202 typical for interior records), sometimes a different constant (0x0303) at a run's first record -- candidate record-type/continuation marker, not yet cross-checked against a consumer function.

**Not found:** any per-section coordinate transform (translation/rotation). Plotting raw `v0` corners top-down does not produce a closed track outline -- each section's vectors appear to be in a local/section-relative frame. The renderer does apply a real GTE hardware rotation matrix at render time (`rtps`/`rtpt`, traced instruction-by-instruction), so rotation is real and computed dynamically, just not stored in the file itself (or not yet located, if it is).

## Verification & testing strategy

### What's already high-confidence, and why

The structural layout (header/directory/record boundaries) is validated the strongest way available for a reverse-engineered format: not by guessing and eyeballing plausibility, but by **replaying the original console's own arithmetic against the real file** (the loader's running-offset accumulation lands on the exact file size, zero slack across all 258 directory entries) and by **tracing which PS1 function consumes each byte** (the bytes 24-39 mapping is confirmed because the renderer's own quad-emitter code copies them into GPU packets we can decode independently). This is closer to a proof than a hypothesis for those two layers.

### Parser correctness/robustness (currently a gap)

`map_rrm.c` has no unit test suite -- `mapparse_main.c` is a CLI inspection tool (prints a summary, optionally dumps PPM/CSV), not a test harness, and there's no CI job exercising the parser. Recommended additions, cheapest/highest-value first:

- **Golden-file regression test:** run the parser against the real MAP.RRM (kept local, never committed) and assert `bytes_consumed == file_size`, `section_count == 258`, and the known-good record/section counts. Cheap, catches any accidental regression in the accumulation arithmetic immediately -- this is the test that would have caught a bug the loader-replay work above was designed to avoid in the first place.
- **Malformed-input unit tests** (no real file needed, synthetic buffers): truncated header (< 4 bytes), truncated directory (header claims N sections but buffer ends mid-directory), truncated bulk data (directory's counts imply more bytes than the buffer holds), `section_count == 0`, a section with all-zero counts, and a directory entry with `count_d != 0` (currently unseen in the real file -- exercises the code path even though it's never hit in practice, and documents the assumption that hitting it wouldn't corrupt the parse).
- **Round-trip/fuzz test:** for a buffer that parses successfully, re-serialize it and confirm byte-identity with the input; then fuzz small mutations (bit flips in the header/directory) and assert the parser either parses a well-defined (if garbage) result or returns one of the defined `MAP_RRM_ERR_*` codes -- never a crash or out-of-bounds read. Given the manual `malloc`/index arithmetic in `map_rrm_parse`, this is the check most likely to catch a real bug (e.g. integer overflow in `total_records * MAP_RRM_RECORD_SIZE` for a maliciously large `section_count`).
- Since `rr-pc-port` already uses CMake/CTest for its other tools, wiring these in as a `ctest` target (using a tiny synthetic-buffer fixture for the malformed-input cases, and an optional/skippable test that only runs when a real MAP.RRM is present locally for the golden-file case) is the natural fit rather than a new framework.

### Methodology for the still-unconfirmed fields

`unk_18`/`unk_1c`/`unk_20` (three of the four UV coordinate bytes) and `flags` have no unit-testable ground truth the way the structural layout does -- "correct" here means "matches what the original game does with these bytes," which can only be established by the same two techniques already used for everything else in this file, not by writing an assertion against a spec:

1. **Trace the consumer, not the data.** Every CONFIRMED field in this format was nailed down by finding the PS1 function that reads it and watching what it does with the value (the loader's arithmetic for the layout, the renderer's `POLY_FT4` packet construction for bytes 24-39). The `flags` field's next step is the same: find what (if anything) branches on it inside `func_8003486C` or a neighboring function, rather than continuing to guess from statistics alone.
2. **Cross-check statistical hypotheses against structural boundaries.** The "near-constant within a run, changes at run start" pattern for `flags` should be checked against the section/type/run boundaries the parser already tags (`section_index`, `type`, `index_in_run` on every `MapRrmTaggedRecord`) -- if a hypothesis is a real field, its transitions should correlate with those boundaries (or with the group_id/CLUT stepping) more often than chance. `mapparse --csv` already emits everything needed for this; the missing piece is a small analysis pass (even a spreadsheet pivot) that computes the correlation rather than eyeballing samples.
3. **Falsify before confirming.** For each hypothesis (BAMS heading angle, bank-angle/curvature category, record-type marker), state the concrete prediction it makes and look for the counterexample first -- e.g. if `heading`-as-CLUT-id is right, every value must land in the y=480..509 palette rows with no exceptions (this was checked); if `flags` were a simple record-type marker, its value set should be small and closed, so enumerate the distinct values across the whole file and treat more than a handful of distinct values as evidence against that specific hypothesis.
4. Keep the confidence labels (`CONFIRMED` vs. hypothesis, with the specific evidence cited) in the header comment as each field resolves -- the format doc and the code comments are the same source of truth here, so a future round changing one without the other is the main regression risk for a reverse-engineered spec like this one.

## Open items

- `count_d`'s purpose (always 0 in the one shipped course -- untestable without a second course to compare against, which RR1 doesn't have).
- Bytes 38-39 (`flags`) exact semantics.
- Whether a per-section world-space transform exists in a file not yet examined (none of the files documented on this page other than MAP.RRM were checked for this), or whether it's computed at runtime from state not yet traced.
- `IDX.HED`, `OBJ.RRO`, `TEX*.TMS` remain undocumented here (see `tools/mapparse/idx_hed.{h,c}`, `obj_rro.{h,c}`, and `tools/texparse/` in rr-pc-port for the in-progress work on those).
