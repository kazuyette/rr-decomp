"""The translation units the executable is split into.

One list, imported by every tool, so that adding a unit is a one-line
change instead of a hunt through five files for hardcoded "29E8".

The split at 0x8003FA94 is measured: no function at or above that address
calls any function below it, and no lower address has that property. That
is the signature of a linker boundary -- a library object cannot call into
the game that links it.
"""
import os

# (name, generated C unit, segment path for INCLUDE_ASM, target object)
UNITS = [
    ("29E8", "src/29E8.c", "asm/nonmatchings/29E8", "build/asm/29E8.o"),
    ("psyq", "src/psyq.c", "asm/nonmatchings/psyq", "build/asm/psyq.o"),
]

TARGETS = [u[3] for u in UNITS]
GENERATED = [u[1] for u in UNITS]
SEGMENTS = [u[2] for u in UNITS]


def unit_for(func):
    """Which unit owns this function, by where its listing lives.

    Falls back to the first unit so that a caller never gets None; a
    function with no listing at all is one that is currently written in C,
    and the caller is about to ask for a listing to be regenerated.
    """
    for _, gen, seg, _obj in UNITS:
        if os.path.exists(os.path.join(seg, func + ".s")):
            return gen, seg
    return UNITS[0][1], UNITS[0][2]
