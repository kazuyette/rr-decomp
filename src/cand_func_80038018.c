/* cand_func_80038018.c -- one candidate function, decompiled by m2c.
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

s32 func_800497C8(s16 *, u16);
extern M2C_UNK D_80074D94;
extern s16 D_8007C210;

void func_80038018(void *arg0) {
    s16 *temp_a2;
    s16 *temp_v0_8;
    s16 *var_a2;
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    u16 temp_a3;
    void *temp_a2_2;
    void *temp_a2_3;
    void *temp_a2_4;
    void *temp_a2_5;
    void *temp_a2_6;
    void *temp_a2_7;
    void *temp_a2_8;

    temp_a2 = M2C_FIELD(arg0, s16 **, 4);
    temp_a3 = M2C_FIELD(temp_a2, u16 *, 0);
    var_a2 = temp_a2 + 2;
    switch ((s16) temp_a3) {
    case 0:
        temp_a2_2 = var_a2 + 2;
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(temp_a2, u16 *, 2);
        temp_a2_3 = temp_a2_2 + 2;
        M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(var_a2, s16 *, 2);
        temp_a2_4 = temp_a2_3 + 2;
        M2C_FIELD(arg0, s32 *, 0x1C) = (s32) M2C_FIELD(temp_a2_2, u16 *, 2);
        temp_a2_5 = temp_a2_4 + 2;
        M2C_FIELD(arg0, s32 *, 0x44) = (s32) M2C_FIELD(temp_a2_3, s16 *, 2);
        M2C_FIELD(arg0, s32 *, 0x48) = (s32) M2C_FIELD(temp_a2_4, s16 *, 2);
        M2C_FIELD(arg0, s32 *, 0x4C) = (s32) M2C_FIELD(temp_a2_5, s16 *, 2);
        M2C_FIELD(arg0, s32 *, 0x34) = (s32) M2C_FIELD(arg0, s32 *, 0x14);
        M2C_FIELD(arg0, s32 *, 0x38) = (s32) M2C_FIELD(arg0, s32 *, 0x18);
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) M2C_FIELD(arg0, s32 *, 0x1C);
        M2C_FIELD(arg0, s32 *, 0x40) = (s32) M2C_FIELD(arg0, s32 *, 0x20);
        M2C_FIELD(arg0, s32 *, 0x64) = (s32) M2C_FIELD(arg0, s32 *, 0x44);
        M2C_FIELD(arg0, s32 *, 0x68) = (s32) M2C_FIELD(arg0, s32 *, 0x48);
        M2C_FIELD(arg0, s32 *, 0x6C) = (s32) M2C_FIELD(arg0, s32 *, 0x4C);
        M2C_FIELD(arg0, s32 *, 0x70) = (s32) M2C_FIELD(arg0, s32 *, 0x50);
        var_a2 = temp_a2_5 + 2 + 2;
        break;
    case 1:
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) M2C_FIELD(arg0, s32 *, 0x34);
        M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(arg0, s32 *, 0x38);
        M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(arg0, s32 *, 0x3C);
        M2C_FIELD(arg0, s32 *, 0x30) = (s32) M2C_FIELD(arg0, s32 *, 0x40);
        temp_a2_6 = var_a2 + 2;
        M2C_FIELD(arg0, s32 *, 0x34) = (s32) M2C_FIELD(temp_a2, u16 *, 2);
        temp_a2_7 = temp_a2_6 + 2;
        M2C_FIELD(arg0, s32 *, 0x38) = (s32) M2C_FIELD(var_a2, s16 *, 2);
        temp_a2_8 = temp_a2_7 + 2;
        M2C_FIELD(arg0, s32 *, 0x3C) = (s32) M2C_FIELD(temp_a2_6, u16 *, 2);
        M2C_FIELD(arg0, s32 *, 0x74) = (s32) M2C_FIELD(temp_a2_7, s16 *, 2);
        if (D_8007C210 >= 3) {
            M2C_FIELD(arg0, s32 *, 0x74) = (s32) M2C_FIELD(temp_a2_8, s16 *, 2);
        }
        var_a2 = temp_a2_8 + 2 + 2;
        M2C_FIELD(arg0, s32 *, 0x74) = (s32) (M2C_FIELD(arg0, s32 *, 0x74) << 8);
        
    case 2:
        temp_v0 = *var_a2;
        var_a2 += 2;
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
        M2C_FIELD(arg0, u16 *, 8) = temp_a3;
        M2C_FIELD(arg0, s32 *, 0x10) = (s32) temp_v0;
        break;
    case 3:
        temp_v0_2 = (s16) M2C_FIELD(temp_a2, u16 *, 2);
        var_a2 += 2;
        M2C_FIELD(arg0, s32 *, 0x64) = (s32) temp_v0_2;
        M2C_FIELD(arg0, s32 *, 0x44) = (s32) temp_v0_2;
        break;
    case 4:
        temp_v0_3 = (s16) M2C_FIELD(temp_a2, u16 *, 2);
        var_a2 += 2;
        M2C_FIELD(arg0, s32 *, 0x68) = (s32) temp_v0_3;
        M2C_FIELD(arg0, s32 *, 0x48) = (s32) temp_v0_3;
        break;
    case 5:
        temp_v0_4 = (s16) M2C_FIELD(temp_a2, u16 *, 2);
        var_a2 += 2;
        M2C_FIELD(arg0, s32 *, 0x6C) = (s32) temp_v0_4;
        M2C_FIELD(arg0, s32 *, 0x4C) = (s32) temp_v0_4;
        break;
    case 6:
        M2C_FIELD(arg0, s32 *, 0x64) = (s32) (s16) M2C_FIELD(temp_a2, u16 *, 2);
        temp_v0_5 = M2C_FIELD(var_a2, s16 *, 2);
        var_a2 = var_a2 + 2 + 2;
        M2C_FIELD(arg0, s32 *, 0x54) = (s32) temp_v0_5;
        break;
    case 7:
        M2C_FIELD(arg0, s32 *, 0x68) = (s32) (s16) M2C_FIELD(temp_a2, u16 *, 2);
        temp_v0_6 = M2C_FIELD(var_a2, s16 *, 2);
        var_a2 = var_a2 + 2 + 2;
        M2C_FIELD(arg0, s32 *, 0x58) = (s32) temp_v0_6;
        break;
    case 8:
        M2C_FIELD(arg0, s32 *, 0x6C) = (s32) (s16) M2C_FIELD(temp_a2, u16 *, 2);
        temp_v0_7 = M2C_FIELD(var_a2, s16 *, 2);
        var_a2 = var_a2 + 2 + 2;
        M2C_FIELD(arg0, s32 *, 0x5C) = (s32) temp_v0_7;
        break;
    case 9:
        temp_v0_8 = *(&D_80074D94 + ((func_800497C8(var_a2, temp_a3) & 1) * 4));
        M2C_FIELD(arg0, s32 *, 0x78) = 0;
        M2C_FIELD(arg0, s16 **, 0) = temp_v0_8;
        var_a2 = temp_v0_8;
        break;
    }
    M2C_FIELD(arg0, s16 **, 4) = var_a2;
}
