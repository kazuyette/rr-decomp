/* cand_func_80046510.c -- one candidate function, decompiled by m2c.
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

s32 func_80046510(s32 arg0, s16 arg1) {
    s16 var_a1;
    s16 var_a1_2;
    s16 var_v0_2;
    s16 var_v0_3;
    s32 var_v0;
    s32 var_v1;

    if (D_80077378 != 0) {
        var_a1 = arg1;
        if (arg1 >= 0) {
            if (var_a1 >= 0x400) {
                var_a1 = 0x3FF;
            }
            var_v0_2 = var_a1;
        } else {
            var_v0_2 = 0;
        }
        var_v0 = (var_v0_2 & 0xFFF) << 0xC;
        var_v1 = arg0 & 0xFFF;
    } else {
        var_a1_2 = arg1;
        if (arg1 >= 0) {
            if (var_a1_2 >= 0x200) {
                var_a1_2 = 0x1FF;
            }
            var_v0_3 = var_a1_2;
        } else {
            var_v0_3 = 0;
        }
        var_v0 = (var_v0_3 & 0x1FF) << 0xA;
        var_v1 = arg0 & 0x3FF;
    }
    return var_v0 | (var_v1 | 0xE4000000);
}
