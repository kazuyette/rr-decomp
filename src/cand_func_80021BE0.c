/* cand_func_80021BE0.c -- one candidate function, decompiled by m2c.
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

extern s16 D_8007C210;
extern s32 D_8007C260;
extern s16 D_8007C32C;
extern s16 D_8007C32E;
extern s32 D_80173348;
extern s16 D_801D77B8;

void func_80021BE0(void) {
    s32 temp_a2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;

    temp_a2 = D_8007C210 < 3;
    var_a1 = 0x17000;
    if (temp_a2 != 0) {
        var_a1 = 0x10000;
    }
    if (D_801D77B8 == 0) {
        if (D_8007C260 >= 0x2800) {
            var_a0 = (var_a1 + 0x2800) - D_8007C260;
        } else {
            var_a0 = 0x2800 - D_8007C260;
        }
        goto block_12;
    }
    if (D_801D77B8 == 1) {
        var_a0_2 = 0xB900;
        if (temp_a2 == 0) {
            var_a0_2 = 0x12900;
        }
        if (D_8007C260 >= var_a0_2) {
            var_a0 = D_8007C260 - var_a0_2;
        } else {
            var_a0 = (var_a1 - var_a0_2) + D_8007C260;
        }
block_12:
        D_80173348 = var_a0 + ((var_a1 * D_8007C32C) - D_8007C32E);
    }
}
