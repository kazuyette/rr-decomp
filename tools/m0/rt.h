/* Memory and hardware access for the recompilation harness.
 *
 * The trap to avoid: masking every address to 21 bits would drop the GPU
 * registers, written at 0x1F801810, right into the middle of RAM. The three
 * spaces are therefore told apart here, once and for all, rather than in each
 * translated function.
 */
#ifndef RT_H
#define RT_H
#include <stdint.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32; typedef uint64_t u64;
typedef int8_t s8; typedef int16_t s16; typedef int32_t s32; typedef int64_t s64;

extern u8 RAM[0x200000];      /* 2 MB of main memory */
extern u8 SPAD[0x400];        /* the scratchpad, 1 KB of fast RAM in the CPU */
extern u32 g_sp;
extern u32 COP0[32];
u32 psx_syscall(u32, u32, u32, u32);

u32  hw_read32(u32 phys);
u32  hw_read16(u32 phys);
void hw_write32(u32 phys, u32 v, int width);

/* KUSEG, KSEG0 and KSEG1 designate the same physical memory: only the three
   high bits change. Masking them off first avoids having to know which segment
   the game is working in -- it uses both. */
#define PHYS(a) ((a) & 0x1FFFFFFF)

/* The time base: the instruction count.
 *
 * A static recompilation loses the machine's rhythm. The translated code runs
 * at the host's speed, and nothing ties an instruction to a cycle any more --
 * a clock must therefore be manufactured, and the choice decides everything.
 *
 * At first it beat on memory accesses, for want of anything better. That was a
 * convenient and false substitute: time then had to be advanced by hand
 * whenever the game waited without reading anything, and the scanout counter
 * no longer meant anything.
 *
 * It now counts what the machine counted: the instructions executed. The
 * translator bills them per straight-line block -- one addition per block, not
 * per instruction -- and the scanout falls due when a frame's budget is spent.
 * The VSync wait then burns cycles exactly as on the console, without our
 * having to prompt it.
 *
 * The budget: 33.8688 MHz divided by 59.94 frames gives 565,045 cycles. The
 * corresponding instruction count depends on the average number of cycles per
 * instruction, which uncached memory accesses push above one. This is a
 * calibration, not a measurement, and it can be adjusted without recompiling.
 */
extern unsigned long long g_cycles, g_deadline;
extern int in_irq_flag;
void psx_tick(void);
#define CYCLES(n) do { \
    g_cycles += (unsigned)(n); \
    if (g_cycles >= g_deadline && !in_irq_flag) psx_tick(); \
} while (0)

static inline u32 LW(u32 a)
{
    u32 p = PHYS(a);
    if (p < 0x200000) { u32 v; __builtin_memcpy(&v, RAM + p, 4); return v; }
    if (p >= 0x1F800000 && p < 0x1F800400) { u32 v; __builtin_memcpy(&v, SPAD + (p & 0x3FF), 4); return v; }
    if (p >= 0x1F801000) return hw_read32(p);
    return 0;
}
static inline u32 LH(u32 a)
{
    u32 p = PHYS(a);
    if (p < 0x200000) { u16 v; __builtin_memcpy(&v, RAM + p, 2); return v; }
    if (p >= 0x1F800000 && p < 0x1F800400) { u16 v; __builtin_memcpy(&v, SPAD + (p & 0x3FF), 2); return v; }
    /* A sixteen-bit read is not a thirty-two-bit read from which one takes a
       half. Many hardware registers are read by half-word and make no sense
       otherwise: rounding the address down to the lower word, as we used to,
       read the neighbouring register instead. That is how SPUCNT, at
       0x1F801DAA, returned the SPU's transfer queue -- that is to say, zero.
       The driver, which reads this register, modifies it and writes it back,
       lost the enable bit on every pass, and the twenty-four voices played for
       an SPU that believed itself switched off. */
    if (p >= 0x1F801000) return hw_read16(p);
    return 0;
}
static inline u32 LB(u32 a)
{
    u32 p = PHYS(a);
    if (p < 0x200000) return RAM[p];
    if (p >= 0x1F800000 && p < 0x1F800400) return SPAD[p & 0x3FF];
    /* The CD drive's four registers are byte-addressed and change meaning
       according to the index: reading them by shifted word would give
       nonsense. */
    if (p >= 0x1F801800 && p <= 0x1F801803) return hw_read32(p) & 0xFF;
    if (p >= 0x1F801000) return (hw_read32(p & ~3u) >> (8 * (p & 3))) & 0xFF;
    return 0;
}
static inline void SW(u32 a, u32 v)
{
    u32 p = PHYS(a);
    if (p < 0x200000) { __builtin_memcpy(RAM + p, &v, 4); return; }
    if (p >= 0x1F800000 && p < 0x1F800400) { __builtin_memcpy(SPAD + (p & 0x3FF), &v, 4); return; }
    if (p >= 0x1F801000) hw_write32(p, v, 4);
}
static inline void SH(u32 a, u32 v)
{
    u32 p = PHYS(a); u16 h = (u16)v;
    if (p < 0x200000) { __builtin_memcpy(RAM + p, &h, 2); return; }
    if (p >= 0x1F800000 && p < 0x1F800400) { __builtin_memcpy(SPAD + (p & 0x3FF), &h, 2); return; }
    if (p >= 0x1F801000) hw_write32(p, v, 2);
}
static inline void SB(u32 a, u32 v)
{
    u32 p = PHYS(a);
    if (p < 0x200000) { RAM[p] = (u8)v; return; }
    if (p >= 0x1F800000 && p < 0x1F800400) { SPAD[p & 0x3FF] = (u8)v; return; }
    if (p >= 0x1F801000) hw_write32(p, v, 1);
}
#endif
