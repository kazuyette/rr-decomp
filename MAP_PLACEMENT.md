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
