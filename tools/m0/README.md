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
make setup                                          # splat -> asm/
python3 tools/m0/build.py PSX.EXE --iso data.iso --compile
./build/m0/m0 90 PSX.EXE
```

Il te faut deux choses tirées de ta propre copie du jeu : `PSX.EXE`, et une
image de la **piste de données** en secteurs de 2048 octets. Si tu pars d'une
image BIN/CUE (2352 octets par secteur, ce que le lecteur lit vraiment) :

```sh
python3 tools/m0/bin2iso.py RidgeRacer.bin data.iso
```

`PSX.EXE` se copie ensuite depuis l'image montée, ou s'extrait avec n'importe
quel outil ISO 9660. Sans `--iso`, le jeu démarre puis s'arrête au chargement.

### Ce qu'il faut avoir installé

Python 3 et un compilateur C, rien d'autre : `tools/setup.py` installe splat
lui-même au premier appel. Sous Windows, passe par WSL — le banc utilise
`getenv` et des chemins POSIX.

`build.py` recalcule la liste des fonctions à chaque construction, à partir du
désassemblage — rien n'est figé dans un fichier qui se périmerait au premier
symbole renommé. Il annonce le nombre de fonctions traduites et, s'il en reste,
les **bouchons**, avec leur motif.

Les images sortent en PPM, une toutes les cent tables d'affichage, dans le
dossier `IMAGES` (le dossier courant par défaut) :

```sh
IMAGES=/tmp/images ./build/m0/m0 90 PSX.EXE
python3 tools/m0/ppm2png.py /tmp/images/*.ppm
```

Par défaut, la sortie tient en quelques lignes : ce que le jeu imprime
lui-même, puis un état des lieux à la fin. `VERBEUX=1` ajoute le journal des
appels BIOS et le dialogue avec le lecteur — c'est un outil de mise au point,
qui servait à trouver où le démarrage s'arrêtait. Maintenant qu'il ne s'arrête
plus, il ne fait que cacher le reste.

## Le temps

Une recompilation statique n'a pas d'horloge. Le code traduit n'est plus
cadencé par rien : il s'exécute à la vitesse de la machine hôte, et rien ne
relie une instruction à un cycle. Il faut donc en fabriquer une, et le choix
n'est pas neutre.

Elle bat ici sur les **accès mémoire** (`TICK()` dans `rt.h`), parce que c'est
la seule chose que du code qui tourne ne peut pas s'abstenir de faire — une
horloge cadencée sur les accès matériel ou sur les appels s'arrête précisément
pendant qu'une boucle d'attente tourne en mémoire.

Restait un cas que ça ne couvre pas : `VSync` attend en interrogeant le
compteur du BIOS, encore et encore, sans rien faire d'autre. Cette attente ne
fait presque pas avancer une horloge cadencée sur le travail — le jeu y brûlait
**3,2 milliards d'appels pour trois minutes**. Demander l'heure en boucle est
pourtant l'aveu qu'on n'a rien à faire : le temps avance donc à chaque
demande. C'est la détection de boucle d'attente des émulateurs sous sa forme la
plus simple, celle où le code le dit lui-même. Dix fois plus d'images par
seconde, sans toucher à la base de temps du reste.

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
