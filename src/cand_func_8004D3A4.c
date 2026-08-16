/* cand_func_8004D3A4.c -- one candidate function, decompiled by m2c.
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



s32 func_8004D3A4(s32 arg0) {
    /* Written as two returns rather than m2c's "initialise then overwrite
     * under a condition". GCC 2.7.2 if-converts the latter into xori/negu
     * -- branchless arithmetic -- while the retail code branches. Same
     * meaning, different shape; this is the experiment. */
    if ((u32) (arg0 & 0xFFFF) < 0x18U) {
        return 0;
    }
    return -1;
}
