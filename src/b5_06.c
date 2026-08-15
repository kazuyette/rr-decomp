/* b5_06.c -- batch 5, 5 functions recovered with m2c.
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

M2C_UNK func_80013338(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_80013494();
M2C_UNK func_800135B8(s32, s16);
M2C_UNK func_8001AA60(M2C_UNK *);
M2C_UNK func_80021048();
M2C_UNK func_80025D9C(s32);
M2C_UNK func_80028578(s32, s32, s32, M2C_UNK);
M2C_UNK func_8002AF1C(M2C_UNK, M2C_UNK *, M2C_UNK *);
M2C_UNK func_800355A4(M2C_UNK);
M2C_UNK func_800376EC(s32);
M2C_UNK func_8003D154();
M2C_UNK func_80045750(M2C_UNK, u16);
M2C_UNK func_800496C8(M2C_UNK *, s32, s32);
M2C_UNK func_80052410(M2C_UNK, void *);
M2C_UNK func_80052440(u8, M2C_UNK *, M2C_UNK *);
M2C_UNK snd_play_se(M2C_UNK);
extern M2C_UNK *D_8007C248;
extern M2C_UNK D_80011598;
extern M2C_UNK D_800746A0;
extern M2C_UNK D_80074720;
extern M2C_UNK D_80074D9C;
extern M2C_UNK D_80076C80;
extern M2C_UNK D_80077610;
extern M2C_UNK D_80077614;
extern M2C_UNK D_80079D70;
extern M2C_UNK D_8007C258;
extern M2C_UNK D_801733E0;
extern M2C_UNK D_801D3588;
extern M2C_UNK D_801D3590;
extern M2C_UNK D_801E9250;
extern s16 D_8007C210;
extern s16 D_8007C32C;
extern s16 D_8012CDB8;
extern s16 D_80173310;
extern s16 D_801733B8;
extern s16 D_801D34F8;
extern s16 D_801D77C0;
extern s16 D_801D9060;
extern s32 D_80074DAC;
extern s32 D_80074DB0;
extern s32 D_80074DB4;
extern s32 D_80077474;
extern s32 D_800774D0;
extern s32 D_8007C260;
extern s32 D_8007C268;
extern s32 D_8007C26C;
extern s32 D_8007C270;
extern s32 D_8007C480;
extern s32 D_8012CD30;
extern s32 D_8012CDA0;
extern s32 D_8012CF70;
extern s32 D_8012D008;
extern s32 D_8012D020;
extern s32 D_801733E4;
extern s32 D_801733F4;
extern s32 D_80173404;
extern s32 D_80173414;
extern s32 D_801D358C;
extern s32 D_801E90E0;
extern u16 D_80173478;
extern u8 D_800774CF;
s32 SquareRoot(s32, s32, s32, s32);
s32 func_800497C8(s32, M2C_UNK *);
s32 rsin(s32, s32, M2C_UNK *);

void func_8002B370(void) {
    if (D_801D77C0 == 0) {
        func_8003D154();
        return;
    }
    D_8012CD30 += 1;
    D_8012D008 = (s32) D_8007C210;
    D_8007C210 = (s16) D_80173478;
    func_80045750(0, D_80173478);
    func_80013338(0, 0, 0);
    func_800135B8(D_8007C210 < 3, D_801733B8);
    D_801D9060 = 3;
    func_80013494();
    func_80025D9C(D_8007C210 - 1);
    D_8007C480 = 0;
    D_8007C248 = &D_8007C258;
    func_800355A4(5);
    func_8001AA60(&D_8007C258);
    func_80021048();
    func_8002AF1C(0, &D_8007C258, &D_801E9250);
    func_800376EC(D_8012CDA0);
    D_8012CDB8 = 0x180;
    D_80173310 = 0xFFFF;
    D_801D34F8 = 9;
}

void func_80030E10(void) {
    s32 *var_v0;
    s32 temp_s1;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;

    if (D_8012D020 < 0) {
        var_s2 = 1;
        var_s3 = 0;
        var_s4 = 2;
        do {
            var_s0 = 0;
            temp_s1 = var_s3 * 0x10;
loop_3:
            temp_v0 = var_s2 & D_8012D020;
            if ((temp_v0 != 0) && (temp_v0 != 0)) {
                var_v0 = ((temp_s1 + var_s0) * 4) + &D_800746A0;
            } else {
                var_v0 = ((temp_s1 + var_s0) * 4) + &D_80074720;
            }
            var_s0 += 1;
            func_80028578(var_s4 * 8, var_s0 * 8, *var_v0, 0x64);
            var_s2 *= 2;
            if (var_s0 < 0x10) {
                goto loop_3;
            }
            var_s3 += 1;
            var_s4 += 0x12;
        } while (var_s3 < 2);
    }
}

void func_80033584(void *arg0) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_lo;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    temp_a1 = (D_801733E4 - D_801733F4) + (D_80173404 - D_80173414);
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) (M2C_FIELD(arg0, s32 *, 0x28) - (temp_a1 * 4));
    if (temp_a1 >= 5) {
        var_v0 = temp_a1 * M2C_FIELD(arg0, s32 *, 0xA4);
        if (var_v0 < 0) {
            var_v0 += 0x3F;
        }
        M2C_FIELD(arg0, s32 *, 0xAC) = (s32) ((var_v0 >> 6) + M2C_FIELD(arg0, s32 *, 0xAC));
    }
    temp_lo = (s32) ((M2C_FIELD(&D_801733E0, s32 *, 4) + M2C_FIELD(&D_801733E0, s32 *, 0x14) + M2C_FIELD(&D_801733E0, s32 *, 0x24) + M2C_FIELD(&D_801733E0, s32 *, 0x34)) * 0x1E) / 100;
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (temp_lo + M2C_FIELD(arg0, s32 *, 0x14));
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (temp_lo + M2C_FIELD(arg0, s32 *, 0x40));
    temp_a1_2 = (M2C_FIELD(&D_801733E0, s32 *, 4) - M2C_FIELD(&D_801733E0, s32 *, 0x24)) + (M2C_FIELD(&D_801733E0, s32 *, 0x14) - M2C_FIELD(&D_801733E0, s32 *, 0x34));
    temp_v0 = temp_a1_2 * -4;
    D_8012CF70 = temp_v0;
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) + temp_v0);
    var_v1 = rsin(M2C_FIELD(arg0, s32 *, 0x28), temp_a1_2, &D_801733E0) / 64;
    if (var_v1 < 0) {
        var_v1 = -var_v1;
    }
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (var_v1 + M2C_FIELD(arg0, s32 *, 0x14));
}

void func_80038BB4(void) {
    M2C_UNK *var_a1;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1_2;
    s32 var_a2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v1;

    var_a1 = (M2C_UNK *)0x13500;
    temp_v0 = D_8007C210 < 3;
    if (temp_v0 != 0) {
        var_a1 = (M2C_UNK *)0xC000;
    }
    var_s1 = 0xD200;
    if (temp_v0 != 0) {
        var_s1 = 0xC000;
    }
    if (((((s32) ((D_801E90E0 << 0x10) + D_8007C260) % (s32) (D_801E90E0 << 8)) & ~0xFF) == var_a1) && (D_8007C32C != 2)) {
        M2C_FIELD(&D_801D3588, s32 *, 0) = (s32) (func_800497C8(D_8007C260, var_a1) & 0x7F);
        var_a1 = &D_80074D9C;
        M2C_FIELD(&D_801D3590, s32 *, 0) = (s32) M2C_FIELD(&D_80074D9C, s32 *, 0);
        M2C_FIELD(&D_801D3590, s32 *, 4) = (s32) M2C_FIELD(&D_80074D9C, s32 *, 4);
        M2C_FIELD(&D_801D3590, s32 *, 8) = (s32) M2C_FIELD(&D_80074D9C, s32 *, 8);
        M2C_FIELD(&D_801D3590, s32 *, 0xC) = (s32) M2C_FIELD(&D_80074D9C, s32 *, 0xC);
        D_801D358C = 0;
    }
    if (((((s32) ((D_801E90E0 << 0x10) + D_8007C260) % (s32) (D_801E90E0 << 8)) & ~0xFF) == var_s1) && (D_8007C32C == 2)) {
        M2C_FIELD(&D_801D3588, s32 *, 0) = (s32) (func_800497C8(D_8007C260, var_a1) & 0x3F);
        M2C_FIELD(&D_801D3588, s32 *, 8) = (s32) M2C_FIELD(&D_80074D9C, s32 *, 0);
        M2C_FIELD(&D_801D3588, s32 *, 0xC) = (s32) M2C_FIELD(&D_80074D9C, s32 *, 4);
        M2C_FIELD(&D_801D3588, s32 *, 0x10) = (s32) M2C_FIELD(&D_80074D9C, s32 *, 8);
        M2C_FIELD(&D_801D3588, s32 *, 0x14) = (s32) M2C_FIELD(&D_80074D9C, s32 *, 0xC);
        M2C_FIELD(&D_801D3588, s32 *, 4) = 0;
    }
    temp_v0_2 = M2C_FIELD(&D_801D3588, s32 *, 0) + 1;
    if (M2C_FIELD(&D_801D3588, s32 *, 0) > 0) {
        M2C_FIELD(&D_801D3588, s32 *, 0) = temp_v0_2;
        if (temp_v0_2 >= 0x709) {
            M2C_FIELD(&D_801D3588, s32 *, 0) = 0;
        }
        var_a0 = 0xC8 * D_80074DAC;
        if (var_a0 < 0) {
            var_a0 += 0xFFFF;
        }
        var_a2 = 0xC8 * D_80074DB0;
        M2C_FIELD(&D_801D3588, s32 *, 8) = (s32) ((var_a0 >> 0x10) + M2C_FIELD(&D_801D3588, s32 *, 8));
        if (var_a2 < 0) {
            var_a2 += 0xFFFF;
        }
        var_a1_2 = 0xC8 * D_80074DB4;
        M2C_FIELD(&D_801D3588, s32 *, 0xC) = (s32) ((var_a2 >> 0x10) + M2C_FIELD(&D_801D3588, s32 *, 0xC));
        if (var_a1_2 < 0) {
            var_a1_2 += 0xFFFF;
        }
        M2C_FIELD(&D_801D3588, s32 *, 0x10) = (s32) ((var_a1_2 >> 0x10) + M2C_FIELD(&D_801D3588, s32 *, 0x10));
        if (M2C_FIELD(&D_801D3588, s32 *, 4) == 0) {
            temp_a1 = D_8007C268 - M2C_FIELD(&D_801D3588, s32 *, 8);
            temp_a2 = D_8007C26C - M2C_FIELD(&D_801D3588, s32 *, 0xC);
            temp_a3 = D_8007C270 - M2C_FIELD(&D_801D3588, s32 *, 0x10);
            if ((temp_a1 < 0x1000) && (temp_a3 < 0x1000) && (temp_a1 >= -0xFFF) && (temp_a3 >= -0xFFF)) {
                var_v0 = temp_a1 * temp_a1;
                if (var_v0 < 0) {
                    var_v0 += 3;
                }
                var_v1 = temp_a2 * temp_a2;
                temp_a1_2 = var_v0 >> 2;
                if (var_v1 < 0) {
                    var_v1 += 3;
                }
                temp_v0_3 = var_v1 >> 2;
                var_a0_2 = temp_a3 * temp_a3;
                if (var_a0_2 < 0) {
                    var_a0_2 += 3;
                }
                if ((SquareRoot(temp_a1_2 + ((s32) (temp_v0_3 + ((u32) temp_v0_3 >> 0x1F)) >> 1) + (var_a0_2 >> 2), temp_a1_2, temp_a2, temp_a3) >> 0xA) <= 0x7FFF) {
                    M2C_FIELD(&D_801D3588, s32 *, 4) = 1;
                    snd_play_se(0x2B);
                }
            }
        }
    }
}

s32 func_80052BF0(s32 arg0, M2C_UNK arg1) {
    s32 var_s0;
    s32 var_v1;

    var_s0 = 0;
    var_v1 = 0x7FFFFF;
loop_1:
    if (M2C_FIELD(&D_80077614, u8 *, 0) != 0) {
        var_s0 = 4;
    }
    if (M2C_FIELD(&D_80077614, u8 *, 1) != 0) {
        var_s0 = 5;
    }
    if (var_s0 != 0) {
        if (D_80077474 != 0) {
            func_800496C8(&D_80011598, *((var_s0 * 4) + &D_80076C80), D_800774D0);
        }
        *(&D_80077610 + var_s0) = 0;
        func_80052410(arg1, (var_s0 * 8) + &D_80079D70);
        return -1;
    }
    if ((arg0 != 0) || (var_v1 -= 1, (D_800774D0 == 0))) {
        return D_800774D0;
    }
    if (var_v1 == -1) {
        func_80052440(D_800774CF, &D_80077614, &D_80076C80);
        return -1;
    }
    goto loop_1;
}
