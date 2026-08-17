/* Le menu des réglages, dessiné par-dessus le jeu.
 *
 * Pourquoi un menu à nous plutôt qu'une entrée dans celui du jeu
 * -------------------------------------------------------------
 * Ajouter une ligne au menu OPTION de Ridge Racer demanderait d'abord de
 * décompiler l'état 18, qui est encore de l'assembleur traduit mécaniquement :
 * on modifierait du code régénéré à chaque construction, et la modification ne
 * survivrait pas. Ce menu-ci vit entièrement de notre côté. Il ne touche pas
 * au jeu, ne survit pas moins bien aux régénérations, et surtout il a le droit
 * de régler des choses que la console n'avait pas -- la cadence, la latence
 * audio, la résolution.
 *
 * Il se dessine dans l'image finale, après la mémoire vidéo, et non dedans :
 * le jeu ne peut donc pas l'effacer en redessinant, et nous ne pouvons pas
 * salir ce qu'il a produit. Les deux restent séparés, ce qui compte le jour où
 * l'on compare une image à une référence.
 *
 * Tant qu'il est ouvert, la manette rend « rien d'enfoncé » au jeu : on ne
 * veut pas piloter et régler en même temps.
 */
#include <stdio.h>
#include <string.h>
#include "rt.h"

/* Police 5 par 7, une ligne par octet, cinq bits utiles.
   Ecrite en art ASCII puis convertie -- une table de nombres tapee a la
   main se relit mal et se trompe en silence. */
static const unsigned char POLICE[][7] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00},   /* espace */
    {0x0E,0x11,0x11,0x1F,0x11,0x11,0x11},   /* A */
    {0x1E,0x11,0x1E,0x11,0x11,0x11,0x1E},   /* B */
    {0x0F,0x10,0x10,0x10,0x10,0x10,0x0F},   /* C */
    {0x1E,0x11,0x11,0x11,0x11,0x11,0x1E},   /* D */
    {0x1F,0x10,0x1E,0x10,0x10,0x10,0x1F},   /* E */
    {0x1F,0x10,0x1E,0x10,0x10,0x10,0x10},   /* F */
    {0x0F,0x10,0x10,0x17,0x11,0x11,0x0F},   /* G */
    {0x11,0x11,0x1F,0x11,0x11,0x11,0x11},   /* H */
    {0x1F,0x04,0x04,0x04,0x04,0x04,0x1F},   /* I */
    {0x07,0x02,0x02,0x02,0x02,0x12,0x0C},   /* J */
    {0x11,0x12,0x14,0x18,0x14,0x12,0x11},   /* K */
    {0x10,0x10,0x10,0x10,0x10,0x10,0x1F},   /* L */
    {0x11,0x1B,0x15,0x15,0x11,0x11,0x11},   /* M */
    {0x11,0x19,0x15,0x13,0x11,0x11,0x11},   /* N */
    {0x0E,0x11,0x11,0x11,0x11,0x11,0x0E},   /* O */
    {0x1E,0x11,0x11,0x1E,0x10,0x10,0x10},   /* P */
    {0x0E,0x11,0x11,0x11,0x15,0x12,0x0D},   /* Q */
    {0x1E,0x11,0x11,0x1E,0x14,0x12,0x11},   /* R */
    {0x0F,0x10,0x10,0x0E,0x01,0x01,0x1E},   /* S */
    {0x1F,0x04,0x04,0x04,0x04,0x04,0x04},   /* T */
    {0x11,0x11,0x11,0x11,0x11,0x11,0x0E},   /* U */
    {0x11,0x11,0x11,0x11,0x11,0x0A,0x04},   /* V */
    {0x11,0x11,0x11,0x15,0x15,0x1B,0x11},   /* W */
    {0x11,0x11,0x0A,0x04,0x0A,0x11,0x11},   /* X */
    {0x11,0x11,0x0A,0x04,0x04,0x04,0x04},   /* Y */
    {0x1F,0x01,0x02,0x04,0x08,0x10,0x1F},   /* Z */
    {0x0E,0x11,0x13,0x15,0x19,0x11,0x0E},   /* 0 */
    {0x04,0x0C,0x04,0x04,0x04,0x04,0x0E},   /* 1 */
    {0x0E,0x11,0x01,0x06,0x08,0x10,0x1F},   /* 2 */
    {0x1E,0x01,0x01,0x0E,0x01,0x01,0x1E},   /* 3 */
    {0x02,0x06,0x0A,0x12,0x1F,0x02,0x02},   /* 4 */
    {0x1F,0x10,0x1E,0x01,0x01,0x11,0x0E},   /* 5 */
    {0x06,0x08,0x10,0x1E,0x11,0x11,0x0E},   /* 6 */
    {0x1F,0x01,0x02,0x04,0x08,0x08,0x08},   /* 7 */
    {0x0E,0x11,0x11,0x0E,0x11,0x11,0x0E},   /* 8 */
    {0x0E,0x11,0x11,0x0F,0x01,0x02,0x0C},   /* 9 */
    {0x00,0x04,0x04,0x00,0x04,0x04,0x00},   /* : */
    {0x00,0x00,0x00,0x00,0x00,0x0C,0x0C},   /* . */
    {0x00,0x00,0x00,0x1F,0x00,0x00,0x00},   /* - */
    {0x01,0x02,0x02,0x04,0x08,0x08,0x10},   /* / */
    {0x02,0x04,0x08,0x10,0x08,0x04,0x02},   /* < */
    {0x08,0x04,0x02,0x01,0x02,0x04,0x08},   /* > */
    {0x00,0x15,0x0E,0x1F,0x0E,0x15,0x00},   /* * */
    {0x19,0x1A,0x02,0x04,0x08,0x0B,0x13},   /* % */
    {0x02,0x04,0x08,0x08,0x08,0x04,0x02},   /* ( */
    {0x08,0x04,0x02,0x02,0x02,0x04,0x08},   /* ) */
};
static const char ORDRE[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:.-/<>*%()";

/* --- les réglages --------------------------------------------------------
 *
 * Chaque entrée est une valeur entière avec ses bornes et son pas ; le libellé
 * de la valeur est rendu par une fonction, parce que « 60 images/s » et
 * « libre » sont la même variable.
 */
extern double mod_hz;
extern unsigned g_latence_octets;
extern int g_cout_dessin;
extern int mod_muet_musique, mod_muet_spu, mod_afficher_etat;

static int hz_i = 60;
static int lat_i = 40;

struct reglage {
    const char *nom;
    int *valeur, mini, maxi, pas;
    void (*texte)(int, char *);
    void (*appliquer)(int);
};

static void t_hz(int v, char *s)   { if (v) sprintf(s, "%d", v); else sprintf(s, "LIBRE"); }
static void t_ms(int v, char *s)   { sprintf(s, "%d MS", v); }
static void t_oui(int v, char *s)  { strcpy(s, v ? "OUI" : "NON"); }
static void t_non(int v, char *s)  { strcpy(s, v ? "NON" : "OUI"); }

static void a_hz(int v)  { mod_hz = v; }
static void a_lat(int v) { g_latence_octets = 44100u * 4u * (unsigned)v / 1000u; }
static void a_rien(int v){ (void)v; }

static struct reglage REGLAGES[] = {
    { "IMAGES PAR SECONDE", &hz_i,               0, 240, 10, t_hz,  a_hz   },
    { "AVANCE DU SON",      &lat_i,              5, 200,  5, t_ms,  a_lat  },
    { "COUT DU DESSIN",     &g_cout_dessin,      0,   1,  1, t_oui, a_rien },
    { "MUSIQUE",            &mod_muet_musique,   0,   1,  1, t_non, a_rien },
    { "BRUITAGES",          &mod_muet_spu,       0,   1,  1, t_non, a_rien },
    { "ETAT DU JEU",        &mod_afficher_etat,  0,   1,  1, t_oui, a_rien },
};
#define NREGLAGES ((int)(sizeof REGLAGES / sizeof REGLAGES[0]))

static int ouvert, choix;

int mods_ouvert(void) { return ouvert; }
void mods_basculer(void) { ouvert = !ouvert; }

void mods_deplacer(int d)
{
    choix += d;
    if (choix < 0) choix = NREGLAGES - 1;
    if (choix >= NREGLAGES) choix = 0;
}

void mods_changer(int d)
{
    struct reglage *r = &REGLAGES[choix];
    int v = *r->valeur + d * r->pas;
    if (v < r->mini) v = r->mini;
    if (v > r->maxi) v = r->maxi;
    *r->valeur = v;
    r->appliquer(v);
}

/* --- dessin --------------------------------------------------------------- */
static void glyphe(u32 *px, int pas, int l, int h, int x, int y, char c, u32 couleur)
{
    const char *p = strchr(ORDRE, c);
    int i, j, n;
    if (!p) p = ORDRE;
    n = (int)(p - ORDRE);
    for (j = 0; j < 7; j++)
        for (i = 0; i < 5; i++)
            if (POLICE[n][j] & (0x10 >> i)) {
                int xx = x + i, yy = y + j;
                if (xx >= 0 && xx < l && yy >= 0 && yy < h)
                    px[yy * (pas / 4) + xx] = couleur;
            }
}

static void texte(u32 *px, int pas, int l, int h, int x, int y,
                  const char *s, u32 couleur)
{
    for (; *s; s++, x += 6) glyphe(px, pas, l, h, x, y, *s, couleur);
}

static void fond(u32 *px, int pas, int l, int h, int x0, int y0, int x1, int y1)
{
    int x, y;
    for (y = y0; y < y1 && y < h; y++)
        for (x = x0; x < x1 && x < l; x++) {
            /* Assombrir plutot que peindre : on garde le jeu visible dessous,
               ce qui rappelle qu'on regle quelque chose qui tourne. */
            u32 c = px[y * (pas / 4) + x];
            px[y * (pas / 4) + x] = 0xFF000000u | ((c >> 2) & 0x3F3F3Fu);
        }
}

void mods_dessiner(u32 *px, int pas, int l, int h)
{
    char ligne[64], val[24];
    int i, y;
    extern unsigned long etats_vus[64];
    if (mod_afficher_etat) {
        extern u8 RAM[];
        u32 e;
        __builtin_memcpy(&e, RAM + 0x1D34F8, 4);
        sprintf(ligne, "ETAT %u", e);
        texte(px, pas, l, h, 4, 4, ligne, 0xFF00FF00u);
    }
    if (!ouvert) return;

    fond(px, pas, l, h, 8, 20, l - 8, 20 + 14 * NREGLAGES + 24);
    texte(px, pas, l, h, 16, 26, "REGLAGES", 0xFFFFFF00u);
    y = 44;
    for (i = 0; i < NREGLAGES; i++, y += 14) {
        u32 c = (i == choix) ? 0xFFFFFF00u : 0xFFB0B0B0u;
        REGLAGES[i].texte(*REGLAGES[i].valeur, val);
        sprintf(ligne, "%c %-18s %s", (i == choix) ? '>' : ' ',
                REGLAGES[i].nom, val);
        texte(px, pas, l, h, 16, y, ligne, c);
    }
    texte(px, pas, l, h, 16, y + 6, "F1 FERMER  FLECHES REGLER", 0xFF808080u);
    (void)etats_vus;
}
