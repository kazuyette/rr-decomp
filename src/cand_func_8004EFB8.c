/* cand_func_8004EFB8.c -- one candidate function, decompiled by m2c.
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

void func_8004EFB8(s16 arg0, s16 arg1, s32 arg2) {
    s32 *temp_s1;
    s32 *temp_s1_2;
    s32 *temp_s4;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 var_v0;
    u32 temp_a2;
    u8 *temp_a3;
    u8 temp_s5;
    u8 temp_t0;
    void *temp_v0;
    void *temp_v1;
    void *var_s0;

    temp_v1 = (arg1 * 0xA8) + *(&D_801E90E8 + ((s32) (arg0 << 0x10) >> 0xE));
    temp_a3 = M2C_FIELD(temp_v1, u8 **, 4);
    temp_t0 = M2C_FIELD(temp_v1, u8 *, 0x12);
    temp_a2 = arg2 & 0xFF;
    M2C_FIELD(temp_v1, u8 **, 4) = (u8 *) (temp_a3 + 1);
    temp_s5 = *temp_a3;
    switch (temp_a2) {
    case 0x1:
        func_8004F3B8(arg0, arg1, temp_s5, temp_a3);
        return;
    case 0x5:
        func_8004F548(arg0, arg1, temp_s5, temp_a3);
        return;
    case 0x6:
        func_8004FF38(arg0, arg1, temp_s5, temp_a3);
        return;
    case 0x7:
        temp_s1 = (arg0 * 4) + &D_801E90E8;
        temp_s0 = arg1 * 0xA8;
        M2C_FIELD(((temp_t0 * 2) + (temp_s0 + *temp_s1)), s16 *, 0x4C) = (s16) temp_s5;
        var_v0 = func_80050DF8(arg0, arg1, temp_a2, temp_a3);
        var_s0 = temp_s0 + *temp_s1;
block_8:
        M2C_FIELD(var_s0, s32 *, 0x88) = var_v0;
        return;
    case 0xA:
        temp_s1_2 = (arg0 * 4) + &D_801E90E8;
        temp_s0_2 = arg1 * 0xA8;
        M2C_FIELD((temp_t0 + (temp_s0_2 + *temp_s1_2)), u8 *, 0x17) = temp_s5;
        var_v0 = func_80050DF8(arg0, arg1, temp_a2, temp_a3);
        var_s0 = temp_s0_2 + *temp_s1_2;
        goto block_8;
    case 0xB:
        temp_s4 = (arg0 * 4) + &D_801E90E8;
        temp_s0_3 = arg1 * 0xA8;
        temp_v0 = temp_s0_3 + *temp_s4;
        M2C_FIELD(((temp_t0 * 2) + (temp_s0_3 + *temp_s4)), s16 *, 0x4C) = (s16) ((s32) (temp_s5 * func_8004B74C(M2C_FIELD(temp_v0, s16 *, 0x4A), M2C_FIELD((temp_v0 + temp_t0), u8 *, 0x2C), temp_a2, temp_a3)) / 127);
        var_v0 = func_80050DF8(arg0, arg1);
        var_s0 = temp_s0_3 + *temp_s4;
        goto block_8;
    case 0x40:
        if (temp_s5 < 0x40U) {
            func_8004A4CC(temp_a2, temp_a3);
        } else {
            func_8004A4B8(temp_a2, temp_a3);
        }
block_22:
        M2C_FIELD(((arg1 * 0xA8) + *(&D_801E90E8 + (arg0 * 4))), s32 *, 0x88) = func_80050DF8(arg0, arg1);
        return;
    case 0x41:
        func_8004F6D8(arg0, arg1, temp_s5, temp_a3);
        return;
    case 0x5B:
        if (temp_s5 < 0x40U) {
            func_8004D3C0(temp_a2, temp_a3);
        } else {
            func_8004D3E0(temp_a2, temp_a3);
        }
        goto block_22;
    case 0x62:
        func_8004FA1C(arg0, arg1, temp_s5, temp_a3);
        return;
    case 0x63:
        func_8004FBEC(arg0, arg1, temp_s5, temp_a3);
        return;
    case 0x64:
        func_8004FE10(arg0, arg1, temp_s5, temp_a3);
        return;
    case 0x65:
        func_8004FEA4(arg0, arg1, temp_s5, temp_a3);
        return;
    case 0x79:
        func_8004F914(arg0, arg1, temp_s5, temp_a3);
        return;
    default:
        goto block_22;
    }
}
