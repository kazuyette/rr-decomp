#!/usr/bin/env python3
"""Convertit les images du banc en PNG, sans dépendance.

Le banc écrit des PPM parce que c'est le format qu'on peut produire en C sans
bibliothèque -- une ligne d'en-tête et les octets. Personne ne veut regarder du
PPM, d'où ce convertisseur : zlib et struct suffisent à écrire un PNG valide,
et la bibliothèque standard les fournit tous les deux.

    python3 tools/m0/ppm2png.py build/m0/*.ppm
"""
import struct
import sys
import zlib


def convertir(source, destination):
    donnees = open(source, "rb").read()
    parties = donnees.split(b"\n", 3)
    if parties[0] != b"P6":
        raise ValueError(source + " n'est pas un PPM binaire")
    largeur, hauteur = (int(x) for x in parties[1].split())
    pixels = parties[3]
    # Le PNG veut un octet de filtre en tete de chaque ligne ; zero veut dire
    # « aucun filtre », ce qui compresse un peu moins bien et evite d'ecrire un
    # predicteur pour rien.
    brut = b"".join(b"\x00" + pixels[y * largeur * 3:(y + 1) * largeur * 3]
                    for y in range(hauteur))

    def bloc(genre, contenu):
        corps = genre + contenu
        return (struct.pack(">I", len(contenu)) + corps
                + struct.pack(">I", zlib.crc32(corps)))

    png = (b"\x89PNG\r\n\x1a\n"
           + bloc(b"IHDR", struct.pack(">IIBBBBB", largeur, hauteur, 8, 2, 0, 0, 0))
           + bloc(b"IDAT", zlib.compress(brut, 6))
           + bloc(b"IEND", b""))
    open(destination, "wb").write(png)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        sys.exit(__doc__)
    for chemin in sys.argv[1:]:
        sortie = chemin[:-4] + ".png" if chemin.endswith(".ppm") else chemin + ".png"
        convertir(chemin, sortie)
        print(sortie)
