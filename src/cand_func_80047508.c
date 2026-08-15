/* cand_func_80047508.c -- one candidate function, decompiled by m2c.
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

extern s32 D_80077388;
extern s32 D_8007738C;
extern s32 *D_80077390;
extern u32 *D_80077394;
extern s32 *D_800773A0;

s32 func_80047508(s32 arg0) {
    switch (arg0) {
    case 0:
        *D_800773A0 = 0x401;
        *D_80077394 = 0;
block_5:
        D_8007738C = 0;
        D_80077388 = D_8007738C;
        break;
    case 1:
        *D_800773A0 = 0x401;
        *D_80077394 = 0x04000000;
        *D_80077394 = 0x02000000;
        *D_80077394 = 0x01000000;
        goto block_5;
    }
    *D_80077390 = (*D_80077394 & 0x3FFF) | 0xE1001000;
    return ((u32) *D_80077394 >> 0xC) & 1;
}
