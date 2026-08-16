# Le renderer : ce qui a été identifié

*Lecture à la main, août 2026. Chaque point ci-dessous est lu dans les
instructions, pas déduit d'une ressemblance.*

## Quatre fonctions nommées

| adresse | nom | preuve |
|---|---|---|
| `0x8004617C` | `SetDrawMode` | écrit `len = 2` dans l'octet 3 du tag, puis deux mots : `_get_mode(dfe, dtd, tpage)` et `_get_tw(tw)`. Deux commandes GP0, dans cet ordre, juste avant `SetDrawEnv`. |
| `0x80046430` | `_get_mode` | construit `0xE1……` : base `0xE1000200` ou `0xE1000800` selon `dtd`, masque la tpage à `0x1FF` ou `0x27FF` selon le drapeau global `D_80077378`, pose le bit 10 ou 12 selon `dfe`. |
| `0x800465DC` | `_get_tw` | construit `0xE2……` : `(x>>3)<<10 | (y>>3)<<15 | ((-w & 0xFF)>>3) | (((-h & 0xFF)>>3)<<5)`, et rend 0 pour un `RECT *` nul. |
| `0x80043738` | `negate_rot_row0` | `cfc2` des registres de contrôle 0 et 1, négation de R11, R12 et R13 — et **pas** de R21 —, `ctc2` en retour. C'est la première ligne de la matrice de rotation, donc l'axe X du résultat. |

`SetDrawMode` était déjà convertie et matchée (dans `x_c257_00.c`) : ce qui
manquait était son nom, et il vaut pour ses 67 sites d'appel.

## Le drapeau miroir est à l'offset 0x24 du contexte de rendu

Deux fonctions indépendantes lisent le même champ et en tirent la même
conséquence :

`func_80033FBC` (et une quinzaine d'autres bâties sur le même moule) :

```
    lw   $v0, 0x24($s1)        ; s1 = 2e argument = le contexte
    beqz $v0, sans_miroir
    jal  negate_rot_row0       ; X inversé dans la matrice courante
    jal  func_800437AC         ; le vrai travail
    jal  negate_rot_row0       ; remise en état
```

`func_8004006C` (`rtpt` + `nclip`, le transform-et-cull) :

```
    lw   $v0, 0x24($a1)
    bnez $v0, inverse
    mfc2 $v0, $24              ; MAC0 = aire signée sortie de nclip
    bgtz $v0, garder           ; sens normal
inverse:
    mfc2 $v0, $24
    neg  $v0, $v0              ; sens inversé
    bgtz $v0, garder
```

Une réflexion selon X inverse le sens de parcours des polygones ; il faut donc
inverser aussi le test de face arrière, sinon tout le décor se retourne. Les
deux moitiés de cette conséquence sont écrites dans deux fonctions distinctes,
et elles s'accordent. C'est le **mode miroir** du jeu.

Conséquences pratiques :

- le champ `0x24` du contexte de rendu s'appelle `mirror` et rien d'autre ;
- pour le portage, ce drapeau ne se traduit pas par un `scale(-1,1,1)` naïf :
  il faut aussi basculer le sens de winding, exactement comme ici ;
- `func_800437AC` est le corps réel du dessin, appelé dans les deux branches —
  c'est lui qu'il faut lire ensuite, pas le nid de wrappers.

## Ce que ça ne dit pas

Rien sur le placement des sections de `MAP.RRM`. La grappe de quatre fonctions
contiguës (`0x8003486C`, `0x80034EFC`, `0x80035638`, `0x80035EAC`) reste le
meilleur candidat, mais le motif miroir traverse toute la région : la moitié
des appels rencontrés jusqu'ici sont des enveloppes de ce genre, et il faut les
franchir avant d'atteindre la transformation.

## Note d'environnement

La chaîne de compilation (`/opt/psx-gcc`, `/opt/psx-gcc257`) ne survit pas au
recyclage du conteneur. La reconstruire depuis les sources sur une Ubuntu
récente demande deux correctifs que le `Dockerfile` (basé sur focal) n'a pas
besoin de porter :

- **GCC 2.7.2** : `xgcc` ne se lie plus, `sys_nerr` ayant disparu de la glibc.
  Lier avec un objet supplémentaire contenant `int sys_nerr = 132;`.
- **GCC 2.5.7** : `cc1` ne se lie plus, le C moderne étant `-fno-common` par
  défaut (`local_vars_size`, `byte_mode`, `word_mode` doublement définis).
  Lier avec `-Wl,--allow-multiple-definition`.

Les deux correctifs ne touchent que l'édition de liens de l'hôte, jamais la
génération de code : les 944 matchs sont retombés à l'identique après
reconstruction.

## Le bloc des initialiseurs de primitives libgpu

Vingt-deux fonctions contiguës de `0x80047B48` à `0x80047D1C`, chacune de cinq
ou huit instructions, toutes bâties sur le même geste : écrire une longueur
dans l'octet 3 du tag et un code de commande GP0 dans l'octet 7. C'est la
signature de `setPolyF4` et de toute sa fratrie, et une plage contiguë de
fonctions faisant exactement la même chose, bornée par du code qui ne la fait
pas, est une **unité de traduction d'origine** — la troisième identifiée par
contiguïté après les trampolines BIOS et les enveloppes GTE.

| adresse | longueur | code GP0 | nom |
|---|---|---|---|
| `0x80047B48` | 4 | `0x20` | `SetPolyF3` |
| `0x80047B5C` | 7 | `0x24` | `SetPolyFT3` |
| `0x80047B70` | 6 | `0x30` | `SetPolyG3` |
| `0x80047B84` | 9 | `0x34` | `SetPolyGT3` |
| `0x80047B98` | 5 | `0x28` | `SetPolyF4` |
| `0x80047BAC` | 9 | `0x2C` | `SetPolyFT4` |
| `0x80047BC0` | 8 | `0x38` | `SetPolyG4` |
| `0x80047BD4` | 12 | `0x3C` | `SetPolyGT4` |
| `0x80047BE8` | 3 | `0x74` | `SetSprt8` |
| `0x80047BFC` | 3 | `0x7C` | `SetSprt16` |
| `0x80047C10` | 4 | `0x64` | `SetSprt` |
| `0x80047C24` | 2 | `0x68` | `SetTile1` |
| `0x80047C38` | 2 | `0x70` | `SetTile8` |
| `0x80047C4C` | 2 | `0x78` | `SetTile16` |
| `0x80047C60` | 3 | `0x60` | `SetTile` |
| `0x80047C74` | 3 | `0x02` | `SetFill` |
| `0x80047C88` | 3 | `0x40` | `SetLineF2` |
| `0x80047C9C` | 4 | `0x50` | `SetLineG2` |
| `0x80047CB0` | 5 | `0x48` | `SetLineF3` |
| `0x80047CC4` | 7 | `0x58` | `SetLineG3` |
| `0x80047CE4` | 6 | `0x4C` | `SetLineF4` |
| `0x80047D04` | 9 | `0x5C` | `SetLineG4` |

Les codes des polygones, des sprites et des tuiles sont ceux du matériel et se
lisent dans n'importe quelle documentation du GPU. Les quatre lignes demandent
un pas de plus : `0x4C` et `0x5C` posent le bit `0x04`, **que le GPU ignore**.
Le matériel ne connaît que `0x48` pour une polyligne plate et `0x58` pour une
polyligne dégradée ; c'est libgpu qui se sert de ce bit libre comme marqueur
interne pour distinguer la variante à trois points de celle à quatre. Les
longueurs le confirment sans ambiguïté : 5 et 6 pour les plates, 7 et 9 pour
les dégradées, avec le terminateur `0x55555555` écrit au mot correspondant —
`0x18` pour la longueur 6, `0x1C` pour la 7, `0x24` pour la 9.

Ces vingt-deux noms sont acquis sans SDK, en lisant deux constantes par
fonction et une table de commandes matérielles.
