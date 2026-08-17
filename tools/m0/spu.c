/* Le SPU : les vingt-quatre voix.
 *
 * La musique venait du disque et ne demandait qu'à être servie. Le reste --
 * le moteur, les crissements, les voix -- vient d'ici : un demi-mégaoctet de
 * mémoire à part, rempli par le canal 4 du DMA, et vingt-quatre lecteurs qui
 * y puisent des échantillons compressés, chacun à sa hauteur et son volume.
 *
 * Ce qui est implémenté
 * ---------------------
 * La mémoire et son transfert, la décompression ADPCM avec ses boucles, la
 * hauteur, les volumes gauche et droit, l'allumage et l'extinction des voix,
 * et une enveloppe. Le mélange se fait à 44 100 Hz, la fréquence de sortie du
 * matériel, ce qui évite tout rééchantillonnage en sortie.
 *
 * Ce qui est simplifié, et il faut le dire
 * ----------------------------------------
 * L'enveloppe du matériel a quatre phases dont les pentes suivent des tables
 * exponentielles précises. Celle-ci en garde la forme -- montée, chute,
 * maintien, extinction -- avec des pentes linéaires par morceaux. Un son tenu
 * sonnera juste ; une attaque très courte le sera moins. La réverbération
 * n'est pas implémentée du tout : le jeu en écrit les registres, on les
 * accepte et on les ignore.
 */
#include <string.h>
#include <stdio.h>
#include "rt.h"

u8 SPURAM[0x80000];

/* --- une voix ------------------------------------------------------------ */
struct voix {
    u16 vol_g, vol_d;      /* volumes, format materiel */
    u16 pas;               /* hauteur : 0x1000 = 44100 Hz */
    u16 depart, boucle;    /* adresses, en blocs de huit octets */
    u32 adsr;              /* les deux registres d'enveloppe */
    /* etat de lecture */
    u32 addr;              /* octet courant dans la memoire du SPU */
    u32 phase;             /* position fractionnaire, 12 bits */
    s16 ech[28];           /* le bloc decode */
    int n;                 /* combien d'echantillons y restent */
    s16 p1, p2;            /* les deux precedents, pour le filtre */
    int actif;
    int fin;               /* le bloc portait la marque de fin */
    /* enveloppe */
    int phase_env;         /* 0 arret, 1 montee, 2 chute, 3 maintien, 4 extinction */
    int niveau;            /* 0 a 0x7FFF */
    int env_attente;       /* cycles restants avant le pas suivant */
};

static struct voix v[24];
static u16 ctrl, transfert_ctrl;
static u32 transfert_addr;
static u16 vol_principal_g, vol_principal_d;
unsigned long spu_voix_jouees;
int spu_crete;          /* la plus forte amplitude produite */
unsigned long spu_voix_eteint;
unsigned long spu_balayages, spu_vol_simples;

/* --- decompression ------------------------------------------------------- */
static const int filtre_pos[5] = { 0, 60, 115, 98, 122 };
static const int filtre_neg[5] = { 0, 0, -52, -55, -60 };

static s16 sature(int x)
{
    if (x < -32768) return -32768;
    if (x > 32767) return 32767;
    return (s16)x;
}

static void bloc_suivant(struct voix *w)
{
    const u8 *b = SPURAM + (w->addr & 0x7FFF0);
    int decalage = b[0] & 0x0F;
    int filtre = (b[0] >> 4) & 0x0F;
    int drapeaux = b[1];
    int i;
    if (filtre > 4) filtre = 4;
    if (decalage > 12) decalage = 9;       /* le materiel traite ainsi les
                                              valeurs interdites */
    for (i = 0; i < 28; i++) {
        int brut = (b[2 + i / 2] >> ((i & 1) * 4)) & 0x0F;
        int e = (int)((s16)(brut << 12)) >> decalage;
        e += (w->p1 * filtre_pos[filtre] + w->p2 * filtre_neg[filtre]) / 64;
        w->ech[i] = sature(e);
        w->p2 = w->p1;
        w->p1 = w->ech[i];
    }
    w->n = 28;
    /* Le bit 2 designe le point de retour, le bit 0 la fin du son. Sans le
       bit 1, la fin arrete la voix ; avec, elle y revient. */
    if (drapeaux & 4) w->boucle = (u16)((w->addr & 0x7FFF0) >> 3);
    if (drapeaux & 1) {
        w->fin = 1;
        w->addr = (u32)w->boucle << 3;
        if (!(drapeaux & 2)) { w->phase_env = 4; w->env_attente = 1; }
    } else {
        w->addr += 16;
    }
}

/* --- enveloppe ------------------------------------------------------------
 *
 * Les quatre phases du materiel, avec leurs vraies pentes.
 *
 * Le principe est le meme partout : un decalage donne la periode, un pas donne
 * l'amplitude, et le couple se lit dans le registre selon la phase. Au-dela de
 * onze, le decalage espace les mises a jour ; en deca, il amplifie le pas. En
 * mode exponentiel, une montee ralentit d'un facteur quatre passe les trois
 * quarts, et une descente se proportionne au niveau atteint -- c'est ce qui
 * donne aux extinctions leur trainee.
 *
 * La chute a un pas fixe de -8 et est toujours exponentielle ; les autres
 * phases lisent leur mode dans le registre.
 */
static void enveloppe(struct voix *w)
{
    int decalage, pas, expo, decroit, cible = -1;
    if (w->phase_env == 0) { w->niveau = 0; return; }
    if (--w->env_attente > 0) return;
    switch (w->phase_env) {
    case 1:                                   /* montee */
        decalage = (w->adsr >> 10) & 0x1F;
        pas = 7 - ((w->adsr >> 8) & 3);
        expo = (w->adsr >> 15) & 1;
        decroit = 0;
        break;
    case 2:                                   /* chute */
        decalage = (w->adsr >> 4) & 0x0F;
        pas = -8; expo = 1; decroit = 1;
        cible = (int)((w->adsr & 0x0F) + 1) * 0x800;
        if (cible > 0x7FFF) cible = 0x7FFF;
        break;
    case 3:                                   /* maintien */
        decalage = (w->adsr >> 24) & 0x1F;
        decroit = (w->adsr >> 30) & 1;
        pas = decroit ? (-8 + (int)((w->adsr >> 22) & 3))
                      : (7 - (int)((w->adsr >> 22) & 3));
        expo = (w->adsr >> 31) & 1;
        break;
    default:                                  /* extinction */
        decalage = (w->adsr >> 16) & 0x1F;
        pas = -8; expo = (w->adsr >> 21) & 1; decroit = 1;
        break;
    }
    {
        int cycles = 1 << (decalage > 11 ? decalage - 11 : 0);
        int amplitude = pas << (decalage < 11 ? 11 - decalage : 0);
        if (expo) {
            if (!decroit && w->niveau > 0x6000) cycles *= 4;
            if (decroit) amplitude = (int)((long)amplitude * w->niveau / 0x8000);
        }
        w->niveau += amplitude;
        if (w->niveau > 0x7FFF) w->niveau = 0x7FFF;
        if (w->niveau < 0) w->niveau = 0;
        w->env_attente = cycles;
    }
    if (w->phase_env == 1 && w->niveau >= 0x7FFF) w->phase_env = 2;
    else if (w->phase_env == 2 && cible >= 0 && w->niveau <= cible) w->phase_env = 3;
    else if (w->phase_env == 4 && w->niveau <= 0) { w->phase_env = 0; w->actif = 0; }
}

/* Les volumes du materiel sont signes sur quinze bits quand le bit de poids
   fort est a zero ; sinon c'est un balayage, qu'on approche par sa valeur de
   depart. */
static int volume(u16 r)
{
    if (r & 0x8000) return 0x3FFF;
    return (int)(s16)(r << 1) / 2;
}

/* --- melange ------------------------------------------------------------- */
void spu_melanger(s16 *sortie, int trames)
{
    int i, k;
    for (i = 0; i < trames; i++) { sortie[2 * i] = 0; sortie[2 * i + 1] = 0; }
    /* Le bit d'activation est respecte. Il ne l'a pas toujours ete : le jeu
       allumait ses voix alors que ce registre valait zero, ce qui sur la
       console ne produirait rien -- donc il ne le faisait pas, et le defaut
       etait chez nous. Il n'etait pas dans le SPU mais dans la lecture par
       demi-mot, qui rendait le registre voisin. Le compteur ci-dessous reste
       en place : il vaut zero, et c'est ce zero qui atteste. */
    if (!(ctrl & 0x8000)) return;
    for (k = 0; k < 24; k++) {
        struct voix *w = &v[k];
        int g, d;
        if (!w->actif) continue;
        g = volume(w->vol_g);
        d = volume(w->vol_d);
        for (i = 0; i < trames; i++) {
            s16 e;
            if (!w->actif) break;
            if (w->n <= 0) { bloc_suivant(w); if (!w->actif) break; }
            e = w->ech[28 - w->n];
            {
                int a = (int)e * w->niveau >> 15;
                int gg = sortie[2 * i] + (a * g >> 14);
                int dd = sortie[2 * i + 1] + (a * d >> 14);
                sortie[2 * i] = sature(gg);
                sortie[2 * i + 1] = sature(dd);
                if (gg > spu_crete) spu_crete = gg;
                if (-gg > spu_crete) spu_crete = -gg;
            }
            /* L'avance depend de la hauteur : 0x1000 lit un echantillon par
               trame de sortie, le double en lit deux. */
            w->phase += (w->pas > 0x3FFF) ? 0x3FFF : w->pas;
            while (w->phase >= 0x1000) {
                w->phase -= 0x1000;
                if (--w->n <= 0) { bloc_suivant(w); if (!w->actif) break; }
            }
            enveloppe(w);
        }
    }
}

int spu_actif(void)
{
    int k;
    for (k = 0; k < 24; k++) if (v[k].actif) return 1;
    return 0;
}

/* --- registres ----------------------------------------------------------- */
static void allumer(u32 masque)
{
    int k;
    for (k = 0; k < 24; k++)
        if (masque & (1u << k)) {
            struct voix *w = &v[k];
            w->addr = (u32)w->depart << 3;
            w->boucle = w->depart;
            w->phase = 0; w->n = 0; w->p1 = w->p2 = 0;
            w->actif = 1; w->fin = 0;
            w->phase_env = 1; w->niveau = 0; w->env_attente = 1;
            spu_voix_jouees++;
            if (!(ctrl & 0x8000)) spu_voix_eteint++;
        }
}

static void eteindre(u32 masque)
{
    int k;
    for (k = 0; k < 24; k++)
        if (masque & (1u << k)) { v[k].phase_env = 4; v[k].env_attente = 1; }
}

void spu_write16(u32 adresse, u16 valeur)
{
    /* Les registres commencent en 0x1F801C00 : les voix d'abord, seize octets
       chacune, puis le controle a partir de 0x180. */
    u32 p = (adresse - 0x1F801C00u) & 0xFFF;
    if (p < 0x180) {                           /* les vingt-quatre voix */
        struct voix *w = &v[p >> 4];
        switch (p & 0x0F) {
        case 0x0: w->vol_g = valeur; if (valeur & 0x8000) spu_balayages++; else spu_vol_simples++; break;
        case 0x2: w->vol_d = valeur; break;
        case 0x4: w->pas = valeur; break;
        case 0x6: w->depart = valeur; break;
        case 0x8: w->adsr = (w->adsr & 0xFFFF0000u) | valeur; break;
        case 0xA: w->adsr = (w->adsr & 0xFFFFu) | ((u32)valeur << 16); break;
        case 0xC: break;                       /* volume courant, en lecture */
        case 0xE: w->boucle = valeur; break;
        }
        return;
    }
    switch (p) {
    case 0x180: vol_principal_g = valeur; break;
    case 0x182: vol_principal_d = valeur; break;
    /* Ecrire dans ces registres declenche : chaque bit pose allume ou eteint
       sa voix sur-le-champ, moitie basse et moitie haute independamment. */
    case 0x188: allumer(valeur); break;
    case 0x18A: allumer((u32)valeur << 16); break;
    case 0x18C: eteindre(valeur); break;
    case 0x18E: eteindre((u32)valeur << 16); break;
    case 0x1A6: transfert_addr = (u32)valeur << 3; break;
    case 0x1A8:                                /* la file de transfert */
        if (transfert_addr < sizeof SPURAM - 1) {
            SPURAM[transfert_addr] = (u8)valeur;
            SPURAM[transfert_addr + 1] = (u8)(valeur >> 8);
            transfert_addr += 2;
        }
        break;
    case 0x1AA: ctrl = valeur; break;
    case 0x1AC: transfert_ctrl = valeur; break;
    default: break;
    }
}

u16 spu_read16(u32 adresse)
{
    /* Les registres commencent en 0x1F801C00 : les voix d'abord, seize octets
       chacune, puis le controle a partir de 0x180. */
    u32 p = (adresse - 0x1F801C00u) & 0xFFF;
    if (p < 0x180) {
        struct voix *w = &v[p >> 4];
        switch (p & 0x0F) {
        case 0x0: return w->vol_g;
        case 0x2: return w->vol_d;
        case 0x4: return w->pas;
        case 0x6: return w->depart;
        case 0x8: return (u16)w->adsr;
        case 0xA: return (u16)(w->adsr >> 16);
        case 0xC: return (u16)w->niveau;
        case 0xE: return w->boucle;
        }
    }
    switch (p) {
    case 0x1AA: return ctrl;
    case 0x1AC: return transfert_ctrl;
    /* L'etat : le bit 10 dit que le transfert est fini, ce qu'il est toujours
       chez nous, et les bits bas reprennent le controle. */
    case 0x1AE: return (u16)((ctrl & 0x3F) | 0x0000);
    case 0x1B8: case 0x1BA: return 0;
    default: return 0;
    }
}

/* Le canal 4 du DMA verse les echantillons dans la memoire du SPU. */
void spu_dma(const u8 *ram, u32 adresse, u32 octets)
{
    u32 i;
    for (i = 0; i < octets; i++) {
        if (transfert_addr >= sizeof SPURAM) break;
        SPURAM[transfert_addr++] = ram[(adresse + i) & 0x1FFFFF];
    }
}
