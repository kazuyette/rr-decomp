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



void func_8002757C(s32 arg0) {
    s32 temp_s0;
    s32 temp_s1;

    temp_s1 = func_8002721C();
    temp_s0 = func_800177B8(temp_s1, func_8002721C(arg0 - 0x180), 0x80);
    func_800177B8(temp_s0, func_800177B8(temp_s1, func_8002721C(arg0 + 0x180), 0x80), 0x80);
}
