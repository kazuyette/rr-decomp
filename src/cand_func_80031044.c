/* cand_func_80031044.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8012D020;
extern s16 D_801D34F8;
extern u16 D_801D35AA;

void func_80031044(void) {
    if ((D_8012D020 & 1) && (D_801D35AA & 0x1000)) {
        D_801D34F8 = 0x13;
    }
    if ((D_8012D020 & 0x100) && (D_801D35AA & 0x4000)) {
        D_801D34F8 = 0x13;
    }
    if ((D_8012D020 & 0x200) && (D_801D35AA & 0x8000)) {
        D_801D34F8 = 8;
    }
}
