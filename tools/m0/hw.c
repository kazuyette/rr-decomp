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

/* Les interruptions, pour de vrai.
 *
 * I_STAT porte les sources en attente, I_MASK celles qui sont armees. Ecrire
 * dans I_STAT acquitte : les bits a zero dans la valeur ecrite sont effaces.
 * Renvoyer une constante, comme je le faisais, laisse le drapeau leve pour
 * toujours -- le gestionnaire retraite sans fin la meme source et n'atteint
 * jamais les autres. */
u32 g_istat_mirror, g_imask_mirror;
#define istat g_istat_mirror
#define imask g_imask_mirror
void irq_raise(u32 bit) { istat |= bit; }
#define IRQ_VBLANK 0x0001
#define IRQ_CDROM  0x0004

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

/* --- le lecteur CD -------------------------------------------------------
 *
 * Le pilote du jeu ecrit une commande en 0x1F801801, puis attend dans une
 * boucle que le bit 5 du registre d'etat annonce une reponse. Sans reponse, il
 * boucle -- 33 millions de lectures en dix secondes, puis « CdlReset: timeout ».
 *
 * Ce qui est implemente ici est le strict necessaire pour que ce dialogue
 * aboutisse : l'index, les deux files de parametres et de reponses, les
 * drapeaux d'interruption, et les commandes que le demarrage utilise. Les
 * donnees ne sont pas encore servies ; c'est l'etape suivante.
 */
static u8 cd_index;              /* les registres changent de sens selon lui */
static u8 cd_param[16], cd_nparam;
static u8 cd_resp[16], cd_nresp, cd_rpos;
static u8 cd_irq;                /* drapeau d'interruption en attente */
static u8 cd_ie;                 /* masque */
static u8 cd_stat = 0x02;        /* 0x02 : moteur en rotation */
unsigned long cd_cmds[256];
static u8 cd_pending_cmd;
/* La plupart des commandes repondent DEUX fois : un accuse immediat (INT3),
   puis un achevement (INT2) quand le mecanisme a fini de bouger. Le pilote
   compte les deux separement -- ses compteurs Acknowledge et Complete -- et
   n'avance pas tant qu'il n'a pas eu le second. */
static u8 cd_second;

void cd_event(u32 spec);

static void cd_reply(u8 irq, const u8 *b, int n)
{
    int i;
    cd_nresp = 0; cd_rpos = 0;
    for (i = 0; i < n && i < 16; i++) cd_resp[cd_nresp++] = b[i];
    cd_irq = irq;
    /* Le contrôleur a repondu : lever la source d'interruption. C'est le
       gestionnaire du jeu qui decidera quoi en faire -- notre travail s'arrete
       a poser le drapeau, comme le materiel. */
    irq_raise(IRQ_CDROM);
}

static void cd_command(u8 cmd)
{
    u8 one[1];
    cd_cmds[cmd]++;
    cd_pending_cmd = cmd;
    one[0] = cd_stat;
    switch (cmd) {
    case 0x01: cd_reply(3, one, 1); break;                 /* Nop     */
    case 0x02: cd_reply(3, one, 1); break;                 /* Setloc  */
    case 0x0A: cd_stat = 0x02; cd_reply(3, one, 1); cd_second = 2; break; /* Init  */
    case 0x09: cd_reply(3, one, 1); cd_second = 2; break;  /* Pause   */
    case 0x15: case 0x16: cd_reply(3, one, 1); cd_second = 2; break; /* Seek */
    case 0x0C: cd_reply(3, one, 1); break;                 /* Demute  */
    case 0x0E: cd_reply(3, one, 1); break;                 /* Setmode */
    case 0x19: {                                           /* Test    */
        static const u8 ver[4] = { 0x94, 0x09, 0x19, 0xC0 };
        cd_reply(3, ver, 4); break;
    }
    default:   cd_reply(3, one, 1); break;
    }
    cd_nparam = 0;
}

/* Le dialogue avec le lecteur, dans l'ordre. Les compteurs disent qu'il
   s'arrete ; la sequence dit ou. */
static int cdlog;
static void cdtrace(const char *what, u32 a, u32 b)
{
    if (cdlog++ < 70) { printf("  cd: %-12s %02X %02X\n", what, a, b); fflush(stdout); }
}

static u32 cd_read(u32 p)
{
    switch (p & 3) {
    case 0: {
        u32 st = cd_index & 3;
        st |= 0x18;                          /* file de parametres prete et vide */
        if (cd_nresp > cd_rpos) st |= 0x20;  /* une reponse attend */
        return st;
    }
    case 1: {
        u32 r = (cd_rpos < cd_nresp) ? cd_resp[cd_rpos++] : 0;
        cdtrace("lit reponse", r, cd_rpos);
        return r;
    }
    case 2: return 0;
    case 3: {
        u32 r = (cd_index & 1) ? (0xE0 | cd_irq) : (0xE0 | cd_ie);
        cdtrace(cd_index & 1 ? "lit drapeaux" : "lit masque", r, cd_index);
        return r;
    }
    }
    return 0;
}

static void cd_write(u32 p, u32 v)
{
    u8 b = (u8)v;
    switch (p & 3) {
    case 0: cdtrace("index", b & 3, 0); cd_index = b & 3; break;
    case 1:
        if (cd_index == 0) { cdtrace("COMMANDE", b, cd_nparam); cd_command(b); }
        else cdtrace("ecrit 1801", b, cd_index);
        break;
    case 2:
        if (cd_index == 0) { cdtrace("parametre", b, cd_nparam); if (cd_nparam < 16) cd_param[cd_nparam++] = b; }
        else if (cd_index == 1) { cdtrace("arme", b, 0); cd_ie = b; }
        break;
    case 3:
        cdtrace("ecrit 1803", b, cd_index);
        /* Index 1 : ecrire ici acquitte l'interruption. C'est ce que le pilote
           fait apres avoir lu sa reponse, et sans quoi il ne redemande rien. */
        if (cd_index == 1) {
            cdtrace("acquitte", b, cd_second);
            if (b & 0x07) {
                cd_irq = 0;
                if (cd_second) {
                    /* L'accuse a ete releve : on enchaine sur l'achevement. */
                    u8 st = cd_stat;
                    cd_reply(cd_second, &st, 1);
                    cd_second = 0;
                }
            }
        }
        break;
    }
}

/* Le BIOS, sur interruption du lecteur, releve la reponse et acquitte a la
   place du jeu. On expose ici de quoi le faire. */
u32 cd_take_response(u8 *out)
{
    int i;
    u32 t = cd_irq;
    if (!t) return 0;
    for (i = 0; i < 16; i++) out[i] = (i < cd_nresp) ? cd_resp[i] : 0;
    cd_irq = 0;
    istat &= ~IRQ_CDROM;
    if (cd_second) { u8 st = cd_stat; cd_reply(cd_second, &st, 1); cd_second = 0; }
    return t;
}

/* --- registres ---------------------------------------------------------- */
unsigned long hw_writes, hw_reads;

/* Un histogramme des adresses touchees. Le pilote CD passe par un pointeur
   global, donc invisible au desassemblage ; le releve empirique dit tout de
   suite de quel materiel le jeu a besoin, et dans quelle proportion. */
#define HWN 256
u32 hw_addr[HWN]; unsigned long hw_rcnt[HWN], hw_wcnt[HWN]; int hw_naddr;
/* Le gestionnaire d'interruptions et la boucle principale touchent le meme
   materiel pour des raisons opposees. Les compter separement dit ce que le
   gestionnaire cherche -- et donc ce qui lui manque. */
extern int in_irq_flag;
u32 hw_irq_addr[64]; unsigned long hw_irq_cnt[64]; int hw_irq_n;

static void note(u32 p, int write)
{
    int i;
    if (in_irq_flag) {
        for (i = 0; i < hw_irq_n; i++)
            if (hw_irq_addr[i] == p) { hw_irq_cnt[i]++; goto done; }
        if (hw_irq_n < 64) { hw_irq_addr[hw_irq_n] = p; hw_irq_cnt[hw_irq_n++] = 1; }
    }
done:;
    for (i = 0; i < hw_naddr; i++)
        if (hw_addr[i] == p) { if (write) hw_wcnt[i]++; else hw_rcnt[i]++; return; }
    if (hw_naddr < HWN) {
        hw_addr[hw_naddr] = p;
        if (write) hw_wcnt[hw_naddr]++; else hw_rcnt[hw_naddr]++;
        hw_naddr++;
    }
}
static u32 vblank_counter;
static u32 irq_tick;


void deliver_irq(void);

u32 hw_read32(u32 p)
{
    hw_reads++;
    note(p, 0);
    /* Livrer ici, et pas seulement sur l'etat du GPU : la boucle d'attente du
       lecteur ne lit que son propre registre. Cadencer le temps sur le GPU
       revenait a arreter la montre pendant precisement le moment ou le jeu
       attend une interruption. */
    if ((istat & imask) && !in_irq_flag) deliver_irq();
    switch (p) {
    case 0x1F801810: return 0;             /* GPUREAD */
    case 0x1F801814:
        /* Le jeu lit ce registre des millions de fois : c'est sa boucle
           d'attente, donc le meilleur endroit ou faire battre le temps.
           Toutes les mille lectures, on lui livre une interruption. */
        /* Le retour de balayage, environ soixante fois par seconde sur la
           console. Ici on le cadence sur les lectures d'etat du GPU, faute
           d'horloge : ce qui compte est qu'il arrive regulierement. */
        if (++irq_tick >= 20000) { irq_tick = 0; irq_raise(IRQ_VBLANK); }
        /* GPUSTAT. Les bits qui comptent pour que le jeu avance : prêt à
           recevoir une commande, prêt pour un DMA, et le bit d'image qui
           bascule -- sans lui, toute attente de synchro tourne sans fin. */
        vblank_counter++;
        return 0x1C000000u | ((vblank_counter & 1) ? 0x80000000u : 0u);
    case 0x1F8010A0: return dma2_madr;
    case 0x1F8010A4: return dma2_bcr;
    case 0x1F8010A8: return dma2_chcr;
    case 0x1F801800: case 0x1F801801:
    case 0x1F801802: case 0x1F801803: return cd_read(p);
    case 0x1F801070: return istat;
    case 0x1F801074: return imask;
    default: return 0;
    }
}

void deliver_irq(void);

void hw_write32(u32 p, u32 v, int width)
{
    (void)width;
    hw_writes++;
    note(p, 1);
    switch (p) {
    case 0x1F801800: case 0x1F801801:
    case 0x1F801802: case 0x1F801803:
        cd_write(p, v);
        /* Le materiel leve son interruption presque aussitot apres la
           commande. La boucle d'attente du pilote est plus courte que
           n'importe quelle horloge grossiere : il faut livrer ici, sur place. */
        if ((istat & imask) && !in_irq_flag) deliver_irq();
        break;
    case 0x1F801810: gp0_write(v); break;
    case 0x1F801814: gp1_cmds++; break;
    case 0x1F801070: istat &= v; break;    /* acquittement : les zeros effacent */
    case 0x1F801074: {
        /* Quel masque le jeu arme-t-il ? La reponse dit quelles sources il
           attend, et donc lesquelles il faut lever. */
        static u32 last; static int shown;
        if (v != last && shown < 8) {
            printf("[I_MASK = %04X : ", v);
            if (v & 1) printf("vblank ");
            if (v & 2) printf("gpu ");
            if (v & 4) printf("cdrom ");
            if (v & 8) printf("dma ");
            if (v & 0x10) printf("timer0 ");
            if (v & 0x70) printf("timers ");
            if (v & 0x80) printf("carte ");
            if (v & 0x100) printf("spu ");
            printf("]\n"); fflush(stdout); last = v; shown++;
        }
        imask = v; break;
    }
    case 0x1F8010A0: dma2_madr = v; break;
    case 0x1F8010A4: dma2_bcr = v; break;
    case 0x1F8010A8:
        dma2_chcr = v;
        if (v & 0x01000000u) dma2_run();
        break;
    default: break;
    }
}
