#include "m2c_macros.h"

M2C_UNK func_800490B0(M2C_UNK *);
M2C_UNK func_80051CE4(M2C_UNK *);
M2C_UNK func_80051E30(M2C_UNK, s8 *, M2C_UNK);
extern M2C_UNK D_8005497C;
extern M2C_UNK func_80054664;

void func_800521CC(s8 arg0) {
    s8 sp10;
    M2C_UNK var_a0;

    sp10 = arg0;
    func_80051E30(0xE, &sp10, 0);
    var_a0 = 6;
    if (arg0 & 0x100) {
        func_800490B0(&func_80054664);
        func_80051CE4(&D_8005497C);
        var_a0 = 0x1B;
    }
    func_80051E30(var_a0, NULL, 0);
}
