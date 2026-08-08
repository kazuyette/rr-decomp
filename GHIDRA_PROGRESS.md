# Avancement Ghidra - reverse de PSX.EXE

Import : processeur MIPS little-endian, Base Address 0x80010000, File Offset 0x800 (l'en-tete PS-X EXE fait 2048 octets et ne doit pas etre mappe en memoire), Length 0x67800, point d'entree 0x8003FA9C.

## Demarrage / boucle principale

- `_start` (0x8003fa9c) : crt0 - vide le BSS, appelle une trampoline BIOS A0h, puis `main()`, puis `trap(1)` (jamais atteint normalement)
- `main` (0x80012360) : inits puis boucle infinie - double buffering via le scratchpad (0x1f800000), dispatch machine a etats (table de pointeurs a 0x80070ea4, index _DAT_801d34f8, pas encore materialisee dans Ghidra), attente VSync, lecture manette, 3 appels de rendu par frame
- FUN_800121f4 : grosse init systeme - video, reset de globales, ecriture de valeurs 0xff/0x80 en scratchpad (probable calibration manette/analogique)

## Video / GPU

- `SetVideoMode` (0x80045440) : configuration video via une vtable `g_gpu_device`, envoie une commande GP1(08h) Display Mode (NTSC/PAL)
- `g_gpu_device` (0x8007736c) : pointeur vers une petite abstraction/vtable pour le GPU (+4 AddPrim, +0x10 envoi de paquet GP0 brut, +0x28 flags, +0x34 reset/mode) - le rendu ne passe pas directement par libgpu

## Manette

- `read_pad_input` (0x8002e778) : decode l'entree manette - ID 0x41 = pad digital standard, ID 0x23 = neGcon (le controleur volant/twist de Namco), confirme supporte nativement

## Son (SPU, 24 voix materielles)

- File d'evenements son sur 24 slots (0x8003aec0) -> dispatch vers un gestionnaire de voix (0x8004c74c) qui compare les parametres a la voix deja active sur le slot (anti-retrigger)
- `SpuVoiceKeyOn` (0x8004a130) : pose le bit du slot dans un masque KON 24 bits reparti sur deux registres 16 bits - correspond exactement au split materiel des registres KON du SPU PS1
- Lie aux fichiers disque RR.VH/RR.VB (banque VAB)

## BIOS / interruptions

- Deux idiomes distincts identifies : trampolines table A0h (syscalls classiques type memcpy) et trampoline table B0h (kernel - OpenEvent/EnableEvent, utilisee ici pour armer des interruptions timer, probablement le tick du sequenceur audio)

## Bloqueurs / pistes ouvertes

- Table d'etats du jeu (0x80070ea4) : contenu illisible via l'outillage MCP actuel (pas d'outil de lecture memoire brute) - necessite de la materialiser manuellement dans Ghidra (creer un tableau de pointeurs a cette adresse)
- FUN_80039fd4/FUN_80039d00 : mecanisme one-shot request/process dont le role exact reste a determiner
- Les fonctions SpuVoiceKeyOn/voix restent a confirmer plus finement (noms provisoires bases sur des correspondances fortes avec le hardware SPU, mais pas garantis a 100%)
