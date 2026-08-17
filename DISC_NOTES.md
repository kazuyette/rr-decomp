# Notes on the source disc (Japan)

Source: BIN/CUE image, 13 tracks (1 MODE2/2352 data track + 12 CDDA audio
tracks - redbook soundtrack).

## ISO9660 volume (track 1)

- System id: PLAYSTATION
- Volume id: RIDGERACER
- Publisher: NAMCO LIMITED
- File dates: 6-10 Nov. 1994 (JP release 3 Dec. 1994 - build very close to
  the master)
- No SYSTEM.CNF on the disc -> implicit boot on PSX.EXE (behaviour of the
  very first PS1 titles)

## Root files

| File | Size | Likely role |
|---|---|---|
| PSX.EXE | 425 984 bytes | Main executable |
| IDX.HED | 2 048 bytes | Index table (in-house format, undocumented) |
| MAP.RRM | 271 548 bytes | Track data (road geometry + UV/texture per quad) - **documented format**, see [MAP_RRM_FORMAT.md](MAP_RRM_FORMAT.md) |
| OBJ.RRO | 445 348 bytes | 3D models of the objects |
| RR.VH | 32 288 bytes | Sound headers (VAB header, standard Sony format) |
| RR.VB | 491 056 bytes | Sound data (VAB body) |
| TEX0-TEX4.TMS | 699 908 / 197 128 / 140 704 / 109 948 / 14 996 bytes | Texture banks (probably an in-house format, not a standard .TIM) |

## PSX.EXE header

- Magic: PS-X EXE
- Region: "Sony Computer Entertainment Inc. for Japan area"
- Entry point (pc0): 0x8003FA9C
- gp0: 0xEF7E023F
- .text: address 0x80010000, size 0x67800
- No data/bss section declared in the header (the crt0 takes care of it at
  runtime, see GHIDRA_PROGRESS.md)

## Next steps

- Document the IDX.HED format (probably a sector index pointing to assets
  streamed from the CD)
- Convert RR.VH/RR.VB (standard Sony VAB, tools exist in the PS1 homebrew
  ecosystem)
- Reverse the TEXx.TMS format in order to view the textures
- MAP.RRM: format documented (see [MAP_RRM_FORMAT.md](MAP_RRM_FORMAT.md)) -
  still open: the exact semantics of the `flags` field (bytes 38-39 of each
  record) and whether or not a per-section transform (translation/rotation)
  stored in another file exists
