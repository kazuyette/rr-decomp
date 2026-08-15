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

extern M2C_UNK D_80010F50;
extern M2C_UNK D_80010F5C;
extern s32 D_80077374;
extern M2C_UNK D_80077384;

s32 func_800459C0(s16 arg0, void *arg1) {
    s16 temp_a0;
    s16 temp_v1;

    if (D_80077374 == 1) {
        temp_v1 = M2C_FIELD(arg1, s16 *, 0);
        if ((temp_v1 < 0) || (temp_a0 = M2C_FIELD(arg1, s16 *, 2), (temp_a0 < 0)) || ((temp_v1 + M2C_FIELD(arg1, s16 *, 4)) >= 0x401) || ((temp_a0 + M2C_FIELD(arg1, s16 *, 6)) >= 0x201)) {
            D_80077370(&D_80010F50, arg0, arg0);
            D_80077370(&D_80010F5C, M2C_FIELD(arg1, s16 *, 0), M2C_FIELD(arg1, s16 *, 2), M2C_FIELD(arg1, s16 *, 4), (s32) M2C_FIELD(arg1, s16 *, 6));
            return -1;
        }
        goto block_7;
    }
block_7:
    if (D_80077374 == 2) {
        D_80077370(&D_80077384, arg0, arg0);
        D_80077370(&D_80010F5C, M2C_FIELD(arg1, s16 *, 0), M2C_FIELD(arg1, s16 *, 2), M2C_FIELD(arg1, s16 *, 4), (s32) M2C_FIELD(arg1, s16 *, 6));
    }
    return 0;
}
