/* cand_func_80012C14.c -- written by hand.
 *
 * The builder of the section placement table for MAP.RRM. This is the function
 * that yielded the 32x32 grid of IDX.HED; every one of its fields is known,
 * which is the condition under which a manual conversion has a chance.
 *
 * Three points of form, each one read out of the instructions rather than
 * guessed:
 *
 * 1. The roundings are written as DIVISIONS, not as shifts. The retail does
 *    "addiu +0x400 ; bgez ; addiu +0xBFF ; sra 11" -- that is the bias
 *    correction GCC inserts on its own for a signed division by 0x800. Writing
 *    it as >> 11 would produce a bare sra and miss by three instructions per
 *    site. Likewise for /256 on the camera direction.
 *
 * 2. The camera position fractions are read as unsigned 16-bit (lhu) out of
 *    the 32-bit words D_801D9068/6C/70. The map is 32 * 2048 = 65536 units,
 *    exactly the range of a u16: the low part IS the position in the world,
 *    and subtracting it from (cell << 11) gives the offset of the cell
 *    relative to the camera.
 *
 * 3. The index is written into the placement BEFORE being tested, and the bit
 *    in the map of seen cells is set in the same breath -- both precede the
 *    "if negative, skip". Writing the test first would reorder two stores.
 */
#include "m2c_macros.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 index;
} SectionPlacement;   /* 16 bytes, confirmed by the 0x10 stride of both loops */

extern SectionPlacement D_801D7810[];   /* 64 entries */
extern s32 D_801D82D8[];                /* 32 x 32 bitmap of the retained cells */
extern s32 D_801D8354;                  /* its last word, addressed as a symbol of its own */
extern s16 *D_801D82D0;                 /* the table read from IDX.HED */
extern s8 D_8005944C[];                 /* traversal order: 16 dir x 64 (dx,dz) */
extern s32 D_801D9068;                  /* camera X */
extern s32 D_801D906C;                  /* camera Y */
extern s32 D_801D9070;                  /* camera Z */
extern s32 D_801D907C;                  /* camera heading */
extern s16 D_801E91F0[];                /* current rotation matrix */

s32 func_80015AAC(s32 x, s32 z);
s32 func_80015BC4(s32 x, s32 z, s32 zone);
void func_8004315C(s16 *m, s16 *v, s32 *out);

void func_80012C14(void) {
    s16 sp10[3];
    s32 sp18[3];
    s32 i;
    s32 dir;
    s32 cx;
    s32 cz;
    s32 x;
    s32 z;
    s32 zone;
    s32 idx;
    s32 *q;

    /* The retail loads D_801D8354 -- the last word of the bitmap -- as a
     * symbol in its own right and walks a pointer down four bytes at a time.
     * Writing D_801D82D8[i] gives the same address but a relocation on the
     * base plus a displacement of 124, which the retail does not have. */
    q = &D_801D8354;
    for (i = 0x1F; i >= 0; i--) {
        *q = 0;
        q--;
    }

    dir = (D_801D907C / 256) & 0xF;
    cx = (D_801D9068 + 0x400) / 0x800;
    cz = (D_801D9070 + 0x400) / 0x800;
    zone = func_80015AAC(cx, cz);

    /* Indexed by [i] rather than by an advancing pointer: the retail walks two
     * registers over the table, one on the entry and one on its index field,
     * which is what GCC's strength reduction produces from an indexing and not
     * from a single incremented pointer. */
    for (i = 0; i < 0x40; i++) {
        x = cx + D_8005944C[dir * 256 + i * 2];
        z = cz + D_8005944C[dir * 256 + i * 2 + 1];
        if ((u32) x >= 0x20U) {
            D_801D7810[i].index = -1;
            continue;
        }
        if ((u32) z >= 0x20U) {
            D_801D7810[i].index = -1;
            continue;
        }
        if (func_80015BC4(x, z, zone) == 0) {
            D_801D7810[i].index = -1;
            continue;
        }
        idx = D_801D82D0[z * 32 + 30 - x];
        D_801D7810[i].index = idx;
        D_801D82D8[z] |= 1 << x;
        if (idx < 0) {
            continue;
        }
        sp10[0] = (x << 11) - (u16) D_801D9068;
        sp10[1] = -(u16) D_801D906C;
        sp10[2] = (z << 11) - (u16) D_801D9070;
        func_8004315C(D_801E91F0, sp10, sp18);
        D_801D7810[i].x = sp18[0] << 2;
        D_801D7810[i].y = sp18[1] << 2;
        D_801D7810[i].z = sp18[2] << 2;
    }
}
