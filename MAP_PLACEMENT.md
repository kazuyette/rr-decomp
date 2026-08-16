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

## La géométrie est stockée retournée d'un demi-tour

Trois lectures et une mesure, dans cet ordre.

**`func_800125B4`, le chargeur, ne stocke aucune origine.** Son entrée de 32
octets par section est `{ptrA(0), ptrB(4), ptrC(8), cntA(0xC), cntB(0xE),
cntC(0x10)}` et rien d'autre. Le décalage cherché n'est donc pas dans le
fichier — il est dans la convention. (Au passage : `func_800437AC` lit le
pointeur en `0x0` et le compteur en `0xC`, donc la passe de dessin lue plus
haut est celle du **type A**, pas du type B.)

**`func_80015CD4` donne la constante.** Cette fonction d'initialisation écrit
`D_801733A0 = 0xF000` — le global que `TRACK_SPINE_FORMAT.md` désignait comme
« le mécanisme de cours miroir ». Et `0xF000 = 61440 = 30 × 2048`, soit
exactement le `30 −` de l'indexation. Le repère de rendu est donc le repère de
la polyligne réfléchi en X autour de `30 × 2048`.

**La composition s'annule, et elle explique l'arrondi.** En posant
`X_rendu = 0xF000 − X_poly` et `X_poly = 2048q + r` :

```
cellX  = (0xF000 − X_poly + 0x400) >> 11 = 30 − q − [r > 1024]
index  = 30 − cellX                      = q + [r > 1024]
```

soit `index = round(X_poly / 2048)`. La correspondance empirique `z*32 + x` est
donc **dérivée**, pas constatée, et le `+0x400` n'est pas un détail : il place
la cellule `k` sur l'intervalle `[2048k − 1024, 2048k + 1024]`, centré sur
`2048k` et non aligné dessus.

**Reste la mesure.** Puisque le repère de rendu est réfléchi, les coordonnées
locales doivent être niées pour être dessinées dans le repère de la polyligne.
Distance médiane des centroïdes de tunnel à l'axe, demi-largeur de route 503 :

| convention | tunnels | tous les quads |
|---|---|---|
| `origine + local` (ce que je faisais) | 990 | 1 384 |
| `origine − local` en X seulement | 650 | 1 129 |
| `origine − local` en X et Z, origine `+1024` | **300** | **860** |

Nier X **et** Z est un demi-tour autour de Y, pas une double réflexion : le
sens de parcours des polygones est préservé, ce qui est cohérent avec le fait
que le jeu ne bascule le winding qu'en mode miroir. Et le `+1024` est
exactement le demi-pas que l'arrondi ci-dessus impose.

L'image de contrôle avec cette convention est la première où le ruban beige
suit l'axe sur toute sa longueur, où les tunnels verts sont **sur** la route et
non à côté, et où le quartier de droite se lit comme une ville avec ses
viaducs.

Le test de raccord entre sections voisines, essayé avant celui-ci, est nul et
mérite d'être noté comme tel : moins de 0,4 % des sommets coïncident d'une
section à l'autre dans toutes les configurations. Les sections sont autonomes
et pavent leur cellule quel que soit le signe, donc la continuité interne ne
peut rien arbitrer ici.

## La polyligne n'est pas l'axe : c'est un bord de route

Observation extérieure, sur trois portions différentes : la géométrie est
toujours du même côté du trait rouge — au-dessus sur les deux droites
horizontales, à gauche sur la portion verticale. Demande : la basculer de
l'autre côté.

La mesure dit autre chose, et elle est nette. Sur la longue droite sud, les
**353 sommets de type B proches du trait tombent tous dans `[−800, 0]`** en
distance signée. Rien, pas un seul, de l'autre côté. La demi-largeur des nœuds
y vaut 655.

Une géométrie mal placée serait décalée ; une géométrie coupée net sur le trait
ne l'est pas. **La polyligne stockée est un bord de la route, pas son axe.**
C'est moi qui l'appelais l'axe depuis le début, et c'est cette erreur de
lecture qui donnait l'impression d'un décalage.

Ça se confirme en traçant le second bord à `2 × demi-largeur` du premier, du
côté où se trouve la géométrie : sur les deux droites et dans les tunnels, le
ruban de route est **encadré** par les deux traits. Le rendu de contrôle
`map_v4.png` le montre.

Ce qui recale au passage plusieurs chiffres de cette page. Toutes les distances
« à l'axe » mesurées plus haut étaient en fait des distances à un bord, donc
biaisées d'une demi-largeur — et il faut leur retirer ce biais avant de les
comparer entre elles.

### Un défaut de mesure à signaler

La table de la section précédente (990 / 650 / 300) est fausse. La fonction de
score divisait les coordonnées locales par 16 au lieu de 4, rétrécissant la
géométrie d'un facteur quatre et réduisant toutes les distances d'autant. Le
rendu, lui, utilisait le bon facteur — d'où une image qui s'améliorait pendant
que les chiffres devenaient trop beaux. Table refaite, à l'échelle correcte,
avec la distance signée qui doit s'annuler :

| convention | signée | absolue |
|---|---|---|
| `origine + local` | +331 | 1901 |
| `origine + local`, +1 cellule en X | −52 | 813 |
| demi-tour, origine `(+1024, +1024)` | −562 | 1011 |
| **demi-tour, origine `(+0, +1024)`** | **−89** | **351** |
| X nié seul, origine `(+0, +1024)` | +59 | 606 |
| Z nié seul, origine `(+0, +1024)` | +273 | 1744 |

La convention retenue est donc le demi-tour avec l'origine décalée de `+1024`
en Z seulement — et non `+1024` sur les deux axes comme écrit hier.

C'est la deuxième fois sur cette page qu'un chiffre trop flatteur venait d'un
facteur d'échelle et non du sujet étudié. Le garde-fou qui manquait est simple :
quand une image et une métrique divergent sur le même objet, c'est la métrique
qu'il faut relire.

---

# La convention correcte

```
x_monde = cellule_x * 2048  −  localX / 4
z_monde = cellule_z * 2048  +  localZ / 4
```

**X nié, Z non nié, aucun décalage.** C'est tout.

Le X nié vient de `D_801733A0 = 0xF000 = 30 × 2048` lu dans `func_80015CD4` :
le repère de rendu est celui de la polyligne réfléchi en X, et rien ne réfléchit
Z. La dérivation le disait déjà ; je l'ai perdue en route en niant aussi Z sur
la foi d'une métrique fausse.

## La preuve

Intervalle occupé par les sommets de type B autour de la longue droite sud,
en distance signée à la polyligne, pour une demi-largeur de nœud de 655 :

| convention | n | bande | médiane |
|---|---|---|---|
| `(−X, −Z)`, décalage `+1024` en Z | 353 | `[−815 .. −65]` | −428 |
| `(+X, −Z)`, décalage `+1024` en Z | 506 | `[−788 .. +514]` | −262 |
| `(+X, +Z)`, aucun décalage | 532 | `[−1587 .. +885]` | +4 |
| **`(−X, +Z)`, aucun décalage** | **352** | **`[−359 .. +392]`** | **+4** |

La bonne se reconnaît à deux choses ensemble : une médiane nulle **et** une
bande étroite. `(+X, +Z)` a aussi une médiane nulle, mais sur une bande trois
fois trop large — c'est du décor réparti symétriquement, pas une route. Seule
`(−X, +Z)` donne une bande de 750 unités centrée, à comparer aux 1310 de
largeur de route : le revêtement, centré sur son axe.

## Ce que ça retire de cette page

**La polyligne est bien l'axe de la route**, et non un bord. La section
précédente concluait l'inverse à partir d'un intervalle `[−800, 0]` — cet
intervalle était l'artefact du signe de Z. À retirer.

**Les décalages `+1024` sont des artefacts** de la même erreur. Il n'y a aucun
décalage.

**Le demi-tour est faux** : c'est une réflexion en X seule.

Trois conclusions successives invalidées par la même cause, et la cause n'a été
trouvée qu'en changeant de question — non plus « quelle transformation minimise
une distance », mais « quel intervalle occupe la route autour de son axe ». La
première question a un optimum pour n'importe quelle convention ; la seconde
n'a de réponse étroite que pour la bonne.

Le signalement extérieur qui a débloqué ça — « la géométrie est du même côté,
il faut la retourner en miroir » — portait sur trois portions différentes et
était exact. Aucune de mes métriques agrégées ne le voyait, parce qu'elles
moyennaient sur un décor réparti des deux côtés.

## L'amas détaché du nord-est

Signalé de l'extérieur comme suspect sur le rendu final : un groupe de quads de
type A posés à l'écart, sans route ni sol autour. Ce sont huit sections, et
elles se répartissent en deux groupes nets.

| sections | cellules | hauteur (monde) | distance à une piste | biais de profondeur |
|---|---|---|---|---|
| 72, 73, 93 | (19–21, 7–9) | −1221 .. +170 | 1 590 – 3 074 | 50 / 51 |
| 40, 41, 56, 57, 58 | (21–23, 5–6) | −642 .. +1 | 5 975 – 6 716 | 12 |

Chaque section est bâtie de la même façon : une bande de quads en tpage 23 et,
juste au-dessus, une bande en tpage 28, les deux partageant exactement leur
arête en Y. Et les quads sont **verticaux** — celui d'exemple mesure 994 de
large pour 937 de haut sur une empreinte de 285 de profondeur.

Des parois verticales de 300 à 1 200 unités de haut, texturées en deux bandes
superposées, à une à trois cellules de la piste, avec un biais de profondeur de
50 là où la valeur courante du fichier est −8 : c'est un **décor de fond**,
dessiné loin derrière tout le reste. La falaise et le relief qu'on voit par
dessus la baie depuis la section côtière.

L'absence de sol autour n'est donc pas une lacune : entre la route et ces
parois, il y a l'eau, et l'eau n'a pas de quads.

Ce qui corrige une troisième fois la phrase « aucun des trois types n'est un
mur ». Le type A en contient, et des grands. Le test d'empreinte fine en plan
les manquait parce qu'ils sont larges autant que hauts — fins seulement dans la
troisième dimension, celle que la vue de dessus écrase.
