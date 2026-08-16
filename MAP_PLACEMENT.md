# Le placement des sections : résolu

*Question ouverte depuis le début du projet. `MAP_RRM_FORMAT.md` la listait sous
« Not found: any per-section coordinate transform », et `TRACK_SPINE_FORMAT.md`
concluait qu'il n'y avait « rien à placer ». Les deux se trompaient, et la
réponse était dans un fichier qu'on avait mis de côté.*

---

## La réponse en une phrase

**`IDX.HED` est une grille 32 × 32 de cellules de 2048 unités monde qui associe
à chaque cellule un numéro de section de `MAP.RRM`.** La section est posée à
l'origine de sa cellule ; il n'y a pas de rotation, seulement une translation.

## Comment on le sait

Ce n'est pas une inférence sur les données. C'est lu dans `func_800437AC`, le
corps réel du dessin (celui derrière les enveloppes de mode miroir) :

```
    lw   $v0, 0xC($a2)          ; index de section
    bltz $v0, .section_suivante ; -1 = cellule vide
    lw   $t0, 0x0($a2)          ; \
    lw   $t1, 0x4($a2)          ;  > la translation
    lw   $t2, 0x8($a2)          ; /
    ...  neg $t0 si miroir
    ctc2 $t0, $5                ; TRX  \
    ctc2 $t1, $6                ; TRY   > vecteur de translation du GTE
    ctc2 $t2, $7                ; TRZ  /
    lw   $t0, 0x4($a1)          ; table des sections
    sll  $v1, $v0, 5            ; index * 32
    lh   $t3, 0xC($t2)          ; nombre de faces
    lw   $t1, 0x0($t2)          ; pointeur sur les faces
```

Le troisième argument est donc un **tableau de placements de 16 octets** :
`{s32 x, s32 y, s32 z, s32 index}`. Et son constructeur, `func_80012C14`,
dit d'où viennent ces quatre champs :

```
    cellX = (D_801D9068 + 0x400) >> 11      ; caméra -> cellule, pas de 2048
    cellZ = (D_801D9070 + 0x400) >> 11
    dir   = (D_801D907C >> 8) & 0xF         ; 16 directions de caméra
    pour i de 0 à 63 :
        dx = (s8) D_8005944C[dir*256 + i*2]     ; table d'ordre de parcours
        dz = (s8) D_8005944D[dir*256 + i*2]
        x = cellX + dx ; z = cellZ + dz
        si x >= 32 ou z >= 32 (non signé) -> index = -1
        si func_80015BC4(x, z, ...) == 0   -> index = -1     ; test de visibilité
        index = ((s16 *) D_801D82D0)[z*32 + 30 - x]
        D_801D82D8[z] |= 1 << x                              ; bitmap 32x32 de cellules vues
        v = (x << 11 - camX_frac, -camY_frac, z << 11 - camZ_frac)
        ApplyMatrix(D_801E91F0, &v, &out)                    ; func_8004315C
        placement = (out.x << 2, out.y << 2, out.z << 2)
```

Soixante-quatre cellules par image, choisies autour de la caméra dans un ordre
qui dépend de sa direction. `D_801D82D0` pointe sur la table lue depuis
`IDX.HED`.

## La vérification

`IDX.HED` fait 2048 octets = **1024 `u16` = exactement 32 × 32**. Il contient
**258 entrées non-`0xFFFF`**, et `MAP.RRM` contient **258 sections**. La
correspondance cellule ↔ section est une bijection : chacune des 258 sections a
exactement une cellule, aucune n'en a zéro ou deux.

Test indépendant : les 256 nœuds de la polyligne du circuit 0, convertis en
cellules (`monde >> 11`), tombent sur **79 cellules distinctes, et les 79 sont
occupées**. Zéro exception. Aucune des cinq autres orientations d'indexation
essayées ne dépasse 46 sur 79.

Test visuel : en posant chaque section à `cellule × 2048` et en dessinant les
quads de type B vus de dessus, le ruban de route suit la polyligne du circuit.
C'est l'image `map_road_placed.png`.

## L'échelle

La géométrie locale de `MAP.RRM` est en **unités monde × 4**. Le constructeur
décale la translation de 2 bits vers la gauche (`sll $v0, $v0, 2`) avant de
l'écrire, donc le vecteur de translation du GTE — et par conséquent les sommets
qui s'y ajoutent — vit dans un espace quatre fois plus fin que la polyligne.
Une cellule mesure donc 8192 unités de géométrie.

C'est la première tentative de rendu qui l'a montré : à l'échelle 1, les
sections se recouvraient massivement et le tracé disparaissait sous la masse.

## Un point de convention resté ouvert

Le code calcule l'index avec `z*32 + 30 - x`. Empiriquement, ce qui aligne la
polyligne sur la grille est `z*32 + x`. Les deux se réconcilient si l'axe X de
la caméra (`D_801D9068`) est stocké dans le sens inverse de celui de la
polyligne, avec `x_caméra = 30 − x_polyligne`. Ce serait cohérent avec les
autres inversions de X déjà rencontrées — `negate_rot_row0`, le
`0x800 − angle` des bords de route, le global `D_801733A0` du mode miroir —
mais ce n'est pas encore lu dans une fonction, donc ça reste une hypothèse.

## Ce que ça corrige dans la documentation existante

`TRACK_SPINE_FORMAT.md` affirme que « MAP.RRM ne contient pas de transformation
de placement parce qu'il n'y a rien à placer », le circuit étant habillé le long
de la polyligne. La première moitié est vraie — la transformation n'est pas dans
`MAP.RRM` —, la seconde est fausse : les sections sont bien placées, par
`IDX.HED`.

`MAP_RRM_FORMAT.md` posait la question sous « Open items » : « whether a
per-section world-space transform exists in a file not yet examined ». Oui, et
c'était `IDX.HED`.

Enfin, l'hypothèse « grille spatiale » avait été écartée dans une session
antérieure comme « éliminée quantitativement ». Elle était juste. L'élimination
portait sur une lecture des seules données de `MAP.RRM` ; la grille n'y est pas.
C'est le troisième cas de ce projet où lire la fonction consommatrice donne en
dix minutes ce que l'analyse statistique du fichier avait déclaré impossible.

---

# Les trois types d'enregistrement, et les trous

*Suite directe de ce qui précède : l'image de contrôle laissait des trous noirs
sous l'axe du circuit, et `MAP_RRM_FORMAT.md` portait les types A et C comme
« candidat murs de dévers, non confirmé ».*

## Le décalage d'une cellule

Premier acquis, et il corrige le rendu précédent. Les sommets locaux ne sont pas
centrés sur l'origine de la section : X va de −8192 à 0, Z de 0 à +8192
(médianes −4211 et +3827, largeur médiane 9140 pour une cellule de 8192).
L'origine d'une section est donc le **coin +X/−Z de sa cellule**, pas son
centre.

La prédiction est vérifiable : il faut décaler la géométrie d'une cellule
entière en X pour qu'elle s'aligne sur la polyligne. Mesuré — la couverture de
l'axe passe de **165/256 à 200/256**, et l'optimum tombe exactement sur
`+8192`, la valeur prédite. Ce n'est pas un ajustement libre : le décalage
n'avait qu'une valeur admissible et c'est celle-là.

## Ce que sont les trois types

| type | n | sections | ΔY médian | empreinte fine en plan | tpages |
|---|---|---|---|---|---|
| A | 622 | 79 | 475 | 7 % | 8 |
| B | 5 420 | 207 | 116 | 12 % | 12 |
| C | 695 | 23 | 24 | 3 | 3 |

**Aucun des trois n'est un mur.** L'hypothèse « murs de dévers » portée par
`MAP_RRM_FORMAT.md` pour le type A est réfutée : un mur vertical se projette en
plan comme un trait, et seuls 7 % des quads de type A ont une empreinte fine.
Ce sont des surfaces inclinées — ΔY médian 475 contre 116 pour le type B —,
donc des talus et des dévers, pas des parois.

Le type C est l'élément le plus localisé du fichier : **23 sections sur 258,
trois pages de texture**, et un ΔY médian de 24 qui en fait la plus plate des
trois. Sur la carte, il n'apparaît qu'aux sorties de courbe du quart
nord-ouest. Un élément de circuit particulier à cet endroit — dégagement,
sable, ou surface du tunnel — reste à trancher en lisant `func_80034050`, la
seconde passe de dessin, qui prend le même tableau de placements.

## Et les trous

Ils ne sont pas ce qu'ils avaient l'air d'être. Après correction du décalage,
**199 des 256 nœuds** de l'axe du circuit 0 tombent sur un quad de type B. Pour
les 57 restants, le quad le plus proche est à **9 % d'une demi-largeur de route**
(médiane, mesurée perpendiculairement au cap du nœud).

C'est décisif dans un sens qui n'était pas celui attendu : si le revêtement
n'était pas dans `MAP.RRM` — s'il était habillé le long de la polyligne au
moment du rendu, comme le supposait `TRACK_SPINE_FORMAT.md` — le couloir libre
autour de l'axe ferait une demi-largeur, pas neuf pour cent. **Les trous sont
des lacunes ponctuelles, pas un couloir.** Le revêtement est bien dans le
fichier.

Ce qui reste à expliquer, c'est ces 57 lacunes elles-mêmes. La piste la plus
probable est la convention d'axe X restée ouverte plus haut : le code indexe en
`30 − x`, une **réflexion**, là où l'empirique donne `x`, une translation. Les
deux coïncident sur une plage de X limitée et divergent ailleurs — ce qui
produirait exactement une couverture excellente sur une moitié de la carte et
trouée sur l'autre. Une réflexion globale appliquée aux deux jeux de données à
la fois est inobservable par ce test ; il faudra la lire dans le code qui écrit
`D_801D9068`, pas la mesurer.

## Une note d'orientation, pour les rendus de contrôle

Les premières images de contrôle de cette page étaient dessinées avec `+Z` vers
le haut de l'image. C'est faux, et c'est une réflexion, pas un cadrage.

Le PSX travaille en **Y descendant** : X à droite, Y vers le bas, Z vers
l'avant. Une vue de dessus regarde dans la direction `+Y` ; en posant la droite
de l'écran sur `+X`, le haut de l'écran vaut `Y × X = −Z`, donc **`+Z` descend
à l'écran**. Dessiner `hauteur − z` donne la carte vue de dessous, soit son
miroir.

Ça ne change aucune des mesures de cette page — une réflexion globale préserve
la bijection, la couverture et les distances — et ça ne résout pas la question
d'axe restée ouverte, qui porte sur X et non sur Z. Mais toute image de
contrôle produite ici doit sortir avec `+Z` vers le bas, sans quoi on compare
une carte à son reflet.

## Correction : le type C est un tunnel

Le paragraphe ci-dessus décrivait le type C comme « des surfaces plates, un
élément de circuit particulier à trancher ». C'était insuffisant, et il a fallu
lire les quads bruts plutôt que leurs statistiques. La section 156, quatre
enregistrements :

```
(-8195,-655,6763)(-6128,-655,6763)(-8195,-655,8930)(-6128,-655,8930)   Y constant -655
(-6128,   0,7857)(-6128,   0,6774)(-8195,   0,7857)(-8195,   0,6774)   Y constant 0
(-6148,-661,8930)(-6148,-661,6763)(-6148,   6,8930)(-6148,   6,6763)   X constant -6148
(-8175,-661,6763)(-8175,-661,8930)(-8175,   6,6763)(-8175,   6,8930)   X constant -8175
```

Un sol, un plafond 655 unités plus haut, deux parois verticales. **Une boîte.**
Les 23 sections de type C forment deux couloirs de cellules contiguës —
`x = 3..6` sur `z = 13..19`, et `x = 11..13` sur `z = 13..16` — et l'axe du
circuit traverse **16 de ces 23 cellules**. Ce sont les tunnels.

Ce qui invalide aussi la phrase « aucun des trois n'est un mur » écrite plus
haut : 10,8 % des quads de type C sont verticaux, contre 6,2 % pour B. Le test
d'empreinte fine en plan était dilué par les 57,7 % de sols et de plafonds, qui
sont horizontaux par construction. Une proportion agrégée sur un type qui
mélange trois rôles géométriques ne mesure rien ; c'est en lisant quatre
enregistrements consécutifs d'une même section que la structure apparaît.

Le type A reste sans lecture équivalente : 5,8 % de verticales, 6,1 %
d'horizontales, donc presque tout est incliné. Talus et dévers restent
l'hypothèse, cette fois sans réfutation à opposer.

## Ce que le décalage d'une cellule veut dire exactement

Deux tests semblaient se contredire : la couverture de l'axe préfère un
décalage de `+8192` en X, tandis que l'appartenance des cellules de tunnel à
l'axe préfère l'absence de décalage (16 contre 12). Ils ne portent pas sur la
même chose et ils s'accordent.

L'indexation `z*32 + x` est correcte **sans décalage** : la cellule `(3,13)`
est bien celle que l'axe traverse. Et l'origine géométrique de la section
assignée à cette cellule doit être posée à `(x+1) * 2048`, puisque ses sommets
s'étendent de `−8192` à `0` en X. Les deux énoncés disent la même chose : la
section couvre sa propre cellule, son origine étant sur le bord `+X` de
celle-ci.

## Le placement n'est pas encore exact — et la réflexion est écartée

Observation extérieure : le tracé est bon, le placement de la géométrie ne
l'est pas. Elle est juste, et deux mesures la rendent précise.

L'instrument est le tunnel : un tunnel doit être centré sur l'axe. En prenant
les centroïdes des 695 quads de type C et leur distance à la polyligne, avec
une demi-largeur effective de route de **503 unités monde** (`hw*2 >> 4`) :

| placement | distance médiane à l'axe |
|---|---|
| origine à `x_idx * 2048` | 990 |
| origine à `(x_idx + 1) * 2048` | 556 |
| meilleur ajustement libre `(+1536, +512)` | 260 |

Donc le décalage d'une cellule en X va dans le bon sens et divise l'erreur par
presque deux, mais un ajustement libre fait encore deux fois mieux, sur une
valeur qui n'est un multiple propre de rien. **La convention d'origine n'est
donc pas encore dérivée ; elle est ajustée.** C'est à corriger dans la section
précédente, où j'écrivais que le décalage « n'avait qu'une valeur admissible » :
c'était vrai à la résolution d'une cellule, et faux à la résolution où on peut
maintenant mesurer.

## La réflexion en X est réfutée

Même instrument, et cette fois le verdict est net :

| indexation | tunnels | tous les quads |
|---|---|---|
| `x_monde = x_idx * 2048` | 990 | 1 384 |
| `x_monde = (30 − x_idx) * 2048` | 15 813 | 3 889 |
| `x_monde = (31 − x_idx) * 2048` | 17 854 | 4 298 |
| `x_monde = (29 − x_idx) * 2048` | 13 775 | 3 601 |

Seize fois pire. L'hypothèse d'une réflexion en X entre la grille et la
polyligne, ouverte depuis trois sections de cette page, est **fausse** :
`z*32 + x` est bien la correspondance, sans miroir. Le `30 − x` du code
s'explique donc par un stockage inversé de la caméra dans `D_801D9068`, la
réflexion s'appliquant deux fois et s'annulant — ce qui reste à lire, mais
n'est plus une alternative ouverte sur le placement.

## Où chercher la suite

Pas dans un ajustement plus fin. Les deux candidats qui restent sont dans le
code de chargement : `func_800125B4`, qui construit la table de 32 octets par
section à `D_801D35F0`, et ce qui écrit `D_801D82D0`. Si une origine par
section existe, elle est posée là — et un décalage constant qui n'est un
multiple propre de rien ressemble beaucoup plus à un champ lu dans un fichier
qu'à une convention de grille.
