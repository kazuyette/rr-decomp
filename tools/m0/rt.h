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
u32  hw_read16(u32 phys);
void hw_write32(u32 phys, u32 v, int width);

/* Le KUSEG, le KSEG0 et le KSEG1 designent la meme memoire physique : seuls
   les trois bits hauts changent. Les masquer d'abord evite d'avoir a savoir
   dans quel segment le jeu travaille -- il utilise les deux. */
#define PHYS(a) ((a) & 0x1FFFFFFF)

/* La base de temps : le compte des instructions.
 *
 * Une recompilation statique perd le rythme de la machine. Le code traduit
 * s'execute a la vitesse de l'hote, et rien ne relie plus une instruction a un
 * cycle -- il faut donc fabriquer une horloge, et le choix decide de tout.
 *
 * Elle a d'abord battu sur les acces memoire, faute de mieux. C'etait un
 * substitut commode et faux : il fallait ensuite faire avancer le temps a la
 * main quand le jeu attendait sans rien lire, et le compteur de balayages ne
 * voulait plus rien dire.
 *
 * Elle compte maintenant ce que la machine comptait : les instructions
 * executees. Le traducteur les facture par bloc rectiligne -- une addition par
 * bloc, pas par instruction -- et le balayage tombe quand le budget d'une
 * image est epuise. L'attente de VSync brule alors des cycles exactement comme
 * sur la console, sans qu'on ait rien a lui souffler.
 *
 * Le budget : 33,8688 MHz divises par 59,94 images font 565 045 cycles. Le
 * nombre d'instructions correspondant depend du nombre moyen de cycles par
 * instruction, que les acces memoire non caches font monter au-dessus de un.
 * C'est un etalonnage, pas une mesure, et il se regle sans recompiler.
 */
extern unsigned long long g_cycles, g_echeance;
extern int in_irq_flag;
void psx_horloge(void);
#define CYCLES(n) do { \
    g_cycles += (unsigned)(n); \
    if (g_cycles >= g_echeance && !in_irq_flag) psx_horloge(); \
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
    /* Une lecture de seize bits n'est pas une lecture de trente-deux dont on
       prend une moitie. Beaucoup de registres du materiel se lisent par
       demi-mot et n'ont aucun sens autrement : rabattre l'adresse sur le mot
       inferieur, comme on le faisait, faisait lire le registre voisin.
       C'est ainsi que SPUCNT, en 0x1F801DAA, rendait la file de transfert du
       SPU -- c'est-a-dire zero. Le pilote, qui lit ce registre, le modifie et
       le reecrit, y perdait le bit d'activation a chaque passage, et les
       vingt-quatre voix jouaient pour un SPU qui se croyait eteint. */
    if (p >= 0x1F801000) return hw_read16(p);
    return 0;
}
static inline u32 LB(u32 a)
{
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
