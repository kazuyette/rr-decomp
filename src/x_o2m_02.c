/* x_o2m_02.c -- functions verified to reproduce the retail bytes under the
 * "o2" pipeline, filed here by tools/apply_sweep.py.
 *
 * Membership of this file is a measurement, not a judgement: each of
 * these was built under all five known pipelines and matched under this
 * one. The numbered split within a pipeline is mechanical -- two
 * functions that disagree about a shared global's type cannot share a
 * translation unit -- and carries no meaning. Regroup along real module
 * boundaries once the units are identified.
 */
#include "m2c_macros.h"

M2C_UNK func_80051BC4();
M2C_UNK func_80051CCC(M2C_UNK *);
M2C_UNK func_80051CE4(M2C_UNK *);
M2C_UNK func_80051CFC(M2C_UNK *);
extern M2C_UNK func_800535A0;
extern M2C_UNK func_800535C8;
extern M2C_UNK func_800535F0;

void func_800534D8(void) {
    func_80051BC4();
    func_80051CCC(&func_800535A0);
    func_80051CE4(&func_800535C8);
    func_80051CFC(&func_800535F0);
}
