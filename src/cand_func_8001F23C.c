/* cand_func_8001F23C.c -- one candidate function, decompiled by m2c.
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

extern u16 D_8007B1E8;
extern s16 D_8007C210;
extern M2C_UNK D_8007C258;
extern s16 D_8007C25A;
extern s16 D_8007C2D8;
extern s32 D_8012CD90;
extern s16 D_8012CF90;
extern s32 D_80173300;
extern u16 D_80173310;
extern s32 D_80173338;
extern s16 D_801733B8;
extern s16 D_801D34E0;
extern u16 D_801D34F8;
extern u16 D_801D35AA;
extern u16 D_801D35AE;
extern s16 D_801D77B0;
extern u16 D_801D77D0;
extern s16 D_801D77D8;
extern u16 D_801D7E18;
extern s16 D_801D7E90;
extern s16 D_801E90A8;
extern s16 D_801E90C0;
extern s16 D_801E91A0;
extern u16 D_801E91A8;
extern s16 D_801E91B0;
extern s32 D_801E91C0;

void func_8001F23C(void) {
    s16 var_v0;
    s16 var_v0_3;
    s16 var_v1;
    s16 var_v1_2;
    s32 var_v0_2;
    s32 var_v0_4;

    if (D_8012CF90 == 0) {
        func_8001CEC8(1);
    }
    if (D_801D77D0 == 0) {
        if (D_8012CF90 != 0) {
            D_8012CF90 += 1;
        }
        if ((u16) D_80173310 < 0x3CU) {
            D_80173310 += 1;
        }
        if (D_80173310 == 2) {
            func_80045750(1);
        }
        D_8007B1E8 += 1;
    }
    if (D_8012CF90 == 0) {
        if (D_801D77D0 == 0) {
            if (D_801E90C0 == 0) {
                if (D_801D35AE & 0x8000) {
                    if (D_801D77B0 >= 4) {
                        var_v0 = D_801D77B0 - 1;
                        if (D_801D77B0 >= 5) {
                            goto block_18;
                        }
                    } else {
                        var_v0 = D_801D77B0 - 1;
                        if (D_801D77B0 > 0) {
block_18:
                            D_801D77B0 = var_v0;
                            D_8007B1E8 = 0;
                        }
                    }
                }
                if (D_801D35AE & 0x2000) {
                    if (D_801D77B0 >= 4) {
                        var_v0_2 = D_801D77B0 < 5;
                    } else {
                        var_v0_2 = D_801D77B0 < 3;
                    }
                    if (var_v0_2 != 0) {
                        D_801D77B0 += 1;
                        D_8007B1E8 = 0;
                    }
                }
                if ((D_801D35AE & 0x1000) && (D_801D77B0 >= 4)) {
                    D_8007B1E8 = 0;
                    D_801D77B0 = (s16) D_801E91A8;
                }
                if ((D_801D35AE & 0x4000) && (D_801D77B0 < 4)) {
                    D_801E91A8 = (u16) D_801D77B0;
                    var_v1 = 5;
                    if (D_801D77B0 < 2) {
                        var_v1 = 4;
                    }
                    D_801D77B0 = var_v1;
                    D_8007B1E8 = 0;
                }
                if (D_801D77B0 != D_801D77B0) {
                    snd_play_se(0x1F, D_801D77B0);
                }
                if (D_801D35AE & 0x860) {
                    switch (D_801D77B0) {
                    default:
                        snd_play_se(0x2D);
                        switch (D_801D77B0) {
                        case 0:
                            var_v0_3 = D_8007C210;
block_48:
                            D_8012CD90 = (s32) var_v0_3;
                            break;
                        case 1:
                            var_v0_3 = D_8007C2D8;
                            goto block_48;
                        case 2:
                            var_v0_3 = D_8007C25A;
                            goto block_48;
                        case 3:
                            var_v0_3 = D_801D34E0;
                            goto block_48;
                        }
                        D_801D7E90 = 0;
                        D_801E90C0 = D_801E90C0 == 0;
                        break;
                    case 4:
                        snd_play_se(0x20);
                        var_v1_2 = D_801D34E0;
                        D_8012CF90 = 1;
                        if (var_v1_2 == 0) {
                            var_v1_2 = ((s32) (func_800497C8() & 0xFFF) % 6) + 1;
                        }
                        D_80173338 = (s32) var_v1_2;
                        func_8003A1AC(-1);
                        break;
                    case 5:
                        snd_play_se(0x2D);
                        D_801D34F8 = 0x11;
                        D_8007C25A = (s16) ((s32) (D_8007C25A + 0xD) % 13);
                        break;
                    }
                }
                if (D_801D35AE & 0x90) {
                    snd_play_se(0x24);
                    D_801E91A0 = 0;
                    D_801D34F8 = 2;
                    D_8007C25A = (s16) ((s32) (D_8007C25A + 0xD) % 13);
                }
            } else {
                if (D_801D35AE & 0x8000) {
                    D_801D7E90 = -1;
                    switch (D_801D77B0) {
                    case 0:
                        if (D_8007C210 >= 2) {
                            D_8007C210 -= 1;
block_74:
                            snd_play_se(0x21);
                        }
                        break;
                    case 1:
                        if (M2C_FIELD(&D_8007C258, s16 *, 0x80) == D_801D77B0) {
                            M2C_FIELD(&D_8007C258, s16 *, 0x80) = 0;
                            goto block_74;
                        }
                        break;
                    case 2:
                        if (-D_801D77D8 < M2C_FIELD(&D_8007C258, s16 *, 2)) {
                            M2C_FIELD(&D_8007C258, s16 *, 2) = (s16) (M2C_FIELD(&D_8007C258, s16 *, 2) - 1);
                            goto block_74;
                        }
                        break;
                    case 3:
                        if (D_801D34E0 > 0) {
                            D_801D34E0 -= 1;
                            goto block_74;
                        }
                        break;
                    }
                }
                if (D_801D35AE & 0x2000) {
                    D_801D7E90 = 1;
                    switch (D_801D77B0) {
                    case 0:
                        if (D_8007C210 < D_801E90A8) {
                            D_8007C210 += 1;
block_91:
                            snd_play_se(0x2C);
                        }
                        break;
                    case 1:
                        if (M2C_FIELD(&D_8007C258, s16 *, 0x80) == 0) {
                            M2C_FIELD(&D_8007C258, s16 *, 0x80) = 1;
                            goto block_91;
                        }
                        break;
                    case 2:
                        if (M2C_FIELD(&D_8007C258, s16 *, 2) < (D_80173300 - 1)) {
                            M2C_FIELD(&D_8007C258, s16 *, 2) = (s16) (M2C_FIELD(&D_8007C258, s16 *, 2) + 1);
                            goto block_91;
                        }
                        break;
                    case 3:
                        if (D_801D34E0 < 6) {
                            D_801D34E0 += 1;
                            goto block_91;
                        }
                        break;
                    }
                }
                if (D_801D35AE & 0x860) {
                    snd_play_se(0x2D);
                    D_801D7E90 = 0;
                    D_801E90C0 = D_801E90C0 == 0;
                }
                if (D_801D35AE & 0x90) {
                    snd_play_se(0x24);
                    switch (D_801D77B0) {
                    case 0:
                        D_8007C210 = (s16) (u16) D_8012CD90;
                        break;
                    case 1:
                        D_8007C2D8 = (s16) (u16) D_8012CD90;
                        break;
                    case 2:
                        D_8007C25A = (s16) (u16) D_8012CD90;
                        break;
                    case 3:
                        D_801D34E0 = (s16) (u16) D_8012CD90;
                        break;
                    }
                    D_801E90C0 = D_801E90C0 == 0;
                }
            }
            goto block_107;
        }
    } else {
block_107:
        if (D_801D77D0 == 0) {
            var_v0_4 = (M2C_FIELD(&D_8007C258, s16 *, 2) << 0x10) - D_801E91C0;
            if (var_v0_4 < 0) {
                var_v0_4 += 0xF;
            }
            D_801E91C0 += var_v0_4 >> 4;
            if ((D_801D35AA & 8) && (D_801E91B0 < 0x40)) {
                D_801E91B0 += 1;
            }
            if ((D_801D35AA & 4) && (D_801E91B0 >= -0x3F)) {
                D_801E91B0 -= 1;
            }
            D_801D7E18 += (u16) D_801E91B0;
            if (D_8012CF90 >= 0x5B) {
                D_801D34F8 = 0;
                D_8007C25A = (s16) ((s32) (D_8007C25A + 0xD) % 13);
            }
        }
    }
    func_8001E470();
    func_8001EF54(0xF5);
    if (D_801D34F8 != 7) {
        if (D_8007C210 >= 5) {
            D_801733B8 = 1;
            D_8007C210 -= 4;
            return;
        }
        D_801733B8 = 0;
    }
}
