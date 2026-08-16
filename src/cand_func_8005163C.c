/* cand_func_8005163C.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_801E90E8;

void func_8005163C(s32 arg0, s16 arg1) {
    void *temp_v1;

    temp_v1 = (arg1 * 0xA8) + *(&D_801E90E8 + ((s32) (arg0 << 0x10) >> 0xE));
    M2C_FIELD(temp_v1, s32 *, 0x90) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x90) | 4);
}
