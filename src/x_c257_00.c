/* x_c257_00.c -- functions verified to reproduce the retail bytes under the
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

M2C_UNK AddPrim(s32, s32);
extern M2C_UNK D_800105D4;
extern M2C_UNK D_80010EF4;
extern M2C_UNK D_80010F2C;
extern M2C_UNK D_80010F38;
extern M2C_UNK D_80010F70;
extern M2C_UNK D_800771B0;
extern s32 D_800771C8;
extern s32 D_80077374;
extern s32 D_80077378;
extern s32 D_8007737C;
extern s32 D_80077454;
extern s32 D_800775B8;
extern u8 D_800775E8;
extern u8 D_80079B98;
extern s16 D_80079BA0;
extern s32 D_8007B1B8;
extern s32 D_8007B1BC;
extern s32 D_8007B1C0;
extern s32 D_8007B1C4;
extern s32 D_8007C4E0;
extern s32 D_8007C518;
extern s32 D_8012CD30;
extern s32 D_8012CDA8;
extern s16 D_8012CDB8;
extern u16 D_8012CDC0;
extern s32 D_8012CDC8;
extern s32 D_8012CDD0;
extern u16 D_8012CDD8;
extern s32 D_8012CF68;
extern s32 D_8012D010;
extern s16 D_8012D8D0;
extern s16 D_8012D908;
extern u16 D_80173310;
extern s32 D_801734B0;
extern s16 D_801D34F8;
extern u16 D_801D77D0;
extern s32 D_801D9050;
extern u16 D_801D9068;
extern u16 D_801D906C;
extern u16 D_801D9070;
extern s32 D_801E90B0;
extern s32 D_801E90C8;
extern s32 D_801E9168;
extern s16 D_801E91A0;
extern s32 D_801E91D8;
extern s32 D_801E91E0;
extern M2C_UNK D_801E91F0;
extern s32 D_801E9228;
extern M2C_UNK (*D_80077370)(M2C_UNK *, s32, s32, s32);
s32 VSync(M2C_UNK);
s32 func_80012EF0(s32);
M2C_UNK func_80013338(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8001CDBC(M2C_UNK);
M2C_UNK func_80026794();
M2C_UNK func_80028578(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK);
s32 func_800297D8(s32, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32);
M2C_UNK func_8002E490();
M2C_UNK func_8002E528();
M2C_UNK func_8002EBF0();
M2C_UNK func_80031238(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32);
M2C_UNK func_800314BC(M2C_UNK);
M2C_UNK func_800355A4(M2C_UNK);
M2C_UNK func_800376EC(s32);
M2C_UNK func_8003A1AC(M2C_UNK);
M2C_UNK func_8003A640(s32);
M2C_UNK func_8003B2E4(M2C_UNK, M2C_UNK);
M2C_UNK func_8003B340(M2C_UNK);
M2C_UNK func_8003B388(u16);
M2C_UNK func_8003EAAC();
M2C_UNK func_8004315C(M2C_UNK *, void *, void *);
M2C_UNK func_80043470(M2C_UNK, s32);
M2C_UNK func_80043500(void *);
M2C_UNK func_80045750(M2C_UNK);
s32 func_800459C0(M2C_UNK *, s32);
s32 func_80046430(M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_800465DC(M2C_UNK);
s32 func_8004788C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_80048ADC(s32);
M2C_UNK func_80048CCC(M2C_UNK *, void *);
M2C_UNK func_80049638();
M2C_UNK func_80049648(s32);
s32 func_80049668(s32, M2C_UNK, s32);
M2C_UNK func_800497D8();
s32 func_800497E8(s32, M2C_UNK);
s32 func_80049AF4(M2C_UNK);
M2C_UNK func_8004A808(s16, s32, s32, s32, s32);
M2C_UNK func_8004B1BC(M2C_UNK, s16, s16, s32);
M2C_UNK func_8004D400(s16);
M2C_UNK func_8004DF1C(s32);
M2C_UNK func_8004DF3C(s32);
M2C_UNK func_8004E91C(s16, s16);
s32 func_80051CAC(M2C_UNK, M2C_UNK);
M2C_UNK func_80051E30(M2C_UNK, void *, M2C_UNK);
M2C_UNK func_80051F8C(u32, M2C_UNK, M2C_UNK);
s32 func_80059050(s32);
extern void *g_gpu_device;
s32 rcos(s32);
s32 rsin(s32);

void DrawOTag(s32 arg0) {
    if (D_80077374 != 0) {
        func_80048ADC(arg0);
        return;
    }
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(s32, s32, M2C_UNK), 4)(M2C_FIELD(g_gpu_device, s32 *, 0x18), arg0, 0);
}

void func_800129AC(void *arg0, void *arg1, M2C_UNK arg2) {
    s32 temp_a1;

    M2C_FIELD(arg0, s16 *, 0) = (s16) (M2C_FIELD(arg1, u16 *, 0) - D_801D9068);
    M2C_FIELD(arg0, s16 *, 2) = (s16) (M2C_FIELD(arg1, u16 *, 4) - D_801D906C);
    M2C_FIELD(arg0, s16 *, 4) = (s16) (M2C_FIELD(arg1, u16 *, 8) - D_801D9070);
    func_8004315C(&D_801E91F0, arg0, arg0 + 8);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 8) * 4);
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) * 4);
    temp_a1 = M2C_FIELD(arg0, s32 *, 0x10) * 4;
    M2C_FIELD(arg0, s32 *, 0x34) = temp_a1;
    func_80043470(arg2, temp_a1);
    func_80043500(arg0 + 0x18);
}

void func_80013184(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_80012EF0(M2C_FIELD(arg0, s32 *, 8));
    if (temp_v0 != 0) {
        if (D_8012CDC8 == 0) {
            func_8003B2E4(0x46, 0x46);
        }
    } else if (D_8012CDC8 != 0) {
        func_8003B2E4(0, 0);
    }
    D_8012CDC8 = temp_v0;
}

void func_80018584(void *arg0, M2C_UNK arg1) {
    s16 temp_s1;
    s16 temp_v0;

    temp_s1 = rsin(arg1);
    temp_v0 = rcos(arg1);
    M2C_FIELD(arg0, s16 *, 0) = temp_v0;
    M2C_FIELD(arg0, s16 *, 2) = (s16) -temp_s1;
    M2C_FIELD(arg0, s16 *, 4) = 0;
    M2C_FIELD(arg0, s16 *, 6) = temp_s1;
    M2C_FIELD(arg0, s16 *, 8) = temp_v0;
    M2C_FIELD(arg0, s16 *, 0xA) = 0;
    M2C_FIELD(arg0, s16 *, 0xC) = 0;
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
    M2C_FIELD(arg0, s16 *, 0x10) = 0x1000;
}

void func_800185F0(void *arg0, M2C_UNK arg1) {
    s16 temp_s1;
    s16 temp_v0;

    temp_s1 = rsin(arg1);
    temp_v0 = rcos(arg1);
    M2C_FIELD(arg0, s16 *, 0) = temp_v0;
    M2C_FIELD(arg0, s16 *, 2) = 0;
    M2C_FIELD(arg0, s16 *, 4) = (s16) -temp_s1;
    M2C_FIELD(arg0, s16 *, 6) = 0;
    M2C_FIELD(arg0, s16 *, 8) = 0x1000;
    M2C_FIELD(arg0, s16 *, 0xA) = 0;
    M2C_FIELD(arg0, s16 *, 0xC) = temp_s1;
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
    M2C_FIELD(arg0, s16 *, 0x10) = temp_v0;
}

void func_8001865C(void *arg0, M2C_UNK arg1) {
    s16 temp_s1;
    s16 temp_v0;

    temp_s1 = rsin(arg1);
    temp_v0 = rcos(arg1);
    M2C_FIELD(arg0, s16 *, 0) = 0x1000;
    M2C_FIELD(arg0, s16 *, 2) = 0;
    M2C_FIELD(arg0, s16 *, 4) = 0;
    M2C_FIELD(arg0, s16 *, 6) = 0;
    M2C_FIELD(arg0, s16 *, 8) = temp_v0;
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) -temp_s1;
    M2C_FIELD(arg0, s16 *, 0xC) = 0;
    M2C_FIELD(arg0, s16 *, 0xE) = temp_s1;
    M2C_FIELD(arg0, s16 *, 0x10) = temp_v0;
}

void func_8001CE0C(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0;

    var_a0 = arg0;
    temp_v1 = var_a0;
    if (D_801E90B0 > 0) {
        temp_v0 = D_801E90B0 - 1;
        D_801E90B0 = temp_v0;
        if (temp_v0 == 0) {
            var_a0 = D_8007C518;
            if (var_a0 > 0) {
                func_8001CDBC(var_a0);
                return;
            }
            goto block_5;
        }
    } else if (D_801E90B0 == 0) {
block_5:
        if (temp_v1 != 0) {
            func_8003A640(var_a0);
            func_8003A1AC(0x7F);
            D_801E90C8 = 0;
            D_801E90B0 = -1;
        }
    }
}

void func_80028C1C(void) {
    s32 temp_s0;

    temp_s0 = D_8012CF68 + 0xB68;
    AddPrim(temp_s0, D_8012CF68 + 0x22B90);
    AddPrim(temp_s0, D_8012CF68 + 0x22BA4);
    AddPrim(temp_s0, D_8012CF68 + 0x22BB8);
    AddPrim(temp_s0, D_8012CF68 + 0x22BCC);
    AddPrim(temp_s0, D_8012CF68 + 0x22BE0);
    AddPrim(temp_s0, D_8012CF68 + 0x22B70);
}

void func_8002B1A0(void) {
    s32 temp_s0;

    temp_s0 = D_8012CF68 + 0xB6C;
    if (D_801734B0 == 0) {
        if (D_80173310 & 8) {
            func_80028578(0x2C, 0x18, &D_800771B0, 0x64);
        }
        *(s32 *)0x1F800000 = func_800297D8(temp_s0, *(s32 *)0x1F800000, 0x18, 0x12, 0x58, 0x14, 0, 0, 0);
    }
}

void func_8002E400(void) {
    s32 temp_v0;

    temp_v0 = VSync(1);
    if (temp_v0 >= 0xF1) {
        D_8007C4E0 += 1;
        if (D_800771C8 < temp_v0) {
            D_800771C8 = temp_v0;
            D_8007B1C4 = D_8007B1BC;
        }
    }
    D_8007B1B8 = D_8007C4E0;
    D_8007B1C0 = D_800771C8;
}

void func_8002FAC8(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    func_8002EBF0();
    func_800355A4(4);
    D_80173310 = 0;
    D_801E91E0 = 0;
    D_801E91D8 = 0;
    D_801E9168 = 0;
    D_801D9050 = 0;
    D_801D34F8 = 0x16;
    D_8012CDD8 = D_8012D908;
    D_8012CDC0 = D_8012D8D0;
}

s32 func_80031840(s32 arg0, M2C_UNK arg1, s32 arg2, M2C_UNK arg3, s32 arg4) {
    s32 temp_v0;

    func_80031238(arg1, &D_800105D4, 0x119, 0x590, 0x100);
    func_800314BC(arg3);
    temp_v0 = func_800497E8(arg0, 2);
    if (temp_v0 >= 0) {
        if ((func_80049668(temp_v0, arg1, arg2) == arg2) && (func_80049668(temp_v0, arg3, arg4) == arg4)) {
            func_80049648(temp_v0);
            return 1;
        }
        
        return 0;
    }
    return 0;
}

s32 func_80032948(void *arg0, M2C_UNK arg1) {
    s32 temp_v0;
    s32 var_s0;
    u32 temp_s2;

    var_s0 = 0;
    temp_s2 = (u32) (M2C_FIELD(arg0, s32 *, 4) + 0x7FF) >> 0xB;
loop_1:
    func_8002E528();
    func_8002E490();
    func_80051E30(2, arg0, 0);
    func_8002E528();
    func_8002E490();
    func_80051F8C(temp_s2, arg1, 0x80);
    do {
        func_8002E528();
        func_8002E490();
        temp_v0 = func_80051CAC(1, 0);
    } while (temp_v0 > 0);
    if (temp_v0 != 0) {
        var_s0 += 1;
        if (var_s0 < 0xA) {
            goto loop_1;
        }
    }
    func_8002E528();
    func_8002E490();
    return M2C_FIELD(arg0, s32 *, 4);
}

void func_8003B26C(s16 arg0, s16 arg1, s16 arg2) {
    func_8003B340(0);
    if (arg0 < 0xA) {
        func_8004D400(arg0);
        func_8003B340(1);
        func_8003B2E4(arg1, arg2);
    }
}

void func_8003B51C(void) {
    u16 temp_v0;

    if (D_80173310 == 2) {
        func_80045750(1);
    }
    if (D_801D77D0 == 0) {
        temp_v0 = D_80173310;
        D_80173310 = temp_v0 + 1;
        if (temp_v0 >= 0xD3U) {
            D_801D34F8 = 0x1B;
        }
    }
    func_8003B388(D_80173310);
}

s32 func_800456B4(s32 arg0) {
    s32 temp_s0;

    temp_s0 = D_80077374;
    D_80077374 = arg0;
    if (arg0 != 0) {
        D_80077370(&D_80010EF4, arg0, D_80077378, D_8007737C);
    }
    return temp_s0;
}

s32 func_80045854(s32 arg0, M2C_UNK arg1) {
    s32 temp_s0;

    temp_s0 = func_800459C0(&D_80010F2C, arg0);
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(s32, s32, M2C_UNK, M2C_UNK), 8)(M2C_FIELD(g_gpu_device, s32 *, 0x20), arg0, 8, arg1);
    return temp_s0;
}

s32 func_800458B8(s32 arg0, M2C_UNK arg1) {
    s32 temp_s0;

    temp_s0 = func_800459C0(&D_80010F38, arg0);
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(s32, s32, M2C_UNK, M2C_UNK), 8)(M2C_FIELD(g_gpu_device, s32 *, 0x1C), arg0, 8, arg1);
    return temp_s0;
}

void func_80045B78(void *arg0) {
    if (D_80077374 != 0) {
        func_80048CCC(&D_80010F70, arg0);
    }
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(M2C_UNK), 0x3C)(0);
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(void *, u8), 0x14)(arg0 + 4, M2C_FIELD(arg0, u8 *, 3));
}

void func_8004617C(void *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3, s32 arg4) {
    M2C_FIELD(arg0, s8 *, 3) = 2;
    M2C_FIELD(arg0, s32 *, 4) = func_80046430(arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 8) = func_800465DC(arg4);
}

void *func_8004809C(void *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    M2C_FIELD(arg0, s16 *, 0) = arg1;
    M2C_FIELD(arg0, s16 *, 2) = arg2;
    M2C_FIELD(arg0, s16 *, 4) = arg3;
    M2C_FIELD(arg0, s16 *, 0xC) = 0;
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
    M2C_FIELD(arg0, s16 *, 0x10) = 0;
    M2C_FIELD(arg0, s16 *, 0x12) = 0;
    M2C_FIELD(arg0, s8 *, 0x19) = 0;
    M2C_FIELD(arg0, s8 *, 0x1A) = 0;
    M2C_FIELD(arg0, s8 *, 0x1B) = 0;
    M2C_FIELD(arg0, s8 *, 0x16) = 1;
    M2C_FIELD(arg0, s16 *, 8) = arg1;
    M2C_FIELD(arg0, s16 *, 0xA) = arg2;
    M2C_FIELD(arg0, s16 *, 6) = (s16) arg4;
    M2C_FIELD(arg0, s8 *, 0x17) = (s8) (arg4 != 0x1E0);
    M2C_FIELD(arg0, s16 *, 0x14) = func_8004788C(0, 0, 0x280, 0);
    M2C_FIELD(arg0, s8 *, 0x18) = 0;
    return arg0;
}

s32 func_800495DC(s32 arg0) {
    s32 temp_s1;

    temp_s1 = D_80077454;
    if (arg0 != 0) {
        func_80049638();
    } else {
        func_800497D8();
    }
    D_80077454 = arg0;
    return temp_s1;
}

void func_8004A9D4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 temp_v0;

    D_80079B98 = 0x7F;
    temp_v0 = func_80049AF4(0xFF) & 0xFF;
    D_80079BA0 = temp_v0;
    if (temp_v0 < (s32) D_800775E8) {
        func_8004A808(temp_v0, arg0 & 0xFFFF, arg1 & 0xFFFF, arg2 & 0xFFFF, arg3 & 0xFFFF);
    }
}

void func_8004B4F4(s16 arg0, s16 arg1, s32 arg2) {
    func_8004B1BC(0x20, arg0, arg1, arg2 & 0xFFFF);
}

void func_8004E8F0(s16 arg0, s16 arg1) {
    func_8004E91C(arg0, arg1);
}

void func_80058E58(void) {
    if (D_800775B8 == 1) {
        D_800775B8 = 0;
        func_80049638();
        func_8004DF1C(D_801E9228);
        func_8004DF3C(D_801E9228);
        func_800497D8();
    }
}

s32 func_80058F64(s32 arg0) {
    s32 var_v1;

    if ((D_8012CDD0 == 1) || (D_8012CDA8 == 1)) {
        return 1;
    }
    var_v1 = func_80059050(D_801E9228);
    if (arg0 == 1) {
        if (var_v1 == 0) {
            do {
                var_v1 = func_80059050(D_801E9228);
            } while (var_v1 == 0);
        }
        D_8012CDA8 = 1;
        return var_v1;
    }
    if (var_v1 == 1) {
        D_8012CDA8 = var_v1;
    }
    return var_v1;
}

void st_title_init(void) {
    u16 temp_v0;

    temp_v0 = D_801E91A0;
    D_801E91A0 = temp_v0 + 1;
    if (temp_v0 & 1) {
        func_8003EAAC();
        return;
    }
    func_80045750(0);
    D_8012CDB8 = 0x80;
    func_80013338(0x18, 0x30, 0x88);
    func_800376EC(-1);
    D_80173310 = 0;
    D_8012D010 = 0;
    func_80026794();
    func_8001CDBC(8);
    D_8012CD30 = 0;
    D_801D34F8 = 3;
}
