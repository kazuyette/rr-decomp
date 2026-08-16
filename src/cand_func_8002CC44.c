/* cand_func_8002CC44.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_801D9068;
extern s32 D_801D906C;
extern s32 D_801D9070;
extern s32 D_801D9078;
extern s32 D_801D907C;
extern s32 D_801D9080;

void func_8002CC44(void *arg0, void *arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_lo;
    s32 var_v0;

    M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0);
    M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) (((s32) (M2C_FIELD(arg1, s32 *, 0) - M2C_FIELD(&D_801D9068, s32 *, 0)) / 8) + M2C_FIELD(&D_801D9068, s32 *, 0));
    D_801D906C += (s32) (M2C_FIELD(arg1, s32 *, 4) - D_801D906C) / 8;
    var_v0 = M2C_FIELD(arg1, s32 *, 8) - D_801D9070;
    if (var_v0 < 0) {
        var_v0 += 7;
    }
    D_801D9070 += var_v0 >> 3;
    temp_a0 = M2C_FIELD(arg1, s32 *, 0) - M2C_FIELD(arg0, s32 *, 0);
    sp10 = temp_a0;
    sp14 = M2C_FIELD(arg1, s32 *, 4) - M2C_FIELD(arg0, s32 *, 4);
    temp_a1 = M2C_FIELD(arg1, s32 *, 8) - M2C_FIELD(arg0, s32 *, 8);
    sp18 = temp_a1;
    temp_lo = sp10 * sp10;
    D_801D907C = 0x400 - func_800187A0(temp_a0, temp_a1, arg1, &D_801D9068);
    D_801D9078 = 0x400 - func_800187A0(sp14, SquareRoot(temp_lo + (sp18 * sp18), temp_lo) >> 6);
    D_801D9080 = 0;
    func_800186C8();
}
