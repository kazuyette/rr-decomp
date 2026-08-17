#!/usr/bin/env python3
"""Assemble les images du banc en une planche-contact.

Regarder une exécution image par image coûte cher et fait rater les
transitions, qui sont justement l'endroit où les défauts se logent. Une
planche montre trente images d'un coup et fait apparaître ce qu'une image
isolée ne dit pas : un écran qui ne change plus, une couleur qui dérive, un
retour en arrière qu'on n'attendait pas.

    python3 tools/m0/planche.py images/*.ppm -o planche.png -c 6

Sans dépendance : les PPM sont lus tels quels et le PNG écrit à la main.
"""
import argparse
import struct
import sys
import zlib


def lire_ppm(chemin):
    d = open(chemin, "rb").read()
    p = d.split(b"\n", 3)
    if p[0] != b"P6":
        raise ValueError(chemin + " n'est pas un PPM binaire")
    l, h = (int(x) for x in p[1].split())
    return l, h, p[3]


def ecrire_png(chemin, largeur, hauteur, pixels):
    brut = b"".join(b"\x00" + pixels[y * largeur * 3:(y + 1) * largeur * 3]
                    for y in range(hauteur))

    def bloc(genre, contenu):
        corps = genre + contenu
        return (struct.pack(">I", len(contenu)) + corps
                + struct.pack(">I", zlib.crc32(corps)))

    open(chemin, "wb").write(
        b"\x89PNG\r\n\x1a\n"
        + bloc(b"IHDR", struct.pack(">IIBBBBB", largeur, hauteur, 8, 2, 0, 0, 0))
        + bloc(b"IDAT", zlib.compress(brut, 6))
        + bloc(b"IEND", b""))


def main():
    p = argparse.ArgumentParser()
    p.add_argument("images", nargs="+")
    p.add_argument("-o", "--sortie", default="planche.png")
    p.add_argument("-c", "--colonnes", type=int, default=6)
    p.add_argument("-r", "--reduction", type=int, default=2,
                   help="diviseur de taille (2 par defaut)")
    a = p.parse_args()

    vignettes = []
    for chemin in a.images:
        try:
            l, h, px = lire_ppm(chemin)
        except Exception as e:
            sys.stderr.write("%s : %s\n" % (chemin, e))
            continue
        vl, vh = l // a.reduction, h // a.reduction
        v = bytearray(vl * vh * 3)
        for y in range(vh):
            src = (y * a.reduction) * l * 3
            for x in range(vl):
                i = src + (x * a.reduction) * 3
                j = (y * vl + x) * 3
                v[j:j + 3] = px[i:i + 3]
        vignettes.append((vl, vh, bytes(v)))

    if not vignettes:
        sys.exit("aucune image lisible")

    vl, vh = vignettes[0][0], vignettes[0][1]
    cols = min(a.colonnes, len(vignettes))
    lignes = (len(vignettes) + cols - 1) // cols
    L, H = cols * vl, lignes * vh
    planche = bytearray(L * H * 3)
    for n, (l, h, px) in enumerate(vignettes):
        cx, cy = (n % cols) * vl, (n // cols) * vh
        for y in range(min(h, vh)):
            d = ((cy + y) * L + cx) * 3
            s = y * l * 3
            planche[d:d + min(l, vl) * 3] = px[s:s + min(l, vl) * 3]
    ecrire_png(a.sortie, L, H, bytes(planche))
    print("%s : %d images, %d par %d" % (a.sortie, len(vignettes), L, H))


if __name__ == "__main__":
    main()
