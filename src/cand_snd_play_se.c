/* cand_snd_play_se.c -- one candidate function, decompiled by m2c.
 *
 * One function per file on purpose. GCC 2.7.2 allocates registers with
 * the whole translation unit in view, so a function can reproduce the
 * retail bytes alone and miss when compiled beside others; batch 5 lost
 * nine that way. Isolated, a candidate is measured on its own merits,
 * and tools/apply_sweep.py only has to rename the file once the sweep
 * says which pipeline it belongs to.
 *
 * This batch is what the jump tables unlocked: m2c refuses a function
 * whose switch it cannot resolve, and the tables live in .rodata, in a
 * different file from the function. Feeding both to m2c recovered 174
 * functions, among them the largest in the game.
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
