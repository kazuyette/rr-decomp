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

u32 psx_dispatch(u32, u32, u32, u32, u32, u32);

/* Le gestionnaire d'exceptions du jeu, installe par B0(19) HookEntryInt.
 *
 * Le pilote CD ne scrute pas le materiel : il compte des rappels. Sans
 * interruption livree, ses compteurs NoIntr, DataReady et Complete restent a
 * zero et il conclut au timeout -- ce qu'il ferait sur une console dont le
 * lecteur ne repondrait pas. Lui livrer ses interruptions, c'est lui rendre la
 * moitie manquante du dialogue. */
u32 g_irq_handler;
unsigned long irq_delivered;
static int in_irq;

void deliver_irq(void)
{
    if (!g_irq_handler || in_irq) return;
    in_irq = 1;
    irq_delivered++;
    psx_dispatch(g_irq_handler, 0, 0, 0, 0, 0);
    in_irq = 0;
}
unsigned long dispatch_misses;

/* Les appels BIOS. Le jeu y accède par des trampolines qui posent le numéro
 * d'appel dans $t1 et sautent en 0xA0, 0xB0 ou 0xC0. On ne les implémente pas
 * ici : on les compte. Savoir lesquels le jeu réclame, et dans quel ordre, dit
 * où il en est de son démarrage. */
/* --- le systeme d'evenements du BIOS -------------------------------------
 *
 * Le pilote CD n'attend pas le materiel : il attend un evenement. Le jeu en
 * ouvre un pour la classe 0xF0000009, et le BIOS est cense le delivrer quand
 * le lecteur repond. Sans ce chainon, la commande part, le contrôleur repond,
 * et personne ne le sait -- d'ou le timeout.
 */
#define NEV 32
static struct { u32 cls, spec, mode, func; int open, on, done; } ev[NEV];
static int nev;
unsigned long ev_delivered;

static u32 ev_open(u32 cls, u32 spec, u32 mode, u32 func)
{
    if (nev >= NEV) return 0xFFFFFFFFu;
    ev[nev].cls = cls; ev[nev].spec = spec; ev[nev].mode = mode;
    ev[nev].func = func; ev[nev].open = 1; ev[nev].on = 0; ev[nev].done = 0;
    return 0xF1000000u | (u32)nev++;
}

static int ev_index(u32 d) { u32 i = d & 0xFFFF; return (i < (u32)nev) ? (int)i : -1; }

static void ev_deliver(u32 cls, u32 spec)
{
    int i;
    for (i = 0; i < nev; i++)
        if (ev[i].open && ev[i].on && ev[i].cls == cls) {
            ev_delivered++;
            /* Mode 0x1000 : rappel immediat. Sinon l'evenement est simplement
               marque et le jeu le releve par TestEvent. */
            if (ev[i].mode == 0x1000 && ev[i].func) {
                psx_dispatch(ev[i].func, spec, 0, 0, 0, 0);
            } else {
                ev[i].done = 1;
            }
        }
}

void cd_event(u32 spec) { ev_deliver(0xF0000009u, spec); }

static u32 bios_call(u32 vec, u32 fn, u32 a0, u32 a1, u32 a2, u32 a3)
{
    int v = (vec == 0xA0) ? 0 : (vec == 0xB0) ? 1 : 2;
    bios_calls[v][fn & 0xFF]++;
    /* La sequence, pas seulement le total : l'ordre des appels dit ou en est
       le demarrage bien mieux qu'un histogramme. */
    {
        static int seq;
        if (seq < 60 && !(vec == 0xA0 && (fn & 0xFF) == 0x3F)) {
            printf("[bios %c0(%02X) a0=%08X a1=%08X a2=%08X]\n",
                   "ABC"[v], fn & 0xFF, a0, a1, a2);
            fflush(stdout);
            seq++;
        }
    }
    /* A0(3F) est le printf du noyau. L'implementer coute dix lignes et rend
       au jeu sa propre voix : ce qu'il imprime pendant son demarrage dit
       exactement ou il en est, et aucune metrique exterieure ne le dirait
       aussi bien. */
    if (vec == 0xB0) {
        int i;
        switch (fn & 0xFF) {
        case 0x08: return ev_open(a0, a1, a2, a3);
        case 0x09: i = ev_index(a0); if (i >= 0) ev[i].open = 0; return 1;
        case 0x0B: i = ev_index(a0); if (i >= 0 && ev[i].done) { ev[i].done = 0; return 1; } return 0;
        case 0x0C: i = ev_index(a0); if (i >= 0) ev[i].on = 1; return 1;
        case 0x0D: i = ev_index(a0); if (i >= 0) ev[i].on = 0; return 1;
        case 0x07: ev_deliver(a0, a1); return 0;
        default: break;
        }
    }
    if (vec == 0xB0 && (fn & 0xFF) == 0x19) {
        /* HookEntryInt : le premier mot de la structure est l'adresse du
           gestionnaire. On la retient pour pouvoir l'appeler. */
        g_irq_handler = LW(a0);
        printf("[gestionnaire d'interruptions installe en %08X]\n", g_irq_handler);
        fflush(stdout);
        return 0;
    }
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
    printf("interruptions livrees      : %lu\n", irq_delivered);
    printf("evenements delivres        : %lu\n", ev_delivered);
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
        extern u32 hw_addr[]; extern unsigned long hw_rcnt[], hw_wcnt[]; extern int hw_naddr;
        int k;
        extern unsigned long cd_cmds[256];
        printf("commandes CD recues :\n");
        for (k = 0; k < 256; k++)
            if (cd_cmds[k]) {
                const char *n =
                    k == 0x01 ? "Nop" : k == 0x02 ? "Setloc" : k == 0x06 ? "ReadN" :
                    k == 0x09 ? "Pause" : k == 0x0A ? "Init" : k == 0x0C ? "Demute" :
                    k == 0x0E ? "Setmode" : k == 0x15 ? "SeekL" : k == 0x19 ? "Test" :
                    k == 0x1B ? "ReadS" : "?";
                printf("   %02X %-8s %lu fois\n", k, n, cd_cmds[k]);
            }
        printf("registres touches :\n");
        for (k = 0; k < hw_naddr; k++) {
            const char *w =
                (hw_addr[k] >= 0x1F801800 && hw_addr[k] <= 0x1F801803) ? "  <-- lecteur CD" :
                (hw_addr[k] >= 0x1F801810 && hw_addr[k] <= 0x1F801814) ? "  GPU" :
                (hw_addr[k] >= 0x1F8010A0 && hw_addr[k] <= 0x1F8010AC) ? "  DMA GPU" :
                (hw_addr[k] >= 0x1F8010B0 && hw_addr[k] <= 0x1F8010BC) ? "  DMA CD" :
                (hw_addr[k] == 0x1F801070 || hw_addr[k] == 0x1F801074) ? "  interruptions" :
                (hw_addr[k] >= 0x1F801100 && hw_addr[k] <= 0x1F801128) ? "  compteurs" :
                (hw_addr[k] >= 0x1F801C00) ? "  son" : "";
            printf("   %08X  %10lu lectures %8lu ecritures%s\n",
                   hw_addr[k], hw_rcnt[k], hw_wcnt[k], w);
        }
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
