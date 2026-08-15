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

extern M2C_UNK D_800747FC;
extern s32 D_8007C260;
extern s32 D_8007C268;
extern s32 D_8007C26C;
extern s32 D_8007C270;
extern s32 D_8012CDE8;
extern s16 D_801D3578;
extern s16 D_801D357A;
extern s16 D_801D357E;
extern s16 D_801D3580;
extern M2C_UNK D_801D80A8;
extern s32 D_801D80BC;
extern s32 D_801D80C0;
extern s32 D_801D80C4;
extern s32 D_801D8120;
extern s32 D_801E90E0;

void func_800382A0(void) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 var_a1;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a1_4;
    s32 temp_a1_5;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a3;
    s32 temp_a3_2;
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_s2;
    s32 var_s3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v1;
    s32 var_v1_2;
    u32 var_v0_3;

    var_s2 = 4;
    temp_a1 = D_8007C268 - D_801D80BC;
    sp20 = temp_a1;
    temp_a2 = D_8007C26C - D_801D80C0;
    sp24 = temp_a2;
    temp_a3 = D_8007C270 - D_801D80C4;
    sp28 = temp_a3;
    if ((temp_a1 < 0x1001) && (temp_a3 < 0x1001) && (temp_a1 >= -0x1000) && (temp_a3 >= -0x1000)) {
        var_v0 = temp_a1 * temp_a1;
        if (var_v0 < 0) {
            var_v0 += 3;
        }
        var_v1 = temp_a2 * temp_a2;
        temp_a1_2 = var_v0 >> 2;
        if (var_v1 < 0) {
            var_v1 += 3;
        }
        temp_v0 = var_v1 >> 2;
        var_a0 = temp_a3 * temp_a3;
        if (var_a0 < 0) {
            var_a0 += 3;
        }
        temp_s1 = SquareRoot(temp_a1_2 + ((s32) (temp_v0 + ((u32) temp_v0 >> 0x1F)) >> 1) + (var_a0 >> 2), temp_a1_2, temp_a2, temp_a3);
        if (D_801D8120 == 0) {
            var_v0_2 = temp_s1 >> 0xA;
            if (temp_s1 < 0x800) {
                snd_play_se(0x11);
                func_80032F50(5, &D_8007C268 - 0x10);
                D_801D8120 = 1;
                goto block_13;
            }
        } else {
block_13:
            var_v0_2 = temp_s1 >> 0xA;
        }
        var_a1 = 0x64 - var_v0_2;
        if (var_a1 >= 0x65) {
            var_a1 = 0x64;
        }
        var_v0_3 = (u32) var_a1 >> 0x1F;
        if (var_a1 < 0) {
            goto block_17;
        }
    } else {
block_17:
        var_a1 = 0;
        var_v0_3 = 0U >> 0x1F;
    }
    var_a2 = var_a1 - D_8012CDE8;
    temp_a3_2 = (s32) (var_a1 + var_v0_3) >> 1;
    if (var_a2 < -0x14) {
        var_a2 = -0x14;
    }
    if (var_a2 >= 0x15) {
        var_a2 = 0x14;
    }
    D_801D3578 = var_a1;
    D_801D357E = (s16) temp_a3_2;
    D_8012CDE8 = (s32) var_a1;
    temp_v0_2 = ((var_a2 / 2) + 0x3C) << 7;
    D_801D357A = temp_v0_2;
    D_801D3580 = temp_v0_2;
    if (((((s32) ((D_801E90E0 << 0x10) + D_8007C260) % (s32) (D_801E90E0 << 8)) & ~0xFF) == 0x1100) && (M2C_FIELD(&D_801D80A8, s32 *, 0) != &D_800747FC)) {
        func_80037F64(D_8007C260, var_a1, var_a2, temp_a3_2);
    }
    var_a0_2 = func_800373BC(D_8007C260, M2C_FIELD(&D_801D80A8, s32 *, 0x74));
    if (M2C_FIELD(&D_801D80A8, s32 *, 0) == &D_800747FC) {
        var_a0_2 = 0;
    }
    if (var_a0_2 < 0) {
        var_s3 = 1;
    } else if (var_a0_2 < 0x800) {
        var_s3 = 2;
    } else {
        var_s3 = 0x10;
        if (var_a0_2 < 0x1000) {
            var_s3 = 4;
        }
    }
    temp_v1 = M2C_FIELD(&D_801D80A8, s16 *, 8);
    if (temp_v1 == -1) {
        do {
            func_80038018(&D_801D80A8);
        } while (M2C_FIELD(&D_801D80A8, s16 *, 8) == -1);
    }
    switch (temp_v1) {
    case 1:
        temp_v0_3 = var_s3 + M2C_FIELD(&D_801D80A8, s32 *, 0xC);
        M2C_FIELD(&D_801D80A8, s32 *, 0xC) = temp_v0_3;
        if (temp_v0_3 >= M2C_FIELD(&D_801D80A8, s32 *, 0x10)) {
            M2C_FIELD(&D_801D80A8, s16 *, 8) = -1;
            M2C_FIELD(&D_801D80A8, s32 *, 0xC) = (s32) M2C_FIELD(&D_801D80A8, s32 *, 0x10);
        }
        temp_a0 = M2C_FIELD(&D_801D80A8, s32 *, 0x10) - M2C_FIELD(&D_801D80A8, s32 *, 0xC);
        sp10 = (s32) ((temp_a0 * M2C_FIELD(&D_801D80A8, s32 *, 0x24)) + (M2C_FIELD(&D_801D80A8, s32 *, 0xC) * M2C_FIELD(&D_801D80A8, s32 *, 0x34))) / (s32) M2C_FIELD(&D_801D80A8, s32 *, 0x10);
        sp14 = (s32) ((temp_a0 * M2C_FIELD(&D_801D80A8, s32 *, 0x28)) + (M2C_FIELD(&D_801D80A8, s32 *, 0xC) * M2C_FIELD(&D_801D80A8, s32 *, 0x38))) / (s32) M2C_FIELD(&D_801D80A8, s32 *, 0x10);
        sp18 = (s32) ((temp_a0 * M2C_FIELD(&D_801D80A8, s32 *, 0x2C)) + (M2C_FIELD(&D_801D80A8, s32 *, 0xC) * M2C_FIELD(&D_801D80A8, s32 *, 0x3C))) / (s32) M2C_FIELD(&D_801D80A8, s32 *, 0x10);
        if (M2C_FIELD(&D_801D80A8, s32 *, 0xC) < 0x20) {
            var_v0_4 = M2C_FIELD(&D_801D80A8, s32 *, 0xC);
            if (M2C_FIELD(&D_801D80A8, s32 *, 0xC) < 0) {
                var_v0_4 = M2C_FIELD(&D_801D80A8, s32 *, 0xC) + 3;
            }
            goto block_48;
        }
        temp_v0_4 = M2C_FIELD(&D_801D80A8, s32 *, 0x10) - M2C_FIELD(&D_801D80A8, s32 *, 0xC);
        if ((M2C_FIELD(&D_801D80A8, s32 *, 0x10) - 0x20) < M2C_FIELD(&D_801D80A8, s32 *, 0xC)) {
            var_v1_2 = temp_v0_4 >> 2;
            if (temp_v0_4 < 0) {
                var_v0_4 = temp_v0_4 + 3;
block_48:
                var_v1_2 = var_v0_4 >> 2;
            }
            var_s2 = 0xC - var_v1_2;
        } else {
            var_s2 = 4;
        }
        break;
    case 2:
        temp_v0_5 = var_s3 + M2C_FIELD(&D_801D80A8, s32 *, 0xC);
        M2C_FIELD(&D_801D80A8, s32 *, 0xC) = temp_v0_5;
        var_s2 = 0xC;
        if (temp_v0_5 >= M2C_FIELD(&D_801D80A8, s32 *, 0x10)) {
            M2C_FIELD(&D_801D80A8, s16 *, 8) = -1;
        }
        sp10 = M2C_FIELD(&D_801D80A8, s32 *, 0x34);
        sp14 = M2C_FIELD(&D_801D80A8, s32 *, 0x38);
        sp18 = M2C_FIELD(&D_801D80A8, s32 *, 0x3C);
        sp1C = M2C_FIELD(&D_801D80A8, s32 *, 0x40);
        break;
    }
    temp_a2_2 = M2C_FIELD(&D_801D80A8, s32 *, 0x18);
    M2C_FIELD(&D_801D80A8, s32 *, 0x14) = (s32) (((s32) (sp10 - M2C_FIELD(&D_801D80A8, s32 *, 0x14)) / var_s2) + M2C_FIELD(&D_801D80A8, s32 *, 0x14));
    M2C_FIELD(&D_801D80A8, s32 *, 0x18) = (s32) (((s32) (sp14 - temp_a2_2) / var_s2) + temp_a2_2);
    M2C_FIELD(&D_801D80A8, s32 *, 0x1C) = (s32) (((s32) (sp18 - M2C_FIELD(&D_801D80A8, s32 *, 0x1C)) / var_s2) + M2C_FIELD(&D_801D80A8, s32 *, 0x1C));
    if (M2C_FIELD(&D_801D80A8, s32 *, 0x64) != M2C_FIELD(&D_801D80A8, s32 *, 0x44)) {
        temp_a1_3 = ((var_s3 * M2C_FIELD(&D_801D80A8, s32 *, 0x54)) + M2C_FIELD(&D_801D80A8, s32 *, 0x44)) & 0xFFF;
        M2C_FIELD(&D_801D80A8, s32 *, 0x44) = temp_a1_3;
        if (func_80038264(M2C_FIELD(&D_801D80A8, s32 *, 0x64), temp_a1_3, temp_a2_2, M2C_FIELD(&D_801D80A8, s32 *, 0x64)) < (var_s3 * 0x10)) {
            M2C_FIELD(&D_801D80A8, s32 *, 0x44) = (s32) M2C_FIELD(&D_801D80A8, s32 *, 0x64);
        }
    }
    if (M2C_FIELD(&D_801D80A8, s32 *, 0x68) != M2C_FIELD(&D_801D80A8, s32 *, 0x48)) {
        temp_a1_4 = ((var_s3 * M2C_FIELD(&D_801D80A8, s32 *, 0x58)) + M2C_FIELD(&D_801D80A8, s32 *, 0x48)) & 0xFFF;
        M2C_FIELD(&D_801D80A8, s32 *, 0x48) = temp_a1_4;
        if (func_80038264(M2C_FIELD(&D_801D80A8, s32 *, 0x68), temp_a1_4) < (var_s3 * 0x10)) {
            M2C_FIELD(&D_801D80A8, s32 *, 0x48) = (s32) M2C_FIELD(&D_801D80A8, s32 *, 0x68);
        }
    }
    if (M2C_FIELD(&D_801D80A8, s32 *, 0x6C) != M2C_FIELD(&D_801D80A8, s32 *, 0x4C)) {
        temp_a1_5 = ((var_s3 * M2C_FIELD(&D_801D80A8, s32 *, 0x5C)) + M2C_FIELD(&D_801D80A8, s32 *, 0x4C)) & 0xFFF;
        M2C_FIELD(&D_801D80A8, s32 *, 0x4C) = temp_a1_5;
        if (func_80038264(M2C_FIELD(&D_801D80A8, s32 *, 0x6C), temp_a1_5) < (var_s3 * 0x10)) {
            M2C_FIELD(&D_801D80A8, s32 *, 0x4C) = (s32) M2C_FIELD(&D_801D80A8, s32 *, 0x6C);
        }
    }
}
