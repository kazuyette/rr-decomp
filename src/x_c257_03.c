/* x_c257_03.c -- functions verified to reproduce the retail bytes under the
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

extern M2C_UNK D_80011180;
s32 func_800489EC(u8);
s32 func_80048A80(u8);

/* Did not match; reverted to INCLUDE_ASM.
 * Kept here as a starting point for the next attempt.
 * s32 func_80048CCC(s32 arg0, void *arg1) {
 *     s32 temp_v1;
 * 
 *     temp_v1 = func_80048A80(M2C_FIELD(arg1, u8 *, 7)) & 0xFF;
 *     if (temp_v1 != 0) {
 *         if (temp_v1 != M2C_FIELD(arg1, u8 *, 3)) {
 *             D_80077370(&D_80011180, arg0, arg1, func_800489EC(M2C_FIELD(arg1, u8 *, 7)), (s32) M2C_FIELD(arg1, u8 *, 3));
 *             return -1;
 *         }
 *         
 *         return 0;
 *     }
 *     return 0;
 * }
 */
