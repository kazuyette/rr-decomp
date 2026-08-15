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

extern M2C_UNK D_80011038;
extern M2C_UNK D_80011054;
extern M2C_UNK D_80011070;
extern M2C_UNK D_8001107C;

void func_80047EA0(void *arg0) {
    D_80077370(&D_80011038, M2C_FIELD(arg0, s16 *, 0), M2C_FIELD(arg0, s16 *, 2), M2C_FIELD(arg0, s16 *, 4), (s32) M2C_FIELD(arg0, s16 *, 6));
    D_80077370(&D_80011054, M2C_FIELD(arg0, s16 *, 8), M2C_FIELD(arg0, s16 *, 0xA), M2C_FIELD(arg0, s16 *, 0xC), (s32) M2C_FIELD(arg0, s16 *, 0xE));
    D_80077370(&D_80011070, (s16) M2C_FIELD(arg0, u8 *, 0x10));
    D_80077370(&D_8001107C, (s16) M2C_FIELD(arg0, u8 *, 0x11));
}
