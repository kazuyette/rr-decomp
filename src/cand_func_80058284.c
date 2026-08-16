/* cand_func_80058284.c -- one candidate function, decompiled by m2c.
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

extern s32 D_800775B0;
extern s32 D_800775B4;
extern s32 D_80077720;
extern s32 *D_80077728;
extern s32 D_8007B1A0;
extern s32 D_801E9238;

s32 func_80058284(s32 arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a2_2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;
    s32 var_v0;
    u32 temp_s1;
    u32 temp_t1;
    void *temp_a2;
    void *temp_v0;
    void *temp_v1_3;
    void *temp_v1_4;
    void *var_a0;

    var_s0 = 0;
    var_s2 = -1;
    if (D_8007B1A0 == 0) {
        var_s3 = 0;
    } else {
        var_s3 = (0x10000 - D_801E9238) << D_80077720;
    }
    temp_a0 = (1 << D_80077720) - 1;
    var_a1 = arg0;
    if (arg0 & ~temp_a0) {
        var_a1 = arg0 + temp_a0;
    }
    temp_s1 = (var_a1 >> D_80077720) << D_80077720;
    if (*D_80077728 & 0x40000000) {
        var_s2 = 0;
    } else {
        func_80057F18(temp_a0, var_a1);
        if (D_800775B0 > 0) {
            var_a0 = (0 * 8) + D_80077728;
loop_9:
            temp_v1 = M2C_FIELD(var_a0, s32 *, 0);
            if ((temp_v1 & 0x40000000) || ((temp_v1 & 0x80000000) && ((u32) M2C_FIELD(var_a0, u32 *, 4) >= temp_s1))) {
                var_s2 = var_s0;
            } else {
                var_s0 += 1;
                var_a0 += 8;
                if (var_s0 < D_800775B0) {
                    goto loop_9;
                }
            }
        }
    }
    var_v0 = -1;
    temp_s0 = var_s2 * 8;
    if (var_s2 != -1) {
        temp_a2 = temp_s0 + D_80077728;
        temp_v1_2 = M2C_FIELD(temp_a2, s32 *, 0);
        if (temp_v1_2 & 0x40000000) {
            var_v0 = -1;
            if (var_s2 < D_800775B0) {
                var_v0 = -1;
                if ((u32) (M2C_FIELD(temp_a2, u32 *, 4) - var_s3) >= temp_s1) {
                    temp_a0_2 = var_s2 + 1;
                    temp_v1_3 = (temp_a0_2 * 8) + D_80077728;
                    M2C_FIELD(temp_v1_3, s32 *, 0) = (s32) (((M2C_FIELD(temp_a2, s32 *, 0) & 0x0FFFFFFF) + temp_s1) | 0x40000000);
                    M2C_FIELD(temp_v1_3, s32 *, 4) = (s32) (M2C_FIELD(temp_a2, u32 *, 4) - temp_s1);
                    D_800775B4 = temp_a0_2;
                    M2C_FIELD(temp_a2, u32 *, 4) = temp_s1;
                    M2C_FIELD(temp_a2, s32 *, 0) = (s32) (M2C_FIELD(temp_a2, s32 *, 0) & 0x0FFFFFFF);
                    func_80057F18(temp_a0_2, 0x0FFFFFFF, temp_a2, 0x40000000);
                    return *(temp_s0 + D_80077728);
                }
            }
            
            return var_v0;
        }
        temp_t1 = M2C_FIELD(temp_a2, u32 *, 4);
        temp_s0_2 = var_s2 * 8;
        if ((temp_s1 < temp_t1) && (D_800775B4 < D_800775B0)) {
            temp_v0 = (D_800775B4 * 8) + D_80077728;
            temp_a1 = M2C_FIELD(temp_v0, s32 *, 0);
            temp_a2_2 = M2C_FIELD(temp_v0, s32 *, 4);
            M2C_FIELD(temp_v0, s32 *, 0) = (s32) ((temp_s1 + temp_v1_2) | 0x80000000);
            M2C_FIELD(temp_v0, s32 *, 4) = (s32) (temp_t1 - temp_s1);
            D_800775B4 += 1;
            M2C_FIELD(temp_v0, s32 *, 8) = temp_a1;
            M2C_FIELD(temp_v0, s32 *, 0xC) = temp_a2_2;
        }
        temp_v1_4 = temp_s0_2 + D_80077728;
        M2C_FIELD(temp_v1_4, u32 *, 4) = temp_s1;
        M2C_FIELD(temp_v1_4, s32 *, 0) = (s32) (M2C_FIELD(temp_v1_4, s32 *, 0) & 0x0FFFFFFF);
        func_80057F18(0x0FFFFFFF);
        var_v0 = *(temp_s0_2 + D_80077728);
        
        return var_v0;
    }
    return var_v0;
}
