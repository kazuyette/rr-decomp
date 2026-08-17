/* The hardware, seen from very far away: what it takes for the game to run
 * and for us to see what it sends to the screen. Nothing more.
 *
 * M0 does not try to display. It tries to establish that the game's loop
 * runs, and the proof we expect from it is a coherent stream of GPU packets
 * -- recognisable commands, plausible coordinates. A GPU that draws would
 * come later; a GPU that logs is enough to settle the matter.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include "rt.h"

/* Interrupts, for real.
 *
 * I_STAT carries the pending sources, I_MASK the ones that are armed.
 * Writing to I_STAT acknowledges: the bits at zero in the written value are
 * cleared. Returning a constant, as I used to, leaves the flag raised
 * forever -- the handler endlessly reprocesses the same source and never
 * reaches the others. */
u32 g_istat_mirror, g_imask_mirror;
#define istat g_istat_mirror
#define imask g_imask_mirror
void irq_raise(u32 bit) { istat |= bit; }
#define IRQ_VBLANK 0x0001
#define IRQ_CDROM  0x0004

/* --- serving sectors ----------------------------------------------------
 *
 * The metadata -- volume descriptor, path table, directory -- comes from the
 * disc image; the file data from the extracted files, each at the sector
 * declared for it in the directory. The game sees no difference: it asks for
 * a sector, it gets the bytes that are there.
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
    /* The disc image stays open. Opening and closing it for every sector
       costs little on a local disk and a lot across a mount, which is the
       usual case under WSL. */
    static FILE *image;
    for (i = 0; i < 2048; i++) out[i] = 0;
    if (lba < CD_META_SECTORS) {
        /* An image that fails to open used to return sectors of zeros, and
           the game announced "File not found" -- an exact complaint about a
           false fact, which sends you looking for the defect at the other end
           of the chain. So we say it once, here, where we still know what we
           are talking about. */
        static int announced;
        if (!image) {
            image = fopen(CD_META, "rb");
            if (!image && !announced) {
                announced = 1;
                fprintf(stderr, "disc not found: %s\n"
                                "  the game will find none of its files\n",
                        CD_META);
            }
        }
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

/* --- DMA channel 2: the ordering table ----------------------------------
 *
 * The game almost never talks to the GPU directly: it builds a linked list
 * in RAM and asks the DMA to walk it. Walking that list here is seeing
 * exactly what a frame contains. */
static u32 dma2_madr, dma2_bcr, dma2_chcr;
static u32 dma3_madr, dma3_bcr, dma3_chcr;
static u32 dma6_madr, dma6_bcr, dma6_chcr;
static u32 dma4_madr, dma4_bcr, dma4_chcr;
static u32 dicr = 0;

/* The end of a transfer raises an interrupt, if the channel asked for it.
 *
 * The game does not watch the register: it opens an event and falls asleep
 * on it. Without the interrupt the event never arrives and the wait is
 * eternal -- that is exactly where the sound was blocking, once its
 * initialisation had succeeded. The control register carries the enables in
 * its bits 16 to 22 and the flags in bits 24 to 30; bit 31 sums it all up,
 * and it is the one that triggers. */
static void dma_complete(int channel)
{
    if (!(dicr & (1u << (16 + channel)))) return;
    dicr |= 1u << (24 + channel);
    if (dicr & (1u << 23)) {
        dicr |= 0x80000000u;
        irq_raise(0x0008);            /* the "DMA" source */
    }
}
unsigned long dma4_done;
void spu_write16(u32, u16);
u16 spu_read16(u32);
void spu_dma(const u8 *, u32, u32);
void spu_mix(s16 *, int);
int spu_active(void);
unsigned long otc_runs;
unsigned long dma3_done;
unsigned long ot_lists, ot_nodes, ot_broken, dma2_blocks;
u32 g_ot_node, g_ot_n;

unsigned long g_instr_per_frame = 376000;
int g_draw_cost = 1;
int g_capture;
int mod_mute_music, mod_mute_spu, mod_show_state;
extern unsigned long long g_pixels, g_cycles, g_deadline;
void psx_tick(void);
static unsigned long long pixels_seen;
unsigned long states_seen[64], states_outside;

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
        /* Each node carries a complete packet, its length is in the header.
           Starting again from zero at each node bounds the damage of a badly
           read length: it can no longer swallow the whole list. */
        for (i = 0; i < n; i++) {
            u32 w;
            __builtin_memcpy(&w, RAM + ((addr + 4 + i * 4) & 0x1FFFFC), 4);
            gp0_write(w);
        }
        if ((header & 0xFFFFFF) == 0xFFFFFF) break;
        /* A null link is not an end of list: it is an entry that was never
           initialised. Following it led to address zero, then to spinning
           until the guard -- two million nodes for nothing. */
        if ((header & 0xFFFFFF) == 0) { ot_broken++; break; }
        addr = (header & 0x1FFFFC);
    }
    /* Charging for the drawing.
     *
     * The processor was not alone in consuming time: the GPU filled about one
     * pixel per cycle at 53.2 MHz, some 887,000 pixels between two vertical
     * blanks. A scene that asks for more does not fit in one frame, and the
     * console then dropped to thirty per second -- not by decision, but by
     * overrun. That is the slowness we recover here, by converting the pixels
     * written into the same currency as the instructions.
     *
     * Without this accounting, a loaded scene costs us the same time as an
     * empty one, and the game runs too fast exactly where it used to slow
     * down.
     */
    if (g_draw_cost) {
        unsigned long long p = g_pixels - pixels_seen;
        pixels_seen = g_pixels;
        g_cycles += p * (unsigned long long)g_instr_per_frame / 887000ull;
        if (g_cycles >= g_deadline && !in_irq_flag) psx_tick();
    }
    dma2_chcr &= ~0x01000000u;
    /* The pad is read once per frame, as on the console -- and that is also
       what gives the script a stable unit: the number of frames drawn does
       not depend on the time base, whereas the video beats change as soon as
       you adjust it. */
    { void pad_write(unsigned long); pad_write(ot_lists); }
    /* Which part of the game is running.
     *
     * The game dispatches on a forty-entry table at 0x80070EA4, whose index
     * lives at 0x801D34F8. Reading it every frame turns "it feels like it
     * works" into a measurement: here are the states we went through, here
     * are the ones we never reached. It is the only honest way to say what
     * we have actually exercised. */
    {
        u32 e;
        __builtin_memcpy(&e, RAM + 0x1D34F8, 4);
        if (e < 64) states_seen[e]++;
        else states_outside++;
    }
    /* One list walked = one frame drawn. We keep a few of them, spaced out,
       rather than all: what we want to see is the progression. */
    {
        static unsigned long n;
        /* Writing a 230 KB frame to disk every hundred tables is enough to
           make the game stutter -- and since the count stops at a hundred and
           twenty, the stutter stops too, after about one lap of the circuit.
           A defect that heals by itself is the hardest to attribute: you
           think you are watching the game get going.

           So when there is a window, we only capture if we asked for it. */
        if (!g_capture) return;
        if (++n % 100 == 0 && n / 100 <= 120) {
            char p[256];
            const char *d = getenv("IMAGES");
            sprintf(p, "%s/f%03lu.ppm", d ? d : ".", n / 100);
            gpu_write_ppm(p);
        }
    }
}

/* --- the CD drive --------------------------------------------------------
 *
 * The game's driver writes a command at 0x1F801801, then waits in a loop for
 * bit 5 of the status register to announce a response. Without a response it
 * loops -- 33 million reads in ten seconds, then "CdlReset: timeout".
 *
 * What is implemented here is the strict minimum for that dialogue to
 * succeed: the index, the two parameter and response queues, the interrupt
 * flags, and the commands that startup uses. The data is not served yet;
 * that is the next step.
 */
static u8 cd_index;              /* the registers change meaning according to it */
static u8 cd_param[16], cd_nparam;
static u8 cd_resp[16], cd_nresp, cd_rpos;
static u8 cd_irq;                /* pending interrupt flag */
static u8 cd_ie;                 /* mask */
static u8 cd_stat = 0x02;        /* 0x02: motor spinning */
unsigned long cd_cmds[256];
static u8 cd_pending_cmd;
/* Most commands answer TWICE: an immediate acknowledgement (INT3), then a
   completion (INT2) when the mechanism has finished moving. The driver counts
   the two separately -- its Acknowledge and Complete counters -- and does not
   move on until it has had the second. */
static u8 cd_second;
static u8 cd_id_pending;
static u8 cd_pend;           /* second response awaiting its deadline */
static int cd_delay;
static u32 cd_lba;           /* current position, in sectors */
static int cd_reading;
static u8 cd_sector[2048];
static int cd_sector_ready;

static u32 bcd(u8 v) { return (v >> 4) * 10 + (v & 15); }
static u8 to_bcd(u32 v) { return (u8)(((v / 10) % 10) * 16 + v % 10); }

/* --- the music -----------------------------------------------------------
 *
 * The audio tracks are raw 2352-byte sectors, that is exactly 588 sixteen-bit
 * stereo frames at 44,100 Hz: no conversion, no resampling, we read and we
 * push. It is the sound card that sets the pace -- as long as its queue is
 * full enough, we read nothing.
 */
extern int g_verbose;
struct cdtrack { unsigned int start, length, skip; const char *file; };
extern const struct cdtrack CDTRACKS[];
extern const int NCDTRACKS;
int audio_init(void);
void audio_push(const void *, int);
unsigned audio_queued(void);
void audio_flush(void);

static int cd_playing, cd_track = 1, cd_audio_avail;
int cd_audio_enable(int on)
{
    cd_audio_avail = on && audio_init();
    if (cd_audio_avail) printf("sound: audio tracks from the disc\n");
    return cd_audio_avail;
}
static FILE *cd_audio_f;
static u32 cd_audio_sector;       /* position within the track file */
static u32 cd_audio_left;
unsigned long cd_audio_sectors;
unsigned long audio_dry;
static int audio_started;
/* Forty milliseconds: two frames at sixty per second. */
unsigned g_latency_bytes = 44100u * 4u * 40u / 1000u;

static void cd_audio_open(int track)
{
    const struct cdtrack *t;
    u32 start;
    if (cd_audio_f) { fclose(cd_audio_f); cd_audio_f = 0; }
    if (track >= 1 && track <= NCDTRACKS) {
        t = &CDTRACKS[track - 1];
        start = t->skip;                  /* the track's declared start */
    } else {
        /* No number: it is the position set by Setloc that commands. */
        int i;
        for (i = 0; i < NCDTRACKS; i++) {
            u32 base = CDTRACKS[i].start - CDTRACKS[i].skip;
            if (cd_lba >= base && cd_lba < base + CDTRACKS[i].length) {
                cd_track = i + 1;
                t = &CDTRACKS[i];
                start = cd_lba - base;
                goto found;
            }
        }
        return;
    }
found:
    if (g_verbose) { printf("  sound: track %d, from sector %u\n", cd_track, start); fflush(stdout); }
    cd_audio_f = fopen(t->file, "rb");
    if (!cd_audio_f) {
        static int announced;
        if (!announced) {
            announced = 1;
            fprintf(stderr, "audio track not found: %s\n", t->file);
        }
        return;
    }
    cd_audio_sector = start;
    cd_audio_left = (t->length > start) ? t->length - start : 0;
    fseek(cd_audio_f, (long)start * 2352, SEEK_SET);
    audio_flush();
}

/* The mixing, called regularly: we fill the sound card's queue up to the
   chosen latency.
 *
 * That lead is a compromise, and it is audible on both sides. Too short, the
 * sound card runs dry and you hear gaps. Too long, everything already in the
 * queue was computed BEFORE the event that has just happened -- the sound of
 * the impact starts after the impact, by as much time as there is lead. It
 * was a quarter of a second; it is now forty milliseconds, and the counter of
 * times the queue ran empty says whether we have gone too far.
 *
 * This setting would not matter on continuous sound such as music: it only
 * matters for triggered sounds, where the ear compares with the picture.
 *
 * Two sources meet here -- the disc tracks and the twenty-four voices of the
 * SPU -- and they do have to meet somewhere. Pushing them separately would
 * amount to asking the sound card for two outputs, or letting one erase the
 * other. So we add them up, with saturation: that is what the hardware did
 * anyway, the drive's output passing through the same mixer as the voices.
 *
 * The unit is the sector, that is 588 frames: it is the grain of the disc,
 * and it falls right on the output frequency. */
static void cd_audio_feed(void)
{
    static u8 sector[2352];
    static s16 voices[588 * 2];
    if (!cd_audio_avail) return;
    while (audio_queued() < g_latency_bytes) {
        /* We only count the emptiness once the output has started: before the
           first fill, the queue is empty by construction and not by
           accident. */
        if (audio_started && audio_queued() == 0) audio_dry++;
        audio_started = 1;
        s16 *cd = (s16 *)sector;
        int i, got = 0;
        if (cd_playing && cd_audio_f && cd_audio_left) {
            if (fread(sector, 1, 2352, cd_audio_f) == 2352) {
                got = 1; cd_audio_sector++; cd_audio_left--; cd_audio_sectors++;
            } else {
                cd_audio_left = 0;
            }
        }
        if (!got) memset(sector, 0, sizeof sector);
        spu_mix(voices, 588);
        if (mod_mute_spu) memset(voices, 0, sizeof voices);
        if (mod_mute_music) memset(sector, 0, sizeof sector);
        for (i = 0; i < 588 * 2; i++) {
            int sum = (int)cd[i] + (int)voices[i];
            if (sum > 32767) sum = 32767;
            if (sum < -32768) sum = -32768;
            cd[i] = (s16)sum;
        }
        audio_push(sector, 2352);
        /* With neither music nor voices, no point filling the queue for ever:
           we stop as soon as there is enough to hold out, otherwise we would
           spin here. */
        if (!got && !spu_active()) break;
    }
}

void cd_event(u32 spec);

static void cd_reply(u8 irq, const u8 *b, int n)
{
    int i;
    cd_nresp = 0; cd_rpos = 0;
    for (i = 0; i < n && i < 16; i++) cd_resp[cd_nresp++] = b[i];
    cd_irq = irq;
    /* The controller has answered: raise the interrupt source. It is the
       game's handler that will decide what to do with it -- our job stops at
       setting the flag, like the hardware. */
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
        /* The parameters are in minutes, seconds and frames, in binary-coded
           decimal, and the origin is two seconds from the start. */
        if (cd_nparam >= 3)
            cd_lba = (bcd(cd_param[0]) * 60 + bcd(cd_param[1])) * 75
                     + bcd(cd_param[2]) - 150;
        cd_reply(3, one, 1);
        break;
    case 0x06: case 0x1B:                                  /* ReadN, ReadS */
        cd_reading = 1;
        cd_reply(3, one, 1);
        cd_second = 1;      /* INT1: a sector is ready */
        break;
    case 0x0A: cd_stat = 0x02; cd_reply(3, one, 1); cd_second = 2; break; /* Init  */
    /* The commands that make the mechanism move answer twice: an immediate
       acknowledgement, then a completion. Omitting a single one is enough to
       block the driver -- it waits for the completion and ends up declaring a
       timeout. That is what was happening to SetSession, right after the data
       was loaded, at the moment when the game moves to the audio track. */
    case 0x12: cd_reply(3, one, 1); cd_second = 2; break;  /* SetSession */
    case 0x08: cd_reading = 0; cd_playing = 0; cd_reply(3, one, 1); cd_second = 2; break; /* Stop */
    case 0x07: cd_reply(3, one, 1); cd_second = 2; break;  /* MotorOn */
    case 0x0B: cd_reply(3, one, 1); break;                 /* Mute */
    case 0x03:                                             /* Play  */
        /* With no parameter we resume where we were; with one, we jump to the
           requested track. The game uses both. */
        if (cd_nparam >= 1) cd_track = (int)bcd(cd_param[0]);
        cd_audio_open(cd_track);
        cd_playing = 1;
        cd_reply(3, one, 1);
        break;
    case 0x1A: {                                           /* GetID */
        /* A data disc, licensed, region free. */
        static const u8 id[8] = { 0x02, 0x00, 0x20, 0x00, 'S', 'C', 'E', 'A' };
        cd_reply(3, one, 1);
        cd_id_pending = 1;
        cd_second = 2;
        (void)id;
        break;
    }
    case 0x13: {                                           /* GetTN */
        u8 r[3];
        r[0] = cd_stat; r[1] = to_bcd(1);
        r[2] = to_bcd(NCDTRACKS ? NCDTRACKS : 1);
        cd_reply(3, r, 3); break;
    }
    case 0x14: {                                           /* GetTD */
        /* The start position of a track, in minutes and seconds. The disc's
           zero is two seconds from the start of the signal: it is the same
           origin as for Setloc, and forgetting it shifts all the music. */
        int n = cd_nparam ? (int)bcd(cd_param[0]) : 1;
        u32 lba = 0;
        u8 r[3];
        if (n >= 1 && n <= NCDTRACKS) lba = CDTRACKS[n - 1].start;
        else if (n == 0 && NCDTRACKS)   /* track 0: the end of the disc */
            lba = CDTRACKS[NCDTRACKS - 1].start + CDTRACKS[NCDTRACKS - 1].length;
        lba += 150;
        r[0] = cd_stat;
        r[1] = to_bcd((lba / 75) / 60);
        r[2] = to_bcd((lba / 75) % 60);
        cd_reply(3, r, 3); break;
    }
    case 0x09: cd_reading = 0; cd_playing = 0; cd_reply(3, one, 1); cd_second = 2; break;  /* Pause */
    case 0x15: case 0x16:                                  /* SeekL, SeekP */
        cd_audio_open(0);   /* the position comes from the last Setloc */
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

/* The dialogue with the drive, in order. The counters say that it stops; the
   sequence says where. */
extern int g_verbose;
static int cdlog;
static void cdtrace(const char *what, u32 a, u32 b)
{
    if (g_verbose && cdlog++ < 200) { printf("  cd: %-12s %02X %02X\n", what, a, b); fflush(stdout); }
}

static u32 cd_read(u32 p)
{
    switch (p & 3) {
    case 0: {
        u32 st = cd_index & 3;
        st |= 0x18;                          /* parameter queue ready and empty */
        if (cd_nresp > cd_rpos) st |= 0x20;  /* a response is waiting */
        return st;
    }
    case 1: {
        u32 r = (cd_rpos < cd_nresp) ? cd_resp[cd_rpos++] : 0;
        cdtrace("read reply", r, cd_rpos);
        return r;
    }
    case 2: return 0;
    case 3: {
        u32 r = (cd_index & 1) ? (0xE0 | cd_irq) : (0xE0 | cd_ie);
        cdtrace(cd_index & 1 ? "read flags" : "read mask", r, cd_index);
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
        if (cd_index == 0) { cdtrace("COMMAND", b, cd_nparam); cd_command(b); }
        else cdtrace("write 1801", b, cd_index);
        break;
    case 2:
        if (cd_index == 0) { cdtrace("parameter", b, cd_nparam); if (cd_nparam < 16) cd_param[cd_nparam++] = b; }
        else if (cd_index == 1) { cdtrace("arm", b, 0); cd_ie = b; }
        break;
    case 3:
        cdtrace("write 1803", b, cd_index);
        /* Index 1: writing here acknowledges the interrupt. That is what the
           driver does after reading its response, and without it it asks for
           nothing more. */
        if (cd_index == 1) {
            cdtrace("ack", b, cd_second);
            if (b & 0x07) {
                cd_irq = 0;
                istat &= ~IRQ_CDROM;
                /* The second response does not follow the acknowledgement by
                   one cycle: the mechanism takes milliseconds to move, and the
                   driver loops as long as a flag stays raised. Answering on
                   the spot locked it into that loop -- six million sectors
                   served without it ever getting out. So we defer, and we
                   count the time on the game's waiting loop, never on the
                   accesses of the handler itself. */
                if (cd_second) { cd_pend = cd_second; cd_delay = 1; cd_second = 0; }
            }
        }
        break;
    }
}

/* The drive's heartbeat. Called from the game's waiting loop, and from there
   only: that is what guarantees the interrupt handler can finish before the
   next response arrives. */
void cd_dump_state(void)
{
    printf("drive state: irq=%u pend=%u delay=%d reading=%d second=%u nresp=%u rpos=%u ie=%02X index=%u istat=%04X imask=%04X\n",
           cd_irq, cd_pend, cd_delay, cd_reading, cd_second, cd_nresp, cd_rpos, cd_ie, cd_index, istat, imask);
}

void cd_tick(void)
{
    cd_audio_feed();
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
        if (nxt == 1) {                      /* a sector is available */
            cd_fetch(cd_lba, cd_sector);
            cd_sector_ready = 1;
        }
        cd_reply(nxt, &st, 1);
        if (cd_reading && nxt == 1) { cd_pend = 1; cd_delay = 1; }
    }
}

/* The BIOS, on a drive interrupt, picks up the response and acknowledges in
   the game's place. We expose here what it takes to do that. */
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

/* --- registers ---------------------------------------------------------- */
unsigned long hw_writes, hw_reads;

/* A histogram of the addresses touched. The CD driver goes through a global
   pointer, therefore invisible to disassembly; the empirical reading says at
   once which hardware the game needs, and in what proportion. */
#define HWN 256
u32 hw_addr[HWN]; unsigned long hw_rcnt[HWN], hw_wcnt[HWN]; int hw_naddr;
/* The interrupt handler and the main loop touch the same hardware for
   opposite reasons. Counting them separately says what the handler is looking
   for -- and therefore what it is missing. */
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

/* Half-word reads. The registers that exist only in sixteen bits are served
   as they are; the others go through the word read and take whichever half
   fits. */
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
    /* Deliver here, and not only on GPU status: the drive's waiting loop
       reads only its own register. Pacing time on the GPU amounted to
       stopping the clock during precisely the moment when the game is waiting
       for an interrupt. */
    if ((istat & imask) && !in_irq_flag) deliver_irq();
    switch (p) {
    case 0x1F801810: return 0;             /* GPUREAD */
    case 0x1F801814:
        /* The game reads this register millions of times: it is its waiting
           loop, therefore the best place to make time beat. Every thousand
           reads, we deliver it an interrupt. */
        /* The vertical blank, about sixty times per second on the console.
           Here we pace it on GPU status reads, for want of a clock: what
           matters is that it arrives regularly. */
        
        /* GPUSTAT. The bits that matter for the game to move on: ready to
           receive a command, ready for a DMA, and the frame bit that
           toggles -- without it, any wait for sync spins for ever. */
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
        /* The hardware raises its interrupt almost immediately after the
           command. The driver's waiting loop is shorter than any coarse
           clock: it has to be delivered here, on the spot. */
        if ((istat & imask) && !in_irq_flag) deliver_irq();
        break;
    case 0x1F801810: gp0_write(v); break;
    case 0x1F801814: gpu_gp1(v); break;
    case 0x1F801070: istat &= v; break;    /* acknowledgement: the zeros clear */
    case 0x1F801074: {
        /* Which mask does the game arm? The answer says which sources it
           expects, and therefore which ones have to be raised. */
        static u32 last; static int shown;
        if (v != last && shown < 8) {
            printf("[I_MASK = %04X : ", v);
            if (v & 1) printf("vblank ");
            if (v & 2) printf("gpu ");
            if (v & 4) printf("cdrom ");
            if (v & 8) printf("dma ");
            if (v & 0x10) printf("timer0 ");
            if (v & 0x70) printf("timers ");
            if (v & 0x80) printf("card ");
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
            /* The drive fills memory: one sector, then we move on. */
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
    /* Channel 6: the ordering table clearer. It writes into RAM a linked list
       running backwards -- each entry points to the previous one, the last
       carries the end marker. Without it, the table stays at zero and channel
       2 follows a null link: it spins in the void and the GPU receives words
       that are nothing. */
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
        /* The flags are acknowledged by writing a one: so we clear them where
           the write sets them, and keep the rest as it is. */
        dicr = (dicr & ~0x00FF803Fu & ~(v & 0x7F000000u)) | (v & 0x00FF803Fu);
        if (!(dicr & 0x7F000000u)) dicr &= ~0x80000000u;
        break;
    case 0x1F8010C0: dma4_madr = v; break;
    case 0x1F8010C4: dma4_bcr = v; break;
    case 0x1F8010C8:
        /* Channel 4: main memory feeds the SPU. Without it, the voices would
           read half a megabyte of zeros -- which is very audible indeed,
           since it cannot be heard at all. */
        dma4_chcr = v;
        if (v & 0x01000000u) {
            u32 words = (dma4_bcr & 0xFFFF) * ((dma4_bcr >> 16) & 0xFFFF);
            if (!words) words = (dma4_bcr & 0xFFFF);
            if (v & 1) spu_dma(RAM, dma4_madr & 0x1FFFFC, words * 4);
            dma4_chcr &= ~0x01000000u;
            dma4_done++;
            dma_complete(4);
        }
        break;
    case 0x1F8010A0: dma2_madr = v; break;
    case 0x1F8010A4: dma2_bcr = v; break;
    case 0x1F8010A8:
        dma2_chcr = v;
        if (v & 0x01000000u) {
            /* Three modes, and not only the linked list.
               LoadImage sends the header by hand then pushes the pixels by
               block: treating that block as a list made the channel follow a
               link taken from the texture itself -- hence a 1024 by 256
               transfer to an absurd address, which smeared the whole video
               memory. */
            u32 sync = (v >> 9) & 3;
            int to_gpu = (int)(v & 1);     /* 1: memory feeds the GPU */
            if (sync == 2) dma2_run();
            else {
                u32 words = (sync == 1)
                    ? (dma2_bcr & 0xFFFF) * ((dma2_bcr >> 16) & 0xFFFF)
                    : (dma2_bcr & 0xFFFF);
                u32 a = dma2_madr & 0x1FFFFC, i;
                if (!words) words = 0x10000;
                for (i = 0; i < words; i++) {
                    u32 w;
                    if (!to_gpu) {          /* the GPU feeds memory */
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

/* The functions the translator refuses (COP0) are replaced by a stub. We
   count the hits: a stub often reached is a lead, a stub never reached costs
   nothing. */
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
    printf("stubs reached:\n");
    for (i = 0; i < stub_n; i++)
        printf("   %-20s %lu times\n", stub_names[i], stub_counts[i]);
}

unsigned long long g_cycles, g_deadline;
void psx_tick(void)
{
    g_deadline = g_cycles + g_instr_per_frame;
    psx_clock();
}

void psx_clock(void)
{
    void cd_tick(void);
    int video_closed(void);
    extern int g_video;
    /* Closing the window stops the game, and the report prints as if the
       allotted time had run out -- a wanted exit is worth as much as an
       endured one. */
    if (g_video && video_closed()) { void report(int); report(1); _exit(0); }
    cd_tick();
    /* The vertical blank. It used to be paced on GPU status reads -- but the
       VSync wait reads only I_STAT, never the GPU: the clock stopped exactly
       while we were watching it. So it beats here, on the same base as
       everything else. */
    g_vblanks++;
    irq_raise(IRQ_VBLANK);
    if ((istat & imask) && !in_irq_flag) deliver_irq();
}

/* The system coprocessor, reduced to its registers. The game touches it only
   to arm the GTE in the status register and for its critical sections. */
u32 COP0[32];
u32 psx_syscall(u32 a0, u32 a1, u32 a2, u32 a3)
{
    (void)a1; (void)a2; (void)a3;
    /* 1: enter a critical section, 2: leave it. Without a scheduler, there is
       nothing more to do than to note it. */
    (void)a0;
    return 0;
}
