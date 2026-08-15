"""The translation units the executable is split into.

One list, imported by every tool, so that adding a unit is a one-line
change instead of a hunt through five files for a hardcoded "29E8".

The split at 0x8003FA94 is measured, not assumed: no function at or above
that address calls any function below it, and no lower address has that
property. That is the signature of a linker boundary -- a library object
cannot call into the game that links it.
"""
import os
import re

# (name, generated C unit, segment path for INCLUDE_ASM, target object)
UNITS = [
    ("29E8", "src/29E8.c", "asm/nonmatchings/29E8", "build/asm/29E8.o"),
    ("psyq", "src/psyq.c", "asm/nonmatchings/psyq", "build/asm/psyq.o"),
]

TARGETS = [u[3] for u in UNITS]
GENERATED = [u[1] for u in UNITS]
SEGMENTS = [u[2] for u in UNITS]

_OWNER = None


def _owners():
    """{function: (generated unit, segment)}, read from the full listings.

    asm/<unit>.s is the whole unit disassembled, so it names every function
    the unit contains regardless of whether that function is currently
    written in C. That is what makes it the right source here.

    Deciding ownership by "which asm/nonmatchings/<unit>/ holds a listing"
    does not work, and broke the build the first time it was tried: a
    function being restored to INCLUDE_ASM has no per-function listing yet
    -- that is exactly why it is being restored -- so every one of them
    fell through to the first unit. Library functions ended up referenced
    from src/29E8.c while splat had written their listings under psyq/.
    """
    global _OWNER
    if _OWNER is not None:
        return _OWNER
    _OWNER = {}
    for name, gen, seg, _obj in UNITS:
        path = os.path.join("asm", name + ".s")
        if not os.path.exists(path):
            continue
        with open(path) as fh:
            for func in re.findall(r"^glabel (\w+)", fh.read(), re.M):
                _OWNER[func] = (gen, seg)
    return _OWNER


def unit_for(func):
    """Which unit owns this function."""
    owner = _owners().get(func)
    if owner:
        return owner
    # No full listing on disk yet (asm/ not generated). Fall back to
    # wherever a per-function listing happens to live, and to the first
    # unit only as a last resort.
    for _name, gen, seg, _obj in UNITS:
        if os.path.exists(os.path.join(seg, func + ".s")):
            return gen, seg
    return UNITS[0][1], UNITS[0][2]
