/* cand_func_800373BC.c -- one candidate function, decompiled by m2c.
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

extern s32 D_801E90E0;

s32 func_800373BC(s32 arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;

    temp_v0 = D_801E90E0 << 0x10;
    temp_a2 = D_801E90E0 << 8;
    temp_hi = (s32) (arg0 + temp_v0) % temp_a2;
    temp_hi_2 = (s32) (arg1 + temp_v0) % temp_a2;
    var_a1 = temp_hi < temp_hi_2;
    if (var_a1 != 0) {
        var_a0 = temp_hi_2 - temp_hi;
    } else {
        var_a0 = temp_hi - temp_hi_2;
    }
    if ((D_801E90E0 << 7) < var_a0) {
        var_a0 = temp_a2 - var_a0;
        var_a1 = var_a1 == 0;
    }
    var_v0 = var_a0;
    if (var_a1 == 0) {
        var_v0 = -var_v0;
    }
    return var_v0;
}
