/* cand_func_8004E380.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_801E90E8;

void func_8004E380(s16 arg0, s16 arg1) {
    u16 sp10;
    u16 sp12;
    s16 temp_a0;
    s16 temp_a2_2;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s32 *temp_s0;
    s32 temp_a2_3;
    s32 temp_s0_2;
    s32 temp_s1;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_s0;
    s32 var_v0;
    void *temp_a0_2;
    void *temp_a2;
    void *temp_v1;
    void *var_v0_2;

    temp_s0 = (arg0 * 4) + &D_801E90E8;
    temp_s1 = arg1 * 0xA8;
    temp_v1 = temp_s1 + *temp_s0;
    M2C_FIELD(temp_v1, s32 *, 0x98) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x98) - 1);
    temp_a2 = temp_s1 + *temp_s0;
    temp_v1_2 = M2C_FIELD(temp_a2, s16 *, 0x40);
    if (temp_v1_2 > 0) {
        var_v0 = arg1 << 0x10;
        if (((u32) M2C_FIELD(temp_a2, u32 *, 0x98) % (u32) temp_v1_2) == 0) {
            temp_v0 = M2C_FIELD(temp_a2, s16 *, 0x3C);
            if (temp_v0 > 0) {
                M2C_FIELD(temp_a2, u16 *, 0x3E) = (u16) (M2C_FIELD(temp_a2, u16 *, 0x3E) - 1);
                if (M2C_FIELD((temp_s1 + *temp_s0), s16 *, 0x3E) >= 0) {
                    func_8004B688(arg0, &sp10, &sp12, &D_801E90E8);
                    if ((sp10 != 0) && (sp12 != 0)) {
                        var_a1 = sp10 - 1;
                        var_a2 = sp12 - 1;
                        goto block_26;
                    }
                    func_8004B530(arg0, 0, 0, 0);
                    var_v0_2 = (arg1 * 0xA8) + *(&D_801E90E8 + (arg0 * 4));
                    goto block_30;
                }
                var_a1_2 = 0;
                var_a2_2 = 0;
                goto block_29;
            }
            var_a0 = arg1 << 0x10;
            if (temp_v0 < 0) {
                M2C_FIELD(temp_a2, u16 *, 0x3E) = (u16) (M2C_FIELD(temp_a2, u16 *, 0x3E) + 1);
                if (M2C_FIELD((temp_s1 + *temp_s0), s16 *, 0x3E) <= 0) {
                    func_8004B688(arg0, &sp10, &sp12, &D_801E90E8);
                    var_a1 = sp10 + 1;
                    if ((var_a1 >= 0x80) || (var_a2 = sp12 + 1, ((var_a2 < 0x80) == 0))) {
                        func_8004B530(arg0, 0x7F, 0x7F, 0);
                        var_v0_2 = (arg1 * 0xA8) + *(&D_801E90E8 + (arg0 * 4));
                        goto block_30;
                    }
                    goto block_26;
                }
                goto block_28;
            }
            goto block_32;
        }
    } else {
        temp_v0_2 = M2C_FIELD(temp_a2, s16 *, 0x3C);
        if (temp_v0_2 > 0) {
            M2C_FIELD(temp_a2, u16 *, 0x3E) = (u16) (M2C_FIELD(temp_a2, u16 *, 0x3E) + temp_v1_2);
            if (M2C_FIELD((temp_s1 + *temp_s0), s16 *, 0x3E) >= 0) {
                func_8004B688(arg0, &sp10, &sp12, &D_801E90E8);
                temp_v1_3 = M2C_FIELD((temp_s1 + *temp_s0), s16 *, 0x40);
                temp_a0 = -temp_v1_3;
                if ((s32) sp10 >= temp_a0) {
                    var_s0 = arg0 << 0x10;
                    if ((s32) sp12 >= temp_a0) {
                        var_a1 = sp10 + temp_v1_3;
                        var_a2 = sp12 + temp_v1_3;
                        goto block_26;
                    }
                    goto block_20;
                }
                var_s0 = arg0 << 0x10;
block_20:
                temp_s0_2 = var_s0 >> 0x10;
                func_8004B530((s16) temp_s0_2, 0, 0, 0);
                var_v0_2 = (arg1 * 0xA8) + *(&D_801E90E8 + (temp_s0_2 * 4));
                goto block_30;
            }
            var_a1_2 = 0;
            var_a2_2 = 0;
            goto block_29;
        }
        if (temp_v0_2 < 0) {
            M2C_FIELD(temp_a2, u16 *, 0x3E) = (u16) (M2C_FIELD(temp_a2, u16 *, 0x3E) - temp_v1_2);
            if (M2C_FIELD((temp_s1 + *temp_s0), s16 *, 0x3E) <= 0) {
                func_8004B688(arg0, &sp10, &sp12, &D_801E90E8);
                temp_a2_2 = M2C_FIELD((temp_s1 + *temp_s0), s16 *, 0x40);
                var_a1 = sp10 - temp_a2_2;
                if ((var_a1 < 0x80) && (var_a2 = sp12 - temp_a2_2, ((var_a2 < 0x80) != 0))) {
block_26:
                    func_8004B530(arg0, var_a1, var_a2, 0);
                    var_a0 = arg1 << 0x10;
                } else {
                    func_8004B530(arg0, 0x7F, 0x7F, 0);
                    var_v0_2 = (arg1 * 0xA8) + *(&D_801E90E8 + (arg0 * 4));
                    goto block_30;
                }
            } else {
block_28:
                var_a1_2 = 0x7F;
                var_a2_2 = 0x7F;
block_29:
                func_8004B530(arg0, var_a1_2, var_a2_2, 0);
                var_v0_2 = temp_s1 + *temp_s0;
block_30:
                M2C_FIELD(var_v0_2, s32 *, 0x90) = (s32) (M2C_FIELD(var_v0_2, s32 *, 0x90) & ~0x20);
                goto block_31;
            }
        } else {
block_31:
            var_a0 = arg1 << 0x10;
        }
block_32:
        temp_a0_2 = ((var_a0 >> 0x10) * 0xA8) + *(&D_801E90E8 + ((s32) (arg0 << 0x10) >> 0xE));
        if ((M2C_FIELD(temp_a0_2, s32 *, 0x98) == 0) || (var_v0 = arg1 << 0x10, (M2C_FIELD(temp_a0_2, s16 *, 0x3E) == 0))) {
            M2C_FIELD(temp_a0_2, s32 *, 0x90) = (s32) (M2C_FIELD(temp_a0_2, s32 *, 0x90) & ~0x20);
            var_v0 = arg1 << 0x10;
        }
    }
    temp_a2_3 = ((var_v0 >> 0x10) * 0xA8) + *(&D_801E90E8 + (arg0 * 4));
    func_8004B688(arg0, temp_a2_3 + 0x76, temp_a2_3 + 0x78);
}
