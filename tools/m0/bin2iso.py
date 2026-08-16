#!/usr/bin/env python3
"""Extrait la piste de données d'une image BIN/CUE en secteurs de 2048 octets.

Le banc natif sert les secteurs du disque tels quels et attend donc une image
« ISO » : 2048 octets utiles par secteur, rien d'autre. Une image BIN en fait
2352, parce qu'elle garde ce que le lecteur lit vraiment -- douze octets de
synchronisation, quatre d'en-tête, puis les données, puis la correction
d'erreur. Ce script jette l'enveloppe et garde la lettre.

    python3 tools/m0/bin2iso.py RidgeRacer.bin data.iso

Il s'arrête à la première piste audio : celles-ci n'ont ni en-tête ni structure
de secteur, et les inclure produirait du bruit là où le jeu attend son système
de fichiers. Si ton image est déjà en 2048, il le dit et ne fait rien.
"""
import sys

SYNC = b"\x00\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x00"


def convertir(source, destination):
    brut = open(source, "rb").read()
    if len(brut) % 2352 != 0:
        if len(brut) % 2048 == 0:
            sys.exit("%s est deja en secteurs de 2048 octets -- rien a faire"
                     % source)
        sys.exit("%s ne fait un compte rond ni en 2352 ni en 2048 octets"
                 % source)

    sortie = open(destination, "wb")
    gardes = 0
    for i in range(0, len(brut), 2352):
        secteur = brut[i:i + 2352]
        if secteur[:12] != SYNC:
            # Plus de motif de synchronisation : on est entre dans l'audio.
            break
        mode = secteur[15]
        if mode == 1:                 # MODE1 : donnees a l'octet 16
            sortie.write(secteur[16:16 + 2048])
        elif mode == 2:               # MODE2/FORM1 : huit octets de sous-en-tete
            sortie.write(secteur[24:24 + 2048])
        else:
            break
        gardes += 1
    sortie.close()
    print("%s : %d secteurs, %d octets" % (destination, gardes, gardes * 2048))


if __name__ == "__main__":
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    convertir(sys.argv[1], sys.argv[2])
