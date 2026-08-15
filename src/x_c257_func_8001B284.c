/* cand_func_8001B284.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8012CFF0;
extern s32 D_801D7800;

void func_8001B284(void *arg0) {
    s32 temp_a1;
    s32 var_a1;

    temp_a1 = D_801D7800 - 0x1D4C;
    if (temp_a1 < 0) {
        var_a1 = -temp_a1;
    } else {
        var_a1 = temp_a1 * 6;
        M2C_FIELD(arg0, s32 *, 0xB0) = (s32) ((s32) M2C_FIELD(arg0, s32 *, 0xB0) / 2);
    }
    D_8012CFF0 = var_a1 + 0x3E8;
}
