/* cand_func_800181C8.c -- one candidate function, decompiled by m2c.
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

extern s32 D_801733A0;
extern s32 D_801733D8;
extern s32 D_801E90E0;

void func_800181C8(s32 arg0, s32 arg1, void *arg2, void *arg3) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_hi;
    s32 temp_s1;
    s32 temp_v1;
    s32 var_a2;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    void *temp_s2;
    void *temp_s3;

    temp_a1 = arg0 >> 8;
    temp_v1 = D_801E90E0 << 8;
    temp_hi = (s32) (temp_a1 + temp_v1) % (s32) D_801E90E0;
    temp_s1 = arg0 & 0xFF;
    temp_s3 = (temp_hi * 0x14) + D_801733D8;
    temp_a0 = 0x100 - temp_s1;
    var_a2 = M2C_FIELD(temp_s3, s32 *, 0);
    temp_s2 = (((s32) (temp_a1 + (temp_v1 + 1)) % (s32) D_801E90E0) * 0x14) + D_801733D8;
    if (var_a2 < 0) {
        var_a2 += 0x3FFF;
    }
    var_v1 = (temp_a0 * (var_a2 >> 0xE)) + (temp_s1 * ((s32) M2C_FIELD(temp_s2, s32 *, 0) / 16384));
    if (var_v1 < 0) {
        var_v1 += 0xFF;
    }
    M2C_FIELD(arg2, s32 *, 0) = (s32) (D_801733A0 - (var_v1 >> 8));
    M2C_FIELD(arg2, s32 *, 4) = (s32) ((s32) ((s32) -((temp_a0 * M2C_FIELD(temp_s3, s16 *, 8)) + (temp_s1 * M2C_FIELD(temp_s2, s16 *, 8))) / 256) / 2);
    M2C_FIELD(arg2, s32 *, 8) = (s32) ((s32) ((temp_a0 * ((s32) M2C_FIELD(temp_s3, s32 *, 4) / 16384)) + (temp_s1 * ((s32) M2C_FIELD(temp_s2, s32 *, 4) / 16384))) / 256);
    M2C_FIELD(arg3, s32 *, 4) = (s32) (0x800 - func_800177B8(M2C_FIELD(temp_s3, s16 *, 0xA), M2C_FIELD(temp_s2, s16 *, 0xA), temp_s1, temp_hi));
    M2C_FIELD(arg3, s32 *, 0) = func_800177B8(M2C_FIELD(temp_s3, s16 *, 0xC) * 8, M2C_FIELD(temp_s2, s16 *, 0xC) * 8, temp_s1);
    M2C_FIELD(arg3, s32 *, 8) = 0;
    var_v0 = rcos(M2C_FIELD(arg3, s32 *, 4)) * arg1;
    if (var_v0 < 0) {
        var_v0 += 0x7FF;
    }
    M2C_FIELD(arg2, s32 *, 0) = (s32) ((var_v0 >> 0xB) + M2C_FIELD(arg2, s32 *, 0));
    var_v1_2 = rsin(M2C_FIELD(arg3, s32 *, 4)) * arg1;
    if (var_v1_2 < 0) {
        var_v1_2 += 0x7FF;
    }
    M2C_FIELD(arg2, s32 *, 8) = (s32) (M2C_FIELD(arg2, s32 *, 8) - (var_v1_2 >> 0xB));
}
