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
