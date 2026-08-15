/* cand_AddPrim.c -- one candidate function, decompiled by m2c.
 *
 * One function per file on purpose. GCC 2.7.2 allocates registers with
 * the whole translation unit in view, so a function can reproduce the
 * retail bytes alone and miss when compiled beside others; batch 5 lost
 * nine that way. Isolated, a candidate is measured on its own merits,
 * and tools/apply_sweep.py only has to rename the file once the sweep
 * says which pipeline it belongs to.
 *
 * This batch is what the jump tables unlocked: m2c refuses a function
 * whose switch it cannot resolve, and the tables live in .rodata, in a
 * different file from the function. Feeding both to m2c recovered 174
 * functions, among them the largest in the game.
 */
#include "m2c_macros.h"

extern s32 D_800775B0;
extern s32 D_800775B4;
extern s32 D_80077720;
extern void *D_80077728;
extern s32 D_8007B1A0;
extern s32 D_801E9238;

s32 func_800588A0(s32 arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_a3_2;
    s32 temp_s1;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_s0;
    s32 var_s2;
    s32 var_v0;
    s32 var_v0_2;
    u32 var_a1;
    void *temp_v0;
    void *temp_v1;

    var_a0 = arg0;
    if (D_8007B1A0 == 0) {
        var_s2 = 0;
    } else {
        var_s2 = (0x10000 - D_801E9238) << D_80077720;
    }
    temp_a1 = (1 << D_80077720) - 1;
    temp_a3 = ~temp_a1;
    var_a2 = arg1;
    if (arg1 & temp_a3) {
        var_a2 = arg1 + temp_a1;
    }
    temp_s1 = (var_a2 >> D_80077720) << D_80077720;
    if (var_a0 & temp_a3) {
        var_a0 += temp_a1;
    }
    var_s0 = (var_a0 >> D_80077720) << D_80077720;
    var_v0 = -1;
    if (var_s0 >= 0x1000) {
        temp_a3_2 = var_s0 + temp_s1;
        var_v0 = -1;
        if (((0x10000 << D_80077720) - var_s2) >= temp_a3_2) {
            temp_a1_2 = var_s0 - 0x1000;
            if (M2C_FIELD(D_80077728, s32 *, 0) & 0x40000000) {
                temp_a2 = ((M2C_FIELD(D_80077728, s32 *, 4) + 0x1000) - var_s0) - temp_s1;
                if (temp_a1_2 > 0) {
                    if ((D_800775B0 - 2) >= D_800775B4) {
                        M2C_FIELD(D_80077728, s32 *, 0) = 0x80001000;
                        M2C_FIELD(D_80077728, s32 *, 4) = temp_a1_2;
                        M2C_FIELD(D_80077728, s32 *, 8) = var_s0;
                        M2C_FIELD(D_80077728, s32 *, 0xC) = temp_s1;
                        M2C_FIELD(D_80077728, s32 *, 0x10) = (s32) (temp_a3_2 | 0x40000000);
                        M2C_FIELD(D_80077728, s32 *, 0x14) = temp_a2;
                        var_v0_2 = 2;
                        goto block_15;
                    }
                    goto block_16;
                }
                var_v0 = -1;
                if ((D_800775B0 - 1) >= D_800775B4) {
                    M2C_FIELD(D_80077728, s32 *, 0) = var_s0;
                    M2C_FIELD(D_80077728, s32 *, 4) = temp_s1;
                    M2C_FIELD(D_80077728, s32 *, 8) = (s32) (temp_a3_2 | 0x40000000);
                    M2C_FIELD(D_80077728, s32 *, 0xC) = temp_a2;
                    var_v0_2 = 1;
block_15:
                    D_800775B4 = var_v0_2;
                    goto block_30;
                }
                
                return var_v0;
            }
            func_80057F18(D_80077728, temp_a1_2, var_a2, temp_a3_2);
            var_a0_2 = 0;
loop_18:
            temp_v1 = (var_a0_2 * 8) + D_80077728;
            temp_a1_3 = M2C_FIELD(temp_v1, s32 *, 0);
            if (temp_a1_3 < 0) {
                var_a1 = temp_a1_3 & 0x0FFFFFFF;
                if ((u32) var_s0 >= var_a1) {
                    if (((u32) var_s0 < (u32) (var_a1 + M2C_FIELD(temp_v1, s32 *, 4))) || (M2C_FIELD(temp_v1, s32 *, 8) & 0x40000000)) {
                        temp_v0 = (var_a0_2 * 8) + D_80077728;
                        var_a1 = (u32) var_s0;
                        if ((M2C_FIELD(temp_v0, s32 *, 4) - (var_s0 - (M2C_FIELD(temp_v0, s32 *, 0) & 0x0FFFFFFF))) >= temp_s1) {
                            goto block_29;
                        }
                    }
                    goto block_27;
                }
                if (M2C_FIELD(temp_v1, s32 *, 4) < temp_s1) {
                    var_a0_2 += 1;
                    goto loop_18;
                }
                goto block_29;
            }
            if (!(temp_a1_3 & 0x40000000)) {
block_27:
                var_a0_2 += 1;
                goto loop_18;
            }
            var_a1 = temp_a1_3 & 0x0FFFFFFF;
            if ((M2C_FIELD(temp_v1, s32 *, 4) - var_s2) >= temp_s1) {
block_29:
                var_s0 = func_80058544(var_a0_2, var_a1, temp_s1, 0x0FFFFFFF);
block_30:
                func_80057F18();
                var_v0 = var_s0;
                
                return var_v0;
            }
block_16:
            return -1;
        }
    }
    return var_v0;
}
