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

extern M2C_UNK D_80010128;
extern s16 D_801D77B8;
extern s16 D_801E9250;
extern M2C_UNK D_801E9260;
extern M2C_UNK D_801E9264;
extern M2C_UNK D_801E9268;
extern M2C_UNK D_801E9274;
extern M2C_UNK D_801E9294;
extern M2C_UNK D_801E9298;
extern M2C_UNK D_801E929C;
extern M2C_UNK D_801E92A0;
extern M2C_UNK D_801E92A4;
extern M2C_UNK D_801E92A8;
extern M2C_UNK D_801E92B4;
extern M2C_UNK D_801E92BC;
extern M2C_UNK D_801E92D8;
extern M2C_UNK D_801E9310;

u16 func_8001B374(void *arg0) {
    M2C_UNK sp10;
    u16 sp40;
    u16 sp48;
    u16 sp50;
    s16 *sp58;
    s32 sp60;
    s32 sp68;
    M2C_UNK *var_a2;
    M2C_UNK *var_a3;
    M2C_UNK var_a0;
    s16 *var_s7;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s3;
    s32 temp_s4;
    s32 temp_s4_2;
    s32 temp_s5;
    s32 temp_s5_2;
    s32 temp_s6;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_v0;
    s32 var_v0_2;
    void *temp_v0;

    var_a3 = &sp10;
    var_a2 = &D_80010128;
    do {
        M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
        M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
        M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
        M2C_FIELD(var_a3, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
        var_a2 += 0x10;
        var_a3 += 0x10;
    } while (var_a2 != (&D_80010128 + 0x30));
    sp58 = &D_801E9250;
    sp50 = 0;
    sp40 = 0;
    var_s7 = &D_801E9250 + 0xC;
loop_3:
    if (*sp58 == 1) {
        temp_a0 = (s16) sp40 * 0x114;
        if (*(&D_801E92A8 + temp_a0) == 1) {
            sp48 = 0;
            sp68 = (s32) (s16) sp40;
loop_6:
            sp60 = (s32) (s16) sp48;
            temp_v0 = &sp10 + ((s16) sp48 * 8);
            temp_s4 = M2C_FIELD(temp_v0, s32 *, 4);
            temp_s5 = M2C_FIELD(temp_v0, s32 *, 0);
            temp_s6 = M2C_FIELD(arg0, s32 *, 0x24) & 0xFFF;
            temp_s0 = rcos(temp_s6);
            var_s1 = (temp_s0 * temp_s4) + (rsin(temp_s6) * temp_s5);
            if (var_s1 < 0) {
                var_s1 += 0xFFF;
            }
            temp_s0_2 = rsin(temp_s6);
            var_a1 = (-temp_s0_2 * temp_s4) + (rcos(temp_s6) * temp_s5);
            if (var_a1 < 0) {
                var_a1 += 0xFFF;
            }
            temp_a1 = (var_a1 >> 0xC) + M2C_FIELD(arg0, s32 *, 0x18);
            temp_s3 = *(&D_801E9274 + temp_a0) & 0xFFF;
            temp_s4_2 = ((var_s1 >> 0xC) + M2C_FIELD(arg0, s32 *, 0x10)) - *(&D_801E9260 + temp_a0);
            temp_s5_2 = temp_a1 - *(&D_801E9268 + temp_a0);
            temp_s0_3 = rcos(temp_s3, temp_a1);
            var_s1_2 = (temp_s0_3 * temp_s4_2) - (rsin(temp_s3) * temp_s5_2);
            if (var_s1_2 < 0) {
                var_s1_2 += 0xFFF;
            }
            temp_s0_4 = rsin(temp_s3);
            var_a1_2 = (temp_s0_4 * temp_s4_2) + (rcos(temp_s3) * temp_s5_2);
            if (var_a1_2 < 0) {
                var_a1_2 += 0xFFF;
            }
            temp_v1 = *(&D_801E9264 + temp_a0);
            temp_a0_2 = M2C_FIELD(arg0, s32 *, 0x14);
            if ((temp_a0_2 >= (temp_v1 - 0xF)) && ((temp_v1 + 0xF) >= temp_a0_2) && ((u32) ((var_s1_2 >> 0xC) + 0x19) < 0x33U) && ((u32) ((var_a1_2 >> 0xC) + 0x15) < 0x66U)) {
                if (sp60 >= 4) {
                    if ((u32) (func_80019C6C(temp_s3, temp_s6) + 0x4FF) < 0x9FFU) {
                        sp50 = 1;
                        *(&D_801E9294 + temp_a0) = 1;
                        *(&D_801E9298 + temp_a0) = M2C_FIELD(arg0, s32 *, 0x60);
                        *(&D_801E929C + temp_a0) = M2C_FIELD(arg0, s32 *, 0x64);
                        *(&D_801E92A0 + temp_a0) = M2C_FIELD(arg0, s32 *, 0x68);
                        *(&D_801E92A4 + temp_a0) = M2C_FIELD(arg0, s32 *, 0x6C);
                        var_v0 = 2;
                        if (M2C_FIELD(arg0, s32 *, 0xC) >= M2C_FIELD(var_s7, s32 *, 0)) {
                            var_v0 = -2;
                        }
                        *(&D_801E9310 + temp_a0) = var_v0;
                        if (D_801D77B8 == 1) {
                            temp_v0_2 = sp68 * 0x114;
                            *(&D_801E9310 + temp_v0_2) = -*(&D_801E9310 + temp_v0_2);
                        }
                        goto block_27;
                    }
                    if (*(&D_801E92D8 + temp_a0) < 0x320) {
                        sp50 = 1;
                        *(&D_801E9294 + temp_a0) = 1;
block_27:
                        func_80032F50(2, arg0);
                    } else {
                        *(&D_801E9294 + temp_a0) = 1;
                        *(&D_801E92A0 + temp_a0) = *(&D_801E92BC + temp_a0) << 8;
                        *(&D_801E9298 + temp_a0) = *(&D_801E92B4 + temp_a0) << 8;
                        *(&D_801E92D8 + temp_a0) = (s32) (*(&D_801E92D8 + temp_a0) * 2) / 3;
                        var_v0_2 = 6;
                        if (M2C_FIELD(arg0, s32 *, 0xC) >= M2C_FIELD(var_s7, s32 *, 0)) {
                            var_v0_2 = -6;
                        }
                        goto block_32;
                    }
                } else {
                    *(&D_801E9294 + temp_a0) = 1;
                    *(&D_801E92D8 + temp_a0) = (s32) *(&D_801E92D8 + temp_a0) / 2;
                    *(&D_801E9298 + temp_a0) = *(&D_801E92B4 + temp_a0) << 8;
                    *(&D_801E92A0 + temp_a0) = *(&D_801E92BC + temp_a0) << 8;
                    M2C_FIELD(var_s7, s32 *, 0x40) = (s32) ((s32) M2C_FIELD(var_s7, s32 *, 0x40) / 3);
                    M2C_FIELD(var_s7, s32 *, 0x3C) = (s32) ((s32) M2C_FIELD(var_s7, s32 *, 0x3C) / 3);
                    M2C_FIELD(var_s7, s32 *, 0x44) = (s32) ((s32) M2C_FIELD(var_s7, s32 *, 0x44) / 3);
                    var_v0_2 = 7;
                    if (M2C_FIELD(arg0, s32 *, 0xC) >= M2C_FIELD(var_s7, s32 *, 0)) {
                        var_v0_2 = -7;
                    }
block_32:
                    *(&D_801E9310 + temp_a0) = var_v0_2;
                    if (D_801D77B8 == 1) {
                        temp_v0_3 = sp68 * 0x114;
                        *(&D_801E9310 + temp_v0_3) = -*(&D_801E9310 + temp_v0_3);
                    }
                }
            } else {
                temp_v0_4 = sp48 + 1;
                sp48 = temp_v0_4;
                if (temp_v0_4 < 6) {
                    goto loop_6;
                }
            }
        }
    }
    if (sp50 != 1) {
        temp_v0_5 = sp40 + 1;
        var_s7 += 0x114;
        sp40 = temp_v0_5;
        sp58 += 0x114;
        if (temp_v0_5 < 0xC) {
            goto loop_3;
        }
    }
    if (sp50 != 0) {
        var_a0 = 0x18;
        if (M2C_FIELD(arg0, s32 *, 0xA0) >= 0x321) {
            var_a0 = 0x17;
        }
        snd_play_se(var_a0);
    }
    return sp50;
}
