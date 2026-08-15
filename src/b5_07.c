/* b5_07.c -- batch 5, 7 functions recovered with m2c.
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

M2C_UNK func_80012B0C(s32 *, M2C_UNK *, s32, M2C_UNK);
M2C_UNK func_80012E44();
M2C_UNK func_80013240();
M2C_UNK func_800163E4();
M2C_UNK func_80018584(M2C_UNK *, s32);
M2C_UNK func_800185F0(M2C_UNK *, s32);
M2C_UNK func_800186C8();
M2C_UNK func_80018A9C();
M2C_UNK func_800197A8(M2C_UNK);
M2C_UNK func_8001CDBC(M2C_UNK);
M2C_UNK func_8001CE0C(M2C_UNK);
M2C_UNK func_8001CEA0();
M2C_UNK func_8001CEC8(M2C_UNK);
M2C_UNK func_8001EF54(M2C_UNK);
M2C_UNK func_80025C70();
M2C_UNK func_800262B0();
M2C_UNK func_800267E4(M2C_UNK);
M2C_UNK func_80028578(s32, s32, s8 *, M2C_UNK);
M2C_UNK func_8002AF1C(u16, M2C_UNK *, M2C_UNK *);
M2C_UNK func_8002B1A0();
M2C_UNK func_8002C500(M2C_UNK, M2C_UNK *);
M2C_UNK func_8002E6A8(s16, s16);
M2C_UNK func_8002ED1C(M2C_UNK);
M2C_UNK func_8002F71C();
M2C_UNK func_8003A1AC(M2C_UNK, u16);
M2C_UNK func_8003BE58();
M2C_UNK func_8003E5F8(M2C_UNK);
M2C_UNK func_80042E08(M2C_UNK *, M2C_UNK *);
M2C_UNK func_80045750(M2C_UNK);
M2C_UNK func_800490D4(M2C_UNK *);
M2C_UNK func_80049638(s32 *);
M2C_UNK func_800496C8(M2C_UNK *, M2C_UNK *);
M2C_UNK func_800497D8();
M2C_UNK func_80055540();
M2C_UNK func_80055570();
M2C_UNK snd_play_se(M2C_UNK);
extern M2C_UNK D_800118D0;
extern M2C_UNK D_800121C4;
extern M2C_UNK D_8007C258;
extern M2C_UNK D_801D7770;
extern M2C_UNK D_801E91F0;
extern M2C_UNK D_801E9250;
extern M2C_UNK func_80057654;
extern s16 D_8012CDB8;
extern s16 D_801D34F8;
extern s32 *D_80077590;
extern s32 *D_80077594;
extern s32 *D_80077598;
extern s32 *D_8007759C;
extern s32 *D_800775A0;
extern s32 D_800776D8;
extern s32 D_800776F8;
extern s32 D_80077700;
extern s32 D_80077710;
extern s32 D_8007B1B8;
extern s32 D_8007B1BC;
extern s32 D_8012CD30;
extern s32 D_8012CF60;
extern s32 D_80173138;
extern s32 D_801D35D8;
extern s32 D_801D77A8;
extern s32 D_801D77F0;
extern s32 D_801D7E60;
extern s32 D_801D7EB8;
extern s32 D_801D9050;
extern s32 D_801D9068;
extern s32 D_801D906C;
extern s32 D_801D9070;
extern s32 D_801D9078;
extern s32 D_801D907C;
extern s32 D_801D9080;
extern s32 D_801E9168;
extern s32 D_801E9178;
extern s32 D_801E9190;
extern s32 D_801E91E0;
extern s8 D_80010800;
extern s8 D_80010814;
extern u16 D_800776E0;
extern u16 D_8007B1E8;
extern u16 D_8007C210;
extern u16 D_8012CDC0;
extern u16 D_8012CDD8;
extern u16 D_8012D008;
extern u16 D_8012D8D0;
extern u16 D_8012D908;
extern u16 D_80173310;
extern u16 D_801D35AE;
extern u16 D_801D77D0;
extern u32 D_80077708;
extern u8 D_801D35A9;
extern void *D_8007758C;
s32 rcos(s32);
u32 rsin(s32);

void func_8002B4A8(void) {
    M2C_UNK var_a0;
    s32 var_v0;

    func_8001CE0C(1);
    if (D_801D77D0 == 0) {
        D_80173310 += 1;
        D_8007B1E8 += 1;
        if ((D_80173310 - 1) == 2) {
            func_80045750(1);
        }
        var_v0 = D_801D77F0 - 0x78;
        if ((s32) D_80173310 >= D_801D77F0) {
            D_8012CDB8 = 0x80;
            D_801D34F8 = 2;
            D_8007C210 = D_8012D008;
            var_v0 = D_801D77F0 - 0x78;
        }
        if ((D_80173310 == var_v0) && (D_8012CD30 >= 2)) {
            func_8003A1AC(-1, D_80173310);
        }
        if (D_801D35AE & 0x860) {
            D_8012CDB8 = 0x80;
            snd_play_se(0x2D);
            D_801D34F8 = 6;
            func_8001CEA0();
            D_8007C210 = D_8012D008;
        }
        func_8002AF1C(D_80173310, &D_8007C258, &D_801E9250);
    }
    if ((D_80173310 == 0) || (var_a0 = 1, (((u16) D_80173310 < 0x4BU) == 0))) {
        var_a0 = 0;
    }
    func_8002C500(var_a0, &D_8007C258);
    func_80012E44();
    func_800163E4();
    func_80013240();
    func_80025C70();
    func_80018A9C();
    func_8002B1A0();
}

void func_8002FB5C(void) {
    s16 var_v1;
    s32 temp_v0_2;
    u16 temp_v0;

    func_8001CEC8(1);
    if (D_801D77D0 == 0) {
        temp_v0 = D_80173310;
        D_80173310 = temp_v0 + 1;
        if ((temp_v0 & 0xFFFF) == 2) {
            func_80045750(1);
        }
        D_8007B1E8 += 1;
        if (D_801D35AE & 0x90) {
            D_8012D908 = D_8012CDD8;
            D_8012D8D0 = D_8012CDC0;
            snd_play_se(0x24);
            D_801D34F8 = 0x11;
        }
        if (D_801D35AE & 0x860) {
            func_8002E6A8((s16) D_8012D908, (s16) D_8012D8D0);
            snd_play_se(0x2D);
            if (D_801D35A9 == 0x23) {
                var_v1 = 0x11;
                if (D_801D35AE & 0x800) {
                    var_v1 = 0x22;
                }
                D_801D34F8 = var_v1;
            } else {
                D_801D34F8 = 0x11;
            }
        }
        if (D_801D35AE & 0x8000) {
            if (D_801D35A9 == 0x23) {
                if ((s16) D_8012D8D0 > 0) {
                    D_8012D8D0 = (s16) D_8012D8D0 - 1;
                    goto block_17;
                }
            } else if ((s16) D_8012D908 > 0) {
                D_8012D908 = (s16) D_8012D908 - 1;
block_17:
                D_801E9190 = 0;
                D_801E9168 = 0x1E;
                D_801E91E0 += 0x800;
                snd_play_se(0x21);
            }
        }
        if (D_801D35AE & 0x2000) {
            if (D_801D35A9 == 0x23) {
                if ((s16) D_8012D8D0 < 7) {
                    D_8012D8D0 = (s16) D_8012D8D0 + 1;
                    goto block_24;
                }
            } else if ((s16) D_8012D908 < 3) {
                D_8012D908 = (s16) D_8012D908 + 1;
block_24:
                D_801E9190 = 1;
                D_801E9168 = 0x1E;
                D_801E91E0 -= 0x800;
                snd_play_se(0x2C);
            }
        }
        temp_v0_2 = D_801E9168 - 1;
        if (D_801E9168 > 0) {
            D_801E9168 = temp_v0_2;
            D_801D9050 = ((u32) temp_v0_2 >> 2) & 1;
        }
        D_801E91E0 = (s32) (D_801E91E0 * 0xF) / 16;
    }
    func_8002F71C();
    func_8002ED1C(0);
    func_8001EF54(0xF4);
    D_8007B1B8 = (s32) (s16) D_8012D8D0;
    D_8007B1BC = (s32) D_801D35A9;
}

void func_8003B59C(void) {
    M2C_UNK sp20;
    M2C_UNK sp40;
    M2C_UNK sp60;
    s32 spC0;
    s32 spC4;
    s32 spC8;
    s32 temp_hi;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_s0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_v0;
    u32 temp_v0;
    u32 var_v0_2;
    u32 var_v0_3;
    u8 temp_a2;

    D_801D9070 = 0;
    D_801D906C = 0;
    D_801D9068 = 0;
    D_801D9080 = 0;
    D_801D907C = 0;
    D_801D9078 = 0;
    D_801D906C = -0x600;
    D_801D9078 = 0x80;
    var_s1 = 0;
    D_801D9070 = (D_80173138 << 5) - 0x2400;
    D_801D9080 = D_80173138 * 8;
    func_800186C8();
    do {
        var_v0 = D_801D35D8 + 0x80;
        if (var_v0 < 0) {
            var_v0 = D_801D35D8 + 0x17F;
        }
        temp_hi = (s32) (var_s1 + (var_v0 >> 8)) % 40;
        temp_s0 = ((s32) (var_s1 << 0xC) / 40) + ((s32) (D_801D35D8 * 0x10) / 40);
        func_800185F0(&sp20, temp_s0);
        func_80042E08(&D_801E91F0, &sp20);
        func_800185F0(&sp60, temp_s0 + 0x800);
        func_80042E08(&D_801E91F0, &sp60);
        spC0 = (s32) (rsin(temp_s0) * 5) / 2;
        temp_v1 = rcos(temp_s0) * 2;
        spC8 = temp_v1 - 0x3000;
        if (temp_hi == 0x14) {
            spC8 = temp_v1 - 0x4800;
            spC0 = 0;
        }
        temp_v0 = rsin(((s32) (var_s1 << 0xD) / 40) + (D_80173310 * 0x10));
        var_a0 = spC8;
        temp_v1_2 = (s32) ((temp_v0 >> 0x1F) + temp_v0) >> 1;
        if (var_a0 < 0) {
            var_a0 += 3;
        }
        spC4 = temp_v1_2 - ((var_a0 >> 2) + 0x1400);
        if (temp_hi == 0x14) {
            spC4 = -0x1000;
        }
        temp_s0_2 = 0xF4 - var_s1;
        func_80012B0C(&spC0, &sp20, temp_s0_2, 0);
        func_80012B0C(&spC0, &sp60, temp_s0_2, 0);
        var_s1 += 1;
        var_s0 = -0xC00;
    } while (var_s1 < 0x28);
    var_s1_2 = 0;
    do {
        func_800185F0(&sp20, 0x800);
        if (D_8012CF60 == var_s1_2) {
            var_v0_2 = rsin(D_80173310 << 5);
            if ((s32) var_v0_2 < 0) {
                var_v0_2 += 0x1F;
            }
            func_80018584(&sp40, (s32) var_v0_2 >> 5);
        } else {
            func_80018584(&sp40, 0);
        }
        func_80042E08(&sp40, &sp20);
        func_80042E08(&D_801E91F0, &sp20);
        spC0 = var_s0;
        spC8 = -0x6400;
        spC4 = -0x100;
        if (D_8012CF60 == var_s1_2) {
            var_v0_3 = rsin(D_80173310 << 6);
            if ((s32) var_v0_3 < 0) {
                var_v0_3 += 3;
            }
            spC4 += (s32) var_v0_3 >> 2;
        }
        temp_a2 = *(&D_801D7770 + var_s1_2);
        var_s0 += 0xC00;
        var_s1_2 += 1;
        func_80012B0C(&spC0, &sp20, temp_a2 + 0x8C, 0x01410000);
    } while (var_s1_2 < 3);
}

void func_8003C4B4(void) {
    s32 sp10;
    u16 temp_v0;

    func_8001CEC8(1);
    if (D_801D77D0 == 0) {
        temp_v0 = D_80173310;
        D_80173310 = temp_v0 + 1;
        if ((temp_v0 & 0xFFFF) == 2) {
            func_80045750(1);
        }
        D_8007B1E8 += 1;
        if (D_801D35AE & 0x90 & 0xFFFF) {
            snd_play_se(0x24);
            D_801D34F8 = 6;
        }
        if (D_801D35AE & 0x860 & 0xFFFF) {
            snd_play_se(0x2D);
            switch (D_801D7E60) {
            case 0:
                D_801D34F8 = 0x17;
                break;
            case 1:
                D_801D34F8 = 0x15;
                break;
            case 2:
                D_801D34F8 = 0x19;
                break;
            }
        }
        sp10 = D_801D7E60;
        if (D_801D35AE & 0x8000 & 0xFFFF) {
            D_801D7E60 = 0;
            D_801D7EB8 = 0;
        }
        if (D_801D35AE & 0x2000 & 0xFFFF) {
            D_801D7E60 = 1;
            D_801D7EB8 = 1;
        }
        if (D_801D35AE & 0x4000 & 0xFFFF) {
            D_801D7E60 = 2;
        }
        if (D_801D35AE & 0x1000 & 0xFFFF) {
            D_801D7E60 = D_801D7EB8;
        }
        if (sp10 != D_801D7E60) {
            snd_play_se(0x1F);
        }
    }
    func_8003BE58();
    func_8001EF54(0xF2);
}

void func_8003D704(void) {
    s8 sp10;
    s8 sp11;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    func_80028578(0x20, 0xC8, &D_80010800, 0x7F);
    if (D_801D35AE & 0x800) {
        D_801E9178 = 0;
    }
    func_80028578(0x48, 0x20, &D_80010814, 0x64);
    var_s0 = 0;
    var_s2 = 0;
    do {
        var_s1 = 0x20;
loop_4:
        sp10 = var_s2 + 0x20 + (var_s0 * 0x10);
        sp11 = 0;
        func_80028578(var_s1, (var_s0 + 8) * 8, &sp10, 0x64);
        func_80028578(var_s1, (var_s0 + 0xD) * 8, &sp10, 0x7F);
        var_s2 += 1;
        var_s1 += 8;
        if (var_s2 < 0x10) {
            goto loop_4;
        }
        var_s0 += 1;
        var_s2 = 0;
    } while (var_s0 < 4);
}

void func_8003EB0C(void) {
    if (D_8012CD30 < 0x33) {
        func_8001CE0C(0);
    }
    func_800262B0();
    func_800267E4(1);
    if (D_80173310 == 2) {
        func_80045750(1);
    }
    if (D_801D77D0 == 0) {
        D_80173310 += 1;
        D_8007B1E8 += 1;
        D_801D77A8 += 1;
        if ((D_80173310 == 0x1E) && (D_8012CD30 >= 0x33)) {
            func_8001CDBC(8);
            D_8012CD30 = 1;
        }
        if ((u16) D_80173310 >= 0x1C3U) {
            D_801D34F8 = 8;
        }
        if (D_801D35AE & 0x8F0) {
            snd_play_se(0x2D);
            D_801D34F8 = 6;
            func_8001CEA0();
        }
    }
    func_800197A8(1);
    func_8003E5F8(0);
}

void func_800576E8(s32 arg0, u32 arg1) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_v0;

    M2C_FIELD(D_8007758C, u16 *, 0x1A6) = (u16) D_800776E0;
    temp_s0 = M2C_FIELD(D_8007758C, u16 *, 0x1AE) & 0x7FF;
    func_80055570();
    D_800776D8 = 0;
    temp_s0_2 = temp_s0 & 0xFFFF;
    if ((M2C_FIELD(D_8007758C, u16 *, 0x1AE) & 0x7FF) != temp_s0_2) {
loop_1:
        temp_v0 = D_800776D8 + 1;
        D_800776D8 = temp_v0;
        if (temp_v0 >= 0x1389) {
            func_800496C8(&D_800118D0, &D_800121C4);
        } else if ((M2C_FIELD(D_8007758C, u16 *, 0x1AE) & 0x7FF) != temp_s0_2) {
            goto loop_1;
        }
    }
    M2C_FIELD(D_8007758C, u16 *, 0x1AA) = (u16) ((M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 0xFFCF) | 0x20);
    func_80055570();
    func_80055540();
    D_80077700 = arg0;
    D_80077708 = arg1;
    D_80077710 = (arg1 >> 6) + ((arg1 & 0x3F) != 0);
    *D_800775A0 |= 0x900000;
    *D_8007759C |= 0x80000;
    *D_80077590 = D_80077700;
    *D_80077594 = (D_80077710 << 0x10) | 0x10;
    D_800776F8 = 0;
    func_80049638(D_8007759C);
    func_800490D4(&func_80057654);
    func_800497D8();
    *D_80077598 = 0x01000201;
}
