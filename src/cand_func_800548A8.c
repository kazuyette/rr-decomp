/* cand_func_800548A8.c -- one candidate function, decompiled by m2c.
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

extern s32 D_80077688;
extern s32 D_800776A0;
extern s32 D_801734A0;

s32 func_800548A8(s32 *arg0, u16 **arg1) {
    s32 var_v0;
    u16 *var_a3;

    var_a3 = (D_800776A0 << 5) + D_801734A0;
    if ((*var_a3 & 0xFFFF) == 1) {
        D_800776A0 = 0;
        *var_a3 = 0;
        var_a3 = (D_800776A0 << 5) + D_801734A0;
    }
    var_v0 = 1;
    if ((*var_a3 & 0xFFFF) == 2) {
        *var_a3 = 4;
        var_v0 = 0;
        *arg0 = (D_80077688 << 5) + D_801734A0 + (D_800776A0 * 0x7E0);
        *arg1 = var_a3;
    }
    return var_v0;
}
