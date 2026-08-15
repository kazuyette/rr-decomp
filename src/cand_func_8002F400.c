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

extern M2C_UNK D_800743F4;
extern M2C_UNK D_80074494;
extern M2C_UNK D_80074534;
extern M2C_UNK D_80074536;
extern M2C_UNK D_80074538;
extern M2C_UNK D_8007453A;
extern s16 D_8012D8D0;
extern s32 D_801E91E0;

s16 func_8002F400(s16 arg0) {
    s16 temp_a1;
    s16 temp_a1_2;
    s16 var_a1;
    s16 var_a2;
    s16 var_a2_2;
    s16 var_a3;
    s16 var_a3_2;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_s2;
    s32 var_v1;
    void *temp_s0_2;
    void *temp_s1;

    temp_v0 = D_8012D8D0 * 8;
    temp_v1 = D_8012D8D0 * 8;
    temp_a1 = func_80029278(arg0, func_80029278(*(&D_80074534 + temp_v0), *(&D_80074536 + temp_v0), 0x38, 0x10, 0, 0, 0xE4), *(&D_80074538 + temp_v1), *(&D_8007453A + temp_v1), 0x38, 0x10, 0, 0x10, 0xE3);
    if (D_8012D8D0 != 5) {
        if (D_8012D8D0 < 6) {
            var_a2 = 0x7C;
            if (D_8012D8D0 != 4) {
                var_a3 = 0x40;
            } else {
                var_a3 = 0xC0;
            }
        } else {
            var_a2 = 0x7C;
            if (D_8012D8D0 < 8) {
                var_a2 = 0x50;
                var_a3 = 0xC0;
            } else {
                var_a3 = 0x40;
            }
        }
    } else {
        var_a2 = 0xD0;
        var_a3 = 0xC0;
    }
    temp_a1_2 = func_80029278(arg0, func_80029278(arg0, temp_a1, var_a2, var_a3, 0x48, 0x10, 0xB8, 0, 0xE5), 0x10, 0x30, 0x48, 0x10, 0xB8, 0x10, 0xE6);
    var_a2_2 = 0xE8;
    if ((0x4A >> D_8012D8D0) & 1) {
        var_a3_2 = 0x30;
    } else {
        var_a2_2 = 0x10;
        var_a3_2 = 0xA8;
    }
    var_a1 = func_80029278(arg0, temp_a1_2, var_a2_2, var_a3_2, 0x48, 0x10, 0xB8, 0x20, 0xE7);
    if ((u32) (D_801E91E0 + 0xF) < 0x1FU) {
        var_s2 = 0;
        var_v1 = 0 * 4;
        do {
            temp_s0 = D_8012D8D0 * 0x14;
            temp_s1 = temp_s0 + (var_v1 + &D_800743F4);
            temp_s0_2 = temp_s0 + (var_v1 + &D_80074494);
            var_s2 += 1;
            var_a1 = func_8002F0D0(arg0, func_8002F0D0(arg0, func_8002F0D0(arg0, var_a1, 0, M2C_FIELD(temp_s1, s16 *, 0), (s32) M2C_FIELD(temp_s1, s16 *, 2), (s32) M2C_FIELD(temp_s0_2, s16 *, 0), (s32) M2C_FIELD(temp_s0_2, s16 *, 2), 0, 0, 0), 1, M2C_FIELD(temp_s1, s16 *, 0) - 1, (s32) M2C_FIELD(temp_s1, s16 *, 2), M2C_FIELD(temp_s0_2, s16 *, 0) - 1, (s32) M2C_FIELD(temp_s0_2, s16 *, 2), 0, 0, 0), 1, M2C_FIELD(temp_s1, s16 *, 0) + 1, (s32) M2C_FIELD(temp_s1, s16 *, 2), M2C_FIELD(temp_s0_2, s16 *, 0) + 1, (s32) M2C_FIELD(temp_s0_2, s16 *, 2), 0, 0, 0);
            var_v1 = var_s2 * 4;
        } while (var_s2 < 5);
    }
    return var_a1;
}
