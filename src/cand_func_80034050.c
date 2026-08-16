/* cand_func_80034050.c -- one candidate function, decompiled by m2c.
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



s32 func_80034050(s32 arg0, void *arg1, s32 *arg2, s32 arg3) {
    s32 sp10;
    s32 *sp18;
    s32 sp20;
    s32 sp28;
    void *sp30;
    void *sp38;
    s32 *var_fp;
    s32 temp_a0;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_t0;
    s32 temp_v0;
    s32 var_s3;
    s32 var_s4;
    s32 var_s6;
    s32 var_s7;
    s32 var_v0;
    u16 temp_v0_2;
    void *temp_s5;
    void *var_s1;

    sp10 = arg0;
    sp18 = arg2;
    sp20 = arg3;
    M2C_FIELD(arg1, s8 *, 0x13) = 0x2C;
    sp28 = 0;
    sp38 = arg1 + 0x44;
    temp_s5 = arg1 + 0xA4;
    if (arg3 > 0) {
        var_fp = arg2 + 0xC;
        do {
            if (M2C_FIELD(var_fp, s32 *, 0) >= 0) {
                M2C_FIELD(sp38, s32 *, 0x14) = (s32) *sp18;
                M2C_FIELD(sp38, s32 *, 0x18) = (s32) M2C_FIELD(var_fp, s32 *, -8);
                M2C_FIELD(sp38, s32 *, 0x1C) = (s32) M2C_FIELD(var_fp, s32 *, -4);
                func_80043500(sp38);
                temp_a0 = M2C_FIELD(arg1, s32 *, 0x24);
                sp30 = (M2C_FIELD(var_fp, s32 *, 0) << 5) + M2C_FIELD(arg1, s32 *, 4);
                if (temp_a0 != 0) {
                    func_80043738(temp_a0);
                    func_80043794();
                }
                var_s7 = M2C_FIELD(sp30, s32 *, 4);
                var_s6 = 0;
                if (M2C_FIELD(sp30, s16 *, 0xE) > 0) {
                    var_s1 = var_s7 + 0x1E;
                    do {
                        temp_v0 = func_80040140(var_s7, arg1);
                        if ((temp_v0 != 0) && (func_8003FDF8(sp10, arg1, sp18, sp20) != 0)) {
                            temp_v0_2 = M2C_FIELD(var_s1, u16 *, 8);
                            temp_s4 = temp_v0_2 & 0xFF;
                            temp_s3 = (s32) (temp_v0_2 << 0x10) >> 0x18;
                            if (temp_v0 < M2C_FIELD(arg1, s32 *, 0x1C)) {
                                if (((M2C_FIELD(arg1, s16 *, 0x34) < 0x141) || (M2C_FIELD(arg1, s16 *, 0x38) < 0x141) || (M2C_FIELD(arg1, s16 *, 0x3C) < 0x141) || (M2C_FIELD(arg1, s16 *, 0x40) < 0x141)) && ((M2C_FIELD(arg1, s16 *, 0x36) < 0xF1) || (M2C_FIELD(arg1, s16 *, 0x3A) < 0xF1) || (M2C_FIELD(arg1, s16 *, 0x3E) < 0xF1) || (M2C_FIELD(arg1, s16 *, 0x42) < 0xF1)) && ((M2C_FIELD(arg1, s16 *, 0x34) >= 0) || (M2C_FIELD(arg1, s16 *, 0x38) >= 0) || (M2C_FIELD(arg1, s16 *, 0x3C) >= 0) || (M2C_FIELD(arg1, s16 *, 0x40) >= 0)) && ((M2C_FIELD(arg1, s16 *, 0x36) >= 0) || (M2C_FIELD(arg1, s16 *, 0x3A) >= 0) || (M2C_FIELD(arg1, s16 *, 0x3E) >= 0) || (M2C_FIELD(arg1, s16 *, 0x42) >= 0))) {
                                    func_8003FD24(arg1 + 0x6C, arg1 + 0x7C, arg1 + 0x8C, arg1 + 0x9C);
                                    var_v0 = temp_v0 >> 0xA;
                                    if ((M2C_FIELD(arg1, s32 *, 0x6C) < 0x140) && (var_v0 = temp_v0 >> 0xA, ((M2C_FIELD(arg1, s32 *, 0x7C) < 0x140) != 0)) && (var_v0 = temp_v0 >> 0xA, ((M2C_FIELD(arg1, s32 *, 0x8C) < 0x140) != 0))) {
                                        if (M2C_FIELD(arg1, s32 *, 0x9C) >= 0x140) {
                                            goto block_30;
                                        }
                                    } else {
                                        goto block_31;
                                    }
                                }
                            } else {
block_30:
                                var_v0 = temp_v0 >> 0xA;
block_31:
                                var_s4 = temp_s4 - var_v0;
                                var_s3 = temp_s3 - var_v0;
                                if (var_s4 < 0) {
                                    var_s4 = 0;
                                }
                                if (var_s3 < 0) {
                                    var_s3 = 0;
                                }
                                temp_s2 = temp_v0 >> M2C_FIELD(arg1, s32 *, 0x20);
                                if ((u32) (temp_s2 - 1) < 0x1BFU) {
                                    M2C_FIELD(temp_s5, u16 *, 0x28) = (u16) M2C_FIELD(var_s1, u16 *, -6);
                                    M2C_FIELD(temp_s5, u16 *, 0x2A) = (u16) M2C_FIELD(var_s1, u16 *, -2);
                                    M2C_FIELD(temp_s5, u16 *, 0x2C) = (u16) M2C_FIELD(var_s1, u16 *, 2);
                                    M2C_FIELD(temp_s5, u16 *, 0x2E) = (u16) M2C_FIELD(var_s1, u16 *, 6);
                                    M2C_FIELD(temp_s5, s32 *, 4) = (s32) (M2C_FIELD(arg1, s32 *, 0) - (((temp_s2 + M2C_FIELD(var_s1, s16 *, 4)) * 4) + 0x200));
                                    M2C_FIELD(arg1, u16 *, 0xA4) = (u16) M2C_FIELD(var_s1, u16 *, -4);
                                    M2C_FIELD(temp_s5, u16 *, 2) = (u16) M2C_FIELD(var_s1, u16 *, 0);
                                    gte_dpcs(arg1 + 0x10, M2C_FIELD(arg1, s32 *, 0x28), temp_s5 + 0x70);
                                    sp10 = func_80044098(sp10, temp_s5, var_s4, var_s3);
                                }
                            }
                        }
                        var_s6 += 1;
                        var_s1 += 0x28;
                        var_s7 += 0x28;
                    } while (var_s6 < M2C_FIELD(sp30, s16 *, 0xE));
                }
                if (M2C_FIELD(arg1, s32 *, 0x24) != 0) {
                    func_80043738();
                    func_80043794();
                }
            }
            sp18 += 0x10;
            temp_t0 = sp28 + 1;
            sp28 = temp_t0;
            var_fp += 0x10;
        } while (temp_t0 < sp20);
    }
    return sp10;
}
