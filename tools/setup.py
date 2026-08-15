#!/usr/bin/env python3
"""Regenerate asm/ from your own copy of PSX.EXE.

asm/ is not in this repository and should not be: a disassembly is the
game's code in another notation, and committing it would put copyrighted
material here just as committing the executable would. What is tracked is
everything needed to produce it -- psx.exe.yaml, symbol_addrs.txt,
reloc_addrs.txt -- plus the recovered C.

Run this once after cloning, with PSX.EXE (SLPS-00001, sha1
31ec5d3616a0fdb456da27a984fc5b92259ff1f6) in the repository root, and
again whenever psx.exe.yaml or symbol_addrs.txt changes.

splat never overwrites an existing file, so a symbol rename only takes
effect after the listings mentioning it are deleted; --clean does that.
"""
import hashlib
import os
import shutil
import subprocess
import sys

EXE = "PSX.EXE"
SHA1 = "31ec5d3616a0fdb456da27a984fc5b92259ff1f6"


def main():
    if not os.path.exists(EXE):
        print(f"{EXE} not found in the repository root.\n"
              f"Supply your own copy, extracted from the disc you own.")
        return 1
    digest = hashlib.sha1(open(EXE, "rb").read()).hexdigest()
    if digest != SHA1:
        print(f"{EXE} has sha1 {digest}, expected {SHA1}.\n"
              f"This project targets the Japanese release, SLPS-00001.")
        return 1

    if "--clean" in sys.argv and os.path.isdir("asm"):
        shutil.rmtree("asm")

    r = subprocess.run([sys.executable, "-m", "splat", "split", "psx.exe.yaml"])
    if r.returncode != 0:
        print("\nsplat failed. If it stopped on a UnicodeDecodeError inside "
              "the header segment, set that segment's type to `bin` in "
              "psx.exe.yaml, re-run, then set it back to `header`.")
        return r.returncode
    print("\nasm/ regenerated. `make all` next.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
