/* x_o1d_00.c -- functions verified to reproduce the retail bytes under the
 * "o1ndb" pipeline, filed here by tools/apply_sweep.py.
 *
 * Membership of this file is a measurement, not a judgement: each of
 * these was built under all five known pipelines and matched under this
 * one. The numbered split within a pipeline is mechanical -- two
 * functions that disagree about a shared global's type cannot share a
 * translation unit -- and carries no meaning. Regroup along real module
 * boundaries once the units are identified.
 */
#include "m2c_macros.h"

extern s32 *D_80077394;
extern s32 **D_80077398;
extern s32 *D_8007739C;
extern s32 *D_800773A0;
extern s32 *D_800773B0;

void func_800470D0(s32 arg0) {
    *D_80077394 = 0x04000002;
    *D_800773B0 |= 0x800;
    *D_80077398 = arg0;
    *D_8007739C = 0;
    *D_800773A0 = 0x01000401;
}
