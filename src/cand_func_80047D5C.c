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
