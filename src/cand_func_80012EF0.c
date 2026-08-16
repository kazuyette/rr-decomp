/* cand_func_80012EF0.c -- one candidate function, decompiled by m2c.
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

extern s32 D_8012D8E0;
extern s32 D_8012D8E8;
extern s32 D_801D9030;
extern s32 D_801D9040;
extern s32 D_801E90E0;

s32 func_80012EF0(s32 arg0) {
    s32 temp_hi;
    s32 var_v0;

    temp_hi = (s32) (arg0 + (D_801E90E0 << 0x10)) % (s32) (D_801E90E0 << 8);
    if ((temp_hi < D_8012D8E0) && (D_801D9030 < temp_hi)) {
        var_v0 = D_8012D8E0 - temp_hi;
        if ((D_8012D8E0 - 0x100) >= temp_hi) {
            if (temp_hi < (D_801D9030 + 0x100)) {
                return temp_hi - D_801D9030;
            }
            goto block_9;
        }
        
        return var_v0;
    }
    var_v0 = temp_hi < D_8012D8E8;
    if (var_v0 != 0) {
        var_v0 = D_801D9040 < temp_hi;
        if (var_v0 != 0) {
            var_v0 = D_8012D8E8 - temp_hi;
            if ((D_8012D8E8 - 0x100) >= temp_hi) {
                var_v0 = temp_hi - D_801D9040;
                if (temp_hi >= (D_801D9040 + 0x100)) {
block_9:
                    var_v0 = 0x100;
                }
            }
        }
    }
    return var_v0;
}
