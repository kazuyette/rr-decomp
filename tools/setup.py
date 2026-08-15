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
import re
import os
import shutil
import subprocess
import sys

EXE = "PSX.EXE"
YAML = "psx.exe.yaml"
SHA1 = "31ec5d3616a0fdb456da27a984fc5b92259ff1f6"


# The toolchain image ships a compiler, not a disassembler. splat is a
# Python package, so it can be installed into the running container the
# first time this script needs it; docker/toolchain.Dockerfile installs
# the same set, so a rebuilt image skips this entirely.
#
# The versions are pinned deliberately. spimdisasm decides how the
# listings are written, and a different version can emit a different --
# still correct -- rendering of the same instruction. That would change
# asm/29E8.s under our feet and break matches that have nothing wrong
# with them.
REQS = [
    "splat64==0.50.0",
    "spimdisasm==1.42.4",
    "rabbitizer==1.16.2",
    # splat64 pins these two exactly; anything else and it refuses.
    "intervaltree==3.1.0",
    "tqdm==4.67.1",
    "colorama",
    "pyyaml",
    # Nothing below is used by a PSX project. splat imports its N64
    # segment types eagerly, so pygfxd (display lists) and crunch64
    # (MIO0/Yay0) have to be importable even though nothing here will ever
    # call them. crunch64 is capped at 0.5.3 because later releases stopped
    # shipping a CPython 3.10 wheel and the image is Ubuntu 22.04.
    "n64img",
    "pygfxd==1.0.5",
    "crunch64==0.5.3",
]


def ensure_splat():
    try:
        import splat  # noqa: F401
        return True
    except ImportError:
        pass

    print("splat is not installed in this image; installing it now.")

    # pylibyaml is only a C-loader accelerator for PyYAML and has no wheel
    # for this platform -- pip would try to build it and fail. splat merely
    # imports it, so a no-op module satisfies the import at no cost beyond
    # slower YAML parsing.
    import site
    target = (site.getsitepackages() or [site.getusersitepackages()])[0]
    shim = os.path.join(target, "pylibyaml.py")
    if not os.path.exists(shim):
        with open(shim, "w") as fh:
            fh.write("# no-op stand-in: PyYAML's C loader accelerator.\n"
                     "# splat imports this but does not require it.\n")

    # --break-system-packages only exists from pip 23; the toolchain image
    # is Ubuntu 22.04 and ships an older one, which rejects the flag
    # outright. Try with it, fall back without.
    def pip_install(args):
        base = [sys.executable, "-m", "pip", "install"]
        r = subprocess.run(base + ["--break-system-packages"] + args,
                           capture_output=True, text=True)
        if r.returncode != 0 and "break-system-packages" in r.stderr:
            r = subprocess.run(base + args, capture_output=True, text=True)
        out = (r.stdout + r.stderr).strip()
        if out:
            print(out[-3000:])
        return r.returncode == 0

    if not pip_install(["--no-deps", REQS[0]]):
        return False
    if not pip_install(REQS[1:]):
        return False
    try:
        import splat  # noqa: F401
        return True
    except Exception as exc:
        # Print the real reason. Swallowing it cost a round trip once
        # already: pip reported success, the import still failed, and the
        # message that would have said why was caught and thrown away.
        print(f"splat still will not import: {type(exc).__name__}: {exc}")
        print(f"python {sys.version.split()[0]} at {sys.executable}")
        for p in sys.path:
            print(f"  path {p}")
        return False



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

    if not ensure_splat():
        return 1

    if "--clean" in sys.argv and os.path.isdir("asm"):
        shutil.rmtree("asm")

    # Two passes, because the tree needs two different things out of the
    # same segment.
    #
    # As configured, the 29E8 subsegment is type `c`: splat writes one
    # listing per function under asm/nonmatchings/, which is what the
    # INCLUDE_ASM lines in src/29E8.c point at. It does not write
    # asm/29E8.s -- and that file is the target of the whole build, the
    # reassembled ground truth every conversion is compared against.
    #
    # Flipping the subsegment to `asm` produces exactly that file. So the
    # yaml is patched, splat is run, and the yaml is put back. This was a
    # manual dance documented in the README; it belongs here instead.
    original = open(YAML).read()
    listing_pass = re.sub(r"(\[\s*0x[0-9A-Fa-f]+\s*,\s*)c(\s*,)",
                          r"\1asm\2", original)
    if listing_pass == original:
        print(f"no `c` subsegment found in {YAML}; expected at least one.")
        return 1

    try:
        open(YAML, "w").write(listing_pass)
        r = subprocess.run([sys.executable, "-m", "splat", "split", YAML])
    finally:
        open(YAML, "w").write(original)
    if r.returncode != 0:
        print("\nsplat failed on the listing pass; its output above says why.")
        return r.returncode

    # Second pass, with the yaml as committed: per-function listings, and
    # the linker script and dependency file in their normal form.
    r = subprocess.run([sys.executable, "-m", "splat", "split", YAML])
    if r.returncode != 0:
        print("\nsplat failed; its own output above says why. The header\n"
              "segment used to be the usual culprit -- a non-ASCII byte at\n"
              "0x7E -- which tools/splat_ext/header.py now handles.")
        return r.returncode

    print("\nasm/ regenerated. `make all` next.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
