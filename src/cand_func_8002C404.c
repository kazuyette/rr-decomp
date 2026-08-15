/* cand_func_8002C404.c -- one candidate function, decompiled by m2c.
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

extern s32 D_801E90E0;

s32 func_8002C404(s32 arg0, s32 arg1) {
    s32 temp_a3;
    s32 temp_hi;
    s32 temp_t1;
    s32 var_a0;
    s32 var_a2;
    u32 temp_v0;

    temp_t1 = D_801E90E0 << 0x10;
    temp_a3 = D_801E90E0 << 8;
    temp_hi = (s32) (arg0 + temp_t1) % temp_a3;
    var_a2 = (s32) (arg1 + temp_t1) % temp_a3;
    var_a0 = temp_hi;
    if (var_a2 < var_a0) {
        var_a0 = var_a2;
        var_a2 = temp_hi;
    }
    if ((D_801E90E0 << 7) >= (var_a2 - var_a0)) {
        temp_v0 = var_a0 + var_a2;
        return (s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1;
    }
    return (s32) (((s32) (var_a0 + temp_a3 + var_a2) / 2) + temp_t1) % temp_a3;
}
