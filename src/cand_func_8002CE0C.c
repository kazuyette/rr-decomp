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

extern M2C_UNK D_8007C258;
extern M2C_UNK D_801D9068;
extern s32 D_801D906C;
extern s32 D_801D9070;
extern s32 D_801D9078;
extern s32 D_801D907C;
extern s32 D_801D9080;
extern M2C_UNK D_801E90D0;
extern s32 D_801E90D4;
extern s32 D_801E90D8;

void func_8002CE0C(void *arg0, s32 arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_lo;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 var_a1;
    s32 var_a2;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;

    var_s0 = arg1;
    if (var_s0 < 0x96) {
        var_s0 = 0x96;
    }
    temp_s0 = 0xF0 - var_s0;
    func_800273B4(M2C_FIELD(arg0, s32 *, 8) - (temp_s0 * 2), &sp10);
    var_v0 = rsin(M2C_FIELD(arg0, s32 *, 0x24));
    if (var_v0 < 0) {
        var_v0 += 0x3F;
    }
    sp10 += var_v0 >> 6;
    var_v0_2 = rcos(M2C_FIELD(arg0, s32 *, 0x24));
    temp_s1 = temp_s0 << 5;
    if (var_v0_2 < 0) {
        var_v0_2 += 0x3F;
    }
    sp18 += var_v0_2 >> 6;
    var_a1 = (s32) (rsin(temp_s1) * 0x3C) / 100;
    if (var_a1 < 0) {
        var_a1 += 0xF;
    }
    sp10 += var_a1 >> 4;
    var_a2 = (s32) (rcos(temp_s1, var_a1) * 0x3C) / 100;
    if (var_a2 < 0) {
        var_a2 += 0xF;
    }
    temp_a3 = M2C_FIELD(&D_801E90D0, s32 *, 0);
    temp_a2 = (var_a2 >> 4) + sp18;
    sp18 = temp_a2;
    temp_a0 = sp14 - 0x3C;
    var_v0_3 = sp10 - temp_a3;
    sp14 = temp_a0;
    if (var_v0_3 < 0) {
        var_v0_3 += 0xF;
    }
    M2C_FIELD(&D_801E90D0, s32 *, 0) = (s32) ((var_v0_3 >> 4) + temp_a3);
    var_v0_4 = temp_a0 - D_801E90D4;
    if (var_v0_4 < 0) {
        var_v0_4 += 0xF;
    }
    D_801E90D4 += var_v0_4 >> 4;
    var_v0_5 = temp_a2 - D_801E90D8;
    if (var_v0_5 < 0) {
        var_v0_5 += 0xF;
    }
    D_801E90D8 += var_v0_5 >> 4;
    M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(&D_801E90D0, s32 *, 0);
    M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(&D_801E90D0, s32 *, 4);
    M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(&D_801E90D0, s32 *, 8);
    M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(&D_801E90D0, s32 *, 0xC);
    temp_a0_2 = M2C_FIELD(arg0, s32 *, 0x10) - M2C_FIELD(&D_801D9068, s32 *, 0);
    sp10 = temp_a0_2;
    sp14 = M2C_FIELD(arg0, s32 *, 0x14) - D_801D906C;
    temp_a1 = M2C_FIELD(arg0, s32 *, 0x18) - D_801D9070;
    sp18 = temp_a1;
    temp_lo = sp10 * sp10;
    D_801D907C = 0x400 - func_800187A0(temp_a0_2, temp_a1, M2C_FIELD(&D_801E90D0, s32 *, 0xC), temp_a3);
    temp_s0_2 = 0x400 - func_800187A0(sp14, SquareRoot(temp_lo + (sp18 * sp18), temp_lo) >> 6);
    D_801D9078 = temp_s0_2;
    D_801D9080 = 0;
    if (temp_s0_2 >= 0x51) {
        D_801D9078 = 0x50;
    }
    if (D_801D9078 < -0x50) {
        D_801D9078 = -0x50;
    }
    func_800186C8();
    func_8002128C(&D_8007C258, 1);
    func_800377B4(M2C_FIELD(arg0, s32 *, 8));
}
