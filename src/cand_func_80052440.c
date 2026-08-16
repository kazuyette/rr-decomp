/* cand_func_80052440.c -- one candidate function, decompiled by m2c.
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
    printf(&D_80011544, *(&D_80076C0C + ((arg0 & 0xFF) * 4)));
    do {
        temp_a1 = *var_s1;
        var_s1 += 4;
        var_s2 += 1;
        printf(&D_800774EC, temp_a1, *var_s0);
        *var_s0 = 0;
        var_s0 += 1;
    } while (var_s2 < 6);
    putchar(0xA);
}
