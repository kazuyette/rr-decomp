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

extern M2C_UNK D_80072E80;
extern s32 D_80072E8C;
extern u16 D_8007B1E8;
extern M2C_UNK D_8007C258;
extern s32 D_8007C4D8;
extern s32 D_8012CD98;
extern s32 D_8012CF70;
extern s32 D_8012CF80;
extern s32 D_8012CF88;
extern s32 D_8012CFA8;
extern s32 D_80173180;
extern u16 D_801D77D0;
extern M2C_UNK D_801D80BC;
extern s32 D_801D80F0;
extern M2C_UNK D_801D9068;
extern s32 D_801D906C;
extern s32 D_801D9070;
extern s32 D_801D9074;
extern M2C_UNK D_801D9078;
extern s32 D_801D907C;
extern s32 D_801D9080;
extern u32 D_801E90A0;

void func_8002BBA0(u32 arg0, void *arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    M2C_UNK *temp_a1_3;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s2;
    s32 var_s6;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    void *temp_v0;

    var_s6 = M2C_FIELD(arg1, s32 *, 8);
    switch (arg0) {
    case 0:
        temp_v0 = (func_8002BA20(arg1) * 0x10) + D_80173180;
        temp_a2 = M2C_FIELD(temp_v0, s32 *, 4);
        temp_a3 = M2C_FIELD(temp_v0, s32 *, 8);
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(temp_v0, s32 *, 0);
        M2C_FIELD(&D_801D9068, s32 *, 4) = temp_a2;
        M2C_FIELD(&D_801D9068, s32 *, 8) = temp_a3;
        M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(temp_v0, s32 *, 0xC);
        var_v0 = func_8002BB50(func_8002BAE0(&D_801D9068, arg1 + 0x10, temp_a2, temp_a3) * 2);
        if (var_v0 < 0) {
            var_v0 += 0x7F;
        }
        temp_v1 = D_801D906C - (var_v0 >> 7);
        D_801D906C = temp_v1;
        temp_a0 = M2C_FIELD(arg1, s32 *, 0x10) - M2C_FIELD(&D_801D9068, s32 *, 0);
        sp10 = temp_a0;
        sp14 = M2C_FIELD(arg1, s32 *, 0x14) - temp_v1;
        var_s6 = D_801D9074;
        temp_a1 = M2C_FIELD(arg1, s32 *, 0x18) - D_801D9070;
        sp18 = temp_a1;
        temp_lo = sp10 * sp10;
        D_801D907C = 0x400 - func_800187A0(temp_a0, temp_a1);
        M2C_FIELD(&D_801D9078, s32 *, 0) = (s32) (0x400 - func_800187A0(sp14, SquareRoot(temp_lo + (sp18 * sp18), temp_lo) >> 6));
        D_801D9080 = 0;
        break;
    case 1:
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x18);
        M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0x1C);
        D_801D906C -= 0x18;
        M2C_FIELD(&D_801D9078, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0x20);
        M2C_FIELD(&D_801D9078, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 0x24);
        M2C_FIELD(&D_801D9078, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x28);
        M2C_FIELD(&D_801D9078, M2C_UNK **, 0xC) = (M2C_UNK *) M2C_FIELD(arg1, M2C_UNK **, 0x2C);
        D_801D9080 -= D_8012CD98 * 2;
        break;
    case 2:
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x18);
        M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0x1C);
        M2C_FIELD(&D_801D9078, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0x20);
        M2C_FIELD(&D_801D9078, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 0x24);
        M2C_FIELD(&D_801D9078, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x28);
        M2C_FIELD(&D_801D9078, M2C_UNK **, 0xC) = (M2C_UNK *) M2C_FIELD(arg1, M2C_UNK **, 0x2C);
        D_801D906C -= 0x58;
        var_v1 = (s32) ((s32) (rsin(D_801D907C, &D_801D9078) * 3) / 4) / 8;
        if (var_v1 < 0) {
            var_v1 += 3;
        }
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) ((var_v1 >> 2) + M2C_FIELD(&D_801D9068, s32 *, 0));
        temp_v1_2 = rcos(D_801D907C) * 3;
        var_v0_2 = temp_v1_2 >> 2;
        if (temp_v1_2 < 0) {
            var_v0_2 = (s32) (temp_v1_2 + 3) >> 2;
        }
        var_v0_3 = var_v0_2 / 8;
        if (var_v0_3 < 0) {
            var_v0_3 += 3;
        }
        D_801D9080 = 0;
        temp_a0_2 = M2C_FIELD(&D_801D9078, s32 *, 0);
        D_801D9070 += var_v0_3 >> 2;
        M2C_FIELD(&D_801D9078, s32 *, 0) = (s32) (temp_a0_2 + 0x400);
        D_801D906C -= 0x800;
        M2C_FIELD(&D_801D9078, s32 *, 0) = (s32) (temp_a0_2 + 0x360);
        break;
    case 3:
        if (arg0 != D_801E90A0) {
            var_v0_4 = M2C_FIELD(arg1, s32 *, 0xA8);
            goto block_19;
        }
        if (D_801D77D0 == 0) {
            var_v0_5 = func_80019CA8(D_8007C4D8, M2C_FIELD(arg1, s32 *, 0xA8));
            if (var_v0_5 < 0) {
                var_v0_5 += 3;
            }
            var_v0_4 = (var_v0_5 >> 2) + D_8007C4D8;
block_19:
            D_8007C4D8 = var_v0_4;
        }
        var_s2 = func_80019CA8(D_8007C4D8, M2C_FIELD(arg1, s32 *, 0x24));
        var_v0_6 = var_s2 < -0x400;
        if (var_s2 >= 0x401) {
            var_s2 = 0x800 - var_s2;
            var_v0_6 = var_s2 < -0x400;
        }
        if (var_v0_6 != 0) {
            var_s2 = -0x800 - var_s2;
        }
        temp_lo_2 = var_s2 / 6;
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x18);
        M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0x1C);
        M2C_FIELD(&D_801D9078, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0x20);
        M2C_FIELD(&D_801D9078, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 0x24);
        M2C_FIELD(&D_801D9078, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x28);
        M2C_FIELD(&D_801D9078, M2C_UNK **, 0xC) = (M2C_UNK *) M2C_FIELD(arg1, M2C_UNK **, 0x2C);
        temp_a1_2 = M2C_FIELD(&D_801D9078, s32 *, 0);
        temp_s1 = ((((0x50 - D_8012CF70) - D_8012CF80) - D_8012CFA8) - D_8012CF88) + temp_a1_2;
        M2C_FIELD(&D_801D9078, s32 *, 0) = temp_s1;
        temp_s0 = (s32) (rcos(temp_s1, temp_a1_2) * 0xF0) / 4096;
        var_v1_2 = rsin(temp_s1) * 0x1E0;
        if (var_v1_2 < 0) {
            var_v1_2 += 0xFFF;
        }
        D_801D906C -= var_v1_2 >> 0xC;
        var_v1_3 = temp_s0 * rsin(D_8007C4D8 - temp_lo_2);
        if (var_v1_3 < 0) {
            var_v1_3 += 0xFFF;
        }
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) (M2C_FIELD(&D_801D9068, s32 *, 0) - (var_v1_3 >> 0xC));
        var_v1_4 = temp_s0 * rcos(D_8007C4D8 - temp_lo_2);
        if (var_v1_4 < 0) {
            var_v1_4 += 0xFFF;
        }
        D_801D9080 = 0;
        D_801D9070 -= var_v1_4 >> 0xC;
        D_801D907C = D_8007C4D8;
        break;
    case 4:
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(&D_80072E80, s32 *, 0);
        M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(&D_80072E80, s32 *, 4);
        M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(&D_80072E80, s32 *, 8);
        M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(&D_80072E80, s32 *, 0xC);
        M2C_FIELD(&D_801D9078, s32 *, 0) = 0x400;
        D_801D9080 = 0;
        D_801D906C -= 0x800;
        D_801D907C = D_80072E8C;
        break;
    case 5:
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x18);
        M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0x1C);
        temp_a1_3 = M2C_FIELD(arg1, M2C_UNK **, 0x2C);
        M2C_FIELD(&D_801D9068, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x20);
        M2C_FIELD(&D_801D9068, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x24);
        M2C_FIELD(&D_801D9068, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 0x28);
        M2C_FIELD(&D_801D9068, M2C_UNK **, 0x1C) = temp_a1_3;
        D_801D906C -= 0x10;
        rsin(D_8007B1E8 * 0x10, temp_a1_3);
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) ((rsin(D_801D907C + 0x80) / 24) + M2C_FIELD(&D_801D9068, s32 *, 0));
        temp_v0_2 = rcos(D_801D907C + 0x80) / 24;
        D_801D9080 = 0;
        D_801D907C += 0x800;
        M2C_FIELD(&D_801D9068, s32 *, 0x10) = (s32) (M2C_FIELD(&D_801D9068, s32 *, 0x10) - 8);
        D_801D9070 += temp_v0_2;
        break;
    case 15:
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(&D_801D80BC, s32 *, 0);
        M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(&D_801D80BC, s32 *, 4);
        M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(&D_801D80BC, s32 *, 8);
        M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(&D_801D80BC, s32 *, 0xC);
        M2C_FIELD(&D_801D9078, s32 *, 0) = 0x400;
        D_801D9080 = 0;
        D_801D906C -= 0x1000;
        D_801D907C = 0x800 - D_801D80F0;
        break;
    }
    func_800186C8();
    if ((arg0 != 1) || (arg1 != &D_8007C258)) {
        func_8002128C(&D_8007C258, 1);
    }
    func_800377B4(var_s6);
    D_801E90A0 = arg0;
}
