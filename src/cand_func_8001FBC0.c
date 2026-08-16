/* cand_func_8001FBC0.c -- one candidate function, decompiled by m2c.
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



s32 func_8001FBC0(s32 arg0, s32 arg1) {
    return ((arg0 / 30) * 0x3E8) + (((s32) ((arg0 % 30) * 0x64) / 3) + arg1);
}
