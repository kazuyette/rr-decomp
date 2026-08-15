/* x_o1m_00.c -- functions verified to reproduce the retail bytes under the
 * "o1" pipeline, filed here by tools/apply_sweep.py.
 *
 * Membership of this file is a measurement, not a judgement: each of
 * these was built under all five known pipelines and matched under this
 * one. The numbered split within a pipeline is mechanical -- two
 * functions that disagree about a shared global's type cannot share a
 * translation unit -- and carries no meaning. Regroup along real module
 * boundaries once the units are identified.
 */
#include "m2c_macros.h"

extern M2C_UNK D_80010800;
extern M2C_UNK D_80010948;
extern M2C_UNK D_8005F140;
extern M2C_UNK D_8005F2A0;
extern M2C_UNK D_80070F44;
extern M2C_UNK D_80070FEC;
extern M2C_UNK D_80071094;
extern M2C_UNK D_8007113C;
extern M2C_UNK D_800711E4;
extern M2C_UNK D_80071784;
extern M2C_UNK D_80077128;
extern s32 D_800774D4;
extern s32 D_80077688;
extern s32 D_80077690;
extern s32 D_80077698;
extern s32 D_800776A0;
extern s32 D_8007C4F0;
extern s32 D_8012CD30;
extern s32 D_8012CDA0;
extern s16 D_8012CDB8;
extern s32 D_8012CDE0;
extern s32 D_8012CFE8;
extern s32 D_8012D070;
extern s32 D_8012D8D8;
extern s32 D_8012D8E0;
extern s32 D_8012D8E8;
extern s32 D_8012D940;
extern s32 D_8012D944;
extern s32 D_8012D948;
extern s32 D_8012D94C;
extern s16 D_80173164;
extern M2C_UNK *D_80173180;
extern u16 D_80173310;
extern s32 D_80173368;
extern s32 D_80173378;
extern s32 D_80173420;
extern u8 D_80173428;
extern s32 D_80173480;
extern s32 D_80173488;
extern s32 D_80173490;
extern s32 D_801734A0;
extern s32 D_801734B8;
extern s32 D_801734C0;
extern s16 D_801D34F8;
extern u16 D_801D35AE;
extern s8 D_801D35C0;
extern s8 D_801D35C1;
extern s8 D_801D35C2;
extern s8 D_801D35C3;
extern s32 D_801D7E28;
extern s32 D_801D9030;
extern s32 D_801D9040;
extern s32 D_801E9098;
extern s32 D_801E90E0;
extern s32 D_801E9178;
extern s16 D_801E91A0;
extern s32 D_801E9210;
extern s32 D_801E9248;
extern s32 D_801E9F40;
extern M2C_UNK (*D_80077370)(M2C_UNK *, s32, s32, s32);
M2C_UNK func_80013338(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8001602C(M2C_UNK *);
M2C_UNK func_8001613C(M2C_UNK *);
M2C_UNK func_8001624C(M2C_UNK *);
M2C_UNK func_80026794();
M2C_UNK func_80028578(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK func_80028A0C(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
M2C_UNK func_8002D134();
M2C_UNK func_800366FC(M2C_UNK *);
s32 func_800373BC(s32, s32);
M2C_UNK func_800376EC(s32);
M2C_UNK func_800439D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32);
M2C_UNK func_80045750(M2C_UNK);
M2C_UNK func_8004617C(s32, M2C_UNK, M2C_UNK, s32, M2C_UNK *);
s32 func_800465A0(u16, u16);
s32 func_800465DC(M2C_UNK);
s32 func_8004788C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8004DFC4(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_80051B24(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_80051E30(M2C_UNK, void *, M2C_UNK);
M2C_UNK func_80051EF0(M2C_UNK, M2C_UNK, u8 *);
M2C_UNK func_80052504(M2C_UNK);
M2C_UNK func_8005486C(M2C_UNK);

void D_80052820(void) {
    D_800774D4 = 1;
    func_80052504(1);
    D_800774D4 = 0;
}

void func_80012578(void) {
    func_800439D8(0x1F8000B0, 0x160, 0x110, 0x140, 0, 0x10000);
}

void func_80013240(void) {
    func_8001602C(&D_80070F44);
    func_8001613C(&D_80070FEC);
    if (D_80173164 != 0) {
        func_8001624C(&D_80071784);
        func_8001602C(&D_8007113C);
        return;
    }
    func_800366FC(&D_800711E4);
    func_8001613C(&D_80071094);
}

void func_800135B8(s32 arg0, s32 arg1) {
    s32 var_v0;
    s32 var_v0_2;

    if (arg0 != 0) {
        D_801734B8 = 0xA700;
        D_80173480 = 0xD00;
        if (arg1 != 0) {
            D_8012CDA0 = 0xB900;
            var_v0 = 0x6400;
        } else {
            D_8012CDA0 = 0x2700;
            var_v0 = 0x6800;
        }
        D_80173488 = var_v0;
        D_80173180 = &D_8005F140;
        D_801E90E0 = 0x100;
        D_801E9210 = 1;
        D_80173368 = 0xC570;
        D_801E9248 = 0xBBE0;
        D_80173378 = 0x9E00;
        D_801E9F40 = 0x9490;
        D_8012D8E0 = 0x1AB3;
        D_801D9030 = 0;
        D_8012D8E8 = 0x6F50;
        D_801D9040 = 0x6200;
        D_8012D8D8 = 0xAC00;
        D_8007C4F0 = -1;
        D_8012D940 = 0xED00;
        D_8012D944 = 0x9100;
        D_8012D948 = -1;
        D_8012D94C = -1;
    } else {
        D_801734B8 = 0x11600;
        D_801734C0 = 0x9F00;
        D_80173480 = 0xD00;
        if (arg1 != 0) {
            D_8012CDA0 = 0x12900;
            var_v0_2 = 0xD400;
        } else {
            D_8012CDA0 = 0x2700;
            var_v0_2 = 0xD800;
        }
        D_80173488 = var_v0_2;
        D_80173180 = &D_8005F2A0;
        D_801E90E0 = 0x170;
        D_801E9210 = 2;
        D_80173368 = 0x13570;
        D_801E9248 = 0x12BE0;
        D_80173378 = 0x10E00;
        D_801E9F40 = 0x10490;
        D_8012D8E0 = 0x1AB3;
        D_801D9030 = 0;
        D_8012D8E8 = 0xDE90;
        D_801D9040 = 0xD1D0;
        D_8012D8D8 = 0x11C00;
        D_8007C4F0 = 0x6300;
        D_8012D940 = 0x15D00;
        D_8012D944 = 0x10100;
        D_8012D948 = 0xAE00;
        D_8012D94C = 0x8000;
    }
    D_80173490 = func_800373BC(D_80173480, D_80173488);
}

void func_800205E4(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s16 *, 0x38) = 0;
    if ((u32) (arg2 - 4) < 4U) {
        M2C_FIELD(arg0, s16 *, 0x38) = 1;
    }
    M2C_FIELD(arg0, s16 *, 0x3A) = 0x14;
    M2C_FIELD(arg0, s16 *, 0x3C) = 0;
    M2C_FIELD(arg0, s16 *, 0x3E) = -1;
    M2C_FIELD(arg0, s16 *, 0x40) = -1;
    M2C_FIELD(arg0, s16 *, 0x46) = 0;
    M2C_FIELD(arg0, s16 *, 0x4C) = -0x3C;
    M2C_FIELD(arg0, s16 *, 0x4E) = 0;
    M2C_FIELD(arg0, s16 *, 0x50) = 0;
    M2C_FIELD(arg0, s16 *, 0x42) = -3;
    M2C_FIELD(arg0, s16 *, 0x54) = 0;
    M2C_FIELD(arg0, s16 *, 0x56) = 0;
    M2C_FIELD(arg0, s32 *, 0x58) = 0;
    if (arg1 < 5) {
        M2C_FIELD(arg0, s16 *, 0x44) = 0;
        M2C_FIELD(arg0, s16 *, 0x4A) = -1;
    } else {
        M2C_FIELD(arg0, s16 *, 0x44) = 1;
        M2C_FIELD(arg0, s16 *, 0x4A) = 0;
    }
    if (arg1 == 0xB) {
        M2C_FIELD(arg0, s16 *, 0x56) = 1;
        M2C_FIELD(arg0, s16 *, 0x4A) = -2;
        M2C_FIELD(arg0, s16 *, 0x4E) = -1;
        M2C_FIELD(arg0, s16 *, 0x3C) = -1;
    }
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    M2C_FIELD(arg0, s32 *, 0x64) = 0;
    M2C_FIELD(arg0, s16 *, 0x8E) = 0;
    M2C_FIELD(arg0, s16 *, 0x8C) = 0;
    M2C_FIELD(arg0, s32 *, 0x98) = 0;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    M2C_FIELD(arg0, s16 *, 0x8E) = 0;
    M2C_FIELD(arg0, s32 *, 0x74) = 0;
    M2C_FIELD(arg0, s32 *, 0x70) = 0;
    M2C_FIELD(arg0, s32 *, 0x7C) = 0;
    M2C_FIELD(arg0, s32 *, 0x78) = 0;
    M2C_FIELD(arg0, s32 *, 0x80) = 0;
    M2C_FIELD(arg0, s32 *, 0x84) = 0;
    M2C_FIELD(arg0, s32 *, 0x88) = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
}

void func_80028AC8(s32 arg0) {
    func_8004617C(arg0, 0, 1, func_8004788C(0, 0, 0x140, 0) & 0xFFFF, &D_80077128);
    func_80028A0C(arg0 + 0x20, 0xE8, 0x98, 0x50, 0x50, 0x48, 0x48, 0x64);
    func_80028A0C(arg0 + 0x34, 0x58, 8, 0x30, 8, 0, 0x10, 0x7E);
    func_80028A0C(arg0 + 0x48, 0x98, 8, 0x30, 8, 0x30, 0x10, 0x7E);
    func_80028A0C(arg0 + 0x5C, 0xC2, 0x18, 0x10, 0x10, 0xA0, 0xB0, 0x80);
    func_80028A0C(arg0 + 0x70, 0x120, 0xD8, 0x20, 8, 0x10, 0x60, 0x64);
}

void func_8002E3AC(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    func_8002D134();
    D_80173310 = 0;
    D_801D34F8 = 0xB;
}

void func_80039D00(void) {
    s8 sp10;

    func_80051B24(0, 0, 1);
    func_8004DFC4(0, 0x7FFF, 0x7FFF);
    sp10 = 7;
    func_80051E30(0xE, &sp10, 0);
    D_80173428 = 1;
    D_801E9098 = 0;
    D_801D35C0 = 0x7F;
    D_801D35C1 = 0;
    D_801D35C2 = 0x7F;
    D_801D35C3 = 0;
}

void func_8003B4C4(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    D_80173310 = 0;
    D_801D34F8 = 0x10;
    D_801E91A0 = 0;
    D_8012CD30 = 0x64;
}

void func_8003D518(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    D_80173310 = 0;
    D_8012D070 = 0;
    D_801E9178 = 0;
    D_80173420 = 1;
    D_801D7E28 = 0;
    D_801D34F8 = 0x14;
}

void func_8003DC28(void) {
    func_80028578(0x20, 0xC8, &D_80010800, 0x7F);
    if (D_801D35AE & 0x800) {
        D_801E9178 = 0;
    }
    func_80028578(0x78, 0x20, &D_80010948, 0x64);
}

void func_8003EAAC(void) {
    func_80045750(0);
    D_8012CDB8 = 0x80;
    func_80013338(8, 0x20, 0x40);
    func_800376EC(-1);
    D_80173310 = 0;
    func_80026794();
    D_801D34F8 = 0x1C;
}

void func_8003EC5C(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    D_80173310 = 0;
    D_801D34F8 = 0x18;
}

void func_800460DC(void *arg0, M2C_UNK arg1) {
    M2C_FIELD(arg0, s8 *, 3) = 2;
    M2C_FIELD(arg0, s32 *, 4) = func_800465DC(arg1);
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

void func_80046114(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s8 *, 3) = 2;
    M2C_FIELD(arg0, s32 *, 4) = func_800465A0(M2C_FIELD(arg1, u16 *, 0), M2C_FIELD(arg1, u16 *, 2));
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

void func_800521A0(s8 arg0) {
    s8 sp10;

    sp10 = arg0;
    func_80051E30(0xE, &sp10, 0);
}

u8 func_800540C0(void) {
    u8 sp10;

    func_80051EF0(1, 0, &sp10);
    return sp10;
}

void func_80054584(s32 arg0, s32 arg1) {
    D_801734A0 = arg0;
    D_80077688 = arg1;
    D_800776A0 = 0;
    D_80077698 = 0;
    D_80077690 = 0;
    D_8012CDE0 = 0;
    func_8005486C(0);
    D_8012CFE8 = 0;
}
