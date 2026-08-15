/* cand_func_800177B8.c -- one candidate function, decompiled by m2c.
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



s32 func_800177B8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_lo;

    temp_a0 = arg0 & 0xFFF;
    var_a1 = arg1 & 0xFFF;
    temp_v1 = 0x100 - arg2;
    if (var_a1 < temp_a0) {
        var_lo = temp_a0 * temp_v1;
        if ((temp_a0 - var_a1) >= 0x801) {
            var_a1 += 0x1000;
        }
    } else {
        var_lo = temp_a0 * temp_v1;
        if ((var_a1 - temp_a0) >= 0x801) {
            var_lo = (temp_a0 + 0x1000) * temp_v1;
        }
    }
    return ((s32) (var_lo + (var_a1 * arg2)) / 256) & 0xFFF;
}
