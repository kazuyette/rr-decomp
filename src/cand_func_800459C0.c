/* cand_func_800459C0.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_80010F50;
extern M2C_UNK D_80010F5C;
extern s32 D_80077374;
extern M2C_UNK D_80077384;

s32 func_800459C0(s16 arg0, void *arg1) {
    s16 temp_a0;
    s16 temp_v1;

    if (D_80077374 == 1) {
        temp_v1 = M2C_FIELD(arg1, s16 *, 0);
        if ((temp_v1 < 0) || (temp_a0 = M2C_FIELD(arg1, s16 *, 2), (temp_a0 < 0)) || ((temp_v1 + M2C_FIELD(arg1, s16 *, 4)) >= 0x401) || ((temp_a0 + M2C_FIELD(arg1, s16 *, 6)) >= 0x201)) {
            D_80077370(&D_80010F50, arg0, arg0);
            D_80077370(&D_80010F5C, M2C_FIELD(arg1, s16 *, 0), M2C_FIELD(arg1, s16 *, 2), M2C_FIELD(arg1, s16 *, 4), (s32) M2C_FIELD(arg1, s16 *, 6));
            return -1;
        }
        goto block_7;
    }
block_7:
    if (D_80077374 == 2) {
        D_80077370(&D_80077384, arg0, arg0);
        D_80077370(&D_80010F5C, M2C_FIELD(arg1, s16 *, 0), M2C_FIELD(arg1, s16 *, 2), M2C_FIELD(arg1, s16 *, 4), (s32) M2C_FIELD(arg1, s16 *, 6));
    }
    return 0;
}
