# M0 — l'exécutable natif qui démarre

Ce dossier contient l'environnement d'exécution ; le code du jeu lui-même est
**généré** par `tools/recomp.py` depuis ta propre copie de `PSX.EXE` et n'est
pas versionné, comme le reste du désassemblage.

```
python3 tools/recomp.py PSX.EXE asm/psyq.s <fonctions...>  > game.c
gcc -O0 -I tools/m0 -o m0 tools/m0/main.c tools/m0/hw.c tools/m0/gte.c game.c table.c
./m0 15
```

- `rt.h` — la mémoire : 2 Mo de RAM, le bloc-notes de 1 Ko, et l'aiguillage
  vers les registres matériels. Le piège qu'il désamorce : masquer toutes les
  adresses sur 21 bits ferait tomber le GPU en pleine RAM.
- `hw.c` — le GPU vu de loin : il journalise les paquets au lieu de dessiner,
  et déroule les tables d'affichage que le DMA lui présente.
- `gte.c` — le coprocesseur géométrique, vérifié à part (voir `gte_check.py`).
- `main.c` — le chargeur, l'aiguillage des appels indirects, et les appels
  BIOS.
