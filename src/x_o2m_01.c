/* x_o2m_01.c -- functions verified to reproduce the retail bytes under the
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

extern s16 D_801D3540;
extern s16 D_801D3546;
extern s16 D_801D354C;
extern s16 D_801D3552;
extern s16 D_801D3558;
extern s16 D_801D355E;
extern s16 D_801D3564;
extern s16 D_801D3570;
extern s16 D_801D3576;
extern s16 D_801D357C;
extern s16 D_801D3582;
M2C_UNK func_8003F0C0(M2C_UNK *);
M2C_UNK func_8003F164(M2C_UNK *, M2C_UNK, M2C_UNK);

void func_8003F26C(void) {
    func_8003F0C0(&D_801D354C);
    func_8003F0C0(&D_801D3570);
    func_8003F0C0(&D_801D355E);
    func_8003F0C0(&D_801D3564);
    func_8003F0C0(&D_801D3576);
    func_8003F0C0(&D_801D357C);
    func_8003F0C0(&D_801D3552);
    func_8003F0C0(&D_801D3558);
    func_8003F0C0(&D_801D3582);
    func_8003F164(&D_801D3540, 0x2E, 1);
    func_8003F164(&D_801D3546, 0x2F, 0);
}
