/* cand_VSync.c -- one candidate function, decompiled by m2c.
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



s32 VSync(s32 arg0) {
    s32 temp_s1;
    s32 var_s0;
    s32 var_v0;

    
    var_s0 = 0;
    temp_s1 = arg0 << 8;
    if (arg0 >= 2) {
        goto block_4;
    }
    var_v0 = temp_s1 < 0;
    if (arg0 < 0) {
        goto block_5;
    }
    return func_80048DC4();
block_3:
    var_s0 += func_80048DC4(0);
block_4:
    var_v0 = temp_s1 < var_s0;
block_5:
    if (var_v0 == 0) {
        goto block_3;
    }
    return var_s0;
}
