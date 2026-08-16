/* cand_func_8001AE90.c -- one candidate function, decompiled by m2c.
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

extern s32 D_80173140;
extern s16 D_801D354E;
extern s16 D_801D3550;
extern s16 D_801D3554;
extern s16 D_801D3556;
extern s16 D_801D355A;
extern s16 D_801D355C;
extern s16 D_801D3560;
extern s16 D_801D3562;
extern s16 D_801D356C;
extern s32 D_801D7800;
extern s32 D_801D7E38;

void func_8001AE90(void) {
    s16 temp_v1;
    s32 temp_a2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v0;

    var_a0 = (((s32) D_801D7800 / 500) + (((s32) (D_80173140 * 0x78) / 256) + 0x14)) * D_801D7E38;
    if (var_a0 < 0) {
        var_a0 += 0xFF;
    }
    D_801D354E = (s16) (var_a0 >> 8);
    D_801D356C = 0;
    temp_a2 = D_80173140 * 0x1E;
    temp_v1 = ((s32) (D_801D7800 * 0x1800) / 10000) + 0x1200;
    D_801D3550 = temp_v1;
    var_v0 = temp_a2;
    if (temp_a2 < 0) {
        var_v0 = temp_a2 + 0xFF;
    }
    var_a0_2 = (((s32) D_801D7800 / 250) - ((var_v0 >> 8) - 0x23)) * D_801D7E38;
    if (var_a0_2 < 0) {
        var_a0_2 += 0xFF;
    }
    D_801D355A = (s16) (var_a0_2 >> 8);
    D_801D355C = temp_v1;
    D_801D3554 = (s16) ((s32) ((((s32) D_801D7800 / 1000) + (((s32) (D_80173140 * 0x50) / 256) + 0xA)) * D_801D7E38) / 256);
    D_801D3556 = temp_v1;
    D_801D3560 = 0;
    D_801D3562 = temp_v1;
    D_801D3560 = (s16) ((s32) ((temp_a2 / 256) * D_801D7E38) / 256);
    D_801D3562 = temp_v1;
}
