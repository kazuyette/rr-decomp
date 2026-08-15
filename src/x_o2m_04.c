/* x_o2m_04.c -- functions verified to reproduce the retail bytes under the
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

extern M2C_UNK *D_A00003E0;
extern M2C_UNK *D_A00003F0;
extern M2C_UNK *D_A00003F8;
extern M2C_UNK *D_A0000414;
extern void *D_A0000454;
extern void *D_A0000488;
extern void *D_A000048C;
M2C_UNK _96_remove();
extern M2C_UNK DeliverEvent;
extern M2C_UNK func_800536B0;
extern M2C_UNK func_800536D8;
extern M2C_UNK func_80053700;
extern M2C_UNK func_8005373C;

void func_80053630(void) {
    void *temp_v0;

    _96_remove();
    D_A00003E0 = &func_800536B0;
    D_A00003F0 = &func_80053700;
    D_A00003F8 = &func_8005373C;
    D_A0000414 = &func_800536D8;
    temp_v0 = &DeliverEvent + 0x10;
    D_A0000454 = temp_v0;
    D_A0000488 = temp_v0;
    D_A000048C = temp_v0;
}
