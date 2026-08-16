/* cand_snd_play_se.c -- one candidate function, decompiled by m2c.
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

s32 func_8003A9D8(s16);
s16 func_8003AAD8(s16);
s32 func_8003AC2C(s16);
extern s16 D_800772FC;

s32 snd_play_se(s16 arg0) {
    s16 var_v0;
    s32 var_v0_2;

    var_v0 = D_800772FC;
    if (var_v0 == 0) {
        var_v0 = arg0 < 0x3A;
        if (var_v0 != 0) {
            if (arg0 < 0x11) {
                var_v0_2 = func_8003A9D8(arg0) << 0x10;
                goto block_6;
            }
            if (arg0 >= 0x1F) {
                var_v0_2 = func_8003AC2C(arg0) << 0x10;
block_6:
                return var_v0_2 >> 0x10;
            }
            var_v0 = func_8003AAD8(arg0);
            
            return (s32) var_v0;
        }
    }
    return (s32) var_v0;
}
