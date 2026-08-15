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

extern M2C_UNK D_80077128;

s32 *func_80036D30(s32 *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *sp18;
    M2C_UNK *var_s2_2;
    s32 *temp_a1;
    s32 *temp_v0_3;
    s32 *var_s1;
    s32 *var_s3;
    s32 temp_a3;
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_fp;
    s32 var_s4;
    s32 var_s5;
    s32 var_s7;
    s32 var_s7_2;
    void *temp_a2;
    void *temp_s6;
    void *var_a1;
    void *var_a2;
    void *var_s2;

    var_s3 = arg0;
    temp_a2 = (arg2 * 0x10) + M2C_FIELD(arg1, s32 *, 8);
    sp18 = temp_a2;
    var_fp = M2C_FIELD(temp_a2, s32 *, 0xC);
    temp_s6 = arg1 + 0xA4;
    if (M2C_FIELD(arg1, s32 *, 0x24) != 0) {
        func_80043738(temp_a2);
        func_80043794();
    }
    var_s7 = 0;
    if (M2C_FIELD(sp18, s16 *, 0) > 0) {
        var_s2 = var_fp + 0x22;
        var_s1 = var_s3;
        do {
            var_s7 += 1;
            if (func_8004006C(var_fp, arg1) > 0) {
                temp_v0 = (s32) M2C_FIELD(arg1, s32 *, 0x2C) >> M2C_FIELD(arg1, s32 *, 0x20);
                M2C_FIELD(arg1, s32 *, 0x2C) = temp_v0;
                if ((u32) (temp_v0 - 1) < 0x1BFU) {
                    M2C_FIELD(var_s1, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x34);
                    M2C_FIELD(var_s1, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x38);
                    M2C_FIELD(var_s1, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 0x3C);
                    M2C_FIELD(var_s1, s32 *, 0x20) = (s32) M2C_FIELD(arg1, s32 *, 0x40);
                    M2C_FIELD(var_s1, s32 *, 0xC) = (s32) (arg3 + M2C_FIELD(var_s2, s32 *, -0xA));
                    M2C_FIELD(var_s1, s32 *, 0x14) = (s32) M2C_FIELD(var_s2, s32 *, -6);
                    M2C_FIELD(var_s1, u16 *, 0x1C) = (u16) M2C_FIELD(var_s2, u16 *, -2);
                    M2C_FIELD(var_s1, u16 *, 0x24) = (u16) M2C_FIELD(var_s2, u16 *, 2);
                    gte_dpcs(arg1 + 0x10, M2C_FIELD(arg1, s32 *, 0x28), var_s3 + 4);
                    *var_s3 = 0x09000000;
                    M2C_FIELD(var_s1, s8 *, 7) = 0x2C;
                    temp_a1 = var_s1;
                    var_s1 += 0x28;
                    var_s3 += 0x28;
                    AddPrim(M2C_FIELD(arg1, s32 *, 0) - (((M2C_FIELD(var_s2, s16 *, 0) + M2C_FIELD(arg1, s32 *, 0x2C)) * 4) + 0x200), temp_a1);
                }
            }
            var_s2 += 0x28;
            var_fp += 0x28;
        } while (var_s7 < M2C_FIELD(sp18, s16 *, 0));
    }
    M2C_FIELD(arg1, s8 *, 0x13) = 0x2C;
    var_s7_2 = 0;
    if (M2C_FIELD(sp18, s16 *, 2) > 0) {
        var_s2_2 = var_fp + 0x28;
        do {
            temp_v0_2 = func_80040140(var_fp, arg1);
            if ((temp_v0_2 != 0) && (func_8003FFF8(arg1) != 0)) {
                if (temp_v0_2 < M2C_FIELD(arg1, s32 *, 0x1C)) {
                    if ((((s16) M2C_FIELD(arg1, s32 *, 0x34) < 0x141) || ((s16) M2C_FIELD(arg1, s32 *, 0x38) < 0x141) || ((s16) M2C_FIELD(arg1, s32 *, 0x3C) < 0x141) || ((s16) M2C_FIELD(arg1, s32 *, 0x40) < 0x141)) && ((M2C_FIELD(arg1, s16 *, 0x36) < 0xF1) || (M2C_FIELD(arg1, s16 *, 0x3A) < 0xF1) || (M2C_FIELD(arg1, s16 *, 0x3E) < 0xF1) || (M2C_FIELD(arg1, s16 *, 0x42) < 0xF1)) && (((s16) M2C_FIELD(arg1, s32 *, 0x34) >= 0) || ((s16) M2C_FIELD(arg1, s32 *, 0x38) >= 0) || ((s16) M2C_FIELD(arg1, s32 *, 0x3C) >= 0) || ((s16) M2C_FIELD(arg1, s32 *, 0x40) >= 0))) {
                        if (M2C_FIELD(arg1, s16 *, 0x36) < 0) {
                            var_a1 = arg1 + 0x7C;
                            if (M2C_FIELD(arg1, s16 *, 0x3A) < 0) {
                                var_a2 = arg1 + 0x8C;
                                if (M2C_FIELD(arg1, s16 *, 0x3E) < 0) {
                                    if (M2C_FIELD(arg1, s16 *, 0x42) >= 0) {
                                        goto block_29;
                                    }
                                } else {
                                    goto block_31;
                                }
                            } else {
                                goto block_30;
                            }
                        } else {
block_29:
                            var_a1 = arg1 + 0x7C;
block_30:
                            var_a2 = arg1 + 0x8C;
block_31:
                            func_8003FD24(arg1 + 0x6C, var_a1, var_a2, arg1 + 0x9C);
                            if ((M2C_FIELD(arg1, s32 *, 0x6C) >= 0x140) || (M2C_FIELD(arg1, s32 *, 0x7C) >= 0x140) || (M2C_FIELD(arg1, s32 *, 0x8C) >= 0x140) || (M2C_FIELD(arg1, s32 *, 0x9C) >= 0x140)) {
                                goto block_35;
                            }
                        }
                    }
                } else {
block_35:
                    temp_a3 = temp_v0_2 >> 0xA;
                    var_s5 = arg4 - temp_a3;
                    if (var_s5 < 0) {
                        var_s5 = 0;
                    }
                    var_s4 = arg5 - temp_a3;
                    if (var_s4 < 0) {
                        var_s4 = 0;
                    }
                    temp_s1 = temp_v0_2 >> M2C_FIELD(arg1, s32 *, 0x20);
                    if ((u32) (temp_s1 - 1) < 0x1BFU) {
                        M2C_FIELD(temp_s6, u16 *, 0x28) = (u16) M2C_FIELD(var_s2_2, u16 *, -0x10);
                        M2C_FIELD(temp_s6, u16 *, 0x2A) = (u16) M2C_FIELD(var_s2_2, u16 *, -0xC);
                        M2C_FIELD(temp_s6, u16 *, 0x2C) = (u16) M2C_FIELD(var_s2_2, u16 *, -8);
                        M2C_FIELD(temp_s6, u16 *, 0x2E) = (u16) M2C_FIELD(var_s2_2, u16 *, -4);
                        M2C_FIELD(temp_s6, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 0) - (((temp_s1 + M2C_FIELD(var_s2_2, s16 *, -6)) * 4) + 0x200));
                        M2C_FIELD(arg1, u16 *, 0xA4) = (u16) M2C_FIELD(var_s2_2, u16 *, -0xE);
                        M2C_FIELD(temp_s6, u16 *, 2) = (u16) M2C_FIELD(var_s2_2, u16 *, -0xA);
                        gte_dpcs(arg1 + 0x10, M2C_FIELD(arg1, s32 *, 0x28), temp_s6 + 0x70, temp_a3);
                        func_8004617C(var_s3, 0, 1, 0, &D_80077128);
                        AddPrim(M2C_FIELD(temp_s6, s32 *, 4), var_s3);
                        temp_v0_3 = func_80044098(var_s3 + 0xC, temp_s6, var_s5, var_s4);
                        func_8004617C(temp_v0_3, 0, 1, 0, var_s2_2);
                        var_s3 = temp_v0_3 + 0xC;
                        AddPrim(M2C_FIELD(temp_s6, s32 *, 4), temp_v0_3);
                    }
                }
            }
            var_s7_2 += 1;
            var_s2_2 += 0x30;
            var_fp += 0x30;
        } while (var_s7_2 < M2C_FIELD(sp18, s16 *, 2));
    }
    if (M2C_FIELD(arg1, s32 *, 0x24) != 0) {
        func_80043738();
        func_80043794();
    }
    return var_s3;
}
