/* cand_func_8002F1A4.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_800743B8;
extern M2C_UNK D_800743CC;
extern s16 D_8012D908;
extern s32 D_801E91E0;

s32 func_8002F1A4(s32 arg0) {
    s32 temp_s0;
    s32 var_a0;
    s32 var_a1;
    s32 var_s2;
    void *temp_s0_2;
    void *temp_s1;

    temp_s0 = (D_8012D908 < 2) * 0x10;
    var_a1 = func_80029278(arg0, func_80029278(arg0, func_80029278(arg0, func_80029278(arg0, func_80029278(0x58, 0xC0, 0x38, 0x10, 0, temp_s0, 0xE4), 0xA8, 0xC0, 0x38, 0x10, 0, 0x10 - temp_s0, 0xE3), 0x10, 0x30, 0x48, 0x10, 0xB8, 0x10, 0xE6), 0x7C, 0x40, 0x48, 0x10, 0xB8, 0, 0xE5), 0xE8, 0x30, 0x48, 0x10, 0xB8, 0x20, 0xE7);
    if ((u32) (D_801E91E0 + 0xF) < 0x1FU) {
        var_s2 = 0;
        var_a0 = 0 * 4;
        do {
            temp_s1 = var_a0 + &D_800743B8;
            temp_s0_2 = (((u16) D_8012D908 & 1) * 0x14) + (var_a0 + &D_800743CC);
            var_s2 += 1;
            var_a1 = func_8002F0D0(arg0, func_8002F0D0(arg0, func_8002F0D0(arg0, var_a1, 0, M2C_FIELD(temp_s1, s16 *, 0), (s32) M2C_FIELD(temp_s1, s16 *, 2), (s32) M2C_FIELD(temp_s0_2, s16 *, 0), (s32) M2C_FIELD(temp_s0_2, s16 *, 2), 0, 0, 0), 1, M2C_FIELD(temp_s1, s16 *, 0) - 1, (s32) M2C_FIELD(temp_s1, s16 *, 2), M2C_FIELD(temp_s0_2, s16 *, 0) - 1, (s32) M2C_FIELD(temp_s0_2, s16 *, 2), 0, 0, 0), 1, M2C_FIELD(temp_s1, s16 *, 0) + 1, (s32) M2C_FIELD(temp_s1, s16 *, 2), M2C_FIELD(temp_s0_2, s16 *, 0) + 1, (s32) M2C_FIELD(temp_s0_2, s16 *, 2), 0, 0, 0);
            var_a0 = var_s2 * 4;
        } while (var_s2 < 5);
    }
    return var_a1;
}
