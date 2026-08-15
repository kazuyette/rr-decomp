/* cand_func_8002BB50.c -- one candidate function, decompiled by m2c.
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

s32 rcos(s32);

s32 func_8002BB50(u32 arg0) {
    u32 temp_v0;

    if ((u32) (arg0 + 0x1000) < 0x2001U) {
        temp_v0 = rcos((s32) (arg0 + (arg0 >> 0x1F)) >> 1) + 0x1000;
        return (s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1;
    }
    return 0;
}
