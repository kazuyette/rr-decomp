#include "m2c_macros.h"

extern u8 *D_80077248;

u8 *func_80031378(u8 *arg0) {
    s32 var_v1;
    u8 *var_a1;
    u8 *var_a2;
    u8 *var_v0;

    var_a1 = arg0;
    var_a2 = D_80077248;
loop_1:
    var_v0 = NULL;
    if (*var_a2 == *var_a1) {
        var_a1 += 1;
        var_a2 += 1;
        if ((s32) var_a1 >= (arg0 + 0xC)) {
            var_v1 = 0;
            var_v0 = arg0;
loop_4:
            var_v0 = NULL;
            if ((u32) (M2C_FIELD(var_v0, u8 *, 0xC) - 0x30) < 0xAU) {
                var_v1 += 1;
                var_v0 = var_v1 + arg0;
                if (var_v1 < 8) {
                    goto loop_4;
                }
            }
        } else {
            goto loop_1;
        }
    }
    return var_v0;
}
