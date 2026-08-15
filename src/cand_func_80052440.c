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

extern M2C_UNK D_80011544;
extern M2C_UNK D_80076C0C;
extern s32 D_80076C80;
extern M2C_UNK D_800774EC;
extern u8 D_80077610;

void func_80052440(s32 arg0) {
    s32 *var_s1;
    s32 temp_a1;
    s32 var_s2;
    u8 *var_s0;

    var_s0 = &D_80077610;
    var_s1 = &D_80076C80;
    var_s2 = 0;
    func_800496C8(&D_80011544, *(&D_80076C0C + ((arg0 & 0xFF) * 4)));
    do {
        temp_a1 = *var_s1;
        var_s1 += 4;
        var_s2 += 1;
        func_800496C8(&D_800774EC, temp_a1, *var_s0);
        *var_s0 = 0;
        var_s0 += 1;
    } while (var_s2 < 6);
    func_800534C8(0xA);
}
