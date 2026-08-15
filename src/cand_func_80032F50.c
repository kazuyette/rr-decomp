/* cand_func_80032F50.c -- one candidate function, decompiled by m2c.
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

s32 func_80019C6C(s32, s32);
s32 func_8002721C(s32);
s32 rand();
extern s32 D_8012D8F8;
extern s32 D_8012D900;
extern s32 D_801E91D0;

void func_80032F50(s32 arg0, void *arg1) {
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;

    D_8012D900 = arg0;
    switch (arg0) {
    case 1:
        D_801E91D0 = 0x1E;
        D_8012D8F8 = M2C_FIELD(arg1, s16 *, 0xBA) * 8;
        return;
    case 2:
        var_v1 = func_80019C6C(func_8002721C(M2C_FIELD(arg1, s32 *, 8)), M2C_FIELD(arg1, s32 *, 0x24));
        if (var_v1 >= 0x401) {
            var_v1 = 0x800 - var_v1;
        }
        D_8012D8F8 = (s32) ((s32) (var_v1 * M2C_FIELD(arg1, s32 *, 0xA0)) / 2048) / 2;
        D_801E91D0 = 0x1E;
        if (rand() & 0x80) {
            D_8012D8F8 = -D_8012D8F8;
            return;
        }
    default:
        return;
    case 3:
        var_v0 = M2C_FIELD(arg1, s32 *, 0xA0);
        if (var_v0 < 0) {
            var_v0 += 7;
        }
        var_v0_2 = var_v0 >> 3;
block_14:
        D_8012D8F8 = var_v0_2;
        D_801E91D0 = 0x1E;
        break;
    case 4:
        var_v0_3 = M2C_FIELD(arg1, s32 *, 0xA0);
        if (var_v0_3 < 0) {
            var_v0_3 += 7;
        }
        var_v0_2 = var_v0_3 >> 3;
        goto block_14;
    case 5:
        var_v0_2 = 0xC8;
        goto block_14;
    }
}
