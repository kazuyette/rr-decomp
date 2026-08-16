/* cand_func_80047604.c -- one candidate function, decompiled by m2c.
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

extern M2C_UNK D_7FFFFF;
extern s32 D_80077388;
extern s32 D_8007738C;
extern s32 *D_80077394;
extern s32 *D_800773A0;

s32 func_80047604(s32 arg0) {
    M2C_UNK *var_s0;
    M2C_UNK *var_s0_2;
    M2C_UNK *var_s0_3;
    s32 temp_v0;
    s32 var_v0;

    if (arg0 == 0) {
        if (D_80077388 != D_8007738C) {
            var_s0 = &D_7FFFFF;
loop_3:
            if (var_s0 != (M2C_UNK *)-1) {
                if (!(*D_800773A0 & 0x01000000)) {
                    func_80047354();
                }
                var_s0 -= 1;
                if (D_80077388 == D_8007738C) {
                    goto block_8;
                }
                goto loop_3;
            }
            func_80046738();
            return -1;
        }
block_8:
        var_s0_2 = &D_7FFFFF;
loop_9:
        if (var_s0_2 != (M2C_UNK *)-1) {
            if (!(*D_80077394 & 0x60000000)) {
                if (!(*D_80077394 & 0x10000000)) {
                    var_s0_2 -= 1;
                    goto loop_9;
                }
                goto block_15;
            }
            var_s0_2 -= 1;
            if (!(*D_800773A0 & 0x01000000)) {
                *D_80077394 = 0x04000000;
block_15:
                var_v0 = *D_80077394 & 0x04000000;
                if (var_v0 == 0) {
                    var_s0_3 = &D_7FFFFF;
loop_17:
                    if (var_s0_3 != (M2C_UNK *)-1) {
                        temp_v0 = *D_80077394 & 0x04000000;
                        var_s0_3 -= 1;
                        if (temp_v0 != 0) {
                            return temp_v0;
                        }
                        goto loop_17;
                    }
                    func_80046738(0x04000000, -1, 0x10000000, 0x60000000);
                    return -1;
                }
                
                return var_v0;
            }
            goto loop_9;
        }
        func_80046738(0x01000000, 0x04000000, 0x10000000, 0x60000000);
        return -1;
    }
    if (D_80077388 != D_8007738C) {
        return (D_80077388 - D_8007738C) & 0x3F;
    }
    var_v0 = 1;
    if (*D_80077394 & 0x10000000) {
        if (*D_80077394 & 0x04000000) {
            return 1;
        }
        var_v0 = 0;
        
        return var_v0;
    }
    return var_v0;
}
