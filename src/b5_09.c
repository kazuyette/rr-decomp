/* b5_09.c -- batch 5, 5 functions recovered with m2c.
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

M2C_UNK func_80012E44();
M2C_UNK func_80013240();
M2C_UNK func_800163E4();
M2C_UNK func_80018A9C();
M2C_UNK func_8001CD90();
M2C_UNK func_8001CDA8();
M2C_UNK func_8001CE0C(M2C_UNK);
M2C_UNK func_8001CEA0();
M2C_UNK func_80025BFC();
M2C_UNK func_80025C98();
M2C_UNK func_80028578(M2C_UNK, s32, s32, M2C_UNK);
M2C_UNK func_8002C500(s32, void *);
M2C_UNK func_8002E6A8(s16, s16, u16, u16);
M2C_UNK func_8003A1AC(M2C_UNK);
M2C_UNK func_8003A1D8(s32);
M2C_UNK func_8003A640();
M2C_UNK func_8003C84C();
M2C_UNK func_80045750(M2C_UNK);
M2C_UNK snd_play_se(M2C_UNK);
extern M2C_UNK D_80077360;
extern M2C_UNK D_8007C488;
extern M2C_UNK D_801D7628;
extern M2C_UNK D_801E9250;
extern s16 D_8012CDB8;
extern s16 D_801D34F8;
extern s32 D_800757B0;
extern s32 D_8012CD30;
extern s32 D_8012CD38;
extern s32 D_8012CF50;
extern s32 D_8012D0B8;
extern s32 D_8012D8F0;
extern s32 D_801732F8;
extern s32 D_80173478;
extern s32 D_801D7610;
extern s32 D_801D7618;
extern s32 D_801D77A0;
extern s32 D_801D7E80;
extern u16 D_8007B1E8;
extern u16 D_8007C210;
extern u16 D_8007C25A;
extern u16 D_8007C2D8;
extern u16 D_8012CFF8;
extern u16 D_8012CFFA;
extern u16 D_8012CFFC;
extern u16 D_8012D008;
extern u16 D_8012D0B0;
extern u16 D_8012D8D0;
extern u16 D_8012D908;
extern u16 D_80173310;
extern u16 D_801733B8;
extern u16 D_801733C0;
extern u16 D_801733D0;
extern u16 D_801D34E0;
extern u16 D_801D35AE;
extern u16 D_801D35C8;
extern u16 D_801D77D0;
extern u16 D_801D77D8;
extern u16 D_801D7808;
extern u16 D_801D7E70;
s32 func_8003A198();
s32 func_8003CAB0(M2C_UNK, s32);
s32 func_800497C8();
s32 rcos(s16);
s32 rsin(s16, void *, s32);

void func_80031668(void *arg0) {
    M2C_UNK *var_t0;
    s32 *var_a1;
    s32 *var_a1_2;
    s32 *var_a3_2;
    s32 *var_t2;
    s32 *var_v1;
    s32 *var_v1_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_t1;
    u16 temp_a0;
    u16 temp_a1;
    u16 temp_a2;
    u16 temp_a3;
    void *var_a3;
    void *var_t0_2;

    var_t0 = &D_8007C488;
    var_a3 = arg0;
    var_a2 = 0;
    do {
        M2C_FIELD(var_t0, s32 *, 0) = (s32) M2C_FIELD(var_a3, s32 *, 0);
        M2C_FIELD(var_t0, s32 *, 4) = (s32) M2C_FIELD(var_a3, s32 *, 4);
        M2C_FIELD(var_t0, s32 *, 8) = (s32) M2C_FIELD(var_a3, s32 *, 8);
        var_t0 += 0xC;
        var_a2 += 3;
        var_a3 += 0xC;
    } while (var_a2 < 0x12);
    var_t1 = 0;
    var_t0_2 = arg0;
    var_t2 = &D_8012CD38;
    do {
        var_a2_2 = 0;
        var_a3_2 = var_t2;
loop_4:
        var_a0 = 0;
        var_a1 = var_a3_2;
        var_v1 = var_a2_2 + (var_t0_2 + 0x48);
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
        var_a1_2 = var_a2_2 + ((var_t1 << 5) + &D_801D7628);
        var_v1_2 = var_a2_2 + (var_t0_2 + 0x88);
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
        var_t0_2 += 0x20;
        var_t1 += 1;
        var_t2 += 0x20;
    } while (var_t1 < 2);
    temp_a0 = M2C_FIELD(arg0, u16 *, 0xCA);
    temp_a1 = M2C_FIELD(arg0, u16 *, 0xCC);
    D_8012CFF8 = M2C_FIELD(arg0, u16 *, 0xD0);
    D_8012CFFA = M2C_FIELD(arg0, u16 *, 0xD2);
    D_8012CFFC = M2C_FIELD(arg0, u16 *, 0xD4);
    temp_a3 = M2C_FIELD(arg0, u16 *, 0xD6);
    D_801733C0 = M2C_FIELD(arg0, u16 *, 0xC8);
    D_8012D908 = temp_a0;
    D_8012D8D0 = temp_a1;
    D_801D7808 = M2C_FIELD(arg0, u16 *, 0xCE);
    D_8007C2D8 = M2C_FIELD(arg0, u16 *, 0xDE);
    D_8007C25A = M2C_FIELD(arg0, u16 *, 0xE0);
    temp_a2 = M2C_FIELD(arg0, u16 *, 0xE6);
    D_8012D0B0 = temp_a3;
    D_801733D0 = M2C_FIELD(arg0, u16 *, 0xD8);
    D_801733B8 = M2C_FIELD(arg0, u16 *, 0xDA);
    D_8007C210 = M2C_FIELD(arg0, u16 *, 0xDC);
    D_801D34E0 = M2C_FIELD(arg0, u16 *, 0xE2);
    D_801D35C8 = M2C_FIELD(arg0, u16 *, 0xE4);
    D_801D77D8 = temp_a2;
    func_8002E6A8((s16) temp_a0, (s16) temp_a1, temp_a2, temp_a3);
}

void func_8003CBD8(void) {
    s32 sp10;
    s32 temp_v0;
    s32 temp_v0_2;

    if (D_8012D0B8 > 0) {
        temp_v0 = D_8012D0B8 - 1;
        D_8012D0B8 = temp_v0;
        if (temp_v0 == 0) {
            if (D_8012D8F0 != 0) {
                func_8003A1D8(D_8012D8F0);
                D_8012D0B8 = 0x3C;
                D_8012D8F0 = 0;
            } else {
                func_8003A640();
                func_8003A1AC(0x80);
            }
        }
    } else {
        temp_v0_2 = func_8003A198();
        sp10 = temp_v0_2;
        if (temp_v0_2 == 0) {
            D_801D7610 += 1;
            D_801D7610 = (s32) (D_801D7610 + 6) % 6;
            func_8003A1D8(D_801D7610 + 2);
            D_8012D0B8 = 0x3C;
        }
    }
    if (D_801D77D0 == 0) {
        D_8007B1E8 += 1;
        D_80173310 += 1;
        if (D_80173310 == 2) {
            func_80045750(1);
        }
        if ((D_801D35AE & 0x8000 & 0xFFFF) && (D_801D77A0 > 0)) {
            D_801D77A0 -= 1;
        }
        if ((D_801D35AE & 0x2000 & 0xFFFF) && (D_801D77A0 < 2)) {
            D_801D77A0 += 1;
        }
        if (D_801D35AE & 0x860 & 0xFFFF) {
            switch (D_801D77A0) {
            case 0:
                D_801D7610 -= 1;
                D_801D7610 = (s32) (D_801D7610 + 6) % 6;
                if (D_8012D0B8 == 0) {
                    func_8003A1D8(D_801D7610 + 2);
                    D_8012D0B8 = 0x3C;
                } else {
                    D_8012D8F0 = D_801D7610 + 2;
                }
                break;
            case 2:
                D_801D7610 += 1;
                D_801D7610 = (s32) (D_801D7610 + 6) % 6;
                if (D_8012D0B8 == 0) {
                    func_8003A1D8(D_801D7610 + 2);
                    D_8012D0B8 = 0x3C;
                } else {
                    D_8012D8F0 = D_801D7610 + 2;
                }
                break;
            case 1:
                D_8012CDB8 = 0x80;
                D_8007C210 = D_8012D008;
                D_80173478 = D_801D7E80;
                D_801733B8 = D_801D7E70;
                D_801D34F8 = 0x11;
                func_8001CD90();
                func_8001CDA8();
                func_8001CEA0();
                func_8003A1AC(-2);
                break;
            }
        }
        func_80025C98();
    }
    func_8002C500(D_801D7618, (D_801732F8 * 0x114) + &D_801E9250);
    D_801732F8 = func_8003CAB0(0xFF, D_801732F8);
    func_80012E44();
    func_800163E4();
    func_80013240();
    func_80025BFC();
    func_80018A9C();
    func_8003C84C();
}

void func_8003D278(void) {
    func_8001CE0C(1);
    if (D_801D77D0 == 0) {
        D_8007B1E8 += 1;
        D_80173310 += 1;
        if (D_80173310 == 2) {
            func_80045750(1);
        }
        if ((u16) D_80173310 >= 0x5DCU) {
            D_8007C210 = D_8012D008;
            D_80173478 = D_801D7E80;
            D_801733B8 = D_801D7E70;
            D_8012CDB8 = 0x80;
            D_801D34F8 = 2;
        }
        if ((D_80173310 == 0x564) && (D_8012CD30 >= 2)) {
            func_8003A1AC(-1);
        }
        if (D_801D35AE & 0x860 & 0xFFFF) {
            D_8007C210 = D_8012D008;
            D_80173478 = D_801D7E80;
            D_801733B8 = D_801D7E70;
            D_8012CDB8 = 0x80;
            snd_play_se(0x2D);
            D_801D34F8 = 6;
            func_8001CEA0();
        }
        func_80025C98();
    }
    func_8002C500(D_801D7618, (D_801732F8 * 0x114) + &D_801E9250);
    if (!(D_80173310 & 0xFF & 0xFFFF)) {
        D_801D7618 = func_800497C8() & 3;
        if (D_801D7618 == 1) {
            D_801D7618 = 0;
        }
    }
    D_801732F8 = func_8003CAB0(0x3F, D_801732F8);
    func_80012E44();
    func_800163E4();
    func_80013240();
    func_80025BFC();
    func_80018A9C();
}

void func_8003F4B0(s32 arg0) {
    s32 *var_s2;
    s32 temp_s0;
    s32 var_s1;
    s32 var_s3;
    s32 var_s4;

    var_s4 = arg0;
    if (var_s4 >= 0x565) {
        var_s4 = 0x564;
    }
    var_s2 = &D_800757B0;
    var_s3 = 0;
    if (D_800757B0 != 0) {
        do {
            var_s1 = *var_s2;
            if (var_s1 == -2) {
                var_s1 = *((D_8012CF50 * 4) + &D_80077360);
            }
            var_s2 += 4;
            if (var_s1 != -1) {
                temp_s0 = (var_s3 * 0x10) - (var_s4 - 0xF0);
                if ((u32) (temp_s0 + 7) < 0xFFU) {
                    func_80028578(0, temp_s0, var_s1, 0x64);
                    func_80028578(1, temp_s0 + 1, var_s1, 0x11D);
                }
            }
            var_s3 += 1;
        } while (*var_s2 != 0);
    }
}

void *func_80044A68(s16 arg0, void *arg1) {
    s32 sp24;
    s16 temp_a0;
    s16 temp_a3;
    s16 temp_t0;
    s16 temp_t1;
    s16 temp_t2;
    s16 temp_t3;
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = rcos(arg0);
    sp24 = temp_v0;
    temp_a0 = M2C_FIELD(arg1, s16 *, 0);
    temp_a3 = M2C_FIELD(arg1, s16 *, 0xC);
    temp_v1 = -rsin(arg0, arg1, temp_v0);
    temp_t0 = M2C_FIELD(arg1, s16 *, 2);
    temp_t1 = M2C_FIELD(arg1, s16 *, 0xE);
    temp_t2 = M2C_FIELD(arg1, s16 *, 4);
    temp_t3 = M2C_FIELD(arg1, s16 *, 0x10);
    M2C_FIELD(arg1, s16 *, 0) = (s16) ((s32) ((temp_v0 * temp_a0) - (temp_v1 * temp_a3)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 2) = (s16) ((s32) ((temp_v0 * temp_t0) - (temp_v1 * temp_t1)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 4) = (s16) ((s32) ((temp_v0 * temp_t2) - (temp_v1 * temp_t3)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 0xC) = (s16) ((s32) ((temp_v1 * temp_a0) + (temp_v0 * temp_a3)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) ((s32) ((temp_v1 * temp_t0) + (temp_v0 * temp_t1)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 0x10) = (s16) ((s32) ((temp_v1 * temp_t2) + (temp_v0 * temp_t3)) >> 0xC);
    return arg1;
}
