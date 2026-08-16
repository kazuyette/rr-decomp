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


    # --- couleur et brume
    def col(self, v, n):
        if v > 0xFF:
            self.flag |= (1 << 21) >> (n - 1)
            return 0xFF
        if v < 0:
            self.flag |= (1 << 21) >> (n - 1)
            return 0
        return v

    def interp(self, base, sf, lm):
        """MAC <- MAC + IR0 * (FC - MAC), a l'echelle du materiel.

        La specification dit : IR = ((FC SHL 12) - MAC) SAR (sf*12), puis
        MAC = (IR * IR0 + MAC) SAR (sf*12). Le MAC de depart n'est PAS
        redecale ; c'est le piege de cette famille.
        """
        sh = 12 if sf else 0
        fc = (s32(self.c[21]), s32(self.c[22]), s32(self.c[23]))
        mac = list(base)
        irs = []
        for i in range(3):
            irs.append(self.ir(i + 1, ((fc[i] << 12) - mac[i]) >> sh, 0))
        ir0 = s16(self.d[8])
        out = [self.mac(i + 1, (irs[i] * ir0 + mac[i]) >> sh) for i in range(3)]
        firs = [self.ir(i + 1, out[i], lm) for i in range(3)]
        rgb = [self.col(out[i] >> 4, i + 1) for i in range(3)]
        return out, firs, rgb

    def gpf(self, sf, lm):
        sh = 12 if sf else 0
        ir0 = s16(self.d[8])
        ir = [s16(self.d[9]), s16(self.d[10]), s16(self.d[11])]
        out = [self.mac(i + 1, (ir[i] * ir0) >> sh) for i in range(3)]
        return out, [self.ir(i + 1, out[i], lm) for i in range(3)], \
               [self.col(out[i] >> 4, i + 1) for i in range(3)]

    def gpl(self, sf, lm):
        sh = 12 if sf else 0
        ir0 = s16(self.d[8])
        ir = [s16(self.d[9]), s16(self.d[10]), s16(self.d[11])]
        mac = [s32(self.d[25]), s32(self.d[26]), s32(self.d[27])]
        out = [self.mac(i + 1, ((mac[i] << sh) + ir[i] * ir0) >> sh) for i in range(3)]
        return out, [self.ir(i + 1, out[i], lm) for i in range(3)], \
               [self.col(out[i] >> 4, i + 1) for i in range(3)]

    def intpl(self, sf, lm):
        ir = [s16(self.d[9]), s16(self.d[10]), s16(self.d[11])]
        return self.interp([x << 12 for x in ir], sf, lm)

    def dpcs(self, sf, lm):
        rgbc = self.d[6]
        return self.interp([(rgbc & 0xFF) << 16, ((rgbc >> 8) & 0xFF) << 16,
                            ((rgbc >> 16) & 0xFF) << 16], sf, lm)

    # --- eclairage
    def matvec(self, mk, v, t, sf, lm):
        sh = 12 if sf else 0
        m = self.MX(mk)
        out = []
        for row in range(3):
            x = ((t[row] << 12) + m[row * 3] * v[0] + m[row * 3 + 1] * v[1]
                 + m[row * 3 + 2] * v[2])
            out.append(self.mac(row + 1, x >> sh))
        irs = [self.ir(i + 1, out[i], lm) for i in range(3)]
        return out, irs

    def nc(self, vi, sf, lm, use_rgb, fog):
        """La chaine complete : lumiere, couleur, teinte, puis brume.

        Le point sur lequel les deux transcriptions pouvaient diverger est le
        sort du MAC entre la seconde matrice et la couleur : sans teinte par
        RGBC, la specification le laisse tel quel et la FIFO recoit MAC/16.
        """
        sh = 12 if sf else 0
        v = self.V(vi)
        _, ir = self.matvec(1, v, (0, 0, 0), sf, lm)
        bk = (s32(self.c[13]), s32(self.c[14]), s32(self.c[15]))
        mac, ir = self.matvec(2, ir, bk, sf, lm)
        rgbc = self.d[6]
        if use_rgb:
            base = [((rgbc >> (8 * i)) & 0xFF) * ir[i] << 4 for i in range(3)]
        else:
            base = list(mac)
        if fog:
            return self.interp(base, sf, lm)
        if use_rgb:
            out = [self.mac(i + 1, base[i] >> sh) for i in range(3)]
        else:
            out = list(base)
        firs = [self.ir(i + 1, out[i], lm) for i in range(3)]
        return out, firs, [self.col(out[i] >> 4, i + 1) for i in range(3)]

    def cc_op(self, sf, lm, depth):
        sh = 12 if sf else 0
        ir = [s16(self.d[9]), s16(self.d[10]), s16(self.d[11])]
        bk = (s32(self.c[13]), s32(self.c[14]), s32(self.c[15]))
        mac, ir = self.matvec(2, ir, bk, sf, lm)
        rgbc = self.d[6]
        base = [((rgbc >> (8 * i)) & 0xFF) * ir[i] << 4 for i in range(3)]
        if depth:
            return self.interp(base, sf, lm)
        out = [self.mac(i + 1, base[i] >> sh) for i in range(3)]
        firs = [self.ir(i + 1, out[i], lm) for i in range(3)]
        return out, firs, [self.col(out[i] >> 4, i + 1) for i in range(3)]

    def dcpl(self, sf, lm):
        rgbc = self.d[6]
        ir = [s16(self.d[9]), s16(self.d[10]), s16(self.d[11])]
        return self.interp([((rgbc >> (8 * i)) & 0xFF) * ir[i] << 4 for i in range(3)],
                           sf, lm)

    # --- projection
    def unr(self, h, sz3):
        """La division du materiel : table de 257 entrees, deux iterations.

        Reecrite depuis la specification sans regarder l'implementation C. Le
        point delicat est le decalage de normalisation : il faut amener SZ3 sur
        son bit de poids fort avant d'indexer la table, sinon l'approximation
        part sur la mauvaise decade.
        """
        if h >= sz3 * 2:
            self.flag |= 1 << 17
            return 0x1FFFF
        z = 0
        while z < 16 and not ((sz3 << z) & 0x8000):
            z += 1
        n = h << z
        d = sz3 << z
        tbl = []
        for i in range(257):
            v = (0x40000 // (i + 0x100) + 1) // 2 - 0x101
            tbl.append(0 if v < 0 else (0xFF if v > 0xFF else v))
        u = tbl[(d - 0x7FC0) >> 7] + 0x101
        d = ((0x2000080 - (d * u)) >> 8) & 0xFFFFFFFF
        d = ((0x0000080 + (d * u)) >> 8) & 0xFFFFFFFF
        n = ((n * d + 0x8000) >> 16) & 0xFFFFFFFF
        return min(n, 0x1FFFF)

    def rtp(self, vi, sf, lm, last, st):
        sh = 12 if sf else 0
        m = self.RT()
        vx, vy, vz = self.V(vi)
        tr = (s32(self.c[5]), s32(self.c[6]), s32(self.c[7]))
        acc = []
        for row in range(3):
            v = ((tr[row] << 12) + m[row * 3] * vx + m[row * 3 + 1] * vy
                 + m[row * 3 + 2] * vz)
            acc.append(v)
        mac = [self.mac(i + 1, acc[i] >> sh) for i in range(3)]
        ir1 = self.ir(1, mac[0], lm)
        ir2 = self.ir(2, mac[1], lm)
        unshifted = acc[2] >> 12
        if unshifted < -0x8000 or unshifted > 0x7FFF:
            self.flag |= 1 << 22
        lo = 0 if lm else -0x8000
        ir3 = 0x7FFF if mac[2] > 0x7FFF else (lo if mac[2] < lo else mac[2])
        z = unshifted
        sz3 = 0 if z < 0 else (0xFFFF if z > 0xFFFF else z)
        st["sz"] = st["sz"][1:] + [sz3]
        h = self.c[26] & 0xFFFF
        q = self.unr(h, sz3)
        ofx, ofy = s32(self.c[24]), s32(self.c[25])
        sx = q * ir1 + ofx
        sy = q * ir2 + ofy
        cx = sx >> 16
        cy = sy >> 16
        cx = 0x3FF if cx > 0x3FF else (-0x400 if cx < -0x400 else cx)
        cy = 0x3FF if cy > 0x3FF else (-0x400 if cy < -0x400 else cy)
        st["sxy"] = st["sxy"][1:] + [(cx, cy)]
        st["mac"] = mac
        st["ir"] = [ir1, ir2, ir3]
        st["mac0"] = s32(sy)
        if last:
            dqa = s16(self.c[27] & 0xFFFF)
            dqb = s32(self.c[28])
            dq = q * dqa + dqb
            st["mac0"] = s32(dq)
            v = dq >> 12
            st["ir0"] = 0x1000 if v > 0x1000 else (0 if v < 0 else v)
        return st

    def rtps(self, sf, lm, three):
        st = {"sz": [self.d[16] & 0xFFFF, self.d[17] & 0xFFFF,
                     self.d[18] & 0xFFFF, self.d[19] & 0xFFFF][1:],
              "sxy": [(s16(self.d[12] & 0xFFFF), s16(self.d[12] >> 16)),
                      (s16(self.d[13] & 0xFFFF), s16(self.d[13] >> 16)),
                      (s16(self.d[14] & 0xFFFF), s16(self.d[14] >> 16))],
              "ir0": s16(self.d[8])}
        if three:
            for i in range(3):
                st = self.rtp(i, sf, lm, i == 2, st)
        else:
            st = self.rtp(0, sf, lm, 1, st)
        return st

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
    ("rtps",        0x0180001), ("rtpt",        0x0280030),
    ("gpf    sf=1", 0x198003D), ("gpf    sf=0", 0x190003D),
    ("gpl    sf=1", 0x1A8003E), ("gpl    sf=0", 0x1A0003E),
    ("intpl",       0x0980011), ("dpcs",        0x0780010),
    ("ncs",         0x0C8041E), ("nct",         0x0D80420),
    ("nccs",        0x108041B), ("ncct",        0x118043F),
    ("ncds",        0x0E80413), ("ncdt",        0x0F80416),
    ("cc",          0x138041C), ("cdp",         0x1280414),
    ("dcpl",        0x0680029),
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
        elif fn in (0x01, 0x30):
            st = ref.rtps((code >> 19) & 1, (code >> 10) & 1, fn == 0x30)
            want = (tuple(st["mac"]), tuple(st["ir"]), st["sz"][-1],
                    st["sxy"][-1], st["ir0"], st["mac0"])
            got = (tuple(s32(lib.gte_read_data(i)) for i in (25, 26, 27)),
                   tuple(s16(lib.gte_read_data(i)) for i in (9, 10, 11)),
                   lib.gte_read_data(19),
                   (s16(lib.gte_read_data(14) & 0xFFFF), s16(lib.gte_read_data(14) >> 16)),
                   s16(lib.gte_read_data(8)), s32(lib.gte_read_data(24)))
        elif fn in (0x3D, 0x3E, 0x11, 0x10):
            sf = (code >> 19) & 1; lm = (code >> 10) & 1
            f = {0x3D: ref.gpf, 0x3E: ref.gpl, 0x11: ref.intpl, 0x10: ref.dpcs}[fn]
            macs, irs, rgb = f(sf, lm)
            want = (tuple(macs), tuple(irs), tuple(rgb))
            c2 = lib.gte_read_data(22)
            got = (tuple(s32(lib.gte_read_data(i)) for i in (25, 26, 27)),
                   tuple(s16(lib.gte_read_data(i)) for i in (9, 10, 11)),
                   (c2 & 0xFF, (c2 >> 8) & 0xFF, (c2 >> 16) & 0xFF))
        elif fn in (0x1E, 0x20, 0x1B, 0x3F, 0x13, 0x16, 0x1C, 0x14, 0x29):
            sf = (code >> 19) & 1; lm = (code >> 10) & 1
            if fn == 0x29:
                macs, irs, rgb = ref.dcpl(sf, lm)
            elif fn in (0x1C, 0x14):
                macs, irs, rgb = ref.cc_op(sf, lm, fn == 0x14)
            else:
                three = fn in (0x20, 0x3F, 0x16)
                use_rgb = fn in (0x1B, 0x3F, 0x13, 0x16)
                fog = fn in (0x13, 0x16)
                for vi in range(3 if three else 1):
                    macs, irs, rgb = ref.nc(vi, sf, lm, use_rgb, fog)
            want = (tuple(macs), tuple(irs), tuple(rgb))
            c2 = lib.gte_read_data(22)
            got = (tuple(s32(lib.gte_read_data(i)) for i in (25, 26, 27)),
                   tuple(s16(lib.gte_read_data(i)) for i in (9, 10, 11)),
                   (c2 & 0xFF, (c2 >> 8) & 0xFF, (c2 >> 16) & 0xFF))
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
