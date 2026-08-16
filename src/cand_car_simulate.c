/* cand_car_simulate.c -- one candidate function, decompiled by m2c.
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

s32 func_80019C6C(s32, s32);
M2C_UNK func_80026E7C(void *);
M2C_UNK func_80027734(void *);
M2C_UNK func_80027F60(void *);
M2C_UNK func_80028294(void *);
s32 func_800497C8();
extern s32 D_80077140;
extern s32 D_8007B1A8;
extern s32 D_8007B1F8;
extern s32 D_8012CD20;
extern s32 D_8012CF78;
extern s32 D_8012CFC0;
extern s32 D_8012CFF0;
extern s16 D_8012D8D0;
extern s32 D_80173140;
extern s32 D_80173358;
extern s16 D_801D3572;
extern s16 D_801D3574;
extern u8 D_801D35A9;
extern u16 D_801D35AA;
extern s16 D_801D35B2;
extern s16 D_801D35B4;
extern s16 D_801D35B6;
extern s16 D_801D777C;
extern s16 D_801D777E;
extern s16 D_801D778C;
extern s16 D_801D778E;
extern M2C_UNK D_801D7EC8;
extern s32 D_801D9038;
extern s16 D_801D9060;

void car_simulate(void *arg0, s16 arg1) {
    s16 temp_v1;
    s16 temp_v1_2;
    s16 var_a1;
    s16 var_v0_16;
    s16 var_v0_3;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a0_5;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s2;
    s32 var_s2_2;
    s32 var_s2_3;
    s32 var_v0;
    s32 var_v0_10;
    s32 var_v0_12;
    s32 var_v0_13;
    s32 var_v0_14;
    s32 var_v0_15;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_8;
    s32 var_v0_9;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    s32 var_v1_5;
    s32 var_v1_6;
    s32 var_v1_7;
    u32 var_v0_11;
    void *temp_s1;
    void *temp_s4;

    var_a1 = arg1;
    temp_s4 = (M2C_FIELD(arg0, s16 *, 0x82) * 0x14) + &D_801D7EC8;
    temp_s1 = arg0 + 0x58;
    if ((D_801D9060 != 4) && (D_8012CD20 >= 0x1E)) {
        if (D_801D35A9 == 0x41) {
            M2C_FIELD(arg0, s16 *, 0xC8) = (s16) (((D_801D35AA & D_801D777C) != 0) << 8);
            M2C_FIELD(arg0, s16 *, 0xCA) = (s16) (((D_801D35AA & D_801D777E) != 0) << 8);
            if (M2C_FIELD(arg0, s16 *, 0xC8) >= 0x80) {
                var_v0 = D_8007B1F8 - 0x19;
                if (D_8007B1F8 > 0) {
                    goto block_19;
                }
            } else {
                var_v0 = D_8007B1F8 + 0x19;
                if (D_8007B1F8 < 0x100) {
                    goto block_19;
                }
            }
        } else {
            if (D_801D35A9 == 0x23) {
                M2C_FIELD(arg0, s16 *, 0xC8) = (s16) (((D_801D35AA & D_801D778C) != 0) << 8);
                M2C_FIELD(arg0, s16 *, 0xCA) = (s16) (((D_801D35AA & D_801D778E) != 0) << 8);
                switch (D_8012D8D0) {
                case 0:
                case 1:
                    M2C_FIELD(temp_s1, s16 *, 0x70) = (s16) ((s32) (D_801D35B2 << 8) / 106);
                    var_v0_2 = D_801D35B4 << 8;
block_14:
                    M2C_FIELD(temp_s1, s16 *, 0x72) = (s16) (var_v0_2 / 106);
                    break;
                case 2:
                case 3:
                    var_v0_3 = D_801D35B2;
block_16:
                    M2C_FIELD(temp_s1, s16 *, 0x72) = (s16) ((s32) (var_v0_3 << 8) / 106);
                    M2C_FIELD(temp_s1, s16 *, 0x70) = (s16) ((s32) (D_801D35B4 << 8) / 106);
                    break;
                case 4:
                    var_v0_2 = D_801D35B6 << 8;
                    goto block_14;
                case 5:
                    var_v0_3 = D_801D35B6;
                    goto block_16;
                }
                var_v0 = 0x100 - M2C_FIELD(temp_s1, s16 *, 0x70);
            } else {
                goto block_18;
            }
            goto block_19;
        }
    } else {
block_18:
        M2C_FIELD(arg0, s16 *, 0xCA) = 0;
        M2C_FIELD(arg0, s16 *, 0xC8) = 0;
        var_v0 = 0x100;
block_19:
        D_8007B1F8 = var_v0;
    }
    if (M2C_FIELD(temp_s1, s16 *, 0x60) != 0) {
        var_a1 = M2C_FIELD(temp_s1, s16 *, 0x70);
        M2C_FIELD(temp_s1, s16 *, 0x72) = 0;
        M2C_FIELD(temp_s1, s16 *, 0x70) = 0;
    }
    temp_v1 = M2C_FIELD(temp_s1, s16 *, 0x6C);
    if (temp_v1 == 0) {
        if (M2C_FIELD(temp_s1, s16 *, 0x70) >= 0x85) {
            M2C_FIELD(temp_s1, s16 *, 0x6C) = 1;
        }
    } else if (temp_v1 == 1) {
        M2C_FIELD(temp_s1, s16 *, 0x6C) = 2;
    } else if (M2C_FIELD(temp_s1, s16 *, 0x70) < 0x7C) {
        M2C_FIELD(temp_s1, s16 *, 0x6C) = 0;
    }
    temp_v1_2 = M2C_FIELD(temp_s1, s16 *, 0x6E);
    if (temp_v1_2 == 0) {
        if (M2C_FIELD(temp_s1, s16 *, 0x72) >= 0x85) {
            M2C_FIELD(temp_s1, s16 *, 0x6E) = 1;
        }
    } else if (temp_v1_2 == 1) {
        M2C_FIELD(temp_s1, s16 *, 0x6E) = 2;
    } else if (M2C_FIELD(temp_s1, s16 *, 0x72) < 0x7C) {
        M2C_FIELD(temp_s1, s16 *, 0x6E) = 0;
    }
    if (M2C_FIELD(temp_s1, s16 *, 0x60) != 0) {
        M2C_FIELD(temp_s1, s16 *, 0x70) = var_a1;
    }
    temp_v0 = M2C_FIELD(temp_s1, s32 *, 0x2C) - 0x1F40;
    D_8007B1A8 = temp_v0;
    if (temp_v0 < 0) {
        D_8007B1A8 = 0;
    }
    var_v0_4 = D_8007B1A8;
    if (var_v0_4 < 0) {
        var_v0_4 += 7;
    }
    temp_a0 = var_v0_4 >> 3;
    D_8007B1A8 = temp_a0;
    var_v0_5 = (s32) D_801D9038 >> 0xF;
    if (D_801D9038 < 0) {
        var_v0_5 = (s32) (D_801D9038 + 0x7FFF) >> 0xF;
    }
    temp_v0_2 = M2C_FIELD(temp_s1, s16 *, 0x70) + var_v0_5 + temp_a0;
    D_8007B1A8 = temp_v0_2;
    if (temp_v0_2 < 0) {
        D_8007B1A8 = 0;
    }
    if (D_8007B1A8 >= 0x101) {
        D_8007B1A8 = 0x100;
    }
    var_v0_6 = D_80173140 - D_8007B1A8;
    if (D_80173140 < D_8007B1A8) {
        if (var_v0_6 < 0) {
            var_v0_6 += 7;
        }
        var_v0_7 = var_v0_6 >> 3;
    } else {
        var_v0_7 = var_v0_6 / 16;
    }
    D_80173140 -= var_v0_7;
    temp_v0_3 = M2C_FIELD(temp_s1, s16 *, 0x70) * 0x64;
    var_a0 = temp_v0_3 >> 8;
    if (temp_v0_3 < 0) {
        var_a0 = (s32) (temp_v0_3 + 0xFF) >> 8;
    }
    temp_a0_2 = (0x17C - var_a0) + ((s32) (M2C_FIELD(temp_s1, s16 *, 0x72) * 0x64) / 256);
    if (M2C_FIELD(temp_s1, s32 *, 0x5C) == 1) {
        var_v0_8 = temp_a0_2 + 0x190 + D_80077140;
    } else {
        var_v0_8 = ((s32) (temp_a0_2 * M2C_FIELD(temp_s1, s32 *, 0x40)) / 1000) + D_80077140;
    }
    D_80077140 = var_v0_8 / 2;
    temp_a0_3 = (M2C_FIELD(temp_s1, s32 *, 0x2C) * M2C_FIELD(temp_s4, s32 *, 0)) - M2C_FIELD(temp_s1, s32 *, 0x58);
    var_v0_9 = temp_a0_3;
    if (temp_a0_3 < 0) {
        var_v0_9 = -var_v0_9;
    }
    temp_v1_3 = var_v0_9 + D_8012CF78;
    D_8012CF78 = temp_v1_3;
    var_s0 = 0;
    if (temp_a0_3 <= 0) {
        D_801D9038 -= temp_a0_3;
    }
    if (temp_v1_3 > 0) {
        temp_v0_4 = temp_v1_3 + 0xFFFC0000;
        D_8012CF78 = temp_v0_4;
        if (temp_v0_4 < 0) {
            D_8012CF78 = 0;
        }
    }
    if (D_801D9038 > 0) {
        D_801D9038 += 0xFFFF0000;
    }
    if (M2C_FIELD(temp_s1, s32 *, 0x5C) == 1) {
        var_v0_10 = temp_a0_3;
        if (temp_a0_3 < 0) {
            var_v0_10 = temp_a0_3 + 0xFF;
        }
        var_s0_2 = var_v0_10 >> 8;
        if (var_s0_2 < 0) {
            var_s0_2 += 0xF;
        }
        var_s0 = var_s0_2 >> 4;
    } else if (temp_a0_3 >= -0x30D3) {
        if (temp_a0_3 > 0x186A0) {
            var_v1 = temp_a0_3;
            if (temp_a0_3 < 0) {
                var_v1 = temp_a0_3 + 0xFF;
            }
            var_s0_3 = (s32) ((var_v1 >> 8) * 0x46) / 100;
            var_v0_11 = (u32) var_s0_3 >> 0x1F;
            goto block_83;
        }
    } else {
        var_v0_12 = temp_a0_3;
        if (temp_a0_3 < 0) {
            var_v0_12 = temp_a0_3 + 0xFF;
        }
        temp_v0_5 = var_v0_12 >> 8;
        var_s0_3 = temp_v0_5 >> 2;
        if (temp_v0_5 < 0) {
            var_s0_3 = (s32) (temp_v0_5 + 3) >> 2;
        }
        var_v0_11 = (u32) var_s0_3 >> 0x1F;
block_83:
        var_s0 = (s32) (var_s0_3 + var_v0_11) >> 1;
    }
    temp_a1 = M2C_FIELD(temp_s1, s32 *, 0x2C);
    if (temp_a1 < 0x1388) {
        var_a0_2 = M2C_FIELD(temp_s4, s32 *, 4);
        var_v1_2 = M2C_FIELD(temp_s4, s32 *, 8) * temp_a1;
        var_v0_13 = 0x1388;
    } else {
        var_a0_2 = M2C_FIELD(temp_s4, s32 *, 8);
        var_v1_2 = (temp_a1 - 0x1388) * M2C_FIELD(temp_s4, s32 *, 0xC);
        var_v0_13 = 0x2710;
    }
    var_a0_3 = (s32) (var_v1_2 + ((var_v0_13 - temp_a1) * var_a0_2)) / 50000;
    if (var_a0_3 < 0) {
        var_a0_3 = 0;
    }
    if (D_801D9060 >= 2) {
        if (M2C_FIELD(temp_s1, s16 *, 0x60) == 0) {
            var_s0 += (s32) M2C_FIELD(temp_s1, s32 *, 0x2C) / 256;
        }
        var_s2 = var_a0_3 * M2C_FIELD(temp_s1, s16 *, 0x70);
        if (var_s2 < 0) {
            var_s2 += 0xFF;
        }
        temp_a0_4 = M2C_FIELD(temp_s1, s32 *, 0x2C);
        var_v1_3 = M2C_FIELD(temp_s1, s16 *, 0x72) * temp_a0_4;
        var_s2_2 = var_s2 >> 8;
        if (var_v1_3 < 0) {
            var_v1_3 += 0xFF;
        }
        var_v1_4 = var_v1_3 >> 8;
        if (var_v1_4 < 0) {
            var_v1_4 += 0x1F;
        }
        var_s0 += var_v1_4 >> 5;
        if (D_8012CD20 < 0x1E) {
            var_s0 += temp_a0_4 / 16;
        }
    } else {
        var_s2_3 = (M2C_FIELD(temp_s1, s16 *, 0x70) - 0x4D) * 0x29A;
        if (var_s2_3 < 0) {
            var_s2_3 += 0xFF;
        }
        temp_v1_4 = M2C_FIELD(temp_s1, s32 *, 0x2C);
        var_s2_2 = var_s2_3 >> 8;
        if (temp_v1_4 >= 0x23F1) {
            var_s0 = var_s0 - 0x23F0 + temp_v1_4;
        }
    }
    temp_v0_6 = func_80019C6C(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(temp_s1, s32 *, 0x50));
    D_80173358 = temp_v0_6;
    if (temp_v0_6 >= 0x401) {
        D_80173358 = 0x800 - temp_v0_6;
    }
    var_s0_4 = var_s0 + ((s32) D_80173358 / 256);
    if ((D_801D9060 == 2) && (M2C_FIELD(temp_s1, s32 *, 0x5C) == 3)) {
        var_s0_4 += (D_8012CFF0 & 0x1F) << 5;
    }
    if (D_8012CFC0 > 0) {
        var_s0_4 = var_s0_4 + 0xC8 + (D_8012CFC0 * 0x14);
        D_8012CFC0 -= 1;
    }
    temp_v0_7 = (var_s2_2 - var_s0_4) + M2C_FIELD(temp_s1, s32 *, 0x2C);
    M2C_FIELD(temp_s1, s32 *, 0x2C) = temp_v0_7;
    if (temp_v0_7 < 0) {
        M2C_FIELD(temp_s1, s32 *, 0x2C) = 0;
    } else if (temp_v0_7 >= 0x3A99) {
        M2C_FIELD(temp_s1, s32 *, 0x2C) = 0x3A98;
    }
    temp_lo = M2C_FIELD(temp_s1, s32 *, 0x2C) * M2C_FIELD(temp_s4, s32 *, 0);
    M2C_FIELD(temp_s1, s32 *, 0x58) = temp_lo;
    if (M2C_FIELD(temp_s1, s32 *, 0x5C) == 1) {
        var_v0_14 = temp_lo;
        if (temp_lo < 0) {
            var_v0_14 = temp_lo + 0xFF;
        }
        temp_v1_5 = var_v0_14 >> 8;
        var_a0_4 = temp_v1_5 >> 5;
        if (temp_v1_5 < 0) {
            var_a0_4 = (s32) (temp_v1_5 + 0x1F) >> 5;
        }
        if (var_a0_4 < 0) {
            var_a0_4 += 0x7F;
        }
        var_v0_15 = (s32) (M2C_FIELD(temp_s1, s32 *, 0x48) * 0x3E4) / 1000;
        var_v1_5 = var_a0_4 >> 7;
    } else {
        var_v1_6 = temp_lo >> 8;
        if (temp_lo < 0) {
            var_v1_6 = (s32) (temp_lo + 0xFF) >> 8;
        }
        var_a0_5 = var_v1_6 >> 5;
        if (var_v1_6 < 0) {
            var_a0_5 = (s32) (var_v1_6 + 0x1F) >> 5;
        }
        if (var_a0_5 < 0) {
            var_a0_5 += 0xF;
        }
        var_v0_15 = (s32) (M2C_FIELD(temp_s1, s32 *, 0x48) * 0x5E) / 100;
        var_v1_5 = var_a0_5 >> 4;
    }
    M2C_FIELD(temp_s1, s32 *, 0x4C) = var_v1_5;
    M2C_FIELD(temp_s1, s32 *, 0x48) = var_v0_15;
    if (M2C_FIELD(temp_s1, s16 *, 0x60) != 0) {
        M2C_FIELD(temp_s1, s32 *, 0x4C) = (s32) ((s32) (M2C_FIELD(temp_s1, s32 *, 0x4C) * 0x8F) / 160);
    }
    if (M2C_FIELD(temp_s1, s32 *, 0x48) < 8) {
        M2C_FIELD(temp_s1, s32 *, 0x50) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
    }
    if (D_801D9060 != 1) {
        temp_v1_6 = M2C_FIELD(temp_s1, s32 *, 0x5C);
        switch (temp_v1_6) {
        case 0:
            func_80026E7C(arg0);
            break;
        case 1:
            func_80027734(arg0);
            break;
        case 2:
            func_80027F60(arg0);
            break;
        case 3:
            func_80028294(arg0);
            break;
        }
    }
    if (M2C_FIELD(temp_s1, s32 *, 0x5C) == 0) {
        var_v1_7 = D_8012CF78;
        if (var_v1_7 > 0x100000) {
            if (var_v1_7 < 0) {
                var_v1_7 += 0x7FF;
            }
            if (M2C_FIELD(temp_s1, s32 *, 0x48) < (var_v1_7 >> 0xB)) {
                temp_lo_2 = (s32) ((func_800497C8() & 0x7F) * 0x28) / 100;
                D_801D3572 = (s16) temp_lo_2;
                var_v0_16 = (temp_lo_2 * 0xC) + 0x1800;
                goto block_153;
            }
        } else {
            D_801D3572 = 0;
            var_v0_16 = 0x1E00;
block_153:
            D_801D3574 = var_v0_16;
        }
    }
    if (M2C_FIELD(temp_s1, s32 *, 0x48) < 8) {
        M2C_FIELD(temp_s1, s32 *, 0x50) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
    }
    if (D_8012CFC0 > 0) {
        D_801D3572 = 0x37;
        D_801D3574 = ((func_800497C8() & 3) + 0x38) << 7;
    }
    if (M2C_FIELD(temp_s1, s16 *, 0x60) != 0) {
        D_801D3572 = 0;
    }
}
