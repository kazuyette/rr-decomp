/* cand_func_800177B8.c -- one candidate function, decompiled by m2c.
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



s32 func_800177B8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_lo;

    temp_a0 = arg0 & 0xFFF;
    var_a1 = arg1 & 0xFFF;
    temp_v1 = 0x100 - arg2;
    if (var_a1 < temp_a0) {
        var_lo = temp_a0 * temp_v1;
        if ((temp_a0 - var_a1) >= 0x801) {
            var_a1 += 0x1000;
        }
    } else {
        var_lo = temp_a0 * temp_v1;
        if ((var_a1 - temp_a0) >= 0x801) {
            var_lo = (temp_a0 + 0x1000) * temp_v1;
        }
    }
    return ((s32) (var_lo + (var_a1 * arg2)) / 256) & 0xFFF;
}
