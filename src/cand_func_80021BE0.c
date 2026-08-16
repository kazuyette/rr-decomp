/* cand_func_80021BE0.c -- one candidate function, decompiled by m2c.
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

extern s16 D_8007C210;
extern s32 D_8007C260;
extern s16 D_8007C32C;
extern s16 D_8007C32E;
extern s32 D_80173348;
extern s16 D_801D77B8;

void func_80021BE0(void) {
    s32 temp_a2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;

    temp_a2 = D_8007C210 < 3;
    var_a1 = 0x17000;
    if (temp_a2 != 0) {
        var_a1 = 0x10000;
    }
    if (D_801D77B8 == 0) {
        if (D_8007C260 >= 0x2800) {
            var_a0 = (var_a1 + 0x2800) - D_8007C260;
        } else {
            var_a0 = 0x2800 - D_8007C260;
        }
        goto block_12;
    }
    if (D_801D77B8 == 1) {
        var_a0_2 = 0xB900;
        if (temp_a2 == 0) {
            var_a0_2 = 0x12900;
        }
        if (D_8007C260 >= var_a0_2) {
            var_a0 = D_8007C260 - var_a0_2;
        } else {
            var_a0 = (var_a1 - var_a0_2) + D_8007C260;
        }
block_12:
        D_80173348 = var_a0 + ((var_a1 * D_8007C32C) - D_8007C32E);
    }
}
