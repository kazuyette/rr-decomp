/* cand_func_800439D8.c -- one candidate function, decompiled by m2c.
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

extern s32 D_80075F90;
extern s32 D_80077730;
extern s32 D_80077734;
extern s32 D_80077738;
extern s32 D_8007773C;
extern s32 D_80077740;
extern s32 D_80077744;

void func_800439D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_at;
    s32 var_at_2;

    D_80075F90 = arg0;
    temp_t0 = arg3 << 0xC;
    var_at = arg1;
    if (arg1 < 0) {
        var_at += 1;
    }
    temp_v0 = var_at >> 1;
    D_80077734 = temp_t0 / temp_v0;
    var_at_2 = arg2;
    if (arg2 < 0) {
        var_at_2 += 1;
    }
    temp_v1 = var_at_2 >> 1;
    D_8007773C = temp_t0 / temp_v1;
    D_80077730 = (s32) (temp_v0 << 0xC) / arg3;
    D_80077738 = (s32) (temp_v1 << 0xC) / arg3;
    D_80077744 = arg4;
    D_80077740 = arg5;
}
