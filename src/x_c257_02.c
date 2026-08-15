/* x_c257_02.c -- functions verified to reproduce the retail bytes under the
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

extern M2C_UNK D_80010FD0;

/* Did not match; reverted to INCLUDE_ASM.
 * Kept here as a starting point for the next attempt.
 * void func_800479C8(s32 arg0) {
 *     D_80077370(&D_80010FD0, (arg0 & 0x3F) * 0x10, (u32) (arg0 & 0xFFFF) >> 6);
 * }
 */
