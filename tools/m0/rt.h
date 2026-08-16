/* Memoire et acces materiels du banc de recompilation.
 *
 * Le piege a eviter : masquer toutes les adresses sur 21 bits ferait tomber
 * les registres du GPU, ecrits en 0x1F801810, au beau milieu de la RAM. Les
 * trois espaces sont donc distingues ici, une fois pour toutes, plutot que
 * dans chaque fonction traduite.
 */
#ifndef RT_H
#define RT_H
#include <stdint.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32; typedef uint64_t u64;
typedef int8_t s8; typedef int16_t s16; typedef int32_t s32; typedef int64_t s64;

extern u8 RAM[0x200000];      /* 2 Mo de memoire principale */
extern u8 SPAD[0x400];        /* le bloc-notes, 1 Ko de RAM rapide dans le CPU */
extern u32 g_sp;
extern u32 COP0[32];
u32 psx_syscall(u32, u32, u32, u32);

u32  hw_read32(u32 phys);
void hw_write32(u32 phys, u32 v, int width);

/* Le KUSEG, le KSEG0 et le KSEG1 designent la meme memoire physique : seuls
   les trois bits hauts changent. Les masquer d'abord evite d'avoir a savoir
   dans quel segment le jeu travaille -- il utilise les deux. */
#define PHYS(a) ((a) & 0x1FFFFFFF)

/* La base de temps.
 *
 * Le pilote CD attend dans une boucle qui ne lit aucun registre et n'appelle
 * aucune fonction : elle surveille un octet en RAM que le gestionnaire doit
 * poser. Une horloge cadencee sur le materiel ou sur les appels s'arrete donc
 * exactement pendant le moment ou le jeu attend. Les acces memoire, eux, ont
 * lieu dans toutes les boucles sans exception -- c'est la seule chose que du
 * code qui tourne ne peut pas s'abstenir de faire. */
extern unsigned long g_cycles;
extern int in_irq_flag;
void psx_clock(void);
#define TICK() do { if (!(++g_cycles & 0xFFFF) && !in_irq_flag) psx_clock(); } while (0)

static inline u32 LW(u32 a)
{
    TICK();
    u32 p = PHYS(a);
    if (p < 0x200000) { u32 v; __builtin_memcpy(&v, RAM + p, 4); return v; }
    if (p >= 0x1F800000 && p < 0x1F800400) { u32 v; __builtin_memcpy(&v, SPAD + (p & 0x3FF), 4); return v; }
    if (p >= 0x1F801000) return hw_read32(p);
    return 0;
}
static inline u32 LH(u32 a)
{
    TICK();
    u32 p = PHYS(a);
    if (p < 0x200000) { u16 v; __builtin_memcpy(&v, RAM + p, 2); return v; }
    if (p >= 0x1F800000 && p < 0x1F800400) { u16 v; __builtin_memcpy(&v, SPAD + (p & 0x3FF), 2); return v; }
    if (p >= 0x1F801000) return hw_read32(p & ~3u) >> (8 * (p & 2));
    return 0;
}
static inline u32 LB(u32 a)
{
    TICK();
    u32 p = PHYS(a);
    if (p < 0x200000) return RAM[p];
    if (p >= 0x1F800000 && p < 0x1F800400) return SPAD[p & 0x3FF];
    /* Les quatre registres du lecteur CD s'adressent a l'octet et changent de
       sens selon l'index : les lire par mot decale donnerait n'importe quoi. */
    if (p >= 0x1F801800 && p <= 0x1F801803) return hw_read32(p) & 0xFF;
    if (p >= 0x1F801000) return (hw_read32(p & ~3u) >> (8 * (p & 3))) & 0xFF;
    return 0;
}
static inline void SW(u32 a, u32 v)
{
    TICK();
    u32 p = PHYS(a);
    if (p < 0x200000) { __builtin_memcpy(RAM + p, &v, 4); return; }
    if (p >= 0x1F800000 && p < 0x1F800400) { __builtin_memcpy(SPAD + (p & 0x3FF), &v, 4); return; }
    if (p >= 0x1F801000) hw_write32(p, v, 4);
}
static inline void SH(u32 a, u32 v)
{
    TICK();
    u32 p = PHYS(a); u16 h = (u16)v;
    if (p < 0x200000) { __builtin_memcpy(RAM + p, &h, 2); return; }
    if (p >= 0x1F800000 && p < 0x1F800400) { __builtin_memcpy(SPAD + (p & 0x3FF), &h, 2); return; }
    if (p >= 0x1F801000) hw_write32(p, v, 2);
}
static inline void SB(u32 a, u32 v)
{
    TICK();
    u32 p = PHYS(a);
    if (p < 0x200000) { RAM[p] = (u8)v; return; }
    if (p >= 0x1F800000 && p < 0x1F800400) { SPAD[p & 0x3FF] = (u8)v; return; }
    if (p >= 0x1F801000) hw_write32(p, v, 1);
}
#endif
