/* cand_func_80047D24.c -- one candidate function, decompiled by m2c.
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



s32 func_80047D24(void *arg0, void *arg1) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 3) + M2C_FIELD(arg1, u8 *, 3) + 1;
    if (temp_v1 < 0x21) {
        M2C_FIELD(arg0, u8 *, 3) = (u8) temp_v1;
        M2C_FIELD(arg1, s32 *, 0) = 0;
        return 0;
    }
    return -1;
}
