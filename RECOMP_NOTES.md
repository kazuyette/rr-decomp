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

**120 cas — cinq fonctions, vingt-quatre vecteurs chacune — et aucune
divergence.** `_get_tw`, `MargePrim`, `SetLineG3`, `TermPrim` et
`SetSemiTrans` rendent octet pour octet ce que rend le vrai code.

Ce n'est pas un grand nombre de fonctions, mais c'est la bonne question posée
de la bonne façon : la référence n'est pas ma lecture du code, c'est son
exécution.

## Trois erreurs que le banc a attrapées

Chacune aurait produit du code plausible et faux.

**Les sauts absolus.** L'opcode `j` n'encode que les 28 bits bas de sa cible.
Ma première version calculait `(w & 0x3FFFFFF) << 2` en oubliant les quatre
bits hauts du compteur de programme. Côté référence, le même oubli déplaçait le
code et envoyait `MargePrim` dans le vide — d'où le chargement des fonctions à
leur adresse d'origine masquée sur 28 bits.

**Le créneau de retard.** L'instruction qui suit un branchement s'exécute avant
lui, pris ou non. Émise après le `goto`, elle donne du code qui marche partout
sauf là où le créneau modifie le registre testé. Le traducteur la déplace donc
systématiquement devant, après avoir figé la condition.

**Les entrées que la console refuserait.** Mes premiers vecteurs passaient des
pointeurs non alignés : `SIGBUS` immédiat, comme sur le vrai matériel. Le banc
doit poser des questions que la console pouvait entendre.

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
- **un harnais qui tient la charge** : à quarante fonctions, la construction
  du banc devient très lente, et certaines fonctions nourries d'entrées
  quelconques partent en boucle sans fin sous qemu. Une alarme par cas et une
  génération en deux temps sont en place mais pas encore validées.

Rien de tout cela ne remet en cause la fidélité mesurée sur les cinq premières.
