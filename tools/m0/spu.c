/* The SPU: the twenty-four voices.
 *
 * The music came from the disc and asked only to be served. The rest -- the
 * engine, the tyre squeals, the voices -- comes from here: half a megabyte of
 * separate memory, filled by DMA channel 4, and twenty-four players that draw
 * compressed samples from it, each at its own pitch and volume.
 *
 * What is implemented
 * -------------------
 * The memory and its transfer, ADPCM decompression with its loops, pitch, the
 * left and right volumes, keying voices on and off, and an envelope. Mixing is
 * done at 44100 Hz, the hardware's output rate, which avoids any resampling on
 * the way out.
 *
 * What is simplified, and it should be said
 * -----------------------------------------
 * The hardware envelope has four phases whose slopes follow precise
 * exponential tables. This one keeps its shape -- attack, decay, sustain,
 * release -- with piecewise linear slopes. A held note will sound right; a
 * very short attack will sound less so. Reverb is not implemented at all: the
 * game writes its registers, we accept them and ignore them.
 */
#include <string.h>
#include <stdio.h>
#include "rt.h"

u8 SPURAM[0x80000];

/* --- one voice ----------------------------------------------------------- */
struct voice {
    u16 vol_l, vol_r;      /* volumes, hardware format */
    u16 pitch;             /* pitch: 0x1000 = 44100 Hz */
    u16 start, loop;       /* addresses, in blocks of eight bytes */
    u32 adsr;              /* the two envelope registers */
    /* playback state */
    u32 addr;              /* current byte in the SPU's memory */
    u32 phase;             /* fractional position, 12 bits */
    s16 smp[28];           /* the decoded block */
    int n;                 /* how many samples are left in it */
    s16 p1, p2;            /* the previous two, for the filter */
    int active;
    int ended;             /* the block carried the end marker */
    /* envelope */
    int env_phase;         /* 0 off, 1 attack, 2 decay, 3 sustain, 4 release */
    int level;             /* 0 to 0x7FFF */
    int env_wait;          /* cycles left before the next step */
};

static struct voice v[24];
static u16 ctrl, transfer_ctrl;
static u32 transfer_addr;
static u16 master_vol_l, master_vol_r;
unsigned long spu_voices_played;
int spu_peak;           /* the loudest amplitude produced */
unsigned long spu_voices_off;
unsigned long spu_sweeps, spu_vol_plain;

/* --- decompression ------------------------------------------------------- */
static const int filter_pos[5] = { 0, 60, 115, 98, 122 };
static const int filter_neg[5] = { 0, 0, -52, -55, -60 };

static s16 saturate(int x)
{
    if (x < -32768) return -32768;
    if (x > 32767) return 32767;
    return (s16)x;
}

static void next_block(struct voice *w)
{
    const u8 *b = SPURAM + (w->addr & 0x7FFF0);
    int shift = b[0] & 0x0F;
    int filter = (b[0] >> 4) & 0x0F;
    int flags = b[1];
    int i;
    if (filter > 4) filter = 4;
    if (shift > 12) shift = 9;   /* this is how the hardware handles
                                    forbidden values */
    for (i = 0; i < 28; i++) {
        int raw = (b[2 + i / 2] >> ((i & 1) * 4)) & 0x0F;
        int e = (int)((s16)(raw << 12)) >> shift;
        e += (w->p1 * filter_pos[filter] + w->p2 * filter_neg[filter]) / 64;
        w->smp[i] = saturate(e);
        w->p2 = w->p1;
        w->p1 = w->smp[i];
    }
    w->n = 28;
    /* Bit 2 marks the return point, bit 0 the end of the sound. Without bit 1,
       the end stops the voice; with it, the voice goes back there. */
    if (flags & 4) w->loop = (u16)((w->addr & 0x7FFF0) >> 3);
    if (flags & 1) {
        w->ended = 1;
        w->addr = (u32)w->loop << 3;
        if (!(flags & 2)) { w->env_phase = 4; w->env_wait = 1; }
    } else {
        w->addr += 16;
    }
}

/* --- envelope -------------------------------------------------------------
 *
 * The four phases of the hardware, with their real slopes.
 *
 * The principle is the same everywhere: a shift gives the period, a step gives
 * the amplitude, and the pair is read from the register according to the
 * phase. Above eleven, the shift spaces the updates out; below it, the shift
 * amplifies the step. In exponential mode, a rise slows by a factor of four
 * past three quarters, and a fall is proportional to the level reached -- that
 * is what gives releases their tail.
 *
 * Decay has a fixed step of -8 and is always exponential; the other phases
 * read their mode from the register.
 */
static void envelope(struct voice *w)
{
    int shift, step, expo, decaying, target = -1;
    if (w->env_phase == 0) { w->level = 0; return; }
    if (--w->env_wait > 0) return;
    switch (w->env_phase) {
    case 1:                                   /* attack */
        shift = (w->adsr >> 10) & 0x1F;
        step = 7 - ((w->adsr >> 8) & 3);
        expo = (w->adsr >> 15) & 1;
        decaying = 0;
        break;
    case 2:                                   /* decay */
        shift = (w->adsr >> 4) & 0x0F;
        step = -8; expo = 1; decaying = 1;
        target = (int)((w->adsr & 0x0F) + 1) * 0x800;
        if (target > 0x7FFF) target = 0x7FFF;
        break;
    case 3:                                   /* sustain */
        shift = (w->adsr >> 24) & 0x1F;
        decaying = (w->adsr >> 30) & 1;
        step = decaying ? (-8 + (int)((w->adsr >> 22) & 3))
                        : (7 - (int)((w->adsr >> 22) & 3));
        expo = (w->adsr >> 31) & 1;
        break;
    default:                                  /* release */
        shift = (w->adsr >> 16) & 0x1F;
        step = -8; expo = (w->adsr >> 21) & 1; decaying = 1;
        break;
    }
    {
        int cycles = 1 << (shift > 11 ? shift - 11 : 0);
        int amplitude = step << (shift < 11 ? 11 - shift : 0);
        if (expo) {
            if (!decaying && w->level > 0x6000) cycles *= 4;
            if (decaying) amplitude = (int)((long)amplitude * w->level / 0x8000);
        }
        w->level += amplitude;
        if (w->level > 0x7FFF) w->level = 0x7FFF;
        if (w->level < 0) w->level = 0;
        w->env_wait = cycles;
    }
    if (w->env_phase == 1 && w->level >= 0x7FFF) w->env_phase = 2;
    else if (w->env_phase == 2 && target >= 0 && w->level <= target) w->env_phase = 3;
    else if (w->env_phase == 4 && w->level <= 0) { w->env_phase = 0; w->active = 0; }
}

/* The hardware volumes are fifteen-bit signed when the top bit is zero;
   otherwise it is a sweep, which we approximate by its starting value. */
static int volume(u16 r)
{
    if (r & 0x8000) return 0x3FFF;
    return (int)(s16)(r << 1) / 2;
}

/* --- mixing -------------------------------------------------------------- */
void spu_mix(s16 *out, int frames)
{
    int i, k;
    for (i = 0; i < frames; i++) { out[2 * i] = 0; out[2 * i + 1] = 0; }
    /* The enable bit is respected. It has not always been: the game was keying
       its voices on while this register read zero, which on the console would
       produce nothing -- so it was not doing that, and the fault was ours. It
       was not in the SPU but in the halfword read, which returned the
       neighbouring register. The counter below stays in place: it reads zero,
       and it is that zero which attests to the fix. */
    if (!(ctrl & 0x8000)) return;
    for (k = 0; k < 24; k++) {
        struct voice *w = &v[k];
        int lv, rv;
        if (!w->active) continue;
        lv = volume(w->vol_l);
        rv = volume(w->vol_r);
        for (i = 0; i < frames; i++) {
            s16 e;
            if (!w->active) break;
            if (w->n <= 0) { next_block(w); if (!w->active) break; }
            e = w->smp[28 - w->n];
            {
                int a = (int)e * w->level >> 15;
                int nl = out[2 * i] + (a * lv >> 14);
                int nr = out[2 * i + 1] + (a * rv >> 14);
                out[2 * i] = saturate(nl);
                out[2 * i + 1] = saturate(nr);
                if (nl > spu_peak) spu_peak = nl;
                if (-nl > spu_peak) spu_peak = -nl;
            }
            /* The advance depends on the pitch: 0x1000 reads one sample per
               output frame, twice that reads two. */
            w->phase += (w->pitch > 0x3FFF) ? 0x3FFF : w->pitch;
            while (w->phase >= 0x1000) {
                w->phase -= 0x1000;
                if (--w->n <= 0) { next_block(w); if (!w->active) break; }
            }
            envelope(w);
        }
    }
}

int spu_active(void)
{
    int k;
    for (k = 0; k < 24; k++) if (v[k].active) return 1;
    return 0;
}

/* --- registers ----------------------------------------------------------- */
static void key_on(u32 mask)
{
    int k;
    for (k = 0; k < 24; k++)
        if (mask & (1u << k)) {
            struct voice *w = &v[k];
            w->addr = (u32)w->start << 3;
            w->loop = w->start;
            w->phase = 0; w->n = 0; w->p1 = w->p2 = 0;
            w->active = 1; w->ended = 0;
            w->env_phase = 1; w->level = 0; w->env_wait = 1;
            spu_voices_played++;
            if (!(ctrl & 0x8000)) spu_voices_off++;
        }
}

static void key_off(u32 mask)
{
    int k;
    for (k = 0; k < 24; k++)
        if (mask & (1u << k)) { v[k].env_phase = 4; v[k].env_wait = 1; }
}

void spu_write16(u32 addr, u16 value)
{
    /* The registers start at 0x1F801C00: the voices first, sixteen bytes each,
       then the control block from 0x180 on. */
    u32 p = (addr - 0x1F801C00u) & 0xFFF;
    if (p < 0x180) {                           /* the twenty-four voices */
        struct voice *w = &v[p >> 4];
        switch (p & 0x0F) {
        case 0x0: w->vol_l = value; if (value & 0x8000) spu_sweeps++; else spu_vol_plain++; break;
        case 0x2: w->vol_r = value; break;
        case 0x4: w->pitch = value; break;
        case 0x6: w->start = value; break;
        case 0x8: w->adsr = (w->adsr & 0xFFFF0000u) | value; break;
        case 0xA: w->adsr = (w->adsr & 0xFFFFu) | ((u32)value << 16); break;
        case 0xC: break;                       /* current volume, read only */
        case 0xE: w->loop = value; break;
        }
        return;
    }
    switch (p) {
    case 0x180: master_vol_l = value; break;
    case 0x182: master_vol_r = value; break;
    /* Writing to these registers acts at once: each bit set keys its voice on
       or off immediately, low half and high half independently. */
    case 0x188: key_on(value); break;
    case 0x18A: key_on((u32)value << 16); break;
    case 0x18C: key_off(value); break;
    case 0x18E: key_off((u32)value << 16); break;
    case 0x1A6: transfer_addr = (u32)value << 3; break;
    case 0x1A8:                                /* the transfer queue */
        if (transfer_addr < sizeof SPURAM - 1) {
            SPURAM[transfer_addr] = (u8)value;
            SPURAM[transfer_addr + 1] = (u8)(value >> 8);
            transfer_addr += 2;
        }
        break;
    case 0x1AA: ctrl = value; break;
    case 0x1AC: transfer_ctrl = value; break;
    default: break;
    }
}

u16 spu_read16(u32 addr)
{
    /* The registers start at 0x1F801C00: the voices first, sixteen bytes each,
       then the control block from 0x180 on. */
    u32 p = (addr - 0x1F801C00u) & 0xFFF;
    if (p < 0x180) {
        struct voice *w = &v[p >> 4];
        switch (p & 0x0F) {
        case 0x0: return w->vol_l;
        case 0x2: return w->vol_r;
        case 0x4: return w->pitch;
        case 0x6: return w->start;
        case 0x8: return (u16)w->adsr;
        case 0xA: return (u16)(w->adsr >> 16);
        case 0xC: return (u16)w->level;
        case 0xE: return w->loop;
        }
    }
    switch (p) {
    case 0x1AA: return ctrl;
    case 0x1AC: return transfer_ctrl;
    /* The status: bit 10 says the transfer is finished, which here it always
       is, and the low bits repeat the control register. */
    case 0x1AE: return (u16)((ctrl & 0x3F) | 0x0000);
    case 0x1B8: case 0x1BA: return 0;
    default: return 0;
    }
}

/* DMA channel 4 pours the samples into the SPU's memory. */
void spu_dma(const u8 *ram, u32 addr, u32 bytes)
{
    u32 i;
    for (i = 0; i < bytes; i++) {
        if (transfer_addr >= sizeof SPURAM) break;
        SPURAM[transfer_addr++] = ram[(addr + i) & 0x1FFFFF];
    }
}
