/* cand_func_8004D238.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8007745C;

s32 func_8004D238(s32 arg0, s16 arg1, s16 arg2) {
    void *temp_v1;

    if ((u32) (arg0 & 0xFFFF) >= 0x18U) {
        return -1;
    }
    temp_v1 = ((s32) (arg0 << 0x10) >> 0xC) + D_8007745C;
    M2C_FIELD(temp_v1, s16 *, 0) = arg1;
    M2C_FIELD(temp_v1, s16 *, 2) = arg2;
    return 0;
}
