/* b5_03.c -- batch 5, 31 functions recovered with m2c.
 *
 * m2c was run in --valid-syntax mode over every remaining INCLUDE_ASM
 * function; what is here is everything that came back as compilable C89
 * with no unrecoverable construct -- no unresolved jump table, no
 * unaligned access, no unimplemented instruction, no 64-bit or floating
 * point type that GCC 2.7.2 would refuse.
 *
 * The split across eleven files is mechanical, not meaningful: two
 * functions can disagree about the type of a global they share or about
 * a callee's signature, and such a pair cannot live in one translation
 * unit. Regroup along real module boundaries once the units are known.
 *
 * Default flag set (-O2 -mrnames -fno-builtin -fsigned-char -gcoff).
 * Whatever does not byte-match goes back to INCLUDE_ASM via
 * tools/revert_failed.py and stays here, commented out, as the starting
 * point for a retry under -O1 or -O1 -fno-delayed-branch.
 */
#include "m2c_macros.h"

M2C_UNK AddPrim(s32, void *);
M2C_UNK SpuVoiceKeyOn(M2C_UNK);
M2C_UNK func_80013338(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_80018584(M2C_UNK *, s32);
M2C_UNK func_800185F0(M2C_UNK *, s32, s32, s32);
M2C_UNK func_8001865C(M2C_UNK *, s32);
M2C_UNK func_8001CEC8(M2C_UNK);
M2C_UNK func_8001EF54(M2C_UNK);
M2C_UNK func_8001F098();
M2C_UNK func_8001FFD8(M2C_UNK, s32, s32, M2C_UNK, s32);
M2C_UNK func_80025EB0(s32 *);
M2C_UNK func_80026794();
M2C_UNK func_80028578(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK func_8002E490();
M2C_UNK func_8002E528();
M2C_UNK func_8002EBF0();
M2C_UNK func_8002ED1C(M2C_UNK);
M2C_UNK func_80030030();
M2C_UNK func_800304E0();
M2C_UNK func_800355A4(M2C_UNK);
M2C_UNK func_800376EC(M2C_UNK);
M2C_UNK func_8003FC08(u8, u8, u8, s16);
M2C_UNK func_80042E08(M2C_UNK *, M2C_UNK *);
M2C_UNK func_80043470(M2C_UNK *);
M2C_UNK func_80045750(M2C_UNK);
M2C_UNK func_80045790(M2C_UNK);
M2C_UNK func_800458B8(s16 *, void *);
M2C_UNK func_8004617C(void *, M2C_UNK, M2C_UNK, s32, M2C_UNK *);
M2C_UNK func_80046738(M2C_UNK);
M2C_UNK func_80047354(M2C_UNK);
M2C_UNK func_80047AF8(void *, M2C_UNK);
M2C_UNK func_80047C60(void *);
M2C_UNK func_80048198(M2C_UNK *, s32, s32, s32, s32, s32);
M2C_UNK func_80048F80();
M2C_UNK func_80049638();
M2C_UNK func_800496B8(M2C_UNK *);
M2C_UNK func_800496C8(M2C_UNK *, s32, s32);
M2C_UNK func_800497D8();
M2C_UNK func_80049D7C(M2C_UNK, s32);
M2C_UNK func_8004A33C(u8);
M2C_UNK func_8004A4DC(s16);
M2C_UNK func_8004A8D0(s16);
M2C_UNK func_8004C8AC(s32, s16, s16, s32, s32, s32, s32);
M2C_UNK func_8004CC08(s16, u8, u8 *, s32);
M2C_UNK func_8004CDDC(s16, u8, s32, M2C_UNK *);
M2C_UNK func_8004D018(s16, u8, s32, M2C_UNK *);
M2C_UNK func_8004DF2C(s32);
M2C_UNK func_80052410(M2C_UNK, void *);
M2C_UNK func_80052440(u8);
M2C_UNK func_800524D8();
M2C_UNK func_800555C8();
M2C_UNK func_80055810(s32, u32);
M2C_UNK func_80055E2C(s32, M2C_UNK, s32 *);
M2C_UNK snd_play_se(M2C_UNK);
extern M2C_UNK (*D_80077370)(M2C_UNK *, s32, void *, s32, s32);
extern M2C_UNK D_8001028C;
extern M2C_UNK D_800105BC;
extern M2C_UNK D_80010F2C;
extern M2C_UNK D_80011180;
extern M2C_UNK D_80011584;
extern M2C_UNK D_80076C0C;
extern M2C_UNK D_80076C80;
extern M2C_UNK D_80076E30;
extern M2C_UNK D_80077128;
extern M2C_UNK D_80077258;
extern M2C_UNK D_80077260;
extern M2C_UNK D_800775BC;
extern M2C_UNK D_80077610;
extern M2C_UNK D_80077615;
extern M2C_UNK D_800782C0;
extern M2C_UNK D_800782C4;
extern M2C_UNK D_800782C8;
extern M2C_UNK D_800797D8;
extern M2C_UNK D_800797DA;
extern M2C_UNK D_800797DC;
extern M2C_UNK D_800797DE;
extern M2C_UNK D_800797E0;
extern M2C_UNK D_800797E2;
extern M2C_UNK D_800797E4;
extern M2C_UNK D_800797E6;
extern M2C_UNK D_800797E8;
extern M2C_UNK D_800797EA;
extern M2C_UNK D_800797EF;
extern M2C_UNK D_80079D70;
extern M2C_UNK D_8017319A;
extern M2C_UNK D_8017319B;
extern M2C_UNK D_8017319C;
extern M2C_UNK D_801733E0;
extern M2C_UNK D_801733E4;
extern M2C_UNK D_801733E8;
extern M2C_UNK D_801734E0;
extern M2C_UNK D_801D7670;
extern M2C_UNK D_801D7672;
extern M2C_UNK D_801D7676;
extern M2C_UNK D_801E90E8;
extern M2C_UNK D_801E91F0;
extern s16 D_8007306E;
extern s16 D_80077296;
extern s16 D_800772FC;
extern s16 D_80079BA0;
extern s16 D_8007C25A;
extern s16 D_8012CDB8;
extern s16 D_8012CF90;
extern s16 D_8012CFD8;
extern s16 D_80173150;
extern s16 D_8017315E;
extern s16 D_80173160;
extern s16 D_80173164;
extern s16 D_80173166;
extern s16 D_80173168;
extern s16 D_80173310;
extern s16 D_80173330;
extern s16 D_801733B8;
extern s16 D_801D34F0;
extern s16 D_801D34F8;
extern s16 D_801D35C8;
extern s16 D_801D77B0;
extern s16 D_801D7E18;
extern s16 D_801D7EA0;
extern s16 D_801D7EA2;
extern s16 D_801E90A8;
extern s16 D_801E90C0;
extern s16 D_801E91A0;
extern s16 D_801E91A8;
extern s16 D_801E91B0;
extern s32 *D_800773A0;
extern s32 *D_80173340;
extern s32 D_80074048;
extern s32 D_80077248;
extern s32 D_80077388;
extern s32 D_8007738C;
extern s32 D_8007745C;
extern s32 D_80077474;
extern s32 D_800775B8;
extern s32 D_8007B1A0;
extern s32 D_8007B1BC;
extern s32 D_8007B1C0;
extern s32 D_8007B1C4;
extern s32 D_8007C2F8;
extern s32 D_8007C48C;
extern s32 D_8012CD30;
extern s32 D_8012CD88;
extern s32 D_8012CDA8;
extern s32 D_8012CDD0;
extern s32 D_8012CF68;
extern s32 D_8012D088;
extern s32 D_80173300;
extern s32 D_80173320;
extern s32 D_80173328;
extern s32 D_80173350;
extern s32 D_801733B0;
extern s32 D_801733D8;
extern s32 D_801734C8;
extern s32 D_801D35A0;
extern s32 D_801D7E10;
extern s32 D_801D7E9C;
extern s32 D_801D7EA4;
extern s32 D_801D7EA8;
extern s32 D_801D9050;
extern s32 D_801D9078;
extern s32 D_801D907C;
extern s32 D_801D9080;
extern s32 D_801E90E0;
extern s32 D_801E9168;
extern s32 D_801E91C0;
extern s32 D_801E91D8;
extern s32 D_801E91E0;
extern s32 D_801E9228;
extern s32 D_801E9238;
extern s8 D_80079B88;
extern s8 D_80079B8A;
extern s8 D_80079B8B;
extern s8 D_80079B8C;
extern s8 D_80079B8D;
extern s8 D_80173155;
extern u16 D_80079B9E;
extern u16 D_8007B1E8;
extern u16 D_8007C210;
extern u16 D_8007C500;
extern u16 D_8007C502;
extern u16 D_8007C504;
extern u16 D_8012CDB0;
extern u16 D_8012CFF8;
extern u16 D_8012CFFA;
extern u16 D_8012CFFC;
extern u16 D_8012D0B0;
extern u16 D_8012D8C8;
extern u16 D_801733C0;
extern u16 D_801733D0;
extern u16 D_80173430;
extern u16 D_801D35AE;
extern u16 D_801D7678;
extern u16 D_801D77D0;
extern u16 D_801D7808;
extern u16 D_801D9068;
extern u16 D_801D906C;
extern u16 D_801D9070;
extern u8 D_800774CF;
extern u8 D_800775E8;
extern u8 D_80079B8F;
extern u8 D_80079B92;
extern u8 D_80079B93;
extern u8 D_80079B94;
extern u8 D_80079B95;
extern u8 D_80079B96;
extern u8 D_80079B97;
extern u8 D_80079B98;
extern u8 D_80079B99;
extern u8 D_80079B9A;
extern u8 D_80079B9B;
extern u8 D_80079B9C;
extern u8 D_80079B9D;
extern u8 D_80173152;
extern u8 D_80173153;
extern u8 D_80173154;
extern u8 D_80173156;
extern u8 D_80173157;
extern u8 D_80173158;
extern u8 D_8017315A;
extern u8 D_8017315B;
extern u8 D_8017315C;
extern u8 D_80173188;
extern u8 D_801D35A9;
extern void *g_gpu_device;
s32 VSync(M2C_UNK);
s32 func_80017B58(s32, s32, s32, s32, s32 *, s32 *);
s32 func_80019C6C(s32, s32);
s32 func_8001BAFC(s32 *, s32);
s32 func_8002721C(s32, s32);
s32 func_80031378(u8 *);
s32 func_80031B24(u8 *, s32);
s32 func_800459C0(M2C_UNK *, s32);
s32 func_8004788C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_80047920(s16, s16);
s32 func_800489EC(u8);
s32 func_80048A80(u8);
s32 func_80049798(u8 *);
s32 func_80049818(M2C_UNK *, u8 *);
s32 func_80049AF4(s16);
s32 func_8004ACE4(s16, s16);
s32 func_8004C27C(s16, s16);
s32 func_8004DF5C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_80050DF8(s32, s16);
s32 func_80051D14(s32);
s32 func_80052974(M2C_UNK, M2C_UNK);
s32 func_80052D14(s32, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_80055800(M2C_UNK *, M2C_UNK);
s32 func_80058BB8(s32);
s32 func_800591F8();
s32 rcos(s32);
s32 rsin(s32, s32);

void func_800186C8(void) {
    M2C_UNK sp10;
    s32 temp_a2;
    s32 temp_a3;

    D_8007B1BC = D_801D9068 | (D_801D9078 << 0x10);
    temp_a2 = D_801D906C | (D_801D907C << 0x10);
    D_8007B1C0 = temp_a2;
    temp_a3 = D_801D9070 | (D_801D9080 << 0x10);
    D_8007B1C4 = temp_a3;
    func_800185F0(&D_801E91F0, D_801D907C, temp_a2, temp_a3);
    func_8001865C(&sp10, D_801D9078);
    func_80042E08(&sp10, &D_801E91F0);
    func_80018584(&sp10, D_801D9080);
    func_80042E08(&sp10, &D_801E91F0);
    func_80043470(&D_801E91F0);
}

s32 func_8001BD9C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp18;
    s32 sp20;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp38;
    s32 sp40;
    s32 sp48;
    s32 sp50;
    s32 sp58;
    M2C_UNK var_a0_2;
    M2C_UNK var_a0_3;
    M2C_UNK var_a0_4;
    s16 *var_s2;
    s16 *var_s3;
    s32 temp_a1;
    s32 temp_fp;
    s32 temp_hi;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s6;
    s32 temp_v0;
    s32 var_a0;
    s32 var_s1;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_v0;
    s32 var_v0_2;

    sp30 = arg0;
    sp38 = arg1;
    sp40 = arg2;
    var_s6 = arg3;
    if (arg3 < 0) {
        var_s6 = arg3 + 0xFF;
    }
    temp_s6 = var_s6 >> 8;
    temp_hi = (s32) (temp_s6 + (D_801E90E0 << 8)) % (s32) D_801E90E0;
    var_s5 = 0;
    var_s4 = 0;
    var_s1 = 0;
    var_s2 = &D_8007306E;
    var_s3 = &D_8007306E - 2;
    temp_s0 = -sp40;
    sp50 = (temp_hi * 0x14) + D_801733D8;
    temp_fp = rsin(temp_s0, temp_hi);
    temp_s0_2 = rcos(temp_s0);
    sp58 = -temp_fp;
    do {
        sp18 = sp30 + ((s32) ((temp_s0_2 * *var_s3) + (temp_fp * *var_s2)) / 8192);
        var_v0_2 = (sp58 * *var_s3) + (temp_s0_2 * *var_s2);
        if (var_v0_2 < 0) {
            var_v0_2 += 0xFFF;
        }
        sp20 = sp38 + ((s32) (var_v0_2 >> 0xC) / 2);
        sp28 = func_8001BAFC(&sp18, arg3);
        temp_v0 = func_80017B58(sp18, sp20, temp_s6, sp50, &sp28, &sp2C);
        var_s5 |= temp_v0;
        var_a0 = 0;
        if (temp_v0 & 1) {
            sp48 = var_s4;
        }
        *(&D_801733E0 + var_s1) = sp18;
        temp_a1 = var_s1;
        if ((var_s5 & 2) && (sp2C < -0x7D)) {
            var_a0 = sp2C + 0x7D;
        }
        *(&D_801733E4 + temp_a1) = var_a0;
        var_s2 += 4;
        var_s3 += 4;
        var_s4 += 1;
        *(&D_801733E8 + var_s1) = sp20;
        var_s1 += 0x10;
    } while (var_s4 < 4);
    var_v0 = var_s5 & 1;
    if (var_v0 != 0) {
        if ((u32) (func_80019C6C(func_8002721C(arg3, temp_a1), sp40) - 0x201) < 0x3FFU) {
            var_a0_2 = 0x12;
            if (D_8007C2F8 >= 0x321) {
                var_a0_2 = 0x11;
            }
            snd_play_se(var_a0_2);
            return var_s5 & 1;
        }
        if (sp48 & 1) {
            var_a0_3 = 0x14;
            if (D_8007C2F8 >= 0x321) {
                var_a0_3 = 0x13;
            }
            snd_play_se(var_a0_3);
            return var_s5 & 1;
        }
        var_a0_4 = 0x16;
        if (D_8007C2F8 >= 0x321) {
            var_a0_4 = 0x15;
        }
        snd_play_se(var_a0_4);
        var_v0 = var_s5 & 1;
        
        return var_v0;
    }
    return var_v0;
}

void func_8001F0FC(void) {
    s16 var_a0;
    s32 var_v1;

    func_80045750(0);
    func_80013338(0x60, 0x80, 0xC0);
    func_800376EC(-1);
    func_8001F098();
    D_8012D088 = 0;
    func_800355A4(3);
    D_80173310 = 0;
    D_8012CF90 = 0;
    D_801D77B0 = 4;
    D_801E91A8 = 0;
    D_801E90C0 = 0;
    D_801D7E18 = 0;
    D_801E91B0 = 8;
    if (D_8007C25A == 0xC) {
        D_8007C25A = -1;
    }
    D_801E91C0 = D_8007C25A << 0x10;
    var_a0 = 4;
    if ((D_801733C0 & 0xF) == 0xF) {
        var_a0 = 8;
    }
    D_801E90A8 = var_a0;
    var_v1 = 4;
    if (D_801D35C8 != 0) {
        var_v1 = 0xC;
    }
    D_80173300 = var_v1;
    if (D_801733B8 != 0) {
        D_801733B8 = 0;
        D_8007C210 += 4;
    }
    D_8012CDB8 = 0x80;
    D_801D34F8 = 7;
}

void func_800203F0(void *arg0) {
    M2C_UNK var_a3;
    s32 temp_a2;
    s32 var_s0;
    s32 var_s1;
    void *temp_s3;
    void *var_s2;

    func_80028578(0xF8, 0x18, &D_8001028C, 0x7F);
    var_s1 = 0;
    temp_s3 = arg0 + 0x58;
    if (M2C_FIELD(arg0, s16 *, 0xD4) > 0) {
        var_s2 = temp_s3;
        if (D_801D35A0 > 0) {
            var_s0 = 0x20;
loop_3:
            var_a3 = 0x64;
            if (M2C_FIELD(temp_s3, s16 *, 0x76) == var_s1) {
                var_a3 = 0x7F;
            }
            temp_a2 = M2C_FIELD(var_s2, s32 *, 0x98);
            var_s2 += 4;
            func_8001FFD8(0xF8, var_s0, temp_a2, var_a3, 0x3E8);
            var_s1 += 1;
            var_s0 += 8;
            if ((var_s1 < M2C_FIELD(temp_s3, s16 *, 0x7C)) && (var_s1 < D_801D35A0)) {
                goto loop_3;
            }
        }
    }
}

void func_80025F74(void) {
    s16 temp_a3;
    s32 *temp_a0;
    s32 temp_s0;

    temp_a0 = D_80173340;
    if (*temp_a0 == ((s32) D_8012CD88 % 9000)) {
        D_80173340 = temp_a0 + 0x10;
        func_80025EB0(temp_a0);
        if (*D_80173340 < 0) {
            D_80173340 = D_80074048 + 0x10;
        }
    }
    if (D_80173150 != 0) {
        temp_a3 = D_8017315E + 1;
        if (D_8017315E < D_80173160) {
            temp_s0 = D_80173160 - temp_a3;
            D_80173152 = (u8) ((s32) ((D_80173156 * temp_s0) + (D_8017315A * temp_a3)) / (s16) D_80173160);
            D_80173153 = (u8) ((s32) ((D_80173157 * temp_s0) + (D_8017315B * temp_a3)) / (s16) D_80173160);
            D_80173154 = (u8) ((s32) ((D_80173158 * temp_s0) + (D_8017315C * temp_a3)) / (s16) D_80173160);
            D_8017315E = temp_a3;
            func_8003FC08(D_80173152, D_80173153, D_80173154, temp_a3);
            if (D_80173164 != 0) {
                D_80173155 = (s8) ((s32) ((D_80173166 * temp_s0) + (D_80173168 * D_8017315E)) / (s16) D_80173160);
            }
            if ((D_8017315E == D_80173160) && ((u16) D_80173152 == 0x8080) && (D_80173154 == 0x80)) {
                D_80173150 = 0;
            }
        }
    }
}

void func_8002A788(s8 arg0, M2C_UNK arg1) {
    s32 temp_s2;
    s8 var_s1;
    void *temp_a1;
    void *temp_s0;
    void *var_s0;

    var_s1 = arg0;
    var_s0 = *(void **)0x1F800000;
    temp_s2 = D_8012CF68 + 0xB6C;
    if (var_s1 >= 0xC9) {
        var_s1 -= 0xC8;
        func_80047C60(var_s0);
        func_80047AF8(var_s0, 1);
        M2C_FIELD(var_s0, s16 *, 8) = 0;
        M2C_FIELD(var_s0, s16 *, 0xA) = 0;
        M2C_FIELD(var_s0, s16 *, 0xC) = 0x140;
        M2C_FIELD(var_s0, s16 *, 0xE) = 0xF0;
        M2C_FIELD(var_s0, s8 *, 4) = 0xFF;
        M2C_FIELD(var_s0, s8 *, 5) = 0xFF;
        M2C_FIELD(var_s0, s8 *, 6) = 0xFF;
        temp_a1 = var_s0;
        var_s0 += 0x10;
        AddPrim(temp_s2, temp_a1);
    }
    func_80047C60(var_s0);
    func_80047AF8(var_s0, 1);
    M2C_FIELD(var_s0, s16 *, 8) = 0;
    M2C_FIELD(var_s0, s16 *, 0xA) = 0;
    M2C_FIELD(var_s0, s16 *, 0xC) = 0x140;
    M2C_FIELD(var_s0, s16 *, 0xE) = 0xF0;
    M2C_FIELD(var_s0, s8 *, 4) = var_s1;
    M2C_FIELD(var_s0, s8 *, 5) = var_s1;
    M2C_FIELD(var_s0, s8 *, 6) = var_s1;
    temp_s0 = var_s0 + 0x10;
    AddPrim(temp_s2, var_s0);
    func_8004617C(temp_s0, 0, 1, func_8004788C(0, arg1, 0x140, 0) & 0xFFFF, &D_80077128);
    AddPrim(temp_s2, temp_s0);
    *(void **)0x1F800000 = temp_s0 + 0xC;
}

void func_800308B8(void) {
    u16 temp_a0;
    u16 temp_a1;
    u16 temp_a2;
    u16 temp_v1;

    func_80045750(0);
    func_80013338(0, 0, 0);
    func_8002EBF0();
    func_800355A4(4);
    temp_v1 = D_801D7808;
    temp_a0 = D_8012CFF8;
    temp_a1 = D_8012CFFA;
    temp_a2 = D_8012CFFC;
    D_80173310 = 0;
    D_801E91E0 = 0;
    D_801E91D8 = 0;
    D_801E9168 = 0;
    D_801D9050 = 0;
    D_801D7808 = 0;
    D_8012CFF8 = 0;
    D_8012CFFA = 0;
    D_8012CFFC = 0;
    D_801D34F8 = 0x23;
    D_80173430 = temp_v1;
    D_8007C500 = temp_a0;
    D_8007C502 = temp_a1;
    D_8007C504 = temp_a2;
    D_8012CDB0 = D_8012D0B0;
}

void func_80030AB4(void) {
    func_8001CEC8(1);
    if (D_801D77D0 == 0) {
        D_8007B1E8 += 1;
        if (D_801D35AE & 0x90) {
            D_8012D0B0 = D_8012CDB0;
            snd_play_se(0x24);
            D_801D34F8 = 0x11;
        }
        if (D_801D35AE & 0x860) {
            snd_play_se(0x2D);
            D_801D34F8 = 0x27;
        }
        if ((D_801D35AE & 0x8000) && ((s16) D_8012D0B0 > 0)) {
            D_8012D0B0 = (s16) D_8012D0B0 - 1;
            snd_play_se(0x21);
        }
        if ((D_801D35AE & 0x2000) && ((s16) D_8012D0B0 < 3)) {
            D_8012D0B0 = (s16) D_8012D0B0 + 1;
            snd_play_se(0x2C);
        }
        if (D_801D35A9 != 0x23) {
            D_801D34F8 = 0x11;
            D_8012D0B0 = D_8012CDB0;
        }
    }
    D_801E91D8 = -0x380;
    func_80030030();
    func_8002ED1C(1);
    func_8001EF54(0x1D8);
}

void func_80030C38(void) {
    func_8001CEC8(1);
    if (D_801D77D0 == 0) {
        D_8007B1E8 += 1;
        if (D_801D35AE & 0x90) {
            D_801733D0 = D_8012D8C8;
            snd_play_se(0x24);
            D_801D34F8 = 0x11;
        }
        if (D_801D35AE & 0x860) {
            snd_play_se(0x2D);
            D_801D34F8 = 0x11;
        }
        if ((D_801D35AE & 0x8000) && ((s16) D_801733D0 > 0)) {
            D_801733D0 = (s16) D_801733D0 - 1;
            snd_play_se(0x21);
        }
        if ((D_801D35AE & 0x2000) && ((s16) D_801733D0 < 3)) {
            D_801733D0 = (s16) D_801733D0 + 1;
            snd_play_se(0x2C);
        }
        if (D_801D35A9 != 0x23) {
            D_801D34F8 = 0x11;
            D_801733D0 = D_8012D8C8;
        }
    }
    D_801E91D8 = -0x380;
    func_800304E0();
    func_8002ED1C(1);
    func_8001EF54(0x1D8);
}

void func_800313E4(void) {
    s32 temp_lo;
    s32 var_a1;
    s32 var_v1;

    var_a1 = 0;
    var_v1 = 1;
loop_1:
    if (var_v1 & D_80173328) {
        var_a1 += 1;
        var_v1 *= 2;
        if (var_a1 < 0x20) {
            goto loop_1;
        }
    }
    temp_lo = (s32) D_8007C48C / 1000;
    func_80048198(&D_800105BC, D_80077248, temp_lo / 60, temp_lo % 60, (s32) D_8007C48C % 1000, var_a1);
}

void func_80037C74(s32 arg0) {
    s16 var_s0;
    s32 var_s1;
    s32 var_s2;

    func_8002E528();
    var_s2 = 0;
    var_s1 = 0;
    var_s0 = 0x100;
    do {
        var_s2 += 1;
        if (VSync(1) >= 0xC8) {
            func_8002E490();
            func_8002E528();
        }
        D_80077296 = var_s0;
        func_800458B8(&D_80077296 - 2, (arg0 * 0x30000) + (var_s1 + &D_801734E0));
        func_80045790(0);
        var_s1 += 0x6000;
        var_s0 += 0x20;
    } while (var_s2 < 8);
    func_8002E490();
}

void func_8003B040(void) {
    s32 var_s0;
    s32 var_s2;
    u16 *var_s1;
    u16 temp_a3;

    if (D_800772FC != 0) {
        D_800772FC = 0;
        var_s2 = 0;
        var_s1 = &D_801D7678;
        var_s0 = 0;
        do {
            if (*(&D_801D7670 + var_s0) != 0) {
                temp_a3 = *(&D_801D7676 + var_s0);
                func_8004C8AC(var_s2, D_801D34F0, *(&D_801D7672 + var_s0), (s32) (temp_a3 << 0x10) >> 0x17, temp_a3 & 0x7F, (s32) (*var_s1 << 0x10) >> 0x17, *var_s1 & 0x7F);
            }
            var_s1 += 0xA;
            var_s2 += 1;
            var_s0 += 0xA;
        } while (var_s2 < 0x18);
    }
}

void func_8003B4C4(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    D_80173310 = 0;
    D_801D34F8 = 0x10;
    D_801E91A0 = 0;
    D_8012CD30 = 0x64;
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

s32 func_80045854(s32 arg0, M2C_UNK arg1) {
    s32 temp_s0;

    temp_s0 = func_800459C0(&D_80010F2C, arg0);
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(s32, s32, M2C_UNK, M2C_UNK), 8)(M2C_FIELD(g_gpu_device, s32 *, 0x20), arg0, 8, arg1);
    return temp_s0;
}

s32 func_80048038(s32 arg0, s16 arg1, s16 arg2) {
    s16 sp10;
    s16 sp12;
    s16 sp14;
    s16 sp16;

    sp10 = arg1;
    sp12 = arg2;
    sp14 = 0x100;
    sp16 = 1;
    func_80045854(&sp10, arg0);
    return func_80047920(arg1, arg2) & 0xFFFF;
}

s32 func_80048CCC(s32 arg0, void *arg1) {
    s32 temp_v1;

    temp_v1 = func_80048A80(M2C_FIELD(arg1, u8 *, 7)) & 0xFF;
    if (temp_v1 != 0) {
        if (temp_v1 != M2C_FIELD(arg1, u8 *, 3)) {
            D_80077370(&D_80011180, arg0, arg1, func_800489EC(M2C_FIELD(arg1, u8 *, 7)), (s32) M2C_FIELD(arg1, u8 *, 3));
            return -1;
        }
        
        return 0;
    }
    return 0;
}

void func_8004B900(s16 arg0) {
    s32 var_s0;
    s32 var_v0;

    var_s0 = 0;
    if (D_800775E8 != 0) {
        var_v0 = 0 & 0xFF;
        do {
            if (*(&D_800797E2 + (var_v0 * 0x18)) == arg0) {
                D_80079BA0 = var_s0 & 0xFF;
                SpuVoiceKeyOn(0);
            }
            var_s0 += 1;
            var_v0 = var_s0 & 0xFF;
        } while ((u32) (var_s0 & 0xFF) < (u8) D_800775E8);
    }
}

s16 func_8004C380(s16 arg0, s16 arg1, u8 arg2, s8 arg3, u16 arg4, s32 arg5, s32 arg6) {
    s16 temp_s1;
    s16 var_v0;
    s32 temp_v0_3;
    u16 temp_a0;
    void *temp_v0;
    void *temp_v0_2;

    var_v0 = -1;
    if (func_8004ACE4(arg0, arg1) == 0) {
        D_80079B88 = 0x20;
        D_80079B8A = arg3;
        D_80079B8B = (s8) arg4;
        D_80079B95 = arg2;
        if ((s16) arg5 == (s16) arg6) {
            D_80079B8D = 0x40;
            D_80079B8C = (s8) arg5;
        } else if ((s16) arg6 < (s16) arg5) {
            D_80079B8C = (s8) arg5;
            D_80079B8D = (s8) ((s32) ((s16) arg6 << 6) / (s16) arg5);
        } else {
            D_80079B8C = (s8) arg6;
            D_80079B8D = 0x7F - ((s32) ((s16) arg5 << 6) / (s16) arg6);
        }
        temp_v0 = ((s32) (arg1 << 0x10) >> 0xC) + D_80173350;
        D_80079B92 = M2C_FIELD(temp_v0, u8 *, 1);
        D_80079B93 = M2C_FIELD(temp_v0, u8 *, 4);
        D_80079B94 = M2C_FIELD(temp_v0, u8 *, 0);
        temp_v0_2 = ((D_80079B95 + (D_80079B8F * 0x10)) << 5) + D_801733B0;
        D_80079B98 = M2C_FIELD(temp_v0_2, u8 *, 0);
        temp_a0 = M2C_FIELD(temp_v0_2, u16 *, 0x16);
        D_80079B9E = temp_a0;
        D_80079B96 = M2C_FIELD(temp_v0_2, u8 *, 2);
        D_80079B97 = M2C_FIELD(temp_v0_2, u8 *, 3);
        D_80079B99 = M2C_FIELD(temp_v0_2, u8 *, 4);
        D_80079B9A = M2C_FIELD(temp_v0_2, u8 *, 5);
        D_80079B9D = M2C_FIELD(temp_v0_2, u8 *, 1);
        D_80079B9B = M2C_FIELD(temp_v0_2, u8 *, 6);
        D_80079B9C = M2C_FIELD(temp_v0_2, u8 *, 7);
        var_v0 = -1;
        if ((s16) temp_a0 != 0) {
            temp_s1 = func_80049AF4((s16) temp_a0) & 0xFF;
            if (temp_s1 == D_800775E8) {
                return -1;
            }
            D_80079BA0 = temp_s1;
            temp_v0_3 = temp_s1 * 0x18;
            *(&D_800797E2 + temp_v0_3) = 0x20;
            *(&D_800797EA + temp_v0_3) = arg0;
            *(&D_800797E6 + temp_v0_3) = arg1;
            *(&D_800797E4 + temp_v0_3) = (s16) D_80079B8F;
            *(&D_800797D8 + temp_v0_3) = D_80079B9E;
            *(&D_800797E0 + temp_v0_3) = (s16) arg3;
            *(&D_800797EF + temp_v0_3) = 1;
            *(&D_800797DA + temp_v0_3) = 0;
            *(&D_800797E8 + temp_v0_3) = (s16) D_80079B95;
            func_8004A33C(D_80079B95);
            if ((s16) D_80079B9E == 0xFF) {
                func_8004A4DC(temp_s1);
                return temp_s1;
            }
            func_80049D7C(1, func_8004C27C((s16) arg3, (s16) arg4) & 0xFFFF);
            var_v0 = temp_s1;
            
            return var_v0;
        }
        
        return var_v0;
    }
    return var_v0;
}

s32 func_8004C74C(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    s32 temp_t0;

    if ((u32) (arg0 & 0xFFFF) < 0x18U) {
        temp_t0 = arg0 * 0x18;
        if ((*(&D_800797EF + temp_t0) == 1) && (*(&D_800797EA + temp_t0) == arg1) && (*(&D_800797E6 + temp_t0) == arg2) && (*(&D_800797E8 + temp_t0) == arg3) && (*(&D_800797E0 + temp_t0) == (s16) arg4)) {
            if (*(&D_800797D8 + temp_t0) == 0xFF) {
                func_8004A8D0(arg0);
                return 0;
            }
            D_80079BA0 = arg0;
            SpuVoiceKeyOn(0);
            return 0;
        }
        
        return -1;
    }
    return -1;
}

void func_8004D774(void) {
    s16 temp_v0;
    s16 var_s0;
    s32 temp_a0;
    s32 temp_v0_2;
    s32 var_a0;
    void *temp_a0_2;

    var_s0 = 0;
    if (D_800775E8 != 0) {
        var_a0 = 0 << 0x10;
        do {
            temp_a0 = var_a0 >> 0x10;
            temp_v0_2 = temp_a0 * 0x18;
            *(&D_800797DA + temp_v0_2) = 0x18;
            *(&D_800797D8 + temp_v0_2) = 0xFF;
            *(&D_800797EF + temp_v0_2) = 0;
            *(&D_800797DC + temp_v0_2) = 0;
            *(&D_800797DE + temp_v0_2) = 0;
            *(&D_800797E2 + temp_v0_2) = 0xFF;
            *(&D_800797E4 + temp_v0_2) = 0;
            *(&D_800797E6 + temp_v0_2) = 0;
            *(&D_800797E8 + temp_v0_2) = 0xFF;
            temp_a0_2 = ((s32) (temp_a0 << 0x13) >> 0xF) + D_8007745C;
            M2C_FIELD(temp_a0_2, s16 *, 0) = 0;
            M2C_FIELD(temp_a0_2, s16 *, 2) = 0;
            M2C_FIELD(temp_a0_2, s16 *, 6) = 0x200;
            M2C_FIELD(temp_a0_2, s16 *, 4) = 0x1000;
            M2C_FIELD(temp_a0_2, s16 *, 8) = 0x80FF;
            M2C_FIELD(temp_a0_2, s16 *, 0xA) = 0x4000;
            D_80079BA0 = var_s0;
            SpuVoiceKeyOn(1);
            temp_v0 = var_s0 + 1;
            var_s0 = temp_v0;
            var_a0 = var_s0 << 0x10;
        } while (temp_v0 < (s32) D_800775E8);
    }
}

void func_8004F6D8(s32 arg0, s16 arg1, s32 arg2) {
    u8 sp10;
    M2C_UNK sp20;
    s8 sp21;
    s32 *temp_s1;
    s32 temp_s0;
    s32 temp_s0_3;
    s32 temp_s1_2;
    s32 var_s1;
    s32 var_s3;
    s32 var_s3_2;
    u8 temp_s5;
    void *temp_s0_2;
    void *temp_s0_4;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_s1 = ((s32) (arg0 << 0x10) >> 0xE) + &D_801E90E8;
    temp_v0 = (arg1 * 0xA8) + *temp_s1;
    temp_s5 = M2C_FIELD(temp_v0, u8 *, 0x12);
    func_8004CC08(M2C_FIELD(temp_v0, s16 *, 0x4A), M2C_FIELD((temp_s5 + temp_v0), u8 *, 0x2C), &sp10, arg0);
    if ((u32) (arg2 & 0xFF) < 0x40U) {
        var_s3 = 0;
        if ((s32) sp10 > 0) {
            do {
                temp_s0 = arg1 * 0xA8;
                temp_v0_2 = temp_s0 + *temp_s1;
                func_8004CDDC(M2C_FIELD(temp_v0_2, s16 *, 0x4A), M2C_FIELD((temp_v0_2 + temp_s5), u8 *, 0x2C), var_s3, &sp20);
                sp21 = 2;
                temp_s0_2 = temp_s0 + *temp_s1;
                func_8004D018(M2C_FIELD(temp_s0_2, s16 *, 0x4A), M2C_FIELD((temp_s0_2 + temp_s5), u8 *, 0x2C), var_s3, &sp20);
                var_s3 += 1;
                var_s1 = arg0 << 0x10;
            } while (var_s3 < (s32) sp10);
        } else {
            goto block_9;
        }
    } else {
        if ((u32) ((arg2 - 0x40) & 0xFF) < 0x40U) {
            var_s3_2 = 0;
            if ((s32) sp10 > 0) {
                do {
                    temp_s0_3 = arg1 * 0xA8;
                    temp_v0_3 = temp_s0_3 + *temp_s1;
                    func_8004CDDC(M2C_FIELD(temp_v0_3, s16 *, 0x4A), M2C_FIELD((temp_v0_3 + temp_s5), u8 *, 0x2C), var_s3_2, &sp20);
                    sp21 = 0;
                    temp_s0_4 = temp_s0_3 + *temp_s1;
                    func_8004D018(M2C_FIELD(temp_s0_4, s16 *, 0x4A), M2C_FIELD((temp_s0_4 + temp_s5), u8 *, 0x2C), var_s3_2, &sp20);
                    var_s3_2 += 1;
                } while (var_s3_2 < (s32) sp10);
            }
        }
block_9:
        var_s1 = arg0 << 0x10;
    }
    temp_s1_2 = var_s1 >> 0x10;
    M2C_FIELD(((arg1 * 0xA8) + *(&D_801E90E8 + (temp_s1_2 * 4))), s32 *, 0x88) = func_80050DF8(temp_s1_2, arg1);
}

s32 func_80051EF0(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_s1;

    temp_s1 = arg0 & 0xFF;
    if (func_80051D14(temp_s1) == 0) {
        if (func_80052D14(temp_s1, arg1, arg2, 0) == 0) {
            return func_80052974(0, arg2) == 2;
        }
        
        return 0;
    }
    return 0;
}

void func_8005209C(s8 arg0, s8 arg1) {
    s8 sp10;
    s8 sp11;

    sp10 = arg0;
    sp11 = arg1;
    func_80051EF0(0xD, &sp10, 0);
}

s32 func_80052A98(s32 arg0, M2C_UNK arg1) {
    s32 var_s0;
    s32 var_s1;

    var_s0 = 0;
    var_s1 = 0x07FFFFFF;
loop_1:
    func_800524D8();
    if (M2C_FIELD(&D_80077615, u8 *, 0) != 0) {
        var_s0 = 5;
    }
    if (M2C_FIELD(&D_80077615, u8 *, -1) != 0) {
        var_s0 = 4;
    }
    if (M2C_FIELD(&D_80077615, u8 *, -4) != 0) {
        var_s0 = 1;
    }
    if (var_s0 != 0) {
        if (D_80077474 != 0) {
            func_800496C8(&D_80011584, *(&D_80076C0C + (D_800774CF * 4)), *(&D_80076C80 + (var_s0 * 4)));
        }
        *(&D_80077610 + var_s0) = 0;
        func_80052410(arg1, (var_s0 * 8) + &D_80079D70);
        return var_s0;
    }
    var_s1 -= 1;
    if (arg0 != 0) {
        return 0;
    }
    if (var_s1 == -1) {
        func_80052440(D_800774CF);
        return -1;
    }
    goto loop_1;
}

void func_80058D0C(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    func_80048F80();
    func_800555C8();
    temp_v0 = func_80055800(&D_800775BC, 3);
    D_80173320 = temp_v0;
    D_801D7E10 = 0;
    D_8007B1A0 = 0;
    func_80055E2C(temp_v0, 0x60, &D_801D7E10);
    D_801D7E9C = 0;
    D_801D7EA0 = 0;
    D_801D7EA2 = 0;
    D_801D7EA4 = 0;
    D_801D7EA8 = 0;
    D_801E9238 = *(&D_80076E30 + (D_801D7E9C * 4));
    func_80055E2C(D_80173320, 0x61, &D_801E9238);
    D_8012CDD0 = 0;
    func_80055E2C(D_80173320, 0x21, &D_8012CDD0);
    D_8012CDA8 = 1;
    D_801734C8 = 0;
    if (D_800775B8 == 0) {
        D_800775B8 = 1;
        func_80049638();
        temp_v0_2 = func_8004DF5C(0xF0000009, 0x20, 0x2000, 0);
        D_801E9228 = temp_v0_2;
        func_8004DF2C(temp_v0_2);
        func_800497D8();
    }
}

s32 func_80058EB8(s32 arg0) {
    switch (arg0) {
    case 0:
        D_801D7E10 = 0;
block_8:
        func_80055E2C(D_80173320, 0x60, &D_801D7E10);
        break;
    case 1:
        if ((D_8007B1A0 != arg0) && (func_80058BB8(D_801E9238) != 0)) {
            D_801D7E10 = 0;
        } else {
            D_801D7E10 = arg0;
        }
        goto block_8;
    }
    return D_801D7E10;
}

void func_80059060(s32 arg0) {
    s32 sp10;

    if (arg0 != 0) {
        if (arg0 == 1) {
            sp10 = 0;
        } else {
            goto block_4;
        }
    } else {
block_4:
        sp10 = 1;
    }
    D_8012CDD0 = arg0;
    func_80055E2C(D_80173320, 0x21, &sp10);
}

u32 func_80059170(s32 arg0, u32 arg1) {
    s32 sp10;
    s32 temp_v0;
    u32 var_s0;

    var_s0 = arg1;
    if (var_s0 > 0x7F000U) {
        var_s0 = 0x7F000;
    }
    temp_v0 = func_800591F8();
    sp10 = temp_v0;
    func_80055810(arg0, var_s0);
    sp10 = temp_v0 + var_s0;
    func_80055E2C(D_80173320, 0x2B, &sp10);
    D_8012CDA8 = 0;
    return var_s0;
}

void func_80031BD8(void) {
    u8 sp10;
    s16 var_s2;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s3;
    u8 *temp_a1;
    u8 *var_a0;
    u8 *var_s1;
    u8 *var_v1;
    u8 temp_a0;
    u8 temp_v0;

    D_80173330 = -1;
    D_80173328 = 0;
    var_s3 = 0x7FFFFFFF;
    var_s2 = 0;
    if (func_80049818(&D_80077258, &sp10) == 0) {
        func_800496B8(&D_80077260);
        D_8012CFD8 = 0;
        return;
    }
    var_s1 = &D_80173188;
    var_s0 = 0;
    do {
        var_v1 = var_s1;
        if (func_80031378(&sp10) != 0) {
            var_a0 = &sp10;
            temp_a1 = var_s1 + 0x14;
            do {
                *var_v1 = *var_a0;
                var_v1 += 1;
                var_a0 += 1;
            } while ((s32) var_v1 < (s32) temp_a1);
            *(&D_8017319C + var_s0) = 0;
            temp_v1 = func_80031B24(var_s1, (s32) temp_a1);
            var_s1 += 0x18;
            if (temp_v1 < var_s3) {
                D_80173330 = var_s2;
                var_s3 = temp_v1;
            }
            temp_v0 = *(&D_8017319A + var_s0);
            temp_a0 = *(&D_8017319B + var_s0);
            var_s0 += 0x18;
            var_s2 += 1;
            D_80173328 |= 1 << (((temp_v0 - 0x30) * 0xA) - 0x30 + temp_a0);
        }
    } while (func_80049798(&sp10) != 0);
    D_8012CFD8 = var_s2;
}

s32 func_80047210(s32 arg0, s32 arg1, s32 arg2, M2C_UNK arg3) {
    s32 sp10;
    s32 sp14;
    M2C_UNK var_a3;
    s32 temp_v0;

    var_a3 = arg3;
    sp10 = 0x800000;
    sp14 = (D_80077388 + 1) & 0x3F;
    if (sp14 == D_8007738C) {
        var_a3 = -1;
loop_2:
        temp_v0 = sp10 - 1;
        sp10 = temp_v0;
        if (temp_v0 == -1) {
            func_80046738(-1);
            return -1;
        }
        if (sp14 != D_8007738C) {
            goto block_5;
        }
        goto loop_2;
    }
block_5:
    *(&D_800782C0 + (D_80077388 * 0x10)) = arg0;
    *(&D_800782C4 + (D_80077388 * 0x10)) = arg1;
    *(&D_800782C8 + (D_80077388 * 0x10)) = arg2;
    D_80077388 = sp14;
    if (!(*D_800773A0 & 0x01000000)) {
        func_80047354(var_a3);
    }
    return (D_80077388 - D_8007738C) & 0x3F;
}
