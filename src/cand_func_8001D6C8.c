/* cand_func_8001D6C8.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_8007307C;
extern M2C_UNK D_80077128;
extern s16 D_801D34E0;

s32 func_8001D6C8(s32 arg0, s32 arg2, s32 arg3, s32 arg4) {
    s32 sp28;
    s32 sp30;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s5;
    s32 var_s6;

    sp28 = arg2;
    var_s5 = 0;
    var_s6 = 0x10;
    temp_s1 = arg4 + 8;
    temp_v0 = func_80029278(arg3 + 0x10, temp_s1, 0x18, 8, 0xE8, 0xF8, 0x127);
    sp30 = arg3 + 0x30;
    temp_s0 = func_80029278(arg0, func_80029278(arg0, temp_v0, sp30, temp_s1, 0x18, 8, 0xE8, 0xF0, 0x127), arg3 + 0x18, arg4 + 0x10, 0x10, 0x18, (D_801D34E0 * 0x10) + 0x40, 0x28, 0x126);
    func_8004617C(temp_s0, 0, 1, func_8004788C(0, 0, 0x280, 0x100) & 0xFFFF, &D_80077128);
    AddPrim(arg0, temp_s0);
    var_s0 = func_80029650(arg0, func_80029278(arg0, func_8001D3B8(arg0, temp_s0 + 0xC, sp30, arg4 + 0x18, *(&D_8007307C + (D_801D34E0 * 4))), arg3, arg4, 0x10, 0x38, 0xE8, 0xB8, 0x127), arg3 + 0xB0, arg4, 0x10, 0x38, 0xE8, 0xB8, 0x127, sp28);
    do {
        var_s0 = func_80029278(arg0, var_s0, arg3 + var_s6, arg4, 8, 0x38, 0xF8, 0xB8, 0x127);
        var_s5 += 1;
        var_s6 += 8;
    } while (var_s5 < 0x14);
    return var_s0;
}
