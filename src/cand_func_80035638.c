/* cand_func_80035638.c -- one candidate function, decompiled by m2c.
 *
 * Second run at the seventy-four that matched under none of the five
 * pipelines. The C is unchanged: the point is not to hope for a different
 * result, it is that tools/whydiff.py now exists. These get built and
 * diagnosed before anything is sent back to INCLUDE_ASM, so that we learn
 * *how* they miss rather than only that they do.
 *
 * One function per file: GCC 2.7.2 allocates registers across the whole
 * translation unit, so a candidate measured alone is measured on its own
 * merits.
 */
#include "m2c_macros.h"

extern M2C_UNK D_80077128;

s32 *func_80035638(s32 *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *sp18;
    s32 sp20;
    s32 *temp_a1;
    s32 *temp_a1_2;
    s32 *temp_a1_3;
    s32 *temp_s2;
    s32 *temp_s2_2;
    s32 *temp_s3;
    s32 *temp_s3_2;
    s32 *temp_v0_3;
    s32 *var_s0;
    s32 *var_s0_2;
    s32 *var_s0_3;
    s32 *var_s2_2;
    s32 *var_s3;
    s32 *var_s3_2;
    s32 temp_a3;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 var_s2;
    s32 var_s4;
    s32 var_s4_2;
    s32 var_s4_3;
    s32 var_s4_4;
    s32 var_s4_5;
    s32 var_s5;
    void *temp_s6;
    void *temp_s7;
    void *var_a1;
    void *var_a2;

    sp20 = arg2;
    var_s3_2 = arg0;
    temp_s7 = (arg2 * 0x10) + M2C_FIELD(arg1, s32 *, 8);
    temp_s6 = arg1 + 0xA4;
    sp18 = M2C_FIELD(temp_s7, void **, 0xC);
    if (M2C_FIELD(arg1, s32 *, 0x24) != 0) {
        func_80043738();
        func_80043794();
    }
    var_s4 = 0;
    if (M2C_FIELD(temp_s7, s16 *, 0) > 0) {
        var_s0 = var_s3_2;
        do {
            var_s4 += 1;
            if (func_8004006C(sp18, arg1) > 0) {
                temp_v0 = (s32) M2C_FIELD(arg1, s32 *, 0x2C) >> M2C_FIELD(arg1, s32 *, 0x20);
                M2C_FIELD(arg1, s32 *, 0x2C) = temp_v0;
                if ((u32) (temp_v0 - 1) < 0x1BFU) {
                    M2C_FIELD(var_s0, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x34);
                    M2C_FIELD(var_s0, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x38);
                    M2C_FIELD(var_s0, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 0x3C);
                    M2C_FIELD(var_s0, s32 *, 0x20) = (s32) M2C_FIELD(arg1, s32 *, 0x40);
                    M2C_FIELD(var_s0, s32 *, 0xC) = (s32) (arg3 + M2C_FIELD(sp18, s32 *, 0x18));
                    M2C_FIELD(var_s0, s32 *, 0x14) = (s32) M2C_FIELD(sp18, s32 *, 0x1C);
                    M2C_FIELD(var_s0, u16 *, 0x1C) = (u16) M2C_FIELD(sp18, u16 *, 0x20);
                    M2C_FIELD(var_s0, u16 *, 0x24) = (u16) M2C_FIELD(sp18, u16 *, 0x24);
                    gte_dpcs(arg1 + 0x10, M2C_FIELD(arg1, s32 *, 0x28), var_s3_2 + 4);
                    *var_s3_2 = 0x09000000;
                    M2C_FIELD(var_s0, s8 *, 7) = 0x2C;
                    temp_a1 = var_s0;
                    var_s0 += 0x28;
                    var_s3_2 += 0x28;
                    AddPrim(M2C_FIELD(arg1, s32 *, 0) - (((M2C_FIELD(sp18, s16 *, 0x22) + M2C_FIELD(arg1, s32 *, 0x2C)) * 4) + 0x200), temp_a1);
                }
            }
            sp18 += 0x28;
        } while (var_s4 < M2C_FIELD(temp_s7, s16 *, 0));
    }
    M2C_FIELD(arg1, s8 *, 0x13) = 0x2C;
    var_s4_2 = 0;
    if (M2C_FIELD(temp_s7, s16 *, 2) > 0) {
        do {
            temp_v0_2 = func_80040140(sp18, arg1);
            if ((temp_v0_2 != 0) && (func_8003FFF8(arg1) != 0)) {
                if (temp_v0_2 < M2C_FIELD(arg1, s32 *, 0x1C)) {
                    if ((((s16) M2C_FIELD(arg1, s32 *, 0x34) < 0x141) || ((s16) M2C_FIELD(arg1, s32 *, 0x38) < 0x141) || ((s16) M2C_FIELD(arg1, s32 *, 0x3C) < 0x141) || ((s16) M2C_FIELD(arg1, s32 *, 0x40) < 0x141)) && ((M2C_FIELD(arg1, s16 *, 0x36) < 0xF1) || (M2C_FIELD(arg1, s16 *, 0x3A) < 0xF1) || (M2C_FIELD(arg1, s16 *, 0x3E) < 0xF1) || (M2C_FIELD(arg1, s16 *, 0x42) < 0xF1)) && (((s16) M2C_FIELD(arg1, s32 *, 0x34) >= 0) || ((s16) M2C_FIELD(arg1, s32 *, 0x38) >= 0) || ((s16) M2C_FIELD(arg1, s32 *, 0x3C) >= 0) || ((s16) M2C_FIELD(arg1, s32 *, 0x40) >= 0))) {
                        if (M2C_FIELD(arg1, s16 *, 0x36) < 0) {
                            var_a1 = arg1 + 0x7C;
                            if (M2C_FIELD(arg1, s16 *, 0x3A) < 0) {
                                var_a2 = arg1 + 0x8C;
                                if (M2C_FIELD(arg1, s16 *, 0x3E) < 0) {
                                    if (M2C_FIELD(arg1, s16 *, 0x42) >= 0) {
                                        goto block_28;
                                    }
                                } else {
                                    goto block_30;
                                }
                            } else {
                                goto block_29;
                            }
                        } else {
block_28:
                            var_a1 = arg1 + 0x7C;
block_29:
                            var_a2 = arg1 + 0x8C;
block_30:
                            func_8003FD24(arg1 + 0x6C, var_a1, var_a2, arg1 + 0x9C);
                            if ((M2C_FIELD(arg1, s32 *, 0x6C) >= 0x140) || (M2C_FIELD(arg1, s32 *, 0x7C) >= 0x140) || (M2C_FIELD(arg1, s32 *, 0x8C) >= 0x140) || (M2C_FIELD(arg1, s32 *, 0x9C) >= 0x140)) {
                                goto block_34;
                            }
                        }
                    }
                } else {
block_34:
                    temp_a3 = temp_v0_2 >> 0xA;
                    var_s5 = arg4 - temp_a3;
                    if (var_s5 < 0) {
                        var_s5 = 0;
                    }
                    var_s2 = arg5 - temp_a3;
                    if (var_s2 < 0) {
                        var_s2 = 0;
                    }
                    temp_s0 = temp_v0_2 >> M2C_FIELD(arg1, s32 *, 0x20);
                    if ((u32) (temp_s0 - 1) < 0x1BFU) {
                        M2C_FIELD(temp_s6, u16 *, 0x28) = (u16) M2C_FIELD(sp18, s32 *, 0x18);
                        M2C_FIELD(temp_s6, u16 *, 0x2A) = (u16) M2C_FIELD(sp18, s32 *, 0x1C);
                        M2C_FIELD(temp_s6, u16 *, 0x2C) = (u16) M2C_FIELD(sp18, u16 *, 0x20);
                        M2C_FIELD(temp_s6, u16 *, 0x2E) = (u16) M2C_FIELD(sp18, u16 *, 0x24);
                        M2C_FIELD(temp_s6, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 0) - (((temp_s0 + M2C_FIELD(sp18, s16 *, 0x22)) * 4) + 0x200));
                        M2C_FIELD(arg1, u16 *, 0xA4) = (u16) M2C_FIELD(sp18, u16 *, 0x1A);
                        M2C_FIELD(temp_s6, u16 *, 2) = (u16) M2C_FIELD(sp18, u16 *, 0x1E);
                        gte_dpcs(arg1 + 0x10, M2C_FIELD(arg1, s32 *, 0x28), temp_s6 + 0x70, temp_a3);
                        func_8004617C(var_s3_2, 0, 1, 0, &D_80077128);
                        AddPrim(M2C_FIELD(temp_s6, s32 *, 4), var_s3_2);
                        temp_v0_3 = func_80044098(var_s3_2 + 0xC, temp_s6, var_s5, var_s2);
                        func_8004617C(temp_v0_3, 0, 1, 0, sp18 + 0x28);
                        var_s3_2 = temp_v0_3 + 0xC;
                        AddPrim(M2C_FIELD(temp_s6, s32 *, 4), temp_v0_3);
                    }
                }
            }
            var_s4_2 += 1;
            sp18 += 0x30;
        } while (var_s4_2 < M2C_FIELD(temp_s7, s16 *, 2));
    }
    var_s4_3 = 0;
    if (M2C_FIELD(temp_s7, s16 *, 4) > 0) {
        var_s0_2 = var_s3_2;
        do {
            var_s4_3 += 1;
            if (func_8003FE6C(var_s3_2, arg1, sp20, arg3, sp18) > 0) {
                temp_v0_4 = (s32) M2C_FIELD(arg1, s32 *, 0x2C) >> M2C_FIELD(arg1, s32 *, 0x20);
                M2C_FIELD(arg1, s32 *, 0x2C) = temp_v0_4;
                if ((u32) (temp_v0_4 - 1) < 0x1BFU) {
                    M2C_FIELD(var_s0_2, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x34);
                    M2C_FIELD(var_s0_2, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0x38);
                    M2C_FIELD(var_s0_2, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x3C);
                    M2C_FIELD(var_s0_2, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x40);
                    gte_dpcs(sp18 + 0x18, M2C_FIELD(arg1, s32 *, 0x28), var_s3_2 + 4);
                    *var_s3_2 = 0x05000000;
                    temp_a1_2 = var_s0_2;
                    var_s0_2 += 0x18;
                    var_s3_2 += 0x18;
                    AddPrim(M2C_FIELD(arg1, s32 *, 0) - ((((s16) M2C_FIELD(sp18, s32 *, 0x1C) + M2C_FIELD(arg1, s32 *, 0x2C)) * 4) + 0x200), temp_a1_2);
                }
            }
            sp18 += 0x20;
        } while (var_s4_3 < M2C_FIELD(temp_s7, s16 *, 4));
    }
    var_s3 = func_80042730(var_s3_2, arg1, sp20, arg3, temp_s7, &sp18);
    var_s4_4 = 0;
    if (M2C_FIELD(temp_s7, s16 *, 8) > 0) {
        var_s2_2 = var_s3;
        do {
            var_s4_4 += 1;
            if (func_8004006C(sp18, arg1) > 0) {
                temp_t0 = (s32) M2C_FIELD(arg1, s32 *, 0x2C) >> M2C_FIELD(arg1, s32 *, 0x20);
                M2C_FIELD(arg1, s32 *, 0x2C) = temp_t0;
                if ((u32) (temp_t0 - 1) < 0x1BFU) {
                    temp_s0_2 = M2C_FIELD(arg1, s32 *, 0) - (((M2C_FIELD(sp18, s16 *, 0x3A) + temp_t0) * 4) + 0x200);
                    func_8004617C(var_s3, 0, 1, 0, &D_80077128);
                    AddPrim(temp_s0_2, var_s2_2);
                    temp_s2 = var_s2_2 + 0xC;
                    M2C_FIELD(temp_s2, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x34);
                    M2C_FIELD(temp_s2, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x38);
                    M2C_FIELD(temp_s2, s32 *, 0x20) = (s32) M2C_FIELD(arg1, s32 *, 0x3C);
                    M2C_FIELD(temp_s2, s32 *, 0x2C) = (s32) M2C_FIELD(arg1, s32 *, 0x40);
                    M2C_FIELD(temp_s2, s32 *, 0xC) = (s32) (arg3 + M2C_FIELD(sp18, s32 *, 0x30));
                    M2C_FIELD(temp_s2, s32 *, 0x18) = (s32) M2C_FIELD(sp18, s32 *, 0x34);
                    temp_s3 = var_s3 + 0xC;
                    M2C_FIELD(temp_s2, u16 *, 0x24) = (u16) M2C_FIELD(sp18, u16 *, 0x38);
                    M2C_FIELD(temp_s2, u16 *, 0x30) = (u16) M2C_FIELD(sp18, u16 *, 0x3C);
                    func_800402E4(temp_s3, arg1, sp18);
                    M2C_FIELD(var_s3, s32 *, 0xC) = 0x0C000000;
                    M2C_FIELD(temp_s2, s8 *, 7) = 0x3C;
                    temp_s2_2 = temp_s2 + 0x34;
                    temp_s3_2 = temp_s3 + 0x34;
                    AddPrim(temp_s0_2, temp_s2);
                    var_s3 = temp_s3_2 + 0xC;
                    func_8004617C(temp_s3_2, 0, 1, 0, sp18 + 0x40);
                    var_s2_2 = temp_s2_2 + 0xC;
                    AddPrim(temp_s0_2, temp_s2_2);
                }
            }
            sp18 += 0x48;
        } while (var_s4_4 < M2C_FIELD(temp_s7, s16 *, 8));
    }
    var_s4_5 = 0;
    if (M2C_FIELD(temp_s7, s16 *, 0xA) > 0) {
        var_s0_3 = var_s3;
        do {
            var_s4_5 += 1;
            if (func_8004006C(sp18, arg1) > 0) {
                temp_v0_5 = (s32) M2C_FIELD(arg1, s32 *, 0x2C) >> M2C_FIELD(arg1, s32 *, 0x20);
                M2C_FIELD(arg1, s32 *, 0x2C) = temp_v0_5;
                if ((u32) (temp_v0_5 - 1) < 0x1BFU) {
                    M2C_FIELD(var_s0_3, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x34);
                    M2C_FIELD(var_s0_3, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x38);
                    M2C_FIELD(var_s0_3, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 0x3C);
                    M2C_FIELD(var_s0_3, s32 *, 0x20) = (s32) M2C_FIELD(arg1, s32 *, 0x40);
                    func_80040370(var_s3, arg1, sp18);
                    *var_s3 = 0x08000000;
                    temp_a1_3 = var_s0_3;
                    var_s0_3 += 0x24;
                    var_s3 += 0x24;
                    AddPrim(M2C_FIELD(arg1, s32 *, 0) - ((((s16) M2C_FIELD(sp18, s32 *, 0x34) + M2C_FIELD(arg1, s32 *, 0x2C)) * 4) + 0x200), temp_a1_3);
                }
            }
            sp18 += 0x38;
        } while (var_s4_5 < M2C_FIELD(temp_s7, s16 *, 0xA));
    }
    if (M2C_FIELD(arg1, s32 *, 0x24) != 0) {
        func_80043738();
        func_80043794();
    }
    return var_s3;
}
