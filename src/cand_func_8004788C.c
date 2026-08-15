/* cand_func_8004788C.c -- one candidate function, decompiled by m2c.
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

s32 func_80045718();

s32 func_8004788C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v1;
    s32 var_v0;
    s32 var_v1;

    temp_v1 = arg0 & 3;
    if (func_80045718() != 0) {
        var_v1 = (temp_v1 << 9) | ((arg1 & 3) << 7);
        var_v0 = (s32) (arg3 & 0x300) >> 3;
    } else {
        var_v1 = (temp_v1 << 7) | ((arg1 & 3) << 5);
        var_v0 = (s32) (arg3 & 0x100) >> 4;
    }
    return var_v1 | var_v0 | ((s32) (arg2 & 0x3FF) >> 6);
}
