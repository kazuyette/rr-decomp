/* x_o2m_06.c -- functions verified to reproduce the retail bytes under the
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

M2C_UNK func_80051EF0(M2C_UNK, M2C_UNK, u8 *);

void func_800536D8(void) {
    func_80051EF0(8, 0, 0);
}
