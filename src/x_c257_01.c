/* x_c257_01.c -- functions verified to reproduce the retail bytes under the
 * "c257" pipeline, filed here by tools/apply_sweep.py.
 *
 * Membership of this file is a measurement, not a judgement: each of
 * these was built under all five known pipelines and matched under this
 * one. The numbered split within a pipeline is mechanical -- two
 * functions that disagree about a shared global's type cannot share a
 * translation unit -- and carries no meaning. Regroup along real module
 * boundaries once the units are identified.
 */
#include "m2c_macros.h"

extern s16 D_8012CF58;
extern s16 D_801D3584;
M2C_UNK func_80013184();

void func_80013200(void) {
    func_80013184();
    D_801D3584 = ((D_8012CF58 < 0x88) - 1) & 0x64;
}
