/* cand_func_80047EA0.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_80011038;
extern M2C_UNK D_80011054;
extern M2C_UNK D_80011070;
extern M2C_UNK D_8001107C;

void func_80047EA0(void *arg0) {
    D_80077370(&D_80011038, M2C_FIELD(arg0, s16 *, 0), M2C_FIELD(arg0, s16 *, 2), M2C_FIELD(arg0, s16 *, 4), (s32) M2C_FIELD(arg0, s16 *, 6));
    D_80077370(&D_80011054, M2C_FIELD(arg0, s16 *, 8), M2C_FIELD(arg0, s16 *, 0xA), M2C_FIELD(arg0, s16 *, 0xC), (s32) M2C_FIELD(arg0, s16 *, 0xE));
    D_80077370(&D_80011070, (s16) M2C_FIELD(arg0, u8 *, 0x10));
    D_80077370(&D_8001107C, (s16) M2C_FIELD(arg0, u8 *, 0x11));
}
