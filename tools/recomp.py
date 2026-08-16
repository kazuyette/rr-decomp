#!/usr/bin/env python3
"""Traducteur MIPS R3000 vers C, pour le banc d'essai du portage natif.

Pourquoi celui-ci existe
------------------------
Neuf dixièmes du code de jeu sont encore de l'assembleur. Un jalon natif qui
démarre ne peut donc pas être fait de nos fonctions C plus des bouchons : il
manquerait la boucle de course, la physique et le renderer. La recompilation
statique retourne le problème -- on traduit mécaniquement chaque instruction,
le jeu tourne entier, et chaque fonction décompilée remplace ensuite sa jumelle
traduite.

Ce fichier est l'étape zéro de ce chantier : prouver que la traduction est
fidèle. Pas « ça a l'air de marcher » -- fidèle au bit près, vérifié en
exécutant le vrai code MIPS sous qemu et en comparant les sorties.

La forme choisie
----------------
Une fonction MIPS devient une fonction C prenant les registres d'argument et
rendant $v0, avec la mémoire vue comme un tableau d'octets adressé par des
accesseurs. Les registres deviennent des variables locales u32 ; les branches
deviennent des `goto` vers des étiquettes.

Le point qui décide de tout : le **créneau de retard**. Sur MIPS, l'instruction
qui suit un branchement s'exécute avant lui, qu'il soit pris ou non. Une
traduction naïve qui l'émet après le `goto` produit du code qui a l'air juste
et se trompe partout où le créneau modifie le registre testé. On l'émet donc
AVANT, systématiquement, et on garde une copie de la condition évaluée avant
qu'il ne s'exécute.

Ce que ce traducteur ne fait pas
--------------------------------
Le COP2 (le GTE) n'est pas traduit : ses quarante opcodes demandent une
implémentation à part, validée contre la documentation matérielle et non contre
qemu, qui ne connaît pas ce coprocesseur. Les fonctions qui en contiennent sont
refusées explicitement plutôt que traduites à moitié.
"""
import re
import struct
import sys

REG = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
       "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
       "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
       "t8", "t9", "k0", "k1", "gp", "sp", "s8", "ra"]


def r(n):
    """$zero est la constante 0 ; $sp est un global.

    Le pointeur de pile ne peut pas être une variable locale : un appelé doit
    voir celui de son appelant, sinon les cadres se recouvrent et les
    arguments passés sur la pile -- ceux au-delà du quatrième -- se lisent
    dans le vide. En faire un global rend les deux corrects sans code
    particulier, parce que c'est exactement ce qu'il est sur la machine."""
    if n == 0:
        return "0"
    if n == 29:
        return "g_sp"
    return "r_" + REG[n]


class Unsupported(Exception):
    pass


SYMS = {}   # adresse -> nom, rempli par load_symbols()


def load_symbols(*asm_paths):
    """Toutes les fonctions des unites desassemblees, par adresse."""
    for path in asm_paths:
        txt = open(path, encoding="utf-8", errors="replace").read()
        for f in re.split(r"^glabel ", txt, flags=re.M)[1:]:
            nm = f.split("\n", 1)[0].strip()
            m = re.search(r"/\* [0-9A-F]+ ([0-9A-F]{8}) ", f)
            if m:
                SYMS[int(m.group(1), 16)] = nm
    return SYMS


def decode(w, pc):
    """Rend (texte C, cible de branchement ou None, a_un_creneau)."""
    txt, tgt, dly = _decode(w, pc)
    # $zero est cable a zero : une ecriture dedans est jetee par le materiel.
    # Le retail en contient -- les nop encodes autrement, et les resultats
    # calcules puis abandonnes. Traduites telles quelles, elles donnent une
    # affectation a une constante, que le C refuse.
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
        # jr $ra est un retour ; jr sur tout autre registre est un saut
        # indirect -- une table de branchement, ou un trampoline BIOS. Les
        # confondre compile et s'execute, et se trompe en silence : 54 sauts
        # de ce genre etaient traduits en retours avant qu'on les compte.
        if fn == 0x08:
            return ("JR" if rs == 31 else f"JRIND {r(rs)}"), None, True
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
        # break : GCC en pose un derriere chaque division, sur le chemin pris
        # quand le diviseur est nul. Nos divisions sont deja gardees, donc ce
        # chemin ne s'atteint pas ; on garde la trace plutot que de refuser la
        # fonction entiere pour une instruction qui ne s'execute jamais.
        if fn == 0x0D: return "/* break */", None, False
        raise Unsupported(f"special fn 0x{fn:02X} en {pc:08X}")

    if op == 1:
        if rt == 0: return f"COND(((s32){r(rs)} < 0))", tgt, True
        if rt == 1: return f"COND(((s32){r(rs)} >= 0))", tgt, True
        raise Unsupported(f"regimm rt={rt} en {pc:08X}")

    # La cible d'un saut absolu garde les quatre bits hauts du PC : elle ne
    # tient que sur 26 bits, decalee de deux. L'oublier envoie tous les sauts
    # dans le vide -- et le message d'erreur le dit alors si clairement qu'on
    # ne peut pas se tromper deux fois.
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
    # Chargements et rangements non alignes. Sur MIPS on les ecrit par paires
    # lwl/lwr et swl/swr, chaque moitie prenant la part du mot qui tombe de son
    # cote de la frontiere. En petit-boutiste, lwl prend les octets hauts.
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
    # COP2 : le GTE. Les transferts deviennent des appels aux accesseurs, les
    # commandes un appel avec leur encodage brut -- c'est l'implementation qui
    # decode les champs sf, lm, mx, v et cv, pas le traducteur, pour que les
    # deux restent verifiables separement.
    if op == 18:
        if rs & 0x10:
            return f"gte_command(0x{w & 0x1FFFFFF:07X}u);", None, False
        if rs == 0: return f"{r(rt)} = gte_read_data({rd});", None, False
        if rs == 2: return f"{r(rt)} = gte_read_ctrl({rd});", None, False
        if rs == 4: return f"gte_write_data({rd}, {r(rt)});", None, False
        if rs == 6: return f"gte_write_ctrl({rd}, {r(rt)});", None, False
        raise Unsupported(f"COP2 rs={rs} en {pc:08X}")
    if op == 50: return f"gte_write_data({rt}, LW({r(rs)} + {simm}));", None, False
    if op == 58: return f"SW({r(rs)} + {simm}, gte_read_data({rt}));", None, False
    raise Unsupported(f"opcode {op} en {pc:08X}")


def translate(name, base, words):
    """Traduit une suite de mots en une fonction C."""
    n = len(words)
    end = base + 4 * n
    # première passe : quelles adresses sont des cibles de branchement
    labels = set()
    for i, w in enumerate(words):
        try:
            _, t, _ = decode(w, base + 4 * i)
        except Unsupported:
            raise
        if t is not None and base <= t < end:
            labels.add(t)

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

    i = 0
    while i < n:
        pc = base + 4 * i
        if pc in labels:
            out.append(f"L_{pc:08X}:;")
        w = words[i]
        txt, tgt, delayed = decode(w, pc)
        if not delayed:
            if txt:
                out.append("    " + txt)
            i += 1
            continue

        # instruction du créneau de retard : elle s'exécute AVANT le saut,
        # que celui-ci soit pris ou non. On la déplace donc devant, après
        # avoir figé la condition, qui est évaluée sur les valeurs d'avant.
        ds = words[i + 1] if i + 1 < n else 0
        dtxt, dtgt, ddel = decode(ds, pc + 4)
        if ddel:
            raise Unsupported(f"branchement dans un creneau de retard en {pc:08X}")

        if txt.startswith("COND("):
            cnd = txt[5:-1]
            out.append(f"    cond = {cnd};")
            if dtxt:
                out.append("    " + dtxt)
            if base <= tgt < end:
                out.append(f"    if (cond) goto L_{tgt:08X};")
            else:
                raise Unsupported(f"branchement hors fonction vers {tgt:08X}")
        elif txt == "J":
            if dtxt:
                out.append("    " + dtxt)
            if base <= tgt < end:
                out.append(f"    goto L_{tgt:08X};")
            else:
                raise Unsupported(f"saut hors fonction vers {tgt:08X}")
        elif txt == "JAL":
            callee = SYMS.get(tgt)
            if callee is None:
                raise Unsupported(f"appel vers {tgt:08X}, sans symbole connu")
            if dtxt:
                out.append("    " + dtxt)
            # L'appele reçoit $a0-$a3 et rend $v0. Les registres temporaires de
            # l'appelant sont declares detruits par la convention d'appel, donc
            # les laisser tels quels ne peut pas etre observe par du code qui la
            # respecte -- et le retail la respecte, il a ete compile avec.
            out.append(f"    r_v0 = psx_{callee}(r_a0, r_a1, r_a2, r_a3);")
        elif txt.startswith("JRIND "):
            reg = txt.split()[1]
            if dtxt:
                out.append("    " + dtxt)
            out.append(f"    return psx_dispatch({reg}, r_a0, r_a1, r_a2, r_a3, r_t1);")
        elif txt.startswith("JALR "):
            _, reg, link = txt.split()
            if dtxt:
                out.append("    " + dtxt)
            if link != "0":
                out.append(f"    {link} = 0;   /* adresse de retour, jamais relue */")
            out.append(f"    r_v0 = psx_dispatch({reg}, r_a0, r_a1, r_a2, r_a3, r_t1);")
        elif txt.endswith("JR"):
            pre = txt[:-2].strip()
            if pre:
                out.append("    " + pre)
            if dtxt:
                out.append("    " + dtxt)
            out.append("    return r_v0;")
        # Un branchement peut viser le creneau de retard d'un autre. Comme le
        # creneau a ete deplace devant son branchement, l'adresse ne porte plus
        # d'etiquette et le C refuse le goto. On la remet ici, apres un saut
        # par-dessus pour ne pas rejouer l'instruction en tombant dedans.
        dpc = pc + 4
        if dpc in labels:
            after = f"A_{dpc:08X}"
            out.append(f"    goto {after};")
            out.append(f"L_{dpc:08X}:;")
            if dtxt:
                out.append("    " + dtxt)
            out.append(f"{after}:;")
        i += 2

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
    print("/* genere par tools/recomp.py -- ne pas editer */")
    print('#include "rt.h"')
    print('#include "gte.h"')
    print("u32 psx_dispatch(u32, u32, u32, u32, u32, u32);")
    for nm in names:
        a, c = func_length(asm, nm)
        if a is None:
            sys.exit("fonction introuvable : " + nm)
        ws = words_from_exe(exe, a, c)
        print()
        print(f"/* {nm} @ {a:08X}, {c} instructions */")
        print(translate(nm, a, ws))
