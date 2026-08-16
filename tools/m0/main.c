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

static u32 ENTRY;   /* lu dans l'en-tete de l'executable */

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
int in_irq_flag;
int g_longjmp;          /* fait rendre 1 a setjmp, le temps d'une interruption */

/* Le jeu n'installe pas une fonction : il sauvegarde un contexte.
 *
 *     setjmp(&contexte);
 *     if (v0 == 0) { HookEntryInt(&contexte); return; }
 *     ... corps du gestionnaire ...
 *
 * Sur la console, le BIOS revient dans ce contexte par longjmp a chaque
 * interruption, et l'execution reprend juste apres le setjmp, avec v0 non nul.
 * Une traduction par fonction ne peut pas sauter au milieu d'un cadre mort --
 * mais elle peut rappeler la fonction en faisant rendre 1 au setjmp, ce qui
 * emprunte exactement la meme branche. */
/* Rappeler func_800492B0 depuis le debut rejouait tout son prologue a chaque
 * interruption : elle rearme le masque, remet a zero deux tableaux et rappelle
 * func_800495DC. Autrement dit, chaque interruption effaçait l'etat que le
 * pilote venait d'etablir -- ce qui explique qu'aucune sequence n'aboutissait.
 *
 * Le corps du gestionnaire commence a 0x8004934C, juste apres le test qui suit
 * le setjmp. Traduit comme une fonction a part entiere, il s'execute sans
 * toucher au prologue. C'est la bonne facon de rendre un longjmp dans une
 * traduction par fonction : ne pas rejouer, entrer au bon endroit. */
u32 psx_irq_body(u32, u32, u32, u32);

/* Le service CD du BIOS.
 *
 * Le repartiteur du jeu ne traite que les interruptions dont il a enregistre
 * le rappel, et il n'en enregistre aucun pour le lecteur : il compte sur le
 * BIOS pour lire la reponse, acquitter, et appeler la fonction de
 * synchronisation qu'il a posee par CdSyncCallback.
 *
 * C'est donc ce service-la qu'il faut rendre -- pas emuler une image du BIOS,
 * mais reecrire la quinzaine de fonctions que ce jeu appelle. Celle-ci en fait
 * partie, et c'est le chainon qui manquait. */
#define CD_RESULT 0x801FFE00u
u32 cd_take_response(u8 *buf);   /* rend le type d'interruption, remplit buf */

static void bios_cd_service(void)
{
    u8 buf[16];
    u32 intr, cb, i;
    intr = cd_take_response(buf);
    if (!intr) return;
    for (i = 0; i < 16; i++) SB(CD_RESULT + i, buf[i]);
    cb = LW(0x801E9170u);            /* pose par CdSyncCallback */
    if (cb) psx_dispatch(cb, intr, CD_RESULT, 0, 0, 0);
}

void deliver_irq(void)
{
    if (in_irq) return;
    in_irq = 1;
    in_irq_flag = 1;
    irq_delivered++;
    /* Ne PAS relever la reponse ici : le jeu a enregistre son propre
       gestionnaire pour l'interruption 2, en D_800797A8[2], et le repartiteur
       l'appelle. Mon service BIOS lui volait l'interruption -- il effacait le
       drapeau et la reponse avant que le gestionnaire du jeu puisse les lire.
       Rendre un service que personne n'a demande est une facon discrete de
       casser une chaine qui marchait. */
    /* L'interruption emprunte la pile du code interrompu. Sur la console, le
       gestionnaire d'exception travaille sur sa propre pile et rend le
       contexte intact ; ici, la moindre asymetrie entre les prologues et les
       epilogues traduits fait deriver $sp d'une interruption a l'autre. Elle
       montait : au bout de quelques interruptions, les tampons alloues sur la
       pile tombaient au-dela des deux megaoctets et les ecritures etaient
       jetees en silence -- le jeu lisait alors une position de disque nulle et
       concluait « File not found ». On rend donc la pile telle qu'on l'a
       prise, ce que le materiel garantit et que la traduction ne garantit pas. */
    {
        u32 sp_sauve = g_sp;
        psx_irq_body(0, 0, 0, 0);
        g_sp = sp_sauve;
    }
    in_irq_flag = 0;
    in_irq = 0;
}
int g_seconds = 20;

/* Le journal détaillé -- appels BIOS et dialogue avec le lecteur -- est un
 * outil de mise au point, pas une sortie. Il servait a trouver ou le demarrage
 * s'arretait ; maintenant qu'il ne s'arrete plus, il ne fait que cacher ce que
 * le jeu lui-meme imprime. Il faut donc le demander : VERBEUX=1. */
int g_verbeux;
u32 g_pad_buf[2];
int g_pad_on;
u32 g_pad_boutons = 0xFFFF;   /* actifs a zero : rien d'enfonce */

/* Le scenario. Une liste « instant:touches », l'instant compte en battements
   de retour de balayage. Ecrit plutot qu'interactif, pour que deux executions
   donnent la meme image. */
static struct { unsigned long quand; u32 masque; } scenario[16];
static int nscenario;

void pad_ecrire(unsigned long tick)
{
    int i;
    u32 m = 0xFFFF;
    if (!g_pad_on) return;
    for (i = 0; i < nscenario; i++)
        if (tick >= scenario[i].quand) m = scenario[i].masque;
    g_pad_boutons = m;
    for (i = 0; i < 2; i++) {
        u32 p = g_pad_buf[i] & 0x1FFFFF;
        if (!p) continue;
        RAM[p + 0] = (i == 0) ? 0x00 : 0xFF;   /* seul le premier port existe */
        RAM[p + 1] = 0x41;                     /* manette numerique */
        RAM[p + 2] = (u8)(m >> 8);
        RAM[p + 3] = (u8)m;
    }
}

static u32 touche(const char *nom)
{
    if (!strcmp(nom, "start"))    return 0x0800;
    if (!strcmp(nom, "select"))   return 0x0100;
    if (!strcmp(nom, "haut"))     return 0x1000;
    if (!strcmp(nom, "droite"))   return 0x2000;
    if (!strcmp(nom, "bas"))      return 0x4000;
    if (!strcmp(nom, "gauche"))   return 0x8000;
    if (!strcmp(nom, "croix"))    return 0x0040;
    if (!strcmp(nom, "rond"))     return 0x0020;
    if (!strcmp(nom, "triangle")) return 0x0010;
    if (!strcmp(nom, "carre"))    return 0x0080;
    if (!strcmp(nom, "l1"))       return 0x0004;
    if (!strcmp(nom, "r1"))       return 0x0008;
    return 0;
}

/* « 400:start 460: 900:croix » -- instant, deux-points, touches separees par
   des virgules. Un instant sans touche relache tout. */
void scenario_lire(const char *s)
{
    while (s && *s && nscenario < 16) {
        char mot[64]; int o = 0; u32 m = 0xFFFF;
        unsigned long quand = 0;
        while (*s == ' ') s++;
        while (*s >= '0' && *s <= '9') quand = quand * 10 + (unsigned)(*s++ - '0');
        if (*s == ':') s++;
        while (*s && *s != ' ') {
            o = 0;
            while (*s && *s != ' ' && *s != ',') { if (o < 63) mot[o++] = *s; s++; }
            mot[o] = 0;
            if (o) m &= ~touche(mot);
            if (*s == ',') s++;
        }
        scenario[nscenario].quand = quand;
        scenario[nscenario].masque = m;
        nscenario++;
    }
}
unsigned long dispatch_misses;
unsigned long cdcb_hits;   /* entrees dans le rappel CD du jeu */

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
        if (g_verbeux && seq < 200 && !(vec == 0xA0 && (fn & 0xFF) == 0x3F)) {
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
    /* Les fonctions de chaine et de memoire du BIOS.
     *
     * Le jeu ne les emporte pas : la bibliotheque les remplace par des
     * tremplins qui sautent en 0xA0 avec le numero d'appel dans $t1. Ne pas
     * les implementer ne provoque aucune erreur -- elles rendent zero et ne
     * copient rien, et le defaut se manifeste tres loin de la : ici, un
     * strcpy muet vidait le chemin du fichier et le jeu concluait
     * « File not found » apres avoir correctement lu son disque. */
    /* Les compteurs racine. VSync ne compte pas les images lui-meme : il
       demande au BIOS la difference depuis son dernier appel. Sans reponse,
       la difference est toujours nulle et l'attente ne finit jamais. */
    if (vec == 0xB0 && (fn & 0xFF) >= 0x02 && (fn & 0xFF) <= 0x06) {
        extern unsigned long g_vblanks;
        if ((fn & 0xFF) == 0x03) return (u32)(g_vblanks & 0xFFFF);
        return 1;
    }
    if (vec == 0xA0) {
        u32 p = a0 & 0x1FFFFF, q = a1 & 0x1FFFFF;
        u32 n = a2, i;
        switch (fn & 0xFF) {
        case 0x17:                                  /* strcmp  */
            for (i = 0; ; i++) {
                u8 x = RAM[(p + i) & 0x1FFFFF], y = RAM[(q + i) & 0x1FFFFF];
                if (x != y) return (u32)(s32)((s32)x - (s32)y);
                if (!x) return 0;
            }
        case 0x18:                                  /* strncmp */
            for (i = 0; i < n; i++) {
                u8 x = RAM[(p + i) & 0x1FFFFF], y = RAM[(q + i) & 0x1FFFFF];
                if (x != y) return (u32)(s32)((s32)x - (s32)y);
                if (!x) return 0;
            }
            return 0;
        case 0x19:                                  /* strcpy  */
            for (i = 0; ; i++) {
                u8 c = RAM[(q + i) & 0x1FFFFF];
                RAM[(p + i) & 0x1FFFFF] = c;
                if (!c) break;
            }
            return a0;
        case 0x1A:                                  /* strncpy */
            for (i = 0; i < n; i++) {
                u8 c = RAM[(q + i) & 0x1FFFFF];
                RAM[(p + i) & 0x1FFFFF] = c;
                if (!c) break;
            }
            for (; i < n; i++) RAM[(p + i) & 0x1FFFFF] = 0;
            return a0;
        case 0x1B:                                  /* strlen  */
            for (i = 0; RAM[(p + i) & 0x1FFFFF]; i++) ;
            return i;
        case 0x1C:                                  /* index   */
            for (i = 0; ; i++) {
                u8 c = RAM[(p + i) & 0x1FFFFF];
                if (c == (u8)a1) return a0 + i;
                if (!c) return 0;
            }
        case 0x1D:                                  /* rindex  */
        {
            u32 last = 0;
            for (i = 0; ; i++) {
                u8 c = RAM[(p + i) & 0x1FFFFF];
                if (c == (u8)a1) last = a0 + i;
                if (!c) break;
            }
            return last;
        }
        case 0x27:                                  /* bcopy (src, dst, n) */
            for (i = 0; i < n; i++) RAM[(q + i) & 0x1FFFFF] = RAM[(p + i) & 0x1FFFFF];
            return 0;
        case 0x28:                                  /* bzero  */
            for (i = 0; i < a1; i++) RAM[(p + i) & 0x1FFFFF] = 0;
            return 0;
        case 0x2A:                                  /* memcpy (dst, src, n) */
            for (i = 0; i < n; i++) RAM[(p + i) & 0x1FFFFF] = RAM[(q + i) & 0x1FFFFF];
            return a0;
        case 0x2B:                                  /* memset */
            for (i = 0; i < n; i++) RAM[(p + i) & 0x1FFFFF] = (u8)a1;
            return a0;
        case 0x2C:                                  /* memmove */
            if (p < q) { for (i = 0; i < n; i++) RAM[(p + i) & 0x1FFFFF] = RAM[(q + i) & 0x1FFFFF]; }
            else { for (i = n; i-- > 0; ) RAM[(p + i) & 0x1FFFFF] = RAM[(q + i) & 0x1FFFFF]; }
            return a0;
        case 0x2E:                                  /* memchr */
            for (i = 0; i < n; i++)
                if (RAM[(p + i) & 0x1FFFFF] == (u8)a1) return a0 + i;
            return 0;
        default: break;
        }
    }
    /* La manette.
     *
     * Le BIOS ne la lit pas a la demande : il remplit un tampon que le jeu
     * consulte quand il veut. InitPAD donne l'adresse des deux tampons,
     * StartPAD arme le remplissage. Le format tient en quatre octets --
     * un etat, un type, et seize boutons actifs a zero.
     *
     * Sans elle, le jeu reste sur « PUSH START BUTTON » et ne montre que sa
     * demonstration. Avec elle, on peut le jouer -- ou, ici, lui jouer un
     * scenario ecrit d'avance, ce qui rend le resultat reproductible. */
    if (vec == 0xB0 && (fn & 0xFF) == 0x12) {   /* InitPAD  */
        g_pad_buf[0] = a0; g_pad_buf[1] = a2;
        return 0;
    }
    if (vec == 0xB0 && (fn & 0xFF) == 0x13) {   /* StartPAD */
        g_pad_on = 1;
        return 0;
    }
    if (vec == 0xB0 && (fn & 0xFF) == 0x14) {   /* StopPAD  */
        g_pad_on = 0;
        return 0;
    }
    if (vec == 0xA0 && (fn & 0xFF) == 0x13) {
        /* setjmp. Rend 0 a l'installation, 1 quand on rejoue le contexte. */
        return (u32)g_longjmp;
    }
    if (vec == 0xB0 && (fn & 0xFF) == 0x19) {
        /* HookEntryInt : le premier mot de la structure est l'adresse du
           gestionnaire. On la retient pour pouvoir l'appeler. */
        /* Le jeu reinstalle son gestionnaire a chaque tour de boucle : le
           dire chaque fois noie tout le reste sous des milliers de lignes
           identiques. On ne signale donc qu'un changement. */
        u32 avant = g_irq_handler;
        g_irq_handler = LW(a0);
        if (g_irq_handler != avant) {
            printf("[gestionnaire d'interruptions installe en %08X]\n", g_irq_handler);
            fflush(stdout);
        }
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

/* Une base de temps qui ne depende pas du materiel.
 *
 * La boucle d'attente du pilote CD ne lit aucun registre : elle decompte des
 * tours en surveillant un drapeau en memoire, que le gestionnaire pose. Livrer
 * les interruptions sur les lectures materielles ne l'atteint donc jamais, et
 * elle expire avant d'avoir rien vu -- « CdlReset: timeout » s'imprime avant
 * meme que la reponse soit lue.
 *
 * Les appels de fonction, eux, arrivent tout le temps. Ils font une horloge
 * grossiere mais reguliere, et surtout independante de ce que le jeu regarde. */
extern u32 g_istat_mirror, g_imask_mirror;
void deliver_irq(void);
static unsigned long tick;

u32 psx_dispatch(u32 addr, u32 a0, u32 a1, u32 a2, u32 a3, u32 t1)
{
    int lo = 0, hi = PSX_NFUNCS - 1;
    /* Meme horloge pour les deux : le lecteur doit avancer sur la meme base
       de temps que la livraison des interruptions, sinon sa seconde reponse
       n'arrive jamais pendant que le jeu attend dans une boucle memoire. */
    if ((++tick & 0xFF) == 0 && !in_irq) {
        void cd_tick(void);
        cd_tick();
        if (g_istat_mirror & g_imask_mirror) deliver_irq();
    }
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
    if (sig) printf("\n--- interrompu apres %d s ---\n", g_seconds);
    printf("paquets GPU        : %lu commandes, %lu mots\n", prim_count, gp0_words);
    printf("tables d'affichage : %lu deroulees, %lu noeuds\n", ot_lists, ot_nodes);
    printf("registres          : %lu ecritures, %lu lectures, %lu GP1\n",
           hw_writes, hw_reads, gp1_cmds);
    printf("sauts indirects sans cible : %lu\n", dispatch_misses);
    printf("interruptions livrees      : %lu\n", irq_delivered);
    printf("evenements delivres        : %lu\n", ev_delivered);
    printf("rappel CD du jeu appele    : %lu fois\n", cdcb_hits);
    {
        int k;
        printf("table des rappels d'interruption (D_800797A8) :\n");
        for (k = 0; k < 8; k++) {
            u32 h = LW(0x800797A8u + 4 * k);
            if (h) printf("   irq %d -> %08X%s\n", k, h, k == 2 ? "   <-- lecteur CD" : "");
        }
        printf("rappel de synchronisation CD (D_801E9170) : %08X\n", LW(0x801E9170u));
    }
    {
        extern unsigned long cd_sectors_served, cd_sectors_missing, dma3_done;
        printf("secteurs servis            : %lu (%lu introuvables), %lu transferts DMA\n",
               cd_sectors_served, cd_sectors_missing, dma3_done);
    }
    { extern unsigned long g_vblanks; printf("battements video : %lu\n", g_vblanks); }
    printf("commandes GP0 les plus frequentes :\n");
    {   /* trier par frequence : montrer les douze plus courantes, pas les
           douze premieres -- l'ordre numerique ne dit rien. */
        int ord[256], a, b;
        for (a = 0; a < 256; a++) ord[a] = a;
        for (a = 0; a < 256; a++) for (b = a + 1; b < 256; b++)
            if (prim_hist[ord[b]] > prim_hist[ord[a]]) { int t = ord[a]; ord[a] = ord[b]; ord[b] = t; }
        for (a = 0; a < 256; a++) { i = ord[a];
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
        } }
    }
    {
        extern u32 hw_addr[]; extern unsigned long hw_rcnt[], hw_wcnt[]; extern int hw_naddr;
        int k;
        extern unsigned long cd_cmds[256];
        {
            extern u32 hw_irq_addr[]; extern unsigned long hw_irq_cnt[]; extern int hw_irq_n;
            int j;
            printf("registres lus par le gestionnaire d'interruptions :\n");
            for (j = 0; j < hw_irq_n; j++)
                printf("   %08X  %lu fois\n", hw_irq_addr[j], hw_irq_cnt[j]);
            if (!hw_irq_n) printf("   aucun -- le gestionnaire ne touche pas au materiel\n");
        }
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
    /* L'executable PlayStation porte son propre en-tete : le point d'entree,
       l'adresse de chargement et la taille y sont ecrits. Les lire evite de
       coder en dur trois nombres qui changent d'un jeu -- et d'une region -- a
       l'autre, et fait de ce banc autre chose qu'un montage local. */
    const char *exe = getenv("PSX_EXE");
    unsigned char en_tete[0x800];
    u32 charge, taille;
    FILE *f;
    int seconds = (argc > 1) ? atoi(argv[1]) : 20;
    if (argc > 2) exe = argv[2];
    if (!exe) exe = "PSX.EXE";
    g_seconds = seconds;
    f = fopen(exe, "rb");
    if (!f || fread(en_tete, sizeof en_tete, 1, f) != 1) {
        fprintf(stderr, "executable introuvable : %s\n"
                        "  usage : ./m0 [secondes] [chemin/PSX.EXE]\n"
                        "  ou    : PSX_EXE=chemin/PSX.EXE ./m0 [secondes]\n", exe);
        return 1;
    }
    if (memcmp(en_tete, "PS-X EXE", 8) != 0) {
        fprintf(stderr, "%s n'est pas un executable PlayStation\n", exe);
        return 1;
    }
    __builtin_memcpy(&ENTRY, en_tete + 0x10, 4);
    __builtin_memcpy(&charge, en_tete + 0x18, 4);
    __builtin_memcpy(&taille, en_tete + 0x1C, 4);
    if ((charge & 0x1FFFFFFF) + taille > 0x200000) {
        fprintf(stderr, "l'image ne tient pas en memoire\n");
        return 1;
    }
    if (fread(RAM + (charge & 0x1FFFFFFF), taille, 1, f) != 1) {
        fprintf(stderr, "image tronquee\n");
        return 1;
    }
    fclose(f);
    { const char *j = getenv("JOURNAL_GPU"); if (j) gpulog = fopen(j, "w"); }

    /* L'en-tete de ce jeu ne donne pas de pile utilisable -- gp0 et s_addr y
       sont du bruit, ce qui n'etonne pas pour le tout premier titre de la
       console. On prend donc la pile par defaut du BIOS. */
    g_sp = 0x801FFF00u;

    g_verbeux = getenv("VERBEUX") ? 1 : 0;
    { void scenario_lire(const char *); const char *s = getenv("MANETTE"); if (s) scenario_lire(s); }
    signal(SIGALRM, report);
    alarm(seconds);
    printf("%s : entree en %08X, %u octets, %d fonctions dans la table\n",
           exe, ENTRY, taille, PSX_NFUNCS);
    fflush(stdout);
    psx_dispatch(ENTRY, 0, 0, 0, 0, 0);
    printf("--- le point d'entree est revenu ---\n");
    report(0);
    return 0;
}
