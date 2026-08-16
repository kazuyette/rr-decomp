/* cand_func_8003BB88.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8012CF60;
extern s32 D_80173138;
extern u16 D_80173310;
extern s16 D_801D34F8;
extern u16 D_801D35AA;
extern u16 D_801D35AE;
extern s32 D_801D35D8;
extern M2C_UNK D_801D7770;
extern u16 D_801D77D0;

void func_8003BB88(void) {
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_hi_3;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_v0;
    s32 var_v0_2;

    if (D_80173310 == 2) {
        func_80045750(1);
    }
    if (D_801D77D0 == 0) {
        D_80173310 += 1;
        temp_v1 = D_80173138 + 1;
        if (D_80173138 == 0) {
            var_v0 = D_801D35D8 + 0x80;
            if (var_v0 < 0) {
                var_v0 = D_801D35D8 + 0x17F;
            }
            temp_hi = (s32) ((var_v0 >> 8) + 0x13) % 40;
            temp_a2 = D_801D35AA & 0x8000;
            temp_a0 = D_801D35AA & 0x2000;
            if (temp_a2 != 0) {
                D_801D35D8 -= 0x20;
            }
            if (temp_a0 != 0) {
                D_801D35D8 += 0x20;
            }
            temp_hi_2 = (s32) (D_801D35D8 + 0x2800) % 10240;
            D_801D35D8 = temp_hi_2;
            temp_v0 = temp_hi_2 + 0x80;
            var_v0_2 = temp_v0 >> 8;
            if (temp_v0 < 0) {
                var_v0_2 = (s32) (temp_hi_2 + 0x17F) >> 8;
            }
            temp_hi_3 = (s32) (var_v0_2 + 0x13) % 40;
            if (temp_hi_3 != temp_hi) {
                if (temp_a2 != 0) {
                    snd_play_se(0x21, 0x28, temp_a2, temp_hi);
                } else if (temp_a0 != 0) {
                    snd_play_se(0x2C, 0x28, temp_a2, temp_hi);
                }
            }
            if (D_801D35AE & 0x860) {
                snd_play_se(0x2D);
                if (temp_hi_3 == 0x27) {
                    D_80173138 = 1;
                    func_8003A1AC(-1);
                } else {
                    temp_v1_2 = D_8012CF60;
                    D_8012CF60 = temp_v1_2 + 1;
                    *(&D_801D7770 + temp_v1_2) = temp_hi_3 + 0x41;
                    if (D_8012CF60 == 3) {
                        D_80173138 = 1;
                    }
                }
            }
            if ((D_801D35AE & 0x90) && (D_8012CF60 > 0)) {
                D_8012CF60 -= 1;
                snd_play_se(0x24);
            }
        } else {
            D_80173138 = temp_v1;
            if (temp_v1 == 0x5B) {
                func_8003B960();
                D_801D34F8 = 0xF;
                func_8003A1AC(-1);
            }
        }
    }
    func_8003B59C();
    func_80019A78();
}
