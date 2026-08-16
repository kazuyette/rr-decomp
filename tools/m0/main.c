/* M0 : charger l'image, partir du point d'entrée, voir ce qui sort.
 *
 * Le jalon ne prétend pas afficher. Il prétend établir que la boucle du jeu
 * s'exécute réellement — et la preuve attendue est un flux de paquets GPU
 * cohérent : des commandes reconnaissables, en nombre plausible, groupées en
 * tables d'affichage. Une fenêtre noire prouverait moins.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "rt.h"
#include "gte.h"

extern const struct { u32 a; u32 (*f)(u32, u32, u32, u32); } PSX_FUNCS[];
extern const int PSX_NFUNCS;
extern unsigned long gp0_words, gp1_cmds, prim_count, prim_hist[256];
extern unsigned long ot_lists, ot_nodes, hw_writes, hw_reads;
extern FILE *gpulog;

#define ENTRY 0x8003FA9Cu

static unsigned long bios_calls[3][256];
unsigned long dispatch_misses;

/* Les appels BIOS. Le jeu y accède par des trampolines qui posent le numéro
 * d'appel dans $t1 et sautent en 0xA0, 0xB0 ou 0xC0. On ne les implémente pas
 * ici : on les compte. Savoir lesquels le jeu réclame, et dans quel ordre, dit
 * où il en est de son démarrage. */
static u32 bios_call(u32 vec, u32 fn, u32 a0, u32 a1, u32 a2, u32 a3)
{
    int v = (vec == 0xA0) ? 0 : (vec == 0xB0) ? 1 : 2;
    bios_calls[v][fn & 0xFF]++;
    /* A0(3F) est le printf du noyau. L'implementer coute dix lignes et rend
       au jeu sa propre voix : ce qu'il imprime pendant son demarrage dit
       exactement ou il en est, et aucune metrique exterieure ne le dirait
       aussi bien. */
    if (vec == 0xA0 && (fn & 0xFF) == 0x3F) {
        u32 p = a0 & 0x1FFFFF;
        u32 args[3]; int ai = 0;
        char out[512]; int o = 0;
        args[0] = a1; args[1] = a2; args[2] = a3;
        while (p < 0x200000 && RAM[p] && o < (int)sizeof out - 32) {
            char ch = (char)RAM[p++];
            if (ch != '%') { out[o++] = ch; continue; }
            {
                char spec = (char)RAM[p];
                while (spec && !strchr("diouxXcsfgep%", spec)) spec = (char)RAM[++p];
                p++;
                if (spec == 's') {
                    u32 q = (ai < 3 ? args[ai++] : 0) & 0x1FFFFF;
                    while (q < 0x200000 && RAM[q] && o < (int)sizeof out - 2) out[o++] = (char)RAM[q++];
                } else if (spec == '%') {
                    out[o++] = '%';
                } else {
                    o += sprintf(out + o, "%ld", (long)(s32)(ai < 3 ? args[ai++] : 0));
                }
            }
        }
        out[o] = 0;
        fputs(out, stdout);
        fflush(stdout);
        return 0;
    }
    return 0;
}

u32 psx_dispatch(u32 addr, u32 a0, u32 a1, u32 a2, u32 a3, u32 t1)
{
    int lo = 0, hi = PSX_NFUNCS - 1;
    if (addr == 0xA0 || addr == 0xB0 || addr == 0xC0)
        return bios_call(addr, t1, a0, a1, a2, a3);
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (PSX_FUNCS[mid].a == addr) return PSX_FUNCS[mid].f(a0, a1, a2, a3);
        if (PSX_FUNCS[mid].a < addr) lo = mid + 1; else hi = mid - 1;
    }
    dispatch_misses++;
    return 0;
}

static void report(int sig)
{
    int i, n = 0;
    if (sig) printf("\n--- interrompu apres %d s ---\n", 20);
    printf("paquets GPU        : %lu commandes, %lu mots\n", prim_count, gp0_words);
    printf("tables d'affichage : %lu deroulees, %lu noeuds\n", ot_lists, ot_nodes);
    printf("registres          : %lu ecritures, %lu lectures, %lu GP1\n",
           hw_writes, hw_reads, gp1_cmds);
    printf("sauts indirects sans cible : %lu\n", dispatch_misses);
    printf("commandes GP0 les plus frequentes :\n");
    for (i = 0; i < 256; i++)
        if (prim_hist[i] && n < 12) {
            const char *what =
                ((i & 0xE0) == 0x20) ? "polygone" :
                ((i & 0xE0) == 0x60) ? "rectangle" :
                ((i & 0xE0) == 0x40) ? "ligne" :
                (i == 0xE1) ? "mode de dessin" :
                (i == 0xE2) ? "fenetre de texture" :
                (i == 0xE3 || i == 0xE4) ? "zone de dessin" :
                (i == 0xE5) ? "decalage de dessin" :
                (i == 0xE6) ? "masque" :
                (i == 0x01) ? "vide le cache" :
                (i == 0x02) ? "remplissage" : "?";
            printf("   %02X  %-20s %lu\n", i, what, prim_hist[i]);
            n++;
        }
    {
        int v, f, m = 0;
        printf("appels BIOS :\n");
        for (v = 0; v < 3; v++)
            for (f = 0; f < 256; f++)
                if (bios_calls[v][f] && m < 12) {
                    printf("   %c0(%02X)  %lu fois\n", "ABC"[v], f, bios_calls[v][f]);
                    m++;
                }
        if (!m) printf("   aucun\n");
    }
    fflush(stdout);
    _exit(0);
}

int main(int argc, char **argv)
{
    FILE *f = fopen("/tmp/recomp/psx.img", "rb");
    int seconds = (argc > 1) ? atoi(argv[1]) : 20;
    if (!f || fread(RAM + 0x10000, 423936, 1, f) != 1) {
        fprintf(stderr, "image introuvable\n");
        return 1;
    }
    fclose(f);
    gpulog = fopen("/tmp/recomp/gpu.log", "w");

    /* L'en-tete de ce jeu ne donne pas de pile utilisable -- gp0 et s_addr y
       sont du bruit, ce qui n'etonne pas pour le tout premier titre de la
       console. On prend donc la pile par defaut du BIOS. */
    g_sp = 0x801FFF00u;

    signal(SIGALRM, report);
    alarm(seconds);
    printf("entree en %08X, %d fonctions dans la table\n", ENTRY, PSX_NFUNCS);
    fflush(stdout);
    psx_dispatch(ENTRY, 0, 0, 0, 0, 0);
    printf("--- le point d'entree est revenu ---\n");
    report(0);
    return 0;
}
