/* cand_func_8004DB58.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8012D0C0;
extern s32 D_801D7E20;
extern s32 D_801D9028;

void func_8004DB58(s32 arg0) {
    if (arg0 & 0x1000) {
        D_8012D0C0 = 1;
        D_801D7E20 = arg0 & 0xFFF;
    } else {
        D_8012D0C0 = 0;
        D_801D7E20 = arg0;
    }
    if (D_801D7E20 < 4) {
        switch (D_801D7E20) {
        case 3:
            D_801D9028 = 0x78;
            return;
        case 2:
            D_801D9028 = 0xF0;
            return;
        case 1:
            
        default:
            D_801D9028 = 0x3C;
            return;
        }
    } else {
        D_801D9028 = D_801D7E20;
    }
}
