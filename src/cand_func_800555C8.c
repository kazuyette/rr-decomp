/* cand_func_800555C8.c -- one candidate function, decompiled by m2c.
 *
 * Second run at the seventy-four that matched under none of the five
 * pipelines. The C is unchanged: the point is not to hope for a different
 * result, it is that tools/whydiff.py now exists. These get built and
 * diagnosed before anything is sent back to INCLUDE_ASM, so that we learn
 * *how* they miss rather than only that they do.
 *
 * One function per file: GCC 2.7.2 allocates registers across the whole
 * translation unit, so a candidate measured alone is measured on its own
 * merits.
 */
#include "m2c_macros.h"

extern M2C_UNK D_800118D0;
extern M2C_UNK D_800118E4;
extern M2C_UNK D_80076E20;
extern void *D_8007758C;
extern s32 *D_8007759C;
extern s32 D_800776D8;
extern s16 D_800776E0;
extern s32 D_800776E8;
extern s32 D_800776F0;

s32 func_800555C8(void) {
    s32 sp10;
    s32 sp14;
    s16 sp18;
    s16 sp1A;
    s16 sp20;
    s32 sp24;
    s32 sp2C;
    s32 temp_v0;

    D_800776E8 = 1;
    D_800776F0 = 0;
    D_800776E0 = 0;
    *D_8007759C |= 0xB0000;
    M2C_FIELD(D_8007758C, s16 *, 0x1AA) = 0x8000;
    func_80055570(D_8007759C);
    D_800776D8 = 0;
    if (M2C_FIELD(D_8007758C, u16 *, 0x1AE) & 0x7FF) {
loop_1:
        temp_v0 = D_800776D8 + 1;
        D_800776D8 = temp_v0;
        if (temp_v0 >= 0x1389) {
            printf(&D_800118D0, &D_800118E4);
        } else if (M2C_FIELD(D_8007758C, u16 *, 0x1AE) & 0x7FF) {
            goto loop_1;
        }
    }
    D_800776E0 = 0x200;
    M2C_FIELD(D_8007758C, s16 *, 0x180) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x182) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x184) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x186) = 0;
    M2C_FIELD(D_8007758C, u16 *, 0x18C) = 0xFFFFU;
    M2C_FIELD(D_8007758C, u16 *, 0x18E) = 0xFFFFU;
    M2C_FIELD(D_8007758C, s16 *, 0x190) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x192) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x194) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x196) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x198) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x19A) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x1B0) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x1B2) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x1B4) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x1B6) = 0;
    M2C_FIELD(D_8007758C, s16 *, 0x1AC) = 4;
    func_800558FC(&D_80076E20, 0x10);
    sp10 = -1;
    sp14 = 0x1F;
    sp18 = 0;
    sp1A = 0;
    sp20 = 0x3FFF;
    sp24 = 0x200;
    sp2C = 0;
    D_800776F0 = 0;
    func_80056854(&sp10);
    M2C_FIELD(D_8007758C, u16 *, 0x188) = 0xFFFFU;
    M2C_FIELD(D_8007758C, u16 *, 0x18A) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x18A) | 0xFF);
    func_80055570();
    func_80055570();
    func_80055570();
    func_80055570();
    M2C_FIELD(D_8007758C, u16 *, 0x18C) = 0xFFFFU;
    M2C_FIELD(D_8007758C, u16 *, 0x18E) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x18E) | 0xFF);
    func_80055570();
    func_80055570();
    func_80055570();
    func_80055570();
    M2C_FIELD(D_8007758C, s16 *, 0x1AA) = 0xC000;
    return 0;
}
