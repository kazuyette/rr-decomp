/* b5_01.c -- batch 5, 108 functions recovered with m2c.
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
M2C_UNK SetDrawEnv(s32, void *);
M2C_UNK SpuVoiceKeyOn(M2C_UNK, s32);
M2C_UNK VSync(M2C_UNK);
M2C_UNK car_update_and_collide(M2C_UNK *);
M2C_UNK func_80012C14();
M2C_UNK func_80013184();
M2C_UNK func_80013240();
M2C_UNK func_80013338(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_80013494();
M2C_UNK func_800135B8(s32, s16);
M2C_UNK func_800163E4();
M2C_UNK func_80018480();
M2C_UNK func_800186C8();
M2C_UNK func_80018A9C();
M2C_UNK func_8001AA60(M2C_UNK *);
M2C_UNK func_8001CDBC(M2C_UNK);
M2C_UNK func_8001CE0C();
M2C_UNK func_80021048();
M2C_UNK func_80022B4C(void *, u32 *, s32 *);
M2C_UNK func_80022C40(void *, u32 *, s32 *);
M2C_UNK func_80023A8C(void *, s32, s32);
M2C_UNK func_80025D9C(s32);
M2C_UNK func_80028578(s8 *);
M2C_UNK func_8002AD68();
M2C_UNK func_8002AE14(s32, M2C_UNK *, M2C_UNK *);
M2C_UNK func_8002E6A8(s16, s16);
M2C_UNK func_80030DBC();
M2C_UNK func_800313E4(M2C_UNK *);
M2C_UNK func_80032948(M2C_UNK *, M2C_UNK *);
M2C_UNK func_80032E30();
M2C_UNK func_80032F50(M2C_UNK, M2C_UNK *);
M2C_UNK func_800355A4(M2C_UNK);
M2C_UNK func_800376EC(s32);
M2C_UNK func_80037F64();
M2C_UNK func_80037FD0();
M2C_UNK func_80038B80();
M2C_UNK func_80039034();
M2C_UNK func_80039734();
M2C_UNK func_8003A1D8(s32);
M2C_UNK func_8003B26C(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8003EE20();
M2C_UNK func_8003EF00();
M2C_UNK func_8003F0C0(M2C_UNK *);
M2C_UNK func_8003F164(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_8003FC08(u8, u8, u8);
M2C_UNK func_8003FCC0(s32);
M2C_UNK func_8003FCCC(M2C_UNK);
M2C_UNK func_8004059C(s32, M2C_UNK *, s32 *);
M2C_UNK func_80042E08(M2C_UNK *, s32 *, s32);
M2C_UNK func_80043204(M2C_UNK *, M2C_UNK *);
M2C_UNK func_80043470(M2C_UNK *);
M2C_UNK func_800434A0(s32 *);
M2C_UNK func_80043500(M2C_UNK *);
M2C_UNK func_800439D8(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, s32, s32);
M2C_UNK func_800445D4(M2C_UNK *, M2C_UNK *);
M2C_UNK func_80045750(M2C_UNK);
M2C_UNK func_80045790(M2C_UNK);
M2C_UNK func_80045854(s16 *, s32 *);
M2C_UNK func_800458B8(s16 *, s32 *);
M2C_UNK func_80045B78(s32 *);
M2C_UNK func_80046738();
M2C_UNK func_80047AF8(void *, M2C_UNK);
M2C_UNK func_80047B20(void *, M2C_UNK);
M2C_UNK func_80047BAC(void *);
M2C_UNK func_80047BD4(void *);
M2C_UNK func_80047BE8();
M2C_UNK func_80047C10(void *);
M2C_UNK func_80047C60(void *);
M2C_UNK func_80047C88(void *);
M2C_UNK func_80048198(void *, M2C_UNK *, s32);
M2C_UNK func_80048F80();
M2C_UNK func_800490D4(M2C_UNK);
M2C_UNK func_80049164(M2C_UNK);
M2C_UNK func_80049638();
M2C_UNK func_80049648(s32);
M2C_UNK func_80049688(M2C_UNK *, M2C_UNK, void *, M2C_UNK);
M2C_UNK func_800496C8(M2C_UNK *);
M2C_UNK func_80049718(M2C_UNK, s32, M2C_UNK);
M2C_UNK func_80049748();
M2C_UNK func_800497A8(M2C_UNK);
M2C_UNK func_800497D8();
M2C_UNK func_800497F8();
M2C_UNK func_80049808();
M2C_UNK func_8004986C(M2C_UNK, s32, u16 *, u16 *);
M2C_UNK func_8004A808(s16, s32, s32, s32, s32);
M2C_UNK func_8004A8D0(s32, s32);
M2C_UNK func_8004AA64(s16, s16, u8, u8);
M2C_UNK func_8004ADB8(s16, s16, u8, s32, s32, s32);
M2C_UNK func_8004C74C(s32, s16, s16, s16, s32);
M2C_UNK func_8004C8AC(s16, s16, s16, s32, s32, s32, s32);
M2C_UNK func_8004D3C0(s16);
M2C_UNK func_8004D3E0(s16);
M2C_UNK func_8004D470(s16, s16, s16);
M2C_UNK func_8004DC18();
M2C_UNK func_8004DF1C(s32);
M2C_UNK func_8004DF2C(s32);
M2C_UNK func_8004DF3C(s32);
M2C_UNK func_8004DF4C(M2C_UNK);
M2C_UNK func_8004DFC4(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8004EADC(s16, s16);
M2C_UNK func_80051B24(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_80051BC4();
M2C_UNK func_80051CCC(M2C_UNK *);
M2C_UNK func_80051CE4(M2C_UNK *);
M2C_UNK func_80051CFC(M2C_UNK *);
M2C_UNK func_80051E30(M2C_UNK, s8 *, M2C_UNK);
M2C_UNK func_80051EF0(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8005223C(s32, s8 *);
M2C_UNK func_80052974();
M2C_UNK func_80052BF0();
M2C_UNK func_800530A8();
M2C_UNK func_80053618(M2C_UNK, M2C_UNK);
M2C_UNK func_80053630();
M2C_UNK func_8005486C(M2C_UNK, s32);
M2C_UNK func_8005495C(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_80055570();
M2C_UNK func_80055E2C(M2C_UNK, M2C_UNK, s32 *);
M2C_UNK func_80057F18(void *, s32, s32, void *);
M2C_UNK func_80058BE0(s32);
M2C_UNK func_80058D0C();
M2C_UNK snd_play_se(M2C_UNK);
extern M2C_UNK (*D_80077370)(M2C_UNK *, s32, s32, s32);
extern M2C_UNK *D_8007C248;
extern M2C_UNK *D_801733D8;
extern M2C_UNK D_80000000;
extern M2C_UNK D_800106FC;
extern M2C_UNK D_8001070C;
extern M2C_UNK D_80010EF4;
extern M2C_UNK D_80010F44;
extern M2C_UNK D_800111A8;
extern M2C_UNK D_8005922A;
extern M2C_UNK D_8005E90C;
extern M2C_UNK D_8005E914;
extern M2C_UNK D_8007307C;
extern M2C_UNK D_8007405C;
extern M2C_UNK D_80074DBC;
extern M2C_UNK D_80074EBC;
extern M2C_UNK D_800750DC;
extern M2C_UNK D_80075100;
extern M2C_UNK D_80075102;
extern M2C_UNK D_80075104;
extern M2C_UNK D_80075108;
extern M2C_UNK D_80075460;
extern M2C_UNK D_80077154;
extern M2C_UNK D_800771A0;
extern M2C_UNK D_80078248;
extern M2C_UNK D_80079788;
extern M2C_UNK D_800797A8;
extern M2C_UNK D_800797D8;
extern M2C_UNK D_800797DC;
extern M2C_UNK D_800797DE;
extern M2C_UNK D_800797E0;
extern M2C_UNK D_800797E2;
extern M2C_UNK D_800797E4;
extern M2C_UNK D_800797E6;
extern M2C_UNK D_800797E8;
extern M2C_UNK D_800797EA;
extern M2C_UNK D_800797EF;
extern M2C_UNK D_80079A1A;
extern M2C_UNK D_80079A1C;
extern M2C_UNK D_80079B20;
extern M2C_UNK D_80079B30;
extern M2C_UNK D_80079C68;
extern M2C_UNK D_8007C258;
extern M2C_UNK D_8007C268;
extern M2C_UNK D_8007C278;
extern M2C_UNK D_8007C2B8;
extern M2C_UNK D_8007C488;
extern M2C_UNK D_8007C520;
extern M2C_UNK D_8012D0C8;
extern M2C_UNK D_8012E4C0;
extern M2C_UNK D_80173170;
extern M2C_UNK D_80173188;
extern M2C_UNK D_80173448;
extern M2C_UNK D_801734E0;
extern M2C_UNK D_801A34E0;
extern M2C_UNK D_801D3540;
extern M2C_UNK D_801D3546;
extern M2C_UNK D_801D354C;
extern M2C_UNK D_801D3552;
extern M2C_UNK D_801D3558;
extern M2C_UNK D_801D355E;
extern M2C_UNK D_801D3564;
extern M2C_UNK D_801D3570;
extern M2C_UNK D_801D3576;
extern M2C_UNK D_801D357C;
extern M2C_UNK D_801D3582;
extern M2C_UNK D_801D7670;
extern M2C_UNK D_801D7672;
extern M2C_UNK D_801D7674;
extern M2C_UNK D_801D7676;
extern M2C_UNK D_801D7678;
extern M2C_UNK D_801D7810;
extern M2C_UNK D_801D7C10;
extern M2C_UNK D_801D7D10;
extern M2C_UNK D_801D9068;
extern M2C_UNK D_801D9078;
extern M2C_UNK D_801D9098;
extern M2C_UNK D_801E90E8;
extern M2C_UNK D_801E91F0;
extern M2C_UNK D_801E9250;
extern M2C_UNK D_801E92D8;
extern M2C_UNK D_801E9E2C;
extern M2C_UNK func_8004E178;
extern M2C_UNK func_800535A0;
extern M2C_UNK func_800535C8;
extern M2C_UNK func_800535F0;
extern M2C_UNK g_track_nodes_0;
extern M2C_UNK g_track_nodes_1;
extern M2C_UNK g_track_nodes_2;
extern s16 D_8007728E;
extern s16 D_800772FC;
extern s16 D_80077460;
extern s16 D_80079BA0;
extern s16 D_80079BA2;
extern s16 D_80079BA4;
extern s16 D_8007C210;
extern s16 D_8007C250;
extern s16 D_8007C32C;
extern s16 D_8007C508;
extern s16 D_8012CDB8;
extern s16 D_8012CF58;
extern s16 D_8012CFB8;
extern s16 D_8012CFD8;
extern s16 D_8012D000;
extern s16 D_8012D018;
extern s16 D_8012D8D0;
extern s16 D_8012D908;
extern s16 D_80173150;
extern s16 D_80173164;
extern s16 D_80173310;
extern s16 D_80173390;
extern s16 D_80173398;
extern s16 D_801733B8;
extern s16 D_801D34F0;
extern s16 D_801D3544;
extern s16 D_801D354A;
extern s16 D_801D3584;
extern s16 D_801D3586;
extern s16 D_801D35D0;
extern s16 D_801D77B8;
extern s16 D_801D77D0;
extern s16 D_801D9060;
extern s16 D_801E91A0;
extern s32 **D_80077398;
extern s32 *D_80077390;
extern s32 *D_80077394;
extern s32 *D_8007739C;
extern s32 *D_800773A0;
extern s32 *D_800773B0;
extern s32 *D_8007744C;
extern s32 D_80074064;
extern s32 D_800747DC;
extern s32 D_800747E0;
extern s32 D_80075440;
extern s32 D_80075450;
extern s32 D_80077374;
extern s32 D_80077378;
extern s32 D_8007737C;
extern s32 D_8007745C;
extern s32 D_800775B0;
extern s32 D_800775B4;
extern s32 D_800775B8;
extern s32 D_80077600;
extern s32 D_80077668;
extern s32 D_80077670;
extern s32 D_80077678;
extern s32 D_80077688;
extern s32 D_80077690;
extern s32 D_80077698;
extern s32 D_800776A0;
extern s32 D_800776C0;
extern s32 D_800776C8;
extern s32 D_800776F0;
extern s32 D_800776F8;
extern s32 D_80077720;
extern s32 D_8007B1A0;
extern s32 D_8007C208;
extern s32 D_8007C260;
extern s32 D_8007C2F8;
extern s32 D_8007C338;
extern s32 D_8007C480;
extern s32 D_8007C4F8;
extern s32 D_8012CD20;
extern s32 D_8012CD28;
extern s32 D_8012CD38;
extern s32 D_8012CD58;
extern s32 D_8012CD78;
extern s32 D_8012CD88;
extern s32 D_8012CDC8;
extern s32 D_8012CDE0;
extern s32 D_8012CF50;
extern s32 D_8012CF68;
extern s32 D_8012CFE8;
extern s32 D_8012D020;
extern s32 D_8012D078;
extern s32 D_8012D088;
extern s32 D_8012D0C0;
extern s32 D_8012D900;
extern s32 D_80173338;
extern s32 D_80173350;
extern s32 D_801733A0;
extern s32 D_801733B0;
extern s32 D_80173468;
extern s32 D_80173470;
extern s32 D_801D34E8;
extern s32 D_801D35A0;
extern s32 D_801D7628;
extern s32 D_801D7648;
extern s32 D_801D7668;
extern s32 D_801D7760;
extern s32 D_801D7798;
extern s32 D_801D77F0;
extern s32 D_801D7E20;
extern s32 D_801D7E68;
extern s32 D_801D7E78;
extern s32 D_801D7EB0;
extern s32 D_801D7F58;
extern s32 D_801D8128;
extern s32 D_801D9028;
extern s32 D_801E9098;
extern s32 D_801E90B0;
extern s32 D_801E90C8;
extern s32 D_801E90E0;
extern s32 D_801E9180;
extern s32 D_801E9188;
extern s32 D_801E9210;
extern s32 D_801E9218;
extern s32 D_801E9228;
extern s32 D_801E9238;
extern s8 D_80073124;
extern s8 D_80073126;
extern s8 D_80073127;
extern s8 D_80073129;
extern s8 D_8007312A;
extern s8 D_8007312B;
extern s8 D_80077608;
extern s8 D_80079B98;
extern s8 D_80173428;
extern s8 D_801D35C0;
extern s8 D_801D35C1;
extern s8 D_801D35C2;
extern s8 D_801D35C3;
extern u16 *D_80077444;
extern u16 D_80076B5C;
extern u16 D_80076B6C;
extern u16 D_800771A4;
extern u16 D_800775F0;
extern u16 D_800775F8;
extern u16 D_80079B9E;
extern u16 D_8007B190;
extern u16 D_8007B198;
extern u16 D_8007B1B0;
extern u16 D_8007B1D8;
extern u16 D_8007B1E8;
extern u16 D_8007C25A;
extern u16 D_801733C0;
extern u16 D_801D34F8;
extern u16 D_801D35AA;
extern u16 D_801D35AE;
extern u16 D_801D77F8;
extern u16 D_801D7E88;
extern u8 D_800775E8;
extern u8 D_80079B88;
extern u8 D_80079B8C;
extern u8 D_80079B8D;
extern u8 D_80079B8F;
extern u8 D_80079B92;
extern u8 D_80079B93;
extern u8 D_80079B95;
extern u8 D_80079B96;
extern u8 D_80079B97;
extern u8 D_80079B9D;
extern u8 D_80173152;
extern u8 D_80173153;
extern u8 D_80173154;
extern u8 D_801734A8;
extern u8 D_801D7E50;
extern void *D_8007758C;
extern void *D_800775AC;
extern void *D_80077728;
extern void *D_80173180;
extern void *D_80173388;
extern void *g_gpu_device;
s16 func_8004788C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
s16 func_8004BA7C(M2C_UNK);
s16 func_8004BE7C(s32, s16);
s16 func_8004C27C(s16, s16, s32, s32);
s16 func_8004C380(s16, s16, M2C_UNK, M2C_UNK, s32, s32, s32);
s32 SquareRoot(s32, s32, s32);
s32 func_800177B8(s32, s32, s32);
s32 func_800187A0(s32, s32, s32, s32);
s32 func_8001B2D4(void *, void *);
s32 func_8001D3B8(s32, s32, s32, M2C_UNK, M2C_UNK *);
s32 func_8002B974(s32, s32);
s32 func_80031840(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK *, s32);
s32 func_80033FBC(s32, M2C_UNK, M2C_UNK *, M2C_UNK);
s32 func_80034050(s32, M2C_UNK, M2C_UNK *, M2C_UNK);
s32 func_8003446C(s32, M2C_UNK, M2C_UNK *, M2C_UNK);
s32 func_800397A4(s32 *);
s32 func_800397FC(s32 *);
s32 func_8003A678(M2C_UNK *, M2C_UNK *);
s32 func_800459C0(M2C_UNK *, void *);
s32 func_80046430(M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_800465DC(s32);
s32 func_80049708(M2C_UNK *, M2C_UNK *);
s32 func_800497C8();
s32 func_800497E8(M2C_UNK *, M2C_UNK);
s32 func_80049AF4(M2C_UNK);
s32 func_8004ACE4(s16, s16);
s32 func_8004DF5C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *);
s32 func_80050DF8(s16, s16);
s32 func_80052368(s8 *);
s32 func_80052D14(M2C_UNK, s8 *, M2C_UNK, M2C_UNK);
s32 func_800532C8(M2C_UNK, s32, M2C_UNK, M2C_UNK);
s32 func_80053788(M2C_UNK *, s32);
s32 rcos(s32);
s32 rsin(s32, s32);

void func_80012578(void) {
    func_800439D8(0x1F8000B0, 0x160, 0x110, 0x140, 0, 0x10000);
}

void func_80012E44(void) {
    s32 temp_v0;
    s32 temp_v0_2;

    func_80012C14();
    func_80043470(&D_801E91F0);
    temp_v0 = func_80033FBC(*(s32 *)0x1F800000, 0x1F800038, &D_801D7810, 0x40);
    *(s32 *)0x1F800000 = temp_v0;
    temp_v0_2 = func_80034050(temp_v0, 0x1F800038, &D_801D7810, 0x40);
    *(s32 *)0x1F800000 = temp_v0_2;
    *(s32 *)0x1F800000 = func_8003446C(temp_v0_2, 0x1F800038, &D_801D7810, 0x40);
    func_8003FC08(D_80173152, D_80173153, D_80173154);
}

void st_race_init(void) {
    M2C_UNK *var_v0;
    s16 var_v1;
    s32 var_v0_2;
    s32 var_v0_3;

    func_80045750(0);
    if (D_801D34F8 == 0) {
        func_8003A1D8(D_80173338 + 1);
    }
    func_8003EE20();
    if (D_801D34F8 == 0) {
        func_8003EF00();
        D_801D3586 = 0x1E00;
        D_801D3544 = 0x1E00;
        D_801D354A = 0x1E00;
    }
    func_8003B26C(4, 0, 0);
    func_80013338(0, 0, 0);
    func_800135B8(D_8007C210 < 3, D_801733B8);
    D_801E9210 = 0;
    if (D_801733B8 != 0) {
        if (D_8007C210 < 3) {
            var_v0 = &g_track_nodes_0;
            goto block_9;
        }
        D_801733D8 = &g_track_nodes_2;
        var_v0_2 = 0x170;
    } else {
        var_v0 = &g_track_nodes_1;
block_9:
        D_801733D8 = var_v0;
        var_v0_2 = 0x100;
    }
    D_801E90E0 = var_v0_2;
    func_80013494();
    D_8007C480 = 1;
    D_8007C248 = &D_8007C258;
    if (D_8007C210 == 0) {
        D_80173164 = 0;
        D_80173150 = 0;
    } else {
        func_80025D9C(D_8007C210 - 1);
    }
    D_801D35D0 = (D_801733C0 & 0xF) == 0xF;
    func_8001AA60(&D_8007C258);
    func_80021048();
    if (D_8007C210 == 4) {
        func_80037FD0();
    } else {
        func_80037F64();
    }
    func_80038B80();
    func_80039034();
    func_80039734();
    if (D_801D34F8 != 0x19) {
        func_8002AD68();
    }
    D_801D9060 = 0;
    func_800376EC(D_8007C260);
    D_80173310 = 0;
    D_8012CD88 = 0;
    D_801D7EB0 = 0;
    D_8012CDC8 = 0;
    D_8007C508 = 0;
    D_801D35A0 = 3;
    if (D_801733B8 != 0) {
        var_v1 = *(&D_8005E914 + ((D_8007C210 - 1) * 0xC));
        var_v0_3 = var_v1 * 0x10;
    } else {
        var_v1 = *(&D_8005E90C + ((D_8007C210 - 1) * 0xC));
        var_v0_3 = var_v1 * 0x10;
    }
    D_8012CD20 = (var_v0_3 - var_v1) * 2;
    D_8012CF58 = 0;
    if (D_8007C210 == 1) {
        D_801D35A0 -= 1;
    }
    if (D_801D35A0 <= 0) {
        D_801D35A0 = 1;
    }
    D_8012D088 = 0;
    func_800355A4(5);
    D_801D77D0 = 0;
    D_8012CDB8 = 0x180;
    D_801D34F8 = 1;
}

void func_80013BB8(void) {
    s32 var_v0;
    s32 var_v0_2;

    if (D_801D35AE & 0x800) {
        D_80173398 = D_80173398 == 0;
    }
    if (D_801D35AE & 0x10) {
        D_80173390 = D_80173390 == 0;
    }
    if (D_80173398 != 0) {
        var_v0 = D_801D35AA & 0x4000;
        if (D_801D35AA & 0x1000) {
            D_8007C208 -= 1;
            var_v0 = D_801D35AA & 0x4000;
        }
        var_v0_2 = D_801D35AA & 0x80;
        if (var_v0 != 0) {
            D_8007C208 += 1;
            var_v0_2 = D_801D35AA & 0x80;
        }
        if (var_v0_2 != 0) {
            D_8007C208 = 0;
        }
        func_80018480();
    } else {
        car_update_and_collide(&D_8007C258);
        M2C_FIELD(&D_801D9068, s32 *, 0) = (s32) M2C_FIELD(&D_8007C268, s32 *, 0);
        M2C_FIELD(&D_801D9068, s32 *, 4) = (s32) M2C_FIELD(&D_8007C268, s32 *, 4);
        M2C_FIELD(&D_801D9068, s32 *, 8) = (s32) M2C_FIELD(&D_8007C268, s32 *, 8);
        M2C_FIELD(&D_801D9068, s32 *, 0xC) = (s32) M2C_FIELD(&D_8007C268, s32 *, 0xC);
        M2C_FIELD(&D_801D9078, s32 *, 0) = (s32) M2C_FIELD(&D_8007C278, s32 *, 0);
        M2C_FIELD(&D_801D9078, s32 *, 4) = (s32) M2C_FIELD(&D_8007C278, s32 *, 4);
        M2C_FIELD(&D_801D9078, s32 *, 8) = (s32) M2C_FIELD(&D_8007C278, s32 *, 8);
        M2C_FIELD(&D_801D9078, s32 *, 0xC) = (s32) M2C_FIELD(&D_8007C278, s32 *, 0xC);
    }
    func_800186C8();
    func_80012E44();
    func_800163E4();
    func_80013240();
    func_80018A9C();
}

void func_80014A74(s32 arg0) {
    if (arg0 == 0x78) {
        snd_play_se(0xB);
    }
    if (arg0 == 0x96) {
        snd_play_se(0xC);
    }
    if (arg0 == 0xB4) {
        snd_play_se(0xD);
    }
    if (arg0 == 0xD2) {
        snd_play_se(0xE);
    }
}

void func_80017A14(void *arg0, void *arg1, void *arg2) {
    s32 temp_lo;
    s32 temp_s1;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_v1;

    temp_s1 = M2C_FIELD(arg1, s16 *, 0xE) * 2;
    temp_v0 = rcos(0x800 - M2C_FIELD(arg1, s16 *, 0xA));
    var_v1 = M2C_FIELD(arg1, s32 *, 0);
    if (var_v1 < 0) {
        var_v1 += 0x3FFF;
    }
    var_a1 = temp_v0 * temp_s1;
    if (var_a1 < 0) {
        var_a1 += 0xFFF;
    }
    M2C_FIELD(arg2, s32 *, 0) = (s32) (((D_801733A0 - (var_v1 >> 0xE)) - M2C_FIELD(arg0, s32 *, 0)) - ((s32) ((s32) (var_a1 >> 0xC) / 16) / 2));
    var_a1_2 = M2C_FIELD(arg1, s32 *, 4);
    temp_lo = rsin(0x800 - M2C_FIELD(arg1, s16 *, 0xA), var_a1) * temp_s1;
    if (var_a1_2 < 0) {
        var_a1_2 += 0x3FFF;
    }
    var_a0 = temp_lo;
    if (var_a0 < 0) {
        var_a0 += 0xFFF;
    }
    M2C_FIELD(arg2, s32 *, 8) = (s32) (((var_a1_2 >> 0xE) - M2C_FIELD(arg0, s32 *, 8)) + ((s32) ((s32) (var_a0 >> 0xC) / 16) / 2));
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(arg2, s32 *, 0);
    M2C_FIELD(arg2, s32 *, 8) = (s32) M2C_FIELD(arg2, s32 *, 8);
}

void func_8001CEA0(void) {
    func_8001CDBC(9);
    D_801E90C8 = 0;
}

void func_8001D5D4(s32 arg0, M2C_UNK arg1, s32 arg2, s32 arg3) {
    M2C_UNK sp18;
    s8 sp2C;
    s8 sp37;
    s32 temp_s1;
    s32 var_a0;
    s32 var_v0;
    s8 *var_v1;

    var_v0 = 0x14 - (arg3 / 10);
    temp_s1 = D_8012CF68 + 0xB6C;
    if (var_v0 < 0) {
        var_v0 = 0;
    }
    var_a0 = 0x1F;
    var_v1 = &sp37;
    do {
        *var_v1 = 0x20;
        var_a0 -= 1;
        var_v1 -= 1;
    } while (var_a0 >= 0);
    func_80048198(&sp18 + var_v0, &D_80077154, *(&D_8007307C + (arg2 * 4)));
    sp2C = 0;
    *(s32 *)0x1F800000 = func_8001D3B8(temp_s1, *(s32 *)0x1F800000, arg0, arg1, &sp18);
}

void func_8001FC58(s16 arg0, s16 arg1, s32 arg2, s32 arg3) {
    s16 temp_s1;
    s16 temp_v0;
    s32 var_a0;
    s8 temp_s0;
    s8 temp_v1;
    void *temp_s3;

    temp_s3 = *(void **)0x1F800000;
    func_80047BAC(temp_s3);
    M2C_FIELD(temp_s3, s16 *, 8) = arg0;
    M2C_FIELD(temp_s3, s16 *, 0xA) = arg1;
    temp_v0 = arg0 + 0x18;
    M2C_FIELD(temp_s3, s16 *, 0x10) = temp_v0;
    M2C_FIELD(temp_s3, s16 *, 0x12) = arg1;
    M2C_FIELD(temp_s3, s16 *, 0x18) = arg0;
    temp_s1 = arg1 + 0x18;
    M2C_FIELD(temp_s3, s16 *, 0x1A) = temp_s1;
    M2C_FIELD(temp_s3, s16 *, 0x20) = temp_v0;
    M2C_FIELD(temp_s3, s16 *, 0x22) = temp_s1;
    var_a0 = arg3;
    temp_s0 = (arg2 % 10) * 0x18;
    if (arg3 < 0) {
        var_a0 = arg3 + 0xF;
    }
    M2C_FIELD(temp_s3, s16 *, 0xE) = (s16) ((((var_a0 >> 4) + 0x1E0) << 6) + (arg3 & 0xF));
    M2C_FIELD(temp_s3, s16 *, 0x16) = func_8004788C(0, 0, 0x140, 0);
    M2C_FIELD(temp_s3, s8 *, 0xC) = temp_s0;
    M2C_FIELD(temp_s3, s8 *, 0xD) = 0x98;
    temp_v1 = temp_s0 + 0x18;
    M2C_FIELD(temp_s3, s8 *, 0x14) = temp_v1;
    M2C_FIELD(temp_s3, s8 *, 0x15) = 0x98;
    M2C_FIELD(temp_s3, s8 *, 0x1C) = temp_s0;
    M2C_FIELD(temp_s3, s8 *, 0x1D) = 0xB0;
    M2C_FIELD(temp_s3, s8 *, 0x24) = temp_v1;
    M2C_FIELD(temp_s3, s8 *, 0x25) = 0xB0;
    func_80047B20(temp_s3, 1);
    AddPrim(D_8012CF68 + 0xB68, temp_s3);
    *(void **)0x1F800000 = temp_s3 + 0x28;
}

void *func_8001FDB0(void *arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4) {
    s32 var_v0;

    func_80047BE8();
    func_80047B20(arg0, 1);
    M2C_FIELD(arg0, s16 *, 8) = arg1;
    M2C_FIELD(arg0, s16 *, 0xA) = arg2;
    M2C_FIELD(arg0, s8 *, 0xC) = (s8) ((arg3 + 0xC) * 8);
    M2C_FIELD(arg0, s8 *, 0xD) = 0x10;
    var_v0 = arg4;
    if (arg4 < 0) {
        var_v0 = arg4 + 0xF;
    }
    M2C_FIELD(arg0, s16 *, 0xE) = (s16) ((((var_v0 >> 4) + 0x1E0) << 6) + (arg4 & 0xF));
    AddPrim(D_8012CF68 + 0xB6C, arg0);
    return arg0 + 0x10 + 0x10;
}

void func_8001FFD8(s32 arg2, s32 arg4) {
    s32 temp_hi;
    s32 temp_lo;
    s32 temp_lo_2;

    temp_lo = arg2 / arg4;
    temp_hi = temp_lo % 60;
    temp_lo_2 = (s32) ((arg2 % arg4) * 0x3E8) / arg4;
    D_80073124 = (temp_lo / 60) + 0x30;
    D_80073126 = (temp_hi / 10) + 0x30;
    D_80073127 = (temp_hi % 10) + 0x30;
    D_80073129 = (temp_lo_2 / 100) + 0x30;
    D_8007312B = (temp_lo_2 % 10) + 0x30;
    D_8007312A = ((s32) (temp_lo_2 / 10) % 10) + 0x30;
    func_80028578(&D_80073124);
}

void func_800202A0(s32 arg0) {
    M2C_UNK var_s1;
    s32 var_a0;
    s32 var_a0_2;

    var_a0 = arg0;
    if (var_a0 < 0) {
        var_a0 = 0;
    }
    var_a0_2 = var_a0 / 30;
    if (var_a0_2 >= 0x64) {
        var_a0_2 = 0x63;
        var_s1 = 0x80;
    } else {
        var_s1 = 0x7F;
        if (var_a0_2 < 0xA) {
            var_s1 = 0x81;
        }
    }
    func_8001FC58(0x58, 0x10, var_a0_2 / 10, var_s1);
    func_8001FC58(0x70, 0x10, var_a0_2 % 10, var_s1);
}

void func_8002037C(s32 arg0) {
    func_8001FC58(0x96, 0x10, arg0 / 10, 0x80);
    func_8001FC58(0xAC, 0x10, arg0 % 10, 0x80);
}

void track_select(void *arg0) {
    s32 var_v0;

    if (D_801D77B8 == 0) {
        if (M2C_FIELD(arg0, s16 *, 0x9C) == 0) {
            D_801733D8 = &g_track_nodes_1;
            var_v0 = 0x100;
        } else if (D_8007C210 < 3) {
            D_801733D8 = &g_track_nodes_0;
            var_v0 = 0x100;
        } else {
            goto block_7;
        }
    } else if (D_8007C210 < 3) {
        D_801733D8 = &g_track_nodes_0;
        var_v0 = 0x100;
    } else {
block_7:
        D_801733D8 = &g_track_nodes_2;
        var_v0 = 0x170;
    }
    D_801E90E0 = var_v0;
}

void func_800229F4(void *arg0) {
    s16 var_v0;

    if (M2C_FIELD(arg0, s16 *, 0xA4) == 0) {
        snd_play_se(8);
    }
    if (M2C_FIELD(arg0, s16 *, 0xA4) <= 0) {
        var_v0 = M2C_FIELD(arg0, s16 *, 0xA4) + 1;
    } else {
        var_v0 = M2C_FIELD(arg0, s16 *, 0xA4) + 1;
        if (M2C_FIELD(arg0, s16 *, 0xA4) >= 0x78) {
            var_v0 = -0x96;
        }
    }
    M2C_FIELD(arg0, s16 *, 0xA4) = var_v0;
}

void func_80022F88(void *arg0, s16 arg1) {
    u32 sp10;
    s32 sp14;
    s16 temp_a0;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_6;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    u32 temp_v0;
    u32 var_v0;
    void *temp_s0;

    temp_s0 = arg0 + 0x58;
    if (M2C_FIELD(arg0, s16 *, 0xA2) == -1) {
        sp14 = M2C_FIELD(arg0, s32 *, 0x108);
    } else {
        sp14 = M2C_FIELD(arg0, s32 *, 0xFC);
    }
    temp_a0 = M2C_FIELD(temp_s0, s16 *, 0x4A);
    switch (temp_a0) {
    case 1:
        sp10 = M2C_FIELD(temp_s0, u32 *, 0xB4);
        if ((M2C_FIELD(temp_s0, s16 *, 0x3E) == 0xC) && (M2C_FIELD(temp_s0, s16 *, 0x52) == temp_a0)) {
            temp_v0 = M2C_FIELD(temp_s0, u32 *, 0xB4);
            sp10 = (temp_v0 / 10U) + temp_v0;
        }
        break;
    case 2:
        temp_a0_2 = M2C_FIELD(temp_s0, s32 *, 0xB8);
        sp10 = temp_a0_2;
        if ((D_8007C250 == 1) && (M2C_FIELD(temp_s0, s16 *, 0x52) == D_8007C250)) {
            var_v0 = temp_a0_2 + (temp_a0_2 / 14);
block_27:
            sp10 = var_v0;
        }
        break;
    case 3:
        temp_v1 = M2C_FIELD(temp_s0, s16 *, 0x3E);
        sp14 = M2C_FIELD(temp_s0, s32 *, 0xA8);
        if (temp_v1 >= 0) {
            temp_v0_2 = *(&D_801E92D8 + (temp_v1 * 0x114));
            temp_a0_3 = M2C_FIELD(temp_s0, s32 *, 0xA0);
            temp_v0_3 = temp_v0_2 + (temp_v0_2 / 15);
            sp10 = temp_v0_3;
            if (temp_a0_3 < temp_v0_3) {
                sp10 = temp_a0_3;
            }
block_20:
            if ((s32) sp10 < 0x230) {
                sp10 = 0x230;
            }
        } else {
            sp10 = (s32) (M2C_FIELD(temp_s0, s32 *, 0x30) * 8) / 10;
        }
        break;
    case 4:
        temp_v1_2 = M2C_FIELD(temp_s0, s16 *, 0x3E);
        sp14 = M2C_FIELD(temp_s0, s32 *, 0xA8);
        if (temp_v1_2 >= 0) {
            temp_v1_3 = *(&D_801E92D8 + (temp_v1_2 * 0x114));
            sp10 = temp_v1_3 - (temp_v1_3 / 10);
        } else {
            sp10 = (s32) (M2C_FIELD(temp_s0, s32 *, 0x30) * 8) / 10;
        }
        goto block_20;
    case -1:
        if (M2C_FIELD(arg0, s16 *, 0) == 0x25) {
            sp10 = 0x4B0;
        } else {
            temp_a0_4 = M2C_FIELD(temp_s0, s32 *, 0xA0);
            sp10 = temp_a0_4;
            if (arg1 >= 3) {
                var_v0 = temp_a0_4 + ((s32) (temp_a0_4 * (0x14 - arg1)) / 100);
                goto block_27;
            }
        }
        break;
    case 0:
        temp_v1_4 = M2C_FIELD(temp_s0, s32 *, 0xA0);
        sp10 = temp_v1_4;
        if (M2C_FIELD(temp_s0, s32 *, 0x88) < -0xA00) {
            sp10 = (s32) (temp_v1_4 * 0x50) / 100;
        }
        if (sp10 < M2C_FIELD(temp_s0, s32 *, 0x30)) {
            sp14 = M2C_FIELD(temp_s0, s32 *, 0xA8);
        }
        break;
    default:
        sp10 = 0;
        sp14 = (s32) M2C_FIELD(temp_s0, s32 *, 0xA8) / 20;
        break;
    }
    if (arg0 == &D_801E9E2C) {
        sp14 = M2C_FIELD(temp_s0, s32 *, 0xA4);
        func_80022B4C(arg0, &sp10, &sp14);
    }
    if ((D_801D34F8 != 0x1A) && (arg0 == (&D_801E9E2C - 0xBDC))) {
        temp_v1_5 = M2C_FIELD(temp_s0, s32 *, 0x60);
        sp14 = M2C_FIELD(temp_s0, s32 *, 0xA4);
        if (temp_v1_5 == 0) {
            func_80022C40(arg0, &sp10, &sp14);
        } else {
            sp10 = temp_v1_5;
            if (M2C_FIELD(temp_s0, s32 *, 0x60) < temp_v1_5) {
                sp14 = M2C_FIELD(temp_s0, s32 *, 0xA8);
            } else {
                sp14 = M2C_FIELD(temp_s0, s32 *, 0xA4);
            }
        }
    }
    if ((M2C_FIELD(temp_s0, s16 *, 0x4A) != -1) && (M2C_FIELD(temp_s0, s16 *, 0x3C) != 0)) {
        var_a2 = 9;
        if (M2C_FIELD(temp_s0, s32 *, 0x30) >= 0x281) {
            temp_v1_6 = M2C_FIELD(temp_s0, s16 *, 0x42);
            sp14 = M2C_FIELD(temp_s0, s32 *, 0xA8);
            if (temp_v1_6 >= 0) {
                var_v0_2 = arg1 << 0x10;
                if (temp_v1_6 != 0xC) {
                    var_a2 = 0x10;
                    goto block_49;
                }
            } else {
block_49:
                var_v0_2 = arg1 << 0x10;
            }
            if ((var_v0_2 == 0) && (D_8007C210 == 4) && (D_801D35D0 == 1)) {
                var_a2 = 9;
            }
            var_a0 = M2C_FIELD(temp_s0, s32 *, 0x6C);
            var_v1 = 0x800 - M2C_FIELD(temp_s0, s32 *, 0x70);
            if (var_v1 < var_a0) {
                var_a1 = var_a0 - var_v1;
                if ((var_a0 - var_v1) >= 0x801) {
                    var_v1 += 0x1000;
                    goto block_59;
                }
            } else {
                var_a1 = var_a0 - var_v1;
                if ((var_v1 - var_a0) >= 0x801) {
                    var_a0 += 0x1000;
block_59:
                    var_a1 = var_a0 - var_v1;
                }
            }
            if (var_a1 <= 0) {
                var_a1 = var_v1 - var_a0;
            }
            sp10 -= (sp10 / 100) * (var_a1 / var_a2);
        }
    }
    if (sp14 > 0) {
        var_v0_3 = M2C_FIELD(temp_s0, s32 *, 0x30) < (s32) sp10;
        goto block_67;
    }
    if (sp14 < 0) {
        var_v0_3 = (s32) sp10 < M2C_FIELD(temp_s0, s32 *, 0x30);
block_67:
        if (var_v0_3 != 0) {
            M2C_FIELD(temp_s0, s32 *, 0x30) = (s32) (M2C_FIELD(temp_s0, s32 *, 0x30) + sp14);
        }
    }
    if (M2C_FIELD(temp_s0, s32 *, 0x30) < 0) {
        M2C_FIELD(temp_s0, s32 *, 0x30) = 0;
    }
    if ((M2C_FIELD(temp_s0, s16 *, 0x4A) == 4) && (M2C_FIELD(temp_s0, s32 *, 0x30) < 0x208)) {
        M2C_FIELD(temp_s0, s16 *, 0x4A) = 0;
    }
}

void func_80023B2C(void *arg0) {
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s2;
    s32 temp_s3;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    void *temp_s1;

    var_a2 = 0;
    temp_s1 = arg0 + 0x58;
    temp_s3 = M2C_FIELD(arg0, s32 *, 0xC8);
    temp_a1 = M2C_FIELD(arg0, s32 *, 8);
    temp_s2 = M2C_FIELD(arg0, s32 *, 0xD4);
    temp_s0 = temp_a1 & 0xFF;
    if ((D_801D77B8 == 1) && ((u32) ((((s32) ((D_801E90E0 << 0x10) + temp_a1) % (s32) (D_801E90E0 << 8)) & ~0xFF) - 0x6801) < 0x7FFU)) {
        func_80023A8C(temp_s1, temp_s0, 0);
        var_a2 = 1;
    }
    if (var_a2 != 1) {
        if (M2C_FIELD(temp_s1, s16 *, 0x4E) == 0) {
            var_a0 = temp_s3;
            if (D_801D77B8 == 0) {
                var_a1 = temp_s2;
                goto block_9;
            }
            var_a0 = temp_s2;
            if (D_801D77B8 == 1) {
                var_a1 = temp_s3;
block_9:
                M2C_FIELD(temp_s1, s32 *, 0x6C) = (s32) (0x800 - func_800177B8(var_a0, var_a1, temp_s0));
            }
        } else {
            func_80023A8C(temp_s1, temp_s0, var_a2);
        }
    }
}

s32 func_80024AD4(s16 arg0) {
    s16 temp_a1;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    u16 var_a0;
    void *temp_a2;

    temp_a2 = (arg0 * 0x114) + &D_801E9250;
    temp_a1 = M2C_FIELD(temp_a2, s16 *, 0x9C);
    var_a0 = 0;
    if (D_8007C32C >= temp_a1) {
        if (temp_a1 >= D_8007C32C) {
            if (temp_a1 == D_8007C32C) {
                if (D_801D77B8 == 0) {
                    var_a0_2 = M2C_FIELD(temp_a2, s32 *, 8);
                    if (var_a0_2 < 0x2800) {
                        var_v0_2 = 0x10000;
                        if (D_8007C210 >= 3) {
                            var_v0_2 = 0x17000;
                        }
                        var_a0_2 += var_v0_2;
                    }
                    var_v0_3 = var_a0_2 < D_8007C260;
                    if (D_8007C260 < 0x2800) {
                        var_v0_4 = 0x10000;
                        if (D_8007C210 >= 3) {
                            var_v0_4 = 0x17000;
                        }
                        var_v0_3 = var_a0_2 < (D_8007C260 + var_v0_4);
                    }
                    if (var_v0_3 != 0) {
                        goto block_24;
                    }
                    goto block_25;
                }
                var_v0 = 0 << 0x10;
                if (D_801D77B8 == 1) {
                    var_a0_3 = M2C_FIELD(temp_a2, s32 *, 8);
                    if (var_a0_3 <= 0xB0FF) {
                        var_v0_5 = 0x10000;
                        if (D_8007C210 >= 3) {
                            var_v0_5 = 0x17000;
                        }
                        var_a0_3 += var_v0_5;
                    }
                    var_v0_6 = D_8007C260 < var_a0_3;
                    if (D_8007C260 <= 0xB0FF) {
                        var_v0_7 = 0x10000;
                        if (D_8007C210 >= 3) {
                            var_v0_7 = 0x17000;
                        }
                        var_v0_6 = (D_8007C260 + var_v0_7) < var_a0_3;
                    }
                    if (var_v0_6 != 0) {
                        goto block_24;
                    }
                    goto block_25;
                }
            } else {
                goto block_26;
            }
        } else {
block_25:
            var_a0 = D_8007C25A;
block_26:
            var_v0 = var_a0 << 0x10;
        }
    } else {
block_24:
        var_v0 = M2C_FIELD(temp_a2, u16 *, 2) << 0x10;
    }
    return var_v0 >> 0x10;
}

void func_800262B0(void) {
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    u16 var_v0_8;

    if ((D_801D35AA & 9) && (D_801D35AA & 6)) {
        var_v0 = D_801D35AA & 0x20;
        if (D_801D35AA & 0x80) {
            D_800771A4 += 0x10;
            var_v0 = D_801D35AA & 0x20;
        }
        var_v0_2 = D_801D35AA & 0x8000;
        if (var_v0 != 0) {
            D_800771A4 -= 0x10;
            var_v0_2 = D_801D35AA & 0x8000;
        }
        var_v0_3 = D_801D35AA & 0x2000;
        if (var_v0_2 != 0) {
            M2C_FIELD(&D_800771A0, u16 *, 2) = (u16) (M2C_FIELD(&D_800771A0, u16 *, 2) + 0x10);
            var_v0_3 = D_801D35AA & 0x2000;
        }
        var_v0_4 = D_801D35AA & 0x1000;
        if (var_v0_3 != 0) {
            M2C_FIELD(&D_800771A0, u16 *, 2) = (u16) (M2C_FIELD(&D_800771A0, u16 *, 2) - 0x10);
            var_v0_4 = D_801D35AA & 0x1000;
        }
        var_v0_5 = D_801D35AA & 0x4000;
        if (var_v0_4 != 0) {
            M2C_FIELD(&D_800771A0, u16 *, 0) = (u16) (M2C_FIELD(&D_800771A0, u16 *, 0) - 0x10);
            var_v0_5 = D_801D35AA & 0x4000;
        }
        var_v0_6 = D_801D35AA & 0x40;
        if (var_v0_5 != 0) {
            M2C_FIELD(&D_800771A0, u16 *, 0) = (u16) (M2C_FIELD(&D_800771A0, u16 *, 0) + 0x10);
            var_v0_6 = D_801D35AA & 0x40;
        }
        var_v0_7 = D_801D35AA & 0x10;
        if (var_v0_6 != 0) {
            D_80074064 -= 0x10;
            var_v0_7 = D_801D35AA & 0x10;
        }
        if (var_v0_7 != 0) {
            D_80074064 += 0x10;
        }
        if (D_80074064 >= 0xC01) {
            D_80074064 = 0xC00;
        }
        if (D_80074064 < 0x300) {
            D_80074064 = 0x300;
        }
        var_v0_8 = D_801D35AE & 0xF79F;
        if (D_801D35AE & 0x800) {
            D_8012CD78 = D_8012CD78 == 0;
            var_v0_8 = D_801D35AE & 0xF79F;
        }
        D_801D35AE = var_v0_8;
    }
    func_800445D4(&D_800771A0, &D_801E91F0);
    func_80043204(&D_801E91F0, &D_8007405C);
    func_80043470(&D_801E91F0);
    func_80043500(&D_801E91F0);
}

void func_800266B8(s32 arg0) {
    s16 temp_s4;
    s32 var_s1;
    s32 var_s3;
    void *var_s0;
    void *var_s2;

    temp_s4 = func_8004788C(0, 0, 0x2C0, 0x100);
    var_s2 = (arg0 * 0x22BF4) + &D_8012E4C0;
    var_s3 = 0;
    var_s1 = 0;
    do {
        var_s0 = var_s2 + 0xE;
loop_2:
        func_80047BD4(var_s2);
        M2C_FIELD(var_s0, s16 *, 0xC) = temp_s4;
        M2C_FIELD(var_s0, s16 *, 0) = 0x7E8C;
        var_s1 += 1;
        var_s0 += 0x34;
        var_s2 += 0x34;
        if (var_s1 < 0x1C) {
            goto loop_2;
        }
        var_s3 += 1;
        var_s1 = 0;
    } while (var_s3 < 0x14);
}

void *func_80029278(s32 arg0, void *arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 var_v0;

    func_80047C10(arg1);
    func_80047B20(arg1, 1);
    M2C_FIELD(arg1, s16 *, 8) = arg2;
    M2C_FIELD(arg1, s16 *, 0xA) = arg3;
    M2C_FIELD(arg1, s16 *, 0x10) = (s16) arg4;
    M2C_FIELD(arg1, s16 *, 0x12) = (s16) arg5;
    M2C_FIELD(arg1, s8 *, 0xC) = (s8) arg6;
    M2C_FIELD(arg1, s8 *, 0xD) = (s8) arg7;
    var_v0 = arg8;
    if (arg8 < 0) {
        var_v0 = arg8 + 0xF;
    }
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) ((((var_v0 >> 4) + 0x1E0) << 6) + (arg8 & 0xF));
    AddPrim(arg0, arg1);
    return arg1 + 0x14;
}

void *func_8002935C(s32 arg0, void *arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11) {
    s32 sp10;
    s32 var_v0_2;
    void *var_v0;

    sp10 = arg0;
    if ((arg9 != 0) || (arg10 != 0) || (var_v0 = arg1, (arg11 != 0))) {
        func_80047C10(arg1);
        M2C_FIELD(arg1, s16 *, 8) = arg2;
        M2C_FIELD(arg1, s16 *, 0xA) = arg3;
        M2C_FIELD(arg1, s16 *, 0x10) = (s16) arg4;
        M2C_FIELD(arg1, s16 *, 0x12) = (s16) arg5;
        M2C_FIELD(arg1, s8 *, 0xC) = (s8) arg6;
        var_v0_2 = arg8;
        M2C_FIELD(arg1, s8 *, 4) = (s8) arg9;
        M2C_FIELD(arg1, s8 *, 5) = (s8) arg10;
        M2C_FIELD(arg1, s8 *, 6) = (s8) arg11;
        M2C_FIELD(arg1, s8 *, 0xD) = (s8) arg7;
        if (arg8 < 0) {
            var_v0_2 = arg8 + 0xF;
        }
        M2C_FIELD(arg1, s16 *, 0xE) = (s16) ((((var_v0_2 >> 4) + 0x1E0) << 6) + (arg8 & 0xF));
        AddPrim(sp10, arg1);
        var_v0 = arg1 + 0x14;
    }
    return var_v0;
}

void *func_80029464(s32 arg0, void *arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11) {
    s32 sp10;
    s32 sp18;
    s32 var_v0;

    sp10 = arg0;
    sp18 = arg8;
    func_80047C10(arg1);
    M2C_FIELD(arg1, s16 *, 8) = arg2;
    M2C_FIELD(arg1, s16 *, 0xA) = arg3;
    M2C_FIELD(arg1, s16 *, 0x10) = (s16) arg4;
    M2C_FIELD(arg1, s16 *, 0x12) = (s16) arg5;
    M2C_FIELD(arg1, s8 *, 0xC) = (s8) arg6;
    M2C_FIELD(arg1, s8 *, 4) = (s8) arg9;
    M2C_FIELD(arg1, s8 *, 5) = (s8) arg10;
    M2C_FIELD(arg1, s8 *, 6) = (s8) arg11;
    M2C_FIELD(arg1, s8 *, 0xD) = (s8) arg7;
    var_v0 = arg8;
    if (arg8 < 0) {
        var_v0 = arg8 + 0xF;
    }
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) ((((var_v0 >> 4) + 0x1E0) << 6) + (arg8 & 0xF));
    AddPrim(sp10, arg1);
    return arg1 + 0x14;
}

void *func_80029560(s32 arg0, void *arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    s32 var_v0;

    func_80047C10(arg1);
    func_80047B20(arg1, 1);
    func_80047AF8(arg1, 1);
    M2C_FIELD(arg1, s16 *, 8) = arg2;
    M2C_FIELD(arg1, s16 *, 0xA) = arg3;
    M2C_FIELD(arg1, s16 *, 0x10) = (s16) arg4;
    M2C_FIELD(arg1, s16 *, 0x12) = (s16) arg5;
    M2C_FIELD(arg1, s8 *, 0xC) = (s8) arg6;
    M2C_FIELD(arg1, s8 *, 0xD) = (s8) arg7;
    var_v0 = arg8;
    if (arg8 < 0) {
        var_v0 = arg8 + 0xF;
    }
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) ((((var_v0 >> 4) + 0x1E0) << 6) + (arg8 & 0xF));
    AddPrim(arg0, arg1);
    return arg1 + 0x14;
}

void *func_80029650(s32 arg0, void *arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_v0;
    s16 temp_v0_3;
    s32 var_v0;
    s8 temp_s1;
    s8 temp_v0_2;
    s8 temp_v0_4;
    s8 var_v1;

    func_80047BAC(arg1);
    func_80047B20(arg1, 1);
    temp_s1 = arg6 - 1;
    if (arg6 == 0) {
        temp_a0 = arg2 + arg4;
        M2C_FIELD(arg1, s16 *, 8) = temp_a0;
        temp_v0 = arg3 + arg5;
        M2C_FIELD(arg1, s16 *, 0xA) = temp_v0;
        M2C_FIELD(arg1, s16 *, 0x10) = arg2;
        M2C_FIELD(arg1, s16 *, 0x12) = temp_v0;
        M2C_FIELD(arg1, s16 *, 0x18) = temp_a0;
        M2C_FIELD(arg1, s16 *, 0x1A) = arg3;
        M2C_FIELD(arg1, s16 *, 0x20) = arg2;
        M2C_FIELD(arg1, s16 *, 0x22) = arg3;
        M2C_FIELD(arg1, s8 *, 0xC) = 0;
        temp_v0_2 = arg7 + arg5;
        M2C_FIELD(arg1, s8 *, 0xD) = temp_v0_2;
        var_v1 = arg4 - 1;
        M2C_FIELD(arg1, s8 *, 0x14) = var_v1;
        M2C_FIELD(arg1, s8 *, 0x15) = temp_v0_2;
        M2C_FIELD(arg1, s8 *, 0x1C) = 0;
    } else {
        temp_a0_2 = arg2 + arg4;
        M2C_FIELD(arg1, s16 *, 8) = temp_a0_2;
        temp_v0_3 = arg3 + arg5;
        M2C_FIELD(arg1, s16 *, 0xA) = temp_v0_3;
        M2C_FIELD(arg1, s16 *, 0x10) = arg2;
        M2C_FIELD(arg1, s16 *, 0x12) = temp_v0_3;
        M2C_FIELD(arg1, s16 *, 0x18) = temp_a0_2;
        M2C_FIELD(arg1, s16 *, 0x1A) = arg3;
        M2C_FIELD(arg1, s16 *, 0x20) = arg2;
        M2C_FIELD(arg1, s16 *, 0x22) = arg3;
        M2C_FIELD(arg1, s8 *, 0xC) = temp_s1;
        temp_v0_4 = arg7 + arg5;
        M2C_FIELD(arg1, s8 *, 0xD) = temp_v0_4;
        var_v1 = temp_s1 + arg4;
        M2C_FIELD(arg1, s8 *, 0x14) = var_v1;
        M2C_FIELD(arg1, s8 *, 0x15) = temp_v0_4;
        M2C_FIELD(arg1, s8 *, 0x1C) = temp_s1;
    }
    M2C_FIELD(arg1, s8 *, 0x1D) = (s8) arg7;
    M2C_FIELD(arg1, s8 *, 0x24) = var_v1;
    M2C_FIELD(arg1, s8 *, 0x25) = (s8) arg7;
    var_v0 = arg8;
    if (arg8 < 0) {
        var_v0 = arg8 + 0xF;
    }
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) ((((var_v0 >> 4) + 0x1E0) << 6) + (arg8 & 0xF));
    M2C_FIELD(arg1, s16 *, 0x16) = (s16) arg9;
    AddPrim(arg0, arg1);
    return arg1 + 0x28;
}

void *func_800297D8(s32 arg0, void *arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    func_80047C60(arg1);
    func_80047AF8(arg1, 1);
    M2C_FIELD(arg1, s16 *, 8) = arg2;
    M2C_FIELD(arg1, s16 *, 0xA) = arg3;
    M2C_FIELD(arg1, s16 *, 0xC) = (s16) arg4;
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) arg5;
    M2C_FIELD(arg1, s8 *, 4) = (s8) arg6;
    M2C_FIELD(arg1, s8 *, 5) = (s8) arg7;
    M2C_FIELD(arg1, s8 *, 6) = (s8) arg8;
    AddPrim(arg0, arg1);
    return arg1 + 0x10;
}

void func_8002AF1C(s32 arg0, void *arg1, void *arg2) {
    void *temp_v0;

    M2C_FIELD(arg1, u16 *, 2) = (u16) D_801D7E88;
    M2C_FIELD(arg2, u16 *, 2) = (u16) D_801D77F8;
    temp_v0 = (arg0 * 0x28) + D_8007C4F8;
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) M2C_FIELD(temp_v0, u16 *, 0);
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) M2C_FIELD(temp_v0, s16 *, 2);
    M2C_FIELD(arg1, s32 *, 0x18) = (s32) M2C_FIELD(temp_v0, u16 *, 4);
    M2C_FIELD(arg1, s32 *, 0x40) = (s32) M2C_FIELD(temp_v0, s16 *, 6);
    M2C_FIELD(arg1, s32 *, 0x20) = (s32) M2C_FIELD(temp_v0, s16 *, 8);
    M2C_FIELD(arg1, s32 *, 0x24) = (s32) M2C_FIELD(temp_v0, s16 *, 0xA);
    M2C_FIELD(arg1, s32 *, 0x28) = (s32) M2C_FIELD(temp_v0, s16 *, 0xC);
    M2C_FIELD(arg1, s32 *, 0x38) = (s32) M2C_FIELD(temp_v0, s16 *, 0xE);
    M2C_FIELD(arg2, s32 *, 0x10) = (s32) M2C_FIELD(temp_v0, u16 *, 0x10);
    M2C_FIELD(arg2, s32 *, 0x14) = (s32) M2C_FIELD(temp_v0, s16 *, 0x12);
    M2C_FIELD(arg2, s32 *, 0x18) = (s32) M2C_FIELD(temp_v0, u16 *, 0x14);
    M2C_FIELD(arg2, s32 *, 0x40) = (s32) M2C_FIELD(temp_v0, s16 *, 0x16);
    M2C_FIELD(arg2, s32 *, 0x20) = (s32) M2C_FIELD(temp_v0, s16 *, 0x18);
    M2C_FIELD(arg2, s32 *, 0x24) = (s32) M2C_FIELD(temp_v0, s16 *, 0x1A);
    M2C_FIELD(arg2, s32 *, 0x28) = (s32) M2C_FIELD(temp_v0, s16 *, 0x1C);
    M2C_FIELD(arg2, s32 *, 0x38) = (s32) M2C_FIELD(temp_v0, s16 *, 0x1E);
    M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(temp_v0, s32 *, 0x20);
    M2C_FIELD(arg2, s32 *, 8) = (s32) M2C_FIELD(temp_v0, s32 *, 0x24);
}

void func_8002B024(void) {
    s32 temp_v0;
    s32 temp_v0_2;
    void *temp_a1;

    if (((D_8007C32C == 2) && (D_8007C338 < 0x96)) || (D_8007C32C == 1)) {
        if (D_801D34E8 < 2) {
            temp_a1 = (D_80173470 * 8) + D_801D7760;
            if (M2C_FIELD(temp_a1, s32 *, 0) == (((s32) ((D_801E90E0 << 0x10) + D_8007C260) % (s32) (D_801E90E0 << 8)) & ~0xFF)) {
                D_80173470 += 1;
                D_801D34E8 = 1;
                D_801D7E68 = M2C_FIELD(temp_a1, s32 *, 4);
            }
        }
        if (D_801D34E8 == 1) {
            func_8002AE14(D_801D77F0, &D_8007C258, &D_801E9250);
            temp_v0 = D_801D77F0 + 1;
            D_801D77F0 = temp_v0;
            if (temp_v0 == 0x708) {
                D_801D34E8 = 2;
            }
            temp_v0_2 = D_801D7E68 - 1;
            D_801D7E68 = temp_v0_2;
            if (temp_v0_2 == 0) {
                D_801D34E8 = 0;
            }
        }
    }
}

void func_8002B66C(void) {
    D_80173164 = 0;
    D_80173150 = 0;
    func_80025D9C(D_8007C210 - 1);
    D_80173310 = 0;
    D_801E91A0 = 0;
    D_80173468 = D_8012CF50;
    if ((D_8012CF50 != 0) && (D_801D77F0 >= 0x50B)) {
        D_801E9218 = D_801D77F0;
        D_801D77F0 = 0x50A;
    }
}

s32 func_8002BA20(void *arg0) {
    s32 *var_s0;
    s32 temp_v1;
    s32 var_s1;
    s32 var_s2;
    s32 var_s4;
    s32 var_v0;
    void *temp_s0;

    var_s4 = 0;
    var_s1 = 1;
    temp_s0 = D_80173180 + 0x10;
    var_s2 = func_8002B974(M2C_FIELD(arg0, s32 *, 8), M2C_FIELD(D_80173180, s32 *, 0xC));
    var_v0 = 0;
    if (M2C_FIELD(temp_s0, s32 *, 0xC) != -1) {
        var_s0 = temp_s0 + 0xC;
        do {
            temp_v1 = func_8002B974(M2C_FIELD(arg0, s32 *, 8), *var_s0);
            var_s0 += 0x10;
            if (temp_v1 < var_s2) {
                var_s4 = var_s1;
                var_s2 = temp_v1;
            }
            var_s1 += 1;
        } while (*var_s0 != -1);
        var_v0 = var_s4;
    }
    return var_v0;
}

s32 func_8002BAE0(void *arg0, void *arg1) {
    s32 temp_a2;
    s32 temp_lo;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0_2 = M2C_FIELD(arg0, s32 *, 0) - M2C_FIELD(arg1, s32 *, 0);
    temp_v0_3 = M2C_FIELD(arg0, s32 *, 4) - M2C_FIELD(arg1, s32 *, 4);
    temp_lo = temp_v0_3 * temp_v0_3;
    temp_v0 = M2C_FIELD(arg0, s32 *, 8) - M2C_FIELD(arg1, s32 *, 8);
    temp_a2 = (temp_v0_2 * temp_v0_2) + temp_lo;
    return SquareRoot(temp_a2 + (temp_v0 * temp_v0), temp_lo, temp_a2) >> 6;
}

void func_8002E710(void) {
    func_8002E6A8(D_8012D908, D_8012D8D0);
}

void func_8002E740(void) {
    func_80049688(&D_80173170, 0x10, &D_80173170 + 8, 0x10);
    func_80049748();
}

void func_8002ECA4(void *arg0) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 temp_a2;

    sp10 = M2C_FIELD(arg0, s32 *, 0);
    sp14 = M2C_FIELD(arg0, s32 *, 4);
    sp18 = M2C_FIELD(arg0, s32 *, 8);
    sp1C = M2C_FIELD(arg0, s32 *, 0xC);
    temp_a2 = M2C_FIELD(arg0, s32 *, 0x1C);
    sp20 = M2C_FIELD(arg0, s32 *, 0x10);
    sp24 = M2C_FIELD(arg0, s32 *, 0x14);
    sp28 = M2C_FIELD(arg0, s32 *, 0x18);
    sp2C = temp_a2;
    func_80042E08(&D_80173448, &sp10, temp_a2);
    func_800434A0(&sp10);
}

void *func_8002F0D0(s32 arg0, void *arg1, M2C_UNK arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    func_80047C88(arg1);
    func_80047AF8(arg1, arg2);
    func_80047B20(arg1, 1);
    M2C_FIELD(arg1, s16 *, 8) = arg3;
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) arg4;
    M2C_FIELD(arg1, s16 *, 0xC) = (s16) arg5;
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) arg6;
    M2C_FIELD(arg1, s8 *, 4) = (s8) arg7;
    M2C_FIELD(arg1, s8 *, 5) = (s8) arg8;
    M2C_FIELD(arg1, s8 *, 6) = (s8) arg9;
    AddPrim(arg0, arg1);
    return arg1 + 0x10;
}

void func_80030DE0(void) {
    D_8012D020 = 0;
    D_8012CFB8 = 0;
    func_80030DBC();
}

s32 func_80031910(void) {
    M2C_UNK sp18;
    M2C_UNK sp1D;
    M2C_UNK sp40;
    M2C_UNK sp140;
    M2C_UNK *var_s1;
    s32 temp_v0;
    s32 var_s0;

    func_800313E4(&sp18);
    var_s0 = 0;
    if (D_8012CFD8 > 0) {
        var_s1 = &D_80173188;
loop_2:
        var_s0 += 1;
        if (func_80049708(&sp1D, var_s1) != 0) {
            var_s1 += 0x18;
            if (var_s0 >= D_8012CFD8) {
                goto block_4;
            }
            goto loop_2;
        }
        return 0;
    }
block_4:
    temp_v0 = func_800497E8(&sp18, 0x10200);
    if (temp_v0 >= 0) {
        func_80049648(temp_v0);
        return func_80031840(&sp18, &sp40, 0x100, &sp140, 0x100);
    }
    return -1;
}

void func_80032A24(void) {
    func_800496C8(&D_800106FC);
    func_800497F8();
}

void func_80032D50(void) {
    M2C_UNK sp10;

    if (func_80053788(&sp10, D_800747DC) == 0) {
        func_80032A24();
    }
    func_80032948(&sp10, &D_801D9098);
    if (func_80053788(&sp10, D_800747E0) == 0) {
        func_80032A24();
    }
    func_80032948(&sp10, &D_8007C520);
    if (func_8003A678(&D_801D9098, &D_8007C520) != 0) {
        func_800496C8(&D_8001070C);
    }
}

void func_80032F08(s32 arg1, s32 arg2) {
    D_801D7E78 = 1;
    D_8012D078 = 0x1E;
    D_801E9180 = arg1;
    D_801E9188 = arg2;
    func_80032E30();
}

s32 func_80033218(void *arg0) {
    s16 temp_s0;
    s32 temp_s1;
    s32 var_v0;
    s32 var_v0_2;

    var_v0 = 0;
    if (M2C_FIELD(arg0, s32 *, 0xA0) >= 0x4C0) {
        var_v0 = 0;
        if (D_8012D900 == 0) {
            temp_s0 = D_801733B8;
            temp_s1 = ((s32) ((D_801E90E0 << 0x10) + M2C_FIELD(arg0, s32 *, 8)) % (s32) (D_801E90E0 << 8)) & ~0xFF;
            if (temp_s0 != func_8001B2D4(arg0, arg0)) {
                if (D_8007C210 < 3) {
                    var_v0_2 = 0x7900;
                    if (temp_s1 != 0x3400) {
                        goto block_8;
                    }
                    goto block_7;
                }
                var_v0_2 = 0xE900;
                if (temp_s1 == 0x3400) {
block_7:
                    return 5;
                }
block_8:
                var_v0 = 0;
                if (temp_s1 == var_v0_2) {
                    return 6;
                }
                
                return var_v0;
            }
            if (D_8007C210 < 3) {
                var_v0 = 0;
                if (temp_s1 == 0x7900) {
                    return 1;
                }
                
                return var_v0;
            }
            if (temp_s1 == 0xE900) {
                return 2;
            }
            if (temp_s1 == 0x7700) {
                return 3;
            }
            var_v0 = 0;
            if (temp_s1 == 0x5D00) {
                var_v0 = 4;
            }
            
            return var_v0;
        }
    }
    return var_v0;
}

void func_80037850(s32 arg0) {
    s32 sp10;
    s32 *var_a0;
    s32 *var_a0_2;
    s32 *var_s0;
    s32 *var_s0_2;
    s32 temp_a0;
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v1;
    s32 var_v1_2;
    s8 temp_s3;
    u8 temp_a1;
    u8 temp_v1;

    temp_s1 = arg0 & 0xFF;
    D_8007728E = temp_s1 + 0x100;
    temp_a0 = arg0 >> 8;
    temp_a1 = *(&D_801D7D10 + temp_s1);
    temp_v1 = *(&D_801D7C10 + temp_s1);
    temp_s3 = (3 - temp_a1) - temp_v1;
    if (temp_v1 == temp_a0) {
        func_800458B8(&D_8007728E - 2, &sp10);
        func_80045790(0);
        var_s0 = (temp_s1 * 0x300) + &D_801734E0;
        func_80045854(&D_8007728E - 2, var_s0);
        func_80045790(0);
        var_a0 = &sp10;
        var_v1 = 0;
        do {
            temp_v0 = *var_a0;
            var_a0 += 4;
            var_v1 += 1;
            *var_s0 = temp_v0;
            var_s0 += 4;
        } while (var_v1 < 0xC0);
        *(&D_801D7C10 + temp_s1) = temp_s3;
        return;
    }
    if (temp_a1 == temp_a0) {
        func_800458B8(&D_8007728E - 2, &sp10);
        func_80045790(0);
        var_s0_2 = (temp_s1 * 0x300) + &D_801A34E0;
        func_80045854(&D_8007728E - 2, var_s0_2);
        func_80045790(0);
        var_a0_2 = &sp10;
        var_v1_2 = 0;
        do {
            temp_v0_2 = *var_a0_2;
            var_a0_2 += 4;
            var_v1_2 += 1;
            *var_s0_2 = temp_v0_2;
            var_s0_2 += 4;
        } while (var_v1_2 < 0xC0);
        *(&D_801D7D10 + temp_s1) = temp_s3;
    }
}

void func_8003916C(void) {
    s32 sp10;
    s32 sp18;
    s32 *var_s0;
    s32 *var_s2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_s1;
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_s3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    void *temp_v1;
    void *temp_v1_2;

    var_s2 = &D_801D8128;
    var_s3 = 0;
    var_s0 = &D_801D8128 + 0x18;
    D_801D7668 += 1;
    do {
        if (*var_s2 != 0) {
            temp_v0 = M2C_FIELD(var_s0, s32 *, -0x14);
            temp_s1 = temp_v0 >> 0xC;
            temp_a1 = temp_v0 & 0xFFF;
            temp_a3 = temp_s1 * 0x10;
            temp_v1 = temp_a3 + M2C_FIELD(var_s0, M2C_UNK **, -0x10);
            temp_a2 = 0x1000 - temp_a1;
            var_v0 = (temp_a2 * M2C_FIELD(temp_v1, s32 *, 0)) + (temp_a1 * M2C_FIELD(temp_v1, s32 *, 0x10));
            if (var_v0 < 0) {
                var_v0 += 0xFFF;
            }
            temp_t0 = (var_v0 >> 0xC) + M2C_FIELD(var_s0, s32 *, 8);
            sp10 = temp_t0;
            temp_v1_2 = temp_a3 + M2C_FIELD(var_s0, M2C_UNK **, -0x10);
            var_v1 = (temp_a2 * M2C_FIELD(temp_v1_2, s32 *, 4)) + (temp_a1 * M2C_FIELD(temp_v1_2, s32 *, 0x14));
            if (var_v1 < 0) {
                var_v1 += 0xFFF;
            }
            temp_a1_2 = (var_v1 >> 0xC) + M2C_FIELD(var_s0, s32 *, 0x10);
            sp18 = temp_a1_2;
            M2C_FIELD(var_s0, s32 *, 4) = (s32) (func_800187A0(temp_t0 - M2C_FIELD(var_s0, s32 *, -8), temp_a1_2 - M2C_FIELD(var_s0, s32 *, 0), temp_a2, temp_a3) + 0x400);
            temp_v1_3 = M2C_FIELD(var_s0, s32 *, -8);
            M2C_FIELD(var_s0, s32 *, -8) = (s32) (((s32) (sp10 - temp_v1_3) / 16) + temp_v1_3);
            temp_v1_4 = M2C_FIELD(var_s0, s32 *, 0);
            M2C_FIELD(var_s0, s32 *, 0) = ((s32) (sp18 - temp_v1_4) / 16) + temp_v1_4;
            if ((var_s3 >= 4) && ((u32) (temp_s1 - 9) < 3U)) {
                M2C_FIELD(var_s0, s32 *, -4) = (s32) (M2C_FIELD(var_s0, s32 *, -4) + 1);
            }
            temp_v1_5 = M2C_FIELD(var_s0, s32 *, -0x14) + M2C_FIELD(((temp_s1 * 0x10) + M2C_FIELD(var_s0, M2C_UNK **, -0x10)), s32 *, 0xC);
            var_v0_2 = temp_v1_5;
            M2C_FIELD(var_s0, s32 *, -0x14) = temp_v1_5;
            if (var_v0_2 < 0) {
                var_v0_2 += 0xFFF;
            }
            if ((var_v0_2 >> 0xC) >= M2C_FIELD(var_s0, s32 *, -0xC)) {
                *var_s2 = 0;
            }
        } else if (D_801D7668 >= 9) {
            if (var_s3 < 4) {
                if (!(func_800497C8() & 0x126)) {
                    *var_s2 = 1;
                    M2C_FIELD(var_s0, s32 *, -0x14) = 0x400;
                    M2C_FIELD(var_s0, s32 *, 0x10) = 0;
                    M2C_FIELD(var_s0, s32 *, 8) = 0;
                    if (D_8007B1E8 & 8) {
                        M2C_FIELD(var_s0, s32 *, 0x10) = 0xA0;
                        M2C_FIELD(var_s0, s32 *, 8) = 0xA0;
                    }
                    M2C_FIELD(var_s0, M2C_UNK **, -0x10) = &D_80074DBC;
                    M2C_FIELD(var_s0, s32 *, -4) = -0xC;
                    M2C_FIELD(var_s0, s32 *, -0xC) = 0xF;
                    M2C_FIELD(var_s0, s32 *, 0x18) = (s32) *(&D_8005922A + ((D_8007B1E8 & 7) * 0x10));
                    var_v0_3 = M2C_FIELD(M2C_FIELD(var_s0, M2C_UNK **, -0x10), s32 *, 0);
                    goto block_21;
                }
            } else if (!(func_800497C8() & 0x238C)) {
                *var_s2 = 1;
                M2C_FIELD(var_s0, s32 *, -0x14) = 0x400;
                M2C_FIELD(var_s0, s32 *, 0x10) = 0;
                M2C_FIELD(var_s0, s32 *, 8) = 0;
                M2C_FIELD(var_s0, M2C_UNK **, -0x10) = &D_80074EBC;
                M2C_FIELD(var_s0, s32 *, -4) = -0xD0;
                M2C_FIELD(var_s0, s32 *, -0xC) = 0xF;
                M2C_FIELD(var_s0, s32 *, 0x18) = (s32) ((D_8007B1E8 & 1) + 0xC6);
                var_v0_3 = M2C_FIELD(M2C_FIELD(var_s0, M2C_UNK **, -0x10), s32 *, 0);
block_21:
                M2C_FIELD(var_s0, s32 *, -8) = (s32) (var_v0_3 + M2C_FIELD(var_s0, s32 *, 8));
                D_801D7668 = 0;
                M2C_FIELD(var_s0, s32 *, 0) = M2C_FIELD(M2C_FIELD(var_s0, M2C_UNK **, -0x10), s32 *, 4) + M2C_FIELD(var_s0, s32 *, 0x10);
            }
        }
        var_s3 += 1;
        var_s0 += 0x34;
        var_s2 += 0x34;
    } while (var_s3 < 8);
}

void func_80039874(void) {
    s32 *var_s0;
    s32 *var_s1;
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_s2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_v1_2;

    if (D_8012CD28 != 0) {
        D_8012CD28 -= 1;
    }
    var_s1 = &D_801D7F58;
    var_s2 = 0;
    var_s0 = &D_801D7F58 + 0x14;
    do {
        temp_v1 = *var_s1;
        if (temp_v1 == 0) {
            if (func_800397A4(var_s1) != 0) {
                if (D_801733B8 != 0) {
                    snd_play_se(0x22);
                } else {
                    snd_play_se(0x23);
                }
                *var_s1 = 1;
                M2C_FIELD(var_s0, s32 *, 0x10) = (s32) M2C_FIELD(&D_8007C2B8, s32 *, 0);
                M2C_FIELD(var_s0, s32 *, 0x14) = (s32) M2C_FIELD(&D_8007C2B8, s32 *, 4);
                M2C_FIELD(var_s0, s32 *, 0x18) = (s32) M2C_FIELD(&D_8007C2B8, s32 *, 8);
                M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) M2C_FIELD(&D_8007C2B8, s32 *, 0xC);
                M2C_FIELD(var_s0, s32 *, 0x10) = (s32) (M2C_FIELD(var_s0, s32 *, 0x10) * 2);
                temp_v0 = M2C_FIELD(var_s0, s32 *, 0x10);
                temp_v0_2 = M2C_FIELD(var_s0, s32 *, 0x18) * 2;
                M2C_FIELD(var_s0, s32 *, 0x18) = temp_v0_2;
                var_v0 = (temp_v0 * temp_v0) + (temp_v0_2 * temp_v0_2);
                var_s2 += 1;
                if (var_v0 < 0) {
                    var_v0 += 0x1FFF;
                }
                M2C_FIELD(var_s0, s32 *, 0x20) = (s32) (var_v0 >> 0xD);
            } else {
                goto block_36;
            }
        } else {
            if (temp_v1 == 1) {
                var_v0_2 = M2C_FIELD(var_s0, s32 *, 0x10);
                if (var_v0_2 < 0) {
                    var_v0_2 += 0xFF;
                }
                var_a1 = M2C_FIELD(var_s0, s32 *, 0x18);
                M2C_FIELD(var_s0, s32 *, -0x10) = (s32) ((var_v0_2 >> 8) + M2C_FIELD(var_s0, s32 *, -0x10));
                if (var_a1 < 0) {
                    var_a1 += 0xFF;
                }
                M2C_FIELD(var_s0, s32 *, -8) = (s32) ((var_a1 >> 8) + M2C_FIELD(var_s0, s32 *, -8));
                var_v1 = M2C_FIELD(var_s0, s32 *, 0x10) * 0xF;
                if (var_v1 < 0) {
                    var_v1 += 0xF;
                }
                M2C_FIELD(var_s0, s32 *, 0x10) = (s32) (var_v1 >> 4);
                var_v0_3 = M2C_FIELD(var_s0, s32 *, 0x18) * 0xF;
                if (var_v0_3 < 0) {
                    var_v0_3 += 0xF;
                }
                var_a1_2 = M2C_FIELD(var_s0, s32 *, 0x20);
                M2C_FIELD(var_s0, s32 *, 0x18) = (s32) (var_v0_3 >> 4);
                if (var_a1_2 < 0) {
                    var_a1_2 += 0xFF;
                }
                M2C_FIELD(var_s0, s32 *, 4) = (s32) ((var_a1_2 >> 8) + M2C_FIELD(var_s0, s32 *, 4));
                var_v1_2 = M2C_FIELD(var_s0, s32 *, 0x20) * 0xF;
                if (var_v1_2 < 0) {
                    var_v1_2 += 0xF;
                }
                M2C_FIELD(var_s0, s32 *, 0x20) = (s32) (var_v1_2 >> 4);
                temp_a0 = M2C_FIELD(var_s0, s32 *, 0);
                temp_v1_2 = *((D_801733B8 * 4) + &D_800750DC);
                if (temp_a0 < temp_v1_2) {
                    M2C_FIELD(var_s0, s32 *, 0) = temp_a0 + 0x80;
                } else {
                    M2C_FIELD(var_s0, s32 *, 0) = temp_v1_2;
                }
                if ((M2C_FIELD(var_s0, s32 *, 0x10) == 0) && (M2C_FIELD(var_s0, s32 *, 0x18) == 0) && (M2C_FIELD(var_s0, s32 *, 0x20) == 0) && (M2C_FIELD(var_s0, s32 *, 0) == *((D_801733B8 * 4) + &D_800750DC))) {
                    *var_s1 = 2;
                }
            } else if (func_800397FC(var_s1) != 0) {
                func_80032F50(3, &D_8007C258);
                if ((D_8012CD28 == 0) && (D_8007C2F8 >= 0x191)) {
                    snd_play_se(0x1E);
                    D_8012CD28 = 4;
                }
            }
block_36:
            var_s2 += 1;
        }
        var_s0 += 0x38;
        var_s1 += 0x38;
    } while (var_s2 < 6);
}

void func_80039D00(void) {
    s8 sp10;

    func_80051B24(0, 0, 1);
    func_8004DFC4(0, 0x7FFF, 0x7FFF);
    sp10 = 7;
    func_80051E30(0xE, &sp10, 0);
    D_80173428 = 1;
    D_801E9098 = 0;
    D_801D35C0 = 0x7F;
    D_801D35C1 = 0;
    D_801D35C2 = 0x7F;
    D_801D35C3 = 0;
}

void func_8003A5A4(void) {
    if (D_801734A8 == 0) {
        func_80051EF0(8, 0, 0);
        D_801734A8 = 1;
    }
}

void func_8003A600(void) {
    if (D_801D7E50 == 0) {
        func_80051EF0(9, 0, 0);
        D_801D7E50 = 1;
    }
}

s16 func_8003A9D8(s16 arg0) {
    s16 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;

    temp_v0_2 = arg0 * 0xC;
    temp_v0 = func_8004C380(D_801D34F0, arg0, 0, 0x3C, 0, (s32) *(&D_80075100 + temp_v0_2), (s32) *(&D_80075102 + temp_v0_2));
    if (temp_v0 >= 0) {
        temp_v0_3 = temp_v0 * 0xA;
        *(&D_801D7672 + temp_v0_3) = arg0;
        *(&D_801D7674 + temp_v0_3) = 0;
        *(&D_801D7678 + temp_v0_3) = 0x1E00;
        *(&D_801D7676 + temp_v0_3) = 0x1E00;
        *(&D_801D7670 + temp_v0_3) = 2;
        D_8012D018 = temp_v0;
        D_8012D000 = 0;
    }
    return temp_v0;
}

s32 func_8003AC2C(s16 arg0) {
    s16 var_a0;
    s32 temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;
    void *temp_v1;

    temp_s0 = arg0 * 0xC;
    var_a0 = func_8004C380(D_801D34F0, arg0, 0, 0x3C, 0, (s32) *(&D_80075100 + temp_s0), (s32) *(&D_80075102 + temp_s0));
    if (var_a0 >= 0) {
        temp_v0 = var_a0 * 0xA;
        *(&D_801D7672 + temp_v0) = arg0;
        *(&D_801D7674 + temp_v0) = 0;
        *(&D_801D7678 + temp_v0) = 0x1E00;
        *(&D_801D7676 + temp_v0) = 0x1E00;
        *(&D_801D7670 + temp_v0) = 1;
        var_v0 = var_a0 << 0x10;
        if (*(&D_80075104 + temp_s0) >= 2) {
            temp_v1 = *(&D_80075108 + temp_s0);
            var_a0 = func_8004C380(D_801D34F0, arg0, 1, 0x3C, 0, (s32) M2C_FIELD(temp_v1, s16 *, 0), (s32) M2C_FIELD(temp_v1, s16 *, 2));
            if (var_a0 >= 0) {
                temp_v0_2 = var_a0 * 0xA;
                *(&D_801D7672 + temp_v0_2) = arg0;
                *(&D_801D7674 + temp_v0_2) = 1;
                M2C_FIELD((temp_v0_2 + &D_801D7670), s16 *, 8) = 0x1E00;
                *(&D_801D7676 + temp_v0_2) = 0x1E00;
                *(&D_801D7670 + temp_v0_2) = 1;
            }
            goto block_4;
        }
    } else {
block_4:
        var_v0 = var_a0 << 0x10;
    }
    return var_v0 >> 0x10;
}

void func_8003AEC0(void) {
    s16 var_s1;
    s16 var_v0_2;
    s32 temp_a0;
    s32 temp_s0;
    s32 var_v0;

    var_s1 = 0;
    var_v0 = 0 << 0x10;
    do {
        temp_a0 = var_v0 >> 0x10;
        temp_s0 = temp_a0 * 0xA;
        var_v0_2 = var_s1 + 1;
        if (*(&D_801D7670 + temp_s0) != 0) {
            func_8004C74C(temp_a0, D_801D34F0, *(&D_801D7672 + temp_s0), *(&D_801D7674 + temp_s0), (s32) (*(&D_801D7676 + temp_s0) << 0x10) >> 0x17);
            *(&D_801D7670 + temp_s0) = 0;
            var_v0_2 = var_s1 + 1;
        }
        var_s1 = var_v0_2;
        var_v0 = var_s1 << 0x10;
    } while (var_v0_2 < 0x18);
}

void func_8003B118(s16 arg0, s16 arg1) {
    s32 temp_s0;
    u16 temp_a3;

    if ((D_800772FC == 0) && ((u32) (arg0 & 0xFFFF) < 0x18U)) {
        temp_s0 = arg0 * 0xA;
        if (*(&D_801D7670 + temp_s0) != 0) {
            temp_a3 = *(&D_801D7676 + temp_s0);
            func_8004C8AC(arg0, D_801D34F0, *(&D_801D7672 + temp_s0), (s32) (temp_a3 << 0x10) >> 0x17, temp_a3 & 0x7F, (s32) (arg1 << 0x10) >> 0x17, arg1 & 0x7F);
            *(&D_801D7678 + temp_s0) = arg1;
        }
    }
}

void func_8003B2E4(s16 arg0, s16 arg1) {
    s16 var_a2;
    s16 var_v1;

    var_v1 = arg0;
    var_a2 = arg1;
    if (arg0 >= 0x80) {
        var_v1 = 0x7F;
    }
    if (arg1 >= 0x80) {
        var_a2 = 0x7F;
    }
    func_8004D470(var_v1, var_a2, var_a2);
}

void func_8003B340(s16 arg0) {
    switch (arg0) {
    case 1:
        func_8004D3C0(arg0);
        return;
    case 0:
        func_8004D3E0(arg0);
        return;
    }
}

void func_8003B388(s32 arg0) {
    s16 temp_s3;
    s16 temp_v0;
    s32 temp_s6;
    s32 var_a0;
    s32 var_s2;
    void *temp_s0;

    var_a0 = arg0;
    temp_s6 = D_8012CF68 + 0xB6C;
    if (var_a0 >= 0xC3) {
        var_a0 = (0xD2 - var_a0) * 2;
    }
    var_s2 = var_a0;
    if (var_s2 >= 0x21) {
        var_s2 = 0x20;
    }
    temp_s0 = *(void **)0x1F800000;
    temp_s3 = 0x70 - ((s32) (var_s2 + ((u32) var_s2 >> 0x1F)) >> 1);
    func_80047BAC(temp_s0);
    func_80047B20(temp_s0, 1);
    M2C_FIELD(temp_s0, s16 *, 8) = 0x20;
    M2C_FIELD(temp_s0, s16 *, 0xA) = temp_s3;
    M2C_FIELD(temp_s0, s16 *, 0x10) = 0x11F;
    M2C_FIELD(temp_s0, s16 *, 0x12) = temp_s3;
    M2C_FIELD(temp_s0, s16 *, 0x18) = 0x20;
    temp_v0 = temp_s3 + var_s2;
    M2C_FIELD(temp_s0, s16 *, 0x1A) = temp_v0;
    M2C_FIELD(temp_s0, s16 *, 0x20) = 0x11F;
    M2C_FIELD(temp_s0, s16 *, 0x22) = temp_v0;
    M2C_FIELD(temp_s0, s8 *, 0xC) = 0;
    M2C_FIELD(temp_s0, s8 *, 0xD) = 0x60;
    M2C_FIELD(temp_s0, s8 *, 0x14) = 0xFF;
    M2C_FIELD(temp_s0, s8 *, 0x15) = 0x60;
    M2C_FIELD(temp_s0, s8 *, 0x1C) = 0;
    M2C_FIELD(temp_s0, s8 *, 0x1D) = 0x80;
    M2C_FIELD(temp_s0, s8 *, 0x24) = 0xFF;
    M2C_FIELD(temp_s0, s8 *, 0x25) = 0x80;
    M2C_FIELD(temp_s0, s16 *, 0x16) = func_8004788C(0, 0, 0x240, 0x100);
    M2C_FIELD(temp_s0, s16 *, 0xE) = 0x7ACC;
    AddPrim(temp_s6, temp_s0);
    *(void **)0x1F800000 = temp_s0 + 0x28;
}

void func_8003DFE0(void) {
    M2C_UNK *var_a3_3;
    M2C_UNK *var_t0_3;
    s32 *var_a1;
    s32 *var_a1_2;
    s32 *var_a2;
    s32 *var_a2_2;
    s32 *var_a3;
    s32 *var_a3_2;
    s32 *var_t1;
    s32 *var_t1_2;
    s32 *var_t2;
    s32 *var_t2_2;
    s32 *var_v1;
    s32 *var_v1_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a2_3;
    s32 var_t0;
    s32 var_t0_2;

    var_t0 = 0;
    var_t2 = &D_8012CD38;
    var_t1 = &D_801D7628;
    do {
        var_a0 = 0;
        var_a3 = var_t2;
        var_a2 = &D_80075450;
        var_a1 = var_t1;
        var_v1 = &D_80075440;
loop_2:
        *var_a1 = *var_v1;
        temp_v0 = *var_a2;
        var_v1 += 4;
        var_a0 += 1;
        var_a2 += 4;
        var_a1 += 4;
        *var_a3 = temp_v0;
        var_a3 += 4;
        if (var_a0 < 4) {
            goto loop_2;
        }
        var_t2 += 0x10;
        var_t0 += 1;
        var_t1 += 0x10;
    } while (var_t0 < 2);
    var_t0_2 = 0;
    var_t2_2 = &D_8012CD58;
    var_t1_2 = &D_801D7648;
    do {
        var_a0_2 = 0;
        var_a3_2 = var_t2_2;
        var_a2_2 = &D_80075450;
        var_a1_2 = var_t1_2;
        var_v1_2 = &D_80075440;
loop_6:
        *var_a1_2 = *var_v1_2 - 0xC6;
        temp_v0_2 = *var_a2_2;
        var_v1_2 += 4;
        var_a0_2 += 1;
        var_a2_2 += 4;
        var_a1_2 += 4;
        *var_a3_2 = temp_v0_2 - 0xC6;
        var_a3_2 += 4;
        if (var_a0_2 < 4) {
            goto loop_6;
        }
        var_t2_2 += 0x10;
        var_t0_2 += 1;
        var_t1_2 += 0x10;
    } while (var_t0_2 < 2);
    var_t0_3 = &D_8007C488;
    var_a3_3 = &D_80075460;
    var_a2_3 = 0;
    do {
        M2C_FIELD(var_t0_3, s32 *, 0) = (s32) M2C_FIELD(var_a3_3, s32 *, 0);
        M2C_FIELD(var_t0_3, s32 *, 4) = (s32) M2C_FIELD(var_a3_3, s32 *, 4);
        M2C_FIELD(var_t0_3, s32 *, 8) = (s32) M2C_FIELD(var_a3_3, s32 *, 8);
        var_t0_3 += 0xC;
        var_a2_3 += 3;
        var_a3_3 += 0xC;
    } while (var_a2_3 < 0x12);
}

void func_8003F26C(void) {
    func_8003F0C0(&D_801D354C);
    func_8003F0C0(&D_801D3570);
    func_8003F0C0(&D_801D355E);
    func_8003F0C0(&D_801D3564);
    func_8003F0C0(&D_801D3576);
    func_8003F0C0(&D_801D357C);
    func_8003F0C0(&D_801D3552);
    func_8003F0C0(&D_801D3558);
    func_8003F0C0(&D_801D3582);
    func_8003F164(&D_801D3540, 0x2E, 1);
    func_8003F164(&D_801D3546, 0x2F, 0);
}

void func_80040770(s32 arg0) {
    s32 sp18;
    M2C_UNK sp1C;
    s32 temp_v1;
    s32 var_at;
    s32 var_at_2;
    s32 var_at_3;
    s32 var_v1;

    var_v1 = arg0;
    if (var_v1 < 0) {
        var_v1 = -var_v1;
    }
    temp_v1 = var_v1 % 4096;
    if (temp_v1 >= 0) {
        var_at = temp_v1 < 0x400;
        if (temp_v1 < 0x400) {
            func_8004059C(temp_v1, &sp1C, &sp18);
        } else {
            goto block_6;
        }
    } else {
        var_at = temp_v1 < 0x400;
block_6:
        if (var_at == 0) {
            var_at_2 = temp_v1 < 0x800;
            if (temp_v1 < 0x800) {
                func_8004059C(0x7FF - temp_v1, &sp1C, &sp18);
            } else {
                goto block_10;
            }
        } else {
            var_at_2 = temp_v1 < 0x800;
block_10:
            if (var_at_2 == 0) {
                var_at_3 = temp_v1 < 0xC00;
                if (temp_v1 < 0xC00) {
                    func_8004059C(temp_v1 - 0x800, &sp1C, &sp18);
                } else {
                    goto block_14;
                }
            } else {
                var_at_3 = temp_v1 < 0xC00;
block_14:
                if (var_at_3 == 0) {
                    if (temp_v1 < 0x1000) {
                        func_8004059C(0xFFF - temp_v1, &sp1C, &sp18);
                    }
                }
            }
        }
    }
}

void func_80044F64(s32 arg0, s32 arg1) {
    func_8003FCC0((s32) -(arg0 * 0x140) / arg1);
    func_8003FCCC(0x01400000);
}

s32 func_800456B4(s32 arg0) {
    s32 temp_s0;

    temp_s0 = D_80077374;
    D_80077374 = arg0;
    if (arg0 != 0) {
        D_80077370(&D_80010EF4, arg0, D_80077378, D_8007737C);
    }
    return temp_s0;
}

s32 func_8004591C(void *arg0, s32 arg1, s32 arg2) {
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 temp_v0;

    temp_v0 = func_800459C0(&D_80010F44, arg0);
    sp10 = 0x04FFFFFF;
    sp14 = 0x80000000;
    sp1C = (arg2 << 0x10) | (arg1 & 0xFFFF);
    sp18 = M2C_FIELD(arg0, s32 *, 0);
    sp20 = M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(s32, s32 *, M2C_UNK, M2C_UNK), 8)(M2C_FIELD(g_gpu_device, s32 *, 0x18), &sp10, 0x14, 0);
    return temp_v0;
}

void *PutDrawEnv(void *arg0) {
    M2C_UNK *var_a3;
    s32 temp_s0;
    void *var_a2;

    temp_s0 = arg0 + 0x1C;
    SetDrawEnv(temp_s0, arg0);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | 0xFFFFFF);
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(s32, s32, M2C_UNK), 4)(M2C_FIELD(g_gpu_device, s32 *, 0x18), temp_s0, 0);
    var_a3 = &D_80078248;
    var_a2 = arg0;
    do {
        M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
        M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
        M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
        M2C_FIELD(var_a3, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
        var_a2 += 0x10;
        var_a3 += 0x10;
    } while (var_a2 != (arg0 + 0x50));
    M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
    M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
    M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
    return arg0;
}

void func_8004617C(void *arg0, M2C_UNK arg1, M2C_UNK arg2, M2C_UNK arg3, s32 arg4) {
    M2C_FIELD(arg0, s8 *, 3) = 2;
    M2C_FIELD(arg0, s32 *, 4) = func_80046430(arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 8) = func_800465DC(arg4);
}

s32 func_80046AE8(void *arg0, s32 *arg1) {
    s32 sp10;
    u16 sp18;
    u16 sp1A;
    u16 sp1C;
    u16 sp1E;
    s16 var_a0;
    s16 var_v1;
    s32 *var_s2;
    s32 temp_s1;
    s32 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s1;
    s32 var_s5;
    s32 var_v0;
    u16 temp_v1;

    sp18 = M2C_FIELD(arg0, u16 *, 0);
    sp1A = M2C_FIELD(arg0, u16 *, 2);
    temp_v1 = M2C_FIELD(arg0, u16 *, 4);
    var_s2 = arg1;
    sp1C = temp_v1;
    var_s5 = 0;
    sp10 = 0x800000;
    sp1E = M2C_FIELD(arg0, u16 *, 6);
    if ((s16) temp_v1 > 0) {
        var_v1 = (s16) temp_v1;
        if (var_v1 >= 0x400) {
            var_v1 = 0x3FF;
        }
    } else {
        var_v1 = 1;
    }
    sp1C = var_v1;
    if ((s16) sp1E > 0) {
        var_a0 = (s16) sp1E;
        if ((s16) sp1E >= 0x200) {
            var_a0 = 0x1FF;
        }
    } else {
        var_a0 = 1;
    }
    sp1E = var_a0;
    if ((s16) sp18 >= 0x400) {
        sp18 = (u16) ((s32) ((s16) sp18 - 0x400) / 2);
        var_s5 = 1;
    }
    var_s0 = (s32) ((sp1C * var_a0) + 1) / 2;
    temp_v1_2 = var_s0;
    if (var_s0 < 0) {
        var_s0 += 0xF;
    }
    var_s1 = temp_v1_2;
    if (var_s1 < 0) {
        var_s1 += 0xF;
    }
    temp_s1 = var_s1 >> 4;
    if (!(*D_80077394 & 0x04000000)) {
        do {
            temp_v0 = sp10 - 1;
            sp10 = temp_v0;
            if (temp_v0 == -1) {
                func_80046738();
            }
        } while (!(*D_80077394 & 0x04000000));
    }
    *D_80077390 = 0x01000000;
    var_v0 = 0xA0000000;
    if (var_s5 != 0) {
        var_v0 = 0xB0000000;
    }
    *D_80077390 = var_v0;
    *D_80077390 = (s32) sp18;
    var_s0_2 = (temp_v1_2 - ((var_s0 >> 4) * 0x10)) - 1;
    *D_80077390 = (s32) sp1C;
    if (var_s0_2 != -1) {
        do {
            temp_v1_3 = *var_s2;
            var_s2 += 4;
            var_s0_2 -= 1;
            *D_80077390 = temp_v1_3;
        } while (var_s0_2 != -1);
    }
    if (temp_s1 != 0) {
        *D_80077394 = 0x04000002;
        *D_800773B0 |= 0x800;
        *D_80077398 = var_s2;
        *D_8007739C = (temp_s1 << 0x10) | 0x10;
        *D_800773A0 = 0x01000201;
    }
    return 0;
}

void *func_8004809C(void *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    M2C_FIELD(arg0, s16 *, 0) = arg1;
    M2C_FIELD(arg0, s16 *, 2) = arg2;
    M2C_FIELD(arg0, s16 *, 4) = arg3;
    M2C_FIELD(arg0, s16 *, 0xC) = 0;
    M2C_FIELD(arg0, s16 *, 0xE) = 0;
    M2C_FIELD(arg0, s16 *, 0x10) = 0;
    M2C_FIELD(arg0, s16 *, 0x12) = 0;
    M2C_FIELD(arg0, s8 *, 0x19) = 0;
    M2C_FIELD(arg0, s8 *, 0x1A) = 0;
    M2C_FIELD(arg0, s8 *, 0x1B) = 0;
    M2C_FIELD(arg0, s8 *, 0x16) = 1;
    M2C_FIELD(arg0, s16 *, 8) = arg1;
    M2C_FIELD(arg0, s16 *, 0xA) = arg2;
    M2C_FIELD(arg0, s16 *, 6) = (s16) arg4;
    M2C_FIELD(arg0, s8 *, 0x17) = (s8) (arg4 != 0x1E0);
    M2C_FIELD(arg0, s16 *, 0x14) = func_8004788C(0, 0, 0x280, 0);
    M2C_FIELD(arg0, s8 *, 0x18) = 0;
    return arg0;
}

void func_80048ADC(s32 *arg0) {
    s32 *var_s0;

    var_s0 = arg0;
    if ((*var_s0 & 0xFFFFFF) != 0xFFFFFF) {
        do {
            if (*var_s0 != 0) {
                func_80045B78(var_s0);
            }
            var_s0 = (s32 *) ((*var_s0 & 0xFFFFFF) | (s32) &D_80000000);
        } while ((*var_s0 & 0xFFFFFF) != 0xFFFFFF);
    }
    if (*var_s0 != 0) {
        func_80045B78(var_s0);
    }
}

void func_80048FC0(void) {
    s32 temp_v0;

    temp_v0 = *(s32 *)0x1F801814;
    *(s32 *)0x1F801810 = (temp_v0 & 0x3FFF) | 0xE1001000;
    if (!(temp_v0 & 0x1000)) {
        func_800496C8(&D_800111A8);
        func_80049808();
    }
}

void func_800491AC(s32 arg0, s32 arg1) {
    s32 *temp_a2;

    temp_a2 = (arg0 * 4) + &D_80079788;
    *temp_a2 = 0;
    if (arg1 != 0) {
        *D_8007744C = *D_8007744C | 0x800000 | (0x101 << (arg0 + 0x10));
        *temp_a2 = arg1;
        return;
    }
    *D_8007744C &= ~(0xFF000000 | (1 << (arg0 + 0x10)));
}

s32 func_8004922C(s32 arg0, s32 arg1) {
    s32 *temp_a2;

    if (arg0 == 3) {
        return -1;
    }
    temp_a2 = (arg0 * 4) + &D_800797A8;
    *temp_a2 = 0;
    if (arg1 != 0) {
        *temp_a2 = arg1;
        *D_80077444 |= 1 << arg0;
        return arg0;
    }
    *D_80077444 &= ~(1 << arg0);
    *temp_a2 = 0;
    return arg0;
}

void func_80049D7C(s16 arg1) {
    s32 temp_v1;
    s32 var_a1_2;
    s32 var_a2;
    u32 temp_lo;
    u32 temp_lo_2;
    u32 var_a0;
    u32 var_a1;
    u32 var_lo;
    void *temp_v0;

    temp_lo = (u32) (((s32) (D_80079B8C * (M2C_FIELD(D_80173388, u8 *, 0x18) * 0x3FFF)) / 16129) * D_80079B92 * D_80079B96) / 16129U;
    temp_v1 = D_80079B88 * 8;
    temp_lo_2 = (u32) (temp_lo * *(&D_80079A1A + temp_v1)) / 127U;
    var_a1 = (u32) (temp_lo * *(&D_80079A1C + temp_v1)) / 127U;
    if ((u8) D_80079B97 < 0x40U) {
        var_a0 = temp_lo_2;
        var_a1 = (u32) (var_a1 * D_80079B97) >> 6;
    } else {
        var_a0 = (u32) (temp_lo_2 * (0x7F - D_80079B97)) >> 6;
    }
    if ((u8) D_80079B93 < 0x40U) {
        var_a1 = (u32) (var_a1 * D_80079B93) >> 6;
    } else {
        var_a0 = (u32) (var_a0 * (0x7F - D_80079B93)) >> 6;
    }
    if ((u8) D_80079B8D < 0x40U) {
        var_a1 = (u32) (var_a1 * D_80079B8D) >> 6;
    } else {
        var_a0 = (u32) (var_a0 * (0x7F - D_80079B8D)) >> 6;
    }
    var_lo = var_a0 * var_a0;
    if (D_80077460 == 1) {
        if (var_a0 < var_a1) {
            var_a0 = var_a1;
        } else {
            var_a1 = var_a0;
        }
        var_lo = var_a0 * var_a0;
    }
    temp_v0 = (((D_80079BA0 * 8) & 0xFFFF) * 2) + D_8007745C;
    M2C_FIELD(temp_v0, s16 *, 4) = arg1;
    M2C_FIELD(temp_v0, s16 *, 0) = (s16) (var_lo / 16383U);
    M2C_FIELD(temp_v0, s16 *, 2) = (s16) ((u32) (var_a1 * var_a1) / 16383U);
    *(&D_800797DC + (D_80079BA0 * 0x18)) = arg1;
    *(&D_800797EF + (D_80079BA0 * 0x18)) = 1;
    if (D_80079BA0 < 0x10) {
        var_a2 = 1 << D_80079BA0;
        var_a1_2 = 0;
    } else {
        var_a2 = 0;
        var_a1_2 = 1 << (D_80079BA0 - 0x10);
    }
    if (D_80079B9D & 4) {
        D_8007B1B0 |= var_a2;
        D_8007B1D8 |= var_a1_2;
    } else {
        D_8007B1B0 &= ~var_a2;
        D_8007B1D8 &= ~var_a1_2;
    }
    D_8007B190 |= var_a2;
    D_8007B198 |= var_a1_2;
}

void func_8004A33C(void) {
    s32 var_v1;
    u16 var_v0;
    u32 temp_v0;
    u32 temp_v0_2;

    D_80079BA2 = D_80079BA0 * 8;
    D_80079BA4 = D_80079B95 + (D_80079B8F * 0x10);
    *(&D_800797DE + (D_80079BA0 * 0x18)) = 0xFFFF;
    if ((D_80079B9E & 1) > 0) {
        temp_v0 = (s16) D_80079B9E - 1;
        var_v0 = M2C_FIELD(((((s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1) * 0x10) + D_80173350), u16 *, 0xC);
        var_v1 = D_80079BA2 * 2;
    } else {
        temp_v0_2 = (s16) D_80079B9E - 1;
        var_v0 = M2C_FIELD(((((s32) (temp_v0_2 + (temp_v0_2 >> 0x1F)) >> 1) * 0x10) + D_80173350), u16 *, 0xE);
        var_v1 = D_80079BA2 * 2;
    }
    M2C_FIELD((var_v1 + D_8007745C), u16 *, 6) = var_v0;
    M2C_FIELD(((D_80079BA2 * 2) + D_8007745C), u16 *, 8) = (u16) M2C_FIELD(((((D_80079B8F * 0x10) + D_80079B95) << 5) + D_801733B0), u16 *, 0x10);
    M2C_FIELD(((D_80079BA2 * 2) + D_8007745C), s16 *, 0xA) = (s16) (M2C_FIELD(((((D_80079B8F * 0x10) + D_80079B95) << 5) + D_801733B0), u16 *, 0x12) + D_800775F8);
}

void func_8004A9D4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 temp_v0;

    D_80079B98 = 0x7F;
    temp_v0 = func_80049AF4(0xFF) & 0xFF;
    D_80079BA0 = temp_v0;
    if (temp_v0 < (s32) D_800775E8) {
        func_8004A808(temp_v0, arg0 & 0xFFFF, arg1 & 0xFFFF, arg2 & 0xFFFF, arg3 & 0xFFFF);
    }
}

s32 func_8004B1BC(s16 arg0, s16 arg1, s16 arg2, s32 arg3) {
    s32 temp_a0;
    s32 temp_a1;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    var_s0 = 0;
    if (D_800775E8 != 0) {
        do {
            temp_a0 = var_s0 & 0xFF;
            temp_a1 = temp_a0 * 0x18;
            if ((*(&D_800797E0 + temp_a1) == (arg3 & 0xFFFF)) && (*(&D_800797E6 + temp_a1) == arg2) && (*(&D_800797E2 + temp_a1) == arg0) && (*(&D_800797EA + temp_a1) == arg1)) {
                if (*(&D_800797D8 + temp_a1) == 0xFF) {
                    var_s1 += 1;
                    func_8004A8D0(temp_a0, temp_a1);
                } else {
                    D_80079BA0 = var_s0 & 0xFF;
                    SpuVoiceKeyOn(0, temp_a1);
                    var_s1 += 1;
                }
            }
            var_s0 += 1;
        } while ((u32) (var_s0 & 0xFF) < (u8) D_800775E8);
    }
    return var_s1 & 0xFF;
}

u8 func_8004B6DC(s16 arg0, s16 arg1, s8 arg2) {
    s32 temp_v1;
    u8 var_v0;

    var_v0 = -1U;
    if (func_8004ACE4(arg0, arg1) == 0) {
        temp_v1 = arg1 * 0x10;
        M2C_FIELD((temp_v1 + D_80173350), s8 *, 1) = arg2;
        var_v0 = M2C_FIELD((temp_v1 + D_80173350), u8 *, 1);
    }
    return var_v0;
}

u8 func_8004B74C(s16 arg0, s16 arg1) {
    u8 var_v0;

    var_v0 = -1U;
    if (func_8004ACE4(arg0, arg1) == 0) {
        var_v0 = M2C_FIELD(((arg1 * 0x10) + D_80173350), u8 *, 1);
    }
    return var_v0;
}

u8 func_8004B79C(s16 arg0, s16 arg1, s8 arg2) {
    s32 temp_v1;
    u8 var_v0;

    var_v0 = -1U;
    if (func_8004ACE4(arg0, arg1) == 0) {
        temp_v1 = arg1 * 0x10;
        M2C_FIELD((temp_v1 + D_80173350), s8 *, 4) = arg2;
        var_v0 = M2C_FIELD((temp_v1 + D_80173350), u8 *, 4);
    }
    return var_v0;
}

u8 func_8004B80C(s16 arg0, s16 arg1) {
    u8 var_v0;

    var_v0 = -1U;
    if (func_8004ACE4(arg0, arg1) == 0) {
        var_v0 = M2C_FIELD(((arg1 * 0x10) + D_80173350), u8 *, 4);
    }
    return var_v0;
}

void func_8004B994(s16 arg0) {
    if (((u32) (arg0 & 0xFFFF) < 0x10U) && (*(&D_80079B20 + arg0) == 1)) {
        func_80058BE0(*(&D_80079C68 + (arg0 * 4)));
        *(&D_80079B20 + arg0) = 0;
        D_800775F0 -= 1;
    }
}

s16 func_8004BA20(void) {
    s16 var_v1;

    var_v1 = func_8004BA7C(-1);
    if (var_v1 != -1) {
        var_v1 = func_8004BE7C(*(&D_80079B30 + (var_v1 * 4)), var_v1);
    }
    return var_v1;
}

void func_8004C0E0(s32 arg0, s16 arg1) {
    s16 var_v0;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_lo;
    s32 var_a0;
    s32 var_a1;
    s32 var_v1;
    u32 temp_v1;

    temp_v1 = arg0 & 0xFF;
    if (temp_v1 < 0x18U) {
        temp_a2 = temp_v1 * 0x18;
        D_80079B8F = *(&D_800797E4 + temp_a2);
        D_80079B95 = *(&D_800797E8 + temp_a2);
        D_80079BA0 = arg0 & 0xFF;
        temp_a0 = D_80079B95 + (D_80079B8F * 0x10);
        if (arg1 > 0) {
            temp_lo = arg1 * M2C_FIELD(((temp_a0 << 5) + D_801733B0), u8 *, 0xD);
            var_v0 = *(&D_800797E0 + temp_a2) + (temp_lo / 126);
            var_a1 = temp_lo % 126;
        } else {
            var_a0 = arg1 * M2C_FIELD(((temp_a0 << 5) + D_801733B0), u8 *, 0xC);
            var_v1 = var_a0;
            if (var_a0 < 0) {
                var_v1 = var_a0 + 0x7F;
            }
            var_v0 = (*(&D_800797E0 + temp_a2) + (var_v1 >> 7)) - 1;
            if (var_a0 < 0) {
                var_a0 += 0x7F;
            }
            var_a1 = (s32) ((u32) var_a0 >> 7);
        }
        M2C_FIELD(((temp_v1 * 8 * 2) + D_8007745C), s16 *, 4) = func_8004C27C(var_v0, (s16) var_a1, temp_a2, arg0);
    }
}

s32 func_8004D328(s32 arg0, s16 arg1, s16 arg2) {
    void *temp_v1;

    if ((u32) (arg0 & 0xFFFF) >= 0x18U) {
        return -1;
    }
    temp_v1 = ((s32) (arg0 << 0x10) >> 0xC) + D_8007745C;
    M2C_FIELD(temp_v1, s16 *, 0) = (s16) (arg1 * 0x81);
    M2C_FIELD(temp_v1, s16 *, 2) = (s16) (arg2 * 0x81);
    return 0;
}

void func_8004D8C4(void) {
    M2C_UNK *var_v1_3;
    s32 *var_v0;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a1;
    s32 var_a1_2;
    u16 *var_a2;
    u16 *var_a2_2;
    u16 *var_v1;
    u16 *var_v1_2;
    u16 temp_v0;
    u16 temp_v0_2;

    func_80048F80();
    func_80058D0C();
    var_a2 = (u16 *)0x1F801C00;
    var_a0 = 0;
    do {
        var_a1 = 0;
        var_v1 = &D_80076B5C;
loop_2:
        temp_v0 = *var_v1;
        var_v1 += 2;
        var_a1 += 1;
        *var_a2 = temp_v0;
        var_a2 += 2;
        if (var_a1 < 8) {
            goto loop_2;
        }
        var_a0 += 1;
    } while (var_a0 < 0x18);
    var_a2_2 = (u16 *)0x1F801D80;
    var_a0_2 = 0;
    var_v1_2 = &D_80076B6C;
    do {
        temp_v0_2 = *var_v1_2;
        var_v1_2 += 2;
        var_a0_2 += 1;
        *var_a2_2 = temp_v0_2;
        var_a2_2 += 2;
    } while (var_a0_2 < 0x10);
    func_8004986C(0x18, var_a1, var_a2_2, &D_80076B5C);
    var_a1_2 = 0;
    var_v1_3 = &D_8012D0C8;
    do {
        var_a0_3 = 0xF;
        var_v0 = var_v1_3 + 0x3C;
loop_8:
        *var_v0 = 0;
        var_a0_3 -= 1;
        var_v0 -= 4;
        if (var_a0_3 >= 0) {
            goto loop_8;
        }
        var_a1_2 += 1;
        var_v1_3 += 0x40;
    } while (var_a1_2 < 0x20);
    D_801D9028 = 0x3C;
    D_801D7798 = 0;
}

void func_8004DC34(void) {
    M2C_UNK var_a0;
    M2C_UNK var_s0;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v1;

    var_v1 = 3;
    do {
        var_v1 += 3;
    } while (var_v1 < 0xBB8);
    switch (D_801D7E20) {
    case 0:
        break;
    case 1:
        func_80049638();
        func_8004DF4C(0xF2000003);
        func_80049718(0xF2000003, 1, 0x1000);
        func_8004DC18();
        func_8004DC18();
        func_800497A8(0xF2000003);
        var_a0 = 0xF2000003;
block_17:
        temp_v0 = func_8004DF5C(var_a0, 2, 0x1000, &func_8004E178);
        D_80077600 = temp_v0;
        func_8004DF2C(temp_v0);
        func_800497D8();
        break;
    case 3:
        func_80049638();
        func_8004DF4C(0xF2000002);
        func_80049718(0xF2000002, 0x89D0, 0x1000);
        func_8004DC18();
        func_8004DC18();
        func_800497A8(0xF2000002);
        var_a0 = 0xF2000002;
        goto block_17;
    case 2:
        func_80049638();
        func_8004DF4C(0xF2000002);
        func_80049718(0xF2000002, 0x44E8, 0x1000);
        func_8004DC18();
        func_8004DC18();
        func_800497A8(0xF2000002);
        var_a0 = 0xF2000002;
        goto block_17;
    default:
        if (D_8012D0C0 == 0) {
            if (D_801D7E20 < 0x46) {
                var_v0 = 0x3D86 / (s32) D_801D7E20;
                var_s0 = 0xF2000001;
            } else {
                var_v0 = 0x409980 / (s32) D_801D7E20;
                var_s0 = 0xF2000002;
            }
            func_80049638();
            func_8004DF4C(var_s0);
            func_80049718(var_s0, var_v0 & 0xFFFF, 0x1000);
            func_8004DC18();
            func_8004DC18();
            func_800497A8(var_s0);
            var_a0 = var_s0;
            goto block_17;
        }
        break;
    }
}

void func_8004DF6C(s16 arg0, s16 arg1) {
    s32 sp10;
    s16 sp14;
    s16 sp16;

    sp10 = 3;
    sp14 = arg0 * 0x81;
    sp16 = arg1 * 0x81;
    func_80055E2C(0, 0x100, &sp10);
}

void func_8004E91C(s16 arg0, s16 arg1) {
    s16 temp_v0;
    s16 temp_v1_2;
    s32 *temp_t1;
    s32 temp_a1;
    s32 temp_t0;
    s32 temp_v1;
    s32 temp_v1_3;
    s32 var_s4;
    s32 var_v0;
    void *temp_a0;
    void *temp_v0_2;
    void *var_v1;

    temp_t1 = (arg0 * 4) + &D_801E90E8;
    temp_t0 = arg1 * 0xA8;
    temp_a0 = temp_t0 + *temp_t1;
    temp_v0 = M2C_FIELD(temp_a0, s16 *, 0x6E);
    temp_v1 = M2C_FIELD(temp_a0, s32 *, 0x88);
    temp_a1 = temp_v1 - temp_v0;
    if (temp_a1 > 0) {
        temp_v1_2 = M2C_FIELD(temp_a0, s16 *, 0x6C);
        if (temp_v1_2 > 0) {
            M2C_FIELD(temp_a0, s16 *, 0x6C) = (s16) (temp_v1_2 - 1);
            return;
        }
        if (temp_v1_2 == 0) {
            M2C_FIELD(temp_a0, s16 *, 0x6C) = temp_v0;
            var_v1 = temp_t0 + *temp_t1;
            var_v0 = M2C_FIELD(var_v1, s32 *, 0x88) - 1;
            goto block_12;
        }
        M2C_FIELD(temp_a0, s32 *, 0x88) = temp_a1;
        return;
    }
    var_s4 = temp_v1;
    if (temp_v0 >= temp_v1) {
        do {
loop_9:
            func_8004EADC(arg0, arg1);
            temp_v1_3 = arg1 * 0xA8;
            if (M2C_FIELD((temp_v1_3 + *((arg0 * 4) + &D_801E90E8)), s32 *, 0x88) == 0) {
                goto loop_9;
            }
            temp_v0_2 = temp_v1_3 + *(&D_801E90E8 + (arg0 * 4));
            var_s4 += M2C_FIELD(temp_v0_2, s32 *, 0x88);
        } while (var_s4 < M2C_FIELD(temp_v0_2, s16 *, 0x6E));
        var_v1 = (arg1 * 0xA8) + *(((s32) (arg0 << 0x10) >> 0xE) + &D_801E90E8);
        var_v0 = var_s4 - M2C_FIELD(var_v1, s16 *, 0x6E);
block_12:
        M2C_FIELD(var_v1, s32 *, 0x88) = var_v0;
    }
}

void func_8004EE3C(s16 arg0, s16 arg1, s32 arg2, s32 arg3) {
    s32 temp_a3;
    u8 temp_a0;
    void *temp_a1;
    void *temp_v0;

    temp_a1 = (arg1 * 0xA8) + *(&D_801E90E8 + (arg0 * 4));
    temp_a0 = M2C_FIELD(temp_a1, u8 *, 0x12);
    temp_a3 = arg3 & 0xFF;
    temp_v0 = temp_a1 + temp_a0;
    if (temp_a3 != 0) {
        func_8004ADB8(arg0, M2C_FIELD(temp_a1, s16 *, 0x4A), M2C_FIELD(temp_v0, u8 *, 0x2C), arg2 & 0xFF, (s32) (s16) ((s32) (temp_a3 * M2C_FIELD(((temp_a0 * 2) + temp_a1), s16 *, 0x4C)) / 127), (s32) M2C_FIELD(temp_v0, u8 *, 0x17));
        return;
    }
    func_8004B1BC(arg0, M2C_FIELD(temp_a1, s16 *, 0x4A), M2C_FIELD(temp_v0, u8 *, 0x2C), arg2 & 0xFF);
}

void func_8004EF34(s16 arg0, s16 arg1, s8 arg2) {
    s32 *temp_s1;
    s32 temp_s0;
    void *temp_v0;

    temp_s1 = (arg0 * 4) + &D_801E90E8;
    temp_s0 = arg1 * 0xA8;
    temp_v0 = temp_s0 + *temp_s1;
    M2C_FIELD((temp_v0 + M2C_FIELD(temp_v0, u8 *, 0x12)), s8 *, 0x2C) = arg2;
    M2C_FIELD((temp_s0 + *temp_s1), s32 *, 0x88) = func_80050DF8(arg0, arg1);
}

void func_80050858(s16 arg0, s16 arg1) {
    s32 *temp_s3;
    s32 temp_s0;
    u8 *temp_a0;
    void *temp_v0;
    void *temp_v1;

    temp_s3 = (arg0 * 4) + &D_801E90E8;
    temp_s0 = arg1 * 0xA8;
    temp_v1 = temp_s0 + *temp_s3;
    temp_a0 = M2C_FIELD(temp_v1, u8 **, 4);
    M2C_FIELD(temp_v1, u8 **, 4) = (u8 *) (temp_a0 + 1);
    temp_v0 = temp_s0 + *temp_s3;
    func_8004AA64(arg0, M2C_FIELD(temp_v0, s16 *, 0x4A), M2C_FIELD((M2C_FIELD(temp_v1, u8 *, 0x12) + temp_v0), u8 *, 0x2C), *temp_a0);
    M2C_FIELD((temp_s0 + *temp_s3), s32 *, 0x88) = func_80050DF8(arg0, arg1);
}

void func_80051C6C(void) {
    func_80052974();
}

void func_80051CAC(void) {
    func_80052BF0();
}

s32 func_80051F8C(s32 arg0, M2C_UNK arg1, s8 arg2) {
    s8 sp10;
    M2C_UNK var_s0;
    s32 temp_v1;
    s32 var_v0;

    temp_v1 = arg2 & 0x30;
    if (temp_v1 != 0) {
        var_s0 = 0x249;
        if (temp_v1 != 0x20) {
            var_s0 = 0x246;
        }
    } else {
        var_s0 = 0x200;
    }
    var_v0 = func_80052D14(2, &D_80077608, 0, 0);
    if (var_v0 == 0) {
        sp10 = arg2;
        var_v0 = func_80052D14(0xE, &sp10, 0, 0);
        if (var_v0 == 0) {
            func_8005223C(func_80052368(&D_80077608) + arg0, &D_80077608);
            var_v0 = func_800532C8(arg1, arg0, var_s0, 0) == 0;
        }
    }
    return var_v0;
}

s32 func_800520CC(void) {
    func_800530A8();
    return 1;
}

void func_800521A0(s8 arg0) {
    s8 sp10;

    sp10 = arg0;
    func_80051E30(0xE, &sp10, 0);
}

void func_80053528(void) {
    func_80053630();
    VSync(0);
    func_80051BC4();
    VSync(0);
    func_80051CCC(&func_800535A0);
    VSync(0);
    func_80051CE4(&func_800535C8);
    VSync(0);
    func_80051CFC(&func_800535F0);
}

void func_800536D8(void) {
    func_80051EF0(8, 0, 0);
}

void func_800545DC(void) {
    D_800776A0 = 0;
    D_80077698 = 0;
    D_80077690 = 0;
    D_8012CDE0 = 0;
    func_8005486C(0, D_80077688);
    D_8012CFE8 = 0;
}

void func_80054730(s32 arg0, M2C_UNK arg2, M2C_UNK arg3, s32 arg4, s32 arg5) {
    func_8005495C(1, arg2, arg3);
    D_80077670 = arg0;
    D_80077678 = 0;
    D_80077668 = 0;
    D_800776C0 = arg4;
    D_800776C8 = arg5;
}

s32 func_800569D8(void *arg0) {
    s32 temp_a1;
    s32 temp_a1_2;
    u32 temp_a0;
    void *temp_a3;
    void *temp_v0;
    void *temp_v0_2;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0);
    temp_a3 = (temp_a1 * 0x10) + D_8007758C;
    M2C_FIELD(arg0, u16 *, 8) = (u16) M2C_FIELD(temp_a3, u16 *, 0);
    M2C_FIELD(arg0, u16 *, 0xA) = (u16) M2C_FIELD(temp_a3, u16 *, 2);
    temp_v0 = (temp_a1 * 4) + D_8007758C;
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) M2C_FIELD(temp_v0, u16 *, 0x200);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(temp_v0, u16 *, 0x202);
    M2C_FIELD(arg0, u16 *, 0x10) = (u16) M2C_FIELD(temp_a3, u16 *, 4);
    temp_a0 = (u32) (M2C_FIELD(D_8007758C, u16 *, 0x1AC) & 0xE) >> 1;
    temp_a1_2 = temp_a1 * 8;
    if (D_800776F0 == 0) {
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(temp_a3, u16 *, 6);
    } else {
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(temp_a3, u16 *, 6) << (temp_a0 + 1));
    }
    if (D_800776F0 == 0) {
        M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(((temp_a1_2 * 2) + D_8007758C), u16 *, 0xE);
    } else {
        M2C_FIELD(arg0, s32 *, 0x18) = (s32) (M2C_FIELD(((temp_a1_2 * 2) + D_8007758C), u16 *, 0xE) << (temp_a0 + 1));
    }
    temp_v0_2 = (temp_a1_2 * 2) + D_8007758C;
    M2C_FIELD(arg0, u16 *, 0x12) = (u16) M2C_FIELD(temp_v0_2, u16 *, 0xC);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) ((M2C_FIELD(temp_v0_2, u16 *, 8) & 0xFFFF) << (M2C_FIELD(temp_v0_2, u16 *, 0xA) + 0x10));
    return 0;
}

s32 func_80056AF4(void *arg0) {
    s32 temp_a1;
    s32 temp_a2;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0);
    temp_a2 = temp_a1 == 0;
    if ((temp_a2 != 0) || (temp_a1 & 1)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1C0) = (u16) M2C_FIELD(arg0, u16 *, 4);
    }
    if ((temp_a2 != 0) || (temp_a1 & 2)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1C2) = (u16) M2C_FIELD(arg0, u16 *, 6);
    }
    if ((temp_a2 != 0) || (temp_a1 & 4)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1C4) = (u16) M2C_FIELD(arg0, u16 *, 8);
    }
    if ((temp_a2 != 0) || (temp_a1 & 8)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1C6) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1C8) = (u16) M2C_FIELD(arg0, u16 *, 0xC);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1CA) = (u16) M2C_FIELD(arg0, u16 *, 0xE);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1CC) = (u16) M2C_FIELD(arg0, u16 *, 0x10);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x80)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1CE) = (u16) M2C_FIELD(arg0, u16 *, 0x12);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x100)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1D0) = (u16) M2C_FIELD(arg0, u16 *, 0x14);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x200)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1D2) = (u16) M2C_FIELD(arg0, u16 *, 0x16);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x400)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1D4) = (u16) M2C_FIELD(arg0, u16 *, 0x18);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x800)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1D6) = (u16) M2C_FIELD(arg0, u16 *, 0x1A);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x1000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1D8) = (u16) M2C_FIELD(arg0, u16 *, 0x1C);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x2000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1DA) = (u16) M2C_FIELD(arg0, u16 *, 0x1E);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x4000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1DC) = (u16) M2C_FIELD(arg0, u16 *, 0x20);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x8000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1DE) = (u16) M2C_FIELD(arg0, u16 *, 0x22);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1E0) = (u16) M2C_FIELD(arg0, u16 *, 0x24);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1E2) = (u16) M2C_FIELD(arg0, u16 *, 0x26);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1E4) = (u16) M2C_FIELD(arg0, u16 *, 0x28);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x80000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1E6) = (u16) M2C_FIELD(arg0, u16 *, 0x2A);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x100000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1E8) = (u16) M2C_FIELD(arg0, u16 *, 0x2C);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x200000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1EA) = (u16) M2C_FIELD(arg0, u16 *, 0x2E);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x400000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1EC) = (u16) M2C_FIELD(arg0, u16 *, 0x30);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x800000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1EE) = (u16) M2C_FIELD(arg0, u16 *, 0x32);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x01000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1F0) = (u16) M2C_FIELD(arg0, u16 *, 0x34);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x02000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1F2) = (u16) M2C_FIELD(arg0, u16 *, 0x36);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x04000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1F4) = (u16) M2C_FIELD(arg0, u16 *, 0x38);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x08000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1F6) = (u16) M2C_FIELD(arg0, u16 *, 0x3A);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x10000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1F8) = (u16) M2C_FIELD(arg0, u16 *, 0x3C);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x20000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1FA) = (u16) M2C_FIELD(arg0, u16 *, 0x3E);
    }
    if ((temp_a2 != 0) || (temp_a1 & 0x40000000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1FC) = (u16) M2C_FIELD(arg0, u16 *, 0x40);
    }
    if ((temp_a2 != 0) || (temp_a1 < 0)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1FE) = (u16) M2C_FIELD(arg0, u16 *, 0x42);
    }
    return 0;
}

s32 func_80056FC4(void *arg0) {
    M2C_FIELD(arg0, u16 *, 4) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1C0);
    M2C_FIELD(arg0, u16 *, 6) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1C2);
    M2C_FIELD(arg0, u16 *, 8) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1C4);
    M2C_FIELD(arg0, u16 *, 0xA) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1C6);
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1C8);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1CA);
    M2C_FIELD(arg0, u16 *, 0x10) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1CC);
    M2C_FIELD(arg0, u16 *, 0x12) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1CE);
    M2C_FIELD(arg0, u16 *, 0x14) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1D0);
    M2C_FIELD(arg0, u16 *, 0x16) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1D2);
    M2C_FIELD(arg0, u16 *, 0x18) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1D4);
    M2C_FIELD(arg0, u16 *, 0x1A) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1D6);
    M2C_FIELD(arg0, u16 *, 0x1C) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1D8);
    M2C_FIELD(arg0, u16 *, 0x1E) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1DA);
    M2C_FIELD(arg0, u16 *, 0x20) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1DC);
    M2C_FIELD(arg0, u16 *, 0x22) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1DE);
    M2C_FIELD(arg0, u16 *, 0x24) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1E0);
    M2C_FIELD(arg0, u16 *, 0x26) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1E2);
    M2C_FIELD(arg0, u16 *, 0x28) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1E4);
    M2C_FIELD(arg0, u16 *, 0x2A) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1E6);
    M2C_FIELD(arg0, u16 *, 0x2C) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1E8);
    M2C_FIELD(arg0, u16 *, 0x2E) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1EA);
    M2C_FIELD(arg0, u16 *, 0x30) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1EC);
    M2C_FIELD(arg0, u16 *, 0x32) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1EE);
    M2C_FIELD(arg0, u16 *, 0x34) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1F0);
    M2C_FIELD(arg0, u16 *, 0x36) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1F2);
    M2C_FIELD(arg0, u16 *, 0x38) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1F4);
    M2C_FIELD(arg0, u16 *, 0x3A) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1F6);
    M2C_FIELD(arg0, u16 *, 0x3C) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1F8);
    M2C_FIELD(arg0, u16 *, 0x3E) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1FA);
    M2C_FIELD(arg0, u16 *, 0x40) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1FC);
    M2C_FIELD(arg0, u16 *, 0x42) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1FE);
    return 0;
}

s32 func_80057158(void *arg0) {
    s16 var_v0;
    s16 var_v0_2;
    s16 var_v0_3;
    s16 var_v0_4;
    s32 temp_a1;
    s32 temp_a3;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0);
    temp_a3 = temp_a1 == 0;
    if ((temp_a3 != 0) || (temp_a1 & 1)) {
        M2C_FIELD(D_8007758C, u16 *, 0x180) = (u16) M2C_FIELD(arg0, u16 *, 4);
    }
    if ((temp_a3 != 0) || (temp_a1 & 2)) {
        M2C_FIELD(D_8007758C, u16 *, 0x182) = (u16) M2C_FIELD(arg0, u16 *, 6);
    }
    if ((temp_a3 != 0) || (temp_a1 & 4)) {
        M2C_FIELD(D_8007758C, u16 *, 0x184) = (u16) M2C_FIELD(arg0, u16 *, 8);
    }
    if ((temp_a3 != 0) || (temp_a1 & 8)) {
        M2C_FIELD(D_8007758C, u16 *, 0x186) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
    }
    if ((temp_a3 != 0) || (temp_a1 & 0x10)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1B0) = (u16) M2C_FIELD(arg0, u16 *, 0xC);
    }
    if ((temp_a3 != 0) || (temp_a1 & 0x20)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1B2) = (u16) M2C_FIELD(arg0, u16 *, 0xE);
    }
    if ((temp_a3 != 0) || (temp_a1 & 0x100)) {
        if (M2C_FIELD(arg0, s32 *, 0x10) == 0) {
            var_v0 = M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 0xFFFB;
        } else {
            var_v0 = M2C_FIELD(D_8007758C, u16 *, 0x1AA) | 4;
        }
        M2C_FIELD(D_8007758C, s16 *, 0x1AA) = var_v0;
    }
    if ((temp_a3 != 0) || (temp_a1 & 0x400)) {
        if (M2C_FIELD(arg0, s32 *, 0x14) == 0) {
            var_v0_2 = M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 0xFFFE;
        } else {
            var_v0_2 = M2C_FIELD(D_8007758C, u16 *, 0x1AA) | 1;
        }
        M2C_FIELD(D_8007758C, s16 *, 0x1AA) = var_v0_2;
    }
    if ((temp_a3 != 0) || (temp_a1 & 0x40)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1B4) = (u16) M2C_FIELD(arg0, u16 *, 0x18);
    }
    if ((temp_a3 != 0) || (temp_a1 & 0x80)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1B6) = (u16) M2C_FIELD(arg0, u16 *, 0x1A);
    }
    if ((temp_a3 != 0) || (temp_a1 & 0x200)) {
        if (M2C_FIELD(arg0, s32 *, 0x1C) == 0) {
            var_v0_3 = M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 0xFFF7;
        } else {
            var_v0_3 = M2C_FIELD(D_8007758C, u16 *, 0x1AA) | 8;
        }
        M2C_FIELD(D_8007758C, s16 *, 0x1AA) = var_v0_3;
    }
    if ((temp_a3 != 0) || (temp_a1 & 0x800)) {
        if (M2C_FIELD(arg0, s32 *, 0x20) == 0) {
            var_v0_4 = M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 0xFFFD;
        } else {
            var_v0_4 = M2C_FIELD(D_8007758C, u16 *, 0x1AA) | 2;
        }
        M2C_FIELD(D_8007758C, s16 *, 0x1AA) = var_v0_4;
    }
    if ((temp_a3 != 0) || (temp_a1 & 0x1000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1AA) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 0xC0FF);
        M2C_FIELD(D_8007758C, u16 *, 0x1AA) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x1AA) | ((M2C_FIELD(arg0, u16 *, 0x24) & 0x3F) << 8));
    }
    if ((temp_a3 != 0) || (temp_a1 & 0x2000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1AA) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 0xFF7F);
        M2C_FIELD(D_8007758C, u16 *, 0x1AA) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x1AA) | ((M2C_FIELD(arg0, u16 *, 0x26) & 1) << 7));
    }
    if ((temp_a3 != 0) || (temp_a1 & 0x4000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1AC) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x1AC) & 0xFFF1);
        M2C_FIELD(D_8007758C, u16 *, 0x1AC) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x1AC) | ((M2C_FIELD(arg0, u16 *, 0x28) & 7) * 2));
    }
    if ((temp_a3 != 0) || (temp_a1 & 0x8000)) {
        M2C_FIELD(D_8007758C, u16 *, 0x1AC) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x1AC) & 0xFFFE);
        M2C_FIELD(D_8007758C, u16 *, 0x1AC) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x1AC) | (M2C_FIELD(arg0, u16 *, 0x2A) & 1));
    }
    return 0;
}

s32 func_800574F0(void *arg0) {
    M2C_FIELD(arg0, u16 *, 4) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x180);
    M2C_FIELD(arg0, u16 *, 6) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x182);
    M2C_FIELD(arg0, u16 *, 8) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x184);
    M2C_FIELD(arg0, u16 *, 0xA) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x186);
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1B0);
    M2C_FIELD(arg0, u16 *, 0xE) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1B2);
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) (((u16) M2C_FIELD(D_8007758C, u16 *, 0x1AA) >> 2) & 1);
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) (M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 1);
    M2C_FIELD(arg0, u16 *, 0x18) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1B4);
    M2C_FIELD(arg0, u16 *, 0x1A) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1B6);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (((u16) M2C_FIELD(D_8007758C, u16 *, 0x1AA) >> 3) & 1);
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (((u16) M2C_FIELD(D_8007758C, u16 *, 0x1AA) >> 1) & 1);
    M2C_FIELD(arg0, s16 *, 0x24) = (s16) ((u32) (M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 0x3F00) >> 8);
    M2C_FIELD(arg0, s16 *, 0x26) = (s16) (((u16) M2C_FIELD(D_8007758C, u16 *, 0x1AA) >> 7) & 1);
    M2C_FIELD(arg0, s16 *, 0x28) = (s16) ((u32) (M2C_FIELD(D_8007758C, u16 *, 0x1AC) & 0xE) >> 1);
    M2C_FIELD(arg0, s16 *, 0x2A) = (s16) (M2C_FIELD(D_8007758C, u16 *, 0x1AC) & 1);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(D_8007758C, u16 *, 0x19C) | (M2C_FIELD(D_8007758C, u16 *, 0x19E) << 0x10));
    M2C_FIELD(arg0, u16 *, 0x30) = (u16) M2C_FIELD(D_8007758C, u16 *, 0x1AE);
    return 0;
}

void func_80057654(void) {
    if (D_800776F8 == 0) {
        func_80055570();
        func_80055570();
    }
    M2C_FIELD(D_8007758C, u16 *, 0x1AA) = (u16) (M2C_FIELD(D_8007758C, u16 *, 0x1AA) & 0xFFCF);
    func_80053618(0xF0000009, 0x20);
    func_800490D4(0);
}

void func_800576B8(void) {
    func_80053618(0xF0000009, 2);
    func_80049164(0);
}

s32 func_80058214(s32 arg0, void *arg1) {
    s32 temp_a0;

    if (arg0 <= 0) {
        return 0;
    }
    M2C_FIELD(arg1, s32 *, 0) = 0x40001000;
    D_80077728 = arg1;
    D_800775B4 = 0;
    D_800775B0 = arg0;
    temp_a0 = ((u32) (M2C_FIELD(D_800775AC, u16 *, 0x1AC) & 0xE) >> 1) + 1;
    D_80077720 = temp_a0;
    M2C_FIELD(arg1, s32 *, 4) = (s32) ((0x10000 << temp_a0) - 0x1000);
    return arg0;
}

void func_80058E58(void) {
    if (D_800775B8 == 1) {
        D_800775B8 = 0;
        func_80049638();
        func_8004DF1C(D_801E9228);
        func_8004DF3C(D_801E9228);
        func_800497D8();
    }
}

void func_80013200(void) {
    func_80013184();
    D_801D3584 = ((D_8012CF58 < 0x88) - 1) & 0x64;
}

void func_8001CEC8(void) {
    s32 temp_v0;

    func_8001CE0C();
    if (D_801E90B0 == -1) {
        temp_v0 = D_801E90C8 + 1;
        D_801E90C8 = temp_v0;
        if (temp_v0 >= 0x1C21) {
            func_8001CEA0();
        }
    }
}

s32 func_80058544(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 temp_t0;
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 var_a2;
    s32 var_a3;
    s32 var_t1;
    s32 var_v0_2;
    s32 var_v1;
    void *temp_s0;
    void *temp_v0;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v1_2;
    void *temp_v1_3;
    void *var_a0;
    void *var_a1;
    void *var_v0;

    var_a1 = arg1;
    var_a2 = arg2;
    var_a3 = arg3;
    var_a0 = D_80077728;
    temp_v0 = (arg0 * 8) + var_a0;
    temp_t4 = M2C_FIELD(temp_v0, s32 *, 0);
    temp_t5 = M2C_FIELD(temp_v0, s32 *, 4);
    temp_t0 = var_a2;
    temp_s0 = var_a1;
    temp_t2 = temp_s0 - (temp_t4 & 0x0FFFFFFF);
    if (D_8007B1A0 == 0) {
        var_v1 = 0;
    } else {
        var_a0 = (void *) D_80077720;
        var_v1 = (0x10000 - D_801E9238) << (s32) var_a0;
    }
    if (temp_t4 & 0x40000000) {
        var_t1 = (temp_t5 - temp_t2) - var_v1;
    } else {
        var_t1 = temp_t5 - temp_t2;
    }
    var_v0 = (void *)-1;
    if (var_t1 >= temp_t0) {
        if (temp_t4 & 0x40000000) {
            if (temp_t2 > 0) {
                var_a3 = D_800775B4;
                var_v0 = (void *)-1;
                if ((D_800775B0 - 2) >= var_a3) {
                    var_a2 = (s32) D_80077728;
                    var_a1 = (var_a3 * 8) + var_a2;
                    temp_v0_2 = var_a3 + 1;
                    D_800775B4 = temp_v0_2;
                    M2C_FIELD(var_a1, s32 *, 4) = temp_t2;
                    temp_v0_3 = (temp_v0_2 * 8) + var_a2;
                    M2C_FIELD(var_a1, s32 *, 0) = (s32) ((M2C_FIELD(var_a1, s32 *, 0) & 0x0FFFFFFF) | 0x80000000);
                    M2C_FIELD(temp_v0_3, void **, 0) = temp_s0;
                    M2C_FIELD(temp_v0_3, s32 *, 4) = temp_t0;
                    goto block_13;
                }
            } else {
                var_v0 = (void *)-1;
                if ((D_800775B0 - 1) >= D_800775B4) {
                    temp_v0_4 = (D_800775B4 * 8) + D_80077728;
                    M2C_FIELD(temp_v0_4, s32 *, 4) = temp_t0;
                    M2C_FIELD(temp_v0_4, s32 *, 0) = (s32) (M2C_FIELD(temp_v0_4, s32 *, 0) & 0x0FFFFFFF);
block_13:
                    temp_v1 = D_800775B4 + 1;
                    D_800775B4 = temp_v1;
                    temp_v1_2 = (temp_v1 * 8) + D_80077728;
                    var_a0 = (void *)0x40000000;
                    M2C_FIELD(temp_v1_2, s32 *, 0) = (s32) (((temp_t4 & 0x0FFFFFFF) + temp_t2 + temp_t0) | 0x40000000);
                    M2C_FIELD(temp_v1_2, s32 *, 4) = (s32) ((temp_t5 - temp_t2) - temp_t0);
                    goto block_25;
                }
            }
        } else if (temp_t2 > 0) {
            if (var_t1 == temp_t0) {
                var_v0_2 = D_800775B0 - 2;
            } else {
                var_v0_2 = D_800775B0 - 1;
            }
            var_v0 = (void *)-1;
            if (var_v0_2 >= D_800775B4) {
                var_a1 = D_80077728;
                var_a3 = D_800775B4;
                M2C_FIELD(((arg0 * 8) + var_a1), s32 *, 4) = temp_t2;
                temp_v0_5 = (var_a3 * 8) + var_a1;
                temp_v1_3 = M2C_FIELD(temp_v0_5, void **, 0);
                var_a0 = M2C_FIELD(temp_v0_5, void **, 4);
                M2C_FIELD(temp_v0_5, void **, 0) = temp_s0;
                M2C_FIELD(temp_v0_5, void **, 4) = (void *) temp_t0;
                var_a2 = var_a3 + 1;
                D_800775B4 = var_a2;
                M2C_FIELD(temp_v0_5, void **, 8) = temp_v1_3;
                M2C_FIELD(temp_v0_5, void **, 0xC) = var_a0;
                if (var_t1 >= temp_t0) {
                    var_a0 = (var_a2 * 8) + var_a1;
                    var_a1 = M2C_FIELD(var_a0, void **, 0);
                    var_a2 = M2C_FIELD(var_a0, s32 *, 4);
                    M2C_FIELD(var_a0, void **, 0) = (void *) (((temp_t4 & 0x0FFFFFFF) + temp_t2 + temp_t0) | 0x80000000);
                    M2C_FIELD(var_a0, s32 *, 4) = (s32) (var_t1 - temp_t0);
                    D_800775B4 = var_a3 + 2;
                    M2C_FIELD(var_a0, void **, 8) = var_a1;
                    M2C_FIELD(var_a0, s32 *, 0xC) = var_a2;
                }
                goto block_25;
            }
        } else if ((temp_t0 >= var_t1) || (var_v0 = (void *)-1, (((D_800775B0 - 1) < D_800775B4) == 0))) {
            var_a3 = (s32) D_80077728;
            temp_v0_6 = (arg0 * 8) + var_a3;
            var_a2 = 0x0FFFFFFF;
            M2C_FIELD(temp_v0_6, s32 *, 4) = temp_t0;
            M2C_FIELD(temp_v0_6, s32 *, 0) = (s32) (M2C_FIELD(temp_v0_6, s32 *, 0) & 0x0FFFFFFF);
            if (temp_t0 < var_t1) {
                var_a0 = (D_800775B4 * 8) + var_a3;
                var_a2 = M2C_FIELD(var_a0, s32 *, 0);
                var_a3 = M2C_FIELD(var_a0, s32 *, 4);
                M2C_FIELD(var_a0, s32 *, 0) = (s32) (((temp_t4 & 0x0FFFFFFF) + temp_t0) | 0x80000000);
                M2C_FIELD(var_a0, s32 *, 4) = (s32) (var_t1 - temp_t0);
                var_a1 = D_800775B4 + 1;
                D_800775B4 = (s32) var_a1;
                M2C_FIELD(var_a0, s32 *, 8) = var_a2;
                M2C_FIELD(var_a0, s32 *, 0xC) = var_a3;
            }
block_25:
            func_80057F18(var_a0, (s32) var_a1, var_a2, (void *) var_a3);
            var_v0 = temp_s0;
        }
    }
    return (s32) var_v0;
}
