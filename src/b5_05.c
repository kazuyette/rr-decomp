/* b5_05.c -- batch 5, 16 functions recovered with m2c.
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

M2C_UNK AddPrim(s32, s32 *);
M2C_UNK ClearOTagR(void *, M2C_UNK);
M2C_UNK DrawOTag(void *);
M2C_UNK PutDrawEnv(void *);
M2C_UNK func_80012B0C(s32 *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_800185F0(M2C_UNK *, s32);
M2C_UNK func_8001865C(M2C_UNK *, s32);
M2C_UNK func_800186C8();
M2C_UNK func_800206CC(s16 *, s32, s32 *);
M2C_UNK func_80020B88(s16 *, s32, s32 *, s16 *);
M2C_UNK func_80020D6C(s16 *, s32, s32 *);
M2C_UNK func_80020E4C(s16 *);
M2C_UNK func_80028578(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK func_8002D964();
M2C_UNK func_8002ECA4(M2C_UNK *);
M2C_UNK func_8003AE10(s16);
M2C_UNK func_8003B118(s16, s16);
M2C_UNK func_8003B1EC(s16, s16, s16);
M2C_UNK func_8003E128(s32, s32, M2C_UNK *, M2C_UNK);
M2C_UNK func_800402E4(s32 *, void *, void *);
M2C_UNK func_80040370(s32 *, void *, void *);
M2C_UNK func_80042E08(M2C_UNK *, M2C_UNK *);
M2C_UNK func_80043228(M2C_UNK *, s32 *);
M2C_UNK func_80043738();
M2C_UNK func_80043794();
M2C_UNK func_80043C80(void *, s32, s32 *);
M2C_UNK func_80045790(M2C_UNK);
M2C_UNK func_80045854(s16 *, s32);
M2C_UNK func_8004617C(s32 *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *);
M2C_UNK func_80048198(M2C_UNK *, s32, s32, s32);
M2C_UNK func_800496C8(M2C_UNK *, s32);
M2C_UNK func_80051EF0(M2C_UNK, M2C_UNK, u8 *);
M2C_UNK func_80052410(M2C_UNK, M2C_UNK *);
M2C_UNK func_80052440(u8);
M2C_UNK func_800524D8();
M2C_UNK func_80052D14(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_80055E2C(s32, M2C_UNK, s32 *);
M2C_UNK track_select(s16 *);
extern M2C_UNK *D_80077628;
extern M2C_UNK *D_801E9170;
extern M2C_UNK D_80010A08;
extern M2C_UNK D_80011568;
extern M2C_UNK D_800115AC;
extern M2C_UNK D_800115D8;
extern M2C_UNK D_800743A8;
extern M2C_UNK D_80076C0C;
extern M2C_UNK D_80076C80;
extern M2C_UNK D_80077128;
extern M2C_UNK D_800771CC;
extern M2C_UNK D_800771D4;
extern M2C_UNK D_80077270;
extern M2C_UNK D_80077615;
extern M2C_UNK D_80079D80;
extern M2C_UNK D_80079D98;
extern M2C_UNK D_8012D950;
extern M2C_UNK D_801E90E8;
extern M2C_UNK D_801E91F0;
extern M2C_UNK D_801E9258;
extern M2C_UNK func_80053390;
extern s16 D_8007C210;
extern s16 D_8007C324;
extern s16 D_8012D0B0;
extern s16 D_801733D0;
extern s16 D_801D35BC;
extern s16 D_801D35D0;
extern s16 D_801D7E58;
extern s16 D_801E9240;
extern s16 D_801E9250;
extern s32 D_80073130;
extern s32 D_80073160;
extern s32 D_80073190;
extern s32 D_80077474;
extern s32 D_800774D0;
extern s32 D_80077618;
extern s32 D_80077620;
extern s32 D_8007C4D0;
extern s32 D_8012CFC8;
extern s32 D_80173320;
extern s32 D_80173360;
extern s32 D_801733D8;
extern s32 D_801D7608;
extern s32 D_801D7768;
extern s32 D_801D9068;
extern s32 D_801D906C;
extern s32 D_801D9070;
extern s32 D_801D9078;
extern s32 D_801D907C;
extern s32 D_801D9080;
extern s32 D_801E90E0;
extern s32 D_801E91D8;
extern s32 D_801E91E0;
extern s8 *D_800774D8;
extern u16 D_8007B1E8;
extern u16 D_80173310;
extern u16 D_801733B8;
extern u16 D_801D34F8;
extern u16 D_801D77B8;
extern u16 D_801D77D0;
extern u8 *D_800774DC;
extern u8 *D_800774E0;
extern u8 *D_800774E4;
extern u8 D_800774CF;
extern u8 D_801D35A9;
extern void *D_8012CF68;
extern void *g_gpu_device;
s16 snd_play_se(M2C_UNK);
s32 *func_80042730(s32 *, void *, s32, s32, void *, void **);
s32 func_80037478(s32);
s32 func_8004006C(void *, void *);
s32 func_8004788C(s32, M2C_UNK, s16, s32);
s32 func_800497C8();
s32 func_80052A98(M2C_UNK, M2C_UNK);
s32 rsin(s32);

void func_80021048(void) {
    s16 sp10;
    s16 *var_s0;
    s16 temp_v0;
    s32 *var_s2_2;
    s32 *var_s3;
    s32 *var_s4;
    s32 temp_s6;
    s32 temp_s7;
    s32 var_a1;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s2;

    temp_s6 = D_801733D8;
    temp_s7 = D_801E90E0;
    var_s0 = &D_801E9250;
    D_801D7608 = func_800497C8();
    var_s2 = 0;
    if ((D_8007C210 == 4) && (D_801D35D0 == 1)) {
        D_801E9240 = 1;
    } else {
        D_801E9240 = 0;
    }
    if (D_801D34F8 != 0x1A) {
        sp10 = 0xC;
        var_s3 = &D_80073130;
        D_801D77B8 = D_801733B8;
        var_s1 = 0;
        if (D_8007C210 == 4) {
            var_s3 = &D_80073160;
        }
        func_80020E4C(&sp10);
        var_s4 = var_s3;
        do {
            track_select(var_s0);
            *var_s0 = 0;
            if (var_s1 == 0xB) {
                if (D_801E9240 == 1) {
                    *var_s0 = 1;
                    var_s2 += 1;
                    func_800206CC(var_s0, 0xB, var_s3);
                    var_a1 = 0xB;
                    goto block_13;
                }
            } else if (*var_s4 >= 0) {
                *var_s0 = 1;
                var_s2 += 1;
                func_800206CC(var_s0, var_s1, var_s3);
                var_a1 = var_s1;
block_13:
                func_80020B88(var_s0, var_a1, var_s3, &sp10);
            }
            var_s4 += 4;
            var_s1 += 1;
            var_s0 += 0x114;
        } while (var_s1 < 0xC);
        temp_v0 = var_s2 + 1;
        D_801D7E58 = temp_v0;
        D_8007C324 = temp_v0;
    } else {
        D_801D77B8 = 0;
        var_s1_2 = 0;
        var_s2_2 = &D_80073190;
        do {
            track_select(var_s0);
            if (*var_s2_2 >= 0) {
                *var_s0 = 0x25;
            } else {
                *var_s0 = 0;
            }
            func_800206CC(var_s0, var_s1_2, &D_80073190);
            func_80020D6C(var_s0, var_s1_2, &D_80073190);
            var_s2_2 += 4;
            var_s1_2 += 1;
            var_s0 += 0x114;
        } while (var_s1_2 < 0xC);
    }
    D_801733D8 = temp_s6;
    D_801E90E0 = temp_s7;
}

void func_8002E528(void) {
    s32 temp_v0;
    s32 temp_v0_2;
    void *temp_a0;

    temp_v0 = D_8012CFC8;
    D_8012CFC8 = temp_v0 + 1;
    temp_v0_2 = temp_v0 & 1;
    D_801D7768 = temp_v0_2;
    temp_a0 = (temp_v0_2 * 0x22BF4) + &D_8012D950;
    D_8012CF68 = temp_a0;
    *(void **)0x1F800000 = temp_a0 + 0xB70;
    ClearOTagR(temp_a0 + 0x70, 0x2C0);
    func_8002D964();
    PutDrawEnv(D_8012CF68);
    DrawOTag(D_8012CF68 + 0x70);
    func_80045790(0);
}

void func_8002ED1C(s32 arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    M2C_UNK sp20;
    M2C_UNK sp40;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    M2C_UNK var_a2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;

    sp68 = 0;
    sp64 = 0;
    sp60 = 0;
    D_801D9070 = 0;
    D_801D906C = 0;
    D_801D9068 = 0;
    D_801D9080 = 0;
    D_801D907C = 0;
    D_801D9078 = 0;
    D_801D9070 = -0xDC0;
    if ((D_801D34F8 == 0x24) || (D_801D34F8 == 0x27)) {
        D_801D9070 = -0x9C0;
    }
    D_801D906C = -0xA0;
    func_800186C8();
    if (D_801D35A9 == 0x41) {
        func_8001865C(&sp20, -0x40);
        func_800185F0(&sp40, D_801E91E0 + 0x400);
        func_80042E08(&sp40, &sp20);
        func_80042E08(&D_801E91F0, &sp20);
        sp18 = 0x1000;
        sp14 = 0x1000;
        sp10 = 0x1000;
        func_80043228(&sp40, &sp10);
        func_80042E08(&sp40, &sp20);
        func_8002ECA4(&sp20);
        var_a2 = 0xCC;
        goto block_19;
    }
    if (D_801D35A9 == 0x23) {
        if (D_801D34F8 == 0x27) {
            var_s0 = rsin(D_8007B1E8 * 0x10) * *(&D_800771CC + (D_801733D0 * 2));
            if (var_s0 < 0) {
                var_s0 += 0x1FF;
            }
            var_s0_2 = var_s0 >> 9;
        } else if (D_801D34F8 == 0x24) {
            var_s0_3 = rsin(D_8007B1E8 * 0x10) * 0x10 * *(&D_800743A8 + (D_8012D0B0 * 4));
            if (var_s0_3 < 0) {
                var_s0_3 += 0xFFF;
            }
            var_s0_2 = var_s0_3 >> 0xC;
        } else {
            var_s0_2 = D_801D35BC * 8;
        }
        func_8001865C(&sp20, var_s0_2 + (D_801E91D8 - 0x40));
        func_800185F0(&sp40, D_801E91E0 + 0x400);
        func_80042E08(&sp40, &sp20);
        func_80042E08(&D_801E91F0, &sp20);
        sp18 = 0x1000;
        sp14 = 0x1000;
        sp10 = 0x1000;
        func_80043228(&sp40, &sp10);
        func_80042E08(&sp40, &sp20);
        func_8002ECA4(&sp20);
        func_80012B0C(&sp60, &sp20, 0xF5, 0);
        if (arg0 != 0) {
            func_80012B0C(&sp60, &sp20, 0x8C, 0);
        }
        func_8001865C(&sp20, (D_801E91D8 - 0x40) - var_s0_2);
        func_800185F0(&sp40, D_801E91E0 + 0x400);
        func_80042E08(&sp40, &sp20);
        func_80042E08(&D_801E91F0, &sp20);
        sp18 = 0x1000;
        sp14 = 0x1000;
        sp10 = 0x1000;
        func_80043228(&sp40, &sp10);
        func_80042E08(&sp40, &sp20);
        func_8002ECA4(&sp20);
        func_80012B0C(&sp60, &sp20, 0xF6, 0);
        if (arg0 != 0) {
            var_a2 = 0x8D;
block_19:
            func_80012B0C(&sp60, &sp20, var_a2, 0);
        }
    } else {
        func_80028578(0x88, 0x78, &D_800771D4, 0x7F);
    }
}

void func_80031E48(s32 arg0) {
    M2C_UNK var_a3;
    s32 var_a0;
    s32 var_v1;

    var_v1 = D_8007C4D0;
    if ((arg0 + 8) < var_v1) {
        var_a0 = 1;
        var_v1 -= 8;
    } else {
        var_a0 = 0;
    }
    var_a3 = 0x7A;
    if (D_80173310 & 8) {
        var_a3 = 0x79;
    }
    func_8003E128((var_a0 * 0x90) + 0x10, (var_v1 * 0x10) + 0x40, &D_80077270, var_a3);
}

s32 *func_80034EFC(s32 *arg0, void *arg1, s32 arg2, s32 arg3) {
    void *sp18;
    s32 *temp_a1;
    s32 *temp_a1_2;
    s32 *temp_a1_3;
    s32 *temp_s0;
    s32 *temp_s0_2;
    s32 *temp_s0_3;
    s32 *temp_s0_4;
    s32 *temp_s2;
    s32 *temp_s2_2;
    s32 *temp_s2_3;
    s32 *temp_s2_4;
    s32 *var_s0;
    s32 *var_s0_2;
    s32 *var_s0_3;
    s32 *var_s0_4;
    s32 *var_s0_5;
    s32 *var_s2;
    s32 *var_s2_2;
    s32 temp_s4;
    s32 temp_s4_2;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_s3;
    s32 var_s3_2;
    s32 var_s3_3;
    s32 var_s3_4;
    s32 var_s3_5;
    void *temp_s5;

    temp_s5 = (arg2 * 0x10) + M2C_FIELD(arg1, s32 *, 8);
    var_s2_2 = arg0;
    sp18 = M2C_FIELD(temp_s5, void **, 0xC);
    if (M2C_FIELD(arg1, s32 *, 0x24) != 0) {
        func_80043738();
        func_80043794();
    }
    var_s3 = 0;
    if (M2C_FIELD(temp_s5, s16 *, 0) > 0) {
        var_s0 = var_s2_2;
        do {
            var_s3 += 1;
            if (func_8004006C(sp18, arg1) > 0) {
                temp_v0 = (s32) M2C_FIELD(arg1, s32 *, 0x2C) >> M2C_FIELD(arg1, s32 *, 0x20);
                M2C_FIELD(arg1, s32 *, 0x2C) = temp_v0;
                if ((u32) (temp_v0 - 1) < 0x1BFU) {
                    M2C_FIELD(var_s0, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x34);
                    M2C_FIELD(var_s0, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x38);
                    M2C_FIELD(var_s0, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 0x3C);
                    M2C_FIELD(var_s0, s32 *, 0x20) = (s32) M2C_FIELD(arg1, s32 *, 0x40);
                    M2C_FIELD(var_s0, s32 *, 0xC) = (s32) (arg3 + M2C_FIELD(sp18, s32 *, 0x18));
                    M2C_FIELD(var_s0, s32 *, 0x14) = (s32) M2C_FIELD(sp18, s32 *, 0x1C);
                    M2C_FIELD(var_s0, u16 *, 0x1C) = (u16) M2C_FIELD(sp18, u16 *, 0x20);
                    M2C_FIELD(var_s0, u16 *, 0x24) = (u16) M2C_FIELD(sp18, u16 *, 0x24);
                    func_80043C80(arg1 + 0x10, M2C_FIELD(arg1, s32 *, 0x28), var_s2_2 + 4);
                    *var_s2_2 = 0x09000000;
                    M2C_FIELD(var_s0, s8 *, 7) = 0x2C;
                    temp_a1 = var_s0;
                    var_s0 += 0x28;
                    var_s2_2 += 0x28;
                    AddPrim(M2C_FIELD(arg1, s32 *, 0) - (((M2C_FIELD(sp18, s16 *, 0x22) + M2C_FIELD(arg1, s32 *, 0x2C)) * 4) + 0x200), temp_a1);
                }
            }
            sp18 += 0x28;
        } while (var_s3 < M2C_FIELD(temp_s5, s16 *, 0));
    }
    var_s3_2 = 0;
    if (M2C_FIELD(temp_s5, s16 *, 2) > 0) {
        var_s0_2 = var_s2_2;
        do {
            var_s3_2 += 1;
            if (func_8004006C(sp18, arg1) > 0) {
                temp_t1 = (s32) M2C_FIELD(arg1, s32 *, 0x2C) >> M2C_FIELD(arg1, s32 *, 0x20);
                M2C_FIELD(arg1, s32 *, 0x2C) = temp_t1;
                if ((u32) (temp_t1 - 1) < 0x1BFU) {
                    temp_s4 = M2C_FIELD(arg1, s32 *, 0) - (((M2C_FIELD(sp18, s16 *, 0x22) + temp_t1) * 4) + 0x200);
                    func_8004617C(var_s2_2, 0, 1, 0, &D_80077128);
                    AddPrim(temp_s4, var_s0_2);
                    temp_s0 = var_s0_2 + 0xC;
                    M2C_FIELD(temp_s0, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x34);
                    M2C_FIELD(temp_s0, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x38);
                    M2C_FIELD(temp_s0, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 0x3C);
                    M2C_FIELD(temp_s0, s32 *, 0x20) = (s32) M2C_FIELD(arg1, s32 *, 0x40);
                    M2C_FIELD(temp_s0, s32 *, 0xC) = (s32) (arg3 + M2C_FIELD(sp18, s32 *, 0x18));
                    M2C_FIELD(temp_s0, s32 *, 0x14) = (s32) M2C_FIELD(sp18, s32 *, 0x1C);
                    M2C_FIELD(temp_s0, u16 *, 0x1C) = (u16) M2C_FIELD(sp18, u16 *, 0x20);
                    temp_s2 = var_s2_2 + 0xC;
                    M2C_FIELD(temp_s0, u16 *, 0x24) = (u16) M2C_FIELD(sp18, u16 *, 0x24);
                    func_80043C80(arg1 + 0x10, M2C_FIELD(arg1, s32 *, 0x28), temp_s2 + 4);
                    M2C_FIELD(var_s2_2, s32 *, 0xC) = 0x09000000;
                    M2C_FIELD(temp_s0, s8 *, 7) = 0x2C;
                    temp_s0_2 = temp_s0 + 0x28;
                    temp_s2_2 = temp_s2 + 0x28;
                    AddPrim(temp_s4, temp_s0);
                    var_s2_2 = temp_s2_2 + 0xC;
                    func_8004617C(temp_s2_2, 0, 1, 0, sp18 + 0x28);
                    var_s0_2 = temp_s0_2 + 0xC;
                    AddPrim(temp_s4, temp_s0_2);
                }
            }
            sp18 += 0x30;
        } while (var_s3_2 < M2C_FIELD(temp_s5, s16 *, 2));
    }
    var_s3_3 = 0;
    if (M2C_FIELD(temp_s5, s16 *, 4) > 0) {
        var_s0_3 = var_s2_2;
        do {
            var_s3_3 += 1;
            if (func_8004006C(sp18, arg1) > 0) {
                temp_v0_2 = (s32) M2C_FIELD(arg1, s32 *, 0x2C) >> M2C_FIELD(arg1, s32 *, 0x20);
                M2C_FIELD(arg1, s32 *, 0x2C) = temp_v0_2;
                if ((u32) (temp_v0_2 - 1) < 0x1BFU) {
                    M2C_FIELD(var_s0_3, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x34);
                    M2C_FIELD(var_s0_3, s32 *, 0xC) = (s32) M2C_FIELD(arg1, s32 *, 0x38);
                    M2C_FIELD(var_s0_3, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x3C);
                    M2C_FIELD(var_s0_3, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x40);
                    func_80043C80(sp18 + 0x18, M2C_FIELD(arg1, s32 *, 0x28), var_s2_2 + 4);
                    *var_s2_2 = 0x05000000;
                    temp_a1_2 = var_s0_3;
                    var_s0_3 += 0x18;
                    var_s2_2 += 0x18;
                    AddPrim(M2C_FIELD(arg1, s32 *, 0) - ((((s16) M2C_FIELD(sp18, s32 *, 0x1C) + M2C_FIELD(arg1, s32 *, 0x2C)) * 4) + 0x200), temp_a1_2);
                }
            }
            sp18 += 0x20;
        } while (var_s3_3 < M2C_FIELD(temp_s5, s16 *, 4));
    }
    var_s2 = func_80042730(var_s2_2, arg1, arg2, arg3, temp_s5, &sp18);
    var_s3_4 = 0;
    if (M2C_FIELD(temp_s5, s16 *, 8) > 0) {
        var_s0_4 = var_s2;
        do {
            var_s3_4 += 1;
            if (func_8004006C(sp18, arg1) > 0) {
                temp_t1_2 = (s32) M2C_FIELD(arg1, s32 *, 0x2C) >> M2C_FIELD(arg1, s32 *, 0x20);
                M2C_FIELD(arg1, s32 *, 0x2C) = temp_t1_2;
                if ((u32) (temp_t1_2 - 1) < 0x1BFU) {
                    temp_s4_2 = M2C_FIELD(arg1, s32 *, 0) - (((M2C_FIELD(sp18, s16 *, 0x3A) + temp_t1_2) * 4) + 0x200);
                    func_8004617C(var_s2, 0, 1, 0, &D_80077128);
                    AddPrim(temp_s4_2, var_s0_4);
                    temp_s0_3 = var_s0_4 + 0xC;
                    M2C_FIELD(temp_s0_3, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x34);
                    M2C_FIELD(temp_s0_3, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x38);
                    M2C_FIELD(temp_s0_3, s32 *, 0x20) = (s32) M2C_FIELD(arg1, s32 *, 0x3C);
                    M2C_FIELD(temp_s0_3, s32 *, 0x2C) = (s32) M2C_FIELD(arg1, s32 *, 0x40);
                    M2C_FIELD(temp_s0_3, s32 *, 0xC) = (s32) (arg3 + M2C_FIELD(sp18, s32 *, 0x30));
                    M2C_FIELD(temp_s0_3, s32 *, 0x18) = (s32) M2C_FIELD(sp18, s32 *, 0x34);
                    temp_s2_3 = var_s2 + 0xC;
                    M2C_FIELD(temp_s0_3, u16 *, 0x24) = (u16) M2C_FIELD(sp18, u16 *, 0x38);
                    M2C_FIELD(temp_s0_3, u16 *, 0x30) = (u16) M2C_FIELD(sp18, u16 *, 0x3C);
                    func_800402E4(temp_s2_3, arg1, sp18);
                    M2C_FIELD(var_s2, s32 *, 0xC) = 0x0C000000;
                    M2C_FIELD(temp_s0_3, s8 *, 7) = 0x3C;
                    temp_s0_4 = temp_s0_3 + 0x34;
                    temp_s2_4 = temp_s2_3 + 0x34;
                    AddPrim(temp_s4_2, temp_s0_3);
                    var_s2 = temp_s2_4 + 0xC;
                    func_8004617C(temp_s2_4, 0, 1, 0, sp18 + 0x40);
                    var_s0_4 = temp_s0_4 + 0xC;
                    AddPrim(temp_s4_2, temp_s0_4);
                }
            }
            sp18 += 0x48;
        } while (var_s3_4 < M2C_FIELD(temp_s5, s16 *, 8));
    }
    var_s3_5 = 0;
    if (M2C_FIELD(temp_s5, s16 *, 0xA) > 0) {
        var_s0_5 = var_s2;
        do {
            var_s3_5 += 1;
            if (func_8004006C(sp18, arg1) > 0) {
                temp_v0_3 = (s32) M2C_FIELD(arg1, s32 *, 0x2C) >> M2C_FIELD(arg1, s32 *, 0x20);
                M2C_FIELD(arg1, s32 *, 0x2C) = temp_v0_3;
                if ((u32) (temp_v0_3 - 1) < 0x1BFU) {
                    M2C_FIELD(var_s0_5, s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 0x34);
                    M2C_FIELD(var_s0_5, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x38);
                    M2C_FIELD(var_s0_5, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 0x3C);
                    M2C_FIELD(var_s0_5, s32 *, 0x20) = (s32) M2C_FIELD(arg1, s32 *, 0x40);
                    func_80040370(var_s2, arg1, sp18);
                    *var_s2 = 0x08000000;
                    temp_a1_3 = var_s0_5;
                    var_s0_5 += 0x24;
                    var_s2 += 0x24;
                    AddPrim(M2C_FIELD(arg1, s32 *, 0) - ((((s16) M2C_FIELD(sp18, s32 *, 0x34) + M2C_FIELD(arg1, s32 *, 0x2C)) * 4) + 0x200), temp_a1_3);
                }
            }
            sp18 += 0x38;
        } while (var_s3_5 < M2C_FIELD(temp_s5, s16 *, 0xA));
    }
    if (M2C_FIELD(arg1, s32 *, 0x24) != 0) {
        func_80043738();
        func_80043794();
    }
    return var_s2;
}

s32 func_8003CAB0(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 temp_s0;

    if (!(D_80173310 & arg0)) {
        sp10 = (s32) (func_800497C8() & 0x7FFF) % 11;
        temp_s0 = func_80037478(*(&D_801E9258 + (arg1 * 0x114)));
        if (temp_s0 == func_80037478(*(&D_801E9258 + (sp10 * 0x114)))) {
            return sp10;
        }
    }
    return arg1;
}

s32 func_8003E55C(s32 arg0, s32 arg1) {
    s32 temp_lo;

    temp_lo = arg1 / 1000;
    func_80048198(&D_80010A08, temp_lo / 60, temp_lo % 60, arg1 % 1000);
    return arg0;
}

void func_8003F164(void *arg0, M2C_UNK arg1, s32 arg2) {
    s16 temp_a0;
    s16 temp_a1;
    s32 temp_v0;

    if ((D_801D77D0 != 0) || (M2C_FIELD(arg0, s16 *, 2) == 0)) {
        temp_a0 = M2C_FIELD(arg0, s16 *, 0);
        if (temp_a0 >= 0) {
            func_8003AE10(temp_a0);
            M2C_FIELD(arg0, s16 *, 0) = -1;
            if (arg2 == 0) {
                D_80173360 = 4;
            }
        }
    } else if (M2C_FIELD(arg0, s16 *, 0) < 0) {
        if (arg2 != 0) {
            M2C_FIELD(arg0, s16 *, 0) = snd_play_se(arg1);
        } else {
            temp_v0 = D_80173360 - 1;
            D_80173360 = temp_v0;
            if (temp_v0 == 0) {
                M2C_FIELD(arg0, s16 *, 0) = snd_play_se(arg1);
            }
        }
        if (M2C_FIELD(arg0, s16 *, 0) >= 0) {
            goto block_11;
        }
    } else {
block_11:
        temp_a1 = M2C_FIELD(arg0, s16 *, 2);
        func_8003B1EC(M2C_FIELD(arg0, s16 *, 0), temp_a1, temp_a1);
        func_8003B118(M2C_FIELD(arg0, s16 *, 0), M2C_FIELD(arg0, s16 *, 4));
    }
}

s32 func_80045750(s32 arg0) {
    M2C_UNK var_v1;

    var_v1 = 0x03000001;
    if (arg0 != 0) {
        var_v1 = 0x03000000;
    }
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(M2C_UNK), 0x10)(var_v1);
    return 0;
}

s32 func_80047F50(s32 arg0, s32 arg1, M2C_UNK arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s16 sp10;
    s16 sp12;
    s16 sp14;
    s16 sp16;
    s32 var_v0;

    sp10 = arg3;
    sp12 = (s16) arg4;
    sp16 = (s16) arg6;
    switch (arg1) {
    case 0:
        var_v0 = arg5;
        if (arg5 < 0) {
            var_v0 = arg5 + 3;
        }
        sp14 = (s16) (var_v0 >> 2);
        break;
    case 1:
        sp14 = (s16) (arg5 / 2);
        break;
    case 2:
        sp14 = (s16) arg5;
        break;
    }
    func_80045854(&sp10, arg0);
    return func_8004788C(arg1, arg2, arg3, arg4) & 0xFFFF;
}

s32 func_80050DF8(s32 arg0, s16 arg1) {
    s32 *temp_t0;
    s32 temp_a3;
    s32 temp_v0;
    s32 var_v0;
    u8 *temp_a0;
    u8 *temp_a2;
    u8 temp_v1_2;
    u8 var_a2;
    void *temp_a0_2;
    void *temp_v1;
    void *temp_v1_3;

    temp_t0 = ((s32) (arg0 << 0x10) >> 0xE) + &D_801E90E8;
    temp_a3 = arg1 * 0xA8;
    temp_v1 = temp_a3 + *temp_t0;
    temp_a2 = M2C_FIELD(temp_v1, u8 **, 4);
    M2C_FIELD(temp_v1, u8 **, 4) = (u8 *) (temp_a2 + 1);
    var_a2 = *temp_a2;
    if (var_a2 == 0) {
        return 0;
    }
    var_v0 = arg1 << 0x10;
    if (var_a2 & 0x80) {
        var_a2 &= 0x7F;
        do {
            temp_v1_3 = temp_a3 + *temp_t0;
            temp_a0 = M2C_FIELD(temp_v1_3, u8 **, 4);
            M2C_FIELD(temp_v1_3, u8 **, 4) = (u8 *) (temp_a0 + 1);
            temp_v1_2 = *temp_a0;
            var_a2 = (var_a2 << 7) + (temp_v1_2 & 0x7F);
        } while (temp_v1_2 & 0x80);
        var_v0 = arg1 << 0x10;
    }
    temp_a0_2 = ((var_v0 >> 0x10) * 0xA8) + *(&D_801E90E8 + ((s32) (arg0 << 0x10) >> 0xE));
    temp_v0 = var_a2 * 0xA;
    M2C_FIELD(temp_a0_2, s32 *, 0x80) = (s32) (temp_v0 + M2C_FIELD(temp_a0_2, s32 *, 0x80));
    return temp_v0;
}

s32 func_80052974(s32 arg0, M2C_UNK arg1) {
    s32 var_s0;

    var_s0 = 0x7FFFFF;
loop_1:
    func_800524D8();
    if (M2C_FIELD(&D_80077615, u8 *, 0) != 0) {
        if (D_80077474 != 0) {
            func_800496C8(&D_80011568, *((D_800774CF * 4) + &D_80076C0C));
        }
        M2C_FIELD(&D_80077615, u8 *, 0) = 0U;
        func_80052410(arg1, &D_80079D98);
        return 5;
    }
    if (M2C_FIELD(&D_80077615, u8 *, -3) != 0) {
        func_80052410(arg1, &D_80079D80);
        return 2;
    }
    var_s0 -= 1;
    if (arg0 != 0) {
        return 0;
    }
    if (var_s0 == -1) {
        func_80052440(D_800774CF);
        return -1;
    }
    goto loop_1;
}

s32 func_800530A8(void *arg0) {
    if ((func_80052974(0, 0) != 2) && (D_80077474 != 0)) {
        func_800496C8(&D_800115AC, *(&D_80076C0C + (D_800774CF * 4)));
    }
    *D_800774D8 = 2;
    *D_800774E0 = M2C_FIELD(arg0, u8 *, 0);
    *D_800774E4 = M2C_FIELD(arg0, u8 *, 1);
    *D_800774D8 = 3;
    *D_800774DC = M2C_FIELD(arg0, u8 *, 2);
    *D_800774E0 = M2C_FIELD(arg0, u8 *, 3);
    *D_800774E4 = 0x20;
    return 0;
}

void func_800532C8(s32 arg0, s32 arg1, s32 arg2, M2C_UNK arg3) {
    M2C_UNK *temp_v1;
    s32 temp_v0;

    D_800774D0 = arg1;
    D_80077620 = arg2;
    D_80077618 = arg0;
loop_1:
    temp_v0 = func_80052A98(1, 0);
    if (temp_v0 != 0) {
        if (D_80077474 != 0) {
            func_800496C8(&D_800115D8, *((temp_v0 * 4) + &D_80076C80));
        }
        goto loop_1;
    }
    temp_v1 = D_801E9170;
    D_801E9170 = &func_80053390;
    D_80077628 = temp_v1;
    func_80052D14(6, 0, arg3, 0);
}

void func_80053700(u8 *arg0) {
    u8 sp10;

    func_80051EF0(1, 0, &sp10);
    *arg0 = sp10;
}

s32 func_800591F8(void) {
    s32 sp10;

    func_80055E2C(D_80173320, 0x2D, &sp10);
    return sp10;
}
