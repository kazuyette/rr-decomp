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
#include <stdlib.h>
#include <unistd.h>
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

/* --- servir les secteurs ------------------------------------------------
 *
 * Les metadonnees -- descripteur de volume, table des chemins, repertoire --
 * viennent de l'image du disque ; les donnees des fichiers extraits, chacun a
 * son secteur declare dans le repertoire. Le jeu ne voit aucune difference :
 * il demande un secteur, il obtient les octets qui y sont.
 */
#include <stdio.h>
struct cdfile { unsigned int lba, size; const char *path; };
extern const struct cdfile CDFILES[];
extern const int NCDFILES;
extern const char *CD_META;
extern const unsigned int CD_META_SECTORS;
unsigned long cd_sectors_served, cd_sectors_missing;

static void cd_fetch(u32 lba, u8 *out)
{
    int i;
    FILE *f;
    /* L'image du disque reste ouverte. L'ouvrir et la refermer a chaque
       secteur coute peu sur un disque local et beaucoup a travers un montage,
       ce qui est le cas courant sous WSL. */
    static FILE *image;
    for (i = 0; i < 2048; i++) out[i] = 0;
    if (lba < CD_META_SECTORS) {
        if (!image) image = fopen(CD_META, "rb");
        f = image;
        if (f) { fseek(f, (long)lba * 2048, SEEK_SET); fread(out, 1, 2048, f);
                 cd_sectors_served++; return; }
    }
    for (i = 0; i < NCDFILES; i++) {
        u32 n = (CDFILES[i].size + 2047) / 2048;
        if (lba >= CDFILES[i].lba && lba < CDFILES[i].lba + n) {
            f = fopen(CDFILES[i].path, "rb");
            if (f) { fseek(f, (long)(lba - CDFILES[i].lba) * 2048, SEEK_SET);
                     fread(out, 1, 2048, f); fclose(f); cd_sectors_served++; return; }
        }
    }
    cd_sectors_missing++;
}


u8 RAM[0x200000];
u8 SPAD[0x400];
u32 g_sp;

/* --- GPU ---------------------------------------------------------------- */
void gpu_gp0(u32 v);
void gpu_gp1(u32 v);
void gpu_reset_fifo(void);
void gpu_check_sync(const char *);
u32 gpu_read_word(void);
void gpu_write_ppm(const char *path);
void gpu_write_vram(const char *path);
extern unsigned long gp0_words, gp1_cmds, prim_count, prim_hist[256], gpu_frames;
#define gp0_write(v) gpu_gp0(v)

/* --- DMA canal 2 : la table d'affichage ---------------------------------
 *
 * Le jeu ne parle presque jamais au GPU directement : il construit une liste
 * chaînée en RAM et demande au DMA de la dérouler. Dérouler cette liste ici,
 * c'est voir exactement ce qu'une image contient. */
static u32 dma2_madr, dma2_bcr, dma2_chcr;
static u32 dma3_madr, dma3_bcr, dma3_chcr;
static u32 dma6_madr, dma6_bcr, dma6_chcr;
static u32 dma4_madr, dma4_bcr, dma4_chcr;
static u32 dicr = 0;

/* La fin d'un transfert leve une interruption, si le canal l'a demandee.
 *
 * Le jeu ne surveille pas le registre : il ouvre un evenement et s'endort
 * dessus. Sans l'interruption, l'evenement n'arrive jamais et l'attente est
 * eternelle -- c'est exactement ou le son se bloquait, une fois son
 * initialisation reussie. Le registre de controle porte les autorisations
 * dans ses bits 16 a 22 et les drapeaux dans les bits 24 a 30 ; le bit 31
 * resume, et c'est lui qui declenche. */
static void dma_fini(int canal)
{
    if (!(dicr & (1u << (16 + canal)))) return;
    dicr |= 1u << (24 + canal);
    if (dicr & (1u << 23)) {
        dicr |= 0x80000000u;
        irq_raise(0x0008);            /* la source « DMA » */
    }
}
unsigned long dma4_done;
void spu_write16(u32, u16);
u16 spu_read16(u32);
void spu_dma(const u8 *, u32, u32);
void spu_melanger(s16 *, int);
int spu_actif(void);
unsigned long otc_runs;
unsigned long dma3_done;
unsigned long ot_lists, ot_nodes, ot_broken, dma2_blocks;
u32 g_ot_node, g_ot_n;

unsigned long g_instr_par_image = 376000;
int g_cout_dessin = 1;
int g_capture;
extern unsigned long long g_pixels, g_cycles, g_echeance;
void psx_horloge(void);
static unsigned long long pixels_vus;

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
        /* Chaque noeud porte un paquet complet, sa longueur est dans l'entete.
           Repartir a zero a chaque noeud borne les degats d'une longueur mal
           lue : elle ne peut plus avaler la liste entiere. */
        for (i = 0; i < n; i++) {
            u32 w;
            __builtin_memcpy(&w, RAM + ((addr + 4 + i * 4) & 0x1FFFFC), 4);
            gp0_write(w);
        }
        if ((header & 0xFFFFFF) == 0xFFFFFF) break;
        /* Un chainage nul n'est pas une fin de liste : c'est une entree qui
           n'a jamais ete initialisee. La suivre menait a l'adresse zero, puis
           a tourner jusqu'a la garde -- deux millions de noeuds pour rien. */
        if ((header & 0xFFFFFF) == 0) { ot_broken++; break; }
        addr = (header & 0x1FFFFC);
    }
    /* Facturer le dessin.
     *
     * Le processeur n'etait pas seul a consommer du temps : le GPU remplissait
     * environ un pixel par cycle a 53,2 MHz, soit quelque 887 000 pixels entre
     * deux balayages. Une scene qui en demande plus ne tient pas dans une
     * image, et la console tombait alors a trente par seconde -- non par
     * decision, mais par depassement. C'est cette lenteur-la qu'on retrouve
     * ici, en convertissant les pixels ecrits dans la meme monnaie que les
     * instructions.
     *
     * Sans ce compte, une scene chargee coute chez nous le meme temps qu'une
     * scene vide, et le jeu tourne trop vite exactement la ou il ralentissait.
     */
    if (g_cout_dessin) {
        unsigned long long p = g_pixels - pixels_vus;
        pixels_vus = g_pixels;
        g_cycles += p * (unsigned long long)g_instr_par_image / 887000ull;
        if (g_cycles >= g_echeance && !in_irq_flag) psx_horloge();
    }
    dma2_chcr &= ~0x01000000u;
    /* La manette se lit une fois par image, comme sur la console -- et c'est
       aussi ce qui donne au scenario une unite stable : le nombre d'images
       dessinees ne depend pas de la base de temps, alors que les battements
       video changent des qu'on la regle. */
    { void pad_ecrire(unsigned long); pad_ecrire(ot_lists); }
    /* Une liste deroulee = une image dessinee. On en garde quelques-unes,
       espacees, plutot que toutes : ce qu'on veut voir est la progression. */
    {
        static unsigned long n;
        /* Ecrire une image de 230 Ko sur disque toutes les cent tables suffit
           a faire saccader le jeu -- et comme le compte s'arrete a cent vingt,
           la saccade s'arrete elle aussi, apres environ un tour de circuit.
           Un defaut qui guerit tout seul est le plus difficile a imputer : on
           croit voir le jeu se mettre en route.

           Quand il y a une fenetre, on ne capture donc que si on l'a demande. */
        if (!g_capture) return;
        if (++n % 100 == 0 && n / 100 <= 120) {
            char p[256];
            const char *d = getenv("IMAGES");
            sprintf(p, "%s/f%03lu.ppm", d ? d : ".", n / 100);
            gpu_write_ppm(p);
        }
    }
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
static u8 cd_id_pending;
static u8 cd_pend;           /* seconde reponse en attente d'echeance */
static int cd_delay;
static u32 cd_lba;           /* position courante, en secteurs */
static int cd_reading;
static u8 cd_sector[2048];
static int cd_sector_ready;

static u32 bcd(u8 v) { return (v >> 4) * 10 + (v & 15); }
static u8 vers_bcd(u32 v) { return (u8)(((v / 10) % 10) * 16 + v % 10); }

/* --- la musique ----------------------------------------------------------
 *
 * Les pistes audio sont des secteurs bruts de 2352 octets, soit exactement
 * 588 trames stereo de seize bits a 44 100 Hz : ni conversion ni
 * reechantillonnage, on lit et on pousse. C'est la carte son qui donne le
 * rythme -- tant que sa file est assez remplie, on ne lit rien.
 */
extern int g_verbeux;
struct cdtrack { unsigned int debut, longueur, saut; const char *fichier; };
extern const struct cdtrack CDTRACKS[];
extern const int NCDTRACKS;
int audio_init(void);
void audio_pousser(const void *, int);
unsigned audio_en_attente(void);
void audio_vider(void);

static int cd_joue, cd_piste = 1, cd_audio_dispo;
int cd_audio_dispo_pub(int oui)
{
    cd_audio_dispo = oui && audio_init();
    if (cd_audio_dispo) printf("son : pistes audio du disque\n");
    return cd_audio_dispo;
}
static FILE *cd_audio_f;
static u32 cd_audio_secteur;      /* position dans le fichier de la piste */
static u32 cd_audio_reste;
unsigned long cd_secteurs_audio;

static void cd_audio_ouvrir(int piste)
{
    const struct cdtrack *t;
    u32 depart;
    if (cd_audio_f) { fclose(cd_audio_f); cd_audio_f = 0; }
    if (piste >= 1 && piste <= NCDTRACKS) {
        t = &CDTRACKS[piste - 1];
        depart = t->saut;                 /* le debut annonce de la piste */
    } else {
        /* Pas de numero : c'est la position posee par Setloc qui commande. */
        int i;
        for (i = 0; i < NCDTRACKS; i++) {
            u32 base = CDTRACKS[i].debut - CDTRACKS[i].saut;
            if (cd_lba >= base && cd_lba < base + CDTRACKS[i].longueur) {
                cd_piste = i + 1;
                t = &CDTRACKS[i];
                depart = cd_lba - base;
                goto trouve;
            }
        }
        return;
    }
trouve:
    if (g_verbeux) { printf("  son: piste %d, a partir du secteur %u\n", cd_piste, depart); fflush(stdout); }
    cd_audio_f = fopen(t->fichier, "rb");
    if (!cd_audio_f) return;
    cd_audio_secteur = depart;
    cd_audio_reste = (t->longueur > depart) ? t->longueur - depart : 0;
    fseek(cd_audio_f, (long)depart * 2352, SEEK_SET);
    audio_vider();
}

/* Le melange, appele regulierement : on remplit la file de la carte son
   jusqu'a un quart de seconde d'avance.
 *
 * Deux sources s'y rejoignent -- les pistes du disque et les vingt-quatre voix
 * du SPU -- et il faut bien qu'elles se rejoignent quelque part. Les pousser
 * separement reviendrait a demander deux sorties a la carte son, ou a laisser
 * l'une effacer l'autre. On additionne donc, en saturant : c'est ce que le
 * materiel faisait de toute facon, la sortie du lecteur passant par le meme
 * melangeur que les voix.
 *
 * L'unite est le secteur, soit 588 trames : c'est le grain du disque, et il
 * tombe juste sur la frequence de sortie. */
static void cd_audio_alimenter(void)
{
    static u8 secteur[2352];
    static s16 voix[588 * 2];
    if (!cd_audio_dispo) return;
    while (audio_en_attente() < 44100u * 4u / 4u) {
        s16 *cd = (s16 *)secteur;
        int i, lu = 0;
        if (cd_joue && cd_audio_f && cd_audio_reste) {
            if (fread(secteur, 1, 2352, cd_audio_f) == 2352) {
                lu = 1; cd_audio_secteur++; cd_audio_reste--; cd_secteurs_audio++;
            } else {
                cd_audio_reste = 0;
            }
        }
        if (!lu) memset(secteur, 0, sizeof secteur);
        spu_melanger(voix, 588);
        for (i = 0; i < 588 * 2; i++) {
            int somme = (int)cd[i] + (int)voix[i];
            if (somme > 32767) somme = 32767;
            if (somme < -32768) somme = -32768;
            cd[i] = (s16)somme;
        }
        audio_pousser(secteur, 2352);
        /* Sans musique ni voix, inutile de remplir la file indefiniment : on
           s'arrete des qu'il y a de quoi tenir, sinon on tournerait ici. */
        if (!lu && !spu_actif()) break;
    }
}

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
    case 0x02:                                             /* Setloc  */
        /* Les parametres sont en minutes, secondes et trames, codes en
           decimal binaire, et l'origine est a deux secondes du debut. */
        if (cd_nparam >= 3)
            cd_lba = (bcd(cd_param[0]) * 60 + bcd(cd_param[1])) * 75
                     + bcd(cd_param[2]) - 150;
        cd_reply(3, one, 1);
        break;
    case 0x06: case 0x1B:                                  /* ReadN, ReadS */
        cd_reading = 1;
        cd_reply(3, one, 1);
        cd_second = 1;      /* INT1 : un secteur est pret */
        break;
    case 0x0A: cd_stat = 0x02; cd_reply(3, one, 1); cd_second = 2; break; /* Init  */
    /* Les commandes qui font bouger le mecanisme repondent deux fois : un
       accuse immediat, puis un achevement. En omettre une seule suffit a
       bloquer le pilote -- il attend l'achevement et finit par declarer un
       delai depasse. C'est ce qui arrivait a SetSession, juste apres le
       chargement des donnees, au moment ou le jeu passe a la piste audio. */
    case 0x12: cd_reply(3, one, 1); cd_second = 2; break;  /* SetSession */
    case 0x08: cd_reading = 0; cd_joue = 0; cd_reply(3, one, 1); cd_second = 2; break; /* Stop */
    case 0x07: cd_reply(3, one, 1); cd_second = 2; break;  /* MotorOn */
    case 0x0B: cd_reply(3, one, 1); break;                 /* Mute */
    case 0x03:                                             /* Play  */
        /* Sans parametre, on reprend la ou on etait ; avec, on saute a la
           piste demandee. Le jeu se sert des deux. */
        if (cd_nparam >= 1) cd_piste = (int)bcd(cd_param[0]);
        cd_audio_ouvrir(cd_piste);
        cd_joue = 1;
        cd_reply(3, one, 1);
        break;
    case 0x1A: {                                           /* GetID */
        /* Un disque de donnees, licencie, region libre. */
        static const u8 id[8] = { 0x02, 0x00, 0x20, 0x00, 'S', 'C', 'E', 'A' };
        cd_reply(3, one, 1);
        cd_id_pending = 1;
        cd_second = 2;
        (void)id;
        break;
    }
    case 0x13: {                                           /* GetTN */
        u8 r[3];
        r[0] = cd_stat; r[1] = vers_bcd(1);
        r[2] = vers_bcd(NCDTRACKS ? NCDTRACKS : 1);
        cd_reply(3, r, 3); break;
    }
    case 0x14: {                                           /* GetTD */
        /* La position de debut d'une piste, en minutes et secondes. Le zero
           du disque est a deux secondes du debut du signal : c'est la meme
           origine que pour Setloc, et l'oublier decale toute la musique. */
        int n = cd_nparam ? (int)bcd(cd_param[0]) : 1;
        u32 lba = 0;
        u8 r[3];
        if (n >= 1 && n <= NCDTRACKS) lba = CDTRACKS[n - 1].debut;
        else if (n == 0 && NCDTRACKS)   /* piste 0 : la fin du disque */
            lba = CDTRACKS[NCDTRACKS - 1].debut + CDTRACKS[NCDTRACKS - 1].longueur;
        lba += 150;
        r[0] = cd_stat;
        r[1] = vers_bcd((lba / 75) / 60);
        r[2] = vers_bcd((lba / 75) % 60);
        cd_reply(3, r, 3); break;
    }
    case 0x09: cd_reading = 0; cd_joue = 0; cd_reply(3, one, 1); cd_second = 2; break;  /* Pause */
    case 0x15: case 0x16:                                  /* SeekL, SeekP */
        cd_audio_ouvrir(0);   /* la position vient du dernier Setloc */
        cd_reply(3, one, 1); cd_second = 2; break;
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
extern int g_verbeux;
static int cdlog;
static void cdtrace(const char *what, u32 a, u32 b)
{
    if (g_verbeux && cdlog++ < 200) { printf("  cd: %-12s %02X %02X\n", what, a, b); fflush(stdout); }
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
                istat &= ~IRQ_CDROM;
                /* La seconde reponse ne suit pas l'acquittement d'un cycle :
                   le mecanisme met des millisecondes a bouger, et le pilote
                   boucle tant qu'un drapeau reste leve. Repondre sur-le-champ
                   l'enfermait dans cette boucle -- six millions de secteurs
                   servis sans qu'il en sorte jamais. On differe donc, et on
                   compte le temps sur la boucle d'attente du jeu, jamais sur
                   les acces du gestionnaire lui-meme. */
                if (cd_second) { cd_pend = cd_second; cd_delay = 1; cd_second = 0; }
            }
        }
        break;
    }
}

/* Le battement du lecteur. Appele depuis la boucle d'attente du jeu, et de la
   seulement : c'est ce qui garantit que le gestionnaire d'interruption puisse
   se terminer avant que la reponse suivante n'arrive. */
void cd_etat(void)
{
    printf("etat lecteur : irq=%u pend=%u delai=%d lecture=%d second=%u nresp=%u rpos=%u ie=%02X index=%u istat=%04X imask=%04X\n",
           cd_irq, cd_pend, cd_delay, cd_reading, cd_second, cd_nresp, cd_rpos, cd_ie, cd_index, istat, imask);
}

void cd_tick(void)
{
    cd_audio_alimenter();
    if (!cd_pend || --cd_delay > 0) return;
    {
        u8 st = cd_stat, nxt = cd_pend;
        cd_pend = 0;
        if (cd_id_pending) {
            static const u8 id[8] = { 0x02, 0x00, 0x20, 0x00, 'S', 'C', 'E', 'A' };
            cd_id_pending = 0;
            cd_reply(2, id, 8);
            return;
        }
        if (nxt == 1) {                      /* un secteur est disponible */
            cd_fetch(cd_lba, cd_sector);
            cd_sector_ready = 1;
        }
        cd_reply(nxt, &st, 1);
        if (cd_reading && nxt == 1) { cd_pend = 1; cd_delay = 1; }
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
unsigned long g_vblanks;
static u32 irq_tick;


void deliver_irq(void);

/* La lecture par demi-mot. Les registres qui n'existent qu'en seize bits sont
   servis tels quels ; les autres passent par la lecture de mot et en prennent
   la moitie qui convient. */
u32 hw_read16(u32 p)
{
    if (p >= 0x1F801C00 && p < 0x1F801E80) {
        hw_reads++;
        note(p, 0);
        return spu_read16(p);
    }
    if (p >= 0x1F801800 && p <= 0x1F801803) return hw_read32(p) & 0xFFFF;
    return hw_read32(p & ~3u) >> (8 * (p & 2));
}

u32 hw_read32(u32 p)
{
    hw_reads++;
    note(p, 0);
    if (!in_irq_flag) cd_tick();
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
        
        /* GPUSTAT. Les bits qui comptent pour que le jeu avance : prêt à
           recevoir une commande, prêt pour un DMA, et le bit d'image qui
           bascule -- sans lui, toute attente de synchro tourne sans fin. */
        vblank_counter++;
        return 0x1C000000u | ((vblank_counter & 1) ? 0x80000000u : 0u);
    case 0x1F8010A0: return dma2_madr;
    case 0x1F8010A4: return dma2_bcr;
    case 0x1F8010A8: return dma2_chcr;
    case 0x1F8010B0: return dma3_madr;
    case 0x1F8010B4: return dma3_bcr;
    case 0x1F8010B8: return dma3_chcr;
    case 0x1F8010C0: return dma4_madr;
    case 0x1F8010C4: return dma4_bcr;
    case 0x1F8010C8: return dma4_chcr;
    case 0x1F8010F4: return dicr;
    case 0x1F8010E0: return dma6_madr;
    case 0x1F8010E4: return dma6_bcr;
    case 0x1F8010E8: return dma6_chcr;
    case 0x1F801800: case 0x1F801801:
    case 0x1F801802: case 0x1F801803: return cd_read(p);
    case 0x1F801070: return istat;
    case 0x1F801074: return imask;
    default:
        if (p >= 0x1F801C00 && p < 0x1F801E80) return spu_read16(p);
        return 0;
    }
}

void deliver_irq(void);

void hw_write32(u32 p, u32 v, int width)
{
    (void)width;
    hw_writes++;
    note(p, 1);
    if (!in_irq_flag) cd_tick();
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
    case 0x1F801814: gpu_gp1(v); break;
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
    case 0x1F8010B0: dma3_madr = v; break;
    case 0x1F8010B4: dma3_bcr = v; break;
    case 0x1F8010B8:
        dma3_chcr = v;
        if (v & 0x01000000u) {
            /* Le lecteur remplit la memoire : un secteur, puis on avance. */
            u32 words = (dma3_bcr & 0xFFFF) * (dma3_bcr >> 16);
            u32 a = dma3_madr & 0x1FFFFC, i;
            if (!cd_sector_ready) cd_fetch(cd_lba, cd_sector);
            for (i = 0; i < words && i < 512; i++)
                __builtin_memcpy(RAM + ((a + i * 4) & 0x1FFFFC), cd_sector + i * 4, 4);
            cd_sector_ready = 0;
            cd_lba++;
            dma3_chcr &= ~0x01000000u;
            dma3_done++;
        }
        break;
    /* Canal 6 : l'effaceur de table d'affichage. Il ecrit en RAM une liste
       chainee a l'envers -- chaque entree pointe vers la precedente, la
       derniere porte la marque de fin. Sans lui, la table reste a zero et le
       canal 2 suit un chainage nul : il tourne dans le vide et le GPU recoit
       des mots qui ne sont rien. */
    case 0x1F8010E0: dma6_madr = v; break;
    case 0x1F8010E4: dma6_bcr = v; break;
    case 0x1F8010E8:
        dma6_chcr = v;
        if (v & 0x01000000u) {
            u32 n = dma6_bcr & 0xFFFF, a = dma6_madr & 0x1FFFFC, i;
            if (!n) n = 0x10000;
            for (i = 0; i < n; i++) {
                u32 prev = (i == n - 1) ? 0xFFFFFFu : ((a - 4 * (i + 1)) & 0xFFFFFC);
                u32 w = prev;
                __builtin_memcpy(RAM + ((a - 4 * i) & 0x1FFFFC), &w, 4);
            }
            dma6_chcr &= ~0x01000000u;
            otc_runs++;
        }
        break;
    case 0x1F8010F4:
        /* Les drapeaux s'acquittent en ecrivant un : on les efface donc la ou
           l'ecriture les pose, et on garde le reste tel quel. */
        dicr = (dicr & ~0x00FF803Fu & ~(v & 0x7F000000u)) | (v & 0x00FF803Fu);
        if (!(dicr & 0x7F000000u)) dicr &= ~0x80000000u;
        break;
    case 0x1F8010C0: dma4_madr = v; break;
    case 0x1F8010C4: dma4_bcr = v; break;
    case 0x1F8010C8:
        /* Canal 4 : la memoire principale alimente le SPU. Sans lui, les voix
           liraient un demi-mega-octet de zeros -- ce qui s'entend fort bien,
           puisque cela ne s'entend pas du tout. */
        dma4_chcr = v;
        if (v & 0x01000000u) {
            u32 mots = (dma4_bcr & 0xFFFF) * ((dma4_bcr >> 16) & 0xFFFF);
            if (!mots) mots = (dma4_bcr & 0xFFFF);
            if (v & 1) spu_dma(RAM, dma4_madr & 0x1FFFFC, mots * 4);
            dma4_chcr &= ~0x01000000u;
            dma4_done++;
            dma_fini(4);
        }
        break;
    case 0x1F8010A0: dma2_madr = v; break;
    case 0x1F8010A4: dma2_bcr = v; break;
    case 0x1F8010A8:
        dma2_chcr = v;
        if (v & 0x01000000u) {
            /* Trois modes, et pas seulement la liste chainee.
               LoadImage envoie l'en-tete a la main puis pousse les pixels par
               bloc : traiter ce bloc comme une liste faisait suivre au canal
               un chainage tire de la texture elle-meme -- d'ou un transfert
               de 1024 par 256 a une adresse absurde, qui barbouillait toute
               la memoire video. */
            u32 sync = (v >> 9) & 3;
            int vers_gpu = (int)(v & 1);   /* 1 : la memoire alimente le GPU */
            if (sync == 2) dma2_run();
            else {
                u32 words = (sync == 1)
                    ? (dma2_bcr & 0xFFFF) * ((dma2_bcr >> 16) & 0xFFFF)
                    : (dma2_bcr & 0xFFFF);
                u32 a = dma2_madr & 0x1FFFFC, i;
                if (!words) words = 0x10000;
                for (i = 0; i < words; i++) {
                    u32 w;
                    if (!vers_gpu) {          /* le GPU alimente la memoire */
                        w = gpu_read_word();
                        __builtin_memcpy(RAM + ((a + i * 4) & 0x1FFFFC), &w, 4);
                        continue;
                    }
                    __builtin_memcpy(&w, RAM + ((a + i * 4) & 0x1FFFFC), 4);
                    gp0_write(w);
                }
                dma2_blocks++;
            }
            dma2_chcr &= ~0x01000000u;
        }
        break;
    default:
        if (p >= 0x1F801C00 && p < 0x1F801E80) spu_write16(p, (u16)v);
        break;
    }
}

/* Les fonctions que le traducteur refuse (COP0) sont remplacees par un
   bouchon. On compte les passages : un bouchon souvent atteint est une piste,
   un bouchon jamais atteint ne coute rien. */
static const char *stub_names[64];
static unsigned long stub_counts[64];
static int stub_n;
void stub_hit(const char *nm)
{
    int i;
    for (i = 0; i < stub_n; i++)
        if (stub_names[i] == nm) { stub_counts[i]++; return; }
    if (stub_n < 64) { stub_names[stub_n] = nm; stub_counts[stub_n++] = 1; }
}
void stub_report(void)
{
    int i;
    if (!stub_n) return;
    printf("bouchons atteints :\n");
    for (i = 0; i < stub_n; i++)
        printf("   %-20s %lu fois\n", stub_names[i], stub_counts[i]);
}

unsigned long long g_cycles, g_echeance;
void psx_horloge(void)
{
    g_echeance = g_cycles + g_instr_par_image;
    psx_clock();
}

void psx_clock(void)
{
    void cd_tick(void);
    int video_fermee(void);
    extern int g_video;
    /* Fermer la fenetre arrete le jeu, et l'etat des lieux s'imprime comme si
       le temps imparti etait ecoule -- une sortie voulue vaut bien une sortie
       subie. */
    if (g_video && video_fermee()) { void report(int); report(1); _exit(0); }
    cd_tick();
    /* Le retour de balayage. Il etait cadence sur les lectures de l'etat du
       GPU -- or l'attente de VSync ne lit que I_STAT, jamais le GPU : la
       montre s'arretait exactement pendant qu'on la regardait. Il bat donc
       ici, sur la meme base que tout le reste. */
    g_vblanks++;
    irq_raise(IRQ_VBLANK);
    if ((istat & imask) && !in_irq_flag) deliver_irq();
}

/* Le coprocesseur systeme, reduit a ses registres. Le jeu n'y touche que pour
   armer le GTE dans le registre d'etat et pour ses sections critiques. */
u32 COP0[32];
u32 psx_syscall(u32 a0, u32 a1, u32 a2, u32 a3)
{
    (void)a1; (void)a2; (void)a3;
    /* 1 : entrer en section critique, 2 : en sortir. Sans ordonnanceur, il n'y
       a rien a faire de plus que de le noter. */
    (void)a0;
    return 0;
}
