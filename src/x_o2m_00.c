/* x_o2m_00.c -- functions verified to reproduce the retail bytes under the
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

extern M2C_UNK D_800730E4;
extern M2C_UNK D_80073104;
extern s32 D_80077144;
extern M2C_UNK D_800773BC;
extern s32 D_8007743C;
extern s32 D_800774D4;
extern s32 D_80077600;
extern s32 D_80077720;
extern M2C_UNK D_80078748;
extern s16 D_8007C210;
extern s32 D_8007C240;
extern s32 D_8007C4D0;
extern s32 D_8007C518;
extern s32 D_8012CF50;
extern s16 D_8012CFB8;
extern s16 D_8012CFD8;
extern s32 D_8012D020;
extern s32 D_8012D080;
extern M2C_UNK D_8012D090;
extern s32 D_8012D0C0;
extern s16 D_8012D8D0;
extern s16 D_8012D908;
extern M2C_UNK D_8012E4C0;
extern M2C_UNK D_801510B4;
extern s16 D_80173150;
extern s16 D_80173164;
extern u16 D_80173310;
extern s32 D_80173370;
extern s32 D_80173468;
extern s16 D_801D34F8;
extern s16 D_801D3540;
extern s16 D_801D3544;
extern s16 D_801D3546;
extern s16 D_801D354A;
extern s16 D_801D354C;
extern s16 D_801D3550;
extern s16 D_801D3552;
extern s16 D_801D3556;
extern s16 D_801D3558;
extern s16 D_801D355C;
extern s16 D_801D355E;
extern s16 D_801D3562;
extern s16 D_801D3564;
extern s16 D_801D356A;
extern s16 D_801D356E;
extern s16 D_801D3570;
extern s16 D_801D3574;
extern s16 D_801D3576;
extern s16 D_801D357A;
extern s16 D_801D357C;
extern s16 D_801D3580;
extern s16 D_801D3582;
extern s16 D_801D3586;
extern s32 D_801D77A8;
extern s32 D_801D77F0;
extern s32 D_801D7E20;
extern s32 D_801E90B0;
extern s32 D_801E90C8;
extern s16 D_801E91A0;
extern s32 D_801E9218;
extern M2C_UNK D_801E9250;
extern M2C_UNK (*D_80077370)(M2C_UNK *, s32, s32, s32);
M2C_UNK func_80013338(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8001CE0C();
M2C_UNK func_8002128C(M2C_UNK *, M2C_UNK);
M2C_UNK func_80025D9C(s32);
M2C_UNK func_800266B8(M2C_UNK);
M2C_UNK func_8002E6A8(s16, s16);
M2C_UNK func_80030DBC();
M2C_UNK func_80031BD8();
M2C_UNK func_8003A1AC(M2C_UNK);
M2C_UNK func_8003A1BC();
M2C_UNK func_8003A1D8();
M2C_UNK func_8003AEC0();
M2C_UNK func_8003FBE8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8003FC08(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_800434A0(M2C_UNK *);
M2C_UNK func_800434D0(M2C_UNK *);
M2C_UNK func_80044F64(M2C_UNK, M2C_UNK);
M2C_UNK func_80045750(M2C_UNK);
M2C_UNK func_80048198(M2C_UNK *, M2C_UNK *, s32);
M2C_UNK func_80048FC0();
M2C_UNK func_800491AC(M2C_UNK, s32);
M2C_UNK func_8004922C(M2C_UNK, s32);
M2C_UNK func_800492B0();
M2C_UNK func_80049580();
M2C_UNK func_80049638();
M2C_UNK GPU_cw(s32);
M2C_UNK func_800497D8();
M2C_UNK func_8004A9D4(s32, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_8004B310();
M2C_UNK CloseEvent(s32);
M2C_UNK DisableEvent(s32);
M2C_UNK func_80052504(M2C_UNK);
M2C_UNK func_80052854();
M2C_UNK func_80052974();
M2C_UNK func_80052A98();
M2C_UNK func_80052BF0();
M2C_UNK func_80058E58();
M2C_UNK func_80058EB8(M2C_UNK);
extern void *g_gpu_device;
M2C_UNK st_title_init();

void func_80012550(void) {
    func_8003A1BC();
    func_8003A1AC(0);
}

void func_8001315C(void) {
    func_800434D0(&D_8012D090);
}

void func_8001CDBC(s32 arg0) {
    if (D_801E90B0 > 0) {
        D_8007C518 = arg0;
        return;
    }
    func_8003A1D8();
    D_801E90B0 = 0x78;
    D_8007C518 = 0;
}

void func_8001CEA0(void) {
    func_8001CDBC(9);
    D_801E90C8 = 0;
}

void func_8001CEC8(void) {
    s32 temp_v0;

    func_8001CE0C();
    if (D_801E90B0 == -1) {
        temp_v0 = D_801E90C8 + 1;
        D_801E90C8 = temp_v0;
        if (temp_v0 >= 0x1C21) {
            func_8001CEA0();
        }
    }
}

void func_8001CFD0(void) {
    st_title_init();
    D_80077144 = 0;
}

void func_8001F098(void) {
    func_800434D0(&D_800730E4);
    func_800434A0(&D_80073104);
    func_8003FBE8(0x20, 0x20, 0x20);
    func_8003FC08(0, 0, 0);
    func_80044F64(0x4E20, 0x140);
}

void func_80025C70(void) {
    func_8002128C(&D_801E9250, 1);
}

void func_80026794(void) {
    D_801D77A8 = 0;
    func_800266B8(0);
    func_800266B8(1);
    func_800264C4(&D_8012E4C0);
    func_800264C4(&D_801510B4);
}

void func_8002B66C(void) {
    D_80173164 = 0;
    D_80173150 = 0;
    func_80025D9C(D_8007C210 - 1);
    D_80173310 = 0;
    D_801E91A0 = 0;
    D_80173468 = D_8012CF50;
    if ((D_8012CF50 != 0) && (D_801D77F0 >= 0x50B)) {
        D_801E9218 = D_801D77F0;
        D_801D77F0 = 0x50A;
    }
}

void func_8002E710(void) {
    func_8002E6A8(D_8012D908, D_8012D8D0);
}

void func_80030DE0(void) {
    D_8012D020 = 0;
    D_8012CFB8 = 0;
    func_80030DBC();
}

void func_80030EF4(void) {
    func_80030DBC();
}

void func_800320E0(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    D_80173310 = 0;
    D_8007C4D0 = 0;
    D_8007C240 = 0;
    func_80031BD8();
    D_801D34F8 = 0x1F;
    D_80173370 = D_8012CFD8 + 1;
}

void func_8003247C(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    D_80173310 = 0;
    D_8007C4D0 = 0;
    D_8012D080 = 0;
    D_8007C240 = 0;
    func_80031BD8();
    D_801D34F8 = 0x21;
    D_80173370 = D_8012CFD8 + 2;
}

void func_8003EE20(void) {
    func_8003AEC0();
    D_801D3540 = -1;
    D_801D3546 = -1;
    D_801D354C = -1;
    D_801D3552 = -1;
    D_801D3558 = -1;
    D_801D355E = -1;
    D_801D3564 = -1;
    D_801D356A = -1;
    D_801D3570 = -1;
    D_801D3576 = -1;
    D_801D357C = -1;
    D_801D3582 = -1;
    D_801D3544 = 0x1E00;
    D_801D354A = 0x1E00;
    D_801D3550 = 0x1E00;
    D_801D3556 = 0x1E00;
    D_801D355C = 0x1E00;
    D_801D3562 = 0x1E00;
    D_801D356E = 0x1E00;
    D_801D3574 = 0x1E00;
    D_801D357A = 0x1E00;
    D_801D3580 = 0x1E00;
    D_801D3586 = 0x1E00;
}

void func_80045418(s32 arg0) {
    GPU_cw(arg0 & 0xFFFFFF);
}

void func_80045790(void) {
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(), 0x3C)();
}

s32 func_80045B40(s32 arg0) {
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(), 0x2C)();
    return arg0;
}

M2C_UNK *func_8004815C(s32 arg0) {
    func_80048198(&D_80078748, &D_800773BC, arg0);
    return &D_80078748;
}

void func_80048F80(void) {
    if (D_8007743C == 0) {
        D_8007743C = 1;
        func_80048FC0();
        func_800492B0();
    }
}

void func_8004901C(void) {
    D_8007743C = 0;
    func_80049580();
}

void func_80049044(s32 arg0) {
    func_800491AC(0, arg0);
}

void func_80049068(s32 arg0) {
    func_800491AC(1, arg0);
}

void func_8004908C(s32 arg0) {
    func_800491AC(2, arg0);
}

void func_800490B0(s32 arg0) {
    func_800491AC(3, arg0);
}

void func_800490D4(s32 arg0) {
    func_800491AC(4, arg0);
}

void func_800490F8(s32 arg0) {
    func_800491AC(5, arg0);
}

void func_8004911C(s32 arg0) {
    func_8004922C(0, arg0);
}

void func_80049140(s32 arg0) {
    func_8004922C(2, arg0);
}

void func_80049164(s32 arg0) {
    func_8004922C(9, arg0);
}

void func_80049188(s32 arg0) {
    func_8004922C(0xA, arg0);
}

void func_8004A9A8(s32 arg0, s32 arg1) {
    func_8004A9D4(arg0 & 0xFFFF, arg1 & 0xFFFF, 0x80FF, 0x5FC8);
}

void func_8004D3C0(void) {
    func_80058EB8(1);
}

void func_8004D3E0(void) {
    func_80058EB8(0);
}

void func_8004D754(void) {
    func_8004B310();
}

void func_8004DEAC(void) {
    if ((D_8012D0C0 == 0) || (D_801D7E20 != 0)) {
        func_80049638();
        DisableEvent(D_80077600);
        CloseEvent(D_80077600);
        func_800497D8();
    }
    func_80058E58();
}

void func_80051BC4(void) {
    func_80052854();
}

void func_80051C6C(void) {
    func_80052974();
}

void func_80051C8C(void) {
    func_80052A98();
}

void func_80051CAC(void) {
    func_80052BF0();
}

void func_800524D8(void) {
    if (D_800774D4 != 0) {
        func_80052504(0);
    }
}

void func_8005462C(void) {
    func_80049638();
    func_80049140(0);
    func_800490B0(0);
    func_800497D8();
}

void func_80058BB8(s32 arg0) {
    func_80058B48(arg0 << D_80077720);
}
