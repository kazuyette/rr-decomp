/* cand_func_800548A8.c -- one candidate function, decompiled by m2c.
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
