/* cand_func_800324F4.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_80010648;
extern M2C_UNK D_80010654;
extern M2C_UNK D_80010660;
extern M2C_UNK D_80010670;
extern s32 D_8007C240;
extern s32 D_8007C4D0;
extern s16 D_8012CFD8;
extern u16 D_80173310;
extern s32 D_80173370;
extern s16 D_801D34F8;
extern u16 D_801D35AE;
extern u16 D_801D77D0;

void func_800324F4(void) {
    M2C_UNK *var_a0_3;
    M2C_UNK *var_a0_4;
    M2C_UNK var_a0;
    M2C_UNK var_a0_2;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_v0;

    func_8001CEC8(1);
    if (D_80173310 == 2) {
        func_80045750(1);
    }
    if (D_801D77D0 == 0) {
        D_80173310 += 1;
        switch (D_8007C240) {
        case 0:
            if (D_801D35AE & 0x90) {
                snd_play_se(0x24);
                D_801D34F8 = 0x17;
            }
            if (D_801D35AE & 0x860) {
                temp_s0 = D_8007C4D0;
                switch (temp_s0) {
                case 0:
                    snd_play_se(0x24);
                    D_801D34F8 = 0x17;
                    break;
                case 1:
                    temp_v0 = func_80031910();
                    if (temp_v0 == -1) {
                        D_8007C240 = 3;
                        snd_play_se(0x1C);
                    } else {
                        if (temp_v0 != 0) {
                            D_8007C240 = temp_s0;
                        } else {
                            D_8007C240 = 2;
                        }
                        var_a0 = 0x1C;
                        if (temp_v0 != 0) {
                            var_a0 = 0x2D;
                        }
                        snd_play_se(var_a0);
                    }
block_24:
                    func_80031BD8();
                    D_80173370 = D_8012CFD8 + 2;
                    break;
                default:
                    temp_v0_2 = func_800319D4();
                    var_v0 = 1;
                    if (temp_v0_2 == 0) {
                        var_v0 = 2;
                    }
                    D_8007C240 = var_v0;
                    var_a0_2 = 0x1C;
                    if (temp_v0_2 != 0) {
                        var_a0_2 = 0x2D;
                    }
                    snd_play_se(var_a0_2);
                    goto block_24;
                }
            }
            temp_v1 = D_80173370 - 1;
            if (temp_v1 < D_8007C4D0) {
                D_8007C4D0 = temp_v1;
            }
            func_80031FD0();
            if ((D_801D35AE & 0x1000) && (D_8007C4D0 > 0)) {
                D_8007C4D0 -= 1;
            }
            if ((D_801D35AE & 0x4000) && (D_8007C4D0 < (D_80173370 - 1))) {
                D_8007C4D0 += 1;
            }
            if ((D_801D35AE & 0x8000) && (D_8007C4D0 >= 0xA)) {
                D_8007C4D0 -= 8;
            }
            if ((D_801D35AE & 0x2000) && (D_80173370 >= 0xB)) {
                temp_v0_3 = D_8007C4D0 + 8;
                if ((u32) (D_8007C4D0 - 2) < 8U) {
                    D_8007C4D0 = temp_v0_3;
                    temp_v1_2 = D_80173370 - 1;
                    if (temp_v1_2 < temp_v0_3) {
                        D_8007C4D0 = temp_v1_2;
                    }
                }
            }
            if (D_8007C4D0 != D_8007C4D0) {
                snd_play_se(0x28, D_8007C4D0);
            }
            break;
        case 1:
            if (D_801D35AE & 0x8F0) {
                snd_play_se(0x28);
                D_8007C240 = 0;
            }
            var_a0_3 = &D_80010648;
block_51:
            func_800310C8(var_a0_3, 0x7A);
            break;
        case 2:
            if (D_801D35AE & 0x8F0) {
                snd_play_se(0x28);
                D_8007C240 = 0;
            }
            var_a0_3 = &D_80010654;
            goto block_51;
        case 3:
            if (D_801D35AE & 0x8F0) {
                snd_play_se(0x28);
                D_8007C240 = 0;
            }
            var_a0_4 = &D_80010660;
block_59:
            func_800310C8(var_a0_4, 0x79);
            break;
        default:
            if (D_801D35AE & 0x8F0) {
                snd_play_se(0x28);
                D_8007C240 = 0;
            }
            var_a0_4 = &D_80010670;
            goto block_59;
        }
    }
    if (D_8007C240 == 0) {
        func_80031E48(1);
    }
    func_80031EC4();
    func_8001EF54(0xF3);
}
