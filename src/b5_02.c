/* b5_02.c -- batch 5, 59 functions recovered with m2c.
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
M2C_UNK SetDrawEnv(s32, M2C_UNK *);
M2C_UNK car_update_and_collide();
M2C_UNK func_80013338(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_800135B8(s32, M2C_UNK);
M2C_UNK func_80013D40(void *);
M2C_UNK func_800140A4(void *);
M2C_UNK func_80014280(void *);
M2C_UNK func_8001445C(void *);
M2C_UNK func_800181C8(s32, M2C_UNK, M2C_UNK *, void *);
M2C_UNK func_800186C8(s32, s32, M2C_UNK *, s32);
M2C_UNK func_8001CDBC(M2C_UNK);
M2C_UNK func_8001F098();
M2C_UNK func_8001FFD8(M2C_UNK, M2C_UNK, s32, M2C_UNK, s32);
M2C_UNK func_800217F4(s16 *, s16);
M2C_UNK func_80021DB4(void *, s32, s16);
M2C_UNK func_8002252C(s16 *, s16);
M2C_UNK func_80022F88(s16 *, s16);
M2C_UNK func_8002362C(s16 *);
M2C_UNK func_80023B2C(s16 *);
M2C_UNK func_80023FF8(s16 *);
M2C_UNK func_80024230(s16 *);
M2C_UNK func_8002483C(s16 *);
M2C_UNK func_80024E7C(s16 *, s16);
M2C_UNK func_80026794();
M2C_UNK func_80028578(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK func_80028A0C(s32, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32, s32, s32);
M2C_UNK func_8002BBA0(s32, s32);
M2C_UNK func_8002D134();
M2C_UNK func_8002E490();
M2C_UNK func_8002E528();
M2C_UNK func_8002EBF0();
M2C_UNK func_80031BD8();
M2C_UNK func_800355A4(M2C_UNK);
M2C_UNK func_800376EC(M2C_UNK);
M2C_UNK func_800377B4(s32);
M2C_UNK func_8003A1AC(M2C_UNK, s32, s32);
M2C_UNK func_8003A258(M2C_UNK);
M2C_UNK func_8003B1EC(s16, M2C_UNK, M2C_UNK);
M2C_UNK func_8003B2E4(s16, s16);
M2C_UNK func_8003B340(M2C_UNK);
M2C_UNK func_8003EAAC();
M2C_UNK func_8003FBE8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8003FC08(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_800434A0(M2C_UNK *);
M2C_UNK func_800434D0(M2C_UNK *, s32, M2C_UNK *);
M2C_UNK func_80044F64(M2C_UNK, M2C_UNK);
M2C_UNK func_80045750(M2C_UNK);
M2C_UNK func_80045790(M2C_UNK);
M2C_UNK func_80045854(u16 *, void *);
M2C_UNK func_800458B8(M2C_UNK *, void *);
M2C_UNK func_8004617C(s32, M2C_UNK, M2C_UNK, s32, M2C_UNK *);
M2C_UNK func_80047508(M2C_UNK);
M2C_UNK func_80048198(void *, M2C_UNK *, M2C_UNK);
M2C_UNK func_800490D4(M2C_UNK *);
M2C_UNK func_80049638(s32 *);
M2C_UNK func_800496C8(M2C_UNK *, s32, s32, s32, s32, s32, s32);
M2C_UNK func_800497D8();
M2C_UNK func_8004D400(s16);
M2C_UNK func_8004E380(s32, s32);
M2C_UNK func_8004E890(s32, s32);
M2C_UNK func_8004E8F0(s32, s32);
M2C_UNK func_80051114(s32, s32);
M2C_UNK func_80051688(s32, s32);
M2C_UNK func_80051800(s32, s32);
M2C_UNK func_800518E8(s32, s32);
M2C_UNK func_80051E94(M2C_UNK, void *);
M2C_UNK func_80051EF0(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_80051F8C();
M2C_UNK func_800520CC(M2C_UNK *, s16, u8 *);
M2C_UNK func_80053618(M2C_UNK, M2C_UNK);
M2C_UNK func_80055510(u16);
M2C_UNK func_80055E2C(M2C_UNK, M2C_UNK, s32 *);
M2C_UNK func_80057A24(s32 *, s16, s32);
M2C_UNK func_80057F18(s32 *, s32, s32);
M2C_UNK func_80059060(M2C_UNK);
M2C_UNK func_800590B4(s32);
extern M2C_UNK (*D_80077370)(M2C_UNK *, s32, u32);
extern M2C_UNK D_7FFFFF;
extern M2C_UNK D_80010F7C;
extern M2C_UNK D_80010FD0;
extern M2C_UNK D_80071D24;
extern M2C_UNK D_80071D44;
extern M2C_UNK D_80074358;
extern M2C_UNK D_80074D94;
extern M2C_UNK D_80075100;
extern M2C_UNK D_80075102;
extern M2C_UNK D_80075396;
extern M2C_UNK D_800769D8;
extern M2C_UNK D_80077128;
extern M2C_UNK D_80077188;
extern M2C_UNK D_80077190;
extern M2C_UNK D_800771CC;
extern M2C_UNK D_8007724C;
extern M2C_UNK D_80077274;
extern M2C_UNK D_800775C4;
extern M2C_UNK D_800797D8;
extern M2C_UNK D_800797DA;
extern M2C_UNK D_800797DC;
extern M2C_UNK D_800797DE;
extern M2C_UNK D_800797EF;
extern M2C_UNK D_80079A1A;
extern M2C_UNK D_80079A1C;
extern M2C_UNK D_80079B20;
extern M2C_UNK D_80079BA8;
extern M2C_UNK D_80079BE8;
extern M2C_UNK D_80079C28;
extern M2C_UNK D_80079C68;
extern M2C_UNK D_80079CA8;
extern M2C_UNK D_8007C218;
extern M2C_UNK D_8012CD38;
extern M2C_UNK D_8012D090;
extern M2C_UNK D_8012D950;
extern M2C_UNK D_801734E0;
extern M2C_UNK D_801D3500;
extern M2C_UNK D_801D35A8;
extern M2C_UNK D_801D75F0;
extern M2C_UNK D_801D7628;
extern M2C_UNK D_801D7670;
extern M2C_UNK D_801D7672;
extern M2C_UNK D_801D7674;
extern M2C_UNK D_801D7676;
extern M2C_UNK D_801D7678;
extern M2C_UNK D_801D9068;
extern M2C_UNK D_801D9078;
extern M2C_UNK D_801E925C;
extern M2C_UNK func_80057654;
extern s16 D_8007729C;
extern s16 D_8007729E;
extern s16 D_80077458;
extern s16 D_80077460;
extern s16 D_800775C6;
extern s16 D_800775C8;
extern s16 D_800775CA;
extern s16 D_80079B78;
extern s16 D_80079B7A;
extern s16 D_8007C210;
extern s16 D_8012CDB8;
extern s16 D_8012CFD8;
extern s16 D_8012D0B0;
extern s16 D_80173310;
extern s16 D_801733B8;
extern s16 D_801733D0;
extern s16 D_801D34F0;
extern s16 D_801D34F8;
extern s16 D_801D3542;
extern s16 D_801D3548;
extern s16 D_801D354C;
extern s16 D_801D354E;
extern s16 D_801D3552;
extern s16 D_801D3554;
extern s16 D_801D3558;
extern s16 D_801D355A;
extern s16 D_801D355E;
extern s16 D_801D3560;
extern s16 D_801D3564;
extern s16 D_801D3566;
extern s16 D_801D3570;
extern s16 D_801D3572;
extern s16 D_801D3576;
extern s16 D_801D3578;
extern s16 D_801D357C;
extern s16 D_801D357E;
extern s16 D_801D3582;
extern s16 D_801D3584;
extern s16 D_801D35AE;
extern s16 D_801D35B0;
extern s16 D_801D35B2;
extern s16 D_801D35B4;
extern s16 D_801D35B6;
extern s16 D_801D77B8;
extern s16 D_801D77C0;
extern s16 D_801D77D8;
extern s16 D_801D80B0;
extern s16 D_801D9048;
extern s16 D_801D9060;
extern s16 D_801E91B8;
extern s16 D_801E91C8;
extern s16 D_801E9250;
extern s32 *D_800773A0;
extern s32 *D_80077590;
extern s32 *D_80077594;
extern s32 *D_80077598;
extern s32 *D_8007759C;
extern s32 *D_800775A0;
extern s32 *D_80077728;
extern s32 D_80077388;
extern s32 D_8007738C;
extern s32 D_800775B0;
extern s32 D_800776F8;
extern s32 D_80077700;
extern s32 D_80077710;
extern s32 D_80079B70;
extern s32 D_8007B1C0;
extern s32 D_8007C200;
extern s32 D_8007C208;
extern s32 D_8007C240;
extern s32 D_8007C248;
extern s32 D_8007C264;
extern s32 D_8007C480;
extern s32 D_8007C4D0;
extern s32 D_8007C510;
extern s32 D_8012CD30;
extern s32 D_8012CD80;
extern s32 D_8012CDE8;
extern s32 D_8012CF50;
extern s32 D_8012CF68;
extern s32 D_8012D010;
extern s32 D_8012D020;
extern s32 D_8012D070;
extern s32 D_8012D080;
extern s32 D_8012D088;
extern s32 D_80173350;
extern s32 D_80173360;
extern s32 D_80173370;
extern s32 D_80173388;
extern s32 D_801733B0;
extern s32 D_801733D8;
extern s32 D_80173420;
extern s32 D_80173478;
extern s32 D_801734B0;
extern s32 D_801734D0;
extern s32 D_801D35A0;
extern s32 D_801D75F8;
extern s32 D_801D7608;
extern s32 D_801D7620;
extern s32 D_801D7768;
extern s32 D_801D7798;
extern s32 D_801D77C8;
extern s32 D_801D77F0;
extern s32 D_801D77F8;
extern s32 D_801D7E28;
extern s32 D_801D7E60;
extern s32 D_801D7E88;
extern s32 D_801D7EB8;
extern s32 D_801D80A8;
extern s32 D_801D80AC;
extern s32 D_801D811C;
extern s32 D_801D8120;
extern s32 D_801D8358;
extern s32 D_801D9050;
extern s32 D_801D906C;
extern s32 D_801D9070;
extern s32 D_801D907C;
extern s32 D_801D9080;
extern s32 D_801E9098;
extern s32 D_801E90E0;
extern s32 D_801E90E8;
extern s32 D_801E9168;
extern s32 D_801E9178;
extern s32 D_801E91D8;
extern s32 D_801E91E0;
extern s8 D_800772A0;
extern s8 D_80079B89;
extern s8 D_80079B8E;
extern u16 D_800776E0;
extern u16 D_80079BA0;
extern u16 D_8007B190;
extern u16 D_8007B198;
extern u16 D_8007B1B0;
extern u16 D_8007B1D8;
extern u16 D_8012CDC0;
extern u16 D_8012CDD8;
extern u16 D_8012CFF8;
extern u16 D_8012CFFA;
extern u16 D_8012CFFC;
extern u16 D_8012D8D0;
extern u16 D_8012D908;
extern u16 D_801733C0;
extern u16 D_801D35AA;
extern u16 D_801D35AC;
extern u16 D_801D7808;
extern u16 D_801E91A0;
extern u16 D_801E9F48;
extern u16 D_801E9F50;
extern u32 D_80077708;
extern u8 *D_8007C4F8;
extern u8 D_8005F560;
extern u8 D_8005F562;
extern u8 D_8005F563;
extern u8 D_800775E8;
extern u8 D_80079B88;
extern u8 D_80079B8A;
extern u8 D_80079B8D;
extern u8 D_80079B8F;
extern u8 D_80079B92;
extern u8 D_80079B93;
extern u8 D_80079B95;
extern u8 D_80079B96;
extern u8 D_80079B97;
extern u8 D_80079B99;
extern u8 D_80079B9D;
extern u8 D_80173170;
extern u8 D_80173171;
extern u8 D_80173172;
extern u8 D_80173173;
extern u8 D_80173174;
extern u8 D_80173175;
extern u8 D_80173176;
extern u8 D_80173177;
extern u8 D_80173440;
extern u8 D_801D35A9;
extern u8 D_801D35C0;
extern u8 D_801D35C1;
extern u8 D_801D35C2;
extern u8 D_801D35C3;
extern u8 D_801D75F1;
extern u8 D_801D75F2;
extern u8 D_801D75F3;
extern void *D_8007745C;
extern void *D_8007758C;
s16 func_8004C380(s16, s16, s16, M2C_UNK, s32, s32, s32);
s16 rcos(M2C_UNK);
s16 rsin(M2C_UNK);
s16 snd_play_se(M2C_UNK);
s32 VSync(M2C_UNK);
s32 func_800177B8(s16, s16, s32, s32);
s32 func_8001FDB0(s32, M2C_UNK, M2C_UNK, s32, s32);
s32 func_80021FA4(s32, s32, s32);
s32 func_80029278(s32, s32, M2C_UNK, s32, s32, s32, s32, s32, s32);
s32 func_800297D8(s32, s32, M2C_UNK, s32, s32, s32, s32, s32, s32);
s32 func_800409D4(s32, s32, s32);
s32 func_80044078();
s32 func_8004788C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_800497C8();
s32 func_80051C8C(M2C_UNK, u8 *);
s32 func_80051CAC(M2C_UNK, M2C_UNK);
s32 func_80051D14(s32);
s32 func_80052D14(s32, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_80059120(s32, s32);
u32 func_8004713C();

void func_80013494(void) {
    M2C_UNK var_a0;

    M2C_FIELD(&D_8012D090, s32 *, 0) = (s32) M2C_FIELD(&D_80071D24, s32 *, 0);
    M2C_FIELD(&D_8012D090, s32 *, 4) = (s32) M2C_FIELD(&D_80071D24, s32 *, 4);
    M2C_FIELD(&D_8012D090, s32 *, 8) = (s32) M2C_FIELD(&D_80071D24, s32 *, 8);
    M2C_FIELD(&D_8012D090, s32 *, 0xC) = (s32) M2C_FIELD(&D_80071D24, s32 *, 0xC);
    M2C_FIELD(&D_8012D090, s32 *, 0x10) = (s32) M2C_FIELD(&D_80071D24, s32 *, 0x10);
    M2C_FIELD(&D_8012D090, s32 *, 0x14) = (s32) M2C_FIELD(&D_80071D24, s32 *, 0x14);
    M2C_FIELD(&D_8012D090, s32 *, 0x18) = (s32) M2C_FIELD(&D_80071D24, s32 *, 0x18);
    M2C_FIELD(&D_8012D090, s32 *, 0x1C) = (s32) M2C_FIELD(&D_80071D24, s32 *, 0x1C);
    M2C_FIELD(&D_8007C218, s32 *, 0) = (s32) M2C_FIELD(&D_80071D44, s32 *, 0);
    M2C_FIELD(&D_8007C218, s32 *, 4) = (s32) M2C_FIELD(&D_80071D44, s32 *, 4);
    M2C_FIELD(&D_8007C218, s32 *, 8) = (s32) M2C_FIELD(&D_80071D44, s32 *, 8);
    M2C_FIELD(&D_8007C218, s32 *, 0xC) = (s32) M2C_FIELD(&D_80071D44, s32 *, 0xC);
    M2C_FIELD(&D_8007C218, s32 *, 0x10) = (s32) M2C_FIELD(&D_80071D44, s32 *, 0x10);
    M2C_FIELD(&D_8007C218, s32 *, 0x14) = (s32) M2C_FIELD(&D_80071D44, s32 *, 0x14);
    M2C_FIELD(&D_8007C218, s32 *, 0x18) = (s32) M2C_FIELD(&D_80071D44, s32 *, 0x18);
    M2C_FIELD(&D_8007C218, s32 *, 0x1C) = (s32) M2C_FIELD(&D_80071D44, s32 *, 0x1C);
    func_800434D0(&D_8012D090, M2C_FIELD(&D_80071D44, s32 *, 0x14), &D_80071D44);
    func_800434A0(&D_8007C218);
    func_8003FBE8(0x20, 0x20, 0x20);
    func_8003FC08(0, 0, 0);
    var_a0 = 0xBB8;
    if ((D_801733B8 == 0) && !(D_8012D020 & 0x400)) {
        var_a0 = 0x2710;
    }
    func_80044F64(var_a0, 0x140);
}

void func_8001483C(void *arg0) {
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1_2;
    u16 temp_v0;
    void *temp_v1;
    void *var_v1;

    car_update_and_collide();
    func_8002BBA0(D_8007C480, D_8007C248);
    func_80013D40(arg0);
    if (D_801D35A0 < M2C_FIELD(arg0, s16 *, 0xD4)) {
        var_a0 = 0;
        var_a1 = 0;
        if (D_801D35A0 > 0) {
            var_v1 = arg0;
            do {
                var_a0 += 1;
                var_a1 += M2C_FIELD(var_v1, s32 *, 0xF0);
                var_v1 += 4;
            } while (var_a0 < D_801D35A0);
        }
        temp_v1 = (D_8007C210 * 4) + ((D_801733B8 * 0x10) + ((D_8012D088 << 5) + &D_8012CD38));
        D_801D77C8 = var_a1;
        if (var_a1 < M2C_FIELD(temp_v1, s32 *, -4)) {
            M2C_FIELD(temp_v1, s32 *, -4) = var_a1;
        }
        D_801D8358 = 0;
        D_8012CF50 = 0;
        if (M2C_FIELD(arg0, s16 *, 0xCC) == 1) {
            var_a1 = 1;
            if (((D_801733C0 & 0xF) == 0xF) && (D_8007C210 == 4)) {
                D_801D77D8 = 1;
            }
            var_v1_2 = D_8007C210 - 1;
            if (D_801733B8 == 1) {
                var_v1_2 = D_8007C210 + 3;
            }
            if (!(((s16) D_801733C0 >> var_v1_2) & 1)) {
                temp_v0 = (s16) D_801733C0 | (1 << var_v1_2);
                D_801733C0 = temp_v0;
                D_801D8358 = 1;
                temp_v1_2 = temp_v0 & 0xFF;
                if (temp_v1_2 == 0xFF) {
                    D_8012CF50 = 2;
                } else if (temp_v1_2 == 0xF) {
                    D_8012CF50 = 1;
                } else {
                    D_8012CF50 = 0;
                }
            }
        }
        D_801D9060 = 4;
        D_801D75F8 = 0x78;
        func_8003A1AC(-2, var_a1, D_801D35A0);
    }
    if (D_801733B8 == 0) {
        func_800140A4(arg0);
        if (D_8007C210 >= 3) {
            func_80014280(arg0);
        }
    }
    func_8001445C(arg0);
    M2C_FIELD(arg0, s32 *, 0xD0) = (s32) M2C_FIELD(arg0, s32 *, 8);
}

void func_80018480(void) {
    s32 temp_a1;
    s32 temp_hi;

    if (D_801D35AA & 0x2000) {
        D_801D907C += 0x10;
    }
    if (D_801D35AA & 0x8000) {
        D_801D907C -= 0x10;
    }
    temp_a1 = D_801D7620 + D_8007C208;
    temp_hi = (s32) ((D_801E90E0 << 0x10) + temp_a1) % (s32) (D_801E90E0 << 8);
    D_801D7620 = temp_a1;
    D_801D7620 = temp_hi;
    func_800181C8(temp_hi, 0, &D_801D9068, &D_801D9068 + 0x10);
    D_801D906C -= 0x28;
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

void func_8001FE6C(s32 arg0) {
    s32 temp_s4;

    temp_s4 = func_8001FDB0(func_8001FDB0(func_8001FDB0(*(s32 *)0x1F800000, 0x108, 0xD8, arg0 / 100, 0x64), 0x110, 0xD8, (s32) (arg0 / 10) % 10, 0x64), 0x118, 0xD8, arg0 % 10, 0x64);
    func_8004617C(temp_s4, 0, 1, func_8004788C(0, 0, 0x140, 0) & 0xFFFF, &D_80077128);
    AddPrim(D_8012CF68 + 0xB6C, temp_s4);
    *(s32 *)0x1F800000 = temp_s4 + 0xC;
}

void func_800201B0(void) {
    func_80028578(0x10, 0x40, &D_80077188, 0x7F);
    func_8001FFD8(8, 0x48, M2C_FIELD(((D_8007C210 * 4) + ((D_801733B8 * 0x10) + ((D_8012D088 << 5) + &D_801D7628))), s32 *, -4), 0x64, 0x3E8);
    func_80028578(0x10, 0x58, &D_80077190, 0x7F);
    func_8001FFD8(8, 0x60, M2C_FIELD(((D_8007C210 * 4) + ((D_801733B8 * 0x10) + ((D_8012D088 << 5) + &D_8012CD38))), s32 *, -4), 0x64, 0x3E8);
}

void func_80025C98(void) {
    s16 *var_s1;
    s16 *var_s2;
    s16 var_s3;
    s16 var_v0;

    var_s1 = &D_801E9250;
    var_s3 = 0;
    var_s2 = &D_801E9250 + 0xE0;
    do {
        M2C_FIELD(var_s2, s32 *, -0x88) = 1;
        M2C_FIELD(var_s2, s16 *, -0x44) = 1;
        M2C_FIELD(var_s2, s16 *, -0x36) = 0;
        var_v0 = var_s3 + 1;
        if (*var_s1 == 0x25) {
            if (M2C_FIELD(var_s2, s16 *, -0x46) == -3) {
                func_80024E7C(var_s1, var_s3);
            }
            func_8002362C(var_s1);
            func_800217F4(var_s1, var_s3);
            M2C_FIELD(var_s2, s32 *, 0) = 0xA00;
            func_8002252C(var_s1, var_s3);
            func_80023B2C(var_s1);
            func_80022F88(var_s1, var_s3);
            func_80023FF8(var_s1);
            func_80024230(var_s1);
            func_8002483C(var_s1);
            var_v0 = var_s3 + 1;
        }
        var_s3 = var_v0;
        var_s2 += 0x114;
        var_s1 += 0x114;
    } while (var_v0 < 0xC);
}

s32 func_8002721C(s32 arg0) {
    s32 temp_a0;
    s32 temp_v1;

    temp_a0 = arg0 >> 8;
    temp_v1 = D_801E90E0 << 8;
    return 0x800 - func_800177B8(M2C_FIELD(((((s32) (temp_a0 + temp_v1) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA), M2C_FIELD(((((s32) (temp_a0 + (temp_v1 + 1)) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA), arg0 & 0xFF, D_801733D8);
}

s32 func_800272E8(s32 arg0) {
    s32 temp_a0;
    s32 temp_v1;

    temp_a0 = arg0 >> 8;
    temp_v1 = D_801E90E0 << 8;
    return 0x800 - func_800177B8(M2C_FIELD(((((s32) (temp_a0 + temp_v1) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA), M2C_FIELD(((((s32) (temp_a0 + (temp_v1 + 1)) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA), arg0 & 0xFF, D_801733D8);
}

void func_80028AC8(s32 arg0) {
    func_8004617C(arg0, 0, 1, func_8004788C(0, 0, 0x140, 0) & 0xFFFF, &D_80077128);
    func_80028A0C(arg0 + 0x20, 0xE8, 0x98, 0x50, 0x50, 0x48, 0x48, 0x64);
    func_80028A0C(arg0 + 0x34, 0x58, 8, 0x30, 8, 0, 0x10, 0x7E);
    func_80028A0C(arg0 + 0x48, 0x98, 8, 0x30, 8, 0x30, 0x10, 0x7E);
    func_80028A0C(arg0 + 0x5C, 0xC2, 0x18, 0x10, 0x10, 0xA0, 0xB0, 0x80);
    func_80028A0C(arg0 + 0x70, 0x120, 0xD8, 0x20, 8, 0x10, 0x60, 0x64);
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

s32 gfx_set_letterbox(s32 arg0, s32 arg1, s32 arg2, s16 arg3) {
    M2C_UNK sp10;
    u16 sp12;
    s16 sp16;
    s8 sp28;
    M2C_UNK *var_t1;
    void *temp_t2;
    void *var_t0;

    var_t1 = &sp10;
    var_t0 = (D_801D7768 * 0x22BF4) + &D_8012D950;
    temp_t2 = var_t0 + 0x50;
    do {
        M2C_FIELD(var_t1, s32 *, 0) = (s32) M2C_FIELD(var_t0, s32 *, 0);
        M2C_FIELD(var_t1, s32 *, 4) = (s32) M2C_FIELD(var_t0, s32 *, 4);
        M2C_FIELD(var_t1, s32 *, 8) = (s32) M2C_FIELD(var_t0, s32 *, 8);
        M2C_FIELD(var_t1, s32 *, 0xC) = (s32) M2C_FIELD(var_t0, s32 *, 0xC);
        var_t0 += 0x10;
        var_t1 += 0x10;
    } while (var_t0 != temp_t2);
    M2C_FIELD(var_t1, s32 *, 0) = (s32) M2C_FIELD(var_t0, s32 *, 0);
    M2C_FIELD(var_t1, s32 *, 4) = (s32) M2C_FIELD(var_t0, s32 *, 4);
    M2C_FIELD(var_t1, s32 *, 8) = (s32) M2C_FIELD(var_t0, s32 *, 8);
    sp28 = 0;
    sp16 = arg3;
    sp12 += arg2;
    SetDrawEnv(arg1, &sp10);
    AddPrim(arg0, arg1);
    return arg1 + 0x40;
}

void func_80029FB0(s32 arg0) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;

    temp_s0 = D_8012CF68 + 0xB6C;
    temp_s1 = arg0 + 0x44;
    temp_s2 = func_800297D8(temp_s0, func_800297D8(temp_s0, func_80029278(temp_s0, *(s32 *)0x1F800000, 0x7C, arg0 + 0x48, 0x48, 0x10, 0, 0x40, 0x77), 0x68, temp_s1, 0x70, 0x18, 0, 0, 0), 0x68, temp_s1, 0x70, 0x18, 0, 0, 0);
    func_8004617C(temp_s2, 0, 1, func_8004788C(0, 0, 0x140, 0) & 0xFFFF, &D_80077128);
    AddPrim(D_8012CF68 + 0xB6C, temp_s2);
    *(s32 *)0x1F800000 = temp_s2 + 0xC;
}

void func_8002ACD4(void) {
    func_800135B8(D_8005F560 == 0, 0);
    D_8007C4F8 = &D_8005F560 + 4;
    D_801D77C0 = 1;
    D_801D7E88 = 0;
    D_801D77F8 = 2;
    D_801734B0 = 1;
    D_80173478 = 2;
    D_801D77F0 = (D_8005F563 << 8) + D_8005F562;
}

void func_8002CB30(void *arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a3;
    s32 var_a1;

    temp_a3 = 0x5A - arg1;
    M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x10);
    M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x14);
    M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x18);
    M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0x1C);
    M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) (M2C_FIELD(&D_801D9068, s32 *, 4) - 0x18);
    M2C_FIELD(&D_801D9078, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x20);
    M2C_FIELD(&D_801D9078, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
    M2C_FIELD(&D_801D9078, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x28);
    M2C_FIELD(&D_801D9078, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0x2C);
    var_a1 = temp_a3 * temp_a3;
    D_801D9080 = -D_801D9080;
    M2C_FIELD(&D_801D9078, s32 *, 0) = (s32) M2C_FIELD(&D_801D9078, s32 *, 0);
    if (var_a1 < 0) {
        var_a1 += 0x3F;
    }
    temp_a0 = (var_a1 >> 6) * 3;
    M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) (M2C_FIELD(&D_801D9068, s32 *, 0) - (temp_a3 * 8));
    temp_a1 = D_801D9070;
    D_801D9070 = (temp_a3 * 2) + temp_a1;
    M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) (M2C_FIELD(&D_801D9068, s32 *, 4) - temp_a0);
    func_800186C8(temp_a0, temp_a1, &D_801D9068, temp_a3);
    func_800377B4(M2C_FIELD(arg0, s32 *, 8));
}

void func_8002E3AC(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    func_8002D134();
    D_80173310 = 0;
    D_801D34F8 = 0xB;
}

void read_pad_input(void) {
    s16 temp_t0;
    s16 temp_t1;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 var_a0;
    s32 temp_a0;
    s32 temp_v1_2;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_a0_2;
    u16 temp_v0;
    u16 temp_v1;

    D_8007B1C0 = (s32) D_80173171;
    M2C_FIELD(&D_801D35A8, u8 *, 0) = (u8) D_80173170;
    D_801D35A9 = D_80173171;
    if (D_80173170 == 0) {
        if (D_80173171 == 0x41) {
            temp_v0 = D_801D35AA;
            D_801D35AC = temp_v0;
            temp_v1 = ~((D_80173172 << 8) | D_80173173);
            D_801D35AA = temp_v1;
            D_801D35AE = temp_v1 & ~temp_v0;
            temp_a0 = ((u16) D_801D35AA >> 0xD) & 1;
            var_v0 = temp_a0;
            if (temp_v1 & 0x8000) {
                var_v0 = temp_a0 - 1;
            }
            M2C_FIELD(&D_801D35A8, u16 *, 8) = (u16) ((var_v0 * *(&D_800771CC + (D_801733D0 * 2))) + 0x80);
            M2C_FIELD(&D_801D35A8, s16 *, 0xA) = (s16) (((s32) (M2C_FIELD(&D_801D35A8, u16 *, 2) << 0x19) >> 0x1F) & 0x6A);
            M2C_FIELD(&D_801D35A8, s16 *, 0xC) = (s16) (((s32) (M2C_FIELD(&D_801D35A8, u16 *, 2) << 0x18) >> 0x1F) & 0x6A);
            M2C_FIELD(&D_801D35A8, s16 *, 0xE) = (s16) (((s32) (M2C_FIELD(&D_801D35A8, u16 *, 2) << 0x1C) >> 0x1F) & 0x6A);
        } else if (D_80173171 == 0x23) {
            D_801D35AC = D_801D35AA;
            temp_a0_2 = ~((D_80173172 << 8) | D_80173173);
            D_801D35AA = temp_a0_2;
            D_801D35B0 = (s16) D_80173174;
            temp_t0 = D_80173176 - D_8012CFFA;
            D_801D35B4 = temp_t0;
            temp_t1 = D_80173177 - D_8012CFFC;
            D_801D35B6 = temp_t1;
            temp_v0_2 = D_80173175 - D_8012CFF8;
            D_801D35B2 = temp_v0_2;
            if (temp_v0_2 & 0x8000) {
                D_801D35B2 = 0;
            }
            if (temp_t0 & 0x8000) {
                D_801D35B4 = 0;
            }
            if (temp_t1 & 0x8000) {
                D_801D35B6 = 0;
            }
            var_v0_2 = (s32) D_80173174 < 0x5E;
            if ((s32) D_80173174 >= 0xA3) {
                D_801D35AA = temp_a0_2 | 0x2000;
                var_v0_2 = (s32) D_80173174 < 0x5E;
            }
            if (var_v0_2 != 0) {
                D_801D35AA |= 0x8000;
            }
            if (D_801D35B2 >= 0x36) {
                D_801D35AA |= 0x40;
            }
            if (D_801D35B4 >= 0x36) {
                D_801D35AA |= 0x80;
            }
            if (D_801D35B6 >= 0x36) {
                D_801D35AA |= 4;
            }
            M2C_FIELD(&D_801D35A8, s16 *, 6) = (s16) (M2C_FIELD(&D_801D35A8, u16 *, 2) & ~M2C_FIELD(&D_801D35A8, u16 *, 4));
        } else {
            M2C_FIELD(&D_801D35A8, u8 *, 0) = 1U;
            D_801D35AA = 0;
            D_801D35B0 = 0x80;
            D_801D35B2 = 0;
            D_801D35B4 = 0;
            D_801D35B6 = 0;
        }
        temp_v1_2 = M2C_FIELD(&D_801D35A8, u16 *, 8) - (D_801D7808 + 0x80);
        if ((temp_v1_2 << 0x10) > 0) {
            temp_v0_3 = temp_v1_2 - *(&D_80074358 + (D_8012D0B0 * 4));
            var_a0 = temp_v0_3;
            if (temp_v0_3 & 0x8000) {
                var_a0 = 0;
            }
            temp_v1_3 = *(&D_800771CC + (D_801733D0 * 2));
            if (temp_v1_3 < var_a0) {
                var_a0 = temp_v1_3;
            }
        } else {
            temp_v0_4 = temp_v1_2 + *(&D_80074358 + (D_8012D0B0 * 4));
            var_a0 = temp_v0_4;
            if ((temp_v0_4 << 0x10) > 0) {
                var_a0 = 0;
            }
            temp_v1_4 = *(&D_800771CC + (D_801733D0 * 2));
            if (var_a0 < -temp_v1_4) {
                var_a0 = -temp_v1_4;
            }
        }
        M2C_FIELD(&D_801D35A8, s16 *, 0x14) = var_a0;
        if (M2C_FIELD(&D_801D35A8, s16 *, 0xA) >= 0x6B) {
            M2C_FIELD(&D_801D35A8, s16 *, 0xA) = 0x6A;
        }
        if (M2C_FIELD(&D_801D35A8, s16 *, 0xC) >= 0x6B) {
            M2C_FIELD(&D_801D35A8, s16 *, 0xC) = 0x6A;
        }
        if (M2C_FIELD(&D_801D35A8, s16 *, 0xE) >= 0x6B) {
            M2C_FIELD(&D_801D35A8, s16 *, 0xE) = 0x6A;
        }
    }
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

void func_80031238(void *arg0, M2C_UNK arg1, s32 arg2, s16 arg3, s32 arg4) {
    s16 var_s1;
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;

    var_s0 = arg2;
    M2C_FIELD(arg0, s8 *, 0) = 0x53;
    M2C_FIELD(arg0, s8 *, 1) = 0x43;
    M2C_FIELD(arg0, s8 *, 2) = 0x11;
    M2C_FIELD(arg0, s8 *, 3) = 1;
    func_80048198(arg0 + 4, &D_8007724C, arg1);
    M2C_FIELD(&D_800775C4, s16 *, 0) = (s16) ((var_s0 & 0xF) * 0x10);
    if (var_s0 < 0) {
        var_s0 += 0xF;
    }
    D_800775C6 = (var_s0 >> 4) + 0x1E0;
    D_800775C8 = 0x10;
    D_800775CA = 1;
    func_800458B8(&D_800775C4, arg0 + 0x60);
    func_80045790(0);
    var_s3 = 0;
    var_s2 = 0x80;
    var_s1 = arg3;
    do {
        M2C_FIELD(&D_800775C4, s16 *, 0) = var_s1;
        M2C_FIELD(&D_800775C4, s16 *, 2) = (s16) arg4;
        M2C_FIELD(&D_800775C4, s16 *, 4) = 4;
        M2C_FIELD(&D_800775C4, s16 *, 6) = 0x10;
        func_800458B8(&D_800775C4, arg0 + var_s2);
        func_80045790(0);
        var_s2 += 0x80;
        var_s3 += 1;
        var_s1 += 4;
    } while (var_s3 <= 0);
}

void func_800320E0(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    D_80173310 = 0;
    D_8007C4D0 = 0;
    D_8007C240 = 0;
    func_80031BD8();
    D_801D34F8 = 0x1F;
    D_80173370 = D_8012CFD8 + 1;
}

void func_8003247C(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    D_80173310 = 0;
    D_8007C4D0 = 0;
    D_8012D080 = 0;
    D_8007C240 = 0;
    func_80031BD8();
    D_801D34F8 = 0x21;
    D_80173370 = D_8012CFD8 + 2;
}

void func_80037B24(s32 arg0) {
    u16 sp10;
    u16 sp12;
    u16 sp14;
    u16 sp16;
    s32 *var_s0;
    s32 temp_v0;
    u16 temp_v0_2;
    u16 temp_v1;
    void *temp_s0;
    void *temp_s0_2;
    void *var_s0_2;

    var_s0 = arg0 + 4;
loop_7:
    temp_v0 = *var_s0;
    temp_s0 = var_s0 + 4;
    if (temp_v0 > 0) {
        temp_s0_2 = temp_s0 + 4;
        var_s0_2 = temp_s0_2 + 4;
        if (M2C_FIELD(temp_s0, s32 *, 4) & 8) {
            sp10 = M2C_FIELD(var_s0_2, u16 *, 4);
            sp12 = M2C_FIELD(var_s0_2, u16 *, 6);
            sp14 = M2C_FIELD(var_s0_2, u16 *, 8);
            sp16 = M2C_FIELD(var_s0_2, u16 *, 0xA);
            func_80045854(&sp10, var_s0_2 + 0xC);
            func_80045790(0);
            var_s0_2 += ((u32) M2C_FIELD(temp_s0_2, u32 *, 4) >> 2) * 4;
        }
        sp10 = M2C_FIELD(var_s0_2, u16 *, 4);
        sp12 = M2C_FIELD(var_s0_2, u16 *, 6);
        temp_v0_2 = M2C_FIELD(var_s0_2, u16 *, 8);
        sp14 = temp_v0_2;
        temp_v1 = M2C_FIELD(var_s0_2, u16 *, 0xA);
        sp16 = temp_v1;
        if (((temp_v0_2 << 0x10) > 0) && ((temp_v1 << 0x10) > 0)) {
            func_80045854(&sp10, var_s0_2 + 0xC);
            func_80045790(0);
        }
        var_s0 = temp_s0 + (((u32) temp_v0 >> 2) * 4);
        goto loop_7;
    }
}

void func_80037C30(s32 arg0) {
    func_800458B8(&D_80077274, (arg0 * 0x30000) + &D_801734E0);
    func_80045790(0);
}

void func_80037D38(s32 arg0) {
    u16 sp10;
    u16 sp12;
    u16 sp14;
    u16 sp16;
    s16 var_v0_2;
    s16 var_v0_3;
    s16 var_v1;
    s32 *temp_s3;
    s32 *var_s0;
    s32 temp_s1;
    s32 var_s0_3;
    u16 temp_a0;
    u16 temp_v0;
    u32 var_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *var_s0_2;
    void *var_s1;

    func_8002E528();
    var_s0 = arg0 + 4;
loop_19:
    temp_s1 = *var_s0;
    temp_s0 = var_s0 + 4;
    if (temp_s1 > 0) {
        var_v0 = (u32) temp_s1 >> 2;
        if (VSync(1) >= 0xC8) {
            func_8002E490();
            func_8002E528();
            var_v0 = (u32) temp_s1 >> 2;
        }
        temp_s3 = temp_s0 + (var_v0 * 4);
        temp_s0_2 = temp_s0 + 4;
        var_s0_2 = temp_s0_2 + 4;
        if (M2C_FIELD(temp_s0, s32 *, 4) & 8) {
            sp10 = M2C_FIELD(var_s0_2, u16 *, 4);
            sp12 = M2C_FIELD(var_s0_2, u16 *, 6);
            sp14 = M2C_FIELD(var_s0_2, u16 *, 8);
            sp16 = M2C_FIELD(var_s0_2, u16 *, 0xA);
            func_80045854(&sp10, var_s0_2 + 0xC);
            func_80045790(0);
            var_s0_2 += ((u32) M2C_FIELD(temp_s0_2, u32 *, 4) >> 2) * 4;
        }
        sp10 = M2C_FIELD(var_s0_2, u16 *, 4);
        sp12 = M2C_FIELD(var_s0_2, u16 *, 6);
        temp_v0 = M2C_FIELD(var_s0_2, u16 *, 8);
        sp14 = temp_v0;
        temp_a0 = M2C_FIELD(var_s0_2, u16 *, 0xA);
        sp16 = temp_a0;
        if (((s16) temp_v0 > 0) && ((s16) temp_a0 > 0)) {
            if (((s16) temp_v0 * (s16) temp_a0) >= 0x801) {
                var_v0_2 = (s16) M2C_FIELD(var_s0_2, u16 *, 0xA);
                var_s1 = var_s0_2 + 0xC;
                if (var_v0_2 < 0) {
                    var_v0_2 += 7;
                }
                sp16 = (u16) (var_v0_2 >> 3);
                var_s0_3 = 0;
                do {
                    func_80045854(&sp10, var_s1);
                    func_80045790(0);
                    func_8002E490();
                    func_8002E528();
                    var_v1 = (s16) M2C_FIELD(var_s0_2, u16 *, 0xA);
                    if (var_v1 < 0) {
                        var_v1 += 7;
                    }
                    sp12 += var_v1 >> 3;
                    var_v0_3 = (s16) M2C_FIELD(var_s0_2, u16 *, 0xA);
                    var_s0_3 += 1;
                    if (var_v0_3 < 0) {
                        var_v0_3 += 7;
                    }
                    var_s1 += ((s32) ((var_v0_3 >> 3) * (s16) sp14) / 2) * 4;
                } while (var_s0_3 < 8);
                var_s0 = temp_s3;
            } else {
                func_80045854(&sp10, var_s0_2 + 0xC);
                func_80045790(0);
                goto block_18;
            }
        } else {
block_18:
            var_s0 = temp_s3;
        }
        goto loop_19;
    }
    func_8002E490();
}

void func_80037F64(void) {
    s32 temp_v1;

    temp_v1 = *(&D_80074D94 + ((func_800497C8() & 1) * 4));
    D_801D80B0 = -1;
    D_801D811C = 0;
    D_801D8120 = 0;
    D_8012CDE8 = 0;
    D_801D80AC = temp_v1;
    D_801D80A8 = temp_v1;
}

void func_8003A1D8(s16 arg0) {
    if (D_801D9048 < arg0) {
        D_8007729C = -1;
        return;
    }
    D_8007729C = arg0;
    func_80051E94(0x16, (arg0 * 4) + &D_801D3500);
    D_800772A0 = 4;
    D_801E9098 = (s32) arg0;
}

void func_8003A2C8(void) {
    u8 sp10;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 var_a0;
    s16 var_a0_2;
    s16 var_a0_3;
    s16 var_a0_4;
    s32 temp_v0;

    if (D_8007729C != -1) {
        if (D_80173440 == 1) {
            func_8003A258(1);
            func_80051EF0(3, 0, 0);
            D_80173440 = 2;
            return;
        }
        temp_v0 = func_80051C8C(1, &sp10);
        if (temp_v0 == 1) {
            D_801734D0 = (s32) sp10;
        } else if (temp_v0 == 4) {
            D_80173440 = 0;
        } else {
            D_80173440 = temp_v0 | 0x80;
        }
        if (D_8007729E != 0) {
            temp_v0_2 = M2C_FIELD(&D_801D75F0, u8 *, 0) + D_8007729E;
            var_a0 = temp_v0_2;
            if (temp_v0_2 & 0x8000) {
                var_a0 = 0;
            }
            if ((s32) D_801D35C0 < var_a0) {
                var_a0 = (s16) D_801D35C0;
            }
            M2C_FIELD(&D_801D75F0, u8 *, 0) = (u8) var_a0;
            temp_v0_3 = M2C_FIELD(&D_801D75F0, u8 *, 1) + D_8007729E;
            var_a0_2 = temp_v0_3;
            if (temp_v0_3 & 0x8000) {
                var_a0_2 = 0;
            }
            if ((s32) D_801D35C1 < var_a0_2) {
                var_a0_2 = (s16) D_801D35C1;
            }
            M2C_FIELD(&D_801D75F0, u8 *, 1) = (u8) var_a0_2;
            temp_v0_4 = M2C_FIELD(&D_801D75F0, u8 *, 2) + D_8007729E;
            var_a0_3 = temp_v0_4;
            if (temp_v0_4 & 0x8000) {
                var_a0_3 = 0;
            }
            if ((s32) D_801D35C2 < var_a0_3) {
                var_a0_3 = (s16) D_801D35C2;
            }
            M2C_FIELD(&D_801D75F0, u8 *, 2) = (u8) var_a0_3;
            temp_v0_5 = M2C_FIELD(&D_801D75F0, u8 *, 3) + D_8007729E;
            var_a0_4 = temp_v0_5;
            if (temp_v0_5 & 0x8000) {
                var_a0_4 = 0;
            }
            if ((s32) D_801D35C3 < var_a0_4) {
                var_a0_4 = (s16) D_801D35C3;
            }
            M2C_FIELD(&D_801D75F0, u8 *, 3) = (u8) var_a0_4;
            func_800520CC(&D_801D75F0, D_8007729E, &D_801D35C0);
            if ((M2C_FIELD(&D_801D75F0, u8 *, 0) == 0) && (D_801D75F1 == 0) && (D_801D75F2 == 0) && (D_801D75F3 == 0)) {
                D_8007729E = 0;
            }
            if ((M2C_FIELD(&D_801D75F0, u8 *, 0) == D_801D35C0) && (D_801D75F1 == D_801D35C1) && (D_801D75F2 == D_801D35C2) && (D_801D75F3 == D_801D35C3)) {
                D_8007729E = 0;
            }
        }
    }
}

s32 func_8003AAD8(s16 arg0) {
    s16 *temp_a2;
    s16 temp_v0;
    s16 var_s0;
    s16 var_v0;
    s32 temp_s1;
    s32 temp_v0_2;

    temp_a2 = (arg0 * 2) + &D_80075396;
    var_s0 = 0;
    if (*temp_a2 > 0) {
        temp_s1 = arg0 * 0xC;
        do {
            temp_v0 = func_8004C380(D_801D34F0, arg0, var_s0, 0x3C, 0, (s32) *(&D_80075100 + temp_s1), (s32) *(&D_80075102 + temp_s1));
            var_v0 = var_s0 + 1;
            if (temp_v0 >= 0) {
                temp_v0_2 = temp_v0 * 0xA;
                *(&D_801D7672 + temp_v0_2) = arg0;
                *(&D_801D7674 + temp_v0_2) = var_s0;
                *(&D_801D7678 + temp_v0_2) = 0x1E00;
                *(&D_801D7676 + temp_v0_2) = 0x1E00;
                *(&D_801D7670 + temp_v0_2) = 1;
                var_v0 = var_s0 + 1;
            }
            var_s0 = var_v0;
        } while (var_v0 < *temp_a2);
    }
    return -1;
}

void func_8003B26C(s16 arg0, s16 arg1, s16 arg2) {
    func_8003B340(0);
    if (arg0 < 0xA) {
        func_8004D400(arg0);
        func_8003B340(1);
        func_8003B2E4(arg1, arg2);
    }
}

void func_8003C424(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    func_800376EC(-1);
    func_8001F098();
    func_800355A4(3);
    D_80173310 = 0;
    D_801D7E60 = 0;
    D_801D7EB8 = 0;
    D_8007C200 = 0;
    D_801D34F8 = 0x12;
}

void func_8003D518(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    D_80173310 = 0;
    D_8012D070 = 0;
    D_801E9178 = 0;
    D_80173420 = 1;
    D_801D7E28 = 0;
    D_801D34F8 = 0x14;
}

void func_8003EC5C(void) {
    func_80045750(0);
    func_80013338(0, 0, 0);
    D_80173310 = 0;
    D_801D34F8 = 0x18;
}

void func_8003EF00(void) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 temp_v0_8;
    s16 temp_v0_9;

    temp_v0 = snd_play_se(0x30);
    D_801D354C = temp_v0;
    D_801D354E = 0;
    func_8003B1EC(temp_v0, 0, 0);
    temp_v0_2 = snd_play_se(0x35);
    D_801D3570 = temp_v0_2;
    D_801D3572 = 0;
    func_8003B1EC(temp_v0_2, 0, 0);
    temp_v0_3 = snd_play_se(0x33);
    D_801D355E = temp_v0_3;
    D_801D3560 = 0;
    func_8003B1EC(temp_v0_3, 0, 0);
    temp_v0_4 = snd_play_se(0x33);
    D_801D3564 = temp_v0_4;
    D_801D3566 = 0;
    func_8003B1EC(temp_v0_4, 0, 0);
    temp_v0_5 = snd_play_se(0x36);
    D_801D3576 = temp_v0_5;
    D_801D3578 = 0;
    func_8003B1EC(temp_v0_5, 0, 0);
    temp_v0_6 = snd_play_se(0x37);
    D_801D357C = temp_v0_6;
    D_801D357E = 0;
    func_8003B1EC(temp_v0_6, 0, 0);
    temp_v0_7 = snd_play_se(0x31);
    D_801D3552 = temp_v0_7;
    D_801D3554 = 0;
    func_8003B1EC(temp_v0_7, 0, 0);
    temp_v0_8 = snd_play_se(0x32);
    D_801D3558 = temp_v0_8;
    D_801D355A = 0;
    func_8003B1EC(temp_v0_8, 0, 0);
    temp_v0_9 = snd_play_se(0x38);
    D_801D3582 = temp_v0_9;
    D_801D3584 = 0;
    func_8003B1EC(temp_v0_9, 0, 0);
    D_801D3542 = 0;
    D_801D3548 = 0;
    D_80173360 = 4;
}

s32 SquareRoot(s32 arg0) {
    s32 sp1C;
    s32 temp_a1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;

    if (arg0 == 0) {
        return 0;
    }
    temp_v1 = 8 - func_80044078();
    if (temp_v1 >= 0) {
        temp_v0 = temp_v1 >> 1;
        var_a1 = temp_v0;
        var_a2 = arg0 >> (temp_v0 * 2);
    } else {
        temp_v0_2 = (temp_v1 >> 1) + 1;
        var_a1 = temp_v0_2;
        var_a2 = arg0 << -(temp_v0_2 * 2);
    }
    temp_a1 = var_a1 - 6;
    if (temp_a1 >= 0) {
        sp1C = temp_a1;
        return func_800409D4(var_a2, temp_a1, var_a2) << temp_a1;
    }
    sp1C = temp_a1;
    return func_800409D4(var_a2, temp_a1, var_a2) >> -temp_a1;
}

void func_80046738(void) {
    u32 temp_v0;

    temp_v0 = func_8004713C();
    func_800496C8(&D_80010F7C, D_80077388, D_8007738C, (temp_v0 >> 0x1C) & 1, (temp_v0 >> 0x1A) & 1, (temp_v0 & 0x60000000) != 0, *D_800773A0);
    func_80047508(1);
}

void func_800479C8(s32 arg0) {
    D_80077370(&D_80010FD0, (arg0 & 0x3F) * 0x10, (u32) (arg0 & 0xFFFF) >> 6);
}

void SpuVoiceKeyOn(void) {
    s32 temp_v0;
    s32 var_a1;
    s32 var_a2;
    u32 temp_v1;

    temp_v1 = D_80079BA0 & 0xFFFF;
    if (temp_v1 < 0x10U) {
        var_a2 = 1 << temp_v1;
        var_a1 = 0;
    } else {
        var_a2 = 0;
        var_a1 = 1 << (temp_v1 - 0x10);
    }
    temp_v0 = D_80079BA0 * 0x18;
    *(&D_800797EF + temp_v0) = 0;
    *(&D_800797DC + temp_v0) = 0;
    *(&D_800797D8 + temp_v0) = 0;
    D_801E9F48 |= var_a2;
    D_801E9F50 |= var_a1;
}

void func_8004A4DC(s32 arg0) {
    s16 var_a1_2;
    s16 var_a2_2;
    s32 temp_v0_2;
    s32 temp_v1;
    u32 temp_a0;
    u32 temp_lo;
    u32 temp_lo_2;
    u32 var_a1;
    u32 var_a2;
    void *temp_v0;

    temp_v1 = D_80079B88 * 8;
    temp_lo = (u32) (((u32) (*(&D_80079A1A + temp_v1) * 0x81 * D_80079B92) / 127U) * D_80079B96) / 127U;
    temp_lo_2 = (u32) (((u32) (*(&D_80079A1C + temp_v1) * 0x81 * D_80079B92) / 127U) * D_80079B96) / 127U;
    if ((u8) D_80079B97 < 0x40U) {
        var_a1 = temp_lo;
        var_a2 = (u32) (temp_lo_2 * D_80079B97) >> 6;
    } else {
        var_a2 = temp_lo_2;
        var_a1 = (u32) (temp_lo * (0x7F - D_80079B97)) >> 6;
    }
    if ((u8) D_80079B93 < 0x40U) {
        var_a2 = (u32) (var_a2 * D_80079B93) >> 6;
    } else {
        var_a1 = (u32) (var_a1 * D_80079B93) >> 6;
    }
    if ((u8) D_80079B8D < 0x40U) {
        var_a2 = (u32) (D_80079B8D * var_a2) >> 6;
    } else {
        var_a1 = (u32) (var_a1 * (0x7F - D_80079B8D)) >> 6;
    }
    if (D_80077460 == 1) {
        if (var_a1 < var_a2) {
            var_a1 = var_a2;
        } else {
            var_a2 = var_a1;
        }
    }
    M2C_FIELD(D_8007745C, u16 *, 0x1AA) = (u16) ((M2C_FIELD(D_8007745C, u16 *, 0x1AA) & 0xC0FF) | (((D_80079B8A - D_80079B99) & 0x3F) << 8));
    temp_a0 = arg0 & 0xFF;
    temp_v0 = (temp_a0 * 0x10) + D_8007745C;
    M2C_FIELD(temp_v0, s16 *, 0) = (s16) var_a1;
    M2C_FIELD(temp_v0, s16 *, 2) = (s16) var_a2;
    if (temp_a0 < 0x10U) {
        var_a2_2 = 1 << temp_a0;
        var_a1_2 = 0;
    } else {
        var_a2_2 = 0;
        var_a1_2 = 1 << (temp_a0 - 0x10);
    }
    temp_v0_2 = (arg0 & 0xFF) * 0x18;
    *(&D_800797DC + temp_v0_2) = 0xA;
    *(&D_800797EF + temp_v0_2) = 1;
    D_8007B190 |= var_a2_2;
    D_8007B198 |= var_a1_2;
    if (D_80079B9D & 4) {
        D_8007B1B0 |= var_a2_2;
        D_8007B1D8 |= var_a1_2;
    } else {
        D_8007B1B0 &= ~var_a2_2;
        D_8007B1D8 &= ~var_a1_2;
    }
    M2C_FIELD(D_8007745C, s16 *, 0x194) = var_a2_2;
    M2C_FIELD(D_8007745C, s16 *, 0x196) = var_a1_2;
}

void func_8004A808(s32 arg0, s16 arg1, s16 arg2) {
    s16 var_a3;
    s16 var_t0;
    s32 temp_v0;
    u32 temp_a3;
    void *temp_v1;

    temp_a3 = arg0 & 0xFF;
    temp_v1 = (temp_a3 * 0x10) + D_8007745C;
    M2C_FIELD(temp_v1, s16 *, 0) = arg1;
    M2C_FIELD(temp_v1, s16 *, 2) = arg2;
    if (temp_a3 < 0x10U) {
        var_t0 = 1 << temp_a3;
        var_a3 = 0;
    } else {
        var_t0 = 0;
        var_a3 = 1 << (temp_a3 - 0x10);
    }
    temp_v0 = (arg0 & 0xFF) * 0x18;
    *(&D_800797EF + temp_v0) = 1;
    *(&D_800797DC + temp_v0) = 0xA;
    *(&D_800797DA + temp_v0) = 0;
    D_8007B190 |= var_t0;
    D_8007B198 |= var_a3;
    M2C_FIELD(D_8007745C, s16 *, 0x194) = var_t0;
    M2C_FIELD(D_8007745C, s16 *, 0x196) = var_a3;
}

s32 func_8004ACE4(s16 arg0, s16 arg1) {
    s32 temp_a0;
    s32 temp_v0;
    s32 var_v0;

    if ((u32) (arg0 & 0xFFFF) < 0x10U) {
        var_v0 = -1;
        if (*(&D_80079B20 + arg0) == 1) {
            temp_v0 = arg0 * 4;
            if (arg1 >= D_80077458) {
                goto block_3;
            }
            temp_a0 = *(&D_80079BE8 + temp_v0);
            D_80079B89 = (s8) arg0;
            D_80079B8E = (s8) arg1;
            D_80173388 = *(&D_80079BA8 + temp_v0);
            D_80173350 = temp_a0;
            D_801733B0 = *(&D_80079C28 + temp_v0);
            var_v0 = 0;
            D_80079B8F = M2C_FIELD(((arg1 * 0x10) + temp_a0), u8 *, 8);
            
            return var_v0;
        }
        return var_v0;
    }
block_3:
    return -1;
}

void func_8004B310(void) {
    s32 var_a0;
    s32 var_v0;
    u16 temp_a0;
    u16 temp_a1;
    u16 temp_t0;
    u16 temp_t1;

    var_a0 = 0;
    if (D_800775E8 != 0) {
        var_v0 = 0 & 0xFF;
        do {
            var_a0 += 1;
            *(&D_800797DE + (var_v0 * 0x18)) = M2C_FIELD(((var_v0 * 0x10) + D_8007745C), u16 *, 0xC);
            var_v0 = var_a0 & 0xFF;
        } while ((u32) (var_a0 & 0xFF) < (u8) D_800775E8);
    }
    temp_t1 = D_8007B190;
    temp_t0 = D_8007B198;
    D_8007B190 = 0;
    D_8007B198 = 0;
    temp_a1 = D_801E9F48 & ~temp_t1;
    D_801E9F48 = temp_a1;
    temp_a0 = D_801E9F50 & ~temp_t0;
    D_801E9F50 = temp_a0;
    M2C_FIELD(D_8007745C, u16 *, 0x18C) = temp_a1;
    M2C_FIELD(D_8007745C, u16 *, 0x18E) = temp_a0;
    M2C_FIELD(D_8007745C, u16 *, 0x188) = temp_t1;
    M2C_FIELD(D_8007745C, u16 *, 0x18A) = temp_t0;
    M2C_FIELD(D_8007745C, u16 *, 0x198) = (u16) D_8007B1B0;
    M2C_FIELD(D_8007745C, u16 *, 0x19A) = (u16) D_8007B1D8;
    D_801E9F48 = 0;
    D_801E9F50 = 0;
}

s16 func_8004BE7C(s32 arg0, s16 arg1) {
    s32 *temp_s0_2;
    s32 temp_s0;
    s32 temp_s1;

    if ((u32) (arg1 & 0xFFFF) < 0x11U) {
        if (*(&D_80079B20 + arg1) == 2) {
            temp_s0 = arg1 * 4;
            temp_s1 = *(&D_80079C68 + temp_s0);
            func_80059060(0);
            func_800590B4(temp_s1);
            temp_s0_2 = temp_s0 + &D_80079CA8;
            if (func_80059120(arg0, *temp_s0_2) == *temp_s0_2) {
                *(&D_80079B20 + arg1) = 1;
                return arg1;
            }
            goto block_4;
        }
        
        return -1;
    }
block_4:
    return -1;
}

s32 func_8004C27C(s32 arg0, s32 arg1) {
    s16 temp_v0;
    s16 temp_v0_2;
    s32 temp_a1;
    s32 var_a0;
    s32 var_a2;
    s32 var_v0;
    u16 var_v1;
    void *temp_v1;

    temp_v1 = ((D_80079B95 + (D_80079B8F * 0x10)) << 5) + D_801733B0;
    var_v0 = (arg1 & 0xFFFF) + M2C_FIELD(temp_v1, u8 *, 5);
    var_a2 = 0;
    if (var_v0 < 0) {
        var_v0 += 7;
    }
    temp_a1 = var_v0 >> 3;
    var_a0 = temp_a1;
    if (temp_a1 >= 0x10) {
        var_a2 = 1;
        var_a0 = temp_a1 - 0x10;
    }
    temp_v0 = var_a2 + ((arg0 + 0x3C) - M2C_FIELD(temp_v1, u8 *, 4));
    temp_v0_2 = (temp_v0 / 12) - 5;
    var_v1 = *(&D_800769D8 + ((((temp_v0 % 12) * 0x10) + (s16) var_a0) * 2));
    if (temp_v0_2 > 0) {
        var_v1 <<= temp_v0_2;
    } else if (temp_v0_2 < 0) {
        var_v1 = (u16) ((s32) (var_v1 & 0xFFFF) >> -temp_v0_2);
    }
    return var_v1 & 0xFFFF;
}

void func_8004D470(s16 arg0, s16 arg1) {
    s32 temp_lo;

    temp_lo = (s32) (arg0 * 0x7FFF) / 127;
    D_80079B70 = 6;
    D_80079B78 = (s16) temp_lo;
    D_80079B7A = (s16) ((s32) (arg1 * 0x7FFF) / 127);
    func_80057A24(&D_80079B70, arg1, temp_lo);
}

s32 func_8004D5AC(s16 arg0, s16 arg1) {
    s32 var_v0;
    u32 temp_v0;
    u32 temp_v0_2;

    var_v0 = func_8004ACE4(arg0, 0);
    if (var_v0 != -1) {
        if ((arg1 & 1) > 0) {
            temp_v0 = arg1 - 1;
            return M2C_FIELD(((((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1) * 0x10) + D_80173350), u16 *, 0xC) * 8;
        }
        temp_v0_2 = arg1 - 1;
        var_v0 = M2C_FIELD(((((s32) (temp_v0_2 + (temp_v0_2 >> 0x1F)) >> 1) * 0x10) + D_80173350), u16 *, 0xE) * 8;
        
        return var_v0;
    }
    return var_v0;
}

s32 func_8004D654(s16 arg0, s16 arg2) {
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_v1;
    u32 temp_v0;
    u32 temp_v0_2;

    var_v0 = func_8004ACE4(arg0, 0);
    if (var_v0 != -1) {
        temp_v1 = M2C_FIELD(((((D_80079B8F * 0x10) + arg2) << 5) + D_801733B0), u16 *, 0x16);
        if ((temp_v1 & 1) > 0) {
            temp_v0 = (s16) temp_v1 - 1;
            var_v0_2 = M2C_FIELD(((((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1) * 0x10) + D_80173350), u16 *, 0xC) << 0x13;
        } else {
            temp_v0_2 = (s16) temp_v1 - 1;
            var_v0_2 = M2C_FIELD(((((s32) (temp_v0_2 + (temp_v0_2 >> 0x1F)) >> 1) * 0x10) + D_80173350), u16 *, 0xE) << 0x13;
        }
        var_v0 = var_v0_2 >> 0x10;
    }
    return var_v0;
}

void func_8004E178(void) {
    s32 *var_s4;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;

    func_8004B310();
    var_s2 = 0;
    if (D_801E91B8 > 0) {
        var_s4 = &D_801E90E8;
        do {
            if ((1 << var_s2) & D_801D7798) {
                var_s0 = 0;
                if (D_801E91C8 > 0) {
                    var_s1 = 0;
                    do {
                        if (M2C_FIELD((var_s1 + *var_s4), s32 *, 0x90) & 1) {
                            func_8004E8F0(var_s2, var_s0);
                            if (M2C_FIELD((var_s1 + *var_s4), s32 *, 0x90) & 0x10) {
                                func_80051114(var_s2, var_s0);
                            }
                            if (M2C_FIELD((var_s1 + *var_s4), s32 *, 0x90) & 0x20) {
                                func_8004E380(var_s2, var_s0);
                            }
                            if (M2C_FIELD((var_s1 + *var_s4), s32 *, 0x90) & 0x40) {
                                func_800518E8(var_s2, var_s0);
                            }
                            if (M2C_FIELD((var_s1 + *var_s4), s32 *, 0x90) & 0x80) {
                                func_800518E8(var_s2, var_s0);
                            }
                        }
                        if (M2C_FIELD((var_s1 + *var_s4), s32 *, 0x90) & 2) {
                            func_80051800(var_s2, var_s0);
                        }
                        if (M2C_FIELD((var_s1 + *var_s4), s32 *, 0x90) & 8) {
                            func_8004E890(var_s2, var_s0);
                        }
                        var_s1 += 0xA8;
                        if (M2C_FIELD((var_s1 + *var_s4), s32 *, 0x90) & 4) {
                            func_80051688(var_s2, var_s0);
                        }
                        var_s0 += 1;
                    } while (var_s0 < D_801E91C8);
                }
            }
            var_s2 += 1;
            var_s4 += 4;
        } while (var_s2 < D_801E91B8);
    }
}

void func_80051B24(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp10;
    s32 sp20;
    s32 sp24;
    s32 sp2C;
    s32 sp30;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_v1;

    if (!(arg0 & 0xFF)) {
        temp_v1 = arg1 & 0xFF;
        if (temp_v1 == 0) {
            sp10 = 0x400;
            sp24 = arg2 & 0xFF;
        }
        if (temp_v1 == 1) {
            sp10 = 0x100;
            sp20 = arg2 & 0xFF;
        }
    }
    temp_a0 = arg0 & 0xFF;
    temp_a1 = arg1 & 0xFF;
    if (temp_a0 == 1) {
        if (temp_a1 == 0) {
            sp10 = 0x800;
            sp30 = arg2 & 0xFF;
        }
        if (temp_a1 == temp_a0) {
            sp10 = 0x200;
            sp2C = arg2 & 0xFF;
        }
    }
    func_80055E2C(0, 0x100, &sp10);
}

s32 func_80051E30(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_s0;

    temp_s0 = arg0 & 0xFF;
    if (func_80051D14(temp_s0) == 0) {
        return func_80052D14(temp_s0, arg1, arg2, 0) == 0;
    }
    return 0;
}

void func_800535A0(void) {
    func_80053618(0xF0000003, 0x20);
}

void func_800535C8(void) {
    func_80053618(0xF0000003, 0x40);
}

void func_800535F0(void) {
    func_80053618(0xF0000003, 0x40);
}

void func_800578C4(s32 arg0, u32 arg1) {
    u16 temp_a0;

    M2C_FIELD(D_8007758C, u16 *, 0x1AA) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 0xFFCF);
    M2C_FIELD(D_8007758C, u16 *, 0x1A6) = (u16) D_800776E0;
    temp_a0 = M2C_FIELD(D_8007758C, u16 *, 0x1AA) | 0x30;
    M2C_FIELD(D_8007758C, u16 *, 0x1AA) = temp_a0;
    func_80055510(temp_a0);
    D_80077700 = arg0;
    D_80077708 = arg1;
    D_80077710 = (arg1 >> 6) + ((arg1 & 0x3F) != 0);
    *D_800775A0 |= 0x900000;
    *D_8007759C |= 0x80000;
    *D_80077590 = D_80077700;
    *D_80077594 = (D_80077710 << 0x10) | 0x10;
    D_800776F8 = 1;
    func_80049638(D_8007759C);
    func_800490D4(&func_80057654);
    func_800497D8();
    *D_80077598 = 0x01000200;
}

void func_80058BE0(s32 arg0, s32 *arg1, s32 arg3) {
    s32 *var_a1;
    s32 temp_v1;
    s32 var_a2;
    s32 var_a3;

    var_a1 = arg1;
    var_a3 = arg3;
    var_a2 = 0;
    if (D_800775B0 > 0) {
        var_a3 = D_800775B0;
        var_a1 = D_80077728;
loop_2:
        temp_v1 = *var_a1;
        if (!(temp_v1 & 0x40000000)) {
            var_a2 += 1;
            if (temp_v1 == arg0) {
                *var_a1 = arg0 | 0x80000000;
            } else {
                var_a1 += 8;
                if (var_a2 < var_a3) {
                    goto loop_2;
                }
            }
        }
    }
    func_80057F18(var_a1, var_a2, var_a3);
}

void func_80021FBC(void *arg0, s16 arg1, s16 arg2) {
    s16 temp_a0;
    s16 temp_a2;
    s16 temp_s5;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 var_s0;
    s32 temp_a1;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_fp;
    s32 temp_hi;
    s32 temp_s3;
    s32 temp_v0_2;
    s32 temp_v1_5;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s2;
    s32 var_s3;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_v1_4;
    u32 temp_a0_2;
    u32 temp_a0_3;
    void *temp_s7;
    void *temp_v0;

    temp_a1 = M2C_FIELD(arg0, s32 *, 8);
    temp_fp = (s32) D_801D7608 % 3;
    temp_s7 = arg0 + 0x58;
    temp_v0 = (((s32) ((temp_a1 >> 8) + (D_801E90E0 << 8)) % (s32) D_801E90E0) * 0x14) + D_801733D8;
    temp_a2 = M2C_FIELD(temp_v0, s16 *, 0xE);
    temp_s5 = M2C_FIELD(temp_v0, s16 *, 0x12);
    temp_s3 = temp_a2 + M2C_FIELD(temp_v0, s16 *, 0x10);
    func_80021DB4(temp_s7, temp_a1, temp_a2);
    switch (arg2) {
    case 0:
        if (temp_s3 >= 0x2001) {
            temp_hi = (s32) (arg1 + temp_fp) % 3;
            if (temp_hi == 2) {
                var_s0 = -0x3C;
            } else {
                var_s0 = temp_s5;
                if (temp_hi == 1) {
                    var_s0 = 0x3C;
                }
            }
            if (arg1 == 0xB) {
                var_s0 = -0x3C;
            }
        } else {
            temp_v1 = M2C_FIELD(arg0, s16 *, 0x96);
            if (temp_v1 >= 0) {
                temp_v0_2 = *(&D_801E925C + (temp_v1 * 0x114));
                var_s0 = temp_v0_2 - 0xA;
                if (temp_v0_2 <= 0) {
                    var_s0 = temp_v0_2 + 0xA;
                }
            } else {
                temp_v1_2 = M2C_FIELD(arg0, s16 *, 0x94);
                if (temp_v1_2 == 0) {
                    temp_v1_3 = M2C_FIELD(arg0, s16 *, 0x90);
                    var_s0 = temp_s5;
                    if (temp_v1_3 == 1) {
                        if ((s16) (arg1 % 2) == temp_v1_3) {
                            var_s0 = ((s32) D_8007C510 / 3) + arg1;
                        } else {
                            var_s0 = ((s32) D_8012CD80 / 3) - arg1;
                        }
                    }
                } else {
                    if (temp_v1_2 == -1) {
                        var_a1 = D_8007C510;
                    } else {
                        var_a1 = D_8012CD80;
                    }
                    if (D_801D77B8 == 1) {
                        if (D_8007C210 == D_801D77B8) {
                            var_s0 = (s16) (var_a1 / 3);
                        } else {
                            goto block_23;
                        }
                    } else if (D_8007C210 == 4) {
block_23:
                        var_s0_2 = var_a1;
                        if (var_a1 < 0) {
                            var_s0_2 = var_a1 + 3;
                        }
                        var_s0 = (s16) (var_s0_2 >> 2);
                    } else {
                        var_s0 = (s16) ((s32) (var_a1 + ((u32) var_a1 >> 0x1F)) >> 1);
                    }
                }
            }
        }
        if (M2C_FIELD(temp_s7, s16 *, 0x4E) == 0) {
            M2C_FIELD(temp_s7, s32 *, 0x58) = (s32) var_s0;
            return;
        }
        return;
    case 1:
        if (D_801D77B8 == 0) {
            var_s3 = D_8007C510;
            var_s2 = D_8012CD80;
        } else {
            var_s3 = D_8012CD80;
            var_s2 = D_8007C510;
        }
        temp_v1_4 = M2C_FIELD(temp_s7, u16 *, 0x3E);
        temp_a0 = (s16) M2C_FIELD(temp_s7, u16 *, 0x3E);
        if (temp_a0 == 0xC) {
            var_s0_3 = D_8007C264;
        } else {
            var_s0_3 = *(&D_801E925C + (temp_a0 * 0x114));
        }
        if (var_s0_3 > 0) {
            temp_a2_2 = M2C_FIELD(arg0, s32 *, 0xC);
            var_a1_2 = var_s0_3 - 0x3C;
            if (temp_a2_2 < var_s0_3) {
                temp_a0_2 = var_s0_3 + var_s3;
                var_a0 = (s32) (temp_a0_2 + (temp_a0_2 >> 0x1F)) >> 1;
                if ((s16) temp_v1_4 != 0xC) {
                    if (var_a1_2 >= temp_a2_2) {
                        M2C_FIELD(arg0, s32 *, 0xB0) = var_a0;
                    } else {
                        goto block_46;
                    }
                } else {
                    goto block_47;
                }
            } else {
                var_v0 = var_s0_3 + var_s3;
                if (func_80021FA4(var_s0_3, var_s2, temp_a2_2) >= 0x3D) {
                    var_v0_2 = var_s0_3 + var_s2;
                    goto block_50;
                }
                goto block_51;
            }
        } else {
            temp_a2_3 = M2C_FIELD(arg0, s32 *, 0xC);
            var_a1_2 = var_s0_3 + 0x3C;
            if (var_s0_3 < temp_a2_3) {
                temp_a0_3 = var_s0_3 + var_s2;
                var_a0 = (s32) (temp_a0_3 + (temp_a0_3 >> 0x1F)) >> 1;
                if (((s16) temp_v1_4 != 0xC) && (temp_a2_3 < var_a1_2)) {
block_46:
                    M2C_FIELD(arg0, s32 *, 0xB0) = var_a1_2;
                } else {
block_47:
                    M2C_FIELD(arg0, s32 *, 0xB0) = var_a0;
                }
            } else {
                var_v0 = var_s0_3 + var_s2;
                if (func_80021FA4(var_s0_3, var_s3, temp_a2_3) >= 0x3D) {
                    var_v0_2 = var_s0_3 + var_s3;
block_50:
                    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (var_v0_2 / 2);
                } else {
block_51:
                    M2C_FIELD(arg0, s32 *, 0xB0) = (s32) (var_v0 / 2);
                    M2C_FIELD(arg0, s16 *, 0xA2) = 3;
                }
            }
        }
        var_a1_3 = -0xA;
        if (D_801D77B8 == 0) {
            var_a1_3 = 0xA;
        }
        temp_v1_5 = M2C_FIELD(arg0, s32 *, 0xB0);
        if (((D_8012CD80 - var_a1_3) < temp_v1_5) || (temp_v1_5 < (var_a1_3 + D_8007C510))) {
            M2C_FIELD(arg0, s16 *, 0xA2) = 4;
            M2C_FIELD(arg0, s32 *, 0xB0) = 0;
            M2C_FIELD(arg0, s16 *, 0x9A) = -1;
        }
        break;
    }
}

s32 func_8005373C(void) {
    M2C_UNK *var_s0;
    s32 temp_v0;
    s32 var_v0;

    var_s0 = &D_7FFFFF;
    func_80051F8C();
loop_1:
    temp_v0 = func_80051CAC(1, 0);
    var_v0 = temp_v0 == 0;
    if (temp_v0 > 0) {
        if (var_s0 == (M2C_UNK *)-1) {
            var_v0 = 0;
        } else {
            goto loop_1;
        }
    }
    return var_v0;
}
