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

## Le dialogue, enfin visible

Deux corrections, puis une trace complète.

**La base de temps.** La boucle d'attente du pilote ne lit aucun registre :
elle décompte des tours en surveillant un drapeau en mémoire que le gestionnaire
doit poser. Livrer les interruptions sur les lectures matérielles ne l'atteint
donc jamais — `CdlReset: timeout` s'imprimait **avant** que la réponse soit
lue. Une horloge cadencée sur les appels de fonction n'a pas suffi non plus :
entre la commande et l'expiration, il n'y a pas deux cent cinquante-six appels.

L'interruption est maintenant levée **sur place**, à l'écriture de la commande,
comme le fait le matériel. L'ordre est enfin le bon : commande, drapeaux,
réponse, puis seulement le verdict du pilote.

**Ce que la trace montre.**

```
cd: index        00
cd: COMMANDE     0A          <- Init
cd: index        01
cd: lit drapeaux E3          <- INT3, l'accuse
cd: lit reponse  02          <- l'etat du lecteur
CdlReset: timeout
cd: index        02
cd: ecrit 1803   00          <- volumes audio
cd: index        03
cd: ecrit 1801   80
cd: ecrit 1803   20
```

Le pilote reçoit son accusé et lit la réponse. Puis il déclare le timeout et
passe au réglage des volumes.

## Ce qui manque, nommé précisément

**Il n'acquitte jamais.** Aucune écriture à l'index 1 sur `0x1F801803` — or
c'est ainsi qu'on efface un drapeau d'interruption sur cette machine. Et le
relevé des registres lus *pendant* le gestionnaire le confirme : celui-ci ne
touche que `I_STAT`, `I_MASK` et le contrôle DMA. **Il ne parle jamais au
lecteur.**

La conclusion s'impose : le traitement de l'interruption CD n'est pas dans le
corps que j'ai branché. Il y a un second niveau — un rappel enregistré ailleurs,
que le gestionnaire général appelle et que ma traduction n'atteint pas encore.
C'est ce chaînon-là qu'il faut suivre, et la trace donne maintenant de quoi le
faire : on connaît l'ordre exact des échanges et l'endroit précis où la chaîne
se rompt.

## La chaîne du rappel CD, cartographiée

En cherchant l'adresse du lecteur dans l'image plutôt que dans le code — elle
est rangée en `0x800774D8` et `0x80077520` — on remonte toute la chaîne.

**`D_8005497C` est une fonction, pas une donnée.** Six cent vingt et une
instructions, étiquetées `D_` par splat faute de référence directe, et elle
manipule la base du lecteur, `I_STAT` et `I_MASK`. C'est le rappel CD du jeu.
Elle figure d'ailleurs depuis le début en tête des plus grosses « fonctions »
restées en assembleur, sous ce nom trompeur.

**`func_80051CE4` est `CdSyncCallback`** : trois instructions qui rangent leur
argument dans `D_801E9170` et rendent l'ancien. Le jeu l'appelle avec
`D_8005497C` au démarrage, juste après avoir enregistré `func_80054664` par
`func_800490B0`.

**Cinq fonctions lisent `D_801E9170`** pour invoquer le rappel :
`func_80052504`, `func_80052854`, `func_800532C8`, `func_80053390`, plus
l'enregistreur lui-même.

Deux noms de plus au passage — et surtout la certitude que la fonction manquante
dans la chaîne d'interruption est identifiée, traduite, et présente dans le
binaire natif. Ce qui reste est de comprendre par quel chemin elle devrait être
atteinte depuis le gestionnaire général, puisque celui-ci ne touche jamais au
lecteur.

## Le chaînon trouvé : le jeu comptait sur le BIOS

La lecture du répartiteur du jeu, dans `func_800492B0`, règle la question.

Il boucle sur les bits de `I_STAT & I_MASK`, cherche un rappel dans
`D_800797A8[bit]`, l'appelle par `jalr`, puis acquitte en écrivant
`~(1 << bit)`. Une seconde branche fait la même chose pour les sept canaux du
DMA, avec sa propre table `D_80079788`.

Or **personne n'enregistre de rappel pour le bit 2**, celui du lecteur.
`func_800490B0` enregistre bien `func_80054664`, mais pour le **canal DMA 3** —
le DMA du lecteur, pas son interruption. Le jeu compte donc sur le BIOS pour
lire la réponse, acquitter, et appeler la fonction qu'il a posée par
`CdSyncCallback`.

C'est exactement le service qu'il fallait rendre — non pas émuler une image du
BIOS, mais réécrire la fonction que ce jeu appelle. Une vingtaine de lignes :
relever le type d'interruption et la réponse, acquitter, enchaîner sur
l'achèvement si la commande en attend un, et appeler le rappel avec
`(type, résultat)`.

## Le résultat : la séquence de démarrage avance

```
CdlReset   -> CdlSetloc -> CdlSetmode -> CdlReadN
```

Le pilote franchit maintenant quatre étapes là où il rejouait `CdlReset` en
boucle. C'est la séquence exacte d'un démarrage sur disque : réinitialiser,
se positionner, régler le mode, lire.

Il bute sur la lecture, ce qui est attendu — aucune donnée ne lui est encore
servie. Et c'est là que la remarque sur les deux usages du lecteur prend toute
sa valeur : il n'y a qu'un chargement à servir, une fois, avant que le jeu
n'ait plus jamais besoin du disque.

## Le disque, servi

L'image `data.iso` est un **vrai système de fichiers ISO 9660**, simplement
tronqué : `RIDGERACER`, 184 568 secteurs annoncés dont on possède les 1 559
premiers — ce qui suffit, parce que le descripteur de volume est au secteur 16,
la table des chemins au 18 et la racine au 22. Tout ce qui décrit le disque est
là ; il ne manque que les données.

Et les données, on les a par ailleurs. Le répertoire donne pour chacune son
secteur de départ :

| fichier | secteur | taille |
|---|---|---|
| `PSX.EXE` | 23 | 425 984 |
| `RR.VH` / `RR.VB` | 231 / 247 | son |
| `TEX4` … `TEX3` | 487 … 1003 | textures |
| `MAP.RRM` | 1057 | 271 548 |
| `OBJ.RRO` | 1190 | 445 348 |
| `IDX.HED` | 1408 | 2 048 |

La couche de service est donc simple : **les métadonnées viennent de l'image,
les données des fichiers extraits**, chacun à son secteur déclaré. Le jeu ne
voit aucune différence — il demande un secteur, il obtient les octets qui y
sont. Aucune donnée n'est versionnée : la table se régénère depuis ta propre
image.

`Setloc` est décodé — minutes, secondes et trames en décimal binaire, moins les
150 trames d'amorce — et le canal 3 du DMA transfère un secteur vers la RAM
puis avance d'un.

## Où en est la séquence

Elle s'allonge à chaque correction :

```
CdlReset                                          (au depart)
CdlReset -> CdlSetloc -> CdlSetmode -> CdlReadN    (apres le service BIOS)
... -> CdlReadN -> CdlPause -> CdlReadN            (maintenant)
```

Le pilote enchaîne désormais lecture et pause, et recommence. Mais aucun
secteur n'est encore demandé : il n'atteint pas le transfert, parce que son
initialisation expire toujours avant d'enregistrer sa fonction de
synchronisation — laquelle reste donc nulle, et le rappel jamais appelé.

C'est un cercle qu'il faut ouvrir par le bon bout : ce n'est pas la donnée qui
manque au pilote, c'est la confirmation que sa commande a abouti. Le prochain
travail est là, sur l'achèvement `INT2` et non sur les secteurs — qui, eux,
sont prêts à être servis le jour où il les demandera.

## La chaîne était complète — et je la cassais

En remontant les compteurs du pilote, tout s'éclaire.

`func_80052440` imprime « *commande* : timeout » puis six compteurs lus en
`D_80077610`, qu'elle remet à zéro. Ces compteurs sont incrémentés par
`func_80052504` — la routine d'interruption du pilote, celle qui touche la base
du lecteur et le rappel de synchronisation. Elle est appelée par `D_80052820`,
encore une fonction étiquetée en donnée, dont l'adresse est confiée à
`func_80049140`, qui enregistre… **pour l'interruption 2, celle du lecteur.**

Et à l'exécution, la table est bien remplie :

```
irq 2 -> 80052820        <-- le gestionnaire CD du jeu
rappel de synchronisation (D_801E9170) : 800535C8
```

Le jeu ne comptait donc **pas** sur le BIOS pour le lecteur : il a son propre
gestionnaire, dûment enregistré, et le répartiteur l'appelle par `jalr`.

Mon « service CD du BIOS », écrit au tour précédent, **lui volait
l'interruption** : il relevait la réponse et effaçait le drapeau avant que le
gestionnaire du jeu puisse les lire. Il est retiré.

C'est une leçon qui vaut d'être notée telle quelle : *rendre un service que
personne n'a demandé est une façon discrète de casser une chaîne qui marchait*.
La séquence s'était allongée juste après son ajout, ce qui m'avait convaincu
qu'il aidait — alors qu'elle s'allongeait pour une autre raison, la base de
temps corrigée au même moment.

## Ce qui reste

Le pilote reçoit son accusé `INT3` à chaque commande, et **n'acquitte jamais**
au niveau du contrôleur : aucune écriture à l'index 1 sur `0x1F801803`. Or sans
acquittement, le matériel ne délivre pas la réponse suivante — l'achèvement
`INT2` que le pilote attend pour conclure.

Deux lectures possibles, et il faut les départager plutôt que de choisir :
soit mon modèle du registre d'état est faux et le pilote acquitte autrement,
soit son gestionnaire n'atteint pas le code qui acquitte. La trace des accès
est en place ; ce qui manque est de la lire depuis l'intérieur du gestionnaire
du jeu plutôt que depuis le contrôleur.

## M1 franchi : le jeu lit son disque et dessine

Sept défauts, trouvés dans cet ordre, chacun masquant le suivant.

**1. Le `jr` d'un `switch` n'allait nulle part.** Le gestionnaire d'interruption
du lecteur CD (0x80052504) trie ses six types d'interruption par une table de
sauts. Le traducteur envoyait tout `jr` non-`$ra` au répartiteur global, qui ne
connaît que des entrées de fonction : la cible, interne à la fonction, était
introuvable. Le compteur le disait déjà — « sauts indirects sans cible : 8 » —
et je ne l'avais pas lu. Tout ce qui suit le `switch` était perdu, y compris
l'acquittement. `tools/recomp.py` donne désormais un aiguillage local à toute
fonction contenant un tel saut, avec repli sur le répartiteur.

**2. Le contrôleur répondait trop vite.** La seconde réponse (INT2, INT1) était
émise dans l'acquittement même. Le pilote boucle tant qu'un drapeau est levé :
il ne sortait jamais. Six millions de secteurs servis, aucun progrès.

**3. La base de temps s'arrêtait quand on la regardait.** `CdSync` attend dans
une boucle qui ne lit aucun registre et n'appelle aucune fonction — elle
surveille un octet en RAM. Cadencer le temps sur le matériel ou sur les appels
revenait à arrêter la montre exactement pendant l'attente. L'horloge bat
maintenant sur les accès mémoire (`TICK()` dans `rt.h`) : la seule chose que du
code qui tourne ne peut pas s'abstenir de faire.

**4. L'interruption ne rendait pas la pile.** `$sp` remontait à chaque
interruption. Au bout de quelques-unes, les tampons alloués sur la pile
tombaient au-delà des deux mégaoctets et les écritures étaient jetées en
silence. Le jeu lisait alors une position de disque nulle et concluait
« File not found » — après avoir lu son PVD correctement. `deliver_irq` sauve
et restaure `$sp`, ce que le matériel garantit et que la traduction ne
garantit pas.

**5. `strcpy` n'existait pas.** La bibliothèque remplace les fonctions de
chaîne par des tremplins vers `0xA0`. Non implémentées, elles rendent zéro sans
rien copier — et le défaut se manifeste très loin. Les seize fonctions de
chaîne et de mémoire sont écrites.

**6. `VSync` attendait un compteur absent.** Il ne compte pas les images
lui-même : il demande au BIOS la différence depuis son dernier appel
(`B0(03) GetRCnt`). Sans réponse, la différence est toujours nulle.

**7. Le tableau d'affichage se lisait mal.** Un chaînage nul était suivi comme
une adresse, et les données de texture d'un paquet `A0` étaient comptées comme
des commandes. D'où un journal plein de codes impossibles.

État : 907 secteurs servis, 1677 tables d'affichage déroulées, 99 541 commandes
GPU dont 54 804 rectangles plats et 6 173 texturés. Le jeu imprime son propre
diagnostic sonore (`ss_init error`). Reste à porter GP0 sur OpenGL pour voir
l'image plutôt que la compter.

## M2 : l'image

Le journal GPU est remplacé par un vrai rastériseur (`tools/m0/gpu.c`) :
mémoire vidéo 1024×512, polygones plats, dégradés et texturés, rectangles et
sprites, traits, transferts, palettes 4 et 8 bits, fenêtre de texture, zone de
dessin, décalage, semi-transparence dans ses quatre modes. Logiciel et non
OpenGL : ce qu'on cherche à établir est la fidélité, pas la vitesse, et il
tourne dans un conteneur sans écran.

Quatre défauts se sont révélés en regardant l'image plutôt que les compteurs.

**Le DMA 2 a trois modes, pas un.** `LoadImage` pousse les pixels par bloc.
Les traiter comme une liste chaînée faisait suivre au canal un chaînage tiré
de la texture elle-même — d'où un transfert fantôme de 1024 par 256 qui
barbouillait toute la mémoire vidéo.

**La fenêtre de texture s'applique avec le masque brut.** Je l'inversais, et
la valeur par défaut devenait « ne garder que trois bits d'abscisse » : tous
les texels venaient d'une seule colonne de huit pixels. Les glyphes étaient au
bon endroit, tous identiques.

**Sans dégradé, la couleur unique occupe le premier mot.** Je lisais le mot de
commande comme une coordonnée : chaque polygone plat atterrissait ailleurs.

**Une copie interne de taille nulle** n'est pas « toute la mémoire vidéo » : la
suivre à la lettre revenait à barbouiller l'écran à partir d'un mot mal cadré.

Résultat : l'écran de chargement (le Galaxian), puis l'écran-titre complet —
drapeau à damier, logo, mentions légales, « PUSH START BUTTON » — puis la
démonstration, où seul le fond se dessine. Deux minutes de fonctionnement sans
incident : 751 855 commandes GPU, 4 104 tables d'affichage. Le jeu ne plante
pas ; il lui manque encore la piste.

## M3 : la piste

Trois défauts, et le troisième explique tous les autres symptômes.

**Le canal DMA a un sens.** Le bit 0 du registre de contrôle dit qui alimente
qui. Je le supposais toujours « la mémoire vers le GPU » ; `StoreImage` fait
l'inverse. Résultat : le contenu de la pile était poussé dans le GPU, qui le
lisait comme des commandes — d'où des copies internes tirées de nulle part qui
barbouillaient le tampon d'affichage avec de la texture.

**Les commandes du lecteur qui font bouger le mécanisme répondent deux fois.**
J'en avais implémenté quelques-unes ; `SetSession` manquait, et c'est celle que
le jeu envoie juste après avoir chargé ses données, au moment où il passe à la
piste audio. Le pilote attendait un achèvement qui ne venait pas et déclarait
un délai dépassé — le chargement s'arrêtait là.

**`InitGeom` était un bouchon.** La fonction qui arme le GTE dans le registre
d'état du coprocesseur système règle aussi ZSF3 et ZSF4, les facteurs qui
convertissent une profondeur en indice de table d'affichage. Le traducteur
refusait la fonction pour son unique instruction COP0, je l'avais remplacée par
un bouchon silencieux — et sans ZSF3/ZSF4, `avsz4` rendait zéro pour tous les
polygones. Le jeu, qui jette ce qui tombe à l'indice zéro, jetait la piste
entière : seul le ciel se dessinait. Le traducteur modélise désormais le COP0
par un tableau de registres, et `syscall` par un appel.

La leçon est la même que celle du chapitre précédent : un bouchon silencieux ne
casse pas là où il est. Celui-ci se manifestait à cinq fonctions de distance,
sous la forme d'une image sans route.

Résultat : la démonstration tourne. La ligne droite de départ, le tunnel, le
pont suspendu, les voitures. 908 064 commandes GPU en quatre-vingt-dix
secondes, 3 236 images, aucun secteur manquant.

## M4 : la manette

Le BIOS ne lit pas la manette à la demande. `InitPAD` lui donne l'adresse de
deux tampons, `StartPAD` arme le remplissage, et le jeu consulte ces quatre
octets quand il veut : un état, un type, et seize boutons actifs à zéro. Trois
appels BIOS de plus, et le jeu cesse d'être une démonstration.

L'entrée vient d'un **scénario** écrit d'avance plutôt que d'un clavier —
`MANETTE="60000:start 63000: 90000:start 93000: 140000:start"` — pour que deux
exécutions donnent exactement la même image. Une session interactive viendra
avec le portage OpenGL ; en attendant, un scénario est ce qui rend un défaut
reproductible, et donc trouvable.

Ce scénario-là traverse l'écran-titre, ouvre le menu (`COURSE SELECT`,
`MISSION SELECT`, `CAR SELECT`, `SOUND SELECT`) et lance la course. Le tableau
de bord s'affiche entier : tour, position, temps au tour, record, total, la
carte du circuit, le compte-tours et le rapport engagé.

## Ce qui reste

- **Le son.** `ss_init error / 3312 > 3264` est le diagnostic du jeu lui-même :
  le banc SPU n'est pas modélisé du tout, et les 24 voix ne sont que des
  registres qu'on compte.
- **La vitesse.** Le rastériseur logiciel tient quelques images par seconde. Le
  flux GP0 est déjà exactement ce qu'il faut donner à OpenGL ; c'est la
  prochaine étape naturelle, et elle rendra le jeu interactif.
- **Les fonctions décompilées.** L'intérêt de tout ceci est là : chaque
  fonction byte-matched remplace sa jumelle traduite dans `table.c`, et le jeu
  continue de tourner à chaque remplacement.

## M6 : le temps compté plutôt que deviné

Une recompilation statique perd la seule chose qui donnait son rythme au jeu :
le temps que prenait chaque instruction. Ce n'est pas un désaccord entre deux
cadences, comme le 50/60 Hz de l'époque PAL — c'est l'**absence** de cadence.
Il faut donc en fabriquer une, et le choix décide de tout.

L'horloge a d'abord battu sur les accès mémoire, faute de mieux. Substitut
commode et faux : il fallait ensuite pousser le temps à la main quand le jeu
attendait sans rien lire, et le compteur de balayages ne voulait plus rien
dire.

Elle compte maintenant ce que la machine comptait.

**Le processeur.** Le traducteur facture chaque bloc rectiligne : entre deux
transferts de contrôle on sait exactement combien d'instructions vont
s'exécuter, donc une addition par bloc suffit — 16 518 `CYCLES(n)` pour les 949
fonctions. Le balayage tombe quand le budget d'une image est épuisé.

**Le dessin.** Le GPU remplissait environ un pixel par cycle à 53,2 MHz, soit
887 000 pixels entre deux balayages. Les pixels écrits par le rastériseur sont
convertis dans la même monnaie et retranchés du budget. Sans ce compte, une
scène chargée coûte le même temps qu'une scène vide, et le jeu tourne trop vite
exactement là où il ralentissait.

**L'attente se facture, elle ne se joue pas.** `VSync` fait tourner le
processeur à vide jusqu'au balayage suivant. Simuler cette attente instruction
par instruction serait fidèle et absurde : on avance l'horloge jusqu'à
l'échéance, ce que ces cycles auraient fait de toute façon. C'est le même geste
que la détection de boucle d'attente des émulateurs, mais il ne fabrique plus
un balayage de nulle part — il constate une dépense.

### Ce que la mesure a répondu

Deux questions restaient ouvertes, et le compte les tranche.

*Le jeu vise-t-il 30 ou 60 images par seconde ?* Les quinze appels à `VSync` du
binaire passent tous **1**, jamais 2 : le code demande un balayage par image.
Et les pixels le confirment — **73 000 par table d'affichage**, deux tables par
image, contre 887 000 que le matériel tenait. Ridge Racer utilisait moins du
quart du budget de remplissage. Les 30 images par seconde qu'on lui prête ne
sont pas ce qu'il demandait.

*À quelle vitesse tourne la traduction ?* **1,7 milliard d'instructions par
seconde**, soit une cinquantaine de fois un R3000. C'est pourquoi la bride à
60 Hz de la fenêtre n'est pas un confort mais une nécessité.

## M7 : la musique

Le jeu ne demandait jamais `Play`, et j'ai longtemps cru que la musique
attendait un synthétiseur. Elle attendait une réponse : `GetTN` lui annonçait
**une seule piste**. Dès qu'on lui dit qu'il y en a treize, il réclame `GetTD`
pour chacune, cherche avec `SeekP`, et lance `Play`.

Parce que la bande-son de Ridge Racer n'est pas synthétisée. Ce sont douze
pistes audio ordinaires, gravées à côté des données, que la console lisait avec
le même mécanisme que n'importe quel disque compact. Il n'y avait donc rien à
écrire pour l'entendre — seulement des secteurs à servir.

Le format tombe juste : un secteur audio fait 2352 octets, soit exactement 588
trames stéréo de seize bits à 44 100 Hz. Ni conversion ni rééchantillonnage.

**Qui donne le rythme.** La carte son, pas notre horloge. Tant que sa file est
assez remplie, on ne lit pas de secteur. Accorder les deux cadences aurait
demandé qu'elles restent d'accord, ce qu'elles ne font jamais bien longtemps —
et une dérive de quelques millièmes s'entend, là où elle ne se voit pas.

`build.py` lit la feuille `.cue` et calcule les positions absolues en cumulant
les longueurs de fichiers, un secteur brut faisant 2352 octets. L'`INDEX 01`
donne le début réel de chaque piste, après les deux secondes de silence que
porte son fichier — les oublier décalerait toute la musique.

Le jeu réclame la piste 8 au menu. Reste le SPU, pour le moteur.

## M8 : le SPU

`ss_init error` accusait le SPU absent ; il a disparu dès que les vingt-quatre
voix ont existé. Mais il fallait d'abord démêler ce que le jeu disait.

**`3312 > 3264` n'était pas un défaut.** Ces deux nombres sortent d'un `printf`
aux constantes figées dans le binaire — `li a1,0xCF0`, `li a2,0xCC0` — imprimé
sans condition, dans une fonction qui ne fait rien d'autre qu'initialiser un
pointeur. C'est un avertissement de développeur que Namco a expédié tel quel
vers le port série que personne ne branche. Il s'imprime aussi sur une console.
Seul `ss_init error`, conditionnel lui, nous accusait.

**Le blocage était ailleurs que dans le son.** Une fois l'initialisation
réussie, le jeu allait plus loin et s'endormait sur un événement de fin de
transfert DMA que nous ne délivrions pas. Le registre de contrôle du DMA porte
les autorisations dans ses bits 16 à 22 et les drapeaux dans les bits 24 à 30 ;
sans lui, l'événement n'arrive jamais. Le jeu n'a pas planté — il a attendu,
seize images en deux minutes.

**Ce qui marche** : la mémoire du SPU et son transfert (491 072 octets d'un
coup, la banque entière), la décompression ADPCM avec ses boucles, la hauteur,
les volumes, l'allumage et l'extinction. Crête mesurée à 35 574 sur du
saturé — les voix produisent bien du son.

**Ce qui ne marche pas encore, et qui se compte** : le jeu allume ses voix
alors que `SPUCNT` vaut zéro. Sur la console cela ne produirait rien, donc il
ne le ferait pas : le défaut est chez nous, dans un registre d'état modélisé à
moitié, dont le pilote dérive la valeur qu'il réécrit. Plutôt que de rendre le
silence en attendant d'avoir compris, on mélange et on compte — 288 voix par
minute de jeu. Ce compteur est la mesure exacte de ce qui reste à comprendre,
et il figure dans l'état des lieux à chaque exécution.

### L'écart n'était pas dans le SPU

Le compteur des voix allumées « SPU éteint » a fait son travail plus vite que
prévu : il a désigné la faute, qui n'était pas là où le symptôme s'affichait.

Le pilote fait un lire-modifier-écrire tout à fait propre sur `SPUCNT` —
`lhu 0x1AA`, `andi`, `ori`, `sh 0x1AA`. Le bit d'activation ne pouvait se
perdre que si la **lecture** rendait autre chose. Elle rendait autre chose :

```c
if (p >= 0x1F801000) return hw_read32(p & ~3u) >> (8 * (p & 2));
```

Une lecture de seize bits n'est pas une lecture de trente-deux dont on prend
une moitié. Rabattre l'adresse sur le mot inférieur faisait lire le registre
**voisin** — `SPUCNT` en 0x1F801DAA rendait la file de transfert du SPU,
c'est-à-dire zéro. Le pilote y perdait l'activation à chaque passage.

La moitié des registres du SPU sont à une adresse congrue à 2 modulo 4, donc
la moitié se lisaient faux. Une lecture par demi-mot digne de ce nom les sert
maintenant tels quels.

Deux choses valent d'être retenues. La première est que ce défaut vivait dans
`rt.h` depuis le premier jour, invisible : rien avant le SPU ne lisait un
registre par demi-mot à une adresse impaire en mots. La seconde est que le
compteur a suffi — mettre un nombre sur un écart plutôt que de le décrire
donne quelque chose à faire tomber à zéro.

### L'enveloppe, pour de vrai

Restait une approximation déclarée : les pentes de l'enveloppe. Elles suivent
maintenant le matériel. Le principe est le même dans les quatre phases — un
décalage donne la période, un pas donne l'amplitude — mais le couple se lit à
un endroit différent du registre selon la phase, et deux règles s'ajoutent en
mode exponentiel : une montée ralentit d'un facteur quatre passé les trois
quarts, une descente se proportionne au niveau atteint. C'est cette seconde
règle qui donne aux extinctions leur traînée, et une pente linéaire ne peut
pas l'imiter.

Avant de l'écrire, une mesure a écarté l'autre approximation qui traînait. Les
volumes du matériel peuvent être une valeur fixe ou un balayage ; nous
approchions les balayages par leur valeur de départ. Le compteur dit **20 343
volumes simples et zéro balayage** : ce jeu ne s'en sert jamais. L'approximation
reste, documentée, mais on sait maintenant qu'elle ne coûte rien ici — et le
compteur le redira si un autre jeu passe par là.

Compter avant de corriger a évité d'écrire du code exact pour un chemin mort,
juste après avoir compté pour trouver un chemin faux.
