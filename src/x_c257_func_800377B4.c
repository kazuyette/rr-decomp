/* cand_func_800377B4.c -- one candidate function, decompiled by m2c.
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

s32 func_80037478();
extern s32 D_801D9020;
extern s32 D_801D9058;
extern s32 D_801E90B8;
extern s32 D_801E91E8;

void func_800377B4(void) {
    s32 temp_v0;

    temp_v0 = func_80037478();
    if (D_801E91E8 < temp_v0) {
        D_801D9058 = 0;
        D_801E90B8 = D_801E91E8;
        D_801D9020 = temp_v0 - D_801E91E8;
    } else if (temp_v0 < D_801E91E8) {
        D_801D9058 = 1;
        D_801E90B8 = temp_v0;
        D_801D9020 = D_801E91E8 - temp_v0;
    } else {
        D_801D9058 = -1;
    }
    D_801E91E8 = temp_v0;
}
