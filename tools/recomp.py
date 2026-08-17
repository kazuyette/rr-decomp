#!/usr/bin/env python3
"""MIPS R3000 to C translator, for the test bench of the native port.

Why this one exists
-------------------
Nine tenths of the game code is still assembly. A native milestone that boots
therefore cannot be made of our C functions plus stubs: it would be missing the
race loop, the physics and the renderer. Static recompilation turns the problem
around -- every instruction is translated mechanically, the game runs whole, and
each decompiled function then replaces its translated twin.

This file is step zero of that work: proving that the translation is faithful.
Not "it seems to work" -- faithful down to the bit, verified by running the real
MIPS code under qemu and comparing the outputs.

The form chosen
---------------
A MIPS function becomes a C function taking the argument registers and
returning $v0, with memory seen as a byte array addressed through accessors.
The registers become u32 local variables; the branches become `goto`s to
labels.

The point that decides everything: the **delay slot**. On MIPS, the instruction
that follows a branch executes before it, whether the branch is taken or not. A
naive translation that emits it after the `goto` produces code that looks right
and is wrong everywhere the slot modifies the tested register. So we emit it
BEFORE, systematically, and keep a copy of the condition evaluated before the
slot runs.

What this translator does not do
--------------------------------
The COP2 (the GTE) is not translated: its forty opcodes call for a separate
implementation, validated against the hardware documentation and not against
qemu, which does not know this coprocessor. Functions that contain any of them
are refused explicitly rather than translated halfway.
"""
import re
import struct
import sys

REG = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
       "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
       "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
       "t8", "t9", "k0", "k1", "gp", "sp", "s8", "ra"]


def r(n):
    """$zero is the constant 0; $sp is a global.

    The stack pointer cannot be a local variable: a callee must see its
    caller's one, otherwise the frames overlap and the arguments passed on the
    stack -- those beyond the fourth -- are read out of nowhere. Making it a
    global makes both correct with no special-case code, because that is
    exactly what it is on the machine."""
    if n == 0:
        return "0"
    if n == 29:
        return "g_sp"
    return "r_" + REG[n]


class Unsupported(Exception):
    pass


SYMS = {}   # address -> name, filled in by load_symbols()


def load_symbols(*asm_paths):
    """All the functions of the disassembled units, by address."""
    for path in asm_paths:
        txt = open(path, encoding="utf-8", errors="replace").read()
        for f in re.split(r"^glabel ", txt, flags=re.M)[1:]:
            nm = f.split("\n", 1)[0].strip()
            m = re.search(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ", f)
            if m:
                SYMS[int(m.group(1), 16)] = nm
    return SYMS


def decode(w, pc):
    """Returns (C text, branch target or None, has_a_slot)."""
    txt, tgt, dly = _decode(w, pc)
    # $zero is wired to zero: a write into it is discarded by the hardware.
    # The retail contains some -- nops encoded differently, and results that
    # are computed then abandoned. Translated as they stand, they give an
    # assignment to a constant, which C refuses.
    if txt.startswith("0 = "):
        return "", None, False
    return txt, tgt, dly


def _decode(w, pc):
    op = w >> 26
    rs, rt, rd = (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
    sa = (w >> 6) & 31
    fn = w & 63
    imm = w & 0xFFFF
    simm = imm - 0x10000 if imm & 0x8000 else imm
    tgt = pc + 4 + simm * 4

    if w == 0:
        return "", None, False

    if op == 0:
        if fn == 0x00: return f"{r(rd)} = {r(rt)} << {sa};", None, False
        if fn == 0x02: return f"{r(rd)} = {r(rt)} >> {sa};", None, False
        if fn == 0x03: return f"{r(rd)} = (u32)((s32){r(rt)} >> {sa});", None, False
        if fn == 0x04: return f"{r(rd)} = {r(rt)} << ({r(rs)} & 31);", None, False
        if fn == 0x06: return f"{r(rd)} = {r(rt)} >> ({r(rs)} & 31);", None, False
        if fn == 0x07: return f"{r(rd)} = (u32)((s32){r(rt)} >> ({r(rs)} & 31));", None, False
        # jr $ra is a return; jr on any other register is an indirect jump --
        # a branch table, or a BIOS trampoline. Confusing the two compiles and
        # runs, and is wrong in silence: 54 jumps of this kind were being
        # translated into returns before anyone counted them.
        if fn == 0x08:
            return ("JR" if rs == 31 else f"JRIND {r(rs)}"), None, True
        if fn == 0x0C:
            return "r_v0 = psx_syscall(r_a0, r_a1, r_a2, r_a3);", None, False
        if fn == 0x09:
            return f"JALR {r(rs)} {r(rd)}", None, True
        if fn == 0x10: return f"{r(rd)} = r_hi;", None, False
        if fn == 0x11: return f"r_hi = {r(rs)};", None, False
        if fn == 0x12: return f"{r(rd)} = r_lo;", None, False
        if fn == 0x13: return f"r_lo = {r(rs)};", None, False
        if fn == 0x18: return (f"{{ s64 t = (s64)(s32){r(rs)} * (s64)(s32){r(rt)};"
                               f" r_lo = (u32)t; r_hi = (u32)(t >> 32); }}"), None, False
        if fn == 0x19: return (f"{{ u64 t = (u64){r(rs)} * (u64){r(rt)};"
                               f" r_lo = (u32)t; r_hi = (u32)(t >> 32); }}"), None, False
        if fn == 0x1A: return (f"if ({r(rt)}) {{ r_lo = (u32)((s32){r(rs)} / (s32){r(rt)});"
                               f" r_hi = (u32)((s32){r(rs)} %% (s32){r(rt)}); }}").replace("%%", "%"), None, False
        if fn == 0x1B: return (f"if ({r(rt)}) {{ r_lo = {r(rs)} / {r(rt)};"
                               f" r_hi = {r(rs)} % {r(rt)}; }}"), None, False
        if fn == 0x20 or fn == 0x21: return f"{r(rd)} = {r(rs)} + {r(rt)};", None, False
        if fn == 0x22 or fn == 0x23: return f"{r(rd)} = {r(rs)} - {r(rt)};", None, False
        if fn == 0x24: return f"{r(rd)} = {r(rs)} & {r(rt)};", None, False
        if fn == 0x25: return f"{r(rd)} = {r(rs)} | {r(rt)};", None, False
        if fn == 0x26: return f"{r(rd)} = {r(rs)} ^ {r(rt)};", None, False
        if fn == 0x27: return f"{r(rd)} = ~({r(rs)} | {r(rt)});", None, False
        if fn == 0x2A: return f"{r(rd)} = ((s32){r(rs)} < (s32){r(rt)});", None, False
        if fn == 0x2B: return f"{r(rd)} = ({r(rs)} < {r(rt)});", None, False
        # break: GCC puts one behind every division, on the path taken when
        # the divisor is zero. Our divisions are already guarded, so that path
        # is never reached; we keep the trace rather than refuse the whole
        # function over an instruction that never executes.
        if fn == 0x0D: return "/* break */", None, False
        raise Unsupported(f"special fn 0x{fn:02X} at {pc:08X}")

    if op == 1:
        if rt == 0: return f"COND(((s32){r(rs)} < 0))", tgt, True
        if rt == 1: return f"COND(((s32){r(rs)} >= 0))", tgt, True
        raise Unsupported(f"regimm rt={rt} at {pc:08X}")

    # The target of an absolute jump keeps the four high bits of the PC: it
    # only holds 26 bits, shifted by two. Forgetting this sends every jump into
    # the void -- and the error message then says so clearly enough that the
    # mistake cannot be made twice.
    if op == 2: return "J", (pc & 0xF0000000) | ((w & 0x3FFFFFF) << 2), True
    if op == 3: return "JAL", (pc & 0xF0000000) | ((w & 0x3FFFFFF) << 2), True
    if op == 4: return f"COND(({r(rs)} == {r(rt)}))", tgt, True
    if op == 5: return f"COND(({r(rs)} != {r(rt)}))", tgt, True
    if op == 6: return f"COND(((s32){r(rs)} <= 0))", tgt, True
    if op == 7: return f"COND(((s32){r(rs)} > 0))", tgt, True
    if op == 8 or op == 9: return f"{r(rt)} = {r(rs)} + {simm};", None, False
    if op == 10: return f"{r(rt)} = ((s32){r(rs)} < {simm});", None, False
    if op == 11: return f"{r(rt)} = ({r(rs)} < (u32){simm}u);", None, False
    if op == 12: return f"{r(rt)} = {r(rs)} & {imm}u;", None, False
    if op == 13: return f"{r(rt)} = {r(rs)} | {imm}u;", None, False
    if op == 14: return f"{r(rt)} = {r(rs)} ^ {imm}u;", None, False
    if op == 15: return f"{r(rt)} = {imm}u << 16;", None, False
    # Unaligned loads and stores. On MIPS they are written as lwl/lwr and
    # swl/swr pairs, each half taking the part of the word that falls on its
    # side of the boundary. In little-endian, lwl takes the high bytes.
    if op == 34:   # lwl
        return (f"{{ u32 a = {r(rs)} + {simm}; int n = (int)(a & 3);"
                f" u32 w = LW(a & ~3u);"
                f" {r(rt)} = ({r(rt)} & (u32)((1u << (24 - 8 * n)) - 1u))"
                f" | (w << (24 - 8 * n)); }}"), None, False
    if op == 38:   # lwr
        return (f"{{ u32 a = {r(rs)} + {simm}; int n = (int)(a & 3);"
                f" u32 w = LW(a & ~3u);"
                f" u32 m = (n == 0) ? 0u : (0xFFFFFFFFu << (32 - 8 * n));"
                f" {r(rt)} = ({r(rt)} & m) | (w >> (8 * n)); }}"), None, False
    if op == 42:   # swl
        return (f"{{ u32 a = {r(rs)} + {simm}; int n = (int)(a & 3);"
                f" u32 b = a & ~3u; u32 w = LW(b);"
                f" u32 m = (0xFFFFFFFFu << (8 * (3 - n) + 8)) & 0xFFFFFFFFu;"
                f" if (n == 3) m = 0u;"
                f" SW(b, (w & m) | ({r(rt)} >> (24 - 8 * n))); }}"), None, False
    if op == 46:   # swr
        return (f"{{ u32 a = {r(rs)} + {simm}; int n = (int)(a & 3);"
                f" u32 b = a & ~3u; u32 w = LW(b);"
                f" u32 m = (n == 0) ? 0u : ((1u << (8 * n)) - 1u);"
                f" SW(b, (w & m) | ({r(rt)} << (8 * n))); }}"), None, False
    if op == 32: return f"{r(rt)} = (u32)(s32)(s8)LB({r(rs)} + {simm});", None, False
    if op == 33: return f"{r(rt)} = (u32)(s32)(s16)LH({r(rs)} + {simm});", None, False
    if op == 35: return f"{r(rt)} = LW({r(rs)} + {simm});", None, False
    if op == 36: return f"{r(rt)} = LB({r(rs)} + {simm});", None, False
    if op == 37: return f"{r(rt)} = LH({r(rs)} + {simm});", None, False
    if op == 40: return f"SB({r(rs)} + {simm}, {r(rt)});", None, False
    if op == 41: return f"SH({r(rs)} + {simm}, {r(rt)});", None, False
    if op == 43: return f"SW({r(rs)} + {simm}, {r(rt)});", None, False
    # COP2: the GTE. The transfers become calls to the accessors, the commands
    # a call carrying their raw encoding -- it is the implementation that
    # decodes the sf, lm, mx, v and cv fields, not the translator, so that the
    # two stay separately verifiable.
    # COP0: the system coprocessor. The game only uses it to arm the GTE in the
    # status register and for critical sections. Modelling it as an array of
    # registers is enough -- and ignoring it was expensive: the function that
    # arms the GTE also sets ZSF3 and ZSF4, without which every depth comes out
    # zero and the game throws away every one of its polygons.
    if op == 16:
        if rs == 0: return f"{r(rt)} = COP0[{rd}];", None, False
        if rs == 4: return f"COP0[{rd}] = {r(rt)};", None, False
        if rs & 0x10: return "/* rfe */", None, False
        raise Unsupported(f"COP0 rs={rs} at {pc:08X}")
    if op == 18:
        if rs & 0x10:
            return f"gte_command(0x{w & 0x1FFFFFF:07X}u);", None, False
        if rs == 0: return f"{r(rt)} = gte_read_data({rd});", None, False
        if rs == 2: return f"{r(rt)} = gte_read_ctrl({rd});", None, False
        if rs == 4: return f"gte_write_data({rd}, {r(rt)});", None, False
        if rs == 6: return f"gte_write_ctrl({rd}, {r(rt)});", None, False
        raise Unsupported(f"COP2 rs={rs} at {pc:08X}")
    if op == 50: return f"gte_write_data({rt}, LW({r(rs)} + {simm}));", None, False
    if op == 58: return f"SW({r(rs)} + {simm}, gte_read_data({rt}));", None, False
    raise Unsupported(f"opcode {op} at {pc:08X}")


def translate(name, base, words):
    """Translates a sequence of words into a C function."""
    n = len(words)
    end = base + 4 * n
    # first pass: which addresses are branch targets
    labels = set()
    for i, w in enumerate(words):
        try:
            _, t, _ = decode(w, base + 4 * i)
        except Unsupported:
            raise
        if t is not None and base <= t < end:
            labels.add(t)

    # A `jr` on anything other than $ra targets either another function or --
    # and this is the case of gcc's switches -- an address inside this one,
    # read out of a table. The global dispatcher only knows function entry
    # points: it cannot serve the second case, and that silence cost
    # everything following the switch, interrupt acknowledgement included. So
    # these functions are given a local switchboard to each of their own
    # addresses, falling back on the global dispatcher for external targets.
    has_jrind = any(
        decode(w, base + 4 * i)[0].startswith("JRIND ")
        for i, w in enumerate(words))
    if has_jrind:
        labels |= {base + 4 * i for i in range(n)}

    protos = []
    for i, w in enumerate(words):
        if (w >> 26) == 3:
            t = (base + 4 * i) & 0xF0000000 | ((w & 0x3FFFFFF) << 2)
            if t in SYMS:
                protos.append(f"u32 psx_{SYMS[t]}(u32, u32, u32, u32);")
    out = sorted(set(protos))
    out += [f"u32 {name}(u32 r_a0, u32 r_a1, u32 r_a2, u32 r_a3)", "{"]
    used = sorted({REG[k] for k in range(1, 32)})
    out.append("    u32 " + ", ".join(
        f"r_{x} = 0" for x in used
        if x not in ("a0", "a1", "a2", "a3", "sp")) + ";")
    out.append("    u32 r_hi = 0, r_lo = 0, cond = 0, pc_next = 0;")

    out.append("    (void)r_hi; (void)r_lo; (void)cond; (void)pc_next;")

    # The instruction count.
    #
    # A static recompilation loses the one thing that gave the game its pace:
    # the time each instruction took. It is given back here, by charging in
    # advance the cost of each block of straight-line code -- between two
    # control transfers, we know exactly how many instructions are going to
    # execute, and it costs only one addition per block rather than one per
    # instruction.
    block_start = None
    block_size = 0

    def open_block():
        nonlocal block_start, block_size
        out.append("")            # reserved slot, filled in on close
        block_start = len(out) - 1
        block_size = 0

    def close_block():
        nonlocal block_start
        if block_start is None:
            return
        if block_size:
            out[block_start] = f"    CYCLES({block_size});"
        block_start = None

    open_block()
    i = 0
    while i < n:
        pc = base + 4 * i
        if pc in labels:
            close_block()
            out.append(f"L_{pc:08X}:;")
            open_block()
        w = words[i]
        txt, tgt, delayed = decode(w, pc)
        if not delayed:
            block_size += 1
            if txt:
                out.append("    " + txt)
            i += 1
            continue

        # delay slot instruction: it executes BEFORE the jump, whether that
        # jump is taken or not. So it is moved ahead of it, after freezing the
        # condition, which is evaluated on the values from before.
        block_size += 2       # the branch and its delay slot
        ds = words[i + 1] if i + 1 < n else 0
        dtxt, dtgt, ddel = decode(ds, pc + 4)
        if ddel:
            raise Unsupported(f"branch inside a delay slot at {pc:08X}")

        if txt.startswith("COND("):
            cnd = txt[5:-1]
            out.append(f"    cond = {cnd};")
            if dtxt:
                out.append("    " + dtxt)
            if base <= tgt < end:
                out.append(f"    if (cond) goto L_{tgt:08X};")
            else:
                raise Unsupported(f"branch outside the function to {tgt:08X}")
        elif txt == "J":
            if dtxt:
                out.append("    " + dtxt)
            if base <= tgt < end:
                out.append(f"    goto L_{tgt:08X};")
            else:
                raise Unsupported(f"jump outside the function to {tgt:08X}")
        elif txt == "JAL":
            callee = SYMS.get(tgt)
            if callee is None:
                raise Unsupported(f"call to {tgt:08X}, with no known symbol")
            if dtxt:
                out.append("    " + dtxt)
            # The callee receives $a0-$a3 and returns $v0. The caller's
            # temporary registers are declared clobbered by the calling
            # convention, so leaving them as they are cannot be observed by
            # code that respects it -- and the retail respects it, having been
            # compiled with it.
            out.append(f"    r_v0 = psx_{callee}(r_a0, r_a1, r_a2, r_a3);")
        elif txt.startswith("JRIND "):
            reg = txt.split()[1]
            if dtxt:
                out.append("    " + dtxt)
            out.append(f"    pc_next = {reg};")
            out.append("    goto DISPATCH;")
        elif txt.startswith("JALR "):
            _, reg, link = txt.split()
            if dtxt:
                out.append("    " + dtxt)
            if link != "0":
                out.append(f"    {link} = 0;   /* return address, never read back */")
            out.append(f"    r_v0 = psx_dispatch({reg}, r_a0, r_a1, r_a2, r_a3, r_t1);")
        elif txt.endswith("JR"):
            pre = txt[:-2].strip()
            if pre:
                out.append("    " + pre)
            if dtxt:
                out.append("    " + dtxt)
            out.append("    return r_v0;")
        # A branch can target another branch's delay slot. Since the slot has
        # been moved ahead of its branch, the address no longer carries a label
        # and C refuses the goto. It is put back here, behind a jump over it so
        # that the instruction is not replayed by falling into it.
        close_block()
        open_block()
        dpc = pc + 4
        if dpc in labels:
            after = f"A_{dpc:08X}"
            out.append(f"    goto {after};")
            out.append(f"L_{dpc:08X}:;")
            if dtxt:
                out.append("    " + dtxt)
            out.append(f"{after}:;")
        i += 2

    close_block()
    if has_jrind:
        out.append("    goto END;")
        out.append("DISPATCH:;")
        out.append("    switch (pc_next) {")
        for k in range(n):
            a = base + 4 * k
            out.append(f"    case 0x{a:08X}u: goto L_{a:08X};")
        out.append("    }")
        out.append("    return psx_dispatch(pc_next, r_a0, r_a1, r_a2, r_a3, r_t1);")
        out.append("END:;")
    out.append("    return r_v0;")
    out.append("}")
    return "\n".join(out)


def words_from_exe(path, addr, count, load=0x80010000, off=0x800):
    d = open(path, "rb").read()
    p = addr - load + off
    return list(struct.unpack("<%dI" % count, d[p:p + 4 * count]))


def func_length(asm_path, name):
    txt = open(asm_path, encoding="utf-8", errors="replace").read()
    m = re.search(r"^glabel " + name + r"$(.*?)^endlabel", txt, re.S | re.M)
    if not m:
        return None, None
    ins = re.findall(r"/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/", m.group(1))
    return int(ins[0], 16), len(ins)


if __name__ == "__main__":
    exe, asm = sys.argv[1], sys.argv[2]
    names = sys.argv[3:]
    print("/* generated by tools/recomp.py -- do not edit */")
    print('#include "rt.h"')
    print('#include "gte.h"')
    print("u32 psx_dispatch(u32, u32, u32, u32, u32, u32);")
    for nm in names:
        a, c = func_length(asm, nm)
        if a is None:
            sys.exit("function not found: " + nm)
        ws = words_from_exe(exe, a, c)
        print()
        print(f"/* {nm} @ {a:08X}, {c} instructions */")
        print(translate(nm, a, ws))
