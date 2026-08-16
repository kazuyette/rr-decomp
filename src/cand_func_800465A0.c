/* cand_func_800465A0.c -- one candidate function, decompiled by m2c.
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

extern s32 D_80077378;

s32 func_800465A0(s32 arg0, s32 arg1) {
    s32 var_v0;
    s32 var_v1;

    var_v1 = arg0 & 0xFFF;
    if (D_80077378 == 0) {
        var_v0 = (arg1 & 0x7FF) << 0xB;
        var_v1 = arg0 & 0x7FF;
    } else {
        var_v0 = (arg1 & 0xFFF) << 0xC;
    }
    return var_v0 | (var_v1 | 0xE5000000);
}
