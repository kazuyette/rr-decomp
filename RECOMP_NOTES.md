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

**11 600 comparaisons — quatre cents états, les vingt-neuf encodages relevés
dans le binaire — et aucun écart, registre `FLAG` compris.**

La liste : `mvmva` en quatre variantes de matrice, de vecteur et de décalage ;
`nclip` ; `avsz3` et `avsz4` ; `sqr` et `op` en deux décalages chacun ; `rtps`
et `rtpt`, donc la projection avec sa division par table ; `gpf`, `gpl`,
`intpl`, `dpcs`, `dpct`, `dcpl` ; et toute la famille éclairage — `ncs`,
`nct`, `nccs`, `ncct`, `ncds`, `ncdt`, `cc`, `cdp`.

Chaque comparaison porte sur les trois accumulateurs, les trois registres
intermédiaires, la couleur produite, et **les dix-neuf drapeaux de saturation
et de débordement**.

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

## Ce que les drapeaux ont révélé

Comparer `FLAG` a fait apparaître un troisième écart — cette fois **dans la
référence Python**, pas dans le C. `sqr` et `op` écrivent aussi IR1-3 avec
saturation, donc posent des drapeaux ; ma transcription omettait cette étape.
Tant qu'on ne comparait que les accumulateurs, l'omission était invisible : les
valeurs comparées étaient justes des deux côtés.

C'est le contrôle qui fonctionne dans l'autre sens, et c'est rassurant : une
méthode qui ne trouverait jamais de défaut chez elle-même serait suspecte.

## Ce qui n'est pas contrôlé

La limite de fond ne bouge pas : deux transcriptions indépendantes n'attrapent
pas une lecture fausse partagée. Si la documentation que j'ai suivie se trompe,
mes deux versions se trompent ensemble. Seule la console trancherait — et ce
n'est pas une réserve de style : les émulateurs PSX ont mis des années à
converger sur certains coins du GTE.

---

# M0 : le jeu démarre

## Ce qui tourne

L'image de `PSX.EXE` est chargée en RAM, l'exécution part de `0x8003FA9C`, et
`_start` appelle `InitHeap` puis `main`. Le jeu configure le GPU — mode de
dessin, fenêtre de texture, zone de dessin, décalage, masque : la sortie exacte
de `SetDrawEnv` — puis entre dans sa boucle.

**946 fonctions traduites, trois bouchons** (deux `syscall` et un accès COP0).

## La preuve n'est pas un compteur

Le BIOS `A0(3F)` est le `printf` du noyau. L'implémenter coûte dix lignes et
rend au jeu sa propre voix :

```
ResetCallback: _96_remove ..
CdlReset: timeout
NoIntr: 0
DataReady: 0
Complete: 0
Acknowledge: 0
DataEnd: 0
DiskError: 0
CdlSetloc: timeout
...
```

C'est le pilote CD de Ridge Racer. Il tente `CdlReset`, attend ses drapeaux
d'interruption, n'en reçoit aucun — puisqu'il n'y a pas de lecteur — et
imprime son diagnostic, exactement comme il le ferait sur une console dont le
tiroir serait vide.

Aucune métrique extérieure ne dirait ça aussi bien. Le jeu exécute son vrai
code, atteint son vrai pilote, et rapporte son vrai échec.

## Trois bugs silencieux trouvés en chemin

Aucun n'aurait empêché la compilation.

**Les sauts indirects.** `jr $ra` est un retour ; `jr` sur tout autre registre
est un saut calculé — une table de branchement, ou un trampoline BIOS. Je les
traduisais tous en retours : **54 sauts** partaient à l'envers, en silence.

**Les appels indirects.** `jalr` était traduit en retour lui aussi. **59
appels** ne se faisaient jamais. Ils passent maintenant par une table adresse →
fonction, qui sert aussi à reconnaître les vecteurs BIOS `0xA0`, `0xB0`, `0xC0`.

**Les branchements vers un créneau de retard.** Comme le créneau est déplacé
devant son branchement, l'adresse ne porte plus d'étiquette. Le C refusait le
`goto`, ce qui l'a révélé — le seul des trois que le compilateur ait attrapé.
La correction remet l'étiquette après un saut par-dessus, pour ne pas rejouer
l'instruction en tombant dedans.

Les deux premiers n'existaient que parce que rien ne les avait comptés : le
banc de vérification, lui, n'exerçait aucune fonction qui en contienne.

## Ce que M0 n'est pas

Il n'y a pas d'image. Le GPU journalise au lieu de dessiner, les interruptions
n'existent pas, et le jeu tourne donc en rond dans son attente de CD —
`B0(03)` trois cents millions de fois en vingt secondes, ce qui est très
exactement ce qu'une boucle d'attente sans matériel doit faire.

La suite est M1 : le lecteur CD et les interruptions pour que le jeu dépasse
son chargement, puis le flux GP0 vers OpenGL. Et pour ce dernier, tout le
travail de nommage de libgpu — `SetPolyFT4`, les tpage, les CLUT, la VRAM 4
bits — est déjà fait.

---

# M1, premier temps : le matériel que le jeu réclame

## Le relevé, plutôt que le grep

Le pilote CD passe par un pointeur global, donc invisible au désassemblage. Je
l'ai pris par l'autre bout : un histogramme des adresses matérielles touchées
pendant l'exécution.

| registre | lectures | écritures | |
|---|---|---|---|
| `0x1F801814` | 63 432 514 | 7 | état du GPU |
| `0x1F801800` | 33 554 437 | 3 | **lecteur CD** |
| `0x1F801D80`–`0x1F801DB8` | quelques-unes | ~50 | processeur sonore |
| `0x1F8010A8` | 6 | 3 | DMA du GPU |

Trente-trois millions de lectures sur un seul registre : c'est une boucle
d'attente, et elle dit exactement où le jeu est coincé.

## Ce qui a été construit

**Le contrôleur CD** — index, files de paramètres et de réponses, drapeaux
d'interruption, et les commandes du démarrage. Il fonctionne : le jeu envoie
`Init` une fois et `Setloc` quatre fois, et le contrôleur répond.

**Le système d'événements du BIOS** — `OpenEvent`, `EnableEvent`,
`TestEvent`, `DeliverEvent`. Le jeu ouvre un événement pour la classe
`0xF0000009` dès le démarrage.

**La séquence d'appels BIOS**, tracée dans l'ordre. Elle se lit comme un
journal de démarrage : `InitHeap`, `SetMem(2)` pour deux mégaoctets,
`_96_remove`, l'installation du gestionnaire d'exceptions, `InitPAD2` et
`StartPAD2` pour les manettes, `InitCARD2` et `StartCARD2` pour la carte
mémoire, `_bu_init`, puis l'ouverture de l'événement CD.

## Où ça bloque, précisément

`B0(19) HookEntryInt` installe le gestionnaire d'exceptions **du jeu** : il ne
scrute pas le matériel, il attend d'être appelé. Mais l'adresse lue dans sa
structure vaut zéro, parce que `A0(13)` — qui la remplit — est encore un
bouchon.

C'est un chaînon, pas un mur : tant que le gestionnaire n'a pas d'adresse,
aucune interruption ne peut lui être livrée, et le pilote compte zéro rappel
sur ses six compteurs — `NoIntr`, `DataReady`, `Complete`, `Acknowledge`,
`DataEnd`, `DiskError` — avant de conclure au timeout. Exactement ce qu'il
ferait sur une console dont le lecteur ne répondrait pas.

## Une simplification qui vient du jeu lui-même

Le lecteur ne sert qu'à deux moments : **au chargement initial**, et ensuite
**pour les pistes audio**. Entre les deux, tout est en mémoire — le jeu tient
dans les deux mégaoctets et ne retourne jamais au disque.

Ça change l'ordre du travail. Émuler le lecteur au niveau du secteur, avec sa
table des matières et son ISO 9660, n'est pas nécessaire pour voir une image :
il suffit de servir le chargement initial. Et la lecture audio, qui n'a rien à
voir avec les données, se traite séparément et plus tard.

## Le chaînon réparé — et le suivant

`A0(13)` est **`setjmp`**, déjà nommé dans le dépôt. Le motif se lit alors sans
ambiguïté dans `func_800492B0` :

```
setjmp(&contexte);
if (v0 == 0) { HookEntryInt(&contexte); return; }
... corps du gestionnaire ...
```

Le jeu n'installe pas une fonction : il **sauvegarde un contexte**. Sur la
console, le BIOS y revient par `longjmp` à chaque interruption, et l'exécution
reprend juste après le `setjmp`, avec une valeur non nulle.

Une traduction par fonction ne peut pas sauter au milieu d'un cadre mort — le
`longjmp` de l'hôte viserait une pile qui n'existe plus. Mais elle peut
**rappeler la fonction en faisant rendre 1 au `setjmp`**, ce qui emprunte
exactement la même branche. C'est ce que fait `deliver_irq`.

Résultat : **70 265 interruptions livrées** en dix secondes, et quatre
événements BIOS délivrés. Le gestionnaire du jeu s'exécute.

Mais ses six compteurs restent à zéro. Le chaînon suivant est donc dans
l'acquittement : le gestionnaire tourne, lit l'état, et ne reconnaît pas encore
l'interruption du lecteur comme la sienne. C'est là que reprendra le travail —
et le prochain relevé à faire est celui des registres que le gestionnaire lit
*pendant* qu'il tourne, par opposition à ceux que lit la boucle principale.

## Les interruptions, pour de vrai

Trois corrections, chacune trouvée en instrumentant plutôt qu'en devinant.

**`I_STAT` était une constante.** Je renvoyais une valeur figée pour les
sources en attente, et je perdais les acquittements — les écritures dans ce
registre n'étaient traitées par aucun cas. Un drapeau qui ne s'efface jamais
fait retraiter sans fin la même source, et les autres n'arrivent jamais. Le
registre est maintenant réel : les écritures effacent les bits à zéro, comme le
matériel.

**Le masque, relevé plutôt que supposé.** Le jeu arme `0x0008` puis `0x000C` —
DMA, puis DMA et lecteur CD. Il attend donc bien l'interruption du lecteur, ce
qui écarte l'hypothèse d'un pilote purement scrutateur.

**L'horloge s'arrêtait au mauvais moment.** Je livrais les interruptions en
cadence sur les lectures d'état du GPU. Or la boucle d'attente du lecteur ne
lit que son propre registre, trente-trois millions de fois — jamais le GPU.
Autrement dit, ma montre s'arrêtait précisément pendant que le jeu attendait
une interruption. La livraison se fait maintenant sur toute lecture matérielle.

Le corps du gestionnaire se lit d'ailleurs sans peine une fois qu'on sait où
regarder : il charge `I_STAT` et `I_MASK` **par pointeurs**, stockés en
`D_80077440` et `D_80077444`, les combine, et teste d'abord le bit 3 — le DMA —
avant de se brancher ailleurs pour le reste.

## Ce qui résiste encore

Trois millions d'interruptions livrées, le gestionnaire s'exécute, le masque
est bon, le contrôleur répond — et les six compteurs du pilote restent à zéro.

Le suspect principal est l'émulation du `setjmp`/`longjmp`. Rappeler la
fonction en faisant rendre 1 au `setjmp` emprunte la bonne branche, mais **ne
restaure pas les registres sauvegardés** au moment du `setjmp`. Si le corps du
gestionnaire dépend de l'un d'eux, il travaille sur des valeurs qui ne sont pas
celles que le matériel lui aurait rendues.

C'est une limite de principe de la traduction par fonction, pas un oubli. La
sortie propre serait de sauvegarder et restaurer explicitement les registres
persistants dans la structure de contexte — ce que fait le vrai `setjmp` — et
donc de traduire ces deux fonctions à la main plutôt que de les boucher.

## Ne pas rejouer : entrer au bon endroit

Le diagnostic du `setjmp` était juste sur le principe et faux sur la cause.

Rappeler `func_800492B0` depuis son début empruntait bien la bonne branche —
mais **rejouait tout son prologue à chaque interruption**. Or ce prologue
réarme le masque, remet à zéro deux tableaux et rappelle `func_800495DC`.
Autrement dit, chaque interruption effaçait l'état que le pilote venait
d'établir. Aucune séquence ne pouvait aboutir.

La sortie ne demandait pas de restaurer des registres : elle demandait
d'**entrer au bon endroit**. Le corps du gestionnaire commence à `0x8004934C`,
juste après le test qui suit le `setjmp`. Traduit comme une fonction à part
entière — il l'accepte sans broncher, 141 instructions — il s'exécute sans
toucher au prologue.

C'est la bonne façon de rendre un `longjmp` dans une traduction par fonction :
ne pas rejouer, entrer au point de reprise.

**Résultat : `Acknowledge: 1`.** Le premier compteur non nul du pilote. Le
gestionnaire atteint sa branche CD, reconnaît l'interruption du lecteur et
l'acquitte.

Le contrôleur sait aussi répondre deux fois maintenant — un accusé `INT3` puis
un achèvement `INT2` quand le pilote a relevé le premier —, ce que la console
fait pour `Init`, `Pause` et les recherches.

## L'état, sans arrondir

Un compteur sur six a bougé, et une fois. Le dialogue s'amorce mais ne se
poursuit pas : le pilote reçoit son accusé, puis retombe en timeout. Il manque
encore quelque chose entre l'accusé et la suite — vraisemblablement la
séquence exacte que `CdlReset` attend, ou un état du contrôleur que je rends
faux.

C'est peu, mais c'est la première fois que le pilote reconnaît quelque chose
qui vient de nous. Jusqu'ici, ses six compteurs étaient à zéro parce qu'aucune
interruption ne lui parvenait ; maintenant qu'une lui parvient, ce qui reste à
corriger est du détail de protocole, pas d'architecture.
