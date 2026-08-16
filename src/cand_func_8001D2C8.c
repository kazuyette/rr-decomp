/* cand_func_8001D2C8.c -- one candidate function, decompiled by m2c.
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



void func_8001D2C8(s32 arg0, s32 arg2, s32 arg3, s32 arg4) {
    func_800297D8(arg0, func_80029278(arg0, func_80029278(arg3 - 0x10, 0x90, 0x20, 0x70, (0x10 - (arg4 * 4)) * 8, 0x4C - arg4), arg2, arg3 + 0x10, 0x90, 0x20, 0x70, 0x40, 0x4D), arg2 + 8, arg3 - 8, 0x90, 0x40, 0, 8, 0x20);
}
