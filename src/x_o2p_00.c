/* x_o2p_00.c -- functions verified to reproduce the retail bytes under the
 * "o2_plain" pipeline, filed here by tools/apply_sweep.py.
 *
 * Membership of this file is a measurement, not a judgement: each of
 * these was built under all five known pipelines and matched under this
 * one. The numbered split within a pipeline is mechanical -- two
 * functions that disagree about a shared global's type cannot share a
 * translation unit -- and carries no meaning. Regroup along real module
 * boundaries once the units are identified.
 */
#include "m2c_macros.h"

extern u16 *D_8007758C;
M2C_UNK func_800530A8();
s32 func_800531A8();

s16 func_8004C0B8(s16 arg0) {
    return func_80058F64(arg0);
}

s32 func_80051F6C(void) {
    return func_800531A8() == 0;
}

s32 func_800520CC(void) {
    func_800530A8();
    return 1;
}

s32 func_80056AF4(void *arg0) {
    s32 temp_a1;
    s32 temp_a2;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0);
    temp_a2 = temp_a1 == 0;
    if ((temp_a2 != 0) || (temp_a1 & 1)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1C0) = (u16) M2C_FIELD(arg0, u16 *, 4);
    }
    if ((temp_a2 != 0) || (temp_a1 & 2)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1C2) = (u16) M2C_FIELD(arg0, u16 *, 6);
    }
    if ((temp_a2 != 0) || (temp_a1 & 4)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1C4) = (u16) M2C_FIELD(arg0, u16 *, 8);
    }
    if ((temp_a2 != 0) || (temp_a1 & 8)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1C6) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1C8) = (u16) M2C_FIELD(arg0, u16 *, 0xC);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1CA) = (u16) M2C_FIELD(arg0, u16 *, 0xE);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1CC) = (u16) M2C_FIELD(arg0, u16 *, 0x10);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x80)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1CE) = (u16) M2C_FIELD(arg0, u16 *, 0x12);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x100)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1D0) = (u16) M2C_FIELD(arg0, u16 *, 0x14);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x200)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1D2) = (u16) M2C_FIELD(arg0, u16 *, 0x16);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x400)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1D4) = (u16) M2C_FIELD(arg0, u16 *, 0x18);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x800)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1D6) = (u16) M2C_FIELD(arg0, u16 *, 0x1A);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x1000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1D8) = (u16) M2C_FIELD(arg0, u16 *, 0x1C);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x2000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1DA) = (u16) M2C_FIELD(arg0, u16 *, 0x1E);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x4000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1DC) = (u16) M2C_FIELD(arg0, u16 *, 0x20);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x8000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1DE) = (u16) M2C_FIELD(arg0, u16 *, 0x22);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1E0) = (u16) M2C_FIELD(arg0, u16 *, 0x24);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1E2) = (u16) M2C_FIELD(arg0, u16 *, 0x26);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1E4) = (u16) M2C_FIELD(arg0, u16 *, 0x28);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x80000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1E6) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x100000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1E8) = (u16) M2C_FIELD(arg0, u16 *, 0x2C);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x200000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1EA) = (u16) M2C_FIELD(arg0, u16 *, 0x2E);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x400000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1EC) = (u16) M2C_FIELD(arg0, u16 *, 0x30);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x800000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1EE) = (u16) M2C_FIELD(arg0, u16 *, 0x32);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x01000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1F0) = (u16) M2C_FIELD(arg0, u16 *, 0x34);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x02000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1F2) = (u16) M2C_FIELD(arg0, u16 *, 0x36);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x04000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1F4) = (u16) M2C_FIELD(arg0, u16 *, 0x38);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x08000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1F6) = (u16) M2C_FIELD(arg0, u16 *, 0x3A);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1F8) = (u16) M2C_FIELD(arg0, u16 *, 0x3C);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1FA) = (u16) M2C_FIELD(arg0, u16 *, 0x3E);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1FC) = (u16) M2C_FIELD(arg0, u16 *, 0x40);
    }
    if ((temp_a2 != 0) || (temp_a1 < 0)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1FE) = (u16) M2C_FIELD(arg0, u16 *, 0x42);
    }
    return 0;
}

s32 func_80056FC4(void *arg0) {
    M2C_FIELD(arg0, u16 *, 4) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1C0);
    M2C_FIELD(arg0, u16 *, 6) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1C2);
    M2C_FIELD(arg0, u16 *, 8) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1C4);
    M2C_FIELD(arg0, u16 *, 0xA) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1C6);
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1C8);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1CA);
    M2C_FIELD(arg0, u16 *, 0x10) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1CC);
    M2C_FIELD(arg0, u16 *, 0x12) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1CE);
    M2C_FIELD(arg0, u16 *, 0x14) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1D0);
    M2C_FIELD(arg0, u16 *, 0x16) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1D2);
    M2C_FIELD(arg0, u16 *, 0x18) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1D4);
    M2C_FIELD(arg0, u16 *, 0x1A) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1D6);
    M2C_FIELD(arg0, u16 *, 0x1C) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1D8);
    M2C_FIELD(arg0, u16 *, 0x1E) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1DA);
    M2C_FIELD(arg0, u16 *, 0x20) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1DC);
    M2C_FIELD(arg0, u16 *, 0x22) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1DE);
    M2C_FIELD(arg0, u16 *, 0x24) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1E0);
    M2C_FIELD(arg0, u16 *, 0x26) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1E2);
    M2C_FIELD(arg0, u16 *, 0x28) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1E4);
    M2C_FIELD(arg0, u16 *, 0x2A) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1E6);
    M2C_FIELD(arg0, u16 *, 0x2C) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1E8);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1EA);
    M2C_FIELD(arg0, u16 *, 0x30) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1EC);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1EE);
    M2C_FIELD(arg0, u16 *, 0x34) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1F0);
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1F2);
    M2C_FIELD(arg0, u16 *, 0x38) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1F4);
    M2C_FIELD(arg0, u16 *, 0x3A) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1F6);
    M2C_FIELD(arg0, u16 *, 0x3C) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1F8);
    M2C_FIELD(arg0, u16 *, 0x3E) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1FA);
    M2C_FIELD(arg0, u16 *, 0x40) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1FC);
    M2C_FIELD(arg0, u16 *, 0x42) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1FE);
    return 0;
}

s32 func_800574F0(void *arg0) {
    M2C_FIELD(arg0, u16 *, 4) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x180);
    M2C_FIELD(arg0, u16 *, 6) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x182);
    M2C_FIELD(arg0, u16 *, 8) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x184);
    M2C_FIELD(arg0, u16 *, 0xA) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x186);
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1B0);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1B2);
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (((u16) M2C_FIELD(D_8007758C, u16 *, 0x1AA) >> 2) & 1);
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 1);
    M2C_FIELD(arg0, u16 *, 0x18) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1B4);
    M2C_FIELD(arg0, u16 *, 0x1A) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1B6);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (((u16) M2C_FIELD(D_8007758C, u16 *, 0x1AA) >> 3) & 1);
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (((u16) M2C_FIELD(D_8007758C, u16 *, 0x1AA) >> 1) & 1);
    M2C_FIELD(arg0, s16 *, 0x24) = (s16) ((u32) (M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 0x3F00) >> 8);
    M2C_FIELD(arg0, s16 *, 0x26) = (s16) (((u16) M2C_FIELD(D_8007758C, u16 *, 0x1AA) >> 7) & 1);
    M2C_FIELD(arg0, s16 *, 0x28) = (s16) ((u32) (M2C_FIELD(D_8007758C, u16 *, 0x1AC) & 0xE) >> 1);
    M2C_FIELD(arg0, s16 *, 0x2A) = (s16) (M2C_FIELD(D_8007758C, u16 *, 0x1AC) & 1);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(D_8007758C, u16 *, 0x19C) | (M2C_FIELD(D_8007758C, u16 *, 0x19E) << 0x10));
    M2C_FIELD(arg0, u16 *, 0x30) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1AE);
    return 0;
}
