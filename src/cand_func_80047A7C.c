/* cand_func_80047A7C.c -- one candidate function, decompiled by m2c.
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



void func_80047A7C(s32 *arg0, s32 arg1, s32 *arg2) {
    *arg2 = (*arg2 & 0xFF000000) | (*arg0 & 0xFFFFFF);
    *arg0 = (*arg0 & 0xFF000000) | (arg1 & 0xFFFFFF);
}
