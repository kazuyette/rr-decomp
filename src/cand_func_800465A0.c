/* cand_func_800465A0.c -- one candidate function, decompiled by m2c.
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

extern s32 D_80077378;

s32 func_800465A0(s32 arg0, s32 arg1) {
    s32 var_v0;
    s32 var_v1;

    var_v1 = arg0 & 0xFFF;
    if (D_80077378 == 0) {
        var_v0 = (arg1 & 0x7FF) << 0xB;
        var_v1 = arg0 & 0x7FF;
    } else {
        var_v0 = (arg1 & 0xFFF) << 0xC;
    }
    return var_v0 | (var_v1 | 0xE5000000);
}
