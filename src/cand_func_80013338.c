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
