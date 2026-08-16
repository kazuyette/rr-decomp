/* cand_func_80032150.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_80010630;
extern M2C_UNK D_8001063C;
extern s32 D_8007C240;
extern s32 D_8007C4D0;
extern u16 D_80173310;
extern s32 D_80173370;
extern s16 D_801D34F8;
extern u16 D_801D35AE;
extern u16 D_801D77D0;

void func_80032150(void) {
    M2C_UNK var_a0;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_v1;

    func_8001CEC8(1);
    if (D_80173310 == 2) {
        func_80045750(1);
    }
    if (D_801D77D0 == 0) {
        D_80173310 += 1;
        switch (D_8007C240) {
        case 0:
            if (D_801D35AE & 0x90) {
                D_801D34F8 = 0x17;
                snd_play_se(0x24);
            }
            if (D_801D35AE & 0x860) {
                if (D_8007C4D0 == 0) {
                    D_801D34F8 = 0x17;
                    snd_play_se(0x24);
                } else {
                    var_v1 = 2;
                    if (func_80031A64(D_8007C4D0 - 1) != 0) {
                        var_v1 = 1;
                    }
                    D_8007C240 = var_v1;
                    var_a0 = 0x1C;
                    if (var_v1 != 0) {
                        var_a0 = 0x2D;
                    }
                    snd_play_se(var_a0);
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
            if ((D_801D35AE & 0x8000) && (D_8007C4D0 >= 9)) {
                D_8007C4D0 -= 8;
            }
            if ((D_801D35AE & 0x2000) && (D_80173370 >= 0xA)) {
                temp_v0 = D_8007C4D0 + 8;
                if ((u32) (D_8007C4D0 - 1) < 8U) {
                    D_8007C4D0 = temp_v0;
                    temp_v1_2 = D_80173370 - 1;
                    if (temp_v1_2 < temp_v0) {
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
            func_800310C8(&D_80010630, 0x7A);
            break;
        case 2:
            if (D_801D35AE & 0x8F0) {
                snd_play_se(0x28);
                D_8007C240 = 0;
            }
            func_800310C8(&D_8001063C, 0x79);
            break;
        }
    }
    if (D_8007C240 == 0) {
        func_80031E48(0);
    }
    func_80031D54();
    func_8001EF54(0xF3);
}
