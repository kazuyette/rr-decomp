/* cand_func_800403F8.c -- one candidate function, decompiled by m2c.
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



void *func_800403F8(void *arg0, void *arg1) {
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;

    temp_s2 = func_80040770(M2C_FIELD(arg0, s16 *, 0));
    temp_s3 = func_80040770(M2C_FIELD(arg0, s16 *, 2));
    temp_v0 = func_80040770(M2C_FIELD(arg0, s16 *, 4));
    sp34 = temp_v0;
    temp_v0_2 = func_80040868(M2C_FIELD(arg0, s16 *, 0));
    sp30 = temp_v0_2;
    temp_a2 = -func_80040868(M2C_FIELD(arg0, s16 *, 2), temp_v0_2);
    sp2C = temp_a2;
    temp_v0_3 = func_80040868(M2C_FIELD(arg0, s16 *, 4), temp_v0_2, temp_a2, temp_v0);
    M2C_FIELD(arg1, s16 *, 0) = (s16) ((s32) (temp_v0 * temp_s3) >> 0xC);
    temp_v1 = (s32) (temp_v0 * temp_a2) >> 0xC;
    M2C_FIELD(arg1, s16 *, 6) = (s16) (((s32) (temp_v0_3 * temp_s2) >> 0xC) - ((s32) (temp_v1 * temp_v0_2) >> 0xC));
    M2C_FIELD(arg1, s16 *, 0xC) = (s16) (((s32) (temp_v0_3 * temp_v0_2) >> 0xC) + ((s32) (temp_v1 * temp_s2) >> 0xC));
    M2C_FIELD(arg1, s16 *, 2) = (s16) ((s32) -(temp_v0_3 * temp_s3) >> 0xC);
    temp_a0 = (s32) (temp_v0_3 * temp_a2) >> 0xC;
    M2C_FIELD(arg1, s16 *, 4) = (s16) -temp_a2;
    M2C_FIELD(arg1, s16 *, 8) = (s16) (((s32) (temp_v0 * temp_s2) >> 0xC) + ((s32) (temp_a0 * temp_v0_2) >> 0xC));
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) (((s32) (temp_v0 * temp_v0_2) >> 0xC) - ((s32) (temp_a0 * temp_s2) >> 0xC));
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((s32) -(temp_s3 * temp_v0_2) >> 0xC);
    M2C_FIELD(arg1, s16 *, 0x10) = (s16) ((s32) (temp_s3 * temp_s2) >> 0xC);
    return arg1;
}
