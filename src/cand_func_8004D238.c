/* cand_func_8004D238.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8007745C;

s32 func_8004D238(s32 arg0, s16 arg1, s16 arg2) {
    void *temp_v1;

    if ((u32) (arg0 & 0xFFFF) >= 0x18U) {
        return -1;
    }
    temp_v1 = ((s32) (arg0 << 0x10) >> 0xC) + D_8007745C;
    M2C_FIELD(temp_v1, s16 *, 0) = arg1;
    M2C_FIELD(temp_v1, s16 *, 2) = arg2;
    return 0;
}
