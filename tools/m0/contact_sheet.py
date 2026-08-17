#!/usr/bin/env python3
"""Assembles the bench's frames into a contact sheet.

Watching a run frame by frame is expensive and makes you miss the transitions,
which are exactly where the defects lodge. A sheet shows thirty frames at once
and brings out what an isolated frame does not say: a screen that no longer
changes, a colour that drifts, a step backwards nobody expected.

    python3 tools/m0/contact_sheet.py images/*.ppm -o sheet.png -c 6

No dependencies: the PPMs are read as they are and the PNG is written by hand.
"""
import argparse
import struct
import sys
import zlib


def read_ppm(path):
    d = open(path, "rb").read()
    p = d.split(b"\n", 3)
    if p[0] != b"P6":
        raise ValueError(path + " is not a binary PPM")
    l, h = (int(x) for x in p[1].split())
    return l, h, p[3]


def write_png(path, width, height, pixels):
    raw = b"".join(b"\x00" + pixels[y * width * 3:(y + 1) * width * 3]
                    for y in range(height))

    def chunk(kind, payload):
        body = kind + payload
        return (struct.pack(">I", len(payload)) + body
                + struct.pack(">I", zlib.crc32(body)))

    open(path, "wb").write(
        b"\x89PNG\r\n\x1a\n"
        + chunk(b"IHDR", struct.pack(">IIBBBBB", width, height, 8, 2, 0, 0, 0))
        + chunk(b"IDAT", zlib.compress(raw, 6))
        + chunk(b"IEND", b""))


def main():
    p = argparse.ArgumentParser()
    p.add_argument("images", nargs="+")
    p.add_argument("-o", "--out", default="sheet.png")
    p.add_argument("-c", "--columns", type=int, default=6)
    p.add_argument("-r", "--reduction", type=int, default=2,
                   help="size divisor (2 by default)")
    a = p.parse_args()

    thumbs = []
    for path in a.images:
        try:
            l, h, px = read_ppm(path)
        except Exception as e:
            sys.stderr.write("%s: %s\n" % (path, e))
            continue
        tw, th = l // a.reduction, h // a.reduction
        v = bytearray(tw * th * 3)
        for y in range(th):
            src = (y * a.reduction) * l * 3
            for x in range(tw):
                i = src + (x * a.reduction) * 3
                j = (y * tw + x) * 3
                v[j:j + 3] = px[i:i + 3]
        thumbs.append((tw, th, bytes(v)))

    if not thumbs:
        sys.exit("no readable image")

    tw, th = thumbs[0][0], thumbs[0][1]
    cols = min(a.columns, len(thumbs))
    rows = (len(thumbs) + cols - 1) // cols
    L, H = cols * tw, rows * th
    sheet = bytearray(L * H * 3)
    for n, (l, h, px) in enumerate(thumbs):
        cx, cy = (n % cols) * tw, (n // cols) * th
        for y in range(min(h, th)):
            d = ((cy + y) * L + cx) * 3
            s = y * l * 3
            sheet[d:d + min(l, tw) * 3] = px[s:s + min(l, tw) * 3]
    write_png(a.out, L, H, bytes(sheet))
    print("%s: %d frames, %d by %d" % (a.out, len(thumbs), L, H))


if __name__ == "__main__":
    main()
