#!/usr/bin/env python3
"""Converts the bench's frames to PNG, with no dependencies.

The bench writes PPMs because it is the format one can produce in C without a
library -- one header line and the bytes. Nobody wants to look at PPM, hence
this converter: zlib and struct are enough to write a valid PNG, and the
standard library provides both of them.

    python3 tools/m0/ppm2png.py build/m0/*.ppm
"""
import struct
import sys
import zlib


def convert(source, destination):
    data = open(source, "rb").read()
    parts = data.split(b"\n", 3)
    if parts[0] != b"P6":
        raise ValueError(source + " is not a binary PPM")
    width, height = (int(x) for x in parts[1].split())
    pixels = parts[3]
    # PNG wants a filter byte at the head of each row; zero means "no filter",
    # which compresses a little less well and avoids writing a predictor for
    # nothing.
    raw = b"".join(b"\x00" + pixels[y * width * 3:(y + 1) * width * 3]
                    for y in range(height))

    def chunk(kind, payload):
        body = kind + payload
        return (struct.pack(">I", len(payload)) + body
                + struct.pack(">I", zlib.crc32(body)))

    png = (b"\x89PNG\r\n\x1a\n"
           + chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0))
           + chunk(b"IDAT", zlib.compress(raw, 6))
           + chunk(b"IEND", b""))
    open(destination, "wb").write(png)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    for path in sys.argv[1:]:
        out = path[:-4] + ".png" if path.endswith(".ppm") else path + ".png"
        convert(path, out)
        print(out)
