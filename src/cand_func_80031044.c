/* cand_func_80031044.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8012D020;
extern s16 D_801D34F8;
extern u16 D_801D35AA;

void func_80031044(void) {
    if ((D_8012D020 & 1) && (D_801D35AA & 0x1000)) {
        D_801D34F8 = 0x13;
    }
    if ((D_8012D020 & 0x100) && (D_801D35AA & 0x4000)) {
        D_801D34F8 = 0x13;
    }
    if ((D_8012D020 & 0x200) && (D_801D35AA & 0x8000)) {
        D_801D34F8 = 8;
    }
}
