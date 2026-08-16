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

asm/ is deleted and rebuilt on every run. splat does not overwrite parts
of what it writes, so anything left from a previous state could otherwise
survive into a run meant to replace it -- which is how a symbol rename
used to appear to do nothing.
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
    # splat64 0.50.0 exige cette version exacte ; la laisser libre fait
    # afficher a pip un conflit de dependances a chaque installation, qui
    # n'empeche rien mais qu'on finit par ne plus lire.
    "pyyaml==6.0.3",
    # Nothing below is used by a PSX project. splat imports its N64
    # segment types eagerly, so pygfxd (display lists) and crunch64
    # (MIO0/Yay0) have to be importable even though nothing here will ever
    # call them. crunch64 is capped at 0.5.3 because later releases stopped
    # shipping a CPython 3.10 wheel and the image is Ubuntu 22.04.
    "n64img",
    "pygfxd==1.0.5",
    "crunch64==0.5.3",
]


SPLAT_PIN = "0.50.0"


def installed_splat():
    """The installed splat64 version, or None."""
    try:
        from importlib.metadata import version
        return version("splat64")
    except Exception:
        return None


def ensure_splat():
    have = installed_splat()
    if have == SPLAT_PIN:
        return True
    if have is not None:
        # A different version is not a detail. spimdisasm decides how the
        # listings are rendered, and splat decides where the boundaries
        # fall; either can emit a different -- still correct -- listing of
        # the same instructions, which changes asm/ under our feet and
        # breaks matches that have nothing wrong with them. So we replace
        # it rather than proceed and blame the result on the game.
        print(f"splat64 {have} is installed; this project pins {SPLAT_PIN}.")
        print("Installing the pinned set -- a different version renders the")
        print("listings differently, which would break matches silently.")
    else:
        print("splat is not installed in this image; installing it now.")

    # Ou peut-on ecrire ? Le conteneur de la chaine d'outils tourne en root et
    # ecrit donc dans le site systeme ; une machine ordinaire, non. Supposer
    # l'un des deux cas est la faute la plus banale de ce genre de script, et
    # elle ne se voit pas chez celui qui l'ecrit.
    import site
    en_root = hasattr(os, "geteuid") and os.geteuid() == 0
    candidats = []
    try:
        perso = site.getusersitepackages()
        if isinstance(perso, str):
            candidats.append(perso)
    except Exception:
        pass
    systeme = list(site.getsitepackages() or [])
    candidats = (systeme + candidats) if en_root else (candidats + systeme)

    def ecrivable(dossier):
        try:
            os.makedirs(dossier, exist_ok=True)
            essai = os.path.join(dossier, ".essai-ecriture")
            open(essai, "w").close()
            os.remove(essai)
            return True
        except OSError:
            return False

    target = next((c for c in candidats if ecrivable(c)), None)
    if target is None:
        print("aucun dossier de paquets Python n'est accessible en ecriture :")
        for c in candidats:
            print("   " + c)
        print("installe splat toi-meme, puis relance :")
        print("   python3 -m pip install --user " + " ".join(REQS))
        return False

    # pylibyaml is only a C-loader accelerator for PyYAML and has no wheel
    # for this platform -- pip would try to build it and fail. splat merely
    # imports it, so a no-op module satisfies the import at no cost beyond
    # slower YAML parsing.
    shim = os.path.join(target, "pylibyaml.py")
    if not os.path.exists(shim):
        with open(shim, "w") as fh:
            fh.write("# no-op stand-in: PyYAML's C loader accelerator.\n"
                     "# splat imports this but does not require it.\n")

    # --break-system-packages only exists from pip 23; the toolchain image
    # is Ubuntu 22.04 and ships an older one, which rejects the flag
    # outright. Try with it, fall back without. --user quand on n'est pas
    # root : le site personnel precede le site systeme dans sys.path, donc la
    # version epinglee masque celle de la distribution sans y toucher.
    def pip_install(args):
        base = [sys.executable, "-m", "pip", "install"]
        if not en_root:
            base.append("--user")
        r = subprocess.run(base + ["--break-system-packages"] + args,
                           capture_output=True, text=True)
        if r.returncode != 0 and "break-system-packages" in r.stderr:
            r = subprocess.run(base + args, capture_output=True, text=True)
        out = (r.stdout + r.stderr).strip()
        if out:
            print(out[-3000:])
        return r.returncode == 0

    if not pip_install(["--no-deps", "--force-reinstall", REQS[0]]):
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

    # Always start from nothing. splat will not overwrite some of what it
    # writes, so an asm/ left over from an earlier state can survive into
    # a run that should have replaced it -- and a run interrupted partway
    # leaves a truncated listing that looks perfectly valid to the
    # assembler. asm/29E8.s is the target every conversion is measured
    # against; it must be a function of PSX.EXE alone, never of whatever
    # happened to be on disk. Regenerating it costs seconds.
    if os.path.isdir("asm"):
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
