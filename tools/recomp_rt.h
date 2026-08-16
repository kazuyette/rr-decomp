/* Environnement minimal du banc d'essai : la memoire du PSX vue comme un
   tableau plat, adressee par les 24 bits bas de l'adresse virtuelle -- ce qui
   suffit tant qu'on ne touche ni au scratchpad ni aux registres materiels. */
#ifndef RT_H
#define RT_H
#include <stdint.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32; typedef uint64_t u64;
typedef int8_t s8; typedef int16_t s16; typedef int32_t s32; typedef int64_t s64;
extern u8 RAM[0x200000];
#define AD(a) ((a) & 0x1FFFFF)
static inline u32 LW(u32 a){ u32 v; __builtin_memcpy(&v, RAM+AD(a), 4); return v; }
static inline u32 LH(u32 a){ u16 v; __builtin_memcpy(&v, RAM+AD(a), 2); return v; }
static inline u32 LB(u32 a){ return RAM[AD(a)]; }
static inline void SW(u32 a, u32 v){ __builtin_memcpy(RAM+AD(a), &v, 4); }
static inline void SH(u32 a, u32 v){ u16 h=(u16)v; __builtin_memcpy(RAM+AD(a), &h, 2); }
static inline void SB(u32 a, u32 v){ RAM[AD(a)] = (u8)v; }
#endif
