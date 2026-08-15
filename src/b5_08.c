/* b5_08.c -- batch 5, 6 functions recovered with m2c.
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

M2C_UNK func_8001CEC8(M2C_UNK);
M2C_UNK func_8001EF54(M2C_UNK);
M2C_UNK func_80021048();
M2C_UNK func_80028578(s32, M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK func_8002ED1C(M2C_UNK);
M2C_UNK func_8002FE90();
M2C_UNK func_8003A1AC(M2C_UNK);
M2C_UNK func_8003AEC0();
M2C_UNK func_80045750(M2C_UNK);
M2C_UNK func_80048198(M2C_UNK *, M2C_UNK *, u8, s16);
M2C_UNK snd_play_se(M2C_UNK, u8, u8);
M2C_UNK st_race_init();
extern M2C_UNK *D_801733D8;
extern M2C_UNK D_80010800;
extern M2C_UNK D_8001082C;
extern M2C_UNK D_80010838;
extern M2C_UNK D_80010854;
extern M2C_UNK D_80010860;
extern M2C_UNK D_8001087C;
extern M2C_UNK D_80010898;
extern M2C_UNK D_800108B4;
extern M2C_UNK D_8007732C;
extern M2C_UNK D_80077330;
extern M2C_UNK D_80173170;
extern M2C_UNK g_track_nodes_0;
extern s16 D_8007C210;
extern s16 D_8012CFF8;
extern s16 D_8012CFFA;
extern s16 D_8012CFFC;
extern s16 D_801733B8;
extern s16 D_801D34F8;
extern s16 D_801D35B2;
extern s16 D_801D35B4;
extern s16 D_801D35B6;
extern s16 D_801D35BC;
extern s16 D_801D7808;
extern s16 D_801D9060;
extern s32 D_8012CD30;
extern s32 D_8012D008;
extern s32 D_8012D0B8;
extern s32 D_8012D8F0;
extern s32 D_801732F8;
extern s32 D_80173478;
extern s32 D_801D7610;
extern s32 D_801D7618;
extern s32 D_801D77A0;
extern s32 D_801D7E70;
extern s32 D_801D7E80;
extern s32 D_801E90E0;
extern s32 D_801E9178;
extern s32 D_801E9210;
extern u16 D_8007B1E8;
extern u16 D_80173310;
extern u16 D_801D35AA;
extern u16 D_801D35AE;
extern u16 D_801D77D0;
extern u8 D_80173174;
extern u8 D_80173175;
extern u8 D_80173176;
extern u8 D_80173177;
extern u8 D_801D35A9;
s32 rcos(s16);
s32 rsin(s16, void *);

void func_8003099C(void) {
    u16 temp_v0;

    func_8001CEC8(1);
    if (D_801D77D0 == 0) {
        temp_v0 = D_80173310;
        D_80173310 = temp_v0 + 1;
        if ((temp_v0 & 0xFFFF) == 2) {
            func_80045750(1);
        }
        D_8007B1E8 += 1;
        if (D_801D35AE & 0x800) {
            D_801D7808 = D_80173174 - 0x80;
            D_8012CFF8 = (s16) D_80173175;
            D_8012CFFA = (s16) D_80173176;
            D_8012CFFC = (s16) D_80173177;
            snd_play_se(0x2D, D_80173176, D_80173177);
            D_801D34F8 = 0x24;
        }
        if (D_801D35A9 != 0x23) {
            D_801D34F8 = 0x11;
        }
    }
    func_8002FE90();
    func_8002ED1C(0);
    func_8001EF54(0x1D8);
}

void func_8003C724(void) {
    D_8012D008 = (s32) D_8007C210;
    D_8007C210 = 2;
    D_801D7E80 = D_80173478;
    D_80173478 = (s32) D_8007C210;
    D_801D7E70 = (s32) D_801733B8;
    D_801733B8 = 0;
    st_race_init();
    D_801D9060 = 3;
    D_801733D8 = &g_track_nodes_0;
    D_801E90E0 = 0x100;
    D_801D7618 = 0;
    D_801732F8 = 0;
    D_801E9210 = 1;
    func_8003AEC0();
    D_801D34F8 = 0x1A;
    func_80021048();
    D_801D77A0 = 1;
    D_801D7610 = 0;
    D_8012D0B8 = 0x1E;
    D_8012D8F0 = 2;
    func_8003A1AC(-0x80);
}

void func_8003D154(void) {
    D_8012CD30 += 1;
    D_801D34F8 = 0x19;
    D_8012D008 = (s32) D_8007C210;
    D_8007C210 = 2;
    D_801D7E80 = D_80173478;
    D_80173478 = (s32) D_8007C210;
    D_801D7E70 = (s32) D_801733B8;
    D_801733B8 = 0;
    st_race_init();
    D_801D9060 = 3;
    D_801733D8 = &g_track_nodes_0;
    D_801E90E0 = 0x100;
    D_801D7618 = 0;
    D_801732F8 = 0;
    D_801E9210 = 1;
    func_8003AEC0();
    D_801D34F8 = 0x1A;
    func_80021048();
    D_801D34F8 = 5;
}

void func_8003D7EC(void) {
    M2C_UNK sp10;
    M2C_UNK *var_a2;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    func_80028578(0x20, 0xC8, &D_80010800, 0x7F);
    if (D_801D35AE & 0x800) {
        D_801E9178 = 0;
    }
    func_80028578(0x78, 0x20, &D_8001082C, 0x64);
    func_80028578(0x20, 0x48, &D_80010838, 0x64);
    func_80028578(0x20, 0x50, &D_80010854, 0x64);
    var_s2 = 0;
    var_s1 = 0x8000;
    var_s0 = 0x78;
    do {
        var_a2 = &D_80077330;
        if (D_801D35AA & var_s1) {
            var_a2 = &D_8007732C;
        }
        func_80028578(var_s0, 0x50, var_a2, 0x64);
        var_s0 += 8;
        var_s2 += 1;
        var_s1 = var_s1 >> 1;
    } while (var_s2 < 0x10);
    func_80048198(&sp10, &D_80010860, M2C_FIELD(&D_80173170, u8 *, 4), D_801D35BC);
    func_80028578(0x20, 0x70, &sp10, 0x64);
    func_80048198(&sp10, &D_8001087C, M2C_FIELD(&D_80173170, u8 *, 5), D_801D35B2);
    func_80028578(0x20, 0x78, &sp10, 0x64);
    func_80048198(&sp10, &D_80010898, M2C_FIELD(&D_80173170, u8 *, 6), D_801D35B4);
    func_80028578(0x20, 0x80, &sp10, 0x64);
    func_80048198(&sp10, &D_800108B4, M2C_FIELD(&D_80173170, u8 *, 7), D_801D35B6);
    func_80028578(0x20, 0x88, &sp10, 0x64);
}

void *func_80044918(s16 arg0, void *arg1) {
    s32 sp24;
    s16 temp_a0;
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_t0;
    s16 temp_t1;
    s16 temp_t2;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = rcos(arg0);
    sp24 = temp_v0;
    temp_v0_2 = rsin(arg0, arg1);
    temp_a0 = M2C_FIELD(arg1, s16 *, 6);
    temp_a2 = M2C_FIELD(arg1, s16 *, 0xC);
    temp_a3 = M2C_FIELD(arg1, s16 *, 8);
    temp_t0 = M2C_FIELD(arg1, s16 *, 0xE);
    temp_t1 = M2C_FIELD(arg1, s16 *, 0xA);
    temp_t2 = M2C_FIELD(arg1, s16 *, 0x10);
    M2C_FIELD(arg1, s16 *, 6) = (s16) ((s32) ((temp_v0 * temp_a0) - (temp_v0_2 * temp_a2)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 8) = (s16) ((s32) ((temp_v0 * temp_a3) - (temp_v0_2 * temp_t0)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((s32) ((temp_v0 * temp_t1) - (temp_v0_2 * temp_t2)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 0xC) = (s16) ((s32) ((temp_v0_2 * temp_a0) + (temp_v0 * temp_a2)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) ((s32) ((temp_v0_2 * temp_a3) + (temp_v0 * temp_t0)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 0x10) = (s16) ((s32) ((temp_v0_2 * temp_t1) + (temp_v0 * temp_t2)) >> 0xC);
    return arg1;
}

void *func_80044BBC(s16 arg0, void *arg1) {
    s32 sp24;
    s16 temp_a0;
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_t0;
    s16 temp_t1;
    s16 temp_t2;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = rcos(arg0);
    sp24 = temp_v0;
    temp_v0_2 = rsin(arg0, arg1);
    temp_a0 = M2C_FIELD(arg1, s16 *, 0);
    temp_a2 = M2C_FIELD(arg1, s16 *, 6);
    temp_a3 = M2C_FIELD(arg1, s16 *, 2);
    temp_t0 = M2C_FIELD(arg1, s16 *, 8);
    temp_t1 = M2C_FIELD(arg1, s16 *, 4);
    temp_t2 = M2C_FIELD(arg1, s16 *, 0xA);
    M2C_FIELD(arg1, s16 *, 0) = (s16) ((s32) ((temp_v0 * temp_a0) - (temp_v0_2 * temp_a2)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 2) = (s16) ((s32) ((temp_v0 * temp_a3) - (temp_v0_2 * temp_t0)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 4) = (s16) ((s32) ((temp_v0 * temp_t1) - (temp_v0_2 * temp_t2)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 6) = (s16) ((s32) ((temp_v0_2 * temp_a0) + (temp_v0 * temp_a2)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 8) = (s16) ((s32) ((temp_v0_2 * temp_a3) + (temp_v0 * temp_t0)) >> 0xC);
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) ((s32) ((temp_v0_2 * temp_t1) + (temp_v0 * temp_t2)) >> 0xC);
    return arg1;
}
