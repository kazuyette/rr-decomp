/* cand_func_80037478.c -- one candidate function, decompiled by m2c.
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

s32 func_800373BC(s32, s32);
extern s16 D_801733B8;
extern s32 D_80173480;
extern s32 D_80173488;
extern s32 D_80173490;
extern s16 D_801D9060;

s32 func_80037478(s32 arg0) {
    s32 temp_a0;
    s32 temp_s0;
    s32 temp_v1_2;
    s32 var_v0;
    s32 var_v1;
    u32 temp_v0;
    u32 temp_v1;

    if (D_801D9060 < 3) {
        return (D_801733B8 == 0) << 8;
    }
    temp_s0 = func_800373BC(D_80173480, arg0);
    temp_a0 = func_800373BC(D_80173488, arg0);
    temp_v1 = temp_s0 + 0x200;
    if (temp_v1 < 0x401U) {
        var_v0 = temp_v1 + (temp_v1 >> 0x1F);
        goto block_6;
    }
    if ((u32) (temp_a0 + 0x200) < 0x401U) {
        temp_v0 = 0x200 - temp_a0;
        var_v0 = temp_v0 + (temp_v0 >> 0x1F);
block_6:
        temp_v1_2 = var_v0 >> 1;
        var_v1 = (s32) (temp_v1_2 + ((u32) temp_v1_2 >> 0x1F)) >> 1;
    } else if (temp_s0 > 0) {
        if (D_80173490 > 0) {
            var_v1 = (temp_a0 >> 0x1F) & 0x100;
        } else {
            var_v1 = 0x100;
        }
    } else {
        var_v1 = 0;
        if (D_80173490 < 0) {
            var_v1 = (temp_a0 < 1) << 8;
        }
    }
    return var_v1;
}
