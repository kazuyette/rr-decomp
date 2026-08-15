/* cand_func_8004DB58.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8012D0C0;
extern s32 D_801D7E20;
extern s32 D_801D9028;

void func_8004DB58(s32 arg0) {
    if (arg0 & 0x1000) {
        D_8012D0C0 = 1;
        D_801D7E20 = arg0 & 0xFFF;
    } else {
        D_8012D0C0 = 0;
        D_801D7E20 = arg0;
    }
    if (D_801D7E20 < 4) {
        switch (D_801D7E20) {
        case 3:
            D_801D9028 = 0x78;
            return;
        case 2:
            D_801D9028 = 0xF0;
            return;
        case 1:
            
        default:
            D_801D9028 = 0x3C;
            return;
        }
    } else {
        D_801D9028 = D_801D7E20;
    }
}
