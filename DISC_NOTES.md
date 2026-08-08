# Notes sur le disque source (Japan)

Source : image BIN/CUE, 13 pistes (1 piste data MODE2/2352 + 12 pistes audio CDDA - bande son redbook).

## Volume ISO9660 (piste 1)

- System id: PLAYSTATION
- Volume id: RIDGERACER
- Publisher: NAMCO LIMITED
- Dates fichiers : 6-10 nov. 1994 (sortie JP le 3 dec. 1994 - build tres proche du master)
- Pas de SYSTEM.CNF sur le disque -> boot implicite sur PSX.EXE (comportement des tout premiers titres PS1)

## Fichiers racine

| Fichier | Taille | Role probable |
|---|---|---|
| PSX.EXE | 425 984 o | Executable principal |
| IDX.HED | 2 048 o | Table d'index (format maison, non documente) |
| MAP.RRM | 271 548 o | Donnees de circuit/collision |
| OBJ.RRO | 445 348 o | Modeles 3D des objets |
| RR.VH | 32 288 o | En-tetes sons (VAB header, format Sony standard) |
| RR.VB | 491 056 o | Donnees sons (VAB body) |
| TEX0-TEX4.TMS | 699 908 / 197 128 / 140 704 / 109 948 / 14 996 o | Banques de textures (format probablement maison, pas un .TIM standard) |

## En-tete PSX.EXE

- Magic : PS-X EXE
- Region : "Sony Computer Entertainment Inc. for Japan area"
- Entry point (pc0) : 0x8003FA9C
- gp0 : 0xEF7E023F
- .text : adresse 0x80010000, taille 0x67800
- Pas de section data/bss declaree dans l'en-tete (le crt0 s'en charge au runtime, voir GHIDRA_PROGRESS.md)

## Prochaines etapes

- Documenter le format IDX.HED (probablement un index de secteurs pointant vers des assets streames depuis le CD)
- Convertir RR.VH/RR.VB (VAB Sony standard, outils existants dans l'ecosysteme PS1 homebrew)
- Reverse le format TEXx.TMS pour visualiser les textures
