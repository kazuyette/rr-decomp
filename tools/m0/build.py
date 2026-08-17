#!/usr/bin/env python3
"""Construit l'exécutable natif depuis ta propre copie du jeu.

Ce script est le seul point d'entrée du banc. Il produit les trois fichiers
générés -- le code traduit, la table d'aiguillage, la description du disque --
puis compile. Rien de ce qu'il écrit n'est versionné : ce sont le code et les
données du jeu dans une autre notation, exactement comme `asm/`.

    python3 tools/m0/build.py PSX.EXE --iso data.iso --compile
    ./build/m0 90 PSX.EXE

`data.iso` est l'image de la piste de données de ton disque. Elle sert les
secteurs tels quels : le jeu y trouve son descripteur de volume, son répertoire
et ses fichiers, sans qu'on ait à les extraire.

Pourquoi un script et pas un Makefile
-------------------------------------
La liste des fonctions à traduire n'est pas écrite quelque part : elle se
déduit du désassemblage, qui se déduit lui-même de l'exécutable. Un Makefile
demanderait de figer cette liste dans un fichier, qui se périmerait au premier
symbole renommé. Ici elle est recalculée à chaque construction.
"""
import argparse
import os
import re
import struct
import subprocess
import sys

ENTREES_INTERNES = {"irq_body": 0x8004934C}

ICI = os.path.dirname(os.path.abspath(__file__))
RACINE = os.path.dirname(os.path.dirname(ICI))
sys.path.insert(0, os.path.join(RACINE, "tools"))

import recomp


def unites_asm():
    """Les fichiers de désassemblage, dans l'ordre où splat les écrit."""
    dossier = os.path.join(RACINE, "asm")
    if not os.path.isdir(dossier):
        sys.exit("asm/ est absent -- lance `make setup` d'abord")
    return [os.path.join(dossier, n)
            for n in sorted(os.listdir(dossier)) if n.endswith(".s")]


def fonctions(chemins):
    """Chaque `glabel` avec son adresse et son nombre d'instructions.

    On garde la première définition rencontrée : un même symbole peut
    apparaître dans deux unités quand une frontière a bougé, et la seconde
    n'est alors qu'un doublon."""
    vues = {}
    ordre = []
    motif = re.compile(r"/\* [0-9A-F]+ ([0-9A-F]{8}) [0-9A-F]{8} \*/")
    for chemin in chemins:
        txt = open(chemin, encoding="utf-8", errors="replace").read()
        for bloc in re.split(r"^glabel ", txt, flags=re.M)[1:]:
            nom = bloc.split("\n", 1)[0].strip()
            if nom in vues:
                continue
            ins = motif.findall(bloc.split("\nglabel ")[0])
            if not ins:
                continue
            vues[nom] = (int(ins[0], 16), len(ins))
            ordre.append(nom)
    return ordre, vues


def en_tete_exe(chemin):
    with open(chemin, "rb") as f:
        h = f.read(0x800)
    if h[:8] != b"PS-X EXE":
        sys.exit(chemin + " n'est pas un executable PlayStation")
    pc, = struct.unpack_from("<I", h, 0x10)
    charge, = struct.unpack_from("<I", h, 0x18)
    taille, = struct.unpack_from("<I", h, 0x1C)
    return pc, charge, taille


def ecrire_jeu(exe, sortie):
    """Traduit tout, et rend la liste des fonctions réellement définies."""
    pc, charge, taille = en_tete_exe(exe)
    chemins = unites_asm()
    recomp.load_symbols(*chemins)
    noms, table = fonctions(chemins)

    # Le point d'entrée n'a pas d'étiquette : il est écrit en données brutes
    # dans l'unité qui le contient. On le prend depuis l'en-tête, et on le
    # borne à la première fonction connue qui le suit.
    suivantes = sorted(a for a, _ in table.values() if a > pc)
    fin = suivantes[0] if suivantes else pc + 256
    table["_start"] = (pc, (fin - pc) // 4)
    recomp.SYMS[pc] = "_start"
    noms.insert(0, "_start")

    # Le corps du gestionnaire d'interruption du BIOS. On y entre par le
    # milieu de sa fonction : le prologue installe un contexte une fois pour
    # toutes, et le rejouer a chaque interruption effacait l'etat du pilote CD.
    # C'est le seul point d'entree du binaire qui ne soit pas une entree de
    # fonction, et il est donc declare ici plutot que devine.
    for nom, adresse in ENTREES_INTERNES.items():
        contenant = max((a, n) for a, n in table.values() if a <= adresse)
        reste = (contenant[0] + 4 * contenant[1] - adresse) // 4
        if reste <= 0:
            continue
        table[nom] = (adresse, reste)
        noms.append(nom)

    out = ['/* genere par tools/m0/build.py -- ne pas versionner */',
           '#include "rt.h"', '#include "gte.h"',
           "u32 psx_dispatch(u32,u32,u32,u32,u32,u32);"]
    definies, bouchons = [], []
    for nom in noms:
        adresse, n = table[nom]
        mots = recomp.words_from_exe(exe, adresse, n, load=charge, off=0x800)
        try:
            out.append(recomp.translate("psx_" + nom, adresse, mots))
        except recomp.Unsupported as e:
            # Une fonction que le traducteur refuse devient un bouchon qui se
            # signale. Le silence, ici, coute tres cher : c'est un bouchon muet
            # sur InitGeom qui a fait disparaitre la piste entiere pendant une
            # journee, cinq fonctions plus loin.
            bouchons.append((nom, str(e)))
            out.append('u32 psx_%s(u32 a, u32 b, u32 c, u32 d)\n'
                       '{ extern void stub_hit(const char *); '
                       'stub_hit("%s"); return 0; }' % (nom, nom))
        if nom not in ENTREES_INTERNES:
            definies.append((adresse, nom))
    open(sortie, "w").write("\n".join(out) + "\n")
    return definies, bouchons


def ecrire_table(definies, sortie):
    """La table adresse -> fonction, triée : le répartiteur la lit par
    dichotomie, et un appel indirect est fréquent."""
    definies = sorted(set(definies))
    out = ['/* genere par tools/m0/build.py -- ne pas versionner */',
           '#include "rt.h"']
    for _, nom in definies:
        out.append("u32 psx_%s(u32,u32,u32,u32);" % nom)
    out.append("const struct { u32 a; u32 (*f)(u32,u32,u32,u32); } PSX_FUNCS[] = {")
    for adresse, nom in definies:
        out.append("  {0x%08Xu, psx_%s}," % (adresse, nom))
    out.append("};")
    out.append("const int PSX_NFUNCS = %d;" % len(definies))
    open(sortie, "w").write("\n".join(out) + "\n")
    return len(definies)


def lire_cue(chemin):
    """Les pistes d'une feuille CUE : numero, type, fichier, secteur de debut.

    Les positions absolues ne sont pas ecrites dans la feuille quand chaque
    piste a son propre fichier : elles se deduisent en accumulant les longueurs,
    un secteur brut faisant 2352 octets. L'INDEX 01 donne le debut de la piste
    proprement dite, apres le silence de deux secondes que porte le fichier."""
    dossier = os.path.dirname(os.path.abspath(chemin))
    pistes = []
    fichier = None
    lba = 0
    numero = typ = None
    for ligne in open(chemin, encoding="utf-8", errors="replace"):
        l = ligne.strip()
        if l.startswith("FILE "):
            if fichier:
                lba += os.path.getsize(fichier) // 2352
            nom = l.split('"')[1] if '"' in l else l.split()[1]
            fichier = os.path.join(dossier, nom)
            if not os.path.exists(fichier):
                sys.exit("la feuille designe un fichier absent : " + fichier)
        elif l.startswith("TRACK "):
            parts = l.split()
            numero, typ = int(parts[1]), parts[2]
        elif l.startswith("INDEX 01") and fichier is not None:
            mm, ss, ff = (int(x) for x in l.split()[2].split(":"))
            decalage = (mm * 60 + ss) * 75 + ff
            pistes.append({"n": numero, "audio": typ == "AUDIO",
                           "fichier": fichier, "debut": lba + decalage,
                           "saut": decalage})
    return pistes


def ecrire_disque(iso, cue, sortie):
    """La description du disque : l'image des donnees, et les pistes audio."""
    if iso:
        secteurs = (os.path.getsize(iso) + 2047) // 2048
        chemin = os.path.abspath(iso)
    else:
        secteurs, chemin = 0, ""
    pistes = lire_cue(cue) if cue else []
    audio = [p for p in pistes if p["audio"]]
    lignes = ["/* genere par tools/m0/build.py -- ne pas versionner */",
              "struct cdfile { unsigned int lba, size; const char *path; };",
              "const struct cdfile CDFILES[] = { {0, 0, 0} };",
              "const int NCDFILES = 0;",
              'const char *CD_META = "%s";' % chemin.replace("\\", "\\\\"),
              "const unsigned int CD_META_SECTORS = %u;" % secteurs,
              "",
              "/* Les pistes audio. `debut` est leur secteur absolu sur le",
              "   disque, `saut` le silence que porte leur fichier. */",
              "struct cdtrack { unsigned int debut, longueur, saut; const char *fichier; };",
              "const struct cdtrack CDTRACKS[] = {"]
    for p in pistes:
        n = os.path.getsize(p["fichier"]) // 2352
        lignes.append('  {%u, %u, %u, "%s"},   /* piste %02d%s */'
                      % (p["debut"], n, p["saut"],
                         p["fichier"].replace("\\", "\\\\"),
                         p["n"], "" if p["audio"] else "  donnees"))
    lignes.append("};")
    lignes.append("const int NCDTRACKS = %d;" % len(pistes))
    open(sortie, "w").write("\n".join(lignes) + "\n")
    return secteurs, len(pistes), len(audio)


def sdl_drapeaux():
    """Les options de compilation de SDL2, ou None s'il n'est pas installe."""
    for outil in (["pkg-config", "--cflags", "--libs", "sdl2"],
                  ["sdl2-config", "--cflags", "--libs"]):
        try:
            r = subprocess.run(outil, capture_output=True, text=True)
            if r.returncode == 0 and r.stdout.strip():
                return r.stdout.split()
        except FileNotFoundError:
            continue
    return None


def main():
    p = argparse.ArgumentParser(description=__doc__,
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("exe", help="ta copie de PSX.EXE")
    p.add_argument("--iso", help="image de la piste de donnees du disque")
    p.add_argument("--cue", help="feuille CUE du disque, pour la musique")
    p.add_argument("--out", default=os.path.join(RACINE, "build", "m0"),
                   help="dossier de sortie (defaut : build/m0)")
    p.add_argument("--compile", action="store_true", help="compiler ensuite")
    p.add_argument("--cc", default="gcc")
    a = p.parse_args()

    os.makedirs(a.out, exist_ok=True)
    definies, bouchons = ecrire_jeu(a.exe, os.path.join(a.out, "game.c"))
    n = ecrire_table(definies, os.path.join(a.out, "table.c"))
    secteurs, npistes, naudio = ecrire_disque(a.iso, a.cue, os.path.join(a.out, "cdfiles.c"))
    open(os.path.join(a.out, "ram.c"), "w").write(
        "unsigned char RAM[0x200000];\nunsigned int g_sp;\n")

    print("%d fonctions traduites" % n)
    if bouchons:
        print("%d bouchons :" % len(bouchons))
        for nom, motif in bouchons:
            print("   %-24s %s" % (nom, motif))
    else:
        print("aucun bouchon")
    if a.iso:
        print("disque : %s, %d secteurs" % (a.iso, secteurs))
    else:
        print("disque : aucun (--iso absent) -- le jeu s'arretera au chargement")
    if npistes:
        print("pistes : %d dont %d audio" % (npistes, naudio))
    else:
        print("pistes : aucune (--cue absent) -- pas de musique")

    sources = [os.path.join(ICI, f)
               for f in ("main.c", "hw.c", "gpu.c", "gte.c", "video.c", "audio.c", "spu.c")]
    sources += [os.path.join(a.out, f) for f in ("game.c", "table.c", "cdfiles.c", "ram.c")]
    cmd = [a.cc, "-O1", "-w", "-fcommon", "-I", ICI,
           "-o", os.path.join(a.out, "m0")] + sources

    # SDL2 est facultatif : sans lui le banc ecrit des images sur disque et
    # lit un scenario, comme avant. Avec lui, une fenetre et un clavier.
    sdl = sdl_drapeaux()
    if sdl:
        cmd += ["-DAVEC_SDL"] + sdl
        print("SDL2 trouve : le jeu s'ouvrira dans une fenetre")
    else:
        print("SDL2 absent : pas de fenetre (images sur disque et scenario)")
        print("   sous Debian ou Ubuntu :  sudo apt install libsdl2-dev")
    if a.compile:
        print("compilation...")
        r = subprocess.run(cmd)
        if r.returncode:
            sys.exit(r.returncode)
        print("=> %s" % os.path.join(a.out, "m0"))
        print("   %s 90 %s" % (os.path.join(a.out, "m0"), a.exe))
    else:
        print("\n" + " ".join(cmd))


if __name__ == "__main__":
    main()
