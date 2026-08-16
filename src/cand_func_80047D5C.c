/* cand_func_80047D5C.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_80010FB8;
extern M2C_UNK D_80010FE0;
extern M2C_UNK D_80010FF8;
extern M2C_UNK D_80011008;
extern M2C_UNK D_80011020;
extern M2C_UNK D_8001102C;

void func_80047D5C(void *arg0) {
    s16 var_a1;
    u16 temp_a3;
    u16 temp_a3_2;
    u32 var_a2;

    D_80077370(&D_80010FE0, M2C_FIELD(arg0, s16 *, 0), M2C_FIELD(arg0, s16 *, 2), M2C_FIELD(arg0, s16 *, 4), (s32) M2C_FIELD(arg0, s16 *, 6));
    D_80077370(&D_80010FF8, M2C_FIELD(arg0, s16 *, 8), M2C_FIELD(arg0, s16 *, 0xA));
    D_80077370(&D_80011008, M2C_FIELD(arg0, s16 *, 0xC), M2C_FIELD(arg0, s16 *, 0xE), M2C_FIELD(arg0, s16 *, 0x10), (s32) M2C_FIELD(arg0, s16 *, 0x12));
    D_80077370(&D_80011020, (s16) M2C_FIELD(arg0, u8 *, 0x16));
    D_80077370(&D_8001102C, (s16) M2C_FIELD(arg0, u8 *, 0x17));
    if (func_80045718() != 0) {
        temp_a3 = M2C_FIELD(arg0, u16 *, 0x14);
        var_a1 = (temp_a3 >> 9) & 3;
        var_a2 = temp_a3 >> 7;
    } else {
        temp_a3_2 = M2C_FIELD(arg0, u16 *, 0x14);
        var_a1 = (temp_a3_2 >> 7) & 3;
        var_a2 = temp_a3_2 >> 5;
    }
    D_80077370(&D_80010FB8, var_a1, var_a2 & 3, (M2C_FIELD(arg0, u16 *, 0x14) << 6) & 0x7C0);
}
