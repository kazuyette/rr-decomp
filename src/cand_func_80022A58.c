/* cand_AddPrim.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8007C2F8;

void func_80022A58(void *arg0) {
    s32 temp_a1;
    s32 var_v0;
    s32 var_v1;

    if (M2C_FIELD(arg0, s16 *, 0xA4) >= 0) {
        func_800229F4();
        return;
    }
    if ((M2C_FIELD(arg0, s16 *, 0x96) == 0xC) && (M2C_FIELD(arg0, s16 *, 0xA2) == 1) && (((s32) D_8007C2F8 / 8) >= 0x97)) {
        var_v0 = D_8007C2F8;
        if (var_v0 < 0) {
            var_v0 += 7;
        }
        var_v1 = M2C_FIELD(arg0, s32 *, 0x88);
        temp_a1 = var_v0 >> 3;
        if (var_v1 < 0) {
            var_v1 += 7;
        }
        if (temp_a1 < (var_v1 >> 3)) {
            func_800229F4(temp_a1);
            return;
        }
        goto block_11;
    }
block_11:
    if ((M2C_FIELD(arg0, s16 *, 0xA4) < -0x3C) && (M2C_FIELD(arg0, s16 *, 0x96) != 0xC)) {
        M2C_FIELD(arg0, s16 *, 0xA4) = -0x1E;
    }
}
