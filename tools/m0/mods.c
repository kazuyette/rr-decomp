/* The settings menu, drawn on top of the game.
 *
 * Why a menu of our own rather than an entry in the game's
 * -------------------------------------------------------
 * Adding a line to Ridge Racer's OPTION menu would first require decompiling
 * state 18, which is still mechanically translated assembly: we would be
 * modifying code that is regenerated on every build, and the modification
 * would not survive. This menu lives entirely on our side. It does not touch
 * the game, it does not survive regeneration any less well, and above all it
 * is allowed to adjust things the console did not have -- the frame rate, the
 * audio latency, the resolution.
 *
 * It is drawn into the final image, after video memory rather than inside it:
 * the game therefore cannot erase it by redrawing, and we cannot soil what it
 * has produced. The two remain separate, which matters on the day one compares
 * a frame against a reference.
 *
 * While it is open, the controller reports "nothing pressed" to the game: we
 * do not want to drive and adjust at the same time.
 */
#include <stdio.h>
#include <string.h>
#include "rt.h"

/* 5 by 7 font, one row per byte, five useful bits.
   Written as ASCII art and then converted -- a table of numbers typed by hand
   reads back poorly and goes wrong in silence. */
static const unsigned char FONT[][7] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00},   /* space */
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
static const char CHARSET[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:.-/<>*%()";

/* --- the settings --------------------------------------------------------
 *
 * Each entry is an integer value with its bounds and its step; the value's
 * label is produced by a function, because "60 frames/s" and "free" are the
 * same variable.
 */
extern double mod_hz;
extern unsigned g_latency_bytes;
extern int g_draw_cost;
extern int mod_mute_music, mod_mute_spu, mod_show_state, mod_negcon;
extern int mod_show_pad;
extern u32 g_pad_word;
extern unsigned char g_pad_analog[4];
extern int g_pad_type;

static int hz_i = 60;
static int lat_i = 40;

struct setting {
    const char *name;
    int *value, min, max, step;
    void (*format)(int, char *);
    void (*apply)(int);
};

static void t_hz(int v, char *s)   { if (v) sprintf(s, "%d", v); else sprintf(s, "FREE"); }
static void t_ms(int v, char *s)   { sprintf(s, "%d MS", v); }
static void t_yes(int v, char *s)  { strcpy(s, v ? "YES" : "NO"); }
static void t_no(int v, char *s)   { strcpy(s, v ? "NO" : "YES"); }
static void t_pad(int v, char *s)  { strcpy(s, v ? "NEGCON" : "DIGITAL"); }

static void a_hz(int v)  { mod_hz = v; }
static void a_lat(int v) { g_latency_bytes = 44100u * 4u * (unsigned)v / 1000u; }
static void a_none(int v){ (void)v; }

static struct setting SETTINGS[] = {
    { "FRAMES PER SECOND",  &hz_i,               0, 240, 10, t_hz,  a_hz   },
    { "AUDIO LEAD",         &lat_i,              5, 200,  5, t_ms,  a_lat  },
    { "CONTROLLER",         &mod_negcon,         0,   1,  1, t_pad, a_none },
    { "SHOW CONTROLLER",    &mod_show_pad,       0,   1,  1, t_yes, a_none },
    { "DRAW COST",          &g_draw_cost,        0,   1,  1, t_yes, a_none },
    { "MUSIC",              &mod_mute_music,     0,   1,  1, t_no,  a_none },
    { "EFFECTS",            &mod_mute_spu,       0,   1,  1, t_no,  a_none },
    { "GAME STATE",         &mod_show_state,     0,   1,  1, t_yes, a_none },
};
#define NSETTINGS ((int)(sizeof SETTINGS / sizeof SETTINGS[0]))

static int menu_open, choice;

int mods_is_open(void) { return menu_open; }
void mods_toggle(void) { menu_open = !menu_open; }

void mods_move(int d)
{
    choice += d;
    if (choice < 0) choice = NSETTINGS - 1;
    if (choice >= NSETTINGS) choice = 0;
}

void mods_change(int d)
{
    struct setting *r = &SETTINGS[choice];
    int v = *r->value + d * r->step;
    if (v < r->min) v = r->min;
    if (v > r->max) v = r->max;
    *r->value = v;
    r->apply(v);
}

/* --- drawing -------------------------------------------------------------- */
static void glyph(u32 *px, int pitch, int w, int h, int x, int y, char c, u32 colour)
{
    const char *p = strchr(CHARSET, c);
    int i, j, n;
    if (!p) p = CHARSET;
    n = (int)(p - CHARSET);
    for (j = 0; j < 7; j++)
        for (i = 0; i < 5; i++)
            if (FONT[n][j] & (0x10 >> i)) {
                int xx = x + i, yy = y + j;
                if (xx >= 0 && xx < w && yy >= 0 && yy < h)
                    px[yy * (pitch / 4) + xx] = colour;
            }
}

static void text(u32 *px, int pitch, int w, int h, int x, int y,
                 const char *s, u32 colour)
{
    for (; *s; s++, x += 6) glyph(px, pitch, w, h, x, y, *s, colour);
}

static void backdrop(u32 *px, int pitch, int w, int h, int x0, int y0, int x1, int y1)
{
    int x, y;
    for (y = y0; y < y1 && y < h; y++)
        for (x = x0; x < x1 && x < w; x++) {
            /* Darken rather than paint: the game stays visible underneath,
               which is a reminder that one is adjusting something that runs. */
            u32 c = px[y * (pitch / 4) + x];
            px[y * (pitch / 4) + x] = 0xFF000000u | ((c >> 2) & 0x3F3F3Fu);
        }
}

void mods_draw(u32 *px, int pitch, int w, int h)
{
    char line[64], val[24];
    int i, y;
    extern unsigned long states_seen[64];
    if (mod_show_state) {
        extern u8 RAM[];
        u32 e;
        __builtin_memcpy(&e, RAM + 0x1D34F8, 4);
        sprintf(line, "STATE %u", e);
        text(px, pitch, w, h, 4, 4, line, 0xFF00FF00u);
    }
    if (mod_show_pad) {
        /* The word is active low, as on the console: FFFF means nothing is
           pressed. This is the number to watch -- if it does not move when a
           button goes down, the problem is upstream of the game. */
        sprintf(line, "PAD %04X TYPE %02X  T%02X I%02X II%02X L%02X",
                (unsigned)(g_pad_word & 0xFFFFu), (unsigned)g_pad_type,
                g_pad_analog[0], g_pad_analog[1], g_pad_analog[2], g_pad_analog[3]);
        text(px, pitch, w, h, 4, h - 12, line, 0xFF00FFFFu);
    }
    if (!menu_open) return;

    backdrop(px, pitch, w, h, 8, 20, w - 8, 20 + 14 * NSETTINGS + 24);
    text(px, pitch, w, h, 16, 26, "SETTINGS", 0xFFFFFF00u);
    y = 44;
    for (i = 0; i < NSETTINGS; i++, y += 14) {
        u32 c = (i == choice) ? 0xFFFFFF00u : 0xFFB0B0B0u;
        SETTINGS[i].format(*SETTINGS[i].value, val);
        sprintf(line, "%c %-18s %s", (i == choice) ? '>' : ' ',
                SETTINGS[i].name, val);
        text(px, pitch, w, h, 16, y, line, c);
    }
    text(px, pitch, w, h, 16, y + 6, "F1 CLOSE   ARROWS ADJUST", 0xFF808080u);
    (void)states_seen;
}
