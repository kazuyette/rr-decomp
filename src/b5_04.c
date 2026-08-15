/* b5_04.c -- batch 5, 20 functions recovered with m2c.
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

M2C_UNK AddPrim(s32, s32);
M2C_UNK func_80012B0C(s32 *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_80012E44();
M2C_UNK func_80013240();
M2C_UNK func_800163E4();
M2C_UNK func_800185F0(M2C_UNK *, s16);
M2C_UNK func_8001865C(M2C_UNK *, M2C_UNK);
M2C_UNK func_800186C8();
M2C_UNK func_80018A9C();
M2C_UNK func_800197A8(M2C_UNK);
M2C_UNK func_8001CE0C(M2C_UNK);
M2C_UNK func_8001CEA0();
M2C_UNK func_8001CFF8();
M2C_UNK func_80025BFC();
M2C_UNK func_80025C70();
M2C_UNK func_800262B0();
M2C_UNK func_800267E4(s32);
M2C_UNK func_80028578(M2C_UNK, M2C_UNK, s8 *, M2C_UNK);
M2C_UNK func_8002A498(u16);
M2C_UNK func_8002A788(s32, M2C_UNK);
M2C_UNK func_8002AF1C(u16, M2C_UNK *, M2C_UNK *);
M2C_UNK func_8002C500(M2C_UNK, M2C_UNK *);
M2C_UNK func_8002CC44(s32 *, s32 *, void *, s32);
M2C_UNK func_80030F30();
M2C_UNK func_80031044();
M2C_UNK func_800313E4(M2C_UNK *);
M2C_UNK func_80031668(M2C_UNK *);
M2C_UNK func_8003A1AC(M2C_UNK);
M2C_UNK func_8003A1D8(M2C_UNK);
M2C_UNK func_8003E128(s32, M2C_UNK, u8 *, M2C_UNK);
M2C_UNK func_8003F33C(M2C_UNK *);
M2C_UNK func_8003F4B0(u16);
M2C_UNK func_80042E08(M2C_UNK *, M2C_UNK *);
M2C_UNK func_80043228(M2C_UNK *, s32 *);
M2C_UNK func_80045750(M2C_UNK);
M2C_UNK func_8004617C(s32, M2C_UNK, M2C_UNK, s32, M2C_UNK *);
M2C_UNK func_80048198(M2C_UNK *, M2C_UNK *, void *);
M2C_UNK func_80048F80();
M2C_UNK func_80049140(M2C_UNK *);
M2C_UNK func_80049648(s32);
M2C_UNK func_800496C8(M2C_UNK *, M2C_UNK *);
M2C_UNK func_8004ACE4(s16, s16);
M2C_UNK func_80051EF0(M2C_UNK, s32, M2C_UNK);
M2C_UNK func_80052D14(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_800530A8(s8 *);
M2C_UNK func_800558FC(s32, s32);
M2C_UNK func_80055E2C(s32, M2C_UNK, u32 *);
M2C_UNK func_800576E8(s32, s32);
M2C_UNK snd_play_se(M2C_UNK, s32, u16);
extern M2C_UNK D_80010F38;
extern M2C_UNK D_800118D0;
extern M2C_UNK D_800118F4;
extern M2C_UNK D_80052820;
extern M2C_UNK D_80077128;
extern M2C_UNK D_80077250;
extern M2C_UNK D_800797E0;
extern M2C_UNK D_800797E6;
extern M2C_UNK D_800797E8;
extern M2C_UNK D_800797EA;
extern M2C_UNK D_8007C258;
extern M2C_UNK D_8007C488;
extern M2C_UNK D_8012CD38;
extern M2C_UNK D_80173158;
extern M2C_UNK D_80173188;
extern M2C_UNK D_801D7628;
extern M2C_UNK D_801E90E8;
extern M2C_UNK D_801E91F0;
extern M2C_UNK D_801E9250;
extern s16 D_80079BA0;
extern s16 D_8012CDB8;
extern s16 D_801D34F8;
extern s16 D_801D3572;
extern s16 D_801D3574;
extern s16 D_801D7E18;
extern s16 D_801D7E58;
extern s16 D_801D9060;
extern s32 D_80077144;
extern s32 D_80077148;
extern s32 D_8007745C;
extern s32 D_800774D0;
extern s32 D_800776D8;
extern s32 D_800776E8;
extern s32 D_8007C4D0;
extern s32 D_8012CD78;
extern s32 D_8012CF50;
extern s32 D_8012CF68;
extern s32 D_8012CFA0;
extern s32 D_8012CFF0;
extern s32 D_8012D010;
extern s32 D_80173320;
extern s32 D_801733C8;
extern s32 D_80173468;
extern s32 D_801D77A8;
extern s32 D_801D77F0;
extern s32 D_801D7E40;
extern s32 D_801D7EC0;
extern s32 D_801D9068;
extern s32 D_801D906C;
extern s32 D_801D9070;
extern s32 D_801D9078;
extern s32 D_801D907C;
extern s32 D_801D9080;
extern s32 D_801E9170;
extern s32 D_801E9218;
extern s8 D_8007719C;
extern s8 D_8007719E;
extern s8 D_80079B88;
extern u16 D_8007B1E8;
extern u16 D_8007C210;
extern u16 D_8007C25A;
extern u16 D_8007C2D8;
extern u16 D_8012CFF8;
extern u16 D_8012CFFA;
extern u16 D_8012CFFC;
extern u16 D_8012D0B0;
extern u16 D_8012D8D0;
extern u16 D_8012D908;
extern u16 D_80173310;
extern u16 D_801733B8;
extern u16 D_801733C0;
extern u16 D_801733D0;
extern u16 D_801D34E0;
extern u16 D_801D35AA;
extern u16 D_801D35AE;
extern u16 D_801D35C8;
extern u16 D_801D77D0;
extern u16 D_801D77D8;
extern u16 D_801D7808;
extern u8 D_80077610;
extern u8 D_80077611;
extern u8 D_80077612;
extern u8 D_80077613;
extern u8 D_80077614;
extern u8 D_80077615;
extern u8 D_80079B95;
extern void *D_800774E8;
extern void *D_8007758C;
extern void *D_8012CF98;
extern void *g_gpu_device;
s16 func_8004C27C(s16, s16);
s32 SquareRoot(s32, s32, s32, s32);
s32 func_800187A0(s32, s32);
s32 func_80019CA8(s32, s32);
s32 func_80029278(s32, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32);
s32 func_800297D8(s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_80031840(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK *, s32);
s32 func_800459C0(M2C_UNK *, s32);
s32 func_8004788C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_80049698(M2C_UNK *, M2C_UNK *);
s32 func_800497B8(s32, M2C_UNK *, M2C_UNK);
s32 func_800497C8(s32);
s32 func_800497E8(M2C_UNK *, M2C_UNK);
s32 func_80050DF8(s16, s16, s16);
s32 rcos(s32);
s32 rsin(s32);

void st_title_main(void) {
    s32 temp_a1;
    s32 var_v0;

    func_8001CE0C(0);
    func_800262B0();
    func_800267E4(D_8012CD78);
    if (D_80173310 == 2) {
        func_80045750(1);
    }
    if (D_801D77D0 == 0) {
        D_801D77A8 += 1;
        D_8007B1E8 += 1;
        D_80173310 += 1;
        temp_a1 = D_8012D010 + 1;
        D_8012D010 = temp_a1;
        if (D_801D35AA != 0) {
            D_8012D010 = 0;
        }
        if (D_8012D010 >= 0x1FF) {
            D_801D34F8 = 8;
        }
        if (D_801D35AE & 0x860) {
            snd_play_se(0x2D, temp_a1, D_801D35AA);
            D_801D34F8 = 6;
            func_8001CEA0();
            func_80031044();
        }
        if (D_801D35AE & 0x8000) {
            var_v0 = D_80077144 - 1;
            if (D_80077144 > 0) {
                goto block_14;
            }
        } else if (D_801D35AE & 0x2000) {
            var_v0 = D_80077144 + 1;
            if (D_80077144 < (D_80077148 - 1)) {
block_14:
                D_80077144 = var_v0;
            }
        }
        func_80030F30();
    }
    func_800197A8(0);
    func_8001CFF8();
}

void func_8001DD6C(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    M2C_UNK sp20;
    M2C_UNK sp40;
    s32 sp60;
    s32 sp64;
    s32 sp68;

    D_801D9070 = 0;
    D_801D906C = 0;
    D_801D9068 = 0;
    D_801D9080 = 0;
    D_801D907C = 0;
    D_801D9078 = 0;
    D_801D9070 = -0x300;
    func_800186C8();
    func_800185F0(&sp20, D_801D7E18);
    func_8001865C(&sp40, 0x80);
    func_80042E08(&sp40, &sp20);
    func_80042E08(&D_801E91F0, &sp20);
    sp18 = 0x4000;
    sp14 = 0x4000;
    sp10 = 0x4000;
    func_80043228(&sp40, &sp10);
    func_80042E08(&sp40, &sp20);
    sp60 = 0;
    sp64 = 0;
    sp68 = 0;
    func_80012B0C(&sp60, &sp20, 0xCA, 0);
    if (((s32) (arg0 - 1) / 2) & 1) {
        func_80012B0C(&sp60, &sp20, 0xCB, 0);
    }
}

void func_800204C8(s32 arg0, s32 arg1) {
    s32 var_a0;

    var_a0 = arg0;
    if (var_a0 > 0) {
        if (arg1 < var_a0) {
            var_a0 = arg1;
        }
        D_8007719C = var_a0 + 0x30;
        D_8007719E = arg1 + 0x30;
        func_80028578(0xF0, 8, &D_8007719C - 4, 0x64);
    }
}

void func_80026CA8(void *arg0) {
    s32 sp10;
    s32 sp18;
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v0;

    temp_s0 = rsin(M2C_FIELD(arg0, s32 *, 0xA8));
    var_a0 = temp_s0 * M2C_FIELD(arg0, s32 *, 0xA0);
    temp_v1 = rsin(M2C_FIELD(arg0, s32 *, 0x24));
    if (var_a0 < 0) {
        var_a0 += 3;
    }
    sp10 = (var_a0 >> 2) + (temp_v1 * M2C_FIELD(arg0, s32 *, 0xA4));
    temp_s0_2 = rcos(M2C_FIELD(arg0, s32 *, 0xA8));
    var_a0_2 = temp_s0_2 * M2C_FIELD(arg0, s32 *, 0xA0);
    temp_v1_2 = rcos(M2C_FIELD(arg0, s32 *, 0x24));
    if (var_a0_2 < 0) {
        var_a0_2 += 3;
    }
    sp18 = (var_a0_2 >> 2) + (temp_v1_2 * M2C_FIELD(arg0, s32 *, 0xA4));
    temp_s2 = rsin(M2C_FIELD(arg0, s32 *, 0xA8));
    temp_s1 = rsin(M2C_FIELD(arg0, s32 *, 0x24));
    temp_s0_3 = rcos(M2C_FIELD(arg0, s32 *, 0xA8));
    temp_lo = temp_s2 * temp_s1;
    temp_lo_2 = temp_s0_3 * rcos(M2C_FIELD(arg0, s32 *, 0x24));
    temp_v1_3 = M2C_FIELD(arg0, s32 *, 0xA0);
    temp_v0 = M2C_FIELD(arg0, s32 *, 0xA4);
    var_v0 = temp_lo + temp_lo_2;
    temp_a1 = (temp_v1_3 * temp_v1_3) + (temp_v0 * temp_v0);
    if (var_v0 < 0) {
        var_v0 += 0xFFF;
    }
    M2C_FIELD(arg0, s32 *, 0xA0) = (s32) (SquareRoot(temp_a1 + ((s32) (temp_v0 * 2 * temp_v1_3 * (var_v0 >> 0xC)) / 4096), temp_a1, temp_lo_2, temp_lo) >> 6);
    M2C_FIELD(arg0, s32 *, 0xA8) = (s32) (0x400 - func_800187A0(sp10, sp18));
}

void func_80028294(void *arg0) {
    s32 sp18;
    s32 temp_a0;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    s32 var_v1_2;

    M2C_FIELD(arg0, s32 *, 0x24) = (s32) ((func_80019CA8(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(arg0, s32 *, 0xAC)) / 5) + M2C_FIELD(arg0, s32 *, 0x24));
    func_80026CA8(arg0);
    temp_s1 = rsin(M2C_FIELD(arg0, s32 *, 0x24));
    temp_s2 = rcos(M2C_FIELD(arg0, s32 *, 0x24));
    var_v0 = rsin(M2C_FIELD(arg0, s32 *, 0xA8)) * M2C_FIELD(arg0, s32 *, 0xA0);
    if (var_v0 < 0) {
        var_v0 += 0xFF;
    }
    M2C_FIELD(arg0, s32 *, 0x60) = (s32) (var_v0 >> 8);
    var_v1 = rcos(M2C_FIELD(arg0, s32 *, 0xA8)) * M2C_FIELD(arg0, s32 *, 0xA0);
    if (var_v1 < 0) {
        var_v1 += 0xFF;
    }
    M2C_FIELD(arg0, s32 *, 0x68) = (s32) (var_v1 >> 8);
    temp_v0 = (s32) ((temp_s1 * M2C_FIELD(arg0, s32 *, 0x60)) + (temp_s2 * M2C_FIELD(arg0, s32 *, 0x68))) / 4096;
    var_v1_2 = temp_s1 * temp_v0;
    sp18 = temp_v0;
    if (var_v1_2 < 0) {
        var_v1_2 += 0xFFF;
    }
    M2C_FIELD(arg0, s32 *, 0x60) = (s32) ((s32) (var_v1_2 >> 0xC) / 4);
    var_v0_2 = (s32) (temp_s2 * sp18) / 4096;
    if (var_v0_2 < 0) {
        var_v0_2 += 3;
    }
    temp_a0 = D_8012CFF0;
    M2C_FIELD(arg0, s32 *, 0x68) = (s32) (var_v0_2 >> 2);
    if (temp_a0 >= 0xB) {
        temp_v0_2 = temp_a0 - M2C_FIELD(arg0, s16 *, 0xCA);
        D_8012CFF0 = temp_v0_2;
        temp_s1_2 = M2C_FIELD(arg0, s16 *, 0xC8) + 8;
        temp_v0_3 = temp_v0_2 - temp_s1_2;
        D_8012CFF0 = temp_v0_3;
        if (temp_v0_3 <= 0) {
            M2C_FIELD(arg0, s32 *, 0xB4) = 0;
        }
        D_801D7EC0 = (s32) ((func_800497C8(temp_a0) & 3) * temp_s1_2) / 256;
    } else {
        M2C_FIELD(arg0, s32 *, 0xB4) = 0;
        D_801D7EC0 = 0;
    }
    if (D_801D9060 == 2) {
        D_801D3572 = (s16) ((s32) ((0x60 - ((D_8012CFF0 & 0x1F) * 2)) * M2C_FIELD((arg0 + 0x58), s16 *, 0x70)) / 256);
        D_801D3574 = 0x1A80;
    }
}

void func_8002AB88(void) {
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_s6;

    temp_s2 = D_8012CF68 + 0xB68;
    temp_s1 = ((s16) D_801D7E58 % 10) * 0x10;
    temp_s6 = func_80029278(temp_s2, func_80029278(temp_s2, *(s32 *)0x1F800000, 0xD0, 0x18, 0x10, 0x10, ((s16) D_801D7E58 / 10) * 0x10, 0xB0, 0x80), 0xE0, 0x18, 0x10, 0x10, temp_s1, 0xB0, 0x80);
    func_8004617C(temp_s6, 0, 1, func_8004788C(0, 0, 0x140, 0) & 0xFFFF, &D_80077128);
    AddPrim(temp_s2, temp_s6);
    *(s32 *)0x1F800000 = temp_s6 + 0xC;
}

void func_8002B6F4(void) {
    M2C_UNK var_a0;
    s32 var_a0_2;

    if (D_801D77D0 == 0) {
        D_80173310 += 1;
        D_8007B1E8 += 1;
        if ((D_80173310 - 1) == 2) {
            func_80045750(1);
        }
        if ((D_80173310 == (D_801D77F0 - 0x78)) && (D_8012CF50 == 0)) {
            func_8003A1AC(-1);
        }
        if ((D_80173310 == (D_801D77F0 - 0x1E)) && (D_8012CF50 == 0)) {
            func_8003A1D8(0xC);
            D_80173468 = 1;
        }
        if (((s32) D_80173310 >= D_801D77F0) || ((D_8012CF50 == 0) && (D_801D35AE & 0x860))) {
            if (D_8012CF50 != 0) {
                D_801D34F8 = 0x25;
                D_801D77F0 = D_801E9218;
            } else {
                D_8012CDB8 = 0x80;
                D_801D34F8 = 0xD;
            }
            if (D_80173468 == 0) {
                func_8003A1D8(0xC);
            }
        }
    }
    func_8002AF1C(D_80173310, &D_8007C258, &D_801E9250);
    if ((D_80173310 == 0) || (var_a0 = 1, (((u16) D_80173310 < 0x4BU) == 0))) {
        var_a0 = 0;
    }
    func_8002C500(var_a0, &D_8007C258);
    func_80012E44();
    func_800163E4();
    func_80013240();
    func_80025C70();
    func_80018A9C();
    func_8002A498(D_80173310);
    if ((D_8012CF50 != 0) && ((D_801D77F0 - 0x5A) < (s32) D_80173310)) {
        var_a0_2 = ((D_80173310 + 0x5A) - D_801D77F0) * 3;
        if (var_a0_2 >= 0x141) {
            var_a0_2 = 0x140;
        }
        func_8002A788(var_a0_2, 2);
    }
}

void func_800310C8(u8 *arg0, M2C_UNK arg1) {
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s4;
    s32 temp_s6;
    s32 temp_s7;
    s32 var_s3;
    u8 *var_v1;

    var_s3 = 0;
    temp_s7 = D_8012CF68 + 0xB68;
    if (*arg0 != 0) {
        var_v1 = arg0;
        do {
            var_v1 += 1;
            var_s3 += 1;
        } while (*var_v1 != 0);
    }
    temp_s3 = var_s3 + 2;
    temp_s1 = temp_s3 * 8;
    func_8003E128(0xB0 - temp_s1, 0x70, arg0, arg1);
    temp_s3_2 = temp_s3 * 0x10;
    temp_s4 = 0x18 * 2;
    temp_s2 = 0xA0 - temp_s1;
    temp_s1_2 = 0x78 - 0x18;
    temp_s6 = func_800297D8(temp_s7, func_800297D8(temp_s7, *(s32 *)0x1F800000, temp_s2, temp_s1_2, temp_s3_2, temp_s4, 0xFF, 0xFF, 0xFF), temp_s2, temp_s1_2, temp_s3_2, temp_s4, 0xFF, 0xFF, 0xFF);
    func_8004617C(temp_s6, 0, 1, func_8004788C(0, 2, 0x140, 0) & 0xFFFF, &D_80077128);
    AddPrim(temp_s7, temp_s6);
    *(s32 *)0x1F800000 = temp_s6 + 0xC;
}

void func_800314BC(void *arg0) {
    M2C_UNK *var_a3;
    s32 *var_a1;
    s32 *var_a1_2;
    s32 *var_a3_2;
    s32 *var_v1;
    s32 *var_v1_2;
    s32 temp_t2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_t3;
    void *var_t0;
    void *var_t0_2;

    var_t0 = arg0;
    var_a3 = &D_8007C488;
    var_a2 = 0;
    do {
        M2C_FIELD(var_t0, s32 *, 0) = (s32) M2C_FIELD(var_a3, s32 *, 0);
        M2C_FIELD(var_t0, s32 *, 4) = (s32) M2C_FIELD(var_a3, s32 *, 4);
        M2C_FIELD(var_t0, s32 *, 8) = (s32) M2C_FIELD(var_a3, s32 *, 8);
        var_t0 += 0xC;
        var_a2 += 3;
        var_a3 += 0xC;
    } while (var_a2 < 0x12);
    var_t3 = 0;
    var_t0_2 = arg0;
    do {
        temp_t2 = var_t3 << 5;
        var_a2_2 = 0;
        var_a3_2 = var_t0_2 + 0x48;
loop_4:
        var_a0 = 0;
        var_a1 = var_a3_2;
        var_v1 = var_a2_2 + (temp_t2 + &D_8012CD38);
loop_5:
        temp_v0 = *var_v1;
        var_v1 += 4;
        var_a0 += 1;
        *var_a1 = temp_v0;
        var_a1 += 4;
        if (var_a0 < 4) {
            goto loop_5;
        }
        var_a0_2 = 0;
        var_a1_2 = var_a2_2 + (var_t0_2 + 0x88);
        var_v1_2 = var_a2_2 + (temp_t2 + &D_801D7628);
loop_7:
        temp_v0_2 = *var_v1_2;
        var_v1_2 += 4;
        var_a0_2 += 1;
        *var_a1_2 = temp_v0_2;
        var_a1_2 += 4;
        if (var_a0_2 < 4) {
            goto loop_7;
        }
        var_a2_2 += 0x10;
        var_a3_2 += 0x10;
        if (var_a2_2 < 0x20) {
            goto loop_4;
        }
        var_t3 += 1;
        var_t0_2 += 0x20;
    } while (var_t3 < 2);
    M2C_FIELD(arg0, u16 *, 0xC8) = (u16) D_801733C0;
    M2C_FIELD(arg0, u16 *, 0xCA) = (u16) D_8012D908;
    M2C_FIELD(arg0, u16 *, 0xCC) = (u16) D_8012D8D0;
    M2C_FIELD(arg0, u16 *, 0xCE) = (u16) D_801D7808;
    M2C_FIELD(arg0, u16 *, 0xD0) = (u16) D_8012CFF8;
    M2C_FIELD(arg0, u16 *, 0xD2) = (u16) D_8012CFFA;
    M2C_FIELD(arg0, u16 *, 0xDA) = (u16) D_801733B8;
    M2C_FIELD(arg0, u16 *, 0xDC) = (u16) D_8007C210;
    M2C_FIELD(arg0, u16 *, 0xD6) = (u16) D_8012D0B0;
    M2C_FIELD(arg0, u16 *, 0xD8) = (u16) D_801733D0;
    M2C_FIELD(arg0, u16 *, 0xD4) = (u16) D_8012CFFC;
    M2C_FIELD(arg0, u16 *, 0xDE) = (u16) D_8007C2D8;
    M2C_FIELD(arg0, u16 *, 0xE2) = (u16) D_801D34E0;
    M2C_FIELD(arg0, u16 *, 0xE6) = (u16) D_801D77D8;
    M2C_FIELD(arg0, u16 *, 0xE4) = (u16) D_801D35C8;
    M2C_FIELD(arg0, u16 *, 0xE0) = (u16) D_8007C25A;
}

s32 func_800319D4(void) {
    M2C_UNK sp18;
    M2C_UNK sp40;
    M2C_UNK sp140;
    M2C_UNK sp240;

    func_800313E4(&sp18);
    func_80048198(&sp240, &D_80077250, (D_8007C4D0 * 0x18) + &D_80173158);
    if (func_80049698(&sp240, &sp18) != 0) {
        return func_80031840(&sp18, &sp40, 0x100, &sp140, 0x100);
    }
    return 0;
}

s32 func_80031A64(s32 arg0) {
    M2C_UNK sp10;
    M2C_UNK sp38;
    M2C_UNK sp138;
    s32 temp_v0;
    s32 temp_v0_2;

    func_80048198(&sp10, &D_80077250, (arg0 * 0x18) + &D_80173188);
    temp_v0 = func_800497E8(&sp10, 1);
    if (temp_v0 >= 0) {
        temp_v0_2 = func_800497B8(temp_v0, &sp38, 0x100);
        if ((temp_v0_2 == 0x100) && (func_800497B8(temp_v0, &sp138, 0x100) == temp_v0_2)) {
            func_80049648(temp_v0);
            func_80031668(&sp138);
            return 1;
        }
        
        return 0;
    }
    return 0;
}

void func_8003F5A8(void) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a0_6;
    s32 temp_a0_7;
    s32 temp_a3;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_lo_4;
    s32 temp_lo_5;
    s32 temp_lo_6;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v1;
    u16 temp_v1_2;

    if (D_801D77D0 == 0) {
        D_80173310 += 1;
        D_8007B1E8 += 1;
        if (D_80173310 == 8) {
            func_80045750(1);
        }
        func_8003F33C(&D_801E9250);
        temp_lo = (s32) (D_801733C8 * 0x4F6) / 1280;
        D_801733C8 = temp_lo;
        if (temp_lo < 0x801) {
            temp_v1 = M2C_FIELD(D_8012CF98, s32 *, 0x44);
            temp_a0 = M2C_FIELD(D_8012CF98, s32 *, 0x44);
            D_8012CF98 += 0x44;
            D_801733C8 = temp_v1 << 8;
            if (temp_a0 < 0) {
                D_8012CDB8 = 0x80;
                D_801D34F8 = 0xD;
            }
        }
        temp_v1_2 = D_80173310;
        if (temp_v1_2 == 0x654) {
            func_8003A1AC(-1);
        }
        if (temp_v1_2 == 0x6EA) {
            func_8003A1D8(0xC);
            D_8012CFA0 = 1;
        }
    }
    var_a3 = D_801733C8;
    if (var_a3 < 0) {
        var_a3 += 3;
    }
    temp_a3 = var_a3 >> 2;
    temp_a0_2 = M2C_FIELD(D_8012CF98, s32 *, 0);
    temp_lo_2 = (s32) ((temp_a3 * M2C_FIELD(D_8012CF98, s32 *, 4)) + (((temp_a0_2 << 6) - temp_a3) * M2C_FIELD(D_8012CF98, s32 *, 0x14))) / temp_a0_2;
    var_v0 = temp_lo_2 >> 6;
    if (temp_lo_2 < 0) {
        var_v0 = (s32) (temp_lo_2 + 0x3F) >> 6;
    }
    sp10 = var_v0;
    temp_a0_3 = M2C_FIELD(D_8012CF98, s32 *, 0);
    temp_lo_3 = (s32) ((temp_a3 * M2C_FIELD(D_8012CF98, s32 *, 8)) + (((temp_a0_3 << 6) - temp_a3) * M2C_FIELD(D_8012CF98, s32 *, 0x18))) / temp_a0_3;
    var_v0_2 = temp_lo_3 >> 6;
    if (temp_lo_3 < 0) {
        var_v0_2 = (s32) (temp_lo_3 + 0x3F) >> 6;
    }
    sp14 = var_v0_2;
    temp_a0_4 = M2C_FIELD(D_8012CF98, s32 *, 0);
    temp_lo_4 = (s32) ((temp_a3 * M2C_FIELD(D_8012CF98, s32 *, 0xC)) + (((temp_a0_4 << 6) - temp_a3) * M2C_FIELD(D_8012CF98, s32 *, 0x1C))) / temp_a0_4;
    var_v0_3 = temp_lo_4 >> 6;
    if (temp_lo_4 < 0) {
        var_v0_3 = (s32) (temp_lo_4 + 0x3F) >> 6;
    }
    sp18 = var_v0_3;
    temp_a0_5 = M2C_FIELD(D_8012CF98, s32 *, 0);
    temp_lo_5 = (s32) ((temp_a3 * M2C_FIELD(D_8012CF98, s32 *, 0x24)) + (((temp_a0_5 << 6) - temp_a3) * M2C_FIELD(D_8012CF98, s32 *, 0x34))) / temp_a0_5;
    var_v0_4 = temp_lo_5 >> 6;
    if (temp_lo_5 < 0) {
        var_v0_4 = (s32) (temp_lo_5 + 0x3F) >> 6;
    }
    sp20 = var_v0_4;
    temp_a0_6 = M2C_FIELD(D_8012CF98, s32 *, 0);
    temp_lo_6 = (s32) ((temp_a3 * M2C_FIELD(D_8012CF98, s32 *, 0x28)) + (((temp_a0_6 << 6) - temp_a3) * M2C_FIELD(D_8012CF98, s32 *, 0x38))) / temp_a0_6;
    var_v0_5 = temp_lo_6 >> 6;
    if (temp_lo_6 < 0) {
        var_v0_5 = (s32) (temp_lo_6 + 0x3F) >> 6;
    }
    sp24 = var_v0_5;
    temp_a0_7 = M2C_FIELD(D_8012CF98, s32 *, 0);
    var_v1 = (s32) ((temp_a3 * M2C_FIELD(D_8012CF98, s32 *, 0x2C)) + (((temp_a0_7 << 6) - temp_a3) * M2C_FIELD(D_8012CF98, s32 *, 0x3C))) / temp_a0_7;
    if (var_v1 < 0) {
        var_v1 += 0x3F;
    }
    sp28 = var_v1 >> 6;
    func_8002CC44(&sp10, &sp20, D_8012CF98, temp_a3);
    if ((u16) D_80173310 >= 0x6AFU) {
        var_a0 = (D_80173310 - 0x6AE) * 3;
        if (var_a0 >= 0x141) {
            var_a0 = 0x140;
        }
        func_8002A788(var_a0, 2);
    }
    func_8003F4B0(D_80173310);
    func_80012E44();
    func_800163E4();
    func_80013240();
    func_80025BFC();
    func_80018A9C();
}

void func_80045790(void) {
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(), 0x3C)();
}

s32 func_800458B8(s32 arg0, M2C_UNK arg1) {
    s32 temp_s0;

    temp_s0 = func_800459C0(&D_80010F38, arg0);
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(s32, s32, M2C_UNK, M2C_UNK), 8)(M2C_FIELD(g_gpu_device, s32 *, 0x1C), arg0, 8, arg1);
    return temp_s0;
}

s32 func_8004C8AC(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg5, s32 arg6) {
    s16 temp_a0;
    s16 temp_a1;
    s32 temp_s0;

    if ((u32) (arg0 & 0xFFFF) < 0x18U) {
        temp_s0 = arg0 * 0x18;
        temp_a0 = *(&D_800797EA + temp_s0);
        if (temp_a0 == arg1) {
            temp_a1 = *(&D_800797E6 + temp_s0);
            if (temp_a1 == arg2) {
                if (*(&D_800797E0 + temp_s0) == arg3) {
                    func_8004ACE4(temp_a0, temp_a1);
                    D_80079B88 = 0x20;
                    D_80079BA0 = arg0;
                    D_80079B95 = *(&D_800797E8 + temp_s0);
                    M2C_FIELD(((arg0 * 0x10) + D_8007745C), s16 *, 4) = func_8004C27C((s16) arg5, (s16) arg6);
                    return 0;
                }
                goto block_5;
            }
        }
        
        return -1;
    }
block_5:
    return -1;
}

void func_8004FBEC(s16 arg0, s16 arg1, s8 arg2) {
    s16 temp_a3;
    s32 *temp_s1;
    s32 *temp_s1_2;
    s32 *temp_s1_3;
    s32 temp_s0;
    s32 temp_s0_3;
    s32 temp_s0_4;
    void *temp_s0_2;
    void *temp_v0;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;

    temp_a3 = arg2 & 0xFF;
    switch (temp_a3) {
    case 20:
        temp_s1 = (arg0 * 4) + &D_801E90E8;
        temp_s0 = arg1 * 0xA8;
        M2C_FIELD((temp_s0 + *temp_s1), s8 *, 0x16) = arg2;
        M2C_FIELD((temp_s0 + *temp_s1), s8 *, 0x27) = 1;
        M2C_FIELD((temp_s0 + *temp_s1), s32 *, 0x88) = func_80050DF8(arg0, arg1, temp_a3);
        temp_s0_2 = temp_s0 + *temp_s1;
        M2C_FIELD(temp_s0_2, s32 *, 0xC) = (s32) M2C_FIELD(temp_s0_2, s32 *, 4);
        return;
    case 30:
        temp_s1_2 = (arg0 * 4) + &D_801E90E8;
        temp_s0_3 = arg1 * 0xA8;
        M2C_FIELD((temp_s0_3 + *temp_s1_2), s8 *, 0x16) = arg2;
        temp_v1 = temp_s0_3 + *temp_s1_2;
        if ((u8) M2C_FIELD(temp_v1, u8 *, 0x28) < 0x7FU) {
            M2C_FIELD(temp_v1, u8 *, 0x28) = (u8) (M2C_FIELD(temp_v1, u8 *, 0x28) - 1);
            M2C_FIELD((temp_s0_3 + *temp_s1_2), s32 *, 0x88) = func_80050DF8(arg0, arg1, arg0);
            temp_v1_2 = temp_s0_3 + *temp_s1_2;
            if (M2C_FIELD(temp_v1_2, u8 *, 0x28) != 0) {
                M2C_FIELD(temp_v1_2, s32 *, 4) = (s32) M2C_FIELD(temp_v1_2, s32 *, 0xC);
                return;
            }
            M2C_FIELD(temp_v1_2, s8 *, 0x10) = 0;
            return;
        }
        M2C_FIELD((temp_s0_3 + *temp_s1_2), s32 *, 0x88) = func_80050DF8(arg0, arg1, arg0);
        M2C_FIELD((temp_s0_3 + *temp_s1_2), s32 *, 0x88) = 0;
        temp_v0 = temp_s0_3 + *temp_s1_2;
        M2C_FIELD(temp_v0, s32 *, 4) = (s32) M2C_FIELD(temp_v0, s32 *, 0xC);
        return;
    default:
        temp_s1_3 = (arg0 * 4) + &D_801E90E8;
        temp_s0_4 = arg1 * 0xA8;
        M2C_FIELD((temp_s0_4 + *temp_s1_3), s8 *, 0x16) = arg2;
        temp_v1_3 = temp_s0_4 + *temp_s1_3;
        M2C_FIELD(temp_v1_3, u8 *, 0x2A) = (u8) (M2C_FIELD(temp_v1_3, u8 *, 0x2A) + 1);
        M2C_FIELD((temp_s0_4 + *temp_s1_3), s32 *, 0x88) = func_80050DF8(arg0, arg1, temp_a3);
        return;
    }
}

void func_80052854(void) {
    s8 sp10;
    s8 sp11;
    s8 sp12;
    s8 sp13;

    D_80077611 = 0;
    D_80077610 = D_80077611;
    D_80077615 = 0;
    D_80077614 = D_80077615;
    D_80077613 = 1;
    D_801E9170 = 0;
    D_801D7E40 = 0;
    D_80077612 = D_80077613;
    D_800774D0 = 0;
    func_80048F80();
    func_80049140(&D_80052820);
    func_80052D14(0xA, 0, 0, 0);
    M2C_FIELD(D_800774E8, s16 *, 0x1AA) = 0xC001;
    M2C_FIELD(D_800774E8, s16 *, 0x184) = 0;
    M2C_FIELD(D_800774E8, s16 *, 0x186) = 0;
    if ((M2C_FIELD(D_800774E8, u16 *, 0x1B8) == 0) && (M2C_FIELD(D_800774E8, u16 *, 0x1BA) == 0)) {
        M2C_FIELD(D_800774E8, s16 *, 0x180) = 0x3FFF;
        M2C_FIELD(D_800774E8, s16 *, 0x182) = 0x3FFF;
    }
    M2C_FIELD(D_800774E8, s16 *, 0x1B0) = 0x7FFF;
    M2C_FIELD(D_800774E8, s16 *, 0x1B2) = 0x7FFF;
    sp12 = 0x80;
    sp10 = 0x80;
    sp13 = 0;
    sp11 = 0;
    func_800530A8(&sp10);
}

void func_800536B0(s32 arg0) {
    func_80051EF0(0x15, arg0, 0);
}

s32 func_80055810(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;

    D_800776D8 = 0;
    M2C_FIELD(D_8007758C, u16 *, 0x1AA) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 0xFFCF);
    temp_v0 = M2C_FIELD(D_8007758C, u16 *, 0x1AE) & 0x7FF & 0xFFFF;
    if ((M2C_FIELD(D_8007758C, u16 *, 0x1AE) & 0x7FF) != temp_v0) {
loop_1:
        temp_v0_2 = D_800776D8 + 1;
        D_800776D8 = temp_v0_2;
        if (temp_v0_2 < 0x1389) {
            if ((M2C_FIELD(D_8007758C, u16 *, 0x1AE) & 0x7FF) != temp_v0) {
                goto loop_1;
            }
        } else {
            func_800496C8(&D_800118D0, &D_800118F4);
        }
    }
    if (D_800776E8 == 1) {
        func_800576E8(arg0, arg1);
        return arg1;
    }
    func_800558FC(arg0, arg1);
    return arg1;
}

u32 func_800590B4(u32 arg0) {
    if ((arg0 > 0x7F000U) || (arg0 < 0x1000U)) {
        return 0U;
    }
    if (arg0 & 7) {
        arg0 = (arg0 + 8) & ~4;
    }
    func_80055E2C(D_80173320, 0x2B, &arg0);
    return arg0;
}
