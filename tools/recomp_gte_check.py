#!/usr/bin/env python3
"""Contrôle du GTE : deux transcriptions de la même spécification.

qemu ne connaît pas le COP2 : la référence par exécution qui a validé les
fonctions entières ne dit rien ici. Le seul contrôle disponible est donc de
réécrire les opérations une seconde fois, dans un autre langage et sans
regarder la première, puis de comparer sur des états de registres tirés au
hasard.

Ce que ça vaut, exactement : deux transcriptions indépendantes d'une même
documentation ne se trompent pas au même endroit, sauf si la documentation
elle-même est ambiguë. Ça attrape les fautes de frappe, les décalages
inversés, les saturations oubliées -- c'est-à-dire l'essentiel de ce qui rate
dans ce genre de code. Ça n'attrape pas une lecture fausse partagée. Le seul
contrôle qui le ferait serait la console.
"""
import ctypes
import random
import struct
import subprocess
import sys

D = "/tmp/recomp"
subprocess.run(["gcc", "-O1", "-w", "-shared", "-fPIC", "-I" + D,
                "-o", D + "/libgte.so", D + "/gte.c", D + "/ram.c"], check=True)
lib = ctypes.CDLL(D + "/libgte.so")


def s16(v):
    v &= 0xFFFF
    return v - 0x10000 if v & 0x8000 else v


def s32(v):
    v &= 0xFFFFFFFF
    return v - 0x100000000 if v & 0x80000000 else v


def s64(v):
    v &= (1 << 64) - 1
    return v - (1 << 64) if v & (1 << 63) else v


class Ref:
    """Le GTE, réécrit depuis la documentation matérielle."""

    def __init__(self, rnd):
        self.d = [0] * 32
        self.c = [0] * 32
        for i in range(32):
            self.d[i] = rnd.randrange(1 << 32)
            self.c[i] = rnd.randrange(1 << 32)
        self.flag = 0

    # --- accès nommés
    def V(self, i):
        x = s16(self.d[i * 2] & 0xFFFF)
        y = s16(self.d[i * 2] >> 16)
        z = s16(self.d[i * 2 + 1] & 0xFFFF)
        return x, y, z

    def RT(self):
        m = []
        for i in range(4):
            m.append(s16(self.c[i] & 0xFFFF))
            m.append(s16(self.c[i] >> 16))
        m.append(s16(self.c[4] & 0xFFFF))
        return m

    def MX(self, k):
        base = {0: 0, 1: 8, 2: 16}[k]
        m = []
        for i in range(4):
            m.append(s16(self.c[base + i] & 0xFFFF))
            m.append(s16(self.c[base + i] >> 16))
        m.append(s16(self.c[base + 4] & 0xFFFF))
        return m

    # --- saturations
    def mac(self, n, v):
        v = s64(v)
        if v >= 1 << 43:
            self.flag |= (1 << 30) >> (n - 1)
        if v < -(1 << 43):
            self.flag |= (1 << 27) >> (n - 1)
        return s32(v)

    def ir(self, n, v, lm):
        lo = 0 if lm else -0x8000
        if v > 0x7FFF:
            self.flag |= (1 << 24) >> (n - 1)
            return 0x7FFF
        if v < lo:
            self.flag |= (1 << 24) >> (n - 1)
            return lo
        return v

    # --- opérations
    def mvmva(self, code):
        sf = (code >> 19) & 1
        lm = (code >> 10) & 1
        mx = (code >> 17) & 3
        vx = (code >> 15) & 3
        cv = (code >> 13) & 3
        m = self.MX(mx) if mx < 3 else [0] * 9
        if vx < 3:
            a, b, c = self.V(vx)
        else:
            a, b, c = (s16(self.d[9]), s16(self.d[10]), s16(self.d[11]))
        if cv == 0:
            t = (s32(self.c[5]), s32(self.c[6]), s32(self.c[7]))
        elif cv == 1:
            t = (s32(self.c[13]), s32(self.c[14]), s32(self.c[15]))
        elif cv == 2:
            t = (s32(self.c[21]), s32(self.c[22]), s32(self.c[23]))
        else:
            t = (0, 0, 0)
        sh = 12 if sf else 0
        out = []
        for row in range(3):
            v = (t[row] << 12) + m[row * 3] * a + m[row * 3 + 1] * b + m[row * 3 + 2] * c
            out.append(self.mac(row + 1, v >> sh))
        irs = [self.ir(i + 1, out[i], lm) for i in range(3)]
        return out, irs

    def nclip(self):
        sx = [s16(self.d[12] & 0xFFFF), s16(self.d[13] & 0xFFFF), s16(self.d[14] & 0xFFFF)]
        sy = [s16(self.d[12] >> 16), s16(self.d[13] >> 16), s16(self.d[14] >> 16)]
        v = (sx[0] * (sy[1] - sy[2]) + sx[1] * (sy[2] - sy[0]) + sx[2] * (sy[0] - sy[1]))
        return s32(v)

    def avsz(self, four):
        zsf = s16(self.c[30] & 0xFFFF) if four else s16(self.c[29] & 0xFFFF)
        z = [self.d[16 + i] & 0xFFFF for i in range(4)]
        tot = sum(z) if four else sum(z[1:])
        mac0 = s32(zsf * tot)
        otz = mac0 >> 12
        otz = 0 if otz < 0 else (0xFFFF if otz > 0xFFFF else otz)
        return mac0, otz

    def sqr(self, sf):
        sh = 12 if sf else 0
        ir = [s16(self.d[9]), s16(self.d[10]), s16(self.d[11])]
        return [self.mac(i + 1, (ir[i] * ir[i]) >> sh) for i in range(3)]

    def op(self, sf):
        sh = 12 if sf else 0
        m = self.RT()
        ir1, ir2, ir3 = s16(self.d[9]), s16(self.d[10]), s16(self.d[11])
        return [self.mac(1, (m[4] * ir3 - m[8] * ir2) >> sh),
                self.mac(2, (m[8] * ir1 - m[0] * ir3) >> sh),
                self.mac(3, (m[0] * ir2 - m[4] * ir1) >> sh)]


# --- pilotage de l'implémentation C
lib.gte_write_data.argtypes = [ctypes.c_int, ctypes.c_uint32]
lib.gte_write_ctrl.argtypes = [ctypes.c_int, ctypes.c_uint32]
lib.gte_read_data.restype = ctypes.c_uint32
lib.gte_read_ctrl.restype = ctypes.c_uint32
lib.gte_command.argtypes = [ctypes.c_uint32]


def load(ref):
    """L'ordre compte : certains registres en modifient d'autres à l'écriture.

    Écrire IRGB (28) dépaquette une couleur 5-5-5 dans IR1-3 ; écrire SXYP (15)
    pousse la pile des coordonnées écran ; LZCR (31) et ORGB (29) sont en
    lecture seule. Un chargeur naïf qui balaie 0 à 31 détruit donc une partie de
    l'état qu'il croit poser -- et fait échouer la comparaison pour une raison
    qui n'a rien à voir avec l'implémentation testée.
    """
    SKIP = (15, 28, 29, 31)
    for i in range(32):
        if i not in SKIP:
            lib.gte_write_data(i, ref.d[i])
        lib.gte_write_ctrl(i, ref.c[i])
    for i in (9, 10, 11):        # IR1-3, reposés après tout ce qui les touche
        lib.gte_write_data(i, ref.d[i])


CASES = [
    ("mvmva  sf=1", 0x0480012), ("mvmva  sf=0", 0x0400012),
    ("mvmva  mx=1", 0x04A6412), ("mvmva  mx=2", 0x04DA412),
    ("nclip",       0x1400006),
    ("avsz3",       0x158002D), ("avsz4",       0x168002E),
    ("sqr    sf=1", 0x0A80428), ("sqr    sf=0", 0x0A00428),
    ("op     sf=1", 0x178000C), ("op     sf=0", 0x170000C),
]

rnd = random.Random(20260816)
ROUNDS = 400
bad = {}
for k in range(ROUNDS):
    for name, code in CASES:
        ref = Ref(rnd)
        load(ref)
        lib.gte_command(code)
        fn = code & 0x3F
        got = None
        want = None
        if fn == 0x12:
            macs, irs = ref.mvmva(code)
            want = tuple(macs) + tuple(irs)
            got = tuple(s32(lib.gte_read_data(i)) for i in (25, 26, 27)) + \
                  tuple(s16(lib.gte_read_data(i)) for i in (9, 10, 11))
        elif fn == 0x06:
            want = (ref.nclip(),)
            got = (s32(lib.gte_read_data(24)),)
        elif fn in (0x2D, 0x2E):
            m, o = ref.avsz(fn == 0x2E)
            want = (m, o)
            got = (s32(lib.gte_read_data(24)), lib.gte_read_data(7))
        elif fn == 0x28:
            want = tuple(ref.sqr((code >> 19) & 1))
            got = tuple(s32(lib.gte_read_data(i)) for i in (25, 26, 27))
        elif fn == 0x0C:
            want = tuple(ref.op((code >> 19) & 1))
            got = tuple(s32(lib.gte_read_data(i)) for i in (25, 26, 27))
        if want != got:
            if name not in bad:
                bad[name] = (want, got)
            bad[name] = bad[name]
            bad.setdefault("_n_" + name, 0)
            bad["_n_" + name] += 1

print("%d etats tires, %d operations chacune" % (ROUNDS, len(CASES)))
fails = [k for k in bad if not k.startswith("_n_")]
if not fails:
    print("AUCUN ECART entre les deux transcriptions.")
else:
    for k in fails:
        print("ECART sur %-12s (%d fois)" % (k, bad["_n_" + k]))
        print("   reference python :", bad[k][0])
        print("   implementation C :", bad[k][1])
    sys.exit(1)
