/* cand_func_80013338.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_8012D950;
extern M2C_UNK D_8012D966;
extern M2C_UNK D_8012D968;
extern M2C_UNK D_8012D969;
extern M2C_UNK D_8012D96A;
extern M2C_UNK D_8012D96B;
extern M2C_UNK D_8012D9AC;
extern M2C_UNK D_80150544;
extern M2C_UNK D_801505A0;

void func_80013338(s8 arg0, s8 arg1, s8 arg2) {
    s32 var_v1;

    SetVideoMode(1);
    func_80040CB8();
    func_8003FC9C(0xA0, 0x78);
    func_8003FCB4(0x140);
    func_8004809C(&D_8012D950, 0, 0, 0x140, 0xF0);
    func_8004809C(&D_80150544, 0, 0xF0, 0x140, 0xF0);
    func_80048128(&D_8012D9AC, 0, 0xF0, 0x140, 0xF0);
    func_80048128(&D_801505A0, 0, 0, 0x140, 0xF0);
    var_v1 = 0;
    do {
        *(&D_8012D966 + var_v1) = 1;
        *(&D_8012D968 + var_v1) = 1;
        *(&D_8012D969 + var_v1) = arg0;
        *(&D_8012D96A + var_v1) = arg1;
        *(&D_8012D96B + var_v1) = arg2;
        var_v1 += 0x22BF4;
    } while (var_v1 < 0x457E8);
    func_800132D4(0, 0x457E8);
    func_800132D4(1);
}
