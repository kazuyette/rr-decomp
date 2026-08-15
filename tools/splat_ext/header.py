"""A PSX header segment that survives a non-ASCII byte in the licence string.

splat's built-in PSX header segment emits the region from 0x4C to the end
of the header as a single `.ascii` directive. This executable has a byte
at 0x7E that is not ASCII, so the decode raises and the split dies before
producing anything -- the failure that made `make setup` a two-step manual
dance (set the segment to `bin`, run, set it back).

Here that one field falls back to a `.byte` list, which assembles to the
same bytes and cannot fail to decode. Every other field is left to the
upstream implementation.

Reached via `allow_segment_overrides: True` in psx.exe.yaml, which makes
splat look in extensions_path before its own segment types. The class name
is dictated by splat: <PLATFORM>Seg<Type>.
"""
from splat.segtypes.psx.header import PsxSegHeader


class PSXSegHeader(PsxSegHeader):
    @staticmethod
    def get_line(typ, data, comment):
        if typ == "ascii":
            try:
                data.decode("ASCII")
            except UnicodeDecodeError:
                body = ", ".join(f"0x{b:02X}" for b in data)
                return f".byte {body} /* {comment} */"
        return PsxSegHeader.get_line(typ, data, comment)
