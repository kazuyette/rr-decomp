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



void func_8001D2C8(s32 arg0, s32 arg2, s32 arg3, s32 arg4) {
    func_800297D8(arg0, func_80029278(arg0, func_80029278(arg3 - 0x10, 0x90, 0x20, 0x70, (0x10 - (arg4 * 4)) * 8, 0x4C - arg4), arg2, arg3 + 0x10, 0x90, 0x20, 0x70, 0x40, 0x4D), arg2 + 8, arg3 - 8, 0x90, 0x40, 0, 8, 0x20);
}
