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
