/* cand_func_8004788C.c -- one candidate function, decompiled by m2c.
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

s32 func_80045718();

s32 func_8004788C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v1;
    s32 var_v0;
    s32 var_v1;

    temp_v1 = arg0 & 3;
    if (func_80045718() != 0) {
        var_v1 = (temp_v1 << 9) | ((arg1 & 3) << 7);
        var_v0 = (s32) (arg3 & 0x300) >> 3;
    } else {
        var_v1 = (temp_v1 << 7) | ((arg1 & 3) << 5);
        var_v0 = (s32) (arg3 & 0x100) >> 4;
    }
    return var_v1 | var_v0 | ((s32) (arg2 & 0x3FF) >> 6);
}
