/* cand_func_800439D8.c -- one candidate function, decompiled by m2c.
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

extern s32 D_80075F90;
extern s32 D_80077730;
extern s32 D_80077734;
extern s32 D_80077738;
extern s32 D_8007773C;
extern s32 D_80077740;
extern s32 D_80077744;

void func_800439D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_at;
    s32 var_at_2;

    D_80075F90 = arg0;
    temp_t0 = arg3 << 0xC;
    var_at = arg1;
    if (arg1 < 0) {
        var_at += 1;
    }
    temp_v0 = var_at >> 1;
    D_80077734 = temp_t0 / temp_v0;
    var_at_2 = arg2;
    if (arg2 < 0) {
        var_at_2 += 1;
    }
    temp_v1 = var_at_2 >> 1;
    D_8007773C = temp_t0 / temp_v1;
    D_80077730 = (s32) (temp_v0 << 0xC) / arg3;
    D_80077738 = (s32) (temp_v1 << 0xC) / arg3;
    D_80077744 = arg4;
    D_80077740 = arg5;
}
