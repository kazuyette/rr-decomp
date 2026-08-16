# Recompilation statique : la preuve de principe

*Second chantier, ouvert le 16 août 2026. Le décompilateur qui matche reste la
source de vérité ; ceci est un banc d'essai pour des jalons natifs qui
démarrent.*

## Pourquoi

Neuf dixièmes du code de jeu sont encore de l'assembleur — `st_race_main`,
`car_simulate`, `func_800163E4` et leurs appelés. Un jalon natif fait de nos
fonctions C plus des bouchons n'aurait donc ni boucle, ni physique, ni rendu :
il compilerait et ne prouverait rien.

La recompilation statique retourne le problème. On traduit mécaniquement chaque
instruction MIPS en C, le jeu tourne entier dès le premier jour, et chaque
fonction décompilée remplace ensuite sa jumelle traduite — les deux pouvant
être comparées en marche.

Tout cela ne vaut que si la traduction est fidèle. D'où ce banc.

## La méthode

Deux exécutables, un seul jeu d'entrées.

**La référence** : les mots du retail copiés tels quels dans une section d'un
binaire mipsel, appelés par un harnais C, exécutés sous `qemu-mipsel`. Aucune
interprétation n'intervient — ce sont les instructions d'origine sur un
processeur qui les comprend.

**La traduction** : le C produit par `tools/recomp.py`, compilé pour l'hôte.

Chacun reçoit le même tampon de 256 octets rempli pseudo-aléatoirement et les
mêmes quatre registres d'argument, puis imprime la valeur de retour et le
tampon final. On compare les textes.

## Résultat

**1 120 cas — soixante-dix fonctions, seize vecteurs chacune — et aucune
divergence.** (Première mesure : 120 cas sur cinq fonctions.) Sur les 115 fonctions traduisibles, 45 sont écartées parce que la référence
elle-même ne peut pas les exécuter sur des entrées quelconques — pointeur
invalide ou boucle sans fin, ce que la console ferait aussi. Les 70 restantes
rendent octet pour octet ce que rend le vrai code, valeur de retour comprise.

La référence n'est pas ma lecture du code : c'est son exécution.

## Ce que le banc a attrapé

Deux erreurs de traduction, et cinq défauts du banc lui-même. La distinction
compte : un banc qui échoue pour ses propres raisons ferait condamner un
traducteur correct.

### Dans le traducteur

**Les sauts absolus.** L'opcode `j` n'encode que les 28 bits bas de sa cible.
Ma première version calculait `(w & 0x3FFFFFF) << 2` en oubliant les quatre
bits hauts du compteur de programme. Côté référence, le même oubli déplaçait le
code et envoyait `MargePrim` dans le vide — d'où le chargement des fonctions à
leur adresse d'origine masquée sur 28 bits.

**Le créneau de retard.** L'instruction qui suit un branchement s'exécute avant
lui, pris ou non. Émise après le `goto`, elle donne du code qui marche partout
sauf là où le créneau modifie le registre testé. Le traducteur la déplace donc
systématiquement devant, après avoir figé la condition.

### Dans le banc

**Les entrées que la console refuserait.** Les premiers vecteurs passaient des
pointeurs non alignés : `SIGBUS` immédiat, comme sur le vrai matériel.

**Les vecteurs en littéraux C.** Douze fonctions donnaient déjà 276 Ko de
source et six minutes quarante de compilation, dont 0,2 seconde de calcul. Les
entrées vivent maintenant dans un fichier binaire lu à l'exécution : 0,3
seconde pour cent quinze fonctions.

**Le garde-fou cassé.** Attraper les fautes par `siglongjmp` depuis un
gestionnaire de signal échoue : glibc refuse le retour vers un cadre qu'il juge
non initialisé, et une fonction partie en boucle sans fin n'était pas rattrapée
du tout. Un fils par fonction avec une alarme le fait sans faille.

**Les fonctions sans valeur de retour.** Comparer `$v0` d'une fonction qui ne
l'écrit jamais, c'est comparer du bruit — la fonction vide `func_8003FA94` en
donnait un exemple net. Le banc ne compare le retour que si le désassemblage
montre une écriture de ce registre.

**L'adresse absolue du tampon.** `func_800409D4` ajoute `0x5D50AD` à son
argument et calcule sur le résultat : sa sortie dépend de la valeur du
pointeur, pas seulement de ce qu'il désigne. Le tampon est donc placé à la même
adresse fixe des deux côtés, par une section liée.

**Le cinquième argument.** `func_80048128` lit `0x10($sp)`, là où l'appelant
dépose son cinquième paramètre. Avec quatre arguments elle lisait de la pile
non initialisée. Les deux harnais en passent six, aux mêmes emplacements.

## L'état, honnêtement

Le passage à l'échelle n'est pas fait. Sur les 949 fonctions du binaire, 115
sont traduisibles en l'état — sans GTE, sans appel externe, sans global absolu
— soit 1 346 instructions. Les autres attendent trois choses :

- **le GTE** : 101 fonctions le touchent. Ses quarante opcodes demandent une
  implémentation à part, validée contre la documentation matérielle et non
  contre qemu, qui ne connaît pas ce coprocesseur. Le traducteur les refuse
  explicitement plutôt que de les traduire à moitié ;
- **les appels et les globals** : 722 fonctions, ce qui demande une table de
  symboles et un espace mémoire simulé, pas un changement de principe ;
Le harnais, lui, tient désormais la charge : 2,8 secondes pour construire et
exécuter la référence sur cent quinze fonctions, 1,2 seconde pour la
traduction.

---

# Étape 2 : les appels et les globals

## Le changement de méthode

Le premier banc recopiait chaque fonction à son adresse masquée, une par une.
Tant qu'elles étaient isolées cela suffisait ; dès qu'elles s'appellent entre
elles et lisent des variables globales, il faut le programme entier.

La correction simplifie tout : **on charge l'image complète de l'exécutable**
— 423 936 octets à `0x80010000`, soit `0x00010000` une fois masqué sur 28 bits
— dans une section de la référence, et on déclare chaque fonction comme un
symbole à son adresse dans cette image. Les appels et les adresses absolues
retombent alors justes sans une seule ligne de relocation, parce qu'ils sont
déjà justes.

Au passage, l'en-tête donne le point d'entrée : **`0x8003FA9C`**, huit octets
après `func_8003FA94`, la fonction vide de la frontière jeu/bibliothèque. La
frontière calculée il y a plusieurs sessions par le graphe d'appels tombe donc
exactement sur le début du runtime.

## Ce que le traducteur sait faire maintenant

| | avant | après |
|---|---|---|
| fonctions traduisibles | 115 | **836 sur 948** |

Trois ajouts l'ont permis :

**Les appels.** `jal` devient un appel C vers la fonction traduite
correspondante, résolu par une table de symboles construite depuis le
désassemblage.

**Le pointeur de pile comme global.** `$sp` ne peut pas être une variable
locale : un appelé doit voir celui de son appelant, sinon les cadres se
recouvrent et les arguments passés au-delà du quatrième se lisent dans le vide.
En faire un global rend l'imbrication et les arguments sur pile corrects sans
code particulier — parce que c'est exactement ce qu'il est sur la machine.

**Les globals ne demandent rien.** Les mots du retail contiennent déjà les
adresses absolues ; la traduction les calcule et les accesseurs les ramènent
dans le tableau RAM. Il suffit d'y avoir chargé l'image.

Restent 112 fonctions : le GTE (109), deux `syscall` et un accès COP0.

## Le résultat

**1 856 cas sur 116 fonctions. 114 identiques au bit près, 2 divergentes.**

Les 116 ne sont pas les 836 : le banc écarte 540 fonctions que la référence
elle-même ne peut pas exécuter sur des entrées quelconques, et 180 qui
atteignent — directement ou par transitivité — un appelé non traduisible. Ces
dernières sont écartées par un calcul de point fixe sur le graphe d'appels,
parce qu'un bouchon ne doit jamais passer pour une vérification.

## Quatre défauts de plus, tous dans le banc

**Les écritures dans `$zero`.** Le retail en contient — des `nop` encodés
autrement, des résultats calculés puis abandonnés. Traduites telles quelles
elles donnent `0 = 0 & 0;`, que le C refuse. Le registre est câblé à zéro sur
la machine : l'écriture se jette.

**Les arguments sur la pile.** `func_80028A0C` lit jusqu'à `0x54($sp)`,
`func_80029278` jusqu'à `0x58($sp)` — le neuvième argument. Chaque argument
manquant se lisait dans de la pile non initialisée, différente des deux côtés.
Le harnais en passe douze. Cela seul a fait tomber les divergences de 160 à 32.

**Les appelés non traduisibles**, traités plus haut.

**Le chevauchement de sections**, trivial mais instructif : l'éditeur de liens
a refusé de placer le tampon d'essai dans la zone non initialisée, ce qu'il
avait parfaitement raison de faire.

## Les deux qui restent

`func_80040690` et `rsin_quadrant` divergent sur leur valeur de retour, pas sur
la mémoire. La première teste son argument contre `0x400` — un quadrant
d'angle — et rend une valeur que la référence tire d'un appel dont ma
détection d'écriture de `$v0` ne rend pas compte. Ce sont deux cas à instruire,
pas deux erreurs établies ; et le fait qu'il n'en reste que deux sur 116 dit où
en est le traducteur.

---

# Étape 3 : le GTE

## Ce qui a été implémenté

Pas les quarante opérations du catalogue : **les vingt-deux que ce binaire
utilise réellement**, relevées en comptant les encodages dans les 948
fonctions. Vingt-neuf encodages distincts, `mvmva` en tête avec vingt-cinq
occurrences, puis `nclip`, `intpl`, `rtpt`, `avsz4`, `rtps`. Le reste lève une
erreur franche plutôt que de rendre un résultat faux.

Avec les registres et leurs particularités — la pile des coordonnées écran, la
pile des Z, la pile des couleurs, le dépaquetage 5-5-5 d'IRGB à l'écriture, le
compte de zéros en tête de LZCS, le registre H relu signé — et la saturation
complète avec ses dix-neuf drapeaux.

La division de projection reproduit le chemin du matériel : table de 257
entrées et deux itérations de Newton-Raphson, pas une division exacte. Une
division juste au sens mathématique donnerait des coordonnées écran
différentes de un ou deux — visibles sur les arêtes, invisibles dans un test
qui ne les cherche pas.

## Le traducteur, maintenant

| | fonctions traduisibles |
|---|---|
| avant les appels et les globals | 115 |
| après | 836 |
| **après le GTE** | **945 sur 948** |

Il ne reste que deux `syscall` et un accès COP0.

Les transferts deviennent des appels aux accesseurs, les commandes un appel
avec leur encodage brut. Le décodage des champs `sf`, `lm`, `mx`, `v` et `cv`
est fait par l'implémentation, pas par le traducteur — pour que les deux
restent vérifiables séparément.

## Le contrôle, et ce qu'il vaut

qemu ne connaît pas le COP2 : la référence par exécution qui a validé les
fonctions entières ne dit rien ici. Le seul contrôle disponible est de
réécrire les opérations **une seconde fois**, dans un autre langage, depuis la
même documentation, puis de comparer sur des états de registres tirés au
hasard.

**11 200 comparaisons — quatre cents états, vingt-huit encodages — et aucun
écart.** C'est-à-dire les vingt-neuf encodages relevés dans le binaire moins
`dpct`, qui répète `dpcs` trois fois sur la pile des couleurs.

La liste : `mvmva` en quatre variantes de matrice, de vecteur et de décalage ;
`nclip` ; `avsz3` et `avsz4` ; `sqr` et `op` en deux décalages chacun ; `rtps`
et `rtpt`, donc la projection avec sa division par table ; `gpf`, `gpl`,
`intpl`, `dpcs`, `dcpl` ; et toute la famille éclairage — `ncs`, `nct`,
`nccs`, `ncct`, `ncds`, `ncdt`, `cc`, `cdp`.

Ce que ça vaut, précisément : deux transcriptions indépendantes ne se trompent
pas au même endroit, sauf si la documentation elle-même est ambiguë. Ça attrape
les fautes de frappe, les décalages inversés, les saturations oubliées —
l'essentiel de ce qui rate dans ce genre de code. **Ça n'attrape pas une
lecture fausse partagée.** Le seul contrôle qui le ferait serait la console.

Et le chargeur du banc a lui-même produit un faux échec avant de servir :
écrire les trente-deux registres dans l'ordre détruit une partie de l'état,
parce qu'écrire IRGB dépaquette une couleur dans IR1-3 et qu'écrire SXYP
pousse la pile des coordonnées. Quatre cents états divergeaient pour cette
seule raison.

## La méthode a payé : deux vrais bugs trouvés

`gpf` et `gpl` se sont accordées du premier coup. `intpl` et `dpcs` ont
divergé sur les quatre cents états — et l'erreur était dans le C.

L'interpolation vers la couleur lointaine s'écrit, dans la spécification :

```
IR  = ((FC SHL 12) - MAC) SAR (sf*12)
MAC = (IR * IR0 + MAC)    SAR (sf*12)
```

Le `MAC` de départ n'est **pas** redécalé. Ma première version le décalait de
`sf*12` aux deux endroits, ce qui saturait toute la brume à blanc. Aucun test
d'invariant ne l'aurait vu : les valeurs restaient plausibles, du même ordre de
grandeur, simplement fausses. La seconde transcription l'a attrapé au premier
état tiré.

Le correctif touchait aussi le chemin brume des calculs d'éclairage, qui
compensait le bug en pré-décalant ses entrées — deux erreurs qui s'annulaient à
moitié.

**Le second, dans `ncs` et `nct`.** Sans teinte par `RGBC`, la spécification
garde le MAC issu de la seconde matrice : c'est *lui* le résultat, et la FIFO
de couleur reçoit `MAC/16`. Je le recalculais depuis `IR`, ce qui le divisait
par 256 quand `sf` valait 1. Des couleurs presque noires — plausibles à l'œil,
fausses. Les variantes teintées (`nccs`, `ncct`, `ncds`, `ncdt`) étaient
justes, ce qui rendait l'erreur d'autant plus difficile à soupçonner : elle ne
touchait que deux opérations sur huit de la même famille.

Deux bugs, tous deux dans la manipulation d'échelle, tous deux invisibles à un
test d'invariant, tous deux attrapés au premier état tiré. C'est exactement ce
pour quoi la méthode existe.

## Ce qui n'est pas encore contrôlé

`dpct`, qui répète `dpcs` sur la pile des couleurs — une occurrence dans le
binaire. Les drapeaux de `FLAG` ne sont pas comparés non plus : la référence
Python les accumule mais le banc ne les lit pas. Le jeu les consulte rarement,
mais « rarement » n'est pas « jamais ».

Et la limite de fond ne bouge pas : deux transcriptions indépendantes
n'attrapent pas une lecture fausse partagée. Seule la console le ferait.
