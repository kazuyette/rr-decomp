/* cand_func_80047D24.c -- one candidate function, decompiled by m2c.
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



s32 func_80047D24(void *arg0, void *arg1) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, u8 *, 3) + M2C_FIELD(arg1, u8 *, 3) + 1;
    if (temp_v1 < 0x21) {
        M2C_FIELD(arg0, u8 *, 3) = (u8) temp_v1;
        M2C_FIELD(arg1, s32 *, 0) = 0;
        return 0;
    }
    return -1;
}
