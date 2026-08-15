/* cand_func_80031FD0.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8012D080;
extern u16 D_801D35AA;
extern u16 D_801D35AE;

void func_80031FD0(void) {
    s32 var_v0;
    s32 var_v0_2;
    u16 var_v0_3;

    if (D_801D35AA & 0x1000) {
        var_v0 = D_8012D080 - 1;
        if (D_8012D080 > 0) {
            D_8012D080 = 0;
            var_v0 = D_8012D080 - 1;
        }
        D_8012D080 = var_v0;
    } else if (D_801D35AA & 0x4000) {
        var_v0_2 = D_8012D080 + 1;
        if (D_8012D080 < 0) {
            D_8012D080 = 0;
            var_v0_2 = D_8012D080 + 1;
        }
        D_8012D080 = var_v0_2;
    } else {
        D_8012D080 = 0;
    }
    if (D_8012D080 < -0x19) {
        if (!((D_8012D080 + 0x1A) & 3)) {
            var_v0_3 = D_801D35AE | 0x1000;
            goto block_15;
        }
    } else if ((D_8012D080 >= 0x1A) && !((D_8012D080 - 0x1A) & 3)) {
        var_v0_3 = D_801D35AE | 0x4000;
block_15:
        D_801D35AE = var_v0_3;
    }
}
