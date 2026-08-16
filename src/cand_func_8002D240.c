/* cand_func_8002D240.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_800741D0;
extern s32 D_8007B1D4;
extern void *D_80173148;
extern u16 D_801D35AA;
extern u16 D_801D35AE;

void func_8002D240(void) {
    M2C_UNK *var_s3;
    M2C_UNK var_a0;
    s16 *var_s1;
    s16 temp_a0_2;
    s16 temp_a0_4;
    s16 temp_a0_5;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_v0;
    s16 temp_v0_10;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v0_9;
    s16 temp_v1_3;
    s16 temp_v1_5;
    s16 temp_v1_6;
    s16 temp_v1_7;
    s16 temp_v1_8;
    s16 var_v0;
    s32 temp_s4;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_4;
    s32 var_s0_2;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    u16 temp_v0_5;
    void *temp_a0;
    void *temp_a0_3;
    void *temp_a2_2;
    void *var_a0_2;
    void *var_s0;

    if (D_801D35AA != 0) {
        func_800497C8();
    }
    if (D_801D35AA & 0x40) {
        func_800497C8();
    }
    temp_v1 = M2C_FIELD(D_80173148, s32 *, 0) + 1;
    M2C_FIELD(D_80173148, s32 *, 0) = temp_v1;
    D_8007B1D4 = temp_v1 / 60;
    if (M2C_FIELD(D_80173148, s32 *, 0) == 4) {
        snd_play_se(0x29);
    }
    if (M2C_FIELD(D_80173148, s32 *, 0) == 0xB4) {
        temp_v0 = snd_play_se(0x39);
        M2C_FIELD(D_80173148, s16 *, 0xCBC) = temp_v0;
        func_8003B1EC(temp_v0, 0x14, 0x14);
    }
    temp_a0 = D_80173148;
    temp_v1_2 = M2C_FIELD(temp_a0, s32 *, 0);
    if (temp_v1_2 >= 0x2D1) {
        var_s2 = 0x14 - ((s32) (temp_v1_2 - 0x2D0) / 2);
        if (var_s2 < 0) {
            var_s2 = 0;
        }
        func_8003B1EC(M2C_FIELD(temp_a0, s16 *, 0xCBC), var_s2, var_s2);
        func_8003B118(M2C_FIELD(D_80173148, s16 *, 0xCBC), 0x1E00);
    }
    if ((M2C_FIELD(temp_a0, s32 *, 4) == 0) && (M2C_FIELD(temp_a0, s32 *, 0) == 0x258)) {
        M2C_FIELD(temp_a0, s32 *, 4) = 1;
    }
    temp_v0_2 = M2C_FIELD(D_80173148, s16 *, 0xC0A);
    if (temp_v0_2 >= 0x341) {
        M2C_FIELD(D_80173148, s16 *, 0xC0A) = (s16) (temp_v0_2 - 4);
    }
    temp_v1_3 = M2C_FIELD(D_80173148, s16 *, 0xC0C);
    if (temp_v1_3 == 1) {
        if (D_801D35AA & 0x8000) {
            M2C_FIELD(D_80173148, u16 *, 0xC10) = (u16) (M2C_FIELD(D_80173148, u16 *, 0xC10) - 4);
        }
        if (D_801D35AA & 0x2000) {
            M2C_FIELD(D_80173148, u16 *, 0xC10) = (u16) (M2C_FIELD(D_80173148, u16 *, 0xC10) + 4);
        }
        if ((s16) M2C_FIELD(D_80173148, u16 *, 0xC10) < 0x160) {
            M2C_FIELD(D_80173148, u16 *, 0xC10) = 0x160U;
        }
        if ((s16) M2C_FIELD(D_80173148, u16 *, 0xC10) >= 0x3A1) {
            M2C_FIELD(D_80173148, u16 *, 0xC10) = 0x3A0U;
        }
        temp_v0_3 = M2C_FIELD(D_80173148, s16 *, 0xC12);
        if (temp_v0_3 >= 0x2E1) {
            M2C_FIELD(D_80173148, s16 *, 0xC12) = (s16) (temp_v0_3 - 4);
        }
        if ((D_801D35AE & 0x40) && (M2C_FIELD(D_80173148, s16 *, 0xC14) < 0)) {
            M2C_FIELD(D_80173148, s16 *, 0xC14) = (s16) (M2C_FIELD(D_80173148, u16 *, 0xC10) + 4);
            M2C_FIELD(D_80173148, u16 *, 0xC16) = (u16) ((u16) M2C_FIELD(D_80173148, s16 *, 0xC12) - 0x20);
            snd_play_se(0x26, D_80173148);
        }
    } else {
        temp_v0_4 = temp_v1_3 + 1;
        if (temp_v1_3 >= 2) {
            M2C_FIELD(D_80173148, s16 *, 0xC0C) = temp_v0_4;
            if (temp_v0_4 >= 0x30) {
                M2C_FIELD(D_80173148, s16 *, 0xC0C) = 0;
            }
        }
    }
    if (M2C_FIELD(D_80173148, s16 *, 0xC14) > 0) {
        temp_v0_5 = M2C_FIELD(D_80173148, u16 *, 0xC16) - 0x10;
        M2C_FIELD(D_80173148, u16 *, 0xC16) = temp_v0_5;
        if ((s16) temp_v0_5 < -0x20) {
            M2C_FIELD(D_80173148, s16 *, 0xC14) = -1;
        }
    }
    temp_v1_4 = M2C_FIELD(D_80173148, s32 *, 4);
    if (temp_v1_4 == 0) {
        temp_v0_6 = M2C_FIELD(D_80173148, s16 *, 0xC1A);
        if (temp_v0_6 < 0xE0) {
            var_v0 = temp_v0_6 + 4;
            goto block_43;
        }
    } else if (temp_v1_4 == 1) {
        temp_v0_7 = M2C_FIELD(D_80173148, s16 *, 0xC1A);
        if (temp_v0_7 >= -0x3BF) {
            var_v0 = temp_v0_7 - 4;
block_43:
            M2C_FIELD(D_80173148, s16 *, 0xC1A) = var_v0;
        }
    }
    var_s2_2 = 0;
    var_s3 = &D_800741D0;
    temp_s4 = ((rsin(M2C_FIELD(D_80173148, s32 *, 0) * 0x10) * 4) + 0x10000) * 2;
    var_s1 = D_80173148 + 0xC1C;
    var_s0 = D_80173148 + 0xC22;
    do {
        temp_v1_5 = *var_s1;
        if (temp_v1_5 == 0) {
            var_v1 = M2C_FIELD(var_s3, s16 *, 0) * temp_s4;
            if (var_v1 < 0) {
                var_v1 += 0xFFF;
            }
            M2C_FIELD(var_s0, s16 *, -2) = (s16) (M2C_FIELD(D_80173148, u16 *, 0xC18) + (var_v1 >> 0xC));
            var_v0_2 = M2C_FIELD(var_s3, s16 *, 2) * temp_s4;
            if (var_v0_2 < 0) {
                var_v0_2 += 0xFFF;
            }
            temp_v1_6 = (u16) M2C_FIELD(D_80173148, s16 *, 0xC1A) + (var_v0_2 >> 0xC);
            M2C_FIELD(var_s0, s16 *, 0) = temp_v1_6;
            temp_a2 = (s16) M2C_FIELD(D_80173148, u16 *, 0xC16);
            if (temp_a2 > 0) {
                temp_a1 = M2C_FIELD(var_s0, s16 *, -2);
                temp_a0_2 = M2C_FIELD(D_80173148, s16 *, 0xC14);
                if (((temp_a1 - 0x20) < temp_a0_2) && (temp_a0_2 < (temp_a1 + 0x20)) && ((temp_v1_6 - 0x10) < temp_a2) && (temp_a2 < (temp_v1_6 + 0x10))) {
                    *var_s1 = 1;
                    M2C_FIELD(D_80173148, u16 *, 0xC16) = -1U;
                    var_a0 = 0x25;
                    if (var_s2_2 < 2) {
                        var_a0 = 0x2A;
                    }
                    snd_play_se(var_a0, (void *) temp_a1, temp_a2, D_80173148);
                }
            }
            if ((M2C_FIELD(D_80173148, s16 *, 0xC14) != -2) && (var_v1_2 = 0, ((func_800497C8() & 0x17C2) == 0))) {
                var_a0_2 = D_80173148;
loop_61:
                var_v1_2 += 3;
                if (M2C_FIELD(var_a0_2, s16 *, 0xC8E) < 0) {
                    M2C_FIELD(var_a0_2, u16 *, 0xC8C) = (u16) M2C_FIELD(var_s0, s16 *, -2);
                    var_v1_3 = temp_s4;
                    M2C_FIELD(var_a0_2, s16 *, 0xC8E) = (s16) (u16) M2C_FIELD(var_s0, s16 *, 0);
                    if (var_v1_3 < 0) {
                        var_v1_3 += 7;
                    }
                    var_v0_3 = var_v1_3 >> 3;
                    var_s3 += 8;
                    if (var_v0_3 < 0) {
                        var_v0_3 += 0xFFF;
                    }
                    M2C_FIELD(var_a0_2, s16 *, 0xC90) = (s16) (var_v0_3 >> 0xC);
                } else {
                    var_a0_2 += 6;
                    if (var_v1_2 >= 0x18) {
                        var_s3 += 8;
                    } else {
                        goto loop_61;
                    }
                }
            } else {
                goto block_72;
            }
        } else {
            temp_v0_8 = temp_v1_5 + 1;
            if (temp_v1_5 > 0) {
                *var_s1 = temp_v0_8;
                if (temp_v0_8 >= 0x18) {
                    *var_s1 = -1;
                }
            }
block_72:
            var_s3 += 8;
        }
        var_s2_2 += 1;
        var_s0 += 8;
        var_s1 += 8;
    } while (var_s2_2 < 0xE);
    var_s0_2 = 0;
    do {
        temp_a0_3 = D_80173148 + var_s0_2;
        temp_v0_9 = M2C_FIELD(temp_a0_3, s16 *, 0xC8E);
        if (temp_v0_9 > 0) {
            temp_v0_10 = temp_v0_9 + M2C_FIELD(temp_a0_3, u16 *, 0xC90);
            M2C_FIELD(temp_a0_3, s16 *, 0xC8E) = temp_v0_10;
            if (temp_v0_10 >= 0x321) {
                M2C_FIELD(temp_a0_3, s16 *, 0xC8E) = -1;
            }
            if (M2C_FIELD(D_80173148, s16 *, 0xC0C) == 1) {
                temp_a2_2 = D_80173148 + var_s0_2;
                if (M2C_FIELD(D_80173148, s16 *, 0xCBE) >= 0x81) {
                    temp_a0_4 = (s16) M2C_FIELD(D_80173148, u16 *, 0xC10);
                    temp_v1_7 = M2C_FIELD(temp_a2_2, s16 *, 0xC8C);
                    if (((temp_a0_4 - 0x10) < temp_v1_7) && (temp_v1_7 < (temp_a0_4 + 0x10))) {
                        temp_a0_5 = M2C_FIELD(D_80173148, s16 *, 0xC12);
                        temp_v1_8 = M2C_FIELD(temp_a2_2, s16 *, 0xC8E);
                        if (((temp_a0_5 - 0x10) < temp_v1_8) && (temp_v1_8 < (temp_a0_5 + 0x10))) {
                            M2C_FIELD(D_80173148, s16 *, 0xC0C) = 2;
                            M2C_FIELD(temp_a2_2, s16 *, 0xC8E) = -1;
                            snd_play_se(0x27, D_80173148, (s16) temp_a2_2);
                        }
                    }
                }
            }
        }
        var_s0_2 += 6;
    } while (var_s0_2 < 0x30);
}
