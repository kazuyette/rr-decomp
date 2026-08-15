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

extern s32 D_80077A08;
extern s32 D_80077A0C;
extern s32 D_80077A10;
extern s32 D_80077A14;
extern s32 D_80077A18;
extern s32 D_80077A1C;
extern s32 D_80077A20;
extern s32 D_80077A24;
extern s32 D_80077A28;
extern s32 D_80077A2C;
extern s32 D_80077A30;
extern s32 D_80077A34;

s32 func_800468E4(void *arg0, s32 arg1) {
    u16 sp10;
    u16 sp12;
    u16 sp14;
    u16 sp16;
    s16 var_v1;
    s16 var_v1_2;
    u16 temp_v0;

    sp10 = M2C_FIELD(arg0, u16 *, 0);
    sp12 = M2C_FIELD(arg0, u16 *, 2);
    temp_v0 = M2C_FIELD(arg0, u16 *, 4);
    sp14 = temp_v0;
    sp16 = M2C_FIELD(arg0, u16 *, 6);
    if ((s16) temp_v0 > 0) {
        var_v1 = (s16) temp_v0;
        if (var_v1 >= 0x400) {
            var_v1 = 0x3FF;
        }
    } else {
        var_v1 = 1;
    }
    sp14 = var_v1;
    if ((s16) sp16 > 0) {
        var_v1_2 = (s16) sp16;
        if (var_v1_2 >= 0x200) {
            var_v1_2 = 0x1FF;
        }
    } else {
        var_v1_2 = 1;
    }
    sp16 = var_v1_2;
    if ((sp10 & 0x3F) || ((u16) sp14 & 0x3F)) {
        D_80077A08 = ((s32) &D_80077A28 & 0xFFFFFF) | 0x07000000;
        D_80077A0C = 0xE3000000;
        D_80077A10 = 0xE4FFFFFF;
        D_80077A14 = 0xE5000000;
        D_80077A18 = 0xE6000000;
        D_80077A1C = (arg1 & 0xFFFFFF) | 0x60000000;
        D_80077A28 = 0x03FFFFFF;
        D_80077A20 = (s32) sp10;
        D_80077A24 = (s32) sp14;
        D_80077A2C = func_80047154(3, (s32) sp14, &D_80077A28) | 0xE3000000;
        D_80077A30 = func_80047154(4) | 0xE4000000;
        D_80077A34 = func_80047154(5) | 0xE5000000;
    } else {
        D_80077A08 = 0x04FFFFFF;
        D_80077A0C = 0xE6000000;
        D_80077A10 = (arg1 & 0xFFFFFF) | 0x02000000;
        D_80077A14 = (s32) sp10;
        D_80077A18 = (s32) sp14;
    }
    func_800470D0(&D_80077A08);
    return 0;
}
