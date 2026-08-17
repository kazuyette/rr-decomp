/* The PlayStation GPU, complete enough to see the picture.
 *
 * Why a software rasteriser rather than OpenGL
 * -------------------------------------------
 * What we are trying to establish is not speed but fidelity: does the stream
 * of primitives the game produces really form the game's picture? A rasteriser
 * written here answers that question without depending on a driver, a screen
 * or a context -- and it runs in a container with no display. The port to
 * hardware will come later, once the picture is right.
 *
 * What is implemented
 * -------------------
 * Video memory as it is: 1024 by 512 halfwords. Flat, gouraud and textured
 * polygons; rectangles and sprites; lines; transfers to and from video memory;
 * the texture window, the drawing area, the offset, the texture page and the
 * palette. Semi-transparency is applied in all four of its modes.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rt.h"

u16 VRAM[1024 * 512];

/* --- drawing state ------------------------------------------------------ */
static int draw_x0, draw_y0, draw_x1 = 1023, draw_y1 = 511;
static int off_x, off_y;
static u32 texpage;              /* last E1, or a primitive's page word */
static int tw_mx, tw_my, tw_ox, tw_oy;   /* null mask = the whole window */
static int mask_set, mask_test;

/* --- display ------------------------------------------------------------ */
static int disp_x, disp_y, disp_w = 320, disp_h = 240;
unsigned long pixels_prev;
unsigned long long g_pixels;
int g_tint;
unsigned long gpu_frames, null_copies, tex_empty, tex_full, buffer_transfers, buffer_copies;

static inline u16 vram_get(int x, int y)
{
    return VRAM[((y & 511) << 10) | (x & 1023)];
}
static inline void vram_put(int x, int y, u16 c)
{
    VRAM[((y & 511) << 10) | (x & 1023)] = c;
}

/* Semi-transparent blending, in the four proportions of the hardware. */
static u16 blend(u16 back, u16 front, int mode)
{
    int br = back & 31, bg = (back >> 5) & 31, bb = (back >> 10) & 31;
    int fr = front & 31, fg = (front >> 5) & 31, fb = (front >> 10) & 31;
    int r, g, b;
    switch (mode) {
    case 0: r = (br + fr) / 2; g = (bg + fg) / 2; b = (bb + fb) / 2; break;
    case 1: r = br + fr; g = bg + fg; b = bb + fb; break;
    case 2: r = br - fr; g = bg - fg; b = bb - fb; break;
    default: r = br + fr / 4; g = bg + fg / 4; b = bb + fb / 4; break;
    }
    if (r < 0) r = 0; if (r > 31) r = 31;
    if (g < 0) g = 0; if (g > 31) g = 31;
    if (b < 0) b = 0; if (b > 31) b = 31;
    return (u16)(r | (g << 5) | (b << 10) | (front & 0x8000));
}

static void put_pixel(int x, int y, u16 c, int semi, int mode)
{
    u16 old;
    if (x < draw_x0 || x > draw_x1 || y < draw_y0 || y > draw_y1) return;
    if (x < 0 || x > 1023 || y < 0 || y > 511) return;
    old = vram_get(x, y);
    if (mask_test && (old & 0x8000)) return;
    if (semi) c = blend(old, c, mode);
    if (mask_set) c |= 0x8000;
    g_pixels++;
    vram_put(x, y, c);
}

static u16 to15(u32 rgb)
{
    return (u16)(((rgb & 0xFF) >> 3) | ((((rgb >> 8) & 0xFF) >> 3) << 5)
                 | ((((rgb >> 16) & 0xFF) >> 3) << 10));
}

/* --- reading a texel ---------------------------------------------------- */
static int tex_lookup(int u, int v, u32 tp, u32 clut, u16 *out)
{
    int bx = (int)(tp & 0xF) * 64;
    int by = (int)((tp >> 4) & 1) * 256;
    int depth = (int)((tp >> 7) & 3);
    int cx = (int)(clut & 0x3F) * 16;
    int cy = (int)((clut >> 6) & 0x1FF);
    u16 t;
    u = (u & ~(tw_mx * 8)) | ((tw_ox & tw_mx) * 8);
    v = (v & ~(tw_my * 8)) | ((tw_oy & tw_my) * 8);
    u &= 255; v &= 255;
    if (depth == 0) {                       /* sixteen colours */
        u16 w = vram_get(bx + (u >> 2), by + v);
        int idx = (w >> ((u & 3) * 4)) & 0xF;
        t = vram_get(cx + idx, cy);
    } else if (depth == 1) {                /* two hundred and fifty-six */
        u16 w = vram_get(bx + (u >> 1), by + v);
        int idx = (w >> ((u & 1) * 8)) & 0xFF;
        t = vram_get(cx + idx, cy);
    } else {                                /* direct colour */
        t = vram_get(bx + u, by + v);
    }
    /* Absolute black is transparent: that is the hardware's convention, and
       without it the scenery draws over a solid black field. */
    if (t == 0) { tex_empty++; return 0; }
    tex_full++;
    *out = t;
    return 1;
}

/* --- interpolating a triangle -------------------------------------------- */
struct vtx { int x, y; int r, g, b; int u, v; };

static void tri(struct vtx a, struct vtx b, struct vtx c,
                int textured, int shaded, int semi, int mode,
                u32 tp, u32 clut, int blended)
{
    int minx, maxx, miny, maxy, x, y;
    long area = (long)(b.x - a.x) * (c.y - a.y) - (long)(c.x - a.x) * (b.y - a.y);
    if (area == 0) return;
    if (area < 0) { struct vtx t = b; b = c; c = t; area = -area; }

    minx = a.x < b.x ? (a.x < c.x ? a.x : c.x) : (b.x < c.x ? b.x : c.x);
    maxx = a.x > b.x ? (a.x > c.x ? a.x : c.x) : (b.x > c.x ? b.x : c.x);
    miny = a.y < b.y ? (a.y < c.y ? a.y : c.y) : (b.y < c.y ? b.y : c.y);
    maxy = a.y > b.y ? (a.y > c.y ? a.y : c.y) : (b.y > c.y ? b.y : c.y);
    if (minx < draw_x0) minx = draw_x0;
    if (maxx > draw_x1) maxx = draw_x1;
    if (miny < draw_y0) miny = draw_y0;
    if (maxy > draw_y1) maxy = draw_y1;
    /* An outsized triangle always comes from a coordinate read wrong: drawing
       it would cost minutes without showing anything true. */
    if (maxx - minx > 1024 || maxy - miny > 512) return;

    for (y = miny; y <= maxy; y++) {
        for (x = minx; x <= maxx; x++) {
            long w0 = (long)(b.x - a.x) * (y - a.y) - (long)(x - a.x) * (b.y - a.y);
            long w1 = (long)(c.x - b.x) * (y - b.y) - (long)(x - b.x) * (c.y - b.y);
            long w2 = (long)(a.x - c.x) * (y - c.y) - (long)(x - c.x) * (a.y - c.y);
            u16 col;
            if (w0 < 0 || w1 < 0 || w2 < 0) continue;
            /* w1 weights a, w2 weights b, w0 weights c */
            if (textured) {
                int tu = (int)((w1 * a.u + w2 * b.u + w0 * c.u) / area);
                int tv = (int)((w1 * a.v + w2 * b.v + w0 * c.v) / area);
                u16 t;
                if (!tex_lookup(tu, tv, tp, clut, &t)) continue;
                if (blended) {
                    /* The colour modulates the texture: 0x80 leaves it as is. */
                    int mr = (int)((w1 * a.r + w2 * b.r + w0 * c.r) / area);
                    int mg = (int)((w1 * a.g + w2 * b.g + w0 * c.g) / area);
                    int mb = (int)((w1 * a.b + w2 * b.b + w0 * c.b) / area);
                    int r = ((t & 31) * mr) >> 7, g = (((t >> 5) & 31) * mg) >> 7,
                        bl = (((t >> 10) & 31) * mb) >> 7;
                    if (r > 31) r = 31; if (g > 31) g = 31; if (bl > 31) bl = 31;
                    t = (u16)(r | (g << 5) | (bl << 10) | (t & 0x8000));
                }
                put_pixel(x, y, t, semi && (t & 0x8000), mode);
            } else {
                int r = (int)((w1 * a.r + w2 * b.r + w0 * c.r) / area);
                int g = (int)((w1 * a.g + w2 * b.g + w0 * c.g) / area);
                int bl = (int)((w1 * a.b + w2 * b.b + w0 * c.b) / area);
                (void)shaded;
                col = (u16)((r >> 3) | ((g >> 3) << 5) | ((bl >> 3) << 10));
                put_pixel(x, y, col, semi, mode);
            }
        }
    }
}



/* --- the command queue --------------------------------------------------- */
static u32 fifo[16];
static int nfifo, want;
static int img_left, img_x, img_y, img_w, img_h, img_cx, img_cy;
static int rd_left, rd_x, rd_y, rd_w, rd_h, rd_cx, rd_cy;
unsigned long gp0_words, gp1_cmds, prim_count;
unsigned long prim_hist[256];

static int cmd_len(u32 c)
{
    u32 op = c >> 24;
    if (op == 0x02) return 3;
    if (op >= 0x20 && op <= 0x3F) {
        int quad = (op & 8) ? 4 : 3, tex = (op & 4) ? 1 : 0, sh = (op & 0x10) ? 1 : 0;
        return quad * (1 + tex + sh) + (sh ? 0 : 1);
    }
    if (op >= 0x40 && op <= 0x5F) return (op & 0x10) ? 4 : 3;
    if (op >= 0x60 && op <= 0x7F) {
        int tex = (op & 4) ? 1 : 0, var = (((op >> 3) & 3) == 0) ? 1 : 0;
        return 2 + tex + var;
    }
    if (op >= 0x80 && op <= 0x9F) return 4;
    if (op >= 0xA0 && op <= 0xDF) return 3;
    return 1;
}

static struct vtx mkv(u32 xy, u32 col, u32 uv)
{
    struct vtx v;
    v.x = (int)(s16)(xy & 0xFFFF) + off_x;
    v.y = (int)(s16)(xy >> 16) + off_y;
    v.r = (int)(col & 0xFF); v.g = (int)((col >> 8) & 0xFF); v.b = (int)((col >> 16) & 0xFF);
    v.u = (int)(uv & 0xFF); v.v = (int)((uv >> 8) & 0xFF);
    return v;
}

static void draw_rect(u32 op)
{
    u32 col = fifo[0];
    int x = (int)(s16)(fifo[1] & 0xFFFF) + off_x;
    int y = (int)(s16)(fifo[1] >> 16) + off_y;
    int tex = (op & 4) ? 1 : 0, size = (op >> 3) & 3;
    int w, h, i, j, k = 2, bu = 0, bv = 0;
    u32 clut = 0;
    int semi = (op & 2) ? 1 : 0, mode = (int)((texpage >> 5) & 3);
    if (tex) { bu = (int)(fifo[k] & 0xFF); bv = (int)((fifo[k] >> 8) & 0xFF);
               clut = (fifo[k] >> 16) & 0xFFFF; k++; }
    if (size == 0) { w = (int)(fifo[k] & 0xFFFF); h = (int)(fifo[k] >> 16); }
    else if (size == 1) { w = h = 1; }
    else if (size == 2) { w = h = 8; }
    else { w = h = 16; }
    if (w > 1024) w = 1024;
    if (h > 512) h = 512;
    for (j = 0; j < h; j++)
        for (i = 0; i < w; i++) {
            if (tex) {
                u16 t;
                if (!tex_lookup(bu + i, bv + j, texpage, clut, &t)) continue;
                put_pixel(x + i, y + j, t, semi && (t & 0x8000), mode);
            } else {
                put_pixel(x + i, y + j, to15(col), semi, mode);
            }
        }
}

static void draw_poly(u32 op)
{
    int quad = (op & 8) ? 4 : 3, tex = (op & 4) ? 1 : 0, sh = (op & 0x10) ? 1 : 0;
    int semi = (op & 2) ? 1 : 0, blended = (op & 1) ? 0 : 1;
    struct vtx v[4];
    u32 clut = 0, tp = texpage;
    /* Without gouraud shading, the single colour occupies the first word: the
       vertices begin after it. Starting from zero made the command word be
       read as a coordinate -- the whole polygon landed anywhere at all. */
    int i, k = sh ? 0 : 1;
    u32 col = fifo[0] & 0xFFFFFF;
    for (i = 0; i < quad; i++) {
        u32 c = sh ? (fifo[k++] & 0xFFFFFF) : col;
        u32 xy = fifo[k++];
        u32 uv = 0;
        if (tex) {
            uv = fifo[k++];
            if (i == 0) clut = (uv >> 16) & 0xFFFF;
            if (i == 1) { tp = (uv >> 16) & 0xFFFF; texpage = tp; }
        }
        v[i] = mkv(xy, c, uv);
    }
    if (tex && !blended) { for (i = 0; i < quad; i++) { v[i].r = v[i].g = v[i].b = 0x80; } }
    tri(v[0], v[1], v[2], tex, sh, semi, (int)((tp >> 5) & 3), tp, clut, tex);
    if (quad == 4)
        tri(v[1], v[2], v[3], tex, sh, semi, (int)((tp >> 5) & 3), tp, clut, tex);
}

static void draw_line(u32 op)
{
    int sh = (op & 0x10) ? 1 : 0;
    u32 c0 = fifo[0] & 0xFFFFFF, c1 = sh ? (fifo[2] & 0xFFFFFF) : c0;
    u32 p0 = fifo[1], p1 = sh ? fifo[3] : fifo[2];
    int x0 = (int)(s16)(p0 & 0xFFFF) + off_x, y0 = (int)(s16)(p0 >> 16) + off_y;
    int x1 = (int)(s16)(p1 & 0xFFFF) + off_x, y1 = (int)(s16)(p1 >> 16) + off_y;
    int dx = x1 - x0, dy = y1 - y0, n, i;
    n = (dx < 0 ? -dx : dx) > (dy < 0 ? -dy : dy) ? (dx < 0 ? -dx : dx) : (dy < 0 ? -dy : dy);
    if (n <= 0) n = 1;
    if (n > 2048) return;
    for (i = 0; i <= n; i++) {
        u32 c = (i * 2 < n) ? c0 : c1;
        put_pixel(x0 + dx * i / n, y0 + dy * i / n, to15(c),
                  (op & 2) ? 1 : 0, (int)((texpage >> 5) & 3));
    }
}

static void execute(void)
{
    u32 op = fifo[0] >> 24;
    prim_hist[op]++;
    prim_count++;
    if (op == 0x02) {                          /* plain fill */
        int x = (int)(fifo[1] & 0x3F0), y = (int)((fifo[1] >> 16) & 0x1FF);
        int w = (int)(((fifo[2] & 0x3FF) + 15) & ~15), h = (int)((fifo[2] >> 16) & 0x1FF);
        int i, j;
        for (j = 0; j < h; j++)
            for (i = 0; i < w; i++)
                vram_put(x + i, y + j, to15(fifo[0]));
    } else if (op >= 0x20 && op <= 0x3F) {
        draw_poly(op);
    } else if (op >= 0x40 && op <= 0x5F) {
        draw_line(op);
    } else if (op >= 0x60 && op <= 0x7F) {
        draw_rect(op);
    } else if (op >= 0x80 && op <= 0x9F) {      /* internal copy */

        int sx = (int)(fifo[1] & 0x3FF), sy = (int)((fifo[1] >> 16) & 0x1FF);
        int dx = (int)(fifo[2] & 0x3FF), dy = (int)((fifo[2] >> 16) & 0x1FF);
        int w = (int)(fifo[3] & 0x3FF), h = (int)((fifo[3] >> 16) & 0x1FF);
        int i, j;
        /* A copy of zero size makes no sense: treating it as "the whole of
           video memory", which is what the letter of the specification says,
           amounts to smearing the screen from a badly framed word. We ignore
           it, and count how often -- the counter will say if the framing gets
           repaired. */
        if (!w || !h) { null_copies++; return; }
        for (j = 0; j < h; j++)
            for (i = 0; i < w; i++)
                vram_put(dx + i, dy + j, vram_get(sx + i, sy + j));
    } else if (op >= 0xA0 && op <= 0xBF) {      /* to video memory */
        img_x = (int)(fifo[1] & 0x3FF); img_y = (int)((fifo[1] >> 16) & 0x1FF);
        img_w = (int)(fifo[2] & 0x3FF); img_h = (int)((fifo[2] >> 16) & 0x1FF);
        if (!img_w) img_w = 1024;
        if (!img_h) img_h = 512;
        img_cx = img_cy = 0;
        img_left = (img_w * img_h + 1) / 2;
    } else if (op >= 0xC0 && op <= 0xDF) {   /* video memory -> main memory */
        rd_x = (int)(fifo[1] & 0x3FF); rd_y = (int)((fifo[1] >> 16) & 0x1FF);
        rd_w = (int)(fifo[2] & 0x3FF); rd_h = (int)((fifo[2] >> 16) & 0x1FF);
        if (!rd_w) rd_w = 1024;
        if (!rd_h) rd_h = 512;
        rd_cx = rd_cy = 0; rd_left = (rd_w * rd_h + 1) / 2;
    } else if (op == 0xE1) {
        texpage = fifo[0] & 0x3FFF;
    } else if (op == 0xE2) {
        tw_mx = (int)(fifo[0] & 0x1F); tw_my = (int)((fifo[0] >> 5) & 0x1F);
        tw_ox = (int)((fifo[0] >> 10) & 0x1F); tw_oy = (int)((fifo[0] >> 15) & 0x1F);
    } else if (op == 0xE3) {
        draw_x0 = (int)(fifo[0] & 0x3FF); draw_y0 = (int)((fifo[0] >> 10) & 0x1FF);
    } else if (op == 0xE4) {
        draw_x1 = (int)(fifo[0] & 0x3FF); draw_y1 = (int)((fifo[0] >> 10) & 0x1FF);
    } else if (op == 0xE5) {
        off_x = (int)(((s32)(fifo[0] << 21)) >> 21);
        off_y = (int)(((s32)(fifo[0] << 10)) >> 21);
    } else if (op == 0xE6) {
        mask_set = (int)(fifo[0] & 1); mask_test = (int)((fifo[0] >> 1) & 1);
    }
}

void gpu_gp0(u32 v)
{
    gp0_words++;
    if (img_left > 0) {
        int k;
        for (k = 0; k < 2; k++) {
            u16 half = (u16)(k ? (v >> 16) : v);
            if (img_cy < img_h) vram_put(img_x + img_cx, img_y + img_cy, half);
            if (++img_cx >= img_w) { img_cx = 0; img_cy++; }
        }
        img_left--;
        return;
    }
    if (nfifo == 0) {
        want = cmd_len(v);
        fifo[0] = v; nfifo = 1;
        if (want == 1) { execute(); nfifo = 0; }
        return;
    }
    if (nfifo < 16) fifo[nfifo] = v;
    nfifo++;
    if (nfifo >= want) { execute(); nfifo = 0; }
}

/* Reading video memory. The channel can also pull from the GPU into main
   memory: ignoring the direction bit amounted to pushing the contents of the
   stack into the GPU, which the hardware then read as commands. Hence internal
   copies drawn from nowhere, which smeared the display buffer with texture. */
u32 gpu_read_word(void)
{
    u32 v = 0;
    int k;
    if (rd_left <= 0) return 0;
    for (k = 0; k < 2; k++) {
        u16 h = (rd_cy < rd_h) ? vram_get(rd_x + rd_cx, rd_y + rd_cy) : 0;
        v |= (u32)h << (16 * k);
        if (++rd_cx >= rd_w) { rd_cx = 0; rd_cy++; }
    }
    rd_left--;
    return v;
}

void gpu_reset_fifo(void) { nfifo = 0; }

void gpu_gp1(u32 v)
{
    u32 op = (v >> 24) & 0xFF;
    gp1_cmds++;
    if (op == 0x00) { nfifo = 0; img_left = 0; }
    else if (op == 0x05) {
        /* The game designates the area to display: this is its buffer swap,
           and so the exact moment a frame is finished. That is where the frame
           has to be shown, not at the end of some arbitrary counter. */
        void video_image(const u16 *, int, int, int, int);
        disp_x = (int)(v & 0x3FF); disp_y = (int)((v >> 10) & 0x1FF);
        video_image(VRAM, disp_x, disp_y, disp_w, disp_h);
    }
    else if (op == 0x08) {
        static const int wtab[4] = { 256, 320, 512, 640 };
        disp_w = (v & 0x40) ? 368 : wtab[v & 3];
        disp_h = (v & 4) ? 480 : 240;
    }
}

/* --- output ------------------------------------------------------------- */
void gpu_write_ppm(const char *path)
{
    FILE *f = fopen(path, "wb");
    int x, y;
    if (!f) return;
    fprintf(f, "P6\n%d %d\n255\n", disp_w, disp_h);
    for (y = 0; y < disp_h; y++)
        for (x = 0; x < disp_w; x++) {
            u16 c = vram_get(disp_x + x, disp_y + y);
            unsigned char px[3];
            px[0] = (unsigned char)((c & 31) << 3);
            px[1] = (unsigned char)(((c >> 5) & 31) << 3);
            px[2] = (unsigned char)(((c >> 10) & 31) << 3);
            fwrite(px, 1, 3, f);
        }
    fclose(f);
    gpu_frames++;
}

void gpu_write_vram(const char *path)
{
    FILE *f = fopen(path, "wb");
    int x, y;
    if (!f) return;
    fprintf(f, "P6\n1024 512\n255\n");
    for (y = 0; y < 512; y++)
        for (x = 0; x < 1024; x++) {
            u16 c = vram_get(x, y);
            unsigned char px[3];
            px[0] = (unsigned char)((c & 31) << 3);
            px[1] = (unsigned char)(((c >> 5) & 31) << 3);
            px[2] = (unsigned char)(((c >> 10) & 31) << 3);
            fwrite(px, 1, 3, f);
        }
    fclose(f);
}
FILE *gpulog;
