/* cand_func_80012EF0.c -- one candidate function, decompiled by m2c.
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
