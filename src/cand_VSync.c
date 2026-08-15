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



s32 VSync(s32 arg0) {
    s32 temp_s1;
    s32 var_s0;
    s32 var_v0;

    
    var_s0 = 0;
    temp_s1 = arg0 << 8;
    if (arg0 >= 2) {
        goto block_4;
    }
    var_v0 = temp_s1 < 0;
    if (arg0 < 0) {
        goto block_5;
    }
    return func_80048DC4();
block_3:
    var_s0 += func_80048DC4(0);
block_4:
    var_v0 = temp_s1 < var_s0;
block_5:
    if (var_v0 == 0) {
        goto block_3;
    }
    return var_s0;
}
