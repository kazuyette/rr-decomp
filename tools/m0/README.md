# L'exécutable natif

Ce dossier contient l'environnement d'exécution d'une **recompilation
statique** de Ridge Racer : le code MIPS du jeu est traduit mécaniquement en C
par `tools/recomp.py`, et tourne sur un modèle du matériel écrit ici. Le but
n'est pas de faire un émulateur — c'est d'avoir un jalon qui démarre et qui
progresse, et dans lequel chaque fonction décompilée pourra ensuite remplacer
sa jumelle traduite, une par une, sans jamais casser le tout.

Le code du jeu lui-même est **généré** depuis ta propre copie de `PSX.EXE` et
n'est pas versionné, comme le reste du désassemblage.

## Construire et lancer

```sh
cp /path/to/PSX.EXE .
make setup                                    # splat -> asm/
python3 tools/m0/regen.py.example             # -> game.c  (adapter les chemins)
gcc -O1 -w -fcommon -o m0 \
    tools/m0/main.c tools/m0/hw.c tools/m0/gpu.c tools/m0/gte.c \
    game.c table.c cdfiles.c
./m0 90                                       # 90 secondes
```

`cdfiles.c` décrit ton disque : le fichier image pour les métadonnées ISO et
un fichier extrait par entrée du répertoire. Voir `cdfiles.c.example`.

Les images sont écrites en PPM dans le dossier courant, une toutes les cent
tables d'affichage.

## Les fichiers

| | |
|---|---|
| `rt.h` | La mémoire : 2 Mo de RAM, le bloc-notes de 1 Ko, l'aiguillage vers les registres. Et la base de temps, cadencée sur les accès mémoire — la seule chose que du code qui tourne ne peut pas s'abstenir de faire. |
| `hw.c` | Le lecteur CD, les canaux DMA 2, 3 et 6, les interruptions, le journal des registres. |
| `gpu.c` | Le rastériseur : mémoire vidéo 1024×512, polygones plats, dégradés et texturés, rectangles et sprites, traits, transferts dans les deux sens, palettes 4 et 8 bits, fenêtre de texture, semi-transparence dans ses quatre modes. Logiciel, parce que ce qu'on cherche à établir est la fidélité, pas la vitesse. |
| `gte.c` | Le coprocesseur géométrique, vérifié contre une seconde implémentation indépendante (`gte_check.py`, 11 600 comparaisons, 29 encodages). |
| `main.c` | Le chargeur, l'aiguillage des appels indirects, les appels BIOS, la manette. |

## La manette

Le BIOS ne lit pas la manette à la demande : il remplit un tampon que le jeu
consulte quand il veut. On l'alimente depuis un **scénario** écrit d'avance,
pour que deux exécutions donnent la même image :

```sh
MANETTE="60000:start 63000: 90000:start 93000: 140000:start 143000: 170000:croix" ./m0 180
```

Chaque terme est `instant:touches`, l'instant compté en battements de retour de
balayage ; un instant sans touche relâche tout. Les noms reconnus : `start`,
`select`, `haut`, `bas`, `gauche`, `droite`, `croix`, `rond`, `triangle`,
`carre`, `l1`, `r1`.

Ce scénario-là traverse l'écran-titre, le menu, et lance la course.

## Où en est-on

| jalon | état |
|---|---|
| M0 — le jeu démarre et imprime son propre journal | ✅ |
| M1 — il lit son disque et émet ses primitives | ✅ |
| M2 — l'image : écran de chargement, écran-titre | ✅ |
| M3 — la piste : la démonstration tourne | ✅ |
| M4 — la manette : menu et course | ✅ |
| M5 — le son | ✗ (`ss_init error` : le SPU n'est pas modélisé) |
| M6 — la vitesse : GP0 vers OpenGL | ✗ |

## Ce que ce banc a appris au reste du projet

Les défauts trouvés ici sont documentés un par un dans
[`RECOMP_NOTES.md`](../../RECOMP_NOTES.md). Le motif qui revient, et qui vaut
d'être retenu :

> **Un bouchon silencieux ne casse pas là où il est.**

`InitGeom` était remplacée par un bouchon parce qu'elle contient une unique
instruction COP0. Elle règle aussi ZSF3 et ZSF4, les facteurs qui convertissent
une profondeur en indice de table d'affichage. Sans eux, chaque polygone
recevait la profondeur zéro, et le jeu — qui jette ce qui tombe à l'indice zéro
— jetait la piste entière. Le symptôme, cinq fonctions plus loin : une image
sans route.

Le même motif, en trois autres exemplaires : un `jr` de table de saut envoyé au
répartiteur global, qui coupait le gestionnaire d'interruption juste avant son
acquittement ; un `strcpy` du BIOS non implémenté, qui rendait zéro sans rien
copier et faisait conclure « File not found » à un jeu qui avait lu son disque
correctement ; et un bit de sens de DMA ignoré, qui poussait le contenu de la
pile dans le GPU.
