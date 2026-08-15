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

extern u16 D_8007B1E8;
extern M2C_UNK D_8007C258;
extern s32 D_8012CD98;
extern s32 D_80173180;
extern u16 D_801D34F8;
extern M2C_UNK D_801D80BC;
extern s32 D_801D80F0;
extern M2C_UNK D_801D9068;
extern s32 D_801D906C;
extern s32 D_801D9070;
extern M2C_UNK D_801D9078;
extern s32 D_801D907C;
extern s32 D_801D9080;

void func_8002C500(u32 arg0, void *arg1) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    M2C_UNK *temp_a1_2;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_lo;
    s32 temp_s1;
    s32 temp_s5;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_s1;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    void *temp_v0;

    temp_s5 = M2C_FIELD(arg1, s32 *, 8);
    switch (arg0) {
    case 0:
        temp_v0 = (func_8002BA20(arg1) * 0x10) + D_80173180;
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(temp_v0, s32 *, 0);
        M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(temp_v0, s32 *, 4);
        M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(temp_v0, s32 *, 8);
        M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(temp_v0, s32 *, 0xC);
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) (((s32) (M2C_FIELD(arg1, s32 *, 0x10) - M2C_FIELD(&D_801D9068, s32 *, 0)) / 2) + M2C_FIELD(&D_801D9068, s32 *, 0));
        D_801D906C += (s32) (M2C_FIELD(arg1, s32 *, 0x14) - D_801D906C) / 2;
        temp_a2 = M2C_FIELD(&D_801D9068, s32 *, 8);
        M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) (((s32) (M2C_FIELD(arg1, s32 *, 0x18) - temp_a2) / 2) + temp_a2);
        var_v0 = func_8002BB50(func_8002BAE0(&D_801D9068, arg1 + 0x10, temp_a2) * 2);
        if (var_v0 < 0) {
            var_v0 += 0x7F;
        }
        temp_v1 = D_801D906C - (var_v0 >> 7);
        D_801D906C = temp_v1;
        temp_a0 = M2C_FIELD(arg1, s32 *, 0x10) - M2C_FIELD(&D_801D9068, s32 *, 0);
        sp10 = temp_a0;
        sp14 = M2C_FIELD(arg1, s32 *, 0x14) - temp_v1;
        temp_a1 = M2C_FIELD(arg1, s32 *, 0x18) - M2C_FIELD(&D_801D9068, s32 *, 8);
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
        D_801D9080 = -D_801D9080;
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
        D_801D906C -= 0x40;
        var_v1 = rsin(D_801D907C, &D_801D9078);
        if (var_v1 < 0) {
            var_v1 += 0xF;
        }
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) (M2C_FIELD(&D_801D9068, s32 *, 0) - (var_v1 >> 4));
        var_v1_2 = rcos(D_801D907C);
        if (var_v1_2 < 0) {
            var_v1_2 += 0xF;
        }
        D_801D9080 = 0;
        D_801D9070 -= var_v1_2 >> 4;
        M2C_FIELD(&D_801D9078, s32 *, 0) = (s32) (M2C_FIELD(&D_801D9078, s32 *, 0) + 0x40);
        break;
    case 3:
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0x10);
        M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x18);
        M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0x1C);
        temp_a1_2 = M2C_FIELD(arg1, M2C_UNK **, 0x2C);
        M2C_FIELD(&D_801D9068, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x20);
        M2C_FIELD(&D_801D9068, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x24);
        M2C_FIELD(&D_801D9068, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 0x28);
        M2C_FIELD(&D_801D9068, M2C_UNK **, 0x1C) = temp_a1_2;
        D_801D906C -= 0x40;
        var_s1 = rsin(D_8007B1E8 * 0x10, temp_a1_2);
        if (var_s1 < 0) {
            var_s1 += 0x1F;
        }
        temp_s1 = var_s1 >> 5;
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) ((rsin(temp_s1 + D_801D907C) / 12) + M2C_FIELD(&D_801D9068, s32 *, 0));
        temp_v0_2 = rcos(temp_s1 + D_801D907C) / 12;
        D_801D9080 = 0;
        D_801D907C += 0x800;
        M2C_FIELD(&D_801D9068, s32 *, 0x10) = (s32) (M2C_FIELD(&D_801D9068, s32 *, 0x10) + 0x10);
        D_801D9070 += temp_v0_2;
        break;
    case 4:
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(&D_801D80BC, s32 *, 0);
        M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(&D_801D80BC, s32 *, 4);
        M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(&D_801D80BC, s32 *, 8);
        M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(&D_801D80BC, s32 *, 0xC);
        M2C_FIELD(&D_801D9078, s32 *, 0) = 0x400;
        D_801D9080 = 0;
        D_801D906C -= 0x1000;
        D_801D907C = 0x800 - D_801D80F0;
        break;
    case 5:
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
    }
    func_800186C8();
    if (((arg0 != 1) || (arg1 != &D_8007C258)) && (D_801D34F8 != 0x1A) && (D_801D34F8 != 5)) {
        func_8002128C(&D_8007C258, 1);
    }
    func_800377B4(temp_s5);
}
