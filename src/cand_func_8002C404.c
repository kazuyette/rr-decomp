/* cand_func_8002C404.c -- one candidate function, decompiled by m2c.
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

extern s32 D_801E90E0;

s32 func_8002C404(s32 arg0, s32 arg1) {
    s32 temp_a3;
    s32 temp_hi;
    s32 temp_t1;
    s32 var_a0;
    s32 var_a2;
    u32 temp_v0;

    temp_t1 = D_801E90E0 << 0x10;
    temp_a3 = D_801E90E0 << 8;
    temp_hi = (s32) (arg0 + temp_t1) % temp_a3;
    var_a2 = (s32) (arg1 + temp_t1) % temp_a3;
    var_a0 = temp_hi;
    if (var_a2 < var_a0) {
        var_a0 = var_a2;
        var_a2 = temp_hi;
    }
    if ((D_801E90E0 << 7) >= (var_a2 - var_a0)) {
        temp_v0 = var_a0 + var_a2;
        return (s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1;
    }
    return (s32) (((s32) (var_a0 + temp_a3 + var_a2) / 2) + temp_t1) % temp_a3;
}
