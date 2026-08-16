/* cand_func_8003D9B0.c -- one candidate function, decompiled by m2c.
 *
 * Second run at the seventy-four that matched under none of the five
 * pipelines. The C is unchanged: the point is not to hope for a different
 * result, it is that tools/whydiff.py now exists. These get built and
 * diagnosed before anything is sent back to INCLUDE_ASM, so that we learn
 * *how* they miss rather than only that they do.
 *
 * One function per file: GCC 2.7.2 allocates registers across the whole
 * translation unit, so a candidate measured alone is measured on its own
 * merits.
 */
#include "m2c_macros.h"

extern M2C_UNK D_80010800;
extern M2C_UNK D_800108D0;
extern M2C_UNK D_800108E4;
extern M2C_UNK D_800108F0;
extern M2C_UNK D_80010908;
extern M2C_UNK D_80010914;
extern M2C_UNK D_8001092C;
extern M2C_UNK D_80010938;
extern M2C_UNK D_800753F8;
extern M2C_UNK D_80077334;
extern M2C_UNK D_8007733C;
extern M2C_UNK D_8007C488;
extern M2C_UNK D_8007C48C;
extern M2C_UNK D_8012CD38;
extern u16 D_801D35AE;
extern M2C_UNK D_801D7628;
extern s32 D_801E9178;

void func_8003D9B0(void) {
    M2C_UNK sp18;
    M2C_UNK sp40;
    M2C_UNK sp68;
    M2C_UNK sp90;
    s32 temp_s0;
    s32 temp_v0;
    s32 var_a1;
    s32 var_s0;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s2;
    s32 var_s2_2;
    void *temp_s0_2;

    func_80028578(0x20, 0xC8, &D_80010800, 0x7F);
    if (D_801D35AE & 0x800) {
        D_801E9178 = 0;
    }
    func_80028578(0x58, 0x20, &D_800108D0, 0x64);
    var_s1 = 0;
    var_s2 = 0x30;
    var_s0 = 0;
    do {
        func_80048198(&sp18, &D_800108E4, var_s1, func_8003E55C(&sp40, *(&D_8007C48C + var_s0)), var_s0 + &D_8007C488);
        func_80028578(0x20, var_s2, &sp18, 0x64);
        var_s2 += 8;
        var_s1 += 1;
        var_s0 += 0xC;
    } while (var_s1 < 6);
    var_s1_2 = 0;
    var_s2_2 = 0x78;
    do {
        temp_s0 = var_s1_2 << 5;
        temp_s0_2 = func_8003E55C(&sp40, temp_s0 + &D_8012CD38);
        func_80048198(&sp18, &D_800108E4, var_s1_2, temp_s0_2, func_8003E55C(&sp68, temp_s0 + &D_801D7628));
        func_80028578(0x20, var_s2_2, &sp18, 0x64);
        var_s1_2 += 1;
        var_s2_2 += 8;
    } while (var_s1_2 < 4);
    if (D_801D35AE & 0x1000) {
        func_80048198(&D_800753F8, &D_800108F0, func_800496B8(&D_80077334));
    }
    if (D_801D35AE & 0x4000) {
        temp_v0 = func_800497E8(&D_80010908, 0x10200);
        func_80048198(&D_800753F8, &D_80010914, temp_v0, func_80049648(temp_v0));
    }
    if (D_801D35AE & 0x8000) {
        var_s1_3 = 0;
        if (func_80049818(&D_8007733C, &sp90) != 0) {
            var_a1 = 0;
            do {
                var_s1_3 += 1;
                func_800496C8(&D_8001092C, var_a1, &sp90);
                var_a1 = var_s1_3;
            } while (func_80049798(&sp90) != 0);
        } else {
            func_800496C8(&D_80010938);
        }
    }
    func_80028578(0x10, 0xA0, &D_800753F8, 0x64);
}
