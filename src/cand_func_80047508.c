/* cand_func_80047508.c -- one candidate function, decompiled by m2c.
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

extern s32 D_80077388;
extern s32 D_8007738C;
extern s32 *D_80077390;
extern u32 *D_80077394;
extern s32 *D_800773A0;

s32 func_80047508(s32 arg0) {
    switch (arg0) {
    case 0:
        *D_800773A0 = 0x401;
        *D_80077394 = 0;
block_5:
        D_8007738C = 0;
        D_80077388 = D_8007738C;
        break;
    case 1:
        *D_800773A0 = 0x401;
        *D_80077394 = 0x04000000;
        *D_80077394 = 0x02000000;
        *D_80077394 = 0x01000000;
        goto block_5;
    }
    *D_80077390 = (*D_80077394 & 0x3FFF) | 0xE1001000;
    return ((u32) *D_80077394 >> 0xC) & 1;
}
