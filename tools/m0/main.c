/* M0: load the image, start from the entry point, see what comes out.
 *
 * The milestone does not claim to display. It claims to establish that the
 * game's loop really runs -- and the proof expected is a coherent stream of
 * GPU packets: recognisable commands, in plausible numbers, grouped into
 * ordering tables. A black window would prove less.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "rt.h"
#include "gte.h"

extern const struct { u32 a; u32 (*f)(u32, u32, u32, u32); } PSX_FUNCS[];
extern const int PSX_NFUNCS;
extern unsigned long gp0_words, gp1_cmds, prim_count, prim_hist[256];
extern unsigned long ot_lists, ot_nodes, hw_writes, hw_reads;
extern FILE *gpulog;

static u32 ENTRY;   /* read from the executable's header */

static unsigned long bios_calls[3][256];

u32 psx_dispatch(u32, u32, u32, u32, u32, u32);

/* The game's exception handler, installed by B0(19) HookEntryInt.
 *
 * The CD driver does not poll the hardware: it counts callbacks. With no
 * interrupt delivered, its NoIntr, DataReady and Complete counters stay at
 * zero and it concludes there is a timeout -- which is what it would do on a
 * console whose drive did not answer. Delivering its interrupts to it is
 * giving it back the missing half of the dialogue. */
u32 g_irq_handler;
unsigned long irq_delivered;
static int in_irq;
int in_irq_flag;
int g_longjmp;          /* makes setjmp return 1, for one interrupt */

/* The game does not install a function: it saves a context.
 *
 *     setjmp(&contexte);
 *     if (v0 == 0) { HookEntryInt(&contexte); return; }
 *     ... body of the handler ...
 *
 * On the console, the BIOS comes back into this context by longjmp at every
 * interrupt, and execution resumes just after the setjmp, with v0 non-zero.
 * A function-by-function translation cannot jump into the middle of a dead
 * frame -- but it can call the function again while making the setjmp return
 * 1, which takes exactly the same branch. */
/* Calling func_800492B0 again from the beginning replayed its whole prologue
 * at every interrupt: it rearms the mask, zeroes two tables and calls
 * func_800495DC again. In other words, every interrupt erased the state the
 * driver had just established -- which explains why no sequence ever got
 * through.
 *
 * The body of the handler starts at 0x8004934C, just after the test that
 * follows the setjmp. Translated as a function in its own right, it runs
 * without touching the prologue. That is the right way to render a longjmp in
 * a function-by-function translation: do not replay, enter at the right
 * place. */
u32 psx_irq_body(u32, u32, u32, u32);

/* The BIOS CD service.
 *
 * The game's dispatcher only handles the interrupts whose callback it has
 * registered, and it registers none for the drive: it counts on the BIOS to
 * read the response, acknowledge, and call the synchronisation function it
 * set through CdSyncCallback.
 *
 * So that is the service to render -- not emulate a BIOS image, but rewrite
 * the fifteen or so functions this game calls. This one is among them, and it
 * is the link that was missing. */
#define CD_RESULT 0x801FFE00u
u32 cd_take_response(u8 *buf);   /* returns the interrupt type, fills buf */

static void bios_cd_service(void)
{
    u8 buf[16];
    u32 intr, cb, i;
    intr = cd_take_response(buf);
    if (!intr) return;
    for (i = 0; i < 16; i++) SB(CD_RESULT + i, buf[i]);
    cb = LW(0x801E9170u);            /* set by CdSyncCallback */
    if (cb) psx_dispatch(cb, intr, CD_RESULT, 0, 0, 0);
}

void deliver_irq(void)
{
    if (in_irq) return;
    in_irq = 1;
    in_irq_flag = 1;
    irq_delivered++;
    /* Do NOT pick up the response here: the game has registered its own
       handler for interrupt 2, in D_800797A8[2], and the dispatcher calls it.
       My BIOS service was stealing the interrupt from it -- it cleared the
       flag and the response before the game's handler could read them.
       Rendering a service nobody asked for is a discreet way of breaking a
       chain that worked. */
    /* The interrupt borrows the stack of the interrupted code. On the console
       the exception handler works on its own stack and gives the context back
       intact; here, the slightest asymmetry between the translated prologues
       and epilogues makes $sp drift from one interrupt to the next. It was
       climbing: after a few interrupts, the buffers allocated on the stack
       fell beyond the two megabytes and the writes were silently thrown
       away -- the game then read a null disc position and concluded "File not
       found". So we give the stack back as we took it, which the hardware
       guarantees and the translation does not. */
    {
        u32 sp_saved = g_sp;
        psx_irq_body(0, 0, 0, 0);
        g_sp = sp_saved;
    }
    in_irq_flag = 0;
    in_irq = 0;
}
int g_seconds = 20;

/* The detailed log -- BIOS calls and dialogue with the drive -- is a
 * debugging tool, not an output. It served to find where startup was
 * stopping; now that it no longer stops, it only hides what the game itself
 * prints. So it has to be asked for: VERBOSE=1. */
int g_verbose;
int g_video;
u32 g_pad_buf[2];
int g_pad_on;
u32 g_pad_buttons = 0xFFFF;   /* active low: nothing pressed */

/* Which kind of pad to announce. The game knows two, and its read function
   branches on the type byte: 0x41 for the digital one, 0x23 for Namco's
   neGcon. The second gives the analogue steering and pedals that already
   exist in the 1994 game -- it was designed with that pad.
   We announce it as soon as a real pad is plugged in. */
int mod_negcon = 1;

/* What we actually handed to the game, kept in order to display it.
 *
 * A pad that does nothing asks two questions at once: does SDL read it, and
 * does the game listen? As long as all we have is "nothing moves", both stay
 * open. A sixteen-bit word on the screen separates them: if it changes when
 * you press, SDL reads and it is the game that ignores; if it does not
 * change, no point looking on the game's side. PAD_DEBUG=1 displays it. */
int mod_show_pad;
u32 g_pad_word = 0xFFFF;
unsigned char g_pad_analog[4] = {0x80, 0, 0, 0};
int g_pad_type = 0x41;

/* The script. A list of "instant:keys", the instant counted in vertical
   blank beats. Written rather than interactive, so that two runs give the
   same picture. */
static struct { unsigned long when; u32 mask; } script[16];
static int nscript;

void pad_write(unsigned long tick)
{
    int i;
    u32 m = 0xFFFF;
    u32 video_pad(void);
    if (!g_pad_on) return;
    for (i = 0; i < nscript; i++)
        if (tick >= script[i].when) m = script[i].mask;
    /* The keyboard takes precedence over the script as soon as a key is
       pressed: one can thus start a game with a script and take over along
       the way, which is handy for quickly reaching a place in the game one
       wants to try. */
    if (g_video) {
        u32 live = video_pad();
        if (live != 0xFFFF) m = live;
    }
    g_pad_buttons = m;
    {
        int video_negcon(unsigned char *);
        unsigned char analog[4];
        int neg = g_video && mod_negcon && video_negcon(analog);
        g_pad_word = m;
        g_pad_type = neg ? 0x23 : 0x41;
        if (neg) __builtin_memcpy(g_pad_analog, analog, 4);
        /* The same state to the log, and only when it changes: text five
           pixels high in a 320 by 240 image reads badly, and one line per
           frame would drown its meaning. */
        if (mod_show_pad) {
            static u32 seen_word = 0; static unsigned char seen_analog[4];
            if (seen_word != m || __builtin_memcmp(seen_analog, g_pad_analog, 4)) {
                seen_word = m; __builtin_memcpy(seen_analog, g_pad_analog, 4);
                printf("pad: %04X  type %02X  twist %02X  I %02X  II %02X  L %02X\n",
                       (unsigned)(m & 0xFFFF), (unsigned)g_pad_type,
                       g_pad_analog[0], g_pad_analog[1], g_pad_analog[2], g_pad_analog[3]);
                fflush(stdout);
            }
        }
        for (i = 0; i < 2; i++) {
            u32 p = g_pad_buf[i] & 0x1FFFFF;
            if (!p) continue;
            RAM[p + 0] = (i == 0) ? 0x00 : 0xFF; /* only the first port exists */
            RAM[p + 1] = (i == 0 && neg) ? 0x23 : 0x41;
            RAM[p + 2] = (u8)(m >> 8);
            RAM[p + 3] = (u8)m;
            /* The buffer is sixteen bytes -- InitPAD2 says so -- so the four
               analogue bytes fit without spilling over into the second port,
               which starts eight bytes further on. */
            if (i == 0 && neg) {
                RAM[p + 4] = analog[0];
                RAM[p + 5] = analog[1];
                RAM[p + 6] = analog[2];
                RAM[p + 7] = analog[3];
            }
        }
    }
}

static u32 key(const char *name)
{
    if (!strcmp(name, "start"))    return 0x0800;
    if (!strcmp(name, "select"))   return 0x0100;
    if (!strcmp(name, "up"))       return 0x1000;
    if (!strcmp(name, "right"))    return 0x2000;
    if (!strcmp(name, "down"))     return 0x4000;
    if (!strcmp(name, "left"))     return 0x8000;
    if (!strcmp(name, "cross"))    return 0x0040;
    if (!strcmp(name, "circle"))   return 0x0020;
    if (!strcmp(name, "triangle")) return 0x0010;
    if (!strcmp(name, "square"))   return 0x0080;
    if (!strcmp(name, "l1"))       return 0x0004;
    if (!strcmp(name, "r1"))       return 0x0008;
    return 0;
}

/* "400:start 460: 900:cross" -- instant, colon, keys separated by commas. An
   instant with no key releases everything. The instant is counted in frames
   drawn. */
void script_read(const char *s)
{
    while (s && *s && nscript < 16) {
        char word[64]; int o = 0; u32 m = 0xFFFF;
        unsigned long when = 0;
        while (*s == ' ') s++;
        while (*s >= '0' && *s <= '9') when = when * 10 + (unsigned)(*s++ - '0');
        if (*s == ':') s++;
        while (*s && *s != ' ') {
            o = 0;
            while (*s && *s != ' ' && *s != ',') { if (o < 63) word[o++] = *s; s++; }
            word[o] = 0;
            if (o) m &= ~key(word);
            if (*s == ',') s++;
        }
        script[nscript].when = when;
        script[nscript].mask = m;
        nscript++;
    }
}
unsigned long dispatch_misses;
unsigned long cdcb_hits;   /* entries into the game's CD callback */

/* The BIOS calls. The game reaches them through trampolines that put the call
 * number in $t1 and jump to 0xA0, 0xB0 or 0xC0. We do not implement them
 * here: we count them. Knowing which ones the game asks for, and in what
 * order, says where it is in its startup. */
/* --- the BIOS event system -----------------------------------------------
 *
 * The CD driver does not wait for the hardware: it waits for an event. The
 * game opens one for class 0xF0000009, and the BIOS is supposed to deliver it
 * when the drive answers. Without that link, the command goes out, the
 * controller answers, and nobody knows about it -- hence the timeout.
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
            /* Mode 0x1000: immediate callback. Otherwise the event is simply
               marked and the game picks it up through TestEvent. */
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
    /* The sequence, not just the total: the order of the calls says where
       startup has got to far better than a histogram. */
    {
        static int seq;
        if (g_verbose && seq < 200 && !(vec == 0xA0 && (fn & 0xFF) == 0x3F)) {
            printf("[bios %c0(%02X) a0=%08X a1=%08X a2=%08X]\n",
                   "ABC"[v], fn & 0xFF, a0, a1, a2);
            fflush(stdout);
            seq++;
        }
    }
    /* A0(3F) is the kernel's printf. Implementing it costs ten lines and
       gives the game back its own voice: what it prints during its startup
       says exactly where it has got to, and no external metric would say it
       as well. */
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
    /* The BIOS string and memory functions.
     *
     * The game does not carry them: the library replaces them with
     * trampolines that jump to 0xA0 with the call number in $t1. Not
     * implementing them causes no error -- they return zero and copy nothing,
     * and the defect shows up very far from there: here, a silent strcpy
     * emptied the file path and the game concluded "File not found" after
     * having correctly read its disc. */
    /* The root counters. VSync does not count the frames itself: it asks the
       BIOS for the difference since its last call. Without an answer, the
       difference is always zero and the wait never ends. */
    if (vec == 0xB0 && (fn & 0xFF) >= 0x02 && (fn & 0xFF) <= 0x06) {
        extern unsigned long g_vblanks;
        if ((fn & 0xFF) == 0x03) {
            /* The game asks for the time in a loop: it is VSync waiting, and
               the processor would spin there doing nothing until the next
               vertical blank. Rather than simulate that wait instruction by
               instruction, we CHARGE for it -- we advance the clock to the
               deadline, which those cycles would have done anyway. The model
               does not change; only the time we take to run it changes.

               The difference with what we did before is total: we no longer
               fabricate a vertical blank out of nowhere, we observe that the
               cycles leading to the next one are spent. */
            extern unsigned long long g_cycles, g_deadline;
            void psx_tick(void);
            if (g_cycles < g_deadline) g_cycles = g_deadline;
            psx_tick();
            /* Asking for the time in a loop is the sign that there is nothing
               else to do. VSync waits here, and nothing in that wait makes a
               clock paced on memory accesses advance: the game burned three
               billion calls there for a hundred and eighty seconds. So we
               make time advance at every request -- it is the same idea as
               the emulators' idle-loop detection, in its simplest form: the
               code says itself that it is waiting. */
            return (u32)(g_vblanks & 0xFFFF);
        }
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
    /* The pad.
     *
     * The BIOS does not read it on demand: it fills a buffer that the game
     * consults when it wants. InitPAD gives the address of the two buffers,
     * StartPAD arms the filling. The format fits in four bytes -- a state, a
     * type, and sixteen buttons active low.
     *
     * Without it, the game stays on "PUSH START BUTTON" and shows only its
     * demonstration. With it, one can play it -- or, here, play it a script
     * written in advance, which makes the result reproducible. */
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
        /* setjmp. Returns 0 at installation, 1 when we replay the context. */
        return (u32)g_longjmp;
    }
    if (vec == 0xB0 && (fn & 0xFF) == 0x19) {
        /* HookEntryInt: the first word of the structure is the address of the
           handler. We keep it so as to be able to call it. */
        /* The game reinstalls its handler at every turn of the loop: saying
           so every time drowns everything else under thousands of identical
           lines. So we only report a change. */
        u32 before = g_irq_handler;
        g_irq_handler = LW(a0);
        if (g_irq_handler != before) {
            printf("[interrupt handler installed at %08X]\n", g_irq_handler);
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

/* A time base that does not depend on the hardware.
 *
 * The CD driver's waiting loop reads no register: it counts down turns while
 * watching a flag in memory that the handler sets. Delivering the interrupts
 * on hardware reads therefore never reaches it, and it expires without having
 * seen anything -- "CdlReset: timeout" prints before the response has even
 * been read.
 *
 * Function calls, on the other hand, arrive all the time. They make a coarse
 * but regular clock, and above all one independent of what the game watches. */
extern u32 g_istat_mirror, g_imask_mirror;
void deliver_irq(void);
static unsigned long tick;

u32 psx_dispatch(u32 addr, u32 a0, u32 a1, u32 a2, u32 a3, u32 t1)
{
    int lo = 0, hi = PSX_NFUNCS - 1;
    /* The same clock for both: the drive has to advance on the same time base
       as the delivery of the interrupts, otherwise its second response never
       arrives while the game is waiting in a memory loop. */
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

void report(int sig)
{
    int i, n = 0;
    if (sig) printf("\n--- interrupted after %d s ---\n", g_seconds);
    printf("GPU packets        : %lu commands, %lu words\n", prim_count, gp0_words);
    printf("ordering tables    : %lu walked, %lu nodes\n", ot_lists, ot_nodes);
    printf("registers          : %lu writes, %lu reads, %lu GP1\n",
           hw_writes, hw_reads, gp1_cmds);
    printf("indirect jumps with no target : %lu\n", dispatch_misses);
    printf("interrupts delivered          : %lu\n", irq_delivered);
    printf("events delivered              : %lu\n", ev_delivered);
    printf("game's CD callback called     : %lu times\n", cdcb_hits);
    {
        int k;
        printf("interrupt callback table (D_800797A8):\n");
        for (k = 0; k < 8; k++) {
            u32 h = LW(0x800797A8u + 4 * k);
            if (h) printf("   irq %d -> %08X%s\n", k, h, k == 2 ? "   <-- CD drive" : "");
        }
        printf("CD sync callback (D_801E9170): %08X\n", LW(0x801E9170u));
    }
    {
        extern unsigned long cd_sectors_served, cd_sectors_missing, dma3_done;
        printf("sectors served                : %lu (%lu not found), %lu DMA transfers\n",
               cd_sectors_served, cd_sectors_missing, dma3_done);
    }
    {   extern unsigned long g_vblanks;
        extern unsigned long long g_pixels, g_cycles;
        { extern unsigned long spu_voices_played, dma4_done;
          { extern int spu_peak;
            extern unsigned long spu_voices_off;
            printf("SPU                : %lu voices, %lu transfers, peak %d\n",
                   spu_voices_played, dma4_done, spu_peak);
            { extern unsigned long spu_sweeps, spu_vol_plain;
              printf("   volumes: %lu plain, %lu sweeps\n", spu_vol_plain, spu_sweeps); }
            if (spu_voices_off)
                printf("   of which %lu started while the SPU says off -- our model"
                       " of the status register is incomplete\n", spu_voices_off); } }
        { extern unsigned long cd_audio_sectors;
          extern unsigned long audio_dry;
          extern unsigned g_latency_bytes;
          printf("music              : %lu sectors, %.1f s\n",
                 cd_audio_sectors, cd_audio_sectors / 75.0);
          printf("sound              : %u ms of lead, %lu times run dry\n",
                 g_latency_bytes * 1000u / (44100u * 4u), audio_dry); }
        printf("vertical blanks    : %lu\n", g_vblanks);
        printf("instructions       : %llu\n", g_cycles);
        printf("pixels drawn       : %llu", g_pixels);
        if (ot_lists) printf("  (%llu per frame, the hardware held 887000)",
                             g_pixels / ot_lists);
        printf("\n");
    }
    {   /* Coverage: which states of the game ran, and how many frames each
           of them. A state never seen has never been exercised. */
        extern unsigned long states_seen[64], states_outside;
        int e, n = 0;
        printf("game states (table of 40 at 0x80070EA4):\n");
        for (e = 0; e < 40; e++) {
            u32 h;
            __builtin_memcpy(&h, RAM + 0x70EA4 + 4 * e, 4);
            if (states_seen[e]) {
                printf("   %2d  %08X  %8lu frames\n", e, h, states_seen[e]);
                n++;
            } else {
                printf("   %2d  %08X         -  never reached\n", e, h);
            }
        }
        if (states_outside) printf("   (%lu frames outside the table)\n", states_outside);
        printf("   %d states out of 40 exercised\n", n);
        /* A single script cannot visit everything: the demonstration shows
           what the menu does not show, and the other way round. By appending
           each run to a file, coverage accumulates instead of being recounted
           -- and what is left to reach can be read at a glance. */
        {   const char *c = getenv("COVERAGE");
            if (c) {
                FILE *f = fopen(c, "a");
                if (f) {
                    for (e = 0; e < 40; e++)
                        if (states_seen[e]) fprintf(f, "%d %lu\n", e, states_seen[e]);
                    fclose(f);
                }
            }
        }
    }
    printf("most frequent GP0 commands:\n");
    {   /* sort by frequency: show the twelve most common, not the twelve
           first -- numerical order says nothing. */
        int ord[256], a, b;
        for (a = 0; a < 256; a++) ord[a] = a;
        for (a = 0; a < 256; a++) for (b = a + 1; b < 256; b++)
            if (prim_hist[ord[b]] > prim_hist[ord[a]]) { int t = ord[a]; ord[a] = ord[b]; ord[b] = t; }
        for (a = 0; a < 256; a++) { i = ord[a];
        if (prim_hist[i] && n < 12) {
            const char *what =
                ((i & 0xE0) == 0x20) ? "polygon" :
                ((i & 0xE0) == 0x60) ? "rectangle" :
                ((i & 0xE0) == 0x40) ? "line" :
                (i == 0xE1) ? "draw mode" :
                (i == 0xE2) ? "texture window" :
                (i == 0xE3 || i == 0xE4) ? "drawing area" :
                (i == 0xE5) ? "drawing offset" :
                (i == 0xE6) ? "mask" :
                (i == 0x01) ? "flush cache" :
                (i == 0x02) ? "fill" : "?";
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
            printf("registers read by the interrupt handler:\n");
            for (j = 0; j < hw_irq_n; j++)
                printf("   %08X  %lu times\n", hw_irq_addr[j], hw_irq_cnt[j]);
            if (!hw_irq_n) printf("   none -- the handler does not touch the hardware\n");
        }
        printf("CD commands received:\n");
        for (k = 0; k < 256; k++)
            if (cd_cmds[k]) {
                const char *n =
                    k == 0x01 ? "Nop" : k == 0x02 ? "Setloc" : k == 0x06 ? "ReadN" :
                    k == 0x09 ? "Pause" : k == 0x0A ? "Init" : k == 0x0C ? "Demute" :
                    k == 0x0E ? "Setmode" : k == 0x15 ? "SeekL" : k == 0x19 ? "Test" :
                    k == 0x1B ? "ReadS" : "?";
                printf("   %02X %-8s %lu times\n", k, n, cd_cmds[k]);
            }
        printf("registers touched:\n");
        for (k = 0; k < hw_naddr; k++) {
            const char *w =
                (hw_addr[k] >= 0x1F801800 && hw_addr[k] <= 0x1F801803) ? "  <-- CD drive" :
                (hw_addr[k] >= 0x1F801810 && hw_addr[k] <= 0x1F801814) ? "  GPU" :
                (hw_addr[k] >= 0x1F8010A0 && hw_addr[k] <= 0x1F8010AC) ? "  DMA GPU" :
                (hw_addr[k] >= 0x1F8010B0 && hw_addr[k] <= 0x1F8010BC) ? "  DMA CD" :
                (hw_addr[k] == 0x1F801070 || hw_addr[k] == 0x1F801074) ? "  interrupts" :
                (hw_addr[k] >= 0x1F801100 && hw_addr[k] <= 0x1F801128) ? "  timers" :
                (hw_addr[k] >= 0x1F801C00) ? "  sound" : "";
            printf("   %08X  %10lu reads %8lu writes%s\n",
                   hw_addr[k], hw_rcnt[k], hw_wcnt[k], w);
        }
    }
    {
        int v, f, m = 0;
        printf("BIOS calls:\n");
        for (v = 0; v < 3; v++)
            for (f = 0; f < 256; f++)
                if (bios_calls[v][f] && m < 12) {
                    printf("   %c0(%02X)  %lu times\n", "ABC"[v], f, bios_calls[v][f]);
                    m++;
                }
        if (!m) printf("   none\n");
    }
    fflush(stdout);
    _exit(0);
}

#ifdef _WIN32
static DWORD WINAPI timer(LPVOID seconds)
{
    Sleep((DWORD)(size_t)seconds * 1000u);
    report(1);
    return 0;
}
#endif

int main(int argc, char **argv)
{
    /* The PlayStation executable carries its own header: the entry point, the
       load address and the size are written in it. Reading them avoids
       hard-coding three numbers that change from one game -- and from one
       region -- to the next, and makes this bench something other than a
       local rig. */
    const char *exe = getenv("PSX_EXE");
    unsigned char header[0x800];
    u32 load, size;
    FILE *f;
    int seconds = (argc > 1) ? atoi(argv[1]) : 20;
    if (argc > 2) exe = argv[2];
    if (!exe) exe = "PSX.EXE";
    g_seconds = seconds;
    f = fopen(exe, "rb");
    if (!f || fread(header, sizeof header, 1, f) != 1) {
        fprintf(stderr, "executable not found: %s\n"
                        "  usage: ./m0 [seconds] [path/PSX.EXE]\n"
                        "  or:    PSX_EXE=path/PSX.EXE ./m0 [seconds]\n", exe);
        return 1;
    }
    if (memcmp(header, "PS-X EXE", 8) != 0) {
        fprintf(stderr, "%s is not a PlayStation executable\n", exe);
        return 1;
    }
    __builtin_memcpy(&ENTRY, header + 0x10, 4);
    __builtin_memcpy(&load, header + 0x18, 4);
    __builtin_memcpy(&size, header + 0x1C, 4);
    if ((load & 0x1FFFFFFF) + size > 0x200000) {
        fprintf(stderr, "the image does not fit in memory\n");
        return 1;
    }
    if (fread(RAM + (load & 0x1FFFFFFF), size, 1, f) != 1) {
        fprintf(stderr, "truncated image\n");
        return 1;
    }
    fclose(f);
    { const char *j = getenv("GPU_LOG"); if (j) gpulog = fopen(j, "w"); }

    /* This game's header does not give a usable stack -- gp0 and s_addr are
       noise in it, which is no surprise for the console's very first title.
       So we take the BIOS's default stack. */
    g_sp = 0x801FFF00u;

    g_verbose = getenv("VERBOSE") ? 1 : 0;
    {   /* The lead of the audio queue, in milliseconds. Shorter, the sound
           sticks better to the picture; too short, it develops holes. */
        extern unsigned g_latency_bytes;
        const char *l = getenv("LATENCY");
        if (l) { unsigned ms = (unsigned)atoi(l); if (ms < 5) ms = 5; if (ms > 500) ms = 500;
                 g_latency_bytes = 44100u * 4u * ms / 1000u; }
    }
    {   /* Calibrating the clock: how many instructions the processor executed
           between two vertical blanks. It is set without recompiling, because
           it is a value one adjusts by watching the game run. */
        extern unsigned long g_instr_per_frame;
        const char *e = getenv("INSTR_PER_FRAME");
        if (e) g_instr_per_frame = strtoul(e, 0, 0);
        printf("clock: %lu instructions per vertical blank\n", g_instr_per_frame);
        { extern int g_draw_cost;
          if (getenv("NO_DRAW_COST")) g_draw_cost = 0; }
    }
    {   /* The window opens if SDL is there and we have not refused it.
           Without it, frames on disk and a script, as before. */
        int video_init(void);
        g_video = getenv("NO_WINDOW") ? 0 : video_init();
        /* With no window we capture as a matter of course: it is the only way
           to see. With a window, only if we asked for it through IMAGES. */
        { extern int g_capture; g_capture = (!g_video) || getenv("IMAGES") != 0; }
        if (getenv("PAD_DEBUG")) mod_show_pad = 1;
        /* A way to force the type without going through the menu: if the
           keyboard does not answer either, the menu is out of reach, and that
           is precisely the case where we need to compare the two. */
        if (getenv("PAD_DIGITAL")) mod_negcon = 0;
        {   /* The sound follows the window: without it, nobody is listening. */
            extern int cd_audio_enable(int);
            (void)cd_audio_enable(g_video && !getenv("NO_SOUND"));
        }
    }
    { void script_read(const char *); const char *s = getenv("PAD_SCRIPT"); if (s) script_read(s); }
    /* The time limit. On Unix it is an alarm, that is to say a signal;
       Windows has no equivalent, but a thread that sleeps and hands back
       control does exactly the same work -- and that, besides, is what an
       alarm is, seen from inside the system. */
#ifdef _WIN32
    if (seconds > 0)
        CreateThread(NULL, 0, timer, (LPVOID)(size_t)seconds, 0, NULL);
#else
    signal(SIGALRM, report);
    alarm(seconds);
#endif
    printf("%s: entry at %08X, %u bytes, %d functions in the table\n",
           exe, ENTRY, size, PSX_NFUNCS);
    fflush(stdout);
    psx_dispatch(ENTRY, 0, 0, 0, 0, 0);
    printf("--- the entry point has returned ---\n");
    report(0);
    return 0;
}
