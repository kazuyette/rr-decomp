/* cand_rsin.c -- one candidate function, decompiled by m2c.
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

s32 rsin_quadrant(s32);

s32 rsin(s32 arg0) {
    if (arg0 < 0) {
        return -rsin_quadrant((s32) -arg0 % 4096);
    }
    return rsin_quadrant(arg0 % 4096);
}
