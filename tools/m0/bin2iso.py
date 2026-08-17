#!/usr/bin/env python3
"""Extracts the data track of a BIN/CUE image into 2048-byte sectors.

The native bench serves the disc's sectors as they are and so expects an "ISO"
image: 2048 useful bytes per sector, nothing else. A BIN image makes 2352 of
them, because it keeps what the drive really reads -- twelve bytes of
synchronisation, four of header, then the data, then the error correction.
This script throws away the envelope and keeps the letter.

    python3 tools/m0/bin2iso.py RidgeRacer.bin data.iso

It stops at the first audio track: those have neither header nor sector
structure, and including them would produce noise where the game expects its
file system. If your image is already in 2048, it says so and does nothing.
"""
import sys

SYNC = b"\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x00"


def convert(source, destination):
    try:
        raw = open(source, "rb").read()
    except FileNotFoundError:
        sys.exit("not found: %s\n"
                 "  This name is only an example -- give the path to YOUR image.\n"
                 "  On a disc cut up track by track, it is track 01: the data\n"
                 "  track is always the first one, the ones that follow are the\n"
                 "  music." % source)
    if len(raw) % 2352 != 0:
        if len(raw) % 2048 == 0:
            sys.exit("%s is already in 2048-byte sectors -- nothing to do"
                     % source)
        sys.exit("%s does not come out to a whole number of either 2352 or 2048 bytes"
                 % source)

    out = open(destination, "wb")
    kept = 0
    for i in range(0, len(raw), 2352):
        sector = raw[i:i + 2352]
        if sector[:12] != SYNC:
            # No more synchronisation pattern: we have entered the audio.
            break
        mode = sector[15]
        if mode == 1:                 # MODE1: data at byte 16
            out.write(sector[16:16 + 2048])
        elif mode == 2:               # MODE2/FORM1: eight bytes of subheader
            out.write(sector[24:24 + 2048])
        else:
            break
        kept += 1
    out.close()
    print("%s: %d sectors, %d bytes" % (destination, kept, kept * 2048))


if __name__ == "__main__":
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    convert(sys.argv[1], sys.argv[2])
