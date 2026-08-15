/* b5_10.c -- batch 5, 3 functions recovered with m2c.
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
M2C_UNK func_80025D9C(M2C_UNK);
M2C_UNK func_80028578(M2C_UNK, M2C_UNK, s8 *, M2C_UNK);
M2C_UNK func_800355A4(M2C_UNK);
M2C_UNK func_800376EC(M2C_UNK);
M2C_UNK func_8003A1AC(M2C_UNK);
M2C_UNK func_8003A640();
M2C_UNK func_8003AEC0(M2C_UNK);
M2C_UNK func_8003B4C4();
M2C_UNK func_80044F64(M2C_UNK, M2C_UNK);
M2C_UNK func_80045750(M2C_UNK);
extern s16 D_800775CC;
extern s16 D_8007C210;
extern s16 D_8012CDB8;
extern s16 D_80173310;
extern s16 D_801733B8;
extern s16 D_801D34F8;
extern s16 D_801D9060;
extern s32 *D_8012CF98;
extern s32 D_8007565C;
extern s32 D_8007C4C8;
extern s32 D_8012CF60;
extern s32 D_8012CFA0;
extern s32 D_8012D088;
extern s32 D_80173138;
extern s32 D_801733C8;
extern s32 D_80173420;
extern s32 D_801D35D8;
extern s32 D_801D77C8;
extern s32 D_801E9178;
extern s8 D_80010800;
extern s8 D_80010954;
extern s8 D_80077344;
extern s8 D_801D7770;
extern s8 D_801D7771;
extern s8 D_801D7772;
extern s8 D_801D7773;
extern u16 D_801D35AE;
s16 snd_play_se(s32);

void func_8003BA88(void) {
    if ((D_8012D088 != 0) || (D_801733B8 != 0) || (D_8007C210 != 4) || (D_8007C4C8 < D_801D77C8)) {
        func_8003B4C4();
        return;
    }
    func_80045750(0);
    func_80013338(0x18, 0x30, 0x88);
    func_800355A4(5);
    D_80173310 = 0;
    D_8012CF60 = 0;
    D_801D35D8 = 0x1480;
    D_80173138 = 0;
    D_801D7770 = 0x41;
    D_801D7771 = 0x41;
    D_801D7772 = 0x41;
    D_801D7773 = 0;
    D_801D34F8 = 0xE;
    func_8003A640();
    func_8003A1AC(0x7F);
}

void func_8003DC8C(void) {
    s8 sp88;
    s8 sp89;
    s8 sp8A;
    s8 sp8B;

    if ((D_801D35AE & 0x8000) && (D_80173420 >= 2)) {
        D_80173420 -= 1;
    }
    if ((D_801D35AE & 0x2000) && (D_80173420 < 0x39)) {
        D_80173420 += 1;
    }
    if (D_801D35AE & 0x40) {
        D_800775CC = snd_play_se(D_80173420);
    }
    if (D_801D35AE & 0x80) {
        func_8003AEC0(0x20);
    }
    func_80028578(0x20, 0xC8, &D_80010800, 0x7F);
    if (D_801D35AE & 0x800) {
        D_801E9178 = 0;
    }
    func_80028578(0x58, 0x20, &D_80010954, 0x64);
    sp8B = 0;
    sp88 = ((s32) D_80173420 / 100) + 0x30;
    sp8A = ((s32) D_80173420 % 10) + 0x30;
    sp89 = ((s32) ((s32) D_80173420 / 10) % 10) + 0x30;
    func_80028578(0x60, 0x30, &D_80077344, 0x64);
    func_80028578(0x80, 0x30, &sp88, 0x64);
}

void func_8003F3D4(void) {
    M2C_UNK var_a0;

    func_80045750(0);
    func_80013338(0, 0, 0);
    D_801D9060 = 3;
    func_80013494();
    func_80025D9C(4);
    func_80044F64(0xBB8, 0x140);
    func_800355A4(5);
    var_a0 = 0x11700;
    if (D_8007C210 < 3) {
        var_a0 = 0xA700;
    }
    func_800376EC(var_a0);
    D_8012CF98 = &D_8007565C;
    D_8012CDB8 = 0x180;
    D_80173310 = 0;
    D_801D34F8 = 0x26;
    D_801733C8 = D_8007565C << 8;
    func_8003A640();
    func_8003A1AC(0x7F);
    D_8012CFA0 = 0;
}
