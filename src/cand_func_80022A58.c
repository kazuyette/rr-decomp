/* cand_func_80022A58.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8007C2F8;

void func_80022A58(void *arg0) {
    s32 temp_a1;
    s32 var_v0;
    s32 var_v1;

    if (M2C_FIELD(arg0, s16 *, 0xA4) >= 0) {
        func_800229F4();
        return;
    }
    if ((M2C_FIELD(arg0, s16 *, 0x96) == 0xC) && (M2C_FIELD(arg0, s16 *, 0xA2) == 1) && (((s32) D_8007C2F8 / 8) >= 0x97)) {
        var_v0 = D_8007C2F8;
        if (var_v0 < 0) {
            var_v0 += 7;
        }
        var_v1 = M2C_FIELD(arg0, s32 *, 0x88);
        temp_a1 = var_v0 >> 3;
        if (var_v1 < 0) {
            var_v1 += 7;
        }
        if (temp_a1 < (var_v1 >> 3)) {
            func_800229F4(temp_a1);
            return;
        }
        goto block_11;
    }
block_11:
    if ((M2C_FIELD(arg0, s16 *, 0xA4) < -0x3C) && (M2C_FIELD(arg0, s16 *, 0x96) != 0xC)) {
        M2C_FIELD(arg0, s16 *, 0xA4) = -0x1E;
    }
}
