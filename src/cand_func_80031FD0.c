/* cand_func_80031FD0.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8012D080;
extern u16 D_801D35AA;
extern u16 D_801D35AE;

void func_80031FD0(void) {
    s32 var_v0;
    s32 var_v0_2;
    u16 var_v0_3;

    if (D_801D35AA & 0x1000) {
        var_v0 = D_8012D080 - 1;
        if (D_8012D080 > 0) {
            D_8012D080 = 0;
            var_v0 = D_8012D080 - 1;
        }
        D_8012D080 = var_v0;
    } else if (D_801D35AA & 0x4000) {
        var_v0_2 = D_8012D080 + 1;
        if (D_8012D080 < 0) {
            D_8012D080 = 0;
            var_v0_2 = D_8012D080 + 1;
        }
        D_8012D080 = var_v0_2;
    } else {
        D_8012D080 = 0;
    }
    if (D_8012D080 < -0x19) {
        if (!((D_8012D080 + 0x1A) & 3)) {
            var_v0_3 = D_801D35AE | 0x1000;
            goto block_15;
        }
    } else if ((D_8012D080 >= 0x1A) && !((D_8012D080 - 0x1A) & 3)) {
        var_v0_3 = D_801D35AE | 0x4000;
block_15:
        D_801D35AE = var_v0_3;
    }
}
