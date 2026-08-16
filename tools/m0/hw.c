/* Le matériel, vu de très loin : ce qu'il faut pour que le jeu tourne et
 * qu'on voie ce qu'il envoie à l'écran. Rien de plus.
 *
 * M0 ne cherche pas à afficher. Il cherche à établir que la boucle du jeu
 * s'exécute, et la preuve qu'on en attend est un flux de paquets GPU cohérent
 * — des commandes reconnaissables, des coordonnées plausibles. Un GPU qui
 * dessine viendrait ensuite ; un GPU qui journalise suffit à trancher.
 */
#include <stdio.h>
#include <string.h>
#include "rt.h"

u8 RAM[0x200000];
u8 SPAD[0x400];
u32 g_sp;

/* --- journal GPU ------------------------------------------------------- */
unsigned long gp0_words, gp1_cmds, prim_count;
unsigned long prim_hist[256];
static int gp0_left;          /* mots restants du paquet en cours */
static unsigned gp0_cmd;

FILE *gpulog;

static void gp0_write(u32 v)
{
    gp0_words++;
    if (gp0_left == 0) {
        gp0_cmd = v >> 24;
        prim_hist[gp0_cmd]++;
        prim_count++;
        /* Longueur des commandes de dessin les plus courantes. Les autres
           passent pour un mot, ce qui suffit à un journal. */
        switch (gp0_cmd & 0xE0) {
        case 0x20: {           /* polygones */
            int quad = (gp0_cmd & 8) ? 4 : 3;
            int tex  = (gp0_cmd & 4) ? 1 : 0;
            int grad = (gp0_cmd & 0x10) ? 1 : 0;
            gp0_left = quad * (1 + tex + grad) + (grad ? 0 : 1) - 1;
            break;
        }
        case 0x60: gp0_left = (gp0_cmd & 4) ? 3 : 2; break;   /* rectangles */
        case 0x40: gp0_left = 3; break;                        /* lignes */
        case 0xA0: case 0xC0: gp0_left = 2; break;             /* transferts */
        default:   gp0_left = 0; break;
        }
        if (gpulog && prim_count < 200)
            fprintf(gpulog, "GP0 %02X\n", gp0_cmd);
    } else {
        gp0_left--;
    }
}

/* --- DMA canal 2 : la table d'affichage ---------------------------------
 *
 * Le jeu ne parle presque jamais au GPU directement : il construit une liste
 * chaînée en RAM et demande au DMA de la dérouler. Dérouler cette liste ici,
 * c'est voir exactement ce qu'une image contient. */
static u32 dma2_madr, dma2_bcr, dma2_chcr;
unsigned long ot_lists, ot_nodes;

static void dma2_run(void)
{
    u32 addr = dma2_madr & 0x1FFFFC;
    int guard = 0;
    ot_lists++;
    while (guard++ < 200000) {
        u32 header, n, i;
        __builtin_memcpy(&header, RAM + addr, 4);
        n = header >> 24;
        ot_nodes++;
        for (i = 0; i < n; i++) {
            u32 w;
            __builtin_memcpy(&w, RAM + ((addr + 4 + i * 4) & 0x1FFFFC), 4);
            gp0_write(w);
        }
        if ((header & 0xFFFFFF) == 0xFFFFFF) break;
        addr = (header & 0x1FFFFC);
    }
    dma2_chcr &= ~0x01000000u;
}

/* --- registres ---------------------------------------------------------- */
unsigned long hw_writes, hw_reads;
static u32 vblank_counter;

u32 hw_read32(u32 p)
{
    hw_reads++;
    switch (p) {
    case 0x1F801810: return 0;             /* GPUREAD */
    case 0x1F801814:
        /* GPUSTAT. Les bits qui comptent pour que le jeu avance : prêt à
           recevoir une commande, prêt pour un DMA, et le bit d'image qui
           bascule -- sans lui, toute attente de synchro tourne sans fin. */
        vblank_counter++;
        return 0x1C000000u | ((vblank_counter & 1) ? 0x80000000u : 0u);
    case 0x1F8010A0: return dma2_madr;
    case 0x1F8010A4: return dma2_bcr;
    case 0x1F8010A8: return dma2_chcr;
    case 0x1F801070: return 1;             /* I_STAT : VBlank en attente */
    case 0x1F801074: return 0xFFFF;        /* I_MASK */
    default: return 0;
    }
}

void hw_write32(u32 p, u32 v, int width)
{
    (void)width;
    hw_writes++;
    switch (p) {
    case 0x1F801810: gp0_write(v); break;
    case 0x1F801814: gp1_cmds++; break;
    case 0x1F8010A0: dma2_madr = v; break;
    case 0x1F8010A4: dma2_bcr = v; break;
    case 0x1F8010A8:
        dma2_chcr = v;
        if (v & 0x01000000u) dma2_run();
        break;
    default: break;
    }
}
