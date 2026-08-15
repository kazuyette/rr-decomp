/* b5_00.c -- batch 5, 207 functions recovered with m2c.
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
M2C_UNK SetDrawEnv(s32, M2C_UNK *, void *, M2C_UNK *);
M2C_UNK SetVideoMode(M2C_UNK);
M2C_UNK SpuVoiceKeyOn(M2C_UNK, void *);
M2C_UNK func_80012578();
M2C_UNK func_80012FE4(M2C_UNK);
M2C_UNK func_80015CD4(M2C_UNK *);
M2C_UNK func_8001602C(M2C_UNK *);
M2C_UNK func_8001613C(M2C_UNK *);
M2C_UNK func_8001624C(M2C_UNK *);
M2C_UNK func_800185F0(M2C_UNK *, s32);
M2C_UNK func_8001865C(M2C_UNK *, s32, s32);
M2C_UNK func_8001D5D4(M2C_UNK, M2C_UNK, s32, s32);
M2C_UNK func_8001FE6C(s32);
M2C_UNK func_800201B0();
M2C_UNK func_800202A0(s32);
M2C_UNK func_8002037C(s16);
M2C_UNK func_800203F0(M2C_UNK *);
M2C_UNK func_8002128C(M2C_UNK *, M2C_UNK);
M2C_UNK func_800266B8(M2C_UNK);
M2C_UNK func_80026CA8(void *);
M2C_UNK func_80028578(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK func_80028AC8(void *);
M2C_UNK func_80028C1C();
M2C_UNK func_80028CE4(M2C_UNK *);
M2C_UNK func_80028F64(s32);
M2C_UNK func_80029120(s32);
M2C_UNK func_80029A64();
M2C_UNK func_8002AB88();
M2C_UNK func_8002ACD4();
M2C_UNK func_8002E490();
M2C_UNK func_8002E528();
M2C_UNK func_8002E5E8();
M2C_UNK func_8002E710();
M2C_UNK func_8002E740();
M2C_UNK func_80030DBC();
M2C_UNK func_80030DE0();
M2C_UNK func_80031238(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32);
M2C_UNK func_800314BC(M2C_UNK);
M2C_UNK func_80032A24();
M2C_UNK func_80032D50();
M2C_UNK func_80032E18(s32, s32 *, s32, s32 *);
M2C_UNK func_800355A4(M2C_UNK);
M2C_UNK func_800366FC(M2C_UNK *);
M2C_UNK func_8003776C();
M2C_UNK func_80037850(s32);
M2C_UNK func_80037C74(M2C_UNK);
M2C_UNK func_80037D38(M2C_UNK *);
M2C_UNK func_80039D88(s16, M2C_UNK, s16, M2C_UNK);
M2C_UNK func_8003A1AC(M2C_UNK);
M2C_UNK func_8003A1BC();
M2C_UNK func_8003A1D8();
M2C_UNK func_8003A2C8(M2C_UNK);
M2C_UNK func_8003A588();
M2C_UNK func_8003A5A4(M2C_UNK);
M2C_UNK func_8003A600(M2C_UNK);
M2C_UNK func_8003A640(s32);
M2C_UNK func_8003A65C(M2C_UNK);
M2C_UNK func_8003AEC0();
M2C_UNK func_8003B118(s16, s16);
M2C_UNK func_8003B26C(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8003B2E4(M2C_UNK, M2C_UNK);
M2C_UNK func_8003B340(M2C_UNK);
M2C_UNK func_8003B388(u16);
M2C_UNK func_8003DFE0();
M2C_UNK func_8003E128(M2C_UNK, M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK func_8003E2D4(s32, s32, void *, M2C_UNK);
M2C_UNK func_8003FBE8(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8003FC08(M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK func_8003FCC0(s32);
M2C_UNK func_8003FCCC(M2C_UNK);
M2C_UNK func_8004059C(s32, s32 *, M2C_UNK *);
M2C_UNK func_80040DC8(s32, s32, void *);
M2C_UNK func_80042E08(M2C_UNK *, M2C_UNK *);
M2C_UNK func_8004315C(M2C_UNK *, void *, void *);
M2C_UNK func_80043470(M2C_UNK, s32);
M2C_UNK func_800434A0(M2C_UNK *);
M2C_UNK func_800434D0(M2C_UNK *);
M2C_UNK func_80043500(void *);
M2C_UNK func_80043738();
M2C_UNK func_80043B08(s32, s32, s32, M2C_UNK *);
M2C_UNK func_80043B98(void *, void *, M2C_UNK *);
M2C_UNK func_80044F64(M2C_UNK, M2C_UNK);
M2C_UNK func_800456B4(M2C_UNK);
M2C_UNK func_80045750(M2C_UNK);
M2C_UNK func_80045790(M2C_UNK);
M2C_UNK func_80045854(s16 *, s32 *);
M2C_UNK func_800458B8(s16 *, s32 *);
M2C_UNK func_8004617C(s32, M2C_UNK, M2C_UNK, s32, M2C_UNK *);
M2C_UNK func_80046738(M2C_UNK, s32 *, s32);
M2C_UNK func_80047210(s32, void *, M2C_UNK);
M2C_UNK func_80047834(void *);
M2C_UNK func_80047B20(void *, M2C_UNK);
M2C_UNK func_80047C10();
M2C_UNK func_80048198(M2C_UNK *, M2C_UNK *, s32);
M2C_UNK func_80048ADC(s32);
M2C_UNK func_80048CCC(M2C_UNK *, void *);
M2C_UNK func_80048FC0();
M2C_UNK func_800491AC(M2C_UNK, s32);
M2C_UNK func_8004922C(M2C_UNK, s32);
M2C_UNK func_800492B0();
M2C_UNK func_80049580();
M2C_UNK func_80049638();
M2C_UNK func_80049648(s32);
M2C_UNK func_80049658(s32);
M2C_UNK func_800496C8(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_80049728(M2C_UNK);
M2C_UNK func_80049778();
M2C_UNK func_80049788();
M2C_UNK func_800497D8();
M2C_UNK func_80049808();
M2C_UNK func_8004A8D0(s32);
M2C_UNK func_8004A9D4(s32, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_8004ACE4(s16, s16);
M2C_UNK func_8004ADB8(M2C_UNK, s16, s16, s32, s32, s32);
M2C_UNK func_8004B1BC(M2C_UNK, s16, s16, s32);
M2C_UNK func_8004B310();
M2C_UNK func_8004B900(s16, s16);
M2C_UNK func_8004C0B8(M2C_UNK);
M2C_UNK func_8004C74C(s16, s16, s16, s16, s32);
M2C_UNK func_8004C8AC(s32, s16, s16, s32, s32, s32, s32);
M2C_UNK func_8004CC08(s16, u8, u8 *, s16);
M2C_UNK func_8004CDDC(s16, u8, s32, M2C_UNK *);
M2C_UNK func_8004D018(s16, u8, s32, M2C_UNK *);
M2C_UNK func_8004D8C4();
M2C_UNK func_8004D9B4(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_8004DB58(M2C_UNK);
M2C_UNK func_8004DC34();
M2C_UNK func_8004DF1C(s32);
M2C_UNK func_8004DF3C(s32);
M2C_UNK func_8004DF6C(M2C_UNK, M2C_UNK);
M2C_UNK func_8004E178();
M2C_UNK func_8004E91C(s16, s16);
M2C_UNK func_8004EE3C(s16, s16, u8, u8);
M2C_UNK func_8004EF34(s16, s16, u8);
M2C_UNK func_8004EFB8(s16, s16, u8);
M2C_UNK func_80050858(s16, s16, u8);
M2C_UNK func_80050918(s16, s16, u8);
M2C_UNK func_80051C6C(M2C_UNK, M2C_UNK);
M2C_UNK func_80051CCC(M2C_UNK *);
M2C_UNK func_80051CE4(M2C_UNK *);
M2C_UNK func_80051CFC(M2C_UNK *);
M2C_UNK func_80051E30(M2C_UNK, void *, M2C_UNK);
M2C_UNK func_80051EF0(M2C_UNK, M2C_UNK, u8 *);
M2C_UNK func_80051F8C(u32, M2C_UNK, M2C_UNK);
M2C_UNK func_800520CC(s8 *);
M2C_UNK func_80052440(M2C_UNK, M2C_UNK *, M2C_UNK);
M2C_UNK func_80052504(M2C_UNK);
M2C_UNK func_80052854();
M2C_UNK func_80052A98();
M2C_UNK func_8005486C(M2C_UNK);
M2C_UNK func_8005495C(M2C_UNK);
M2C_UNK func_80055810(u32);
M2C_UNK func_80055E2C(M2C_UNK, M2C_UNK, s32 *, s16);
M2C_UNK func_800578C4();
M2C_UNK func_80057A24(s32 *);
M2C_UNK func_80058214(M2C_UNK, M2C_UNK *);
M2C_UNK func_80058E58();
M2C_UNK func_80058EB8(M2C_UNK);
M2C_UNK func_80059014(M2C_UNK);
M2C_UNK func_80059060(M2C_UNK);
M2C_UNK func_800590B4(s32);
M2C_UNK snd_play_se(s16, void *);
M2C_UNK st_title_init();
extern M2C_UNK (*D_80077370)(M2C_UNK *, s32, s32, s32);
extern M2C_UNK *D_80173180;
extern M2C_UNK *D_801D7760;
extern M2C_UNK *D_A00003E0;
extern M2C_UNK *D_A00003F0;
extern M2C_UNK *D_A00003F8;
extern M2C_UNK *D_A0000414;
extern M2C_UNK D_7FFFFF;
extern M2C_UNK D_80010158;
extern M2C_UNK D_80010170;
extern M2C_UNK D_80010184;
extern M2C_UNK D_80010244;
extern M2C_UNK D_80010250;
extern M2C_UNK D_80010330;
extern M2C_UNK D_800105D4;
extern M2C_UNK D_800105FC;
extern M2C_UNK D_80010610;
extern M2C_UNK D_80010624;
extern M2C_UNK D_80010800;
extern M2C_UNK D_80010948;
extern M2C_UNK D_80010968;
extern M2C_UNK D_8001097C;
extern M2C_UNK D_80010988;
extern M2C_UNK D_80010F20;
extern M2C_UNK D_80010F70;
extern M2C_UNK D_80010FB8;
extern M2C_UNK D_800593B0;
extern M2C_UNK D_8005E90E;
extern M2C_UNK D_8005E910;
extern M2C_UNK D_8005E912;
extern M2C_UNK D_8005E916;
extern M2C_UNK D_8005E93C;
extern M2C_UNK D_8005F140;
extern M2C_UNK D_8005F2A0;
extern M2C_UNK D_80070F44;
extern M2C_UNK D_80070FEC;
extern M2C_UNK D_80071094;
extern M2C_UNK D_8007113C;
extern M2C_UNK D_800711E4;
extern M2C_UNK D_80071784;
extern M2C_UNK D_80071D64;
extern M2C_UNK D_80072A30;
extern M2C_UNK D_80072F60;
extern M2C_UNK D_80072FF8;
extern M2C_UNK D_80073034;
extern M2C_UNK D_8007307C;
extern M2C_UNK D_800730B0;
extern M2C_UNK D_800730D4;
extern M2C_UNK D_800730E4;
extern M2C_UNK D_80073104;
extern M2C_UNK D_80073E5C;
extern M2C_UNK D_80074108;
extern M2C_UNK D_80074128;
extern M2C_UNK D_80074158;
extern M2C_UNK D_80074188;
extern M2C_UNK D_800741D0;
extern M2C_UNK D_80074368;
extern M2C_UNK D_80074388;
extern M2C_UNK D_800747E0;
extern M2C_UNK D_80074DBC;
extern M2C_UNK D_80074FBC;
extern M2C_UNK D_800750E4;
extern M2C_UNK D_80075100;
extern M2C_UNK D_80075102;
extern M2C_UNK D_8007556C;
extern M2C_UNK D_800768BC;
extern M2C_UNK D_8007691C;
extern M2C_UNK D_800769D8;
extern M2C_UNK D_80077128;
extern M2C_UNK D_80077154;
extern M2C_UNK D_80077178;
extern M2C_UNK D_800771B0;
extern M2C_UNK D_800771CC;
extern M2C_UNK D_80077268;
extern M2C_UNK D_800773BC;
extern M2C_UNK D_80077408;
extern M2C_UNK D_8007740C;
extern M2C_UNK D_800775E0;
extern M2C_UNK D_80077A48;
extern M2C_UNK D_80078748;
extern M2C_UNK D_800797D8;
extern M2C_UNK D_800797DA;
extern M2C_UNK D_800797DC;
extern M2C_UNK D_800797DE;
extern M2C_UNK D_800797E0;
extern M2C_UNK D_800797E2;
extern M2C_UNK D_800797E4;
extern M2C_UNK D_800797E6;
extern M2C_UNK D_800797E8;
extern M2C_UNK D_800797EA;
extern M2C_UNK D_800797EC;
extern M2C_UNK D_800797EF;
extern M2C_UNK D_80079A18;
extern M2C_UNK D_80079A1A;
extern M2C_UNK D_80079A1C;
extern M2C_UNK D_80079A1E;
extern M2C_UNK D_80079B20;
extern M2C_UNK D_80079B88;
extern M2C_UNK D_80079BA8;
extern M2C_UNK D_80079C68;
extern M2C_UNK D_80079CA8;
extern M2C_UNK D_80079CE8;
extern M2C_UNK D_8007A0D0;
extern M2C_UNK D_8007B200;
extern M2C_UNK D_8007C258;
extern M2C_UNK D_8007C488;
extern M2C_UNK D_8007C48C;
extern M2C_UNK D_8007C490;
extern M2C_UNK D_8007C520;
extern M2C_UNK D_8012CDF0;
extern M2C_UNK D_8012D090;
extern M2C_UNK D_8012D950;
extern M2C_UNK D_8012E4C0;
extern M2C_UNK D_801510B4;
extern M2C_UNK D_80173194;
extern M2C_UNK D_801733E0;
extern M2C_UNK D_80173448;
extern M2C_UNK D_801734E0;
extern M2C_UNK D_801A34E0;
extern M2C_UNK D_801D3500;
extern M2C_UNK D_801D3501;
extern M2C_UNK D_801D7628;
extern M2C_UNK D_801D7670;
extern M2C_UNK D_801D7672;
extern M2C_UNK D_801D7674;
extern M2C_UNK D_801D7676;
extern M2C_UNK D_801D7678;
extern M2C_UNK D_801D7770;
extern M2C_UNK D_801D7F5C;
extern M2C_UNK D_801D82D8;
extern M2C_UNK D_801E90E8;
extern M2C_UNK D_801E9180;
extern M2C_UNK D_801E91F0;
extern M2C_UNK D_801E9250;
extern M2C_UNK func_800535A0;
extern M2C_UNK func_800535C8;
extern M2C_UNK func_800535F0;
extern M2C_UNK func_80053618;
extern M2C_UNK func_800536B0;
extern M2C_UNK func_800536D8;
extern M2C_UNK func_80053700;
extern M2C_UNK func_8005373C;
extern M2C_UNK g_track_nodes_0;
extern s16 *D_801D35E8;
extern s16 D_8007727E;
extern s16 D_800772FC;
extern s16 D_80077462;
extern s16 D_80077468;
extern s16 D_800775F0;
extern s16 D_800775F8;
extern s16 D_80079B78;
extern s16 D_80079B7A;
extern s16 D_80079BA0;
extern s16 D_8007B190;
extern s16 D_8007B198;
extern s16 D_8007B1B0;
extern s16 D_8007B1D8;
extern s16 D_8007C210;
extern s16 D_8007C25A;
extern s16 D_8007C2D8;
extern s16 D_8007C32C;
extern s16 D_8012CF58;
extern s16 D_8012CFD8;
extern s16 D_8012CFF8;
extern s16 D_8012CFFA;
extern s16 D_8012CFFC;
extern s16 D_8012D018;
extern s16 D_8012D01A;
extern s16 D_8012D0B0;
extern s16 D_8012D8D0;
extern s16 D_8012D908;
extern s16 D_80173164;
extern s16 D_80173330;
extern s16 D_80173390;
extern s16 D_80173398;
extern s16 D_801733B8;
extern s16 D_801733C0;
extern s16 D_801733D0;
extern s16 D_801D34E0;
extern s16 D_801D34F0;
extern s16 D_801D34F8;
extern s16 D_801D3540;
extern s16 D_801D3542;
extern s16 D_801D3544;
extern s16 D_801D3546;
extern s16 D_801D3548;
extern s16 D_801D354A;
extern s16 D_801D354C;
extern s16 D_801D3550;
extern s16 D_801D3552;
extern s16 D_801D3556;
extern s16 D_801D3558;
extern s16 D_801D355C;
extern s16 D_801D355E;
extern s16 D_801D3562;
extern s16 D_801D3564;
extern s16 D_801D356A;
extern s16 D_801D356E;
extern s16 D_801D3570;
extern s16 D_801D3572;
extern s16 D_801D3574;
extern s16 D_801D3576;
extern s16 D_801D357A;
extern s16 D_801D357C;
extern s16 D_801D3580;
extern s16 D_801D3582;
extern s16 D_801D3586;
extern s16 D_801D35BC;
extern s16 D_801D35D0;
extern s16 D_801D7778;
extern s16 D_801D777A;
extern s16 D_801D77B8;
extern s16 D_801D77C0;
extern s16 D_801D77D8;
extern s16 D_801D7808;
extern s16 D_801D9048;
extern s16 D_801D9060;
extern s16 D_801E91A0;
extern s16 D_801E9252;
extern s16 D_801E9F48;
extern s32 *D_800773A4;
extern s32 *D_800773A8;
extern s32 *D_800773AC;
extern s32 *D_800773B0;
extern s32 *D_800774FC;
extern s32 *D_80077500;
extern s32 *D_80077504;
extern s32 *D_80077508;
extern s32 *D_8007750C;
extern s32 *D_80077510;
extern s32 *D_80173148;
extern s32 D_80072F64;
extern s32 D_80072F6C;
extern s32 D_80073018;
extern s32 D_80073050;
extern s32 D_800747BC;
extern s32 D_800747C0;
extern s32 D_800747C4;
extern s32 D_800747C8;
extern s32 D_800747CC;
extern s32 D_800747D0;
extern s32 D_800747D4;
extern s32 D_800747D8;
extern s32 D_80075938;
extern s32 D_80077144;
extern s32 D_800771C8;
extern s32 D_80077300;
extern s32 D_80077374;
extern s32 D_80077378;
extern s32 D_8007737C;
extern s32 D_800773B4;
extern s32 D_8007743C;
extern s32 D_80077454;
extern s32 D_8007745C;
extern s32 D_800774D4;
extern s32 D_800775B4;
extern s32 D_800775D4;
extern s32 D_80077600;
extern s32 D_80077630;
extern s32 D_80077668;
extern s32 D_80077670;
extern s32 D_80077688;
extern s32 D_80077690;
extern s32 D_80077698;
extern s32 D_800776A0;
extern s32 D_800776C0;
extern s32 D_800776C8;
extern s32 D_800776F0;
extern s32 D_80077720;
extern s32 D_80077730;
extern s32 D_80077738;
extern s32 D_80079B70;
extern s32 D_80079B74;
extern s32 D_80079B7C;
extern s32 D_80079B80;
extern s32 D_8007B1B8;
extern s32 D_8007B1BC;
extern s32 D_8007B1C0;
extern s32 D_8007B1C4;
extern s32 D_8007B1F0;
extern s32 D_8007B1F8;
extern s32 D_8007C264;
extern s32 D_8007C2DC;
extern s32 D_8007C2F4;
extern s32 D_8007C4E0;
extern s32 D_8007C4E8;
extern s32 D_8007C4F0;
extern s32 D_8007C4F8;
extern s32 D_8007C510;
extern s32 D_8007C518;
extern s32 D_8012CD20;
extern s32 D_8012CD28;
extern s32 D_8012CD78;
extern s32 D_8012CD80;
extern s32 D_8012CD98;
extern s32 D_8012CDA0;
extern s32 D_8012CDA8;
extern s32 D_8012CDC8;
extern s32 D_8012CDE0;
extern s32 D_8012CF68;
extern s32 D_8012CF70;
extern s32 D_8012CF80;
extern s32 D_8012CF88;
extern s32 D_8012CFA8;
extern s32 D_8012CFB0;
extern s32 D_8012CFC0;
extern s32 D_8012CFE0;
extern s32 D_8012CFE8;
extern s32 D_8012CFF0;
extern s32 D_8012D078;
extern s32 D_8012D088;
extern s32 D_8012D0C0;
extern s32 D_8012D8D8;
extern s32 D_8012D8E0;
extern s32 D_8012D8E8;
extern s32 D_8012D940;
extern s32 D_8012D944;
extern s32 D_8012D948;
extern s32 D_8012D94C;
extern s32 D_80173140;
extern s32 D_801732F0;
extern s32 D_80173318;
extern s32 D_80173338;
extern s32 D_80173348;
extern s32 D_80173350;
extern s32 D_80173358;
extern s32 D_80173368;
extern s32 D_80173378;
extern s32 D_801733A0;
extern s32 D_801733B0;
extern s32 D_801733D8;
extern s32 D_80173438;
extern s32 D_80173470;
extern s32 D_80173478;
extern s32 D_80173480;
extern s32 D_80173488;
extern s32 D_80173490;
extern s32 D_801734A0;
extern s32 D_801734B0;
extern s32 D_801734B8;
extern s32 D_801734C0;
extern s32 D_801D34E8;
extern s32 D_801D35A0;
extern s32 D_801D7668;
extern s32 D_801D7768;
extern s32 D_801D77A8;
extern s32 D_801D77C8;
extern s32 D_801D77F0;
extern s32 D_801D77F8;
extern s32 D_801D7800;
extern s32 D_801D7E20;
extern s32 D_801D7E28;
extern s32 D_801D7E30;
extern s32 D_801D7E38;
extern s32 D_801D7E48;
extern s32 D_801D7E78;
extern s32 D_801D7E88;
extern s32 D_801D7EC8;
extern s32 D_801D7F58;
extern s32 D_801D8128;
extern s32 D_801D8360;
extern s32 D_801D8364;
extern s32 D_801D9020;
extern s32 D_801D9028;
extern s32 D_801D9030;
extern s32 D_801D9040;
extern s32 D_801D9058;
extern s32 D_801E9098;
extern s32 D_801E90B0;
extern s32 D_801E90B8;
extern s32 D_801E90C8;
extern s32 D_801E90E0;
extern s32 D_801E9178;
extern s32 D_801E91E8;
extern s32 D_801E9210;
extern s32 D_801E9248;
extern s32 D_801E9F40;
extern s8 *D_800774D8;
extern s8 *D_800774E4;
extern s8 D_801D75F0;
extern s8 D_801D75F1;
extern s8 D_801D75F2;
extern s8 D_801D75F3;
extern u16 *D_8007758C;
extern u16 D_8007B1E8;
extern u16 D_8012D000;
extern u16 D_80173310;
extern u16 D_801D35AA;
extern u16 D_801D35AE;
extern u16 D_801D77D0;
extern u16 D_801D9068;
extern u16 D_801D906C;
extern u16 D_801D9070;
extern u32 D_80077464;
extern u8 D_800772A0;
extern u8 D_800775E8;
extern u8 D_80079B8A;
extern u8 D_80079B8F;
extern u8 D_80079B98;
extern u8 D_80079B99;
extern u8 D_80079B9A;
extern u8 D_80173428;
extern u8 D_801D35A9;
extern u8 D_801D7D10;
extern void *D_80077728;
extern void *D_80173388;
extern void *D_801D35F0;
extern void *D_A0000454;
extern void *D_A0000488;
extern void *D_A000048C;
extern void *g_gpu_device;
s16 func_80047920(s32, s32);
s16 func_8004BA7C(s32, M2C_UNK);
s16 func_8004BE7C(M2C_UNK, s16);
s16 func_8004C27C(s32, s32);
s16 func_8004C380(s16, s16, s16, s32, s32, s32, s32);
s16 func_8004D328(s16, s16, s16);
s16 func_80054264(M2C_UNK, M2C_UNK *);
s32 SquareRoot(s32, s32);
s32 VSync(M2C_UNK);
s32 func_80012EF0(s32);
s32 func_800177B8(s32, s32, s32, s32);
s32 func_80019C6C(s32, s32);
s32 func_80019CA8(s32, s32);
s32 func_8001D3B8(s32, s32, s32, M2C_UNK, M2C_UNK *);
s32 func_8002721C(s32);
s32 func_8002757C(s32);
s32 func_80029278(s32, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32);
s32 func_800297D8(s32, s32, M2C_UNK, M2C_UNK, s32, s32, s32, s32, s32);
s32 func_8002B238();
s32 func_80033218(void *);
s32 func_8003486C(s32, M2C_UNK, s32, M2C_UNK);
s32 func_80037238(s32, M2C_UNK, s32, M2C_UNK);
s32 func_800373BC(s32, s32);
s32 func_800408CC(s32, s32, s32);
s32 func_80041148(s32);
s32 func_80041528(s32 *);
s32 func_800416D8(s32 *);
s32 func_800437AC(s32, void *, M2C_UNK, M2C_UNK);
s32 func_80044078(s32, s32);
s32 func_80045718();
s32 func_800459C0(M2C_UNK *, s32);
s32 func_800465A0(u16, u16);
s32 func_800465DC(M2C_UNK);
s32 func_8004788C(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_80049668(s32, M2C_UNK, s32);
s32 func_80049708(M2C_UNK, void *);
s32 func_800497C8(s32, s32, s32, s32);
s32 func_800497E8(s32, M2C_UNK);
s32 func_80050DF8(s16, s16);
s32 func_80051CAC(M2C_UNK, M2C_UNK);
s32 func_80051D14(s32, M2C_UNK);
s32 func_80052D14(s32, M2C_UNK, M2C_UNK, M2C_UNK);
s32 func_80053788(M2C_UNK *, s32);
s32 func_80054254(M2C_UNK);
s32 func_80059170(s32, u32);
s32 rcos(s32);
s32 rsin(s32);

void game_init(void) {
    SetVideoMode(0);
    func_800456B4(0);
    func_80045750(0);
    func_8002E740();
    func_80049728(1);
    func_80049778();
    func_80049788();
    func_8004D8C4();
    func_80032D50();
    D_801733C0 = 0;
    D_8012D908 = 0;
    D_8012D8D0 = 0;
    D_801D7808 = 0;
    D_8012CFF8 = 0;
    D_8012CFFA = 0;
    D_8012CFFC = 0;
    D_8012D0B0 = 0;
    D_8012D088 = 0;
    D_80173398 = 1;
    D_80173390 = 0;
    D_801E91A0 = 0;
    D_8012CD78 = 0;
    func_8002E710();
    func_80030DE0();
    func_8003DFE0();
    func_8002ACD4();
    func_80012578();
    *(s8 *)0x1F800022 = 0xFF;
    *(s8 *)0x1F800021 = 0xFF;
    *(s8 *)0x1F800020 = 0xFF;
    *(s8 *)0x1F800026 = 0x80;
    *(s8 *)0x1F800025 = 0x80;
    *(s8 *)0x1F800024 = 0x80;
    func_800355A4(5);
    D_8007C210 = 1;
    D_801733B8 = 0;
    D_8007C2D8 = 0;
    D_8007C25A = 0;
    D_801D34E0 = 0;
    D_801D77D8 = 0;
    D_801D35D0 = 0;
}

void func_80012550(void) {
    func_8003A1BC();
    func_8003A1AC(0);
}

u16 func_800125B4(u16 *arg0) {
    s16 temp_v1;
    s32 var_t0;
    u16 *var_a3;
    u16 temp_t2;
    void **var_a2;
    void **var_t1;
    void *temp_a1;
    void *temp_a1_2;
    void *var_a0;
    void *var_a1;

    var_t1 = &D_801D35F0;
    temp_t2 = *arg0;
    var_a3 = arg0 + 4;
    var_t0 = 0;
    var_a1 = var_a3 + (temp_t2 * 8);
    if (temp_t2 != 0) {
        var_a2 = &D_801D35F0 + 8;
        var_a0 = arg0 + 8;
        do {
            M2C_FIELD(var_a2, u16 *, 4) = (u16) *var_a3;
            *var_t1 = var_a1;
            temp_a1 = var_a1 + ((s16) *var_a3 * 0x28);
            M2C_FIELD(var_a2, void **, -4) = temp_a1;
            M2C_FIELD(var_a2, u16 *, 6) = (u16) M2C_FIELD(var_a0, u16 *, -2);
            var_t0 += 1;
            temp_a1_2 = temp_a1 + ((s16) M2C_FIELD(var_a0, u16 *, -2) * 0x28);
            M2C_FIELD(var_a2, void **, 0) = temp_a1_2;
            M2C_FIELD(var_a2, u16 *, 8) = (u16) M2C_FIELD(var_a0, u16 *, 0);
            temp_v1 = (s16) M2C_FIELD(var_a0, u16 *, 0);
            var_a3 += 8;
            var_t1 += 0x20;
            var_a0 += 8;
            var_a1 = temp_a1_2 + (temp_v1 * 0x28);
            var_a2 += 0x20;
        } while (var_t0 < (s32) temp_t2);
    }
    return temp_t2;
}

s32 func_80012670(s32 *arg0) {
    s16 *var_t2;
    s16 temp_a0;
    s16 temp_a1;
    s16 temp_a2;
    s16 temp_a3;
    s16 temp_t0;
    s32 temp_t5;
    s32 var_t3;
    void *var_t1;
    void *var_t4;

    temp_t5 = *arg0;
    var_t2 = arg0 + 4;
    D_801D35E8 = var_t2;
    var_t3 = 0;
    var_t4 = var_t2 + (temp_t5 * 0x10);
    if (temp_t5 > 0) {
        var_t1 = arg0 + 0xE;
        do {
            M2C_FIELD(var_t1, void **, 2) = var_t4;
            temp_a0 = M2C_FIELD(var_t1, s16 *, -8);
            temp_a2 = M2C_FIELD(var_t1, s16 *, -6);
            temp_a3 = M2C_FIELD(var_t1, s16 *, -4);
            temp_a1 = M2C_FIELD(var_t1, s16 *, -2);
            temp_t0 = M2C_FIELD(var_t1, s16 *, 0);
            var_t3 += 1;
            var_t1 += 0x10;
            var_t4 += (*var_t2 * 0x28) + (temp_a0 * 0x30) + (temp_a2 << 5) + (temp_a3 << 6) + (temp_a1 * 0x48) + (temp_t0 * 0x38);
            var_t2 += 0x10;
        } while (var_t3 < temp_t5);
    }
    D_80173318 = temp_t5;
    return temp_t5;
}

void func_800129AC(void *arg0, void *arg1, M2C_UNK arg2) {
    s32 temp_a1;

    M2C_FIELD(arg0, s16 *, 0) = (s16) (M2C_FIELD(arg1, u16 *, 0) - D_801D9068);
    M2C_FIELD(arg0, s16 *, 2) = (s16) (M2C_FIELD(arg1, u16 *, 4) - D_801D906C);
    M2C_FIELD(arg0, s16 *, 4) = (s16) (M2C_FIELD(arg1, u16 *, 8) - D_801D9070);
    func_8004315C(&D_801E91F0, arg0, arg0 + 8);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) (M2C_FIELD(arg0, s32 *, 8) * 4);
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) * 4);
    temp_a1 = M2C_FIELD(arg0, s32 *, 0x10) * 4;
    M2C_FIELD(arg0, s32 *, 0x34) = temp_a1;
    func_80043470(arg2, temp_a1);
    func_80043500(arg0 + 0x18);
}

void func_80012A5C(void *arg0, void *arg1, M2C_UNK arg2) {
    s32 temp_a1;

    M2C_FIELD(arg0, s16 *, 0) = (s16) (M2C_FIELD(arg1, u16 *, 0) - (D_801D9068 * 4));
    M2C_FIELD(arg0, s16 *, 2) = (s16) (M2C_FIELD(arg1, u16 *, 4) - (D_801D906C * 4));
    M2C_FIELD(arg0, s16 *, 4) = (s16) (M2C_FIELD(arg1, u16 *, 8) - (D_801D9070 * 4));
    func_8004315C(&D_801E91F0, arg0, arg0 + 8);
    temp_a1 = M2C_FIELD(arg0, s32 *, 0x10);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(arg0, s32 *, 0x34) = temp_a1;
    func_80043470(arg2, temp_a1);
    func_80043500(arg0 + 0x18);
}

void func_80012B0C(s32 arg0, M2C_UNK arg1, s32 arg2, M2C_UNK arg3) {
    s32 var_a2;

    func_80012A5C(0x1F800060, arg0, arg1);
    var_a2 = 1;
    if (arg2 < D_80173318) {
        var_a2 = arg2;
    }
    *(s32 *)0x1F800000 = func_8003486C(*(s32 *)0x1F800000, 0x1F800038, var_a2, arg3);
}

void func_80012B90(s32 arg0, M2C_UNK arg1, s32 arg2, M2C_UNK arg3) {
    s32 var_a2;

    func_80012A5C(0x1F800060, arg0, arg1);
    var_a2 = 1;
    if (arg2 < D_80173318) {
        var_a2 = arg2;
    }
    *(s32 *)0x1F800000 = func_80037238(*(s32 *)0x1F800000, 0x1F800038, var_a2, arg3);
}

void func_8001315C(void) {
    func_800434D0(&D_8012D090);
}

void func_80013184(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_80012EF0(M2C_FIELD(arg0, s32 *, 8));
    if (temp_v0 != 0) {
        if (D_8012CDC8 == 0) {
            func_8003B2E4(0x46, 0x46);
        }
    } else if (D_8012CDC8 != 0) {
        func_8003B2E4(0, 0);
    }
    D_8012CDC8 = temp_v0;
}

void func_80013240(void) {
    func_8001602C(&D_80070F44);
    func_8001613C(&D_80070FEC);
    if (D_80173164 != 0) {
        func_8001624C(&D_80071784);
        func_8001602C(&D_8007113C);
        return;
    }
    func_800366FC(&D_800711E4);
    func_8001613C(&D_80071094);
}

void func_800132D4(s32 arg0) {
    func_80028AC8((arg0 * 0x22BF4) + &D_8012D950 + 0x22B70);
}

void func_800135B8(s32 arg0, s32 arg1) {
    s32 var_v0;
    s32 var_v0_2;

    if (arg0 != 0) {
        D_801734B8 = 0xA700;
        D_80173480 = 0xD00;
        if (arg1 != 0) {
            D_8012CDA0 = 0xB900;
            var_v0 = 0x6400;
        } else {
            D_8012CDA0 = 0x2700;
            var_v0 = 0x6800;
        }
        D_80173488 = var_v0;
        D_80173180 = &D_8005F140;
        D_801E90E0 = 0x100;
        D_801E9210 = 1;
        D_80173368 = 0xC570;
        D_801E9248 = 0xBBE0;
        D_80173378 = 0x9E00;
        D_801E9F40 = 0x9490;
        D_8012D8E0 = 0x1AB3;
        D_801D9030 = 0;
        D_8012D8E8 = 0x6F50;
        D_801D9040 = 0x6200;
        D_8012D8D8 = 0xAC00;
        D_8007C4F0 = -1;
        D_8012D940 = 0xED00;
        D_8012D944 = 0x9100;
        D_8012D948 = -1;
        D_8012D94C = -1;
    } else {
        D_801734B8 = 0x11600;
        D_801734C0 = 0x9F00;
        D_80173480 = 0xD00;
        if (arg1 != 0) {
            D_8012CDA0 = 0x12900;
            var_v0_2 = 0xD400;
        } else {
            D_8012CDA0 = 0x2700;
            var_v0_2 = 0xD800;
        }
        D_80173488 = var_v0_2;
        D_80173180 = &D_8005F2A0;
        D_801E90E0 = 0x170;
        D_801E9210 = 2;
        D_80173368 = 0x13570;
        D_801E9248 = 0x12BE0;
        D_80173378 = 0x10E00;
        D_801E9F40 = 0x10490;
        D_8012D8E0 = 0x1AB3;
        D_801D9030 = 0;
        D_8012D8E8 = 0xDE90;
        D_801D9040 = 0xD1D0;
        D_8012D8D8 = 0x11C00;
        D_8007C4F0 = 0x6300;
        D_8012D940 = 0x15D00;
        D_8012D944 = 0x10100;
        D_8012D948 = 0xAE00;
        D_8012D94C = 0x8000;
    }
    D_80173490 = func_800373BC(D_80173480, D_80173488);
}

void func_80013D40(void *arg0) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v1;
    s16 var_s1;
    s16 var_v0;
    s16 var_v1;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 var_a1;
    s32 var_a3;
    void *temp_v1_2;
    void *temp_v1_3;

    var_a3 = 0x100;
    if (D_801733B8 != 0) {
        var_a3 = -0x100;
    }
    temp_a2 = D_801E90E0 << 0x10;
    temp_a0 = D_801E90E0 << 8;
    var_a1 = ((s32) (temp_a2 + M2C_FIELD(arg0, s32 *, 8)) % temp_a0) & ~0xFF;
    if ((var_a1 == D_8012CDA0) && ((((s32) (temp_a2 + M2C_FIELD(arg0, s32 *, 0xD0)) % temp_a0) & ~0xFF) == (var_a3 + var_a1))) {
        temp_v0 = M2C_FIELD(arg0, s16 *, 0xD6);
        if (temp_v0 > 0) {
            var_v0 = temp_v0 - 1;
            goto block_20;
        }
        temp_v1 = M2C_FIELD(arg0, s16 *, 0xD4);
        var_s1 = *(&D_80071D64 + ((D_801D35A0 - temp_v1) * 2));
        if (temp_v1 > 0) {
            temp_v1_2 = arg0 + (M2C_FIELD(arg0, s16 *, 0xD4) * 4);
            M2C_FIELD(temp_v1_2, s32 *, 0xEC) = (s32) ((func_800497C8(temp_a0, var_a1, temp_a2, var_a3) & 0x1F) + M2C_FIELD(temp_v1_2, s32 *, 0xEC));
            var_a1 = (s32) (arg0 + (M2C_FIELD(arg0, s16 *, 0xD4) * 4));
            temp_a0_2 = M2C_FIELD(var_a1, s32 *, 0xEC);
            temp_v1_3 = (D_8007C210 * 4) + ((D_801733B8 * 0x10) + ((D_8012D088 << 5) + &D_801D7628));
            if (temp_a0_2 < M2C_FIELD(temp_v1_3, s32 *, -4)) {
                M2C_FIELD(temp_v1_3, s32 *, -4) = temp_a0_2;
                var_s1 = 1;
                M2C_FIELD(arg0, s16 *, 0xCE) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xD4) - 1);
            }
        }
        if (var_s1 > 0) {
            snd_play_se(var_s1, (void *) var_a1);
        }
        temp_v0_2 = (u16) M2C_FIELD(arg0, s16 *, 0xD4) + 1;
        M2C_FIELD(arg0, s16 *, 0xD4) = temp_v0_2;
        if ((temp_v0_2 >= 2) && (D_801D35A0 >= temp_v0_2)) {
            D_8012CF58 = 0x96;
            if (D_801733B8 != 0) {
                var_v1 = *(&D_8005E916 + ((D_8007C210 - 1) * 0xC));
            } else {
                var_v1 = *(&D_8005E90E + ((D_8007C210 - 1) * 0xC));
            }
            D_8012CD20 += var_v1 * 0x1E;
        }
    } else {
        temp_a2_2 = D_801E90E0 << 0x10;
        temp_a0_3 = D_801E90E0 << 8;
        if (((((s32) (temp_a2_2 + M2C_FIELD(arg0, s32 *, 8)) % temp_a0_3) & ~0xFF) == (var_a3 + D_8012CDA0)) && ((((s32) (temp_a2_2 + M2C_FIELD(arg0, s32 *, 0xD0)) % temp_a0_3) & ~0xFF) == D_8012CDA0)) {
            var_v0 = (u16) M2C_FIELD(arg0, s16 *, 0xD6) + 1;
block_20:
            M2C_FIELD(arg0, s16 *, 0xD6) = var_v0;
        }
    }
}

void func_800140A4(void *arg0) {
    s16 temp_v0;
    s16 var_v0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_a3_2;

    temp_a3 = D_801E90E0 << 0x10;
    temp_a1 = D_801E90E0 << 8;
    temp_a2 = ((s32) (temp_a3 + M2C_FIELD(arg0, s32 *, 8)) % temp_a1) & ~0xFF;
    if ((temp_a2 == D_801734B8) && ((((s32) (temp_a3 + M2C_FIELD(arg0, s32 *, 0xD0)) % temp_a1) & ~0xFF) == (temp_a2 + 0x100))) {
        temp_v0 = M2C_FIELD(arg0, s16 *, 0xD8);
        if (temp_v0 > 0) {
            var_v0 = temp_v0 - 1;
            goto block_8;
        }
        D_8012CF58 = 0x96;
        D_8012CD20 += *(&D_8005E910 + ((D_8007C210 - 1) * 0xC)) * 0x1E;
        return;
    }
    temp_a3_2 = D_801E90E0 << 0x10;
    temp_a1_2 = D_801E90E0 << 8;
    if (((((s32) (temp_a3_2 + M2C_FIELD(arg0, s32 *, 8)) % temp_a1_2) & ~0xFF) == (D_801734B8 + 0x100)) && ((((s32) (temp_a3_2 + M2C_FIELD(arg0, s32 *, 0xD0)) % temp_a1_2) & ~0xFF) == D_801734B8)) {
        var_v0 = (u16) M2C_FIELD(arg0, s16 *, 0xD8) + 1;
block_8:
        M2C_FIELD(arg0, s16 *, 0xD8) = var_v0;
    }
}

void func_80014280(void *arg0) {
    s16 temp_v0;
    s16 var_v0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_a3_2;

    temp_a3 = D_801E90E0 << 0x10;
    temp_a1 = D_801E90E0 << 8;
    temp_a2 = ((s32) (temp_a3 + M2C_FIELD(arg0, s32 *, 8)) % temp_a1) & ~0xFF;
    if ((temp_a2 == D_801734C0) && ((((s32) (temp_a3 + M2C_FIELD(arg0, s32 *, 0xD0)) % temp_a1) & ~0xFF) == (temp_a2 + 0x100))) {
        temp_v0 = M2C_FIELD(arg0, s16 *, 0xDA);
        if (temp_v0 > 0) {
            var_v0 = temp_v0 - 1;
            goto block_8;
        }
        D_8012CF58 = 0x96;
        D_8012CD20 += *(&D_8005E912 + ((D_8007C210 - 1) * 0xC)) * 0x1E;
        return;
    }
    temp_a3_2 = D_801E90E0 << 0x10;
    temp_a1_2 = D_801E90E0 << 8;
    if (((((s32) (temp_a3_2 + M2C_FIELD(arg0, s32 *, 8)) % temp_a1_2) & ~0xFF) == (D_801734C0 + 0x100)) && ((((s32) (temp_a3_2 + M2C_FIELD(arg0, s32 *, 0xD0)) % temp_a1_2) & ~0xFF) == D_801734C0)) {
        var_v0 = (u16) M2C_FIELD(arg0, s16 *, 0xDA) + 1;
block_8:
        M2C_FIELD(arg0, s16 *, 0xDA) = var_v0;
    }
}

void func_80014AE4(s16 arg0) {
    func_8003AEC0();
    func_8003B26C(0, 0, 0);
    func_8003B340(0);
    if ((arg0 != 0x1D) && (arg0 != 0xF)) {
        func_8003A1AC(-0x80);
        func_8003A588();
    }
    D_801D3548 = 0;
    D_801D3542 = 0;
    D_801D34F8 = arg0;
}

void snd_update_ambience_volume(void *arg0) {
    s16 var_v0;
    s16 var_v1;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_a1;

    if (D_801D9060 < 3) {
        temp_v0 = 0x6991 - M2C_FIELD(arg0, s32 *, 0x10);
        var_a1 = temp_v0 * temp_v0;
        temp_v0_2 = 0xA23A - M2C_FIELD(arg0, s32 *, 0x18);
        if (var_a1 < 0) {
            var_a1 += 3;
        }
        var_a0 = temp_v0_2 * temp_v0_2;
        if (var_a0 < 0) {
            var_a0 += 3;
        }
        var_v1 = 0x50 - (SquareRoot((var_a1 >> 2) + (var_a0 >> 2), var_a1) >> 0xA);
        if (var_v1 >= 0x29) {
            var_v1 = 0x28;
        }
        var_v0 = var_v1;
        if (var_v1 < 0) {
            var_v0 = 0;
        }
        D_801D3548 = var_v0;
        D_801D3542 = var_v0;
        return;
    }
    D_801D3548 = 0;
    D_801D3542 = 0;
}

s32 func_80015B18(s32 arg0, s32 arg1) {
    s32 temp_a2;
    s32 var_a3;

    var_a3 = 0;
    if ((arg0 == arg1) || (temp_a2 = *(&D_80072A30 + (D_801E9210 * 8)), (((s32) (arg0 + 1) % temp_a2) == arg1)) || (arg0 == ((s32) (arg1 + 1) % temp_a2))) {
        var_a3 = 1;
    }
    return var_a3;
}

void func_80016368(void *arg0) {
    if ((M2C_FIELD(&D_80072F60, s32 *, 0) >= M2C_FIELD(arg0, s32 *, 0x10)) && (M2C_FIELD(arg0, s32 *, 0x18) > 0x9998)) {
        M2C_FIELD(&D_80072F60, s32 *, 0) = (s32) M2C_FIELD(arg0, s32 *, 0x10);
        M2C_FIELD(&D_80072F60, s32 *, 4) = (s32) M2C_FIELD(arg0, s32 *, 0x14);
        M2C_FIELD(&D_80072F60, s32 *, 8) = (s32) M2C_FIELD(arg0, s32 *, 0x18);
        M2C_FIELD(&D_80072F60, s32 *, 0xC) = (s32) M2C_FIELD(arg0, s32 *, 0x1C);
        D_80072F64 = 0;
        D_80072F6C = 0x400 - M2C_FIELD(arg0, s32 *, 0x24);
    }
}

s32 track_side_of_segment(void *arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_t0;
    s32 temp_t1;

    temp_t1 = M2C_FIELD(arg0, s32 *, 8);
    temp_t0 = M2C_FIELD(arg1, s32 *, 8);
    temp_a0 = M2C_FIELD(arg0, s32 *, 0);
    temp_a1 = M2C_FIELD(arg1, s32 *, 0);
    return (((((temp_t1 - temp_t0) * arg2) - ((temp_a0 - temp_a1) * arg3)) + (temp_a0 * temp_t0)) - (temp_a1 * temp_t1)) > 0;
}

void track_get_node_edge(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 temp_s3;
    s32 temp_s5;
    s32 var_v1;
    s32 var_v1_2;

    var_v1 = M2C_FIELD(arg1, s32 *, 0);
    temp_s3 = M2C_FIELD(arg1, s16 *, 0xE) * 2;
    temp_s5 = temp_s3;
    if (var_v1 < 0) {
        var_v1 += 0x3FFF;
    }
    M2C_FIELD(arg2, s32 *, 0) = (s32) ((D_801733A0 - (var_v1 >> 0xE)) - M2C_FIELD(arg0, s32 *, 0));
    var_v1_2 = M2C_FIELD(arg1, s32 *, 4);
    if (var_v1_2 < 0) {
        var_v1_2 += 0x3FFF;
    }
    M2C_FIELD(arg2, s32 *, 8) = (s32) ((var_v1_2 >> 0xE) - M2C_FIELD(arg0, s32 *, 8));
    M2C_FIELD(arg3, s32 *, 0) = (s32) (((s32) ((s32) (rcos(0x800 - M2C_FIELD(arg1, s16 *, 0xA)) * temp_s3) / 4096) / 32) + M2C_FIELD(arg2, s32 *, 0));
    M2C_FIELD(arg3, s32 *, 8) = (s32) (M2C_FIELD(arg2, s32 *, 8) - ((s32) ((s32) (rsin(0x800 - M2C_FIELD(arg1, s16 *, 0xA)) * temp_s5) / 4096) / 32));
    M2C_FIELD(arg2, s32 *, 0) = (s32) M2C_FIELD(arg2, s32 *, 0);
    M2C_FIELD(arg2, s32 *, 8) = (s32) M2C_FIELD(arg2, s32 *, 8);
    M2C_FIELD(arg3, s32 *, 0) = (s32) M2C_FIELD(arg3, s32 *, 0);
    M2C_FIELD(arg3, s32 *, 8) = (s32) M2C_FIELD(arg3, s32 *, 8);
}

s32 func_80017B58(s32 arg0, s32 arg1, s32 arg2, void *arg3, s32 *arg4, s32 *arg5) {
    s16 var_a3_2;
    s16 var_a3_3;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a3;
    s32 temp_hi;
    s32 temp_s2;
    s32 var_a0;
    s32 var_a2;
    s32 var_a3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    temp_s2 = rsin(M2C_FIELD(arg3, s16 *, 0xA) - 0xC00);
    var_v1 = M2C_FIELD(arg3, s32 *, 0);
    temp_a3 = rcos(M2C_FIELD(arg3, s16 *, 0xA) - 0xC00);
    if (var_v1 < 0) {
        var_v1 += 0x3FFF;
    }
    temp_a0 = arg0 - (D_801733A0 - (var_v1 >> 0xE));
    var_v1_2 = M2C_FIELD(arg3, s32 *, 4);
    if (var_v1_2 < 0) {
        var_v1_2 += 0x3FFF;
    }
    temp_a1 = arg1 - (var_v1_2 >> 0xE);
    var_v0_2 = (temp_a3 * temp_a0) + (temp_s2 * temp_a1);
    if (var_v0_2 < 0) {
        var_v0_2 += 0xF;
    }
    var_a2 = (s32) (var_v0_2 >> 4) / 528;
    var_v0_3 = (-temp_a0 * temp_s2) + (temp_a3 * temp_a1);
    if (var_v0_3 < 0) {
        var_v0_3 += 0xFFF;
    }
    temp_a1_2 = var_v0_3 >> 0xC;
    temp_a1_3 = (s32) (temp_a1_2 + ((u32) temp_a1_2 >> 0x1F)) >> 1;
    if (var_a2 < 0) {
        var_a2 = 0;
    } else if (var_a2 >= 0x100) {
        var_a2 = 0xFF;
    }
    *arg4 = var_a2;
    *arg5 = temp_a1_3;
    if (temp_a1_3 > 0) {
        var_a3_2 = M2C_FIELD(arg3, s16 *, 0x10);
        if (var_a3_2 < 0) {
            var_a3_2 += 0x1F;
        }
        var_a3 = var_a3_2 >> 5;
        goto block_27;
    }
    var_a3_3 = M2C_FIELD(arg3, s16 *, 0xE);
    if (var_a3_3 < 0) {
        var_a3_3 += 0x1F;
    }
    temp_hi = (s32) ((arg2 << 8) + var_a2 + (D_801E90E0 << 0x10)) % (s32) (D_801E90E0 << 8);
    var_a3 = var_a3_3 >> 5;
    if (((temp_hi < D_80173368) && (D_801E9248 < temp_hi)) || ((temp_hi < D_80173378) && (D_801E9F40 < temp_hi))) {
        var_v1_3 = temp_a1_3;
        if (temp_a1_3 < 0) {
            var_v1_3 = -var_v1_3;
        }
        var_a0 = 2;
        if ((var_a3 + 0x40) < var_v1_3) {
            var_a0 = 3;
        }
        return var_a0;
    }
block_27:
    var_v0 = temp_a1_3;
    if (temp_a1_3 < 0) {
        var_v0 = -var_v0;
    }
    return var_a3 < var_v0;
}

s16 func_800187A0(s32 arg0, s32 arg1) {
    s16 var_v0;
    s16 var_v1;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 var_v0_2;

    if (arg0 == 0) {
        if (arg1 == 0) {
            return 0;
        }
        var_v0 = -0x400;
        if (arg1 > 0) {
            return 0x400;
        }
        
        return var_v0;
    }
    if (arg0 > 0) {
        if (arg1 >= 0) {
            if (arg0 < arg1) {
                var_v1 = *(&D_8005E93C + (((s32) (arg0 << 0xA) / arg1) * 2));
                var_v0_2 = 0x400;
                goto block_20;
            }
            return *(&D_8005E93C + (((s32) (arg1 << 0xA) / arg0) * 2));
        }
        temp_a1 = -arg1;
        if (arg0 < temp_a1) {
            return *(&D_8005E93C + (((s32) (arg0 << 0xA) / temp_a1) * 2)) - 0x400;
        }
        return -*(&D_8005E93C + (((s32) (arg1 * -0x400) / arg0) * 2));
    }
    temp_a0 = -arg0;
    if (arg1 >= 0) {
        if (temp_a0 < arg1) {
            return *(&D_8005E93C + (((s32) (arg0 * -0x400) / arg1) * 2)) + 0x400;
        }
        var_v1 = *(&D_8005E93C + (((s32) (arg1 << 0xA) / temp_a0) * 2));
        var_v0_2 = 0x800;
        goto block_20;
    }
    temp_a1_2 = -arg1;
    if (temp_a0 >= temp_a1_2) {
        return *(&D_8005E93C + (((s32) (arg1 * -0x400) / temp_a0) * 2)) + 0x800;
    }
    var_v1 = *(&D_8005E93C + (((s32) (arg0 * -0x400) / temp_a1_2) * 2));
    var_v0_2 = 0xC00;
block_20:
    var_v0 = var_v0_2 - var_v1;
    return var_v0;
}

void func_8001AA60(void *arg0) {
    s32 *var_a1;
    s32 *var_a3;
    s32 *var_t1;
    s32 *var_t2;
    s32 temp_lo;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a2;
    s32 var_t3;
    s32 var_v0;
    s32 var_v1;
    void *temp_s0;
    void *temp_t4;
    void *var_v1_2;

    M2C_FIELD(arg0, s16 *, 0) = 1;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    temp_s0 = arg0 + 0x58;
    temp_t4 = (M2C_FIELD(arg0, s16 *, 2) * 0xC) + &D_800593B0;
    if (D_801733B8 != 0) {
        M2C_FIELD(arg0, s32 *, 0x10) = 0x5C98;
        M2C_FIELD(arg0, s32 *, 0x14) = -0xEF;
        M2C_FIELD(arg0, s32 *, 0x18) = 0x3826;
        M2C_FIELD(arg0, s32 *, 0x20) = 0x1F;
        M2C_FIELD(arg0, s32 *, 0x24) = 0x56A;
        M2C_FIELD(arg0, s32 *, 0x28) = 0;
        var_v1 = 0x10FB1;
        if (D_8007C210 < 3) {
            var_v1 = 0x9FB1;
        }
        M2C_FIELD(arg0, s32 *, 8) = var_v1;
    } else {
        M2C_FIELD(arg0, s32 *, 0x10) = 0x6935;
        M2C_FIELD(arg0, s32 *, 0x14) = 0x60;
        M2C_FIELD(arg0, s32 *, 0x18) = 0xA253;
        M2C_FIELD(arg0, s32 *, 0x20) = 0;
        M2C_FIELD(arg0, s32 *, 0x24) = 0x4B1;
        M2C_FIELD(arg0, s32 *, 0x28) = 0;
        M2C_FIELD(arg0, s32 *, 8) = 0x4400;
    }
    M2C_FIELD(temp_s0, s32 *, 0x78) = (s32) M2C_FIELD(arg0, s32 *, 8);
    var_a0 = 0;
    var_v1_2 = temp_s0;
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x14) + 0x14;
    M2C_FIELD(arg0, s32 *, 0x14) = temp_v0;
    M2C_FIELD(arg0, s32 *, 0x40) = temp_v0;
    M2C_FIELD(temp_s0, s32 *, 0x10) = 0;
    M2C_FIELD(temp_s0, s32 *, 0xC) = 0;
    M2C_FIELD(temp_s0, s32 *, 8) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x20) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x1C) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x18) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x48) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x7E) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x7C) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x82) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x80) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x76) = -1;
    do {
        M2C_FIELD(var_v1_2, s32 *, 0x98) = 0;
        M2C_FIELD(var_v1_2, s32 *, 0x84) = 0;
        var_a0 += 1;
        var_v1_2 += 4;
    } while (var_a0 < 5);
    M2C_FIELD(temp_s0, s32 *, 0x5C) = 3;
    M2C_FIELD(temp_s0, s16 *, 0x2A) = 1;
    temp_v0_2 = M2C_FIELD(arg0, s32 *, 0x24);
    M2C_FIELD(temp_s0, s32 *, 0x2C) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x34) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x58) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x30) = 0;
    M2C_FIELD(temp_s0, s32 *, 0x54) = temp_v0_2;
    M2C_FIELD(temp_s0, s32 *, 0x50) = temp_v0_2;
    temp_lo = (s32) (M2C_FIELD(temp_t4, s16 *, 0) * 8 * M2C_FIELD(((D_8007C210 * 4) + ((M2C_FIELD(temp_s0, s16 *, 0x28) * 0x10) + &D_80072FF8)), s32 *, -4)) / 1000;
    D_8007B1F0 = 0;
    D_801732F0 = 0;
    D_8012CF80 = 0;
    D_8012CF70 = 0;
    D_8012CFA8 = 0;
    D_8012CF88 = 0;
    var_a3 = &D_801D7EC8;
    var_a1 = &D_801D7EC8 + 0x10;
    var_t3 = 0x1824;
    var_t2 = &D_80073018;
    var_t1 = &D_80073050;
    var_a2 = 0;
    var_a0_2 = 0;
    M2C_FIELD(temp_s0, s32 *, 0x44) = temp_lo;
    do {
        *var_a3 = (var_a2 / 6) + 1;
        M2C_FIELD(var_a1, s32 *, -0xC) = (s32) ((s32) (M2C_FIELD(temp_t4, s16 *, 2) * *var_t1) / 100);
        M2C_FIELD(var_a1, s32 *, -8) = (s32) ((s32) (M2C_FIELD(temp_t4, s16 *, 2) * *(&D_80073034 + (var_a0_2 * 4))) / 100);
        if (var_a0_2 == 6) {
            var_v0 = M2C_FIELD(&D_80073018, s32 *, 0x18) * 0xA;
        } else {
            var_v0 = (s32) (M2C_FIELD(temp_t4, s16 *, 2) * *var_t2) / 100;
        }
        M2C_FIELD(var_a1, s32 *, -4) = var_v0;
        M2C_FIELD(var_a1, s32 *, 0) = var_t3;
        var_t3 += 0x140;
        var_t2 += 4;
        var_t1 += 4;
        var_a2 += temp_lo;
        var_a0_2 += 1;
        var_a1 += 0x14;
        var_a3 += 0x14;
    } while (var_a0_2 < 7);
    M2C_FIELD(temp_s0, s32 *, 0x3C) = (s32) (M2C_FIELD(temp_t4, s16 *, 4) * 0xE);
    M2C_FIELD(temp_s0, s32 *, 0x40) = (s32) M2C_FIELD(temp_t4, s16 *, 6);
    func_80032E18(var_a0_2, var_a1, var_a2, var_a3);
    M2C_FIELD(temp_s0, s16 *, 0x60) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x6E) = 0;
    M2C_FIELD(temp_s0, s16 *, 0x6C) = 0;
    D_8012CD98 = 0;
    D_801D7800 = 0;
    D_8007B1F8 = 0;
    D_8012CFF0 = 0;
    D_80173140 = 0;
    D_801D7E38 = 0x28;
    D_8012CFC0 = 0;
}

void func_8001B0CC(void) {
    s32 temp_v0;
    s32 var_a0;
    s32 var_a0_2;

    if (D_801D77D0 == 0) {
        temp_v0 = ((s32) (D_8007C2DC - D_801D7800) / 4) + D_801D7800;
        D_801D7800 = temp_v0;
        if (temp_v0 >= 0x2711) {
            D_801D7800 = 0x2710;
        }
        if (D_801D7800 < 0x1F4) {
            D_801D7800 = 0x1F4;
        }
    }
    func_8002037C(M2C_FIELD(&D_8007C258, s16 *, 0xCC));
    func_800201B0();
    var_a0 = D_8012CD20;
    if (var_a0 < 0) {
        var_a0 = 0;
    }
    func_800202A0(var_a0);
    func_800203F0(&D_8007C258);
    func_80028CE4(&D_8007C258);
    func_80028CE4(&D_801E9250);
    func_80029A64();
    func_80028C1C();
    var_a0_2 = (s32) (M2C_FIELD(&D_8007C258, s32 *, 0xA0) * 0xA0) / 146;
    if (var_a0_2 < 0) {
        var_a0_2 += 7;
    }
    func_8001FE6C(var_a0_2 >> 3);
    func_80028F64(D_801D7800);
    func_80029120(M2C_FIELD(&D_8007C258, s16 *, 0x82) - 1);
    func_8002AB88();
    if ((u32) (D_80173310 - 0x12D) < 0x257U) {
        func_8001D5D4(0x28, 0xD8, D_80173338, D_80173310 - 0x12C);
    }
}

s32 func_8001B2D4(void *arg0) {
    s32 temp_a0;

    temp_a0 = (u32) (((M2C_FIELD(arg0, s32 *, 0xA8) - (0x800 - M2C_FIELD(((((s32) (((s32) M2C_FIELD(arg0, s32 *, 8) >> 8) + (D_801E90E0 << 8)) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA))) & 0xFFF) - 0x401) < 0x7FFU;
    if (D_801733B8 != 0) {
        return temp_a0 == 0;
    }
    return temp_a0;
}

void func_8001C0E4(void *arg0) {
    s32 temp_lo;
    s32 temp_s2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    void *temp_s0;

    temp_s0 = arg0 + 0x58;
    if (D_801D9060 >= 2) {
        if (D_801D9060 == 4) {
            if (D_801733B8 != 0) {
                var_a1 = func_8002721C(M2C_FIELD(arg0, s32 *, 8) + 0xC0) + 0x800;
            } else {
                var_a1 = func_8002721C(M2C_FIELD(arg0, s32 *, 8) - 0x100);
            }
            temp_s2 = func_80019CA8(M2C_FIELD(arg0, s32 *, 0x24), var_a1) << 5;
            var_a1_2 = (0x1000 - rcos(M2C_FIELD(arg0, s32 *, 0xC) * 2)) * 4;
            if (M2C_FIELD(arg0, s32 *, 0xC) > 0) {
                var_a1_2 = -var_a1_2;
            }
            var_a1_3 = var_a1_2 + temp_s2;
            var_v0 = var_a1_3 < 0x1001;
            if (var_a1_3 < -0x1000) {
                var_a1_3 = -0x1000;
                var_v0 = -0x1000 < 0x1001;
            }
            if (var_v0 == 0) {
                var_a1_3 = 0x1000;
            }
            M2C_FIELD(temp_s0, s32 *, 0x1C) = var_a1_3;
            var_v0_2 = var_a1_3;
            goto block_35;
        }
        if (D_801D35A9 == 0x41) {
            if (D_8012D088 != 0) {
                var_a1_4 = D_801D35AA & D_801D7778;
                var_v1 = D_801D35AA & D_801D777A;
            } else {
                var_v1 = D_801D35AA & D_801D7778;
                var_a1_4 = D_801D35AA & D_801D777A;
            }
            if (var_v1 != 0) {
                temp_v1 = M2C_FIELD(temp_s0, s32 *, 0x1C);
                if (temp_v1 > 0) {
                    M2C_FIELD(temp_s0, s32 *, 0x1C) = 0;
                } else if (temp_v1 >= -0xFFF) {
                    M2C_FIELD(temp_s0, s32 *, 0x1C) = (s32) (temp_v1 - 0x500);
                }
                D_8012CD98 -= 6;
            } else if (var_a1_4 != 0) {
                temp_v1_2 = M2C_FIELD(temp_s0, s32 *, 0x1C);
                if (temp_v1_2 < 0) {
                    M2C_FIELD(temp_s0, s32 *, 0x1C) = 0;
                } else if (temp_v1_2 < 0x1000) {
                    M2C_FIELD(temp_s0, s32 *, 0x1C) = (s32) (temp_v1_2 + 0x500);
                }
                D_8012CD98 += 6;
            } else {
                M2C_FIELD(temp_s0, s32 *, 0x1C) = (s32) ((s32) M2C_FIELD(temp_s0, s32 *, 0x1C) / 2);
            }
            if (D_8012CD98 != 0) {
                D_8012CD98 = (s32) (D_8012CD98 * 7) / 8;
            }
        } else if (D_801D35A9 == 0x23) {
            temp_lo = (s32) (D_801D35BC * 0x1800) / (s16) *(&D_800771CC + (D_801733D0 * 2));
            M2C_FIELD(arg0, s32 *, 0x74) = temp_lo;
            if (D_8012D088 != 0) {
                M2C_FIELD(arg0, s32 *, 0x74) = (s32) -temp_lo;
            }
            var_v0_2 = M2C_FIELD(arg0, s32 *, 0x74);
block_35:
            D_8012CD98 = var_v0_2 / 128;
        } else {
            goto block_36;
        }
    } else {
block_36:
        D_8012CD98 = 0;
        M2C_FIELD(arg0, s32 *, 0x74) = 0;
    }
    if (M2C_FIELD(temp_s0, s16 *, 0x60) != 0) {
        var_v0_3 = (s32) M2C_FIELD(temp_s0, s32 *, 0x1C) / 4;
        M2C_FIELD(temp_s0, s32 *, 0x1C) = var_v0_3;
        if (var_v0_3 < 0) {
            var_v0_3 += 0x7F;
        }
        D_8012CD98 = var_v0_3 >> 7;
    }
    temp_v1_3 = M2C_FIELD(arg0, s32 *, 0xA0);
    if (temp_v1_3 < 0x320) {
        D_8012CD98 = (s32) (D_8012CD98 * temp_v1_3) / 800;
    }
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) D_8012CD98;
}

void func_8001CDBC(s32 arg0) {
    if (D_801E90B0 > 0) {
        D_8007C518 = arg0;
        return;
    }
    func_8003A1D8();
    D_801E90B0 = 0x78;
    D_8007C518 = 0;
}

void func_8001CE0C(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0;

    var_a0 = arg0;
    temp_v1 = var_a0;
    if (D_801E90B0 > 0) {
        temp_v0 = D_801E90B0 - 1;
        D_801E90B0 = temp_v0;
        if (temp_v0 == 0) {
            var_a0 = D_8007C518;
            if (var_a0 > 0) {
                func_8001CDBC(var_a0);
                return;
            }
            goto block_5;
        }
    } else if (D_801E90B0 == 0) {
block_5:
        if (temp_v1 != 0) {
            func_8003A640(var_a0);
            func_8003A1AC(0x7F);
            D_801E90C8 = 0;
            D_801E90B0 = -1;
        }
    }
}

void func_8001CFD0(void) {
    st_title_init();
    D_80077144 = 0;
}

void func_8001CFF8(void) {
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_v0;

    temp_s0 = D_8012CF68 + 0xB68;
    temp_s1 = func_8004788C(0, 0, 0x2C0, 0x100) & 0xFFFF;
    temp_v0 = func_80029278(temp_s0, *(s32 *)0x1F800000, 0x70, 0xA2, 0x70, 0x10, 0, 0x70, 0x1B1);
    func_8004617C(temp_v0, 0, 1, temp_s1, &D_80077128);
    AddPrim(temp_s0, temp_v0);
    *(s32 *)0x1F800000 = temp_v0 + 0xC;
    func_80028578(0x48, 0xB8, &D_80010158, 0x64);
    func_80028578(0x50, 0xC8, &D_80010170, 0x64);
    if (D_8007B1E8 & 4) {
        func_80028578(0x60, 0x90, &D_80010184, 0x64);
    }
}

void func_8001D538(s32 arg0, M2C_UNK arg1, s32 arg2) {
    M2C_UNK sp18;
    s32 temp_s0;
    s32 temp_s1;

    temp_s1 = *(s32 *)0x1F800000;
    temp_s0 = D_8012CF68 + 0xB6C;
    func_80048198(&sp18, &D_80077154, *(&D_8007307C + (arg2 * 4)));
    *(s32 *)0x1F800000 = func_8001D3B8(temp_s0, temp_s1, arg0, arg1, &sp18);
}

void func_8001DC94(s32 arg0) {
    func_80028578(0x58, 0xD0, &D_80010244, 0x64);
    func_80028578(0x80, 0xD0, *(&D_800730B0 + (arg0 * 4)), 0x64);
    func_80028578(0x58, 0xDA, &D_80010250, 0x64);
    func_80028578(0xA8, 0xDA, *(&D_800730D4 + (((arg0 - 1) & 3) * 4)), 0x64);
    if (arg0 >= 5) {
        func_80028578(0x88, 0xC4, &D_80077178, 0x7F);
        func_80028578(0x89, 0xC5, &D_80077178, 0x11D);
    }
}

void func_8001F098(void) {
    func_800434D0(&D_800730E4);
    func_800434A0(&D_80073104);
    func_8003FBE8(0x20, 0x20, 0x20);
    func_8003FC08(0, 0, 0);
    func_80044F64(0x4E20, 0x140);
}

void func_800205E4(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s16 *, 0x38) = 0;
    if ((u32) (arg2 - 4) < 4U) {
        M2C_FIELD(arg0, s16 *, 0x38) = 1;
    }
    M2C_FIELD(arg0, s16 *, 0x3A) = 0x14;
    M2C_FIELD(arg0, s16 *, 0x3C) = 0;
    M2C_FIELD(arg0, s16 *, 0x3E) = -1;
    M2C_FIELD(arg0, s16 *, 0x40) = -1;
    M2C_FIELD(arg0, s16 *, 0x46) = 0;
    M2C_FIELD(arg0, s16 *, 0x4C) = -0x3C;
    M2C_FIELD(arg0, s16 *, 0x4E) = 0;
    M2C_FIELD(arg0, s16 *, 0x50) = 0;
    M2C_FIELD(arg0, s16 *, 0x42) = -3;
    M2C_FIELD(arg0, s16 *, 0x54) = 0;
    M2C_FIELD(arg0, s16 *, 0x56) = 0;
    M2C_FIELD(arg0, s32 *, 0x58) = 0;
    if (arg1 < 5) {
        M2C_FIELD(arg0, s16 *, 0x44) = 0;
        M2C_FIELD(arg0, s16 *, 0x4A) = -1;
    } else {
        M2C_FIELD(arg0, s16 *, 0x44) = 1;
        M2C_FIELD(arg0, s16 *, 0x4A) = 0;
    }
    if (arg1 == 0xB) {
        M2C_FIELD(arg0, s16 *, 0x56) = 1;
        M2C_FIELD(arg0, s16 *, 0x4A) = -2;
        M2C_FIELD(arg0, s16 *, 0x4E) = -1;
        M2C_FIELD(arg0, s16 *, 0x3C) = -1;
    }
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
    M2C_FIELD(arg0, s32 *, 0x64) = 0;
    M2C_FIELD(arg0, s16 *, 0x8E) = 0;
    M2C_FIELD(arg0, s16 *, 0x8C) = 0;
    M2C_FIELD(arg0, s32 *, 0x98) = 0;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    M2C_FIELD(arg0, s16 *, 0x8E) = 0;
    M2C_FIELD(arg0, s32 *, 0x74) = 0;
    M2C_FIELD(arg0, s32 *, 0x70) = 0;
    M2C_FIELD(arg0, s32 *, 0x7C) = 0;
    M2C_FIELD(arg0, s32 *, 0x78) = 0;
    M2C_FIELD(arg0, s32 *, 0x80) = 0;
    M2C_FIELD(arg0, s32 *, 0x84) = 0;
    M2C_FIELD(arg0, s32 *, 0x88) = 0;
    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    M2C_FIELD(arg0, s32 *, 0x34) = 0;
}

void func_80021CB4(void *arg0) {
    s32 temp_a3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a2;

    temp_a3 = D_8007C210 < 3;
    var_a2 = 0x17000;
    if (temp_a3 != 0) {
        var_a2 = 0x10000;
    }
    switch (D_801D77B8) {
    case 0:
        temp_v1 = M2C_FIELD(arg0, s32 *, 8);
        if (temp_v1 >= 0x2800) {
            var_a1 = (var_a2 + 0x2800) - temp_v1;
        } else {
            var_a1 = 0x2800 - temp_v1;
        }
        if ((var_a1 + (var_a2 * M2C_FIELD(arg0, s16 *, 0x9C))) >= D_80173348) {
            M2C_FIELD(arg0, s16 *, 0x9E) = 0;
            return;
        }
block_15:
        M2C_FIELD(arg0, s16 *, 0x9E) = 1;
        return;
    case 1:
        var_a1_2 = 0xB900;
        if (temp_a3 == 0) {
            var_a1_2 = 0x12900;
        }
        temp_v1_2 = M2C_FIELD(arg0, s32 *, 8);
        if (temp_v1_2 >= var_a1_2) {
            var_a1_3 = temp_v1_2 - var_a1_2;
        } else {
            var_a1_3 = (var_a2 - var_a1_2) + temp_v1_2;
        }
        if ((var_a1_3 + (var_a2 * M2C_FIELD(arg0, s16 *, 0x9C))) < D_80173348) {
            goto block_15;
        }
        M2C_FIELD(arg0, s16 *, 0x9E) = 0;
        return;
    }
}

void func_80021DB4(void *arg0, s32 arg1) {
    s32 var_a2;
    void *temp_a1;

    var_a2 = 0;
    temp_a1 = (((s32) ((arg1 >> 8) + (D_801E90E0 << 8)) % (s32) D_801E90E0) * 0x14) + D_801733D8;
    switch (D_801D77B8) {
    case 0:
        if (M2C_FIELD(arg0, s32 *, 0x30) >= 0x281) {
            var_a2 = 0xA;
            if ((M2C_FIELD(temp_a1, s16 *, 0xE) + M2C_FIELD(temp_a1, s16 *, 0x10)) < 0x2000) {
                var_a2 = 0x14;
            }
        }
        D_8007C510 = var_a2 - ((s16) M2C_FIELD(temp_a1, s16 *, 0xE) / 34);
        D_8012CD80 = ((s16) M2C_FIELD(temp_a1, s16 *, 0x10) / 34) - var_a2;
        return;
    case 1:
        if (M2C_FIELD(arg0, s32 *, 0x30) >= 0x281) {
            var_a2 = -0xA;
            if ((M2C_FIELD(temp_a1, s16 *, 0xE) + M2C_FIELD(temp_a1, s16 *, 0x10)) < 0x2000) {
                var_a2 = -0x14;
            }
        }
        D_8007C510 = ((s16) M2C_FIELD(temp_a1, s16 *, 0x10) / 34) + var_a2;
        D_8012CD80 = -((s16) M2C_FIELD(temp_a1, s16 *, 0xE) / 34) - var_a2;
        return;
    }
}

void func_80022984(void *arg0, s16 arg1) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a2;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0xE0);
    var_a2 = temp_v1;
    if (temp_v1 <= 0) {
        var_a2 = -temp_v1;
    }
    if ((arg1 != 0) && (arg1 != 0xB)) {
        temp_v0 = M2C_FIELD(arg0, s32 *, 0x58);
        switch (temp_v0) {
        case 1:
            if (var_a2 >= 0x2201) {
                M2C_FIELD(arg0, s32 *, 0x58) = 0;
                return;
            }
            break;
        case 0:
            if (var_a2 < 0x2200) {
                M2C_FIELD(arg0, s32 *, 0x58) = 1;
            }
            break;
        }
    }
}

void func_80022B4C(void *arg0, u32 *arg1, s32 *arg2) {
    s16 temp_v1;

    if (M2C_FIELD(arg0, s16 *, 0xAE) != 0) {
        if (M2C_FIELD(arg0, s16 *, 0xA2) == -2) {
            *arg1 = 0;
            *arg2 = M2C_FIELD(arg0, s32 *, 0x100);
            return;
        }
        if (M2C_FIELD(arg0, s16 *, 0x96) == -1) {
            *arg1 = (u32) (M2C_FIELD(arg0, u32 *, 0x10C) * 6) / 5U;
            return;
        }
        *arg1 = (u32) (M2C_FIELD(arg0, u32 *, 0x10C) * 0xE) / 11U;
        return;
    }
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xA2);
    switch (temp_v1) {
    case 0:
        *arg1 = M2C_FIELD(arg0, u32 *, 0xF8);
        return;
    case 1:
        *arg1 = M2C_FIELD(arg0, u32 *, 0x10C);
        return;
    case 2:
        *arg1 = M2C_FIELD(arg0, u32 *, 0x110);
        return;
    }
}

void func_80022C40(void *arg0, s32 *arg1, s32 *arg2) {
    s16 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_lo;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 var_a0;
    s32 var_t0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;

    if (M2C_FIELD(arg0, s16 *, 0xAA) != 2) {
        var_t0 = 0x800;
        if (D_801D35D0 == 0) {
            var_t0 = D_8007C32C * 0x300;
        }
        temp_a0 = M2C_FIELD(arg0, s16 *, 0x9C);
        var_v0 = temp_a0 < D_8007C32C;
        if (((temp_a0 == D_8007C32C) && (var_v0 = temp_a0 < D_8007C32C, ((var_t0 < M2C_FIELD(arg0, s32 *, 0xE0)) != 0))) || (var_v0 != 0)) {
            temp_v1 = M2C_FIELD(arg0, s32 *, 0x10C);
            *arg1 = (temp_v1 / 100) + temp_v1;
            *arg2 = M2C_FIELD(arg0, s32 *, 0xFC);
        } else {
            var_v0_2 = D_8007C32C < temp_a0;
            if (((temp_a0 == D_8007C32C) && (var_v0_2 = D_8007C32C < temp_a0, ((M2C_FIELD(arg0, s32 *, 0xE0) < -0x600) != 0))) || (var_v0_2 != 0)) {
                temp_v1_2 = *arg1;
                temp_a0_2 = M2C_FIELD(arg0, s32 *, 0xF8);
                var_v1 = temp_v1_2 * 8;
                if (temp_a0_2 < temp_v1_2) {
                    var_v1 = temp_a0_2 * 8;
                }
                temp_lo = var_v1 / 10;
                *arg1 = temp_lo;
                if (M2C_FIELD(arg0, s32 *, 0x88) < temp_lo) {
                    *arg2 = M2C_FIELD(arg0, s32 *, 0xFC);
                } else {
                    *arg2 = M2C_FIELD(arg0, s32 *, 0x100);
                }
            }
        }
        M2C_FIELD(arg0, s32 *, 0xB8) = 0;
    } else {
        if (M2C_FIELD(arg0, s32 *, 0xE0) > 0) {
            temp_v1_3 = D_8007C2F4 - ((s32) (D_8007C2F4 * 3) / 100);
            *arg1 = temp_v1_3;
            if (temp_v1_3 < M2C_FIELD(arg0, s32 *, 0x88)) {
                goto block_20;
            }
        } else {
            temp_a0_3 = D_8007C2F4 - ((s32) (D_8007C2F4 * 0xD) / 100);
            *arg1 = temp_a0_3;
            if (temp_a0_3 < M2C_FIELD(arg0, s32 *, 0x88)) {
block_20:
                *arg2 = M2C_FIELD(arg0, s32 *, 0x100);
            }
        }
        M2C_FIELD(arg0, s32 *, 0xB8) = (s32) *arg1;
    }
    if (D_801D35D0 == 0) {
        var_a0 = 3;
        if (D_8007C210 == 1) {
            var_a0 = 2;
        }
        if (D_8007C32C == var_a0) {
            temp_v1_4 = M2C_FIELD(arg0, s32 *, 0xF8);
            if (temp_v1_4 < *arg1) {
                *arg1 = temp_v1_4;
                if (temp_v1_4 < M2C_FIELD(arg0, s32 *, 0x88)) {
                    *arg2 = M2C_FIELD(arg0, s32 *, 0x100);
                }
            }
            if (M2C_FIELD(arg0, s32 *, 0xB8) != 0) {
                M2C_FIELD(arg0, s32 *, 0xB8) = (s32) ((s32) (D_8007C2F4 * 9) / 10);
            }
        }
    }
}

void func_8002362C(void *arg0) {
    s16 var_a0;
    s16 var_a1;
    s16 var_a2;
    s16 var_a3;
    s16 var_v0;
    s16 var_v0_2;
    s32 temp_t1;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;

    temp_v0 = M2C_FIELD(arg0, s32 *, 8);
    temp_t1 = temp_v0 >> 8;
    if (D_801D77B8 == 0) {
        temp_v1 = D_801E90E0 << 8;
        var_a3 = M2C_FIELD(((((s32) (temp_t1 + temp_v1) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA);
        M2C_FIELD(arg0, s32 *, 0xC8) = (s32) var_a3;
        var_a2 = M2C_FIELD(((((s32) (temp_t1 + (temp_v1 - 1)) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA);
        M2C_FIELD(arg0, s32 *, 0xCC) = (s32) var_a2;
        var_a1 = M2C_FIELD(((((s32) (temp_t1 + (temp_v1 - 2)) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA);
        M2C_FIELD(arg0, s32 *, 0xD0) = (s32) var_a1;
        var_v0 = M2C_FIELD(((((s32) (temp_t1 + (temp_v1 + 1)) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA);
    } else {
        temp_v1_2 = D_801E90E0 << 8;
        var_a3 = M2C_FIELD(((((s32) (temp_t1 + temp_v1_2) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA) + 0x800;
        M2C_FIELD(arg0, s32 *, 0xC8) = (s32) var_a3;
        var_a2 = M2C_FIELD(((((s32) (temp_t1 + (temp_v1_2 + 1)) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA) + 0x800;
        M2C_FIELD(arg0, s32 *, 0xCC) = (s32) var_a2;
        var_a1 = M2C_FIELD(((((s32) (temp_t1 + (temp_v1_2 + 2)) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA) + 0x800;
        M2C_FIELD(arg0, s32 *, 0xD0) = (s32) var_a1;
        var_v0 = M2C_FIELD(((((s32) (temp_t1 + (temp_v1_2 - 1)) % (s32) D_801E90E0) * 0x14) + D_801733D8), s16 *, 0xA) + 0x800;
    }
    M2C_FIELD(arg0, s32 *, 0xD4) = (s32) var_v0;
    if (var_a3 == var_a2) {
        M2C_FIELD(arg0, s16 *, 0x94) = 0;
    } else {
        var_v0_2 = -1;
        if ((var_a2 < var_a3) || (var_v0_2 = 1, ((var_a3 < var_a2) != 0))) {
            M2C_FIELD(arg0, s16 *, 0x94) = var_v0_2;
        }
    }
    M2C_FIELD(arg0, s16 *, 0xAC) = 0;
    if (D_801D77B8 == 1) {
        if (D_8007C210 < 3) {
            if ((u32) ((((s32) ((D_801E90E0 << 0x10) + M2C_FIELD(arg0, s32 *, 8)) % (s32) (D_801E90E0 << 8)) & ~0xFF) - 0x6701) < 0x8FFU) {
                goto block_13;
            }
        } else if ((u32) ((((s32) ((D_801E90E0 << 0x10) + M2C_FIELD(arg0, s32 *, 8)) % (s32) (D_801E90E0 << 8)) & ~0xFF) + 0xFFFF2AFF) < 0x8FFU) {
block_13:
            M2C_FIELD(arg0, s16 *, 0xAC) = 1;
            M2C_FIELD(arg0, s16 *, 0x94) = 0;
        }
    }
    if (D_801D77B8 == 0) {
        var_a0 = var_a2;
        if (M2C_FIELD(arg0, s16 *, 0x90) == 1) {
            var_a0 = var_a1;
            goto block_20;
        }
        var_a1 = var_a3;
    } else {
        var_a0 = var_a3;
        if (M2C_FIELD(arg0, s16 *, 0x90) == 1) {
            var_a0 = var_a2;
        } else {
block_20:
            var_a1 = var_a2;
        }
    }
    M2C_FIELD(arg0, s32 *, 0x78) = (s32) (0x800 - func_800177B8((s32) var_a0, (s32) var_a1, temp_v0 & 0xFF, (s32) var_a3));
}

void func_80023A8C(void *arg0, s32 arg1) {
    s32 temp_a1;
    s32 temp_a3;
    s32 temp_t0;
    s32 var_a0;
    s32 var_v0;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0x70);
    temp_t0 = M2C_FIELD(arg0, s32 *, 0x74);
    temp_a3 = M2C_FIELD(arg0, s32 *, 0x7C);
    if (D_801D77B8 == 0) {
        var_a0 = temp_t0;
        if (arg1 >= 0x81) {
            var_v0 = func_800177B8(temp_a1, temp_a3, arg1 - 0x80, temp_a3);
        } else {
            goto block_6;
        }
        goto block_7;
    }
    if (D_801D77B8 == 1) {
        var_a0 = temp_a3;
        if (arg1 >= 0x81) {
            var_v0 = func_800177B8(temp_a1, temp_t0, arg1 - 0x80, temp_a3);
        } else {
block_6:
            var_v0 = func_800177B8(var_a0, temp_a1, arg1 + 0x80, temp_a3);
        }
block_7:
        M2C_FIELD(arg0, s32 *, 0x6C) = (s32) (0x800 - var_v0);
    }
}

void func_80023C58(void *arg0, s32 arg1) {
    s16 temp_v1;
    s16 temp_v1_3;
    s16 temp_v1_4;
    s16 var_t0;
    s32 temp_v1_2;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v1;
    void *temp_a2;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0x94);
    var_t0 = 0;
    temp_a2 = arg0 + 0x58;
    if ((temp_v1 == 0) || (temp_v1 != M2C_FIELD(arg0, s16 *, 0xA6))) {
        M2C_FIELD(arg0, s16 *, 0xA6) = 0;
    }
    if (D_801D77B8 == 0) {
        if (D_8012CD80 >= arg1) {
            var_v0 = arg1 < D_8007C510;
            goto block_10;
        }
        goto block_8;
    }
    var_v0_2 = 0 << 0x10;
    if (D_801D77B8 == 1) {
        if (arg1 < D_8012CD80) {
block_8:
            var_t0 = 1;
            goto block_12;
        }
        var_v0 = D_8007C510 < arg1;
block_10:
        var_v0_2 = 0 << 0x10;
        if (var_v0 != 0) {
            var_t0 = -1;
block_12:
            var_v0_2 = var_t0 << 0x10;
        }
    }
    temp_v1_2 = var_v0_2 >> 0x10;
    if (temp_v1_2 == 1) {
        var_a0 = (s32) (D_8012CD80 * 9) / 10;
        M2C_FIELD(temp_a2, s16 *, 0x4E) = var_t0;
        var_v1 = (D_8012CD80 - arg1) - 1;
        goto block_17;
    }
    if (temp_v1_2 == -1) {
        var_a0 = (s32) (D_8007C510 * 9) / 10;
        M2C_FIELD(temp_a2, s16 *, 0x4E) = var_t0;
        var_v1 = (D_8007C510 - arg1) + 1;
block_17:
        M2C_FIELD(temp_a2, s32 *, 8) = var_v1;
        M2C_FIELD(temp_a2, s32 *, 0x58) = var_a0;
        if (M2C_FIELD(temp_a2, s16 *, 0x4A) != -2) {
            M2C_FIELD(temp_a2, s16 *, 0x4A) = 4;
        }
    }
    temp_v1_3 = M2C_FIELD(temp_a2, s16 *, 0x42);
    var_v0_3 = temp_v1_3 < -1;
    if (temp_v1_3 != -1) {
        var_v0_3 = temp_v1_3 < -1;
        if (M2C_FIELD(temp_a2, s16 *, 0x4E) == 0) {
            M2C_FIELD(temp_a2, s16 *, 0x4E) = 1;
            var_v0_3 = M2C_FIELD(temp_a2, s16 *, 0x42) < -1;
        }
    }
    if (var_v0_3 == 0) {
        temp_v1_4 = M2C_FIELD(temp_a2, s16 *, 0x54);
        var_v0_4 = var_t0 << 0x10;
        if (temp_v1_4 == 1) {
            if (D_801D77B8 == temp_v1_4) {
                if (arg1 >= 0x3D) {
                    var_v0_5 = -5;
                    goto block_33;
                }
                if (arg1 < -0x3C) {
                    M2C_FIELD(temp_a2, s32 *, 8) = 5;
                }
                goto block_34;
            }
            var_v0_4 = var_t0 << 0x10;
            if (D_801D77B8 == 0) {
                if (arg1 >= 0x47) {
                    var_v0_5 = -4;
                    goto block_33;
                }
                var_v0_5 = 4;
                if (arg1 < -0x46) {
block_33:
                    M2C_FIELD(temp_a2, s32 *, 8) = var_v0_5;
                }
block_34:
                var_v0_4 = var_t0 << 0x10;
            }
        }
        if (var_v0_4 == 0) {
            var_a1 = M2C_FIELD(temp_a2, s32 *, 0x58) - arg1;
            if (var_a1 >= 5) {
                temp_v1_5 = M2C_FIELD(temp_a2, s32 *, 8);
                if (temp_v1_5 < 3) {
                    M2C_FIELD(temp_a2, s32 *, 8) = (s32) (temp_v1_5 + 1);
                }
            } else if (var_a1 < -4) {
                temp_v1_6 = M2C_FIELD(temp_a2, s32 *, 8);
                if (temp_v1_6 >= -2) {
                    M2C_FIELD(temp_a2, s32 *, 8) = (s32) (temp_v1_6 - 1);
                }
            } else if (var_a1 >= 4) {
                temp_v1_7 = M2C_FIELD(temp_a2, s32 *, 8);
                var_v0_6 = temp_v1_7 + 1;
                if (temp_v1_7 >= 2) {
                    if (temp_v1_7 >= 4) {
                        M2C_FIELD(temp_a2, s32 *, 8) = (s32) (temp_v1_7 - 1);
                    }
                } else {
                    goto block_65;
                }
            } else if (var_a1 < -3) {
                temp_v1_8 = M2C_FIELD(temp_a2, s32 *, 8);
                if (temp_v1_8 >= -1) {
                    var_v0_6 = temp_v1_8 - 1;
                    goto block_65;
                }
                if (temp_v1_8 < -3) {
                    M2C_FIELD(temp_a2, s32 *, 8) = (s32) (temp_v1_8 + 1);
                }
            } else {
                if (var_a1 != 0) {
                    if (var_a1 > 0) {
                        M2C_FIELD(temp_a2, s32 *, 8) = 1;
                        return;
                    }
                    goto block_64;
                }
                goto block_62;
            }
        }
    } else {
        switch (M2C_FIELD(temp_a2, s16 *, 0x42)) {
        case -2:
            var_a1 = M2C_FIELD(temp_a2, s32 *, 0x58) - arg1;
            if (var_a1 != 0) {
                if (var_a1 > 0) {
                    M2C_FIELD(temp_a2, s32 *, 8) = 1;
                    return;
                }
block_64:
                var_v0_6 = -1;
                if (var_a1 < 0) {
block_65:
                    M2C_FIELD(temp_a2, s32 *, 8) = var_v0_6;
                }
                return;
            }
block_62:
            M2C_FIELD(temp_a2, s32 *, 8) = 0;
            return;
        case -3:
            M2C_FIELD(temp_a2, s32 *, 8) = 0;
            if ((M2C_FIELD(temp_a2, s16 *, 0x4A) == -2) && (M2C_FIELD(temp_a2, s16 *, 0x56) == 2)) {
                var_a1 = D_8007C510 - arg1;
                if (var_a1 == 0) {
                    goto block_62;
                }
                var_v0_6 = 1;
                if (var_a1 <= 0) {
                    goto block_64;
                }
                goto block_65;
            }
            break;
        }
    }
}

void func_80023FF8(void *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0xC8) - M2C_FIELD(arg0, s32 *, 0xCC);
    if ((u32) (temp_v1 + 0x50) < 0xA1U) {
        temp_v0 = M2C_FIELD(arg0, s32 *, 0x28);
        if (temp_v0 != 0) {
            if (temp_v0 > 0) {
                M2C_FIELD(arg0, s32 *, 0x7C) = (s32) (temp_v0 - 2);
                return;
            }
            M2C_FIELD(arg0, s32 *, 0x7C) = (s32) (temp_v0 + 2);
        }
    } else {
        if (temp_v1 >= 0x51) {
            temp_v1_2 = M2C_FIELD(arg0, s32 *, 0x28);
            if (temp_v1_2 < 0x1E) {
                M2C_FIELD(arg0, s32 *, 0x7C) = (s32) (temp_v1_2 + 2);
                return;
            }
            goto block_10;
        }
        temp_v1_3 = M2C_FIELD(arg0, s32 *, 0x28);
        if (temp_v1_3 >= -0xE) {
            M2C_FIELD(arg0, s32 *, 0x7C) = (s32) (temp_v1_3 - 2);
            return;
        }
block_10:
        M2C_FIELD(arg0, s32 *, 0x7C) = M2C_FIELD(arg0, s32 *, 0x28);
    }
}

void func_80024094(void *arg0) {
    s16 temp_v0;
    s16 temp_v1;
    s32 temp_a0;
    s32 var_a2;
    s32 var_v0;

    var_a2 = 2;
    if (M2C_FIELD(arg0, s16 *, 0x90) == 1) {
        var_a2 = 3;
    }
    if (M2C_FIELD(arg0, s16 *, 0x92) > 0) {
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x88);
        temp_v0 = M2C_FIELD(arg0, s16 *, 0x92);
        var_a2 *= temp_v0;
        M2C_FIELD(arg0, s16 *, 0x92) = (s16) (temp_v0 - 1);
        M2C_FIELD(arg0, s32 *, 0x88) = (s32) (temp_a0 - (temp_a0 / 50));
    } else {
        M2C_FIELD(arg0, s16 *, 0x44) = 0;
        M2C_FIELD(arg0, s16 *, 0x92) = 0x14;
    }
    if (D_801D7E78 == 0) {
        var_a2 = 0;
    }
    temp_v1 = M2C_FIELD(arg0, s16 *, 0x94);
    if (temp_v1 == -1) {
        var_v0 = var_a2 + M2C_FIELD(arg0, s32 *, 0xBC);
    } else if ((temp_v1 != 1) && (D_8007C264 < M2C_FIELD(arg0, s32 *, 0xC))) {
        var_v0 = var_a2 + M2C_FIELD(arg0, s32 *, 0xBC);
    } else {
        var_v0 = M2C_FIELD(arg0, s32 *, 0xBC) - var_a2;
    }
    M2C_FIELD(arg0, s32 *, 0xBC) = var_v0;
    if (M2C_FIELD(arg0, s16 *, 0x9A) >= 0) {
        M2C_FIELD(arg0, s16 *, 0x9A) = -1;
    }
}

void func_800241BC(void *arg0) {
    s32 temp_v1;
    s32 var_v0;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0xBC);
    if (temp_v1 >= 0x800) {
        var_v0 = temp_v1 - 0x1000;
        goto block_3;
    }
    var_v0 = temp_v1 + 0x1000;
    if (temp_v1 < -0x800) {
block_3:
        M2C_FIELD(arg0, s32 *, 0xBC) = var_v0;
    }
    M2C_FIELD(arg0, s32 *, 0xBC) = (s32) ((s32) (M2C_FIELD(arg0, s32 *, 0xBC) * 0xC) / 13);
}

s32 func_80024728(void *arg0) {
    s32 temp_v1;
    s32 var_v0;
    s32 var_v0_2;

    var_v0 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x88) >= 0x540) {
        temp_v1 = ((s32) ((D_801E90E0 << 0x10) + M2C_FIELD(arg0, s32 *, 8)) % (s32) (D_801E90E0 << 8)) & ~0xFF;
        if (D_801D77B8 != 0) {
            if (D_8007C210 < 3) {
                var_v0_2 = 0x7900;
                if (temp_v1 != 0x3400) {
                    goto block_7;
                }
                goto block_6;
            }
            var_v0_2 = 0xE900;
            if (temp_v1 == 0x3400) {
block_6:
                return 5;
            }
block_7:
            var_v0 = 0;
            if (temp_v1 == var_v0_2) {
                return 6;
            }
            
            return var_v0;
        }
        if (D_8007C210 < 3) {
            var_v0 = 0;
            if (temp_v1 == 0x7900) {
                return 1;
            }
            
            return var_v0;
        }
        if (temp_v1 == 0xE900) {
            return 2;
        }
        if (temp_v1 == 0x7700) {
            return 3;
        }
        var_v0 = 0;
        if (temp_v1 == 0x5D00) {
            var_v0 = 4;
        }
        
        return var_v0;
    }
    return var_v0;
}

void func_8002483C(void *arg0) {
    s16 temp_v1;
    s32 temp_lo;
    s32 temp_v0;
    s32 var_v1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0xA8);
    switch (temp_v1) {
    case 1:
        M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(arg0, s32 *, 0xF0) + M2C_FIELD(arg0, s32 *, 0xEC));
        return;
    case 0:
        if (M2C_FIELD(arg0, s16 *, 0xE6) == 0) {
            temp_v0 = func_80024728(arg0);
            if (temp_v0 != 0) {
                var_v1 = M2C_FIELD(arg0, s32 *, 0x88);
                M2C_FIELD(arg0, s16 *, 0xA8) = 1;
                if (var_v1 >= 0x579) {
                    var_v1 = 0x578;
                }
                temp_lo = (s32) ((var_v1 / (s32) *(&D_80073E5C + (temp_v0 * 4))) * -2) / 3;
                M2C_FIELD(arg0, s16 *, 0xE4) = 0;
                M2C_FIELD(arg0, s32 *, 0xEC) = temp_lo;
                M2C_FIELD(arg0, s32 *, 0xF0) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) - temp_lo);
            }
        }
        return;
    }
}

s32 func_80024954(void *arg0, s16 *arg1, s32 *arg2) {
    s16 temp_a3;
    s16 temp_t0;
    s32 var_a0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;

    temp_t0 = M2C_FIELD(arg0, s16 *, 0x9C);
    temp_a3 = *arg1;
    if (temp_a3 < temp_t0) {
        *arg1 = temp_t0;
        if (D_801D77B8 == 0) {
            var_a0 = M2C_FIELD(arg0, s32 *, 8);
            if (var_a0 < 0x2800) {
                var_v0_2 = 0x10000;
                if (D_8007C210 >= 3) {
                    var_v0_2 = 0x17000;
                }
                *arg2 = var_a0 + var_v0_2;
            } else {
                goto block_26;
            }
            goto block_27;
        }
        var_v0 = 0;
        if (D_801D77B8 == 1) {
            var_a0 = M2C_FIELD(arg0, s32 *, 8);
            if (var_a0 <= 0xB0FF) {
                var_v0_3 = 0x10000;
                if (D_8007C210 >= 3) {
                    var_v0_3 = 0x17000;
                }
                *arg2 = var_a0 + var_v0_3;
            } else {
                goto block_26;
            }
            goto block_27;
        }
    } else {
        var_v0 = 0;
        if (temp_a3 == temp_t0) {
            if (D_801D77B8 == 0) {
                var_a0 = M2C_FIELD(arg0, s32 *, 8);
                if (var_a0 < 0x2800) {
                    if (D_8007C210 >= 3) {
                        var_v0_4 = 0x17000;
                    } else {
                        var_v0_4 = 0x10000;
                    }
                    var_a0 += var_v0_4;
                }
                var_v0_5 = var_a0 < *arg2;
                goto block_25;
            }
            var_v0 = 0;
            if (D_801D77B8 == 1) {
                var_a0 = M2C_FIELD(arg0, s32 *, 8);
                if (var_a0 <= 0xB0FF) {
                    var_v0_6 = 0x10000;
                    if (D_8007C210 >= 3) {
                        var_v0_6 = 0x17000;
                    }
                    var_a0 += var_v0_6;
                }
                var_v0_5 = *arg2 < var_a0;
block_25:
                var_v0 = 0;
                if (var_v0_5 != 0) {
block_26:
                    *arg2 = var_a0;
block_27:
                    var_v0 = 1;
                }
            }
        }
    }
    return var_v0;
}

void func_80024C64(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_v0;
    s32 var_v0_2;
    void *temp_a3;

    var_a2 = arg2;
    temp_a3 = arg0 + 0x58;
    if (D_801D77B8 == 0) {
        var_a2 = 0x3600;
        goto block_5;
    }
    var_v0 = arg1 << 0x10;
    if (D_801D77B8 == 1) {
        var_a2 = 0x12100;
        if (D_801733D8 == &g_track_nodes_0) {
            var_a2 = 0xB100;
        }
block_5:
        var_v0 = arg1 << 0x10;
    }
    temp_v1 = var_v0 >> 0x10;
    if (temp_v1 < 5) {
        if (D_801D77B8 == 0) {
            var_a2_2 = var_a2 - (((s16) (arg1 & ((temp_v1 < 4) - 1)) * 0x500) & 0xFF00);
            if (var_a2_2 < 0) {
                var_v0_2 = 0x10000;
                if (D_8007C210 >= 3) {
                    var_v0_2 = 0x17000;
                }
                var_a2_2 += var_v0_2;
            }
            if ((((s32) ((D_801E90E0 << 0x10) + M2C_FIELD(arg0, s32 *, 8)) % (s32) (D_801E90E0 << 8)) & ~0xFF) == var_a2_2) {
                M2C_FIELD(temp_a3, s16 *, 0x4E) = 0;
                goto block_20;
            }
        } else {
            if (D_8007C210 < 3) {
                var_a2_3 = var_a2 + (((arg1 & ((temp_v1 < 3) - 1)) << 0xA) & 0xFC00);
            } else {
                var_a2_3 = var_a2 + 0x800;
            }
            if ((((s32) ((D_801E90E0 << 0x10) + M2C_FIELD(arg0, s32 *, 8)) % (s32) (D_801E90E0 << 8)) & ~0xFF) == var_a2_3) {
                M2C_FIELD(temp_a3, s16 *, 0x4E) = 0;
                goto block_20;
            }
        }
    } else if (((s32) (M2C_FIELD(temp_a3, s32 *, 0xA0) * 7) / 10) < M2C_FIELD(temp_a3, s32 *, 0x30)) {
block_20:
        M2C_FIELD(temp_a3, s16 *, 0x42) = -1;
        M2C_FIELD(temp_a3, s16 *, 0x4A) = 0;
    }
}

void func_80024E7C(void *arg0, s16 arg1) {
    if (arg1 < 5) {
        if ((((s32) ((D_801E90E0 << 0x10) + M2C_FIELD(arg0, s32 *, 8)) % (s32) (D_801E90E0 << 8)) & ~0xFF) == 0x2700) {
            goto block_4;
        }
    } else if (((s32) (M2C_FIELD(arg0, s32 *, 0xF8) * 7) / 10) < M2C_FIELD(arg0, s32 *, 0x88)) {
block_4:
        M2C_FIELD(arg0, s16 *, 0x9A) = -1;
        M2C_FIELD(arg0, s16 *, 0xA2) = 0;
    }
}

void func_80024F54(void *arg0) {
    s16 temp_v1;
    void *temp_a1;

    temp_v1 = M2C_FIELD(arg0, s16 *, 0xAE);
    temp_a1 = arg0 + 0x58;
    switch (temp_v1) {
    case 1:
        M2C_FIELD(arg0, s32 *, 0xB0) = (s32) M2C_FIELD(arg0, s32 *, 0xC);
        if ((M2C_FIELD(arg0, s32 *, 0xE0) >= 0x601) && (M2C_FIELD(arg0, s16 *, 0xA2) == -2)) {
            M2C_FIELD(arg0, s16 *, 0x9A) = -1;
            M2C_FIELD(arg0, s16 *, 0xA2) = -1;
        }
        if ((M2C_FIELD(temp_a1, s32 *, 0x30) >= 0x641) && (M2C_FIELD(temp_a1, s16 *, 0x4A) == -1)) {
            M2C_FIELD(temp_a1, s16 *, 0x4A) = 0;
        }
        if (M2C_FIELD(temp_a1, s16 *, 0x44) == 2) {
            M2C_FIELD(temp_a1, s16 *, 0x56) = 2;
            M2C_FIELD(temp_a1, s16 *, 0x4A) = -2;
            M2C_FIELD(temp_a1, s16 *, 0x42) = -3;
            return;
        }
        return;
    case 2:
        if (M2C_FIELD(arg0, s32 *, 0xE0) >= 0x401) {
            M2C_FIELD(arg0, s16 *, 0xAE) = 3;
            M2C_FIELD(arg0, s16 *, 0xA6) = 0;
            M2C_FIELD(arg0, s16 *, 0xA2) = -1;
            return;
        }
        break;
    case 3:
        if (M2C_FIELD(arg0, s32 *, 0x88) >= 0x280) {
            M2C_FIELD(arg0, s16 *, 0x9A) = -3;
            M2C_FIELD(arg0, s16 *, 0xAE) = 0;
            M2C_FIELD(arg0, s16 *, 0xA2) = 0;
            M2C_FIELD(arg0, s16 *, 0x9A) = -1;
        }
        break;
    }
}

void func_80025050(void *arg0) {
    s32 var_a2;
    s32 var_a3;
    s32 var_t0;

    var_t0 = 3;
    if (D_8007C210 == 1) {
        var_t0 = 2;
    }
    var_a3 = 0x4A00;
    if (D_801D77B8 == 0) {
        var_a2 = 0x1600;
        if (M2C_FIELD(arg0, s16 *, 0xAA) == 0) {
            if ((((s32) ((D_801E90E0 << 0x10) + M2C_FIELD(arg0, s32 *, 8)) % (s32) (D_801E90E0 << 8)) & ~0xFF) == 0x4A00) {
                if (M2C_FIELD(arg0, s16 *, 0x9C) < var_t0) {
                    goto block_14;
                }
                goto block_13;
            }
            goto block_14;
        }
        goto block_16;
    }
    var_a3 = 0x9E00;
    if (D_801D77B8 == 1) {
        var_a2 = 0xBD00;
        if (D_8007C210 >= 3) {
            var_a3 = 0x10E00;
            var_a2 = 0x12D00;
        }
        if (M2C_FIELD(arg0, s16 *, 0xAA) == 0) {
            if (((((s32) ((D_801E90E0 << 0x10) + M2C_FIELD(arg0, s32 *, 8)) % (s32) (D_801E90E0 << 8)) & ~0xFF) == var_a3) && (M2C_FIELD(arg0, s16 *, 0x9C) >= var_t0)) {
block_13:
                M2C_FIELD(arg0, s16 *, 0xAA) = 2;
                return;
            }
block_14:
            if ((((s32) ((D_801E90E0 << 0x10) + M2C_FIELD(arg0, s32 *, 8)) % (s32) (D_801E90E0 << 8)) & ~0xFF) == var_a3) {
                M2C_FIELD(arg0, s16 *, 0xAA) = 1;
            }
        } else {
block_16:
            if ((M2C_FIELD(arg0, s16 *, 0xAA) > 0) && ((((s32) ((D_801E90E0 << 0x10) + M2C_FIELD(arg0, s32 *, 8)) % (s32) (D_801E90E0 << 8)) & ~0xFF) == var_a2)) {
                M2C_FIELD(arg0, s16 *, 0xAA) = 0;
            }
        }
    }
}

void func_80025BFC(void) {
    M2C_UNK *var_s0;
    s32 var_s1;
    s32 var_v0;

    var_s0 = &D_801E9250;
    var_s1 = 0;
    do {
        var_s1 += 1;
        if (M2C_FIELD(var_s0, s16 *, 0) != 0) {
            var_v0 = var_s1 < 0xC;
            if (M2C_FIELD(var_s0, s32 *, 0x58) == 1) {
                func_8002128C(var_s0, 0);
                goto block_4;
            }
        } else {
block_4:
            var_v0 = var_s1 < 0xC;
        }
        var_s0 += 0x114;
    } while (var_v0 != 0);
}

void func_80025C70(void) {
    func_8002128C(&D_801E9250, 1);
}

void func_800264C4(s32 arg0) {
    s32 var_a0;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_t1;
    s32 var_t1_2;
    s32 var_t3;
    s32 var_t3_2;
    s32 var_t6;
    s32 var_t7;
    s32 var_t7_2;
    s8 temp_t2;
    s8 temp_t2_2;
    s8 temp_v0;
    s8 temp_v0_2;
    s8 temp_v1;
    s8 temp_v1_2;
    s8 var_a2;
    s8 var_a2_2;
    s8 var_t0;
    s8 var_t0_2;
    void *temp_a1;
    void *temp_a1_2;

    var_t7 = 0;
    var_t3 = 0;
    do {
loop_2:
        var_t0 = 0x48;
        var_t1 = 0;
loop_3:
        var_a2 = ((var_t3 + var_t7) & 1) * 0x18;
        var_a3 = 0;
        temp_t2 = (var_t0 + 0xC) - 1;
loop_4:
        temp_a1 = arg0 + (((var_t7 * 2) + var_t1) * 0x5B0) + (((var_t3 * 2) + var_a3) * 0x34);
        M2C_FIELD(temp_a1, s8 *, 0xC) = var_a2;
        M2C_FIELD(temp_a1, s8 *, 0xD) = var_t0;
        M2C_FIELD(temp_a1, s8 *, 0x18) = var_a2;
        M2C_FIELD(temp_a1, s8 *, 0x19) = temp_t2;
        temp_v1 = var_a2 + 0xC;
        temp_v0 = temp_v1 - 1;
        M2C_FIELD(temp_a1, s8 *, 0x24) = temp_v0;
        M2C_FIELD(temp_a1, s8 *, 0x25) = var_t0;
        M2C_FIELD(temp_a1, s8 *, 0x30) = temp_v0;
        M2C_FIELD(temp_a1, s8 *, 0x31) = temp_t2;
        var_a3 += 1;
        var_a2 = temp_v1;
        if (var_a3 < 2) {
            goto loop_4;
        }
        var_t1 += 1;
        var_t0 += 0xC;
        if (var_t1 < 2) {
            goto loop_3;
        }
        var_t3 += 1;
        if (var_t3 < 0x1C) {
            goto loop_2;
        }
        var_t7 += 1;
        var_t3 = 0;
    } while (var_t7 < 0x14);
    var_t7_2 = 3;
    var_a0 = 0;
    do {
        var_t3_2 = 2;
        var_t6 = 0;
loop_10:
        var_t0_2 = var_a0 * 8;
        var_t1_2 = 0;
loop_11:
        var_a2_2 = var_t6 * 8;
        var_a3_2 = 0;
        temp_t2_2 = (var_t0_2 + 0xC) - 1;
loop_12:
        temp_a1_2 = arg0 + (((var_t7_2 * 2) + var_t1_2) * 0x5B0) + (((var_t3_2 * 2) + var_a3_2) * 0x34);
        M2C_FIELD(temp_a1_2, s8 *, 0xC) = var_a2_2;
        M2C_FIELD(temp_a1_2, s8 *, 0xD) = var_t0_2;
        M2C_FIELD(temp_a1_2, s8 *, 0x18) = var_a2_2;
        M2C_FIELD(temp_a1_2, s8 *, 0x19) = temp_t2_2;
        temp_v1_2 = var_a2_2 + 0xC;
        temp_v0_2 = temp_v1_2 - 1;
        M2C_FIELD(temp_a1_2, s8 *, 0x24) = temp_v0_2;
        M2C_FIELD(temp_a1_2, s8 *, 0x25) = var_t0_2;
        M2C_FIELD(temp_a1_2, s8 *, 0x30) = temp_v0_2;
        M2C_FIELD(temp_a1_2, s8 *, 0x31) = temp_t2_2;
        var_a3_2 += 1;
        var_a2_2 = temp_v1_2;
        if (var_a3_2 < 2) {
            goto loop_12;
        }
        var_t1_2 += 1;
        var_t0_2 += 0xC;
        if (var_t1_2 < 2) {
            goto loop_11;
        }
        var_t3_2 += 1;
        var_t6 += 3;
        if (var_t3_2 < 0xC) {
            goto loop_10;
        }
        var_t7_2 += 1;
        var_a0 += 3;
    } while (var_t7_2 < 7);
}

void func_80026794(void) {
    D_801D77A8 = 0;
    func_800266B8(0);
    func_800266B8(1);
    func_800264C4(&D_8012E4C0);
    func_800264C4(&D_801510B4);
}

void func_80026E7C(void *arg0) {
    s32 sp10;
    s32 sp18;
    s16 temp_a1;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    void *temp_s3;

    temp_s3 = arg0 + 0x58;
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
    temp_v0 = var_v1 >> 8;
    M2C_FIELD(arg0, s32 *, 0x68) = temp_v0;
    sp10 = (s32) ((temp_s2 * M2C_FIELD(arg0, s32 *, 0x60)) - (temp_s1 * temp_v0)) / 4096;
    temp_v0_2 = (s32) ((temp_s1 * M2C_FIELD(arg0, s32 *, 0x60)) + (temp_s2 * M2C_FIELD(arg0, s32 *, 0x68))) / 4096;
    var_v1_2 = temp_s1 * temp_v0_2;
    sp18 = temp_v0_2;
    if (var_v1_2 < 0) {
        var_v1_2 += 0xFFF;
    }
    M2C_FIELD(arg0, s32 *, 0x60) = (s32) (var_v1_2 >> 0xC);
    var_v0_2 = temp_s2 * sp18;
    if (var_v0_2 < 0) {
        var_v0_2 += 0xFFF;
    }
    M2C_FIELD(arg0, s32 *, 0x68) = (s32) (var_v0_2 >> 0xC);
    if (M2C_FIELD(arg0, s16 *, 0xC4) == 1) {
        temp_v1 = M2C_FIELD(arg0, s32 *, 0xA0) * D_8007B1F0;
        D_8007B1F0 = 0;
        D_801732F0 = temp_v1;
        if ((M2C_FIELD(arg0, s32 *, 0xA0) >= 0x3C1) && (M2C_FIELD(arg0, s32 *, 0x94) < temp_v1)) {
            M2C_FIELD(arg0, s32 *, 0xB4) = 1;
            var_v1_3 = 0x3E8 - ((M2C_FIELD(arg0, s32 *, 0x98) - 0x3E8) * 8);
            if (var_v1_3 < 0x3E8) {
                var_v1_3 = 0x3E8;
            }
            var_v0_3 = ((s32) (-sp10 * var_v1_3) / 1000) * 2;
            goto block_23;
        }
    } else if (M2C_FIELD(arg0, s16 *, 0xC8) < 0x80) {
        temp_a1 = M2C_FIELD(arg0, s16 *, 0xC6);
        if (temp_a1 == 1) {
            var_v0_4 = sp10;
            if (var_v0_4 < 0) {
                var_v0_4 = -var_v0_4;
            }
            var_v1_4 = var_v0_4 * M2C_FIELD(arg0, s32 *, 0xA0);
            if (var_v1_4 < 0) {
                var_v1_4 += 0x3F;
            }
            temp_v1_2 = var_v1_4 >> 6;
            D_801732F0 = temp_v1_2;
            D_8007B1F0 = 0;
            if ((M2C_FIELD(temp_s3, s32 *, 0x48) >= 0x141) && (M2C_FIELD(temp_s3, s32 *, 0x3C) < temp_v1_2)) {
                M2C_FIELD(temp_s3, s32 *, 0x5C) = (s32) temp_a1;
                var_v0_3 = -sp10;
block_23:
                D_8012CFE0 = var_v0_3;
                D_801D7E48 = D_801733B8 ^ func_8001B2D4(arg0);
            }
        } else {
            D_8007B1F0 += 1;
        }
    } else {
        D_8007B1F0 = 0;
    }
}

void func_800273B4(s32 arg0, void *arg1) {
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_t0;
    s32 temp_v1;
    s32 var_a2;
    s32 var_v1;
    void *temp_a1_2;
    void *temp_a3;

    temp_a1 = arg0 >> 8;
    temp_v1 = D_801E90E0 << 8;
    temp_a0 = arg0 & 0xFF;
    temp_a3 = (((s32) (temp_a1 + temp_v1) % (s32) D_801E90E0) * 0x14) + D_801733D8;
    temp_t0 = 0x100 - temp_a0;
    var_a2 = M2C_FIELD(temp_a3, s32 *, 0);
    temp_a1_2 = (((s32) (temp_a1 + (temp_v1 + 1)) % (s32) D_801E90E0) * 0x14) + D_801733D8;
    if (var_a2 < 0) {
        var_a2 += 0x3FFF;
    }
    var_v1 = (temp_t0 * (var_a2 >> 0xE)) + (temp_a0 * ((s32) M2C_FIELD(temp_a1_2, s32 *, 0) / 16384));
    if (var_v1 < 0) {
        var_v1 += 0xFF;
    }
    M2C_FIELD(arg1, s32 *, 0) = (s32) (D_801733A0 - (var_v1 >> 8));
    M2C_FIELD(arg1, s32 *, 4) = (s32) ((s32) ((s32) -((temp_t0 * M2C_FIELD(temp_a3, s16 *, 8)) + (temp_a0 * M2C_FIELD(temp_a1_2, s16 *, 8))) / 256) / 2);
    M2C_FIELD(arg1, s32 *, 8) = (s32) ((s32) ((temp_t0 * ((s32) M2C_FIELD(temp_a3, s32 *, 4) / 16384)) + (temp_a0 * ((s32) M2C_FIELD(temp_a1_2, s32 *, 4) / 16384))) / 256);
}

void func_800275F0(void *arg0) {
    s32 sp10;
    s32 sp18;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_s3;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    s32 var_v0_2;
    void *temp_s2;

    temp_s3 = M2C_FIELD(arg0, s32 *, 0xC);
    temp_a0 = M2C_FIELD(arg0, s32 *, 8);
    temp_s2 = arg0 + 0x58;
    if (D_801D7E48 != 0) {
        var_s0 = temp_a0 + 0x180;
    } else {
        var_s0 = temp_a0 - 0x180;
    }
    func_800273B4(var_s0, &sp10);
    temp_v0 = func_8002757C(var_s0);
    var_v0 = rcos(temp_v0) * temp_s3;
    if (var_v0 < 0) {
        var_v0 += 0x7FF;
    }
    sp10 += var_v0 >> 0xB;
    var_v0_2 = rsin(temp_v0) * temp_s3;
    if (var_v0_2 < 0) {
        var_v0_2 += 0x7FF;
    }
    temp_a1 = sp18 - (var_v0_2 >> 0xB);
    sp18 = temp_a1;
    M2C_FIELD(temp_s2, s32 *, 0x50) = (s32) ((func_80019CA8(M2C_FIELD(temp_s2, s32 *, 0x50), 0x400 - func_800187A0(sp10 - M2C_FIELD(arg0, s32 *, 0x10), temp_a1 - M2C_FIELD(arg0, s32 *, 0x18))) / 5) + M2C_FIELD(temp_s2, s32 *, 0x50));
}

void func_80027734(void *arg0) {
    s32 sp10;
    s32 sp18;
    s16 var_v0_3;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a1;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_lo_4;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_6;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_s3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_8;
    s32 var_v0_9;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    s32 var_v1_4;
    u32 temp_v0_5;
    void *temp_s1;

    var_s3 = D_8012CFE0;
    if (D_8012CFE0 < 0) {
        var_s3 = -var_s3;
    }
    temp_s1 = arg0 + 0x58;
    temp_v0 = func_80019C6C(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(arg0, s32 *, 0xA8));
    if (temp_v0 < 0x201) {
        var_v0 = temp_v0 * 0x7F;
        if (var_v0 < 0) {
            var_v0 += 0x1FF;
        }
        var_v0_2 = var_v0 >> 9;
    } else {
        var_v0_2 = 0x7F;
    }
    D_801D3572 = (s16) var_v0_2;
    if (temp_v0 < 0x201) {
        var_v0_3 = ((s32) (temp_v0 * 3) / 2) + 0x1800;
    } else {
        var_v0_3 = 0x1B00;
    }
    D_801D3574 = var_v0_3;
    D_801D3572 = (s16) ((s32) (D_801D3572 * 0x3C) / 100);
    if ((temp_v0 < 0x80) && (var_s3 < 0x800)) {
        var_v1 = (0x800 - var_s3) * 0xFA0;
        if (var_v1 < 0) {
            var_v1 += 0xFF;
        }
        D_801732F0 -= var_v1 >> 8;
    }
    temp_v1 = M2C_FIELD(temp_s1, s32 *, 0x48);
    if (temp_v1 < 0x190) {
        D_801732F0 -= (0x190 - temp_v1) * 0x64;
    }
    if (D_801732F0 > 0) {
        temp_lo = ((s32) (func_80019CA8(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(temp_s1, s32 *, 0x54)) * 0x62) / 100) * (D_80173358 + 0x800);
        D_8012CFE0 += (temp_lo / 2048) * 0x10;
        if ((u32) (M2C_FIELD(temp_s1, s32 *, 0x1C) + 0x7F) < 0xFFU) {
            if (func_80019C6C(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(temp_s1, s32 *, 0x50)) < 0x200) {
                var_v0_4 = D_8012CFE0 * 0x1F;
                if (var_v0_4 < 0) {
                    var_v0_4 += 0x1F;
                }
                D_8012CFE0 = var_v0_4 >> 5;
                var_v0_5 = func_80019CA8(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(temp_s1, s32 *, 0x50)) + D_8012CFE0;
                goto block_25;
            }
            if (var_s3 < 0x800) {
                var_v0_5 = (temp_lo / 4096) + D_8012CFE0;
block_25:
                D_8012CFE0 = var_v0_5;
            }
        }
        if (D_8012CFE0 >= 0x3601) {
            D_8012CFE0 = 0x3600;
        }
        if (D_8012CFE0 < -0x3600) {
            D_8012CFE0 = -0x3600;
        }
        var_v1_2 = D_8012CFE0;
        if (var_v1_2 < 0) {
            var_v1_2 += 0xFF;
        }
        M2C_FIELD(arg0, s32 *, 0x24) = (s32) ((var_v1_2 >> 8) + M2C_FIELD(arg0, s32 *, 0x24));
        D_801732F0 -= 0x40;
        temp_v0_2 = func_80019C6C(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(temp_s1, s32 *, 0x50));
        temp_lo_2 = temp_v0_2 * temp_v0_2;
        var_a0 = temp_lo_2 >> 4;
        if (temp_lo_2 < 0) {
            var_a0 = (s32) (temp_lo_2 + 0xF) >> 4;
        }
        if (var_a0 < 0) {
            var_a0 += 0xFFF;
        }
        var_a1 = 0x3600 - var_s3;
        temp_a0 = D_801732F0 - (var_a0 >> 0xC);
        D_801732F0 = temp_a0;
        if (var_a1 < 0) {
            var_a1 += 0x3F;
        }
        temp_a1 = temp_a0 - (var_a1 >> 6);
        D_801732F0 = temp_a1;
        temp_a0_2 = M2C_FIELD(temp_s1, s32 *, 0x48);
        if (temp_a0_2 < ((s32) M2C_FIELD(temp_s1, s32 *, 0x44) / 2)) {
            D_801732F0 = temp_a1 - ((s32) (((s32) M2C_FIELD(temp_s1, s32 *, 0x44) / 2) - temp_a0_2) / 8);
        }
        D_801732F0 -= M2C_FIELD(temp_s1, s16 *, 0x72) * 4;
    } else {
        D_8012CFE0 = (s32) (D_8012CFE0 * 0xF) / 16;
        if (var_s3 < 0x1000) {
            M2C_FIELD(temp_s1, s32 *, 0x58) = (s32) ((s32) ((0x64 - ((M2C_FIELD(temp_s1, s16 *, 0x2A) - 1) * 4)) * 0x2710 * M2C_FIELD(temp_s1, s32 *, 0x48)) / 100);
            temp_v0_3 = func_80019CA8(M2C_FIELD(temp_s1, s32 *, 0x50), M2C_FIELD(arg0, s32 *, 0x24));
            D_801D7E30 = temp_v0_3;
            var_a1_2 = temp_v0_3;
            if (temp_v0_3 < 0) {
                var_a1_2 = -var_a1_2;
            }
            D_80173438 = M2C_FIELD(temp_s1, s32 *, 0x50);
            M2C_FIELD(temp_s1, s32 *, 0x50) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
            if (var_a1_2 >= 0x401) {
                var_a1_2 = 0x800 - var_a1_2;
            }
            temp_lo_3 = var_a1_2 * var_a1_2;
            var_a0_2 = temp_lo_3 * M2C_FIELD(temp_s1, s32 *, 0x48);
            if (var_a0_2 < 0) {
                var_a0_2 += 0xFFFFF;
            }
            temp_lo_4 = (0x100000 - temp_lo_3) * M2C_FIELD(temp_s1, s32 *, 0x48);
            D_8007C4E8 = var_a0_2 >> 0x14;
            var_v0_6 = temp_lo_4 >> 0x14;
            if (temp_lo_4 < 0) {
                var_v0_6 = (s32) (temp_lo_4 + 0xFFFFF) >> 0x14;
            }
            M2C_FIELD(temp_s1, s32 *, 0x48) = var_v0_6;
            M2C_FIELD(temp_s1, s32 *, 0x5C) = 2;
        }
    }
    M2C_FIELD(temp_s1, s32 *, 0x54) = (s32) M2C_FIELD(arg0, s32 *, 0x24);
    func_800275F0(arg0);
    temp_v0_4 = func_80019C6C(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(temp_s1, s32 *, 0x50));
    if (temp_v0_4 >= 0x401) {
        temp_v0_5 = M2C_FIELD(temp_s1, u32 *, 0x4C);
        var_a0_3 = (0x3600 - var_s3) * 4 * M2C_FIELD(temp_s1, u32 *, 0x4C) * (temp_v0_4 - 0x400);
        if (var_a0_3 < 0) {
            var_a0_3 += 0x3FF;
        }
        var_v0_7 = ((s32) (temp_v0_5 + (temp_v0_5 >> 0x1F)) >> 1) + ((s32) (var_a0_3 >> 0xA) / 13824);
    } else {
        var_v0_7 = (s32) ((0x200 - temp_v0_4) * M2C_FIELD(temp_s1, u32 *, 0x4C)) / 512;
    }
    M2C_FIELD(temp_s1, u32 *, 0x4C) = (u32) var_v0_7;
    temp_s0 = M2C_FIELD(temp_s1, s32 *, 0x50);
    func_80026CA8(arg0);
    M2C_FIELD(temp_s1, s32 *, 0x50) = temp_s0;
    temp_s0_2 = rsin(M2C_FIELD(arg0, s32 *, 0x24));
    temp_s2 = rcos(M2C_FIELD(arg0, s32 *, 0x24));
    var_v0_8 = rsin(M2C_FIELD(temp_s1, s32 *, 0x50)) * M2C_FIELD(temp_s1, s32 *, 0x48);
    if (var_v0_8 < 0) {
        var_v0_8 += 0xFF;
    }
    M2C_FIELD(temp_s1, s32 *, 8) = (s32) (var_v0_8 >> 8);
    var_v1_3 = rcos(M2C_FIELD(temp_s1, s32 *, 0x50)) * M2C_FIELD(temp_s1, s32 *, 0x48);
    if (var_v1_3 < 0) {
        var_v1_3 += 0xFF;
    }
    temp_v0_6 = var_v1_3 >> 8;
    var_a0_4 = (temp_s2 * M2C_FIELD(temp_s1, s32 *, 8)) - (temp_s0_2 * temp_v0_6);
    M2C_FIELD(temp_s1, s32 *, 0x10) = temp_v0_6;
    if (var_a0_4 < 0) {
        var_a0_4 += 0xFFF;
    }
    temp_a0_3 = var_a0_4 >> 0xC;
    sp10 = temp_a0_3;
    var_v1_4 = (temp_s0_2 * M2C_FIELD(temp_s1, s32 *, 8)) + (temp_s2 * M2C_FIELD(temp_s1, s32 *, 0x10));
    if (var_v1_4 < 0) {
        var_v1_4 += 0xFFF;
    }
    temp_v1_2 = var_v1_4 >> 0xC;
    var_v0_9 = (temp_s2 * temp_a0_3) + (temp_s0_2 * temp_v1_2);
    sp18 = temp_v1_2;
    if (var_v0_9 < 0) {
        var_v0_9 += 0xFFF;
    }
    M2C_FIELD(temp_s1, s32 *, 8) = (s32) (var_v0_9 >> 0xC);
    M2C_FIELD(temp_s1, s32 *, 0x10) = (s32) ((s32) ((-temp_s0_2 * sp10) + (temp_s2 * sp18)) / 4096);
}

void func_80027F60(void *arg0) {
    s32 sp18;
    s32 temp_a0;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_v0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    void *temp_s3;

    temp_s3 = arg0 + 0x58;
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) ((func_80019CA8(M2C_FIELD(arg0, s32 *, 0x24), M2C_FIELD(arg0, s32 *, 0xAC)) / 5) + M2C_FIELD(arg0, s32 *, 0x24));
    func_80026CA8(arg0);
    temp_s1 = rsin(M2C_FIELD(arg0, s32 *, 0x24));
    temp_s2 = rcos(M2C_FIELD(arg0, s32 *, 0x24));
    var_v0 = rsin(M2C_FIELD(arg0, s32 *, 0xA8) + D_801D7E30) * M2C_FIELD(arg0, s32 *, 0xA0);
    if (var_v0 < 0) {
        var_v0 += 0xFF;
    }
    M2C_FIELD(arg0, s32 *, 0x60) = (s32) (var_v0 >> 8);
    var_v1 = rcos(M2C_FIELD(arg0, s32 *, 0xA8) + D_801D7E30) * M2C_FIELD(arg0, s32 *, 0xA0);
    if (var_v1 < 0) {
        var_v1 += 0xFF;
    }
    M2C_FIELD(arg0, s32 *, 0x68) = (s32) (var_v1 >> 8);
    var_v0_2 = (temp_s1 * M2C_FIELD(arg0, s32 *, 0x60)) + (temp_s2 * M2C_FIELD(arg0, s32 *, 0x68));
    if (var_v0_2 < 0) {
        var_v0_2 += 0xFFF;
    }
    sp18 = var_v0_2 >> 0xC;
    var_v1_2 = rsin(D_80173438) * D_8007C4E8;
    if (var_v1_2 < 0) {
        var_v1_2 += 0xFF;
    }
    var_v0_3 = temp_s1 * sp18;
    if (var_v0_3 < 0) {
        var_v0_3 += 0xFFF;
    }
    M2C_FIELD(arg0, s32 *, 0x60) = (s32) ((var_v1_2 >> 8) + (var_v0_3 >> 0xC));
    var_v1_3 = rcos(D_80173438) * D_8007C4E8;
    if (var_v1_3 < 0) {
        var_v1_3 += 0xFF;
    }
    var_v0_4 = temp_s2 * sp18;
    if (var_v0_4 < 0) {
        var_v0_4 += 0xFFF;
    }
    M2C_FIELD(arg0, s32 *, 0x68) = (s32) ((var_v1_3 >> 8) + (var_v0_4 >> 0xC));
    if ((M2C_FIELD(arg0, s16 *, 0xC4) != 1) && (M2C_FIELD(arg0, s16 *, 0xC6) != 1) && (M2C_FIELD(temp_s3, s16 *, 0x70) < 0x80)) {
        D_8007B1F0 += 1;
    } else {
        D_8007B1F0 = 0;
    }
    var_v0_5 = D_8007C4E8 * 0x1F;
    if (var_v0_5 < 0) {
        var_v0_5 += 0x1F;
    }
    temp_a0 = var_v0_5 >> 5;
    D_8007C4E8 = temp_a0;
    temp_v0 = (s32) (D_801D7E30 * 0x1F) / 32;
    D_801D7E30 = temp_v0;
    if ((temp_a0 == 0) && (temp_v0 == 0)) {
        M2C_FIELD(temp_s3, s32 *, 0x5C) = 0;
    }
    D_801D3572 = 0;
}

void func_80028A0C(void *arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 temp_a0;
    s32 var_s6;

    var_s6 = arg7;
    func_80047C10();
    M2C_FIELD(arg0, s16 *, 8) = arg1;
    M2C_FIELD(arg0, s16 *, 0xA) = arg2;
    M2C_FIELD(arg0, s16 *, 0x10) = arg3;
    M2C_FIELD(arg0, s16 *, 0x12) = (s16) arg4;
    M2C_FIELD(arg0, s8 *, 0xC) = (s8) arg5;
    M2C_FIELD(arg0, s8 *, 0xD) = (s8) arg6;
    temp_a0 = (var_s6 & 0xF) * 0x10;
    if (var_s6 < 0) {
        var_s6 += 0xF;
    }
    M2C_FIELD(arg0, s16 *, 0xE) = func_80047920(temp_a0, (var_s6 >> 4) + 0x1E0);
    func_80047B20(arg0, 1);
}

s32 func_8002989C(s32 arg0, s32 arg1) {
    M2C_UNK sp10;
    s8 sp28;
    M2C_UNK *var_a3;
    void *temp_t0;
    void *var_a2;

    var_a3 = &sp10;
    var_a2 = (D_801D7768 * 0x22BF4) + &D_8012D950;
    temp_t0 = var_a2 + 0x50;
    do {
        M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
        M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
        M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
        M2C_FIELD(var_a3, s32 *, 0xC) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
        var_a2 += 0x10;
        var_a3 += 0x10;
    } while (var_a2 != temp_t0);
    M2C_FIELD(var_a3, s32 *, 0) = (s32) M2C_FIELD(var_a2, s32 *, 0);
    M2C_FIELD(var_a3, s32 *, 4) = (s32) M2C_FIELD(var_a2, s32 *, 4);
    M2C_FIELD(var_a3, s32 *, 8) = (s32) M2C_FIELD(var_a2, s32 *, 8);
    sp28 = 0;
    SetDrawEnv(arg1, &sp10, var_a2, var_a3);
    AddPrim(arg0, arg1);
    return arg1 + 0x40;
}

void func_8002AD68(void) {
    M2C_UNK *var_v1;

    D_80173470 = 0;
    D_801D77F0 = 0;
    D_801D34E8 = 0;
    D_801D77C0 = 1;
    if (D_801733B8 != 0) {
        var_v1 = &D_80074188;
        if (D_8007C210 < 3) {
            var_v1 = &D_80074158;
        }
    } else {
        var_v1 = &D_80074128;
        if (D_8007C210 < 3) {
            var_v1 = &D_80074108;
        }
    }
    D_801D7760 = var_v1;
    D_801734B0 = 0;
    D_80173478 = (s32) D_8007C210;
}

void func_8002AE14(s32 arg0, void *arg1, void *arg2) {
    void *temp_v0;

    temp_v0 = (arg0 * 0x28) + D_8007C4F8;
    M2C_FIELD(temp_v0, u16 *, 0) = (u16) M2C_FIELD(arg1, u16 *, 0x10);
    M2C_FIELD(temp_v0, u16 *, 2) = (u16) M2C_FIELD(arg1, u16 *, 0x14);
    M2C_FIELD(temp_v0, u16 *, 4) = (u16) M2C_FIELD(arg1, u16 *, 0x18);
    M2C_FIELD(temp_v0, u16 *, 6) = (u16) M2C_FIELD(arg1, u16 *, 0x40);
    M2C_FIELD(temp_v0, u16 *, 8) = (u16) M2C_FIELD(arg1, u16 *, 0x20);
    M2C_FIELD(temp_v0, u16 *, 0xA) = (u16) M2C_FIELD(arg1, u16 *, 0x24);
    M2C_FIELD(temp_v0, u16 *, 0xC) = (u16) M2C_FIELD(arg1, u16 *, 0x28);
    M2C_FIELD(temp_v0, u16 *, 0xE) = (u16) M2C_FIELD(arg1, u16 *, 0x38);
    M2C_FIELD(temp_v0, u16 *, 0x10) = (u16) M2C_FIELD(arg2, u16 *, 0x10);
    M2C_FIELD(temp_v0, u16 *, 0x12) = (u16) M2C_FIELD(arg2, u16 *, 0x14);
    M2C_FIELD(temp_v0, u16 *, 0x14) = (u16) M2C_FIELD(arg2, u16 *, 0x18);
    M2C_FIELD(temp_v0, u16 *, 0x16) = (u16) M2C_FIELD(arg2, u16 *, 0x40);
    M2C_FIELD(temp_v0, u16 *, 0x18) = (u16) M2C_FIELD(arg2, u16 *, 0x20);
    M2C_FIELD(temp_v0, u16 *, 0x1A) = (u16) M2C_FIELD(arg2, u16 *, 0x24);
    D_801D7E88 = (s32) D_8007C25A;
    D_801D77F8 = (s32) D_801E9252;
    M2C_FIELD(temp_v0, u16 *, 0x1C) = (u16) M2C_FIELD(arg2, u16 *, 0x28);
    M2C_FIELD(temp_v0, u16 *, 0x1E) = (u16) M2C_FIELD(arg2, u16 *, 0x38);
    M2C_FIELD(temp_v0, s32 *, 0x20) = (s32) M2C_FIELD(arg1, s32 *, 8);
    M2C_FIELD(temp_v0, s32 *, 0x24) = (s32) M2C_FIELD(arg2, s32 *, 8);
}

void func_8002B1A0(void) {
    s32 temp_s0;

    temp_s0 = D_8012CF68 + 0xB6C;
    if (D_801734B0 == 0) {
        if (D_80173310 & 8) {
            func_80028578(0x2C, 0x18, &D_800771B0, 0x64);
        }
        *(s32 *)0x1F800000 = func_800297D8(temp_s0, *(s32 *)0x1F800000, 0x18, 0x12, 0x58, 0x14, 0, 0, 0);
    }
}

void func_8002D134(void) {
    M2C_UNK *var_s0;
    s32 *var_a0;
    s32 *var_a0_2;
    s32 *var_v1_2;
    s32 var_a1;
    s32 var_v1;
    s32 var_v1_3;
    u16 temp_v0;

    var_s0 = &D_800741D0;
    func_800496C8(&D_80010330, 0xCF0, 0xCC0);
    D_80173148 = &D_801D8360;
    D_801D8360 = 0;
    D_801D8364 = 0;
    var_a0 = &D_801D8360;
    var_v1 = 0;
    do {
        M2C_FIELD(var_a0, s16 *, 8) = 0;
        var_v1 += 3;
        var_a0 += 0xC;
    } while (var_v1 < 0x300);
    var_a1 = 0;
    var_v1_2 = D_80173148;
    M2C_FIELD(var_v1_2, s16 *, 0xC08) = 0x140;
    M2C_FIELD(var_v1_2, s16 *, 0xC0A) = 0x440;
    M2C_FIELD(var_v1_2, s16 *, 0xC0C) = 1;
    M2C_FIELD(var_v1_2, s16 *, 0xC10) = 0x280;
    M2C_FIELD(var_v1_2, s16 *, 0xC12) = 0x400;
    M2C_FIELD(var_v1_2, s16 *, 0xC14) = -2;
    M2C_FIELD(var_v1_2, s16 *, 0xC18) = 0x280;
    M2C_FIELD(var_v1_2, s16 *, 0xC1A) = -0x100;
    do {
        M2C_FIELD(var_v1_2, s16 *, 0xC1C) = 0;
        temp_v0 = M2C_FIELD(var_s0, u16 *, 4);
        var_a1 += 1;
        var_s0 += 8;
        M2C_FIELD(var_v1_2, u16 *, 0xC1E) = temp_v0;
        var_v1_2 += 8;
    } while (var_a1 < 0xE);
    var_a0_2 = D_80173148;
    var_v1_3 = 0;
    do {
        M2C_FIELD(var_a0_2, s16 *, 0xC8E) = -1;
        var_v1_3 += 3;
        var_a0_2 += 6;
    } while (var_v1_3 < 0x18);
    M2C_FIELD(D_80173148, s16 *, 0xCBE) = 0xFF;
}

void func_8002E400(void) {
    s32 temp_v0;

    temp_v0 = VSync(1);
    if (temp_v0 >= 0xF1) {
        D_8007C4E0 += 1;
        if (D_800771C8 < temp_v0) {
            D_800771C8 = temp_v0;
            D_8007B1C4 = D_8007B1BC;
        }
    }
    D_8007B1B8 = D_8007C4E0;
    D_8007B1C0 = D_800771C8;
}

void func_8002EBF0(void) {
    func_800434D0(&D_80074368);
    func_800434A0(&D_80074388);
    M2C_FIELD(&D_80173448, s32 *, 0) = (s32) M2C_FIELD(&D_80074388, s32 *, 0);
    M2C_FIELD(&D_80173448, s32 *, 4) = (s32) M2C_FIELD(&D_80074388, s32 *, 4);
    M2C_FIELD(&D_80173448, s32 *, 8) = (s32) M2C_FIELD(&D_80074388, s32 *, 8);
    M2C_FIELD(&D_80173448, s32 *, 0xC) = (s32) M2C_FIELD(&D_80074388, s32 *, 0xC);
    M2C_FIELD(&D_80173448, s32 *, 0x10) = (s32) M2C_FIELD(&D_80074388, s32 *, 0x10);
    M2C_FIELD(&D_80173448, s32 *, 0x14) = (s32) M2C_FIELD(&D_80074388, s32 *, 0x14);
    M2C_FIELD(&D_80173448, s32 *, 0x18) = (s32) M2C_FIELD(&D_80074388, s32 *, 0x18);
    M2C_FIELD(&D_80173448, s32 *, 0x1C) = (s32) M2C_FIELD(&D_80074388, s32 *, 0x1C);
    func_8003FBE8(0x20, 0x20, 0x20);
    func_8003FC08(0, 0, 0);
    func_80044F64(0x4E20, 0x140);
}

void func_80030EF4(void) {
    func_80030DBC();
}

s32 func_80031840(s32 arg0, M2C_UNK arg1, s32 arg2, M2C_UNK arg3, s32 arg4) {
    s32 temp_v0;

    func_80031238(arg1, &D_800105D4, 0x119, 0x590, 0x100);
    func_800314BC(arg3);
    temp_v0 = func_800497E8(arg0, 2);
    if (temp_v0 >= 0) {
        if ((func_80049668(temp_v0, arg1, arg2) == arg2) && (func_80049668(temp_v0, arg3, arg4) == arg4)) {
            func_80049648(temp_v0);
            return 1;
        }
        
        return 0;
    }
    return 0;
}

s32 func_80031B24(void *arg0) {
    return (((M2C_FIELD(arg0, u8 *, 0xC) - 0x30) * 0xEA60) + ((M2C_FIELD(arg0, u8 *, 0xD) - 0x30) * 0x2710) + ((M2C_FIELD(arg0, u8 *, 0xE) - 0x30) * 0x3E8) + ((M2C_FIELD(arg0, u8 *, 0xF) - 0x30) * 0x64) + ((M2C_FIELD(arg0, u8 *, 0x10) - 0x30) * 0xA)) - 0x30 + M2C_FIELD(arg0, u8 *, 0x11);
}

void func_80031D54(void) {
    M2C_UNK var_a3;
    s32 var_s0;
    s32 var_s1;
    s32 var_v1;
    void *temp_a2;

    func_8003E128(0x20, 0x20, &D_800105FC, 0x7C);
    func_8003E128(0x20, 0x40, &D_80077268, 0x7A);
    var_s0 = 0;
    if (D_8012CFD8 > 0) {
        var_s1 = 0;
        do {
            var_v1 = var_s0;
            if (var_s0 < 0) {
                var_v1 = var_s0 + 7;
            }
            var_a3 = 0xC5;
            temp_a2 = var_s1 + &D_80173194;
            if (D_80173330 == var_s0) {
                var_a3 = 0x78;
            }
            var_s1 += 0x18;
            func_8003E2D4(((var_v1 >> 3) * 0x90) + 0x10 + 0x10, ((var_s0 & 7) * 0x10) + 0x30 + 0x20, temp_a2, var_a3);
            var_s0 += 1;
        } while (var_s0 < D_8012CFD8);
    }
}

void func_80031EC4(void) {
    M2C_UNK var_a3;
    s32 var_s0;
    s32 var_s1;
    s32 var_v1;
    void *temp_a2;

    func_8003E128(0x20, 0x20, &D_80010610, 0x79);
    func_8003E128(0x20, 0x40, &D_80077268, 0x7A);
    func_8003E128(0x20, 0x50, &D_80010624, 0x7B);
    var_s0 = 0;
    if (D_8012CFD8 > 0) {
        var_s1 = 0;
        do {
            var_v1 = var_s0;
            if (var_s0 < 0) {
                var_v1 = var_s0 + 7;
            }
            var_a3 = 0xC5;
            temp_a2 = var_s1 + &D_80173194;
            if (D_80173330 == var_s0) {
                var_a3 = 0x78;
            }
            var_s1 += 0x18;
            func_8003E2D4(((var_v1 >> 3) * 0x90) + 0x10 + 0x10, ((var_s0 & 7) * 0x10) + 0x40 + 0x20, temp_a2, var_a3);
            var_s0 += 1;
        } while (var_s0 < D_8012CFD8);
    }
}

s32 func_80032948(void *arg0, M2C_UNK arg1) {
    s32 temp_v0;
    s32 var_s0;
    u32 temp_s2;

    var_s0 = 0;
    temp_s2 = (u32) (M2C_FIELD(arg0, s32 *, 4) + 0x7FF) >> 0xB;
loop_1:
    func_8002E528();
    func_8002E490();
    func_80051E30(2, arg0, 0);
    func_8002E528();
    func_8002E490();
    func_80051F8C(temp_s2, arg1, 0x80);
    do {
        func_8002E528();
        func_8002E490();
        temp_v0 = func_80051CAC(1, 0);
    } while (temp_v0 > 0);
    if (temp_v0 != 0) {
        var_s0 += 1;
        if (var_s0 < 0xA) {
            goto loop_1;
        }
    }
    func_8002E528();
    func_8002E490();
    return M2C_FIELD(arg0, s32 *, 4);
}

void func_80032A54(void) {
    M2C_UNK sp10;
    M2C_UNK sp24;
    M2C_UNK sp38;
    M2C_UNK sp4C;
    M2C_UNK sp60;
    M2C_UNK sp74;
    M2C_UNK sp88;
    M2C_UNK sp9C;
    M2C_UNK *temp_s0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;

    if (func_80053788(&sp10, D_800747C8) == 0) {
        func_80032A24();
    }
    if (func_80053788(&sp24, D_800747CC) == 0) {
        func_80032A24();
    }
    if (func_80053788(&sp38, D_800747D0) == 0) {
        func_80032A24();
    }
    if (func_80053788(&sp4C, D_800747D4) == 0) {
        func_80032A24();
    }
    if (func_80053788(&sp60, D_800747D8) == 0) {
        func_80032A24();
    }
    if (func_80053788(&sp74, D_800747BC) == 0) {
        func_80032A24();
    }
    if (func_80053788(&sp88, D_800747C0) == 0) {
        func_80032A24();
    }
    if (func_80053788(&sp9C, D_800747C4) == 0) {
        func_80032A24();
    }
    D_8012CFB0 = 0;
    func_8002E5E8();
    D_8007B1BC = 0;
    func_80032948(&sp60, &D_8007C520);
    func_80037D38(&D_8007C520);
    D_8012CFB0 = 1;
    D_8007B1BC = 0;
    func_80032948(&sp10, &D_8007C520);
    func_80037D38(&D_8007C520);
    D_8007B1BC = 1;
    func_80032948(&sp24, &D_8007C520);
    func_80037D38(&D_8007C520);
    func_80037C74(0);
    D_8007B1BC = 2;
    func_80032948(&sp38, &D_8007C520);
    func_80037D38(&D_8007C520);
    func_80037C74(1);
    D_8007B1BC = 3;
    func_80032948(&sp4C, &D_8007C520);
    func_80037D38(&D_8007C520);
    func_8003776C();
    D_8007B1BC = 4;
    temp_v0 = func_80032948(&sp74, &D_8007C520);
    temp_v0_2 = temp_v0 + 3;
    var_v0 = temp_v0_2 >> 2;
    if (temp_v0_2 < 0) {
        var_v0 = (s32) (temp_v0 + 6) >> 2;
    }
    func_800125B4(&D_8007C520);
    D_8007B1BC = 5;
    temp_s0 = (var_v0 * 4) + &D_8007C520;
    func_80032948(&sp88, temp_s0);
    D_80173318 = func_80012670(temp_s0);
    D_8007B1BC = 6;
    func_80032948(&sp9C, &D_8007B200);
    func_80015CD4(&D_8007B200);
}

void func_80032E30(void *arg0) {
    s32 temp_v0;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;

    if (D_801D7E78 != 0) {
        temp_v0 = D_8012D078 - 1;
        D_8012D078 = temp_v0;
        if (temp_v0 <= 0) {
            D_801D7E78 = 0;
        }
        var_v0 = M2C_FIELD(&D_801E9180, s32 *, 0);
        if (var_v0 < 0) {
            var_v0 += 7;
        }
        M2C_FIELD(arg0, s32 *, 0x10) = (s32) ((var_v0 >> 3) + M2C_FIELD(arg0, s32 *, 0x10));
        var_v0_2 = M2C_FIELD(&D_801E9180, s32 *, 8);
        if (var_v0_2 < 0) {
            var_v0_2 += 7;
        }
        M2C_FIELD(arg0, s32 *, 0x18) = (s32) ((var_v0_2 >> 3) + M2C_FIELD(arg0, s32 *, 0x18));
        var_v1 = M2C_FIELD(&D_801E9180, s32 *, 0) * 7;
        if (var_v1 < 0) {
            var_v1 += 7;
        }
        M2C_FIELD(&D_801E9180, s32 *, 0) = (s32) (var_v1 >> 3);
        M2C_FIELD(&D_801E9180, s32 *, 8) = (s32) ((s32) (M2C_FIELD(&D_801E9180, s32 *, 8) * 7) / 8);
    }
}

void func_8003336C(void *arg0) {
    s32 temp_a0;
    s32 temp_lo;
    s32 temp_v0;
    s32 temp_v0_2;

    if (M2C_FIELD(arg0, s16 *, 0xB8) != 0) {
        temp_a0 = M2C_FIELD(arg0, s32 *, 0x20);
        temp_v0 = M2C_FIELD(arg0, s32 *, 0xC0) + M2C_FIELD(arg0, s32 *, 0xBC);
        M2C_FIELD(arg0, s32 *, 0x20) = temp_v0;
        D_8012CFA8 = temp_v0 - temp_a0;
        return;
    }
    temp_v0_2 = func_80033218(arg0);
    if (temp_v0_2 != 0) {
        M2C_FIELD(arg0, s16 *, 0xB8) = 1;
        temp_lo = (s32) -M2C_FIELD(arg0, s32 *, 0xA0) / (s32) *(&D_800747E0 + (temp_v0_2 * 4));
        M2C_FIELD(arg0, s16 *, 0xBA) = 0;
        M2C_FIELD(arg0, s32 *, 0xBC) = temp_lo;
        M2C_FIELD(arg0, s32 *, 0xC0) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) - temp_lo);
    }
}

void func_80033438(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_v0;

    if (D_801D9060 < 2) {
        D_8012CF80 = 0;
        return;
    }
    if (D_8012CD20 < 0x1E) {
        temp_v0 = D_8012CF80 + 1;
        D_8012CF80 = temp_v0;
        var_v0 = 0x10;
        if (temp_v0 >= 0x11) {
            goto block_13;
        }
    } else if ((M2C_FIELD(arg0, s16 *, 0xCA) >= 0x81) && (M2C_FIELD(arg0, s32 *, 0xA0) >= 0x51)) {
        temp_v0_2 = D_8012CF80 + 1;
        D_8012CF80 = temp_v0_2;
        var_v0 = 8;
        if (temp_v0_2 >= 9) {
            goto block_13;
        }
    } else if (M2C_FIELD((arg0 + 0x58), s16 *, 0x70) >= 0x81) {
        temp_v0_3 = D_8012CF80 - 2;
        D_8012CF80 = temp_v0_3;
        var_v0 = -0x10;
        if (temp_v0_3 < -0x10) {
            goto block_13;
        }
    } else {
        var_v0 = (s32) (D_8012CF80 * 3) / 4;
block_13:
        D_8012CF80 = var_v0;
    }
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (M2C_FIELD(arg0, s32 *, 0x20) + D_8012CF80);
}

s32 func_80033FBC(s32 arg0, void *arg1, M2C_UNK arg2, M2C_UNK arg3) {
    s32 temp_s0;

    if (M2C_FIELD(arg1, s32 *, 0x24) != 0) {
        func_80043738();
        temp_s0 = func_800437AC(arg0, arg1, arg2, arg3);
        func_80043738();
        return temp_s0;
    }
    return func_800437AC(arg0, arg1, arg2, arg3);
}

void func_8003757C(s32 arg0) {
    s32 sp10;
    s32 *var_a0;
    s32 *var_a0_2;
    s32 *var_s0;
    s32 *var_s0_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s3;
    s32 var_s4;
    s32 var_v1;
    s32 var_v1_2;
    u8 *var_s1;
    u8 *var_s2;
    u8 temp_a0;
    u8 temp_s6;
    u8 temp_v1;

    var_s4 = 0;
    var_s1 = &D_801D7D10;
    var_s3 = 0;
    var_s2 = &D_801D7D10 - 0x100;
    do {
        D_8007727E = var_s4 + 0x100;
        temp_a0 = *var_s1;
        temp_v1 = *var_s2;
        temp_s6 = (3 - temp_a0) - temp_v1;
        if (temp_v1 == arg0) {
            func_800458B8(&D_8007727E - 2, &sp10);
            func_80045790(0);
            var_s0 = var_s3 + &D_801734E0;
            func_80045854(&D_8007727E - 2, var_s0);
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
            *var_s2 = temp_s6;
        } else if (temp_a0 == arg0) {
            func_800458B8(&D_8007727E - 2, &sp10);
            func_80045790(0);
            var_s0_2 = var_s3 + &D_801A34E0;
            func_80045854(&D_8007727E - 2, var_s0_2);
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
            *var_s1 = temp_s6;
        }
        var_s1 += 1;
        var_s3 += 0x300;
        var_s4 += 1;
        var_s2 += 1;
    } while (var_s4 < 0x100);
}

void func_800379C0(void) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;

    if (D_801D9058 >= 0) {
        if (D_801D9058 == 0) {
            temp_v0 = D_801D9020;
            var_s0 = 0;
            if (temp_v0 > 0) {
loop_3:
                if (VSync(1) < 0x1D6) {
                    func_80037850((D_801D9058 << 8) + D_801E90B8 + var_s0);
                    var_s0 += 1;
                    if (var_s0 < D_801D9020) {
                        goto loop_3;
                    }
                }
            }
            D_801E91E8 -= temp_v0 - var_s0;
        } else {
            temp_v0_2 = D_801D9020;
            var_s0 = 0;
            if (temp_v0_2 > 0) {
loop_8:
                if (VSync(1) < 0x1D6) {
                    var_s0 += 1;
                    func_80037850(((D_801D9058 << 8) + D_801E90B8 + D_801D9020) - var_s0);
                    if (var_s0 < D_801D9020) {
                        goto loop_8;
                    }
                }
            }
            D_801E91E8 += temp_v0_2 - var_s0;
        }
        if (D_801D9020 == var_s0) {
            D_801D9058 = -1;
        }
    }
}

void func_80039034(void) {
    M2C_UNK *var_s0;
    s32 *var_v0;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s1;
    s32 var_s1_2;
    s32 var_s1_3;
    s32 var_s2;
    void *var_a0;

    var_v0 = &D_801D8128;
    var_s1 = 7;
    do {
        *var_v0 = 0;
        var_s1 -= 1;
        var_v0 += 0x34;
    } while (var_s1 >= 0);
    D_801D7668 = 0;
    var_s2 = 0;
    var_s0 = &D_80074DBC;
    do {
        var_s1_2 = 0;
loop_4:
        temp_v0 = M2C_FIELD(var_s0, s32 *, 0) - M2C_FIELD(var_s0, s32 *, 0x10);
        temp_v0_2 = M2C_FIELD(var_s0, s32 *, 4) - M2C_FIELD(var_s0, s32 *, 0x14);
        var_s1_2 += 1;
        M2C_FIELD(var_s0, s32 *, 8) = func_80041148(((temp_v0 * temp_v0) + (temp_v0_2 * temp_v0_2)) << 6);
        var_s0 += 0x10;
        if (var_s1_2 < 0xF) {
            goto loop_4;
        }
        var_s1_3 = 0;
        var_a0 = var_s2 + &D_80074DBC + 0xC;
loop_6:
        var_s1_3 += 1;
        M2C_FIELD(var_a0, s32 *, 0) = (s32) (0x100000 / (s32) M2C_FIELD(var_a0, s32 *, -4));
        var_a0 += 0x10;
        if (var_s1_3 < 0xF) {
            goto loop_6;
        }
        var_s2 += 0x100;
        var_s0 = var_s2 + &D_80074DBC;
    } while (var_s2 < 0x200);
}

void func_80039734(void) {
    M2C_UNK *var_a3;
    s32 *var_a2;
    s32 *var_t0;
    s32 temp_v0;
    s32 var_t1;

    var_t0 = &D_801D7F58;
    var_a3 = &D_80074FBC;
    var_t1 = 0;
    var_a2 = &D_801D7F58 + 0x14;
    do {
        *var_t0 = 0;
        M2C_FIELD(var_a2, s32 *, -0x10) = (s32) M2C_FIELD(var_a3, s32 *, 0);
        M2C_FIELD(var_a2, s32 *, -0xC) = (s32) M2C_FIELD(var_a3, s32 *, 4);
        M2C_FIELD(var_a2, s32 *, -8) = (s32) M2C_FIELD(var_a3, s32 *, 8);
        M2C_FIELD(var_a2, s32 *, -4) = (s32) M2C_FIELD(var_a3, s32 *, 0xC);
        temp_v0 = M2C_FIELD(var_a3, s32 *, 0xC);
        M2C_FIELD(var_a2, s32 *, 0) = 0;
        var_t1 += 1;
        var_t0 += 0x38;
        var_a3 += 0x10;
        M2C_FIELD(var_a2, s32 *, 4) = temp_v0;
        var_a2 += 0x38;
    } while (var_t1 < 6);
    D_8012CD28 = 0;
}

s32 func_800397FC(void *arg0) {
    M2C_UNK *var_a2;
    s32 temp_a1;
    s32 temp_t1;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a3;
    s32 var_v0;

    var_a2 = &D_801733E0;
    var_a3 = 0;
    temp_t1 = M2C_FIELD(arg0, s32 *, 4);
loop_1:
    temp_v1 = M2C_FIELD(var_a2, s32 *, 0);
    if (((temp_v1 - 0x30) >= temp_t1) || (temp_t1 >= (temp_v1 + 0x30)) || (temp_v1_2 = M2C_FIELD(var_a2, s32 *, 8), temp_a1 = M2C_FIELD(arg0, s32 *, 0xC), (((temp_v1_2 - 0x30) < temp_a1) == 0)) || (var_v0 = 1, ((temp_a1 < (temp_v1_2 + 0x30)) == 0))) {
        var_a3 += 1;
        var_a2 += 0x10;
        if (var_a3 >= 4) {
            var_v0 = 0;
        } else {
            goto loop_1;
        }
    }
    return var_v0;
}

void func_80039B78(void) {
    M2C_UNK sp10;
    M2C_UNK sp30;
    M2C_UNK *var_s0;
    s32 temp_a2;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;
    s32 var_s1;
    s32 var_s2;
    s32 var_v0;

    var_s2 = 0xC8;
    if (D_801733B8 != 0) {
        var_s2 = 0x64;
    }
    func_80012FE4(0x100);
    var_s1 = 0;
    var_s0 = &D_801D7F5C;
    do {
        temp_v1 = M2C_FIELD(var_s0, s32 *, 8);
        var_v0 = temp_v1 + 0x400;
        if (var_v0 < 0) {
            var_v0 = temp_v1 + 0xBFF;
        }
        temp_a2 = M2C_FIELD(var_s0, s32 *, 0);
        var_a1 = temp_a2 + 0x400;
        if (var_a1 < 0) {
            var_a1 = temp_a2 + 0xBFF;
        }
        if ((1 << (var_a1 >> 0xB)) & *(((var_v0 >> 0xB) * 4) + &D_801D82D8)) {
            func_8001865C(&sp10, M2C_FIELD(var_s0, s32 *, 0x10), temp_a2);
            func_800185F0(&sp30, M2C_FIELD(var_s0, s32 *, 0x14));
            func_80042E08(&sp30, &sp10);
            func_80042E08(&D_801E91F0, &sp10);
            func_800129AC(0x1F800060, var_s0, &sp10);
            var_a2 = 1;
            if (var_s2 < D_80173318) {
                var_a2 = var_s2;
            }
            *(s32 *)0x1F800000 = func_8003486C(*(s32 *)0x1F800000, 0x1F800038, var_a2, 0);
        }
        var_s1 += 1;
        var_s0 += 0x38;
    } while (var_s1 < 6);
    func_8001315C();
}

void func_80039DB0(s8 arg0, s8 arg1, s8 arg2, s8 arg3) {
    D_801D75F0 = arg0;
    D_801D75F1 = arg1;
    D_801D75F2 = arg2;
    D_801D75F3 = arg3;
    func_800520CC(&D_801D75F0);
}

void func_80039DF4(void) {
    s32 var_t0;
    u8 *var_a1;
    u8 *var_a2;
    u8 *var_a3;
    u8 temp_a0;
    u8 temp_a0_2;
    u8 temp_a0_3;

    var_t0 = 2;
    if (D_801D9048 >= 2) {
        var_a3 = &D_801D3500 + 8;
        var_a2 = &D_801D3500 + 9;
        var_a1 = &D_801D3500 + 0xA;
        do {
            temp_a0 = *var_a1;
            *var_a1 = (((s32) temp_a0 >> 4) * 0xA) + (temp_a0 & 0xF);
            temp_a0_2 = *var_a2;
            *var_a2 = (((s32) temp_a0_2 >> 4) * 0xA) + (temp_a0_2 & 0xF);
            temp_a0_3 = *var_a3;
            var_t0 += 1;
            var_a1 += 4;
            *var_a3 = (((s32) temp_a0_3 >> 4) * 0xA) + (temp_a0_3 & 0xF);
            var_a2 += 4;
            var_a3 += 4;
        } while (D_801D9048 >= var_t0);
    }
}

void func_80039EB0(void) {
    s32 var_t0;
    u8 *var_a0;
    u8 *var_a1;
    u8 *var_a2;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;

    var_t0 = 2;
    if (D_801D9048 >= 2) {
        var_a2 = &D_801D3500 + 8;
        var_a1 = &D_801D3500 + 9;
        var_a0 = &D_801D3500 + 0xA;
        do {
            temp_v0 = *var_a0;
            *var_a0 = (((s32) temp_v0 / 10) * 0x10) + ((s32) temp_v0 % 10);
            temp_v0_2 = *var_a1;
            *var_a1 = (((s32) temp_v0_2 / 10) * 0x10) + ((s32) temp_v0_2 % 10);
            temp_v0_3 = *var_a2;
            var_t0 += 1;
            var_a0 += 4;
            *var_a2 = (((s32) temp_v0_3 / 10) * 0x10) + ((s32) temp_v0_3 % 10);
            var_a1 += 4;
            var_a2 += 4;
        } while (D_801D9048 >= var_t0);
    }
}

void func_80039FD4(void) {
    s32 var_a0;
    s32 var_a3;
    s32 var_v1;
    u8 *var_a2;
    void *var_a1;

    if (D_80173428 == 1) {
        D_801D9048 = func_80054264(1, &D_801D3500);
        func_80039DF4();
        var_a3 = 2;
        if (D_801D9048 >= 2) {
            var_a2 = &D_801D3500 + 0xA;
            var_a0 = 8;
            var_a1 = &D_801D3500 + 8;
            do {
                var_v1 = *var_a2 - 0xA;
                if (var_v1 < 0) {
                    if (*(&D_801D3501 + var_a0) == 0) {
                        M2C_FIELD(var_a1, s8 *, 0) = (s8) (*(&D_801D3500 + var_a0) - 1);
                        *(&D_801D3501 + var_a0) = 0x3B;
                        var_v1 += 0x4B;
                    } else {
                        M2C_FIELD(var_a1, s8 *, 1) = (s8) (*(&D_801D3501 + var_a0) - 1);
                        var_v1 += 0x4B;
                    }
                }
                *var_a2 = (u8) var_v1;
                var_a2 += 4;
                var_a0 += 4;
                var_a3 += 1;
                var_a1 += 4;
            } while (D_801D9048 >= var_a3);
        }
        func_80039EB0();
        D_80173428 = 0;
        return;
    }
    switch (D_800772A0) {
    case 0:
        func_8003A2C8(1);
        break;
    case 1:
        func_8003A5A4(1);
        break;
    case 2:
        func_8003A600(1);
        break;
    case 3:
        func_8003A65C(1);
        break;
    }
    func_80051C6C(1, 0);
}

void func_8003A258(void) {
    s16 temp_a0;
    s16 temp_a0_2;

    temp_a0 = *(&D_800750E4 + (D_801E9098 * 2));
    func_80039D88(temp_a0, 0, temp_a0, 0);
    temp_a0_2 = *((D_801E9098 * 2) + &D_800750E4);
    func_80039DB0(temp_a0_2, 0, temp_a0_2, 0);
}

s32 func_8003A678(s32 arg0, M2C_UNK arg1) {
    s16 temp_v0;
    s16 temp_v0_2;
    s32 var_v0;
    s32 var_v1;

    func_8004D9B4(&D_8012CDF0, 1, 1);
    func_8004DB58(0x1000);
    func_8004DC34();
    temp_v0 = func_8004BA7C(arg0, -1);
    D_801D34F0 = temp_v0;
    var_v0 = -1;
    if (temp_v0 != -1) {
        temp_v0_2 = func_8004BE7C(arg1, temp_v0);
        D_801D34F0 = temp_v0_2;
        var_v0 = -1;
        if (temp_v0_2 != -1) {
            func_8004C0B8(1);
            func_8004DF6C(0x3FFF, 0x3FFF);
            var_v1 = 0;
            do {
                *(&D_801D7670 + var_v1) = 0;
                var_v1 += 0xA;
                var_v0 = 0;
            } while (var_v1 < 0xF0);
        }
    }
    return var_v0;
}

void func_8003A748(void) {
    s16 temp_v0_2;
    s32 temp_s0;
    s32 temp_v0_3;
    u16 temp_a3;
    u16 temp_v0;

    func_8004E178();
    temp_s0 = D_8012D018 * 0xA;
    if (*(&D_801D7670 + temp_s0) == 2) {
        temp_v0 = D_8012D000 + 1;
        D_8012D000 = temp_v0;
        if ((s16) temp_v0 >= 3) {
            temp_a3 = *(&D_801D7676 + temp_s0);
            temp_v0_2 = func_8004C380(D_801D34F0, *(&D_801D7672 + temp_s0), *(&D_801D7674 + temp_s0), (s32) (temp_a3 << 0x10) >> 0x17, temp_a3 & 0x7F, *(&D_80075100 + (*(&D_801D7672 + temp_s0) * 0xC)) - 0x32, *(&D_80075102 + (*(&D_801D7672 + temp_s0) * 0xC)) - 0x32);
            if (temp_v0_2 >= 0) {
                temp_v0_3 = temp_v0_2 * 0xA;
                *(&D_801D7672 + temp_v0_3) = *(&D_801D7672 + temp_s0);
                *(&D_801D7674 + temp_v0_3) = *(&D_801D7674 + temp_s0);
                *(&D_801D7676 + temp_v0_3) = *(&D_801D7676 + temp_s0);
                *(&D_801D7670 + temp_v0_3) = 1;
                *(&D_801D7678 + temp_v0_3) = *(&D_801D7678 + temp_s0);
                D_8012D01A = temp_v0_2;
            }
            *(&D_801D7670 + temp_s0) = 1;
        }
    }
}

void func_8003AE10(s16 arg0) {
    s32 temp_s0;

    if ((u32) (arg0 & 0xFFFF) < 0x18U) {
        temp_s0 = arg0 * 0xA;
        if (*(&D_801D7670 + temp_s0) != 0) {
            func_8004C74C(arg0, D_801D34F0, *(&D_801D7672 + temp_s0), *(&D_801D7674 + temp_s0), (s32) (*(&D_801D7676 + temp_s0) << 0x10) >> 0x17);
            *(&D_801D7670 + temp_s0) = 0;
        }
    }
}

void func_8003AF8C(void) {
    s32 var_s0;
    s32 var_s1;
    u16 temp_a3;

    if (D_800772FC == 0) {
        D_800772FC = 1;
        var_s1 = 0;
        var_s0 = 0;
        do {
            if (*(&D_801D7670 + var_s0) != 0) {
                temp_a3 = *(&D_801D7676 + var_s0);
                func_8004C8AC(var_s1, D_801D34F0, *(&D_801D7672 + var_s0), (s32) (temp_a3 << 0x10) >> 0x17, temp_a3 & 0x7F, 0, 0);
            }
            var_s1 += 1;
            var_s0 += 0xA;
        } while (var_s1 < 0x18);
    }
}

s16 func_8003B1EC(s16 arg0, s16 arg1, s16 arg2) {
    s16 var_v0;

    var_v0 = D_800772FC;
    if (var_v0 == 0) {
        var_v0 = (u32) (arg0 & 0xFFFF) < 0x18U;
        if (var_v0 != 0) {
            var_v0 = *(&D_801D7670 + (arg0 * 0xA));
            if (var_v0 != 0) {
                var_v0 = func_8004D328(arg0, arg1, arg2);
            }
        }
    }
    return var_v0;
}

void func_8003B51C(void) {
    u16 temp_v0;

    if (D_80173310 == 2) {
        func_80045750(1);
    }
    if (D_801D77D0 == 0) {
        temp_v0 = D_80173310;
        D_80173310 = temp_v0 + 1;
        if (temp_v0 >= 0xD3U) {
            D_801D34F8 = 0x1B;
        }
    }
    func_8003B388(D_80173310);
}

void func_8003B960(void) {
    s32 temp_v0;
    s32 var_a1;
    s32 var_t0;
    s32 var_v0;
    s32 var_v1;
    u8 *var_a2_2;
    u8 temp_v0_2;
    void *var_a2;
    void *var_a3;

    var_t0 = 0;
    var_v1 = 0;
loop_1:
    var_v0 = var_t0 < 5;
    if (D_801D77C8 >= *(&D_8007C48C + var_v1)) {
        var_t0 += 1;
        var_v1 += 0xC;
        if (var_t0 >= 6) {
            var_v0 = var_t0 < 5;
        } else {
            goto loop_1;
        }
    }
    if (var_v0 != 0) {
        var_a2 = &D_8007C488 + 0x3C;
        var_a3 = &D_8007C488 + 0x30;
        do {
            M2C_FIELD(var_a2, s32 *, 0) = (s32) M2C_FIELD(var_a3, s32 *, 0);
            M2C_FIELD(var_a2, s32 *, 4) = (s32) M2C_FIELD(var_a3, s32 *, 4);
            M2C_FIELD(var_a2, s32 *, 8) = (s32) M2C_FIELD(var_a3, s32 *, 8);
            var_a2 -= 0xC;
            var_a3 -= 0xC;
        } while ((s32) ((var_t0 * 0xC) + &D_8007C488) < (s32) var_a2);
    }
    var_a1 = 0;
    temp_v0 = var_t0 * 0xC;
    var_a2_2 = temp_v0 + &D_8007C488;
    *(&D_8007C48C + temp_v0) = D_801D77C8;
    do {
        temp_v0_2 = M2C_FIELD((*(&D_801D7770 + var_a1) + D_80077300), u8 *, -0x41);
        var_a1 += 1;
        *var_a2_2 = temp_v0_2;
        var_a2_2 += 1;
    } while (var_a1 < 3);
    *(&D_8007C490 + (var_t0 * 0xC)) = (s32) D_8007C25A;
}

void func_8003DC28(void) {
    func_80028578(0x20, 0xC8, &D_80010800, 0x7F);
    if (D_801D35AE & 0x800) {
        D_801E9178 = 0;
    }
    func_80028578(0x78, 0x20, &D_80010948, 0x64);
}

void func_8003DE90(void) {
    M2C_UNK *var_a2;
    M2C_UNK var_a3;

    if (D_801D7E28 == 0) {
        D_800775D4 = func_8002B238();
        D_801D7E28 = 1;
    }
    func_80028578(0x20, 0xC8, &D_80010800, 0x7F);
    if (D_801D35AE & 0x800) {
        D_801E9178 = 0;
        D_801D7E28 = 0;
    }
    func_80028578(0x58, 0x20, &D_80010968, 0x64);
    var_a2 = &D_80010988;
    var_a3 = 0x7F;
    if (D_800775D4 != 0) {
        var_a2 = &D_8001097C;
    }
    if (D_800775D4 != 0) {
        var_a3 = 0x64;
    }
    func_80028578(0x60, 0x30, var_a2, var_a3);
}

void func_8003EE20(void) {
    func_8003AEC0();
    D_801D3540 = -1;
    D_801D3546 = -1;
    D_801D354C = -1;
    D_801D3552 = -1;
    D_801D3558 = -1;
    D_801D355E = -1;
    D_801D3564 = -1;
    D_801D356A = -1;
    D_801D3570 = -1;
    D_801D3576 = -1;
    D_801D357C = -1;
    D_801D3582 = -1;
    D_801D3544 = 0x1E00;
    D_801D354A = 0x1E00;
    D_801D3550 = 0x1E00;
    D_801D3556 = 0x1E00;
    D_801D355C = 0x1E00;
    D_801D3562 = 0x1E00;
    D_801D356E = 0x1E00;
    D_801D3574 = 0x1E00;
    D_801D357A = 0x1E00;
    D_801D3580 = 0x1E00;
    D_801D3586 = 0x1E00;
}

void func_8003F0C0(void *arg0) {
    s16 temp_a0;
    s16 var_a1;
    s16 var_s0;
    s32 var_v0;

    temp_a0 = M2C_FIELD(arg0, s16 *, 0);
    if (temp_a0 >= 0) {
        if (D_801D77D0 != 0) {
            func_8003B1EC(temp_a0, 0, 0);
            return;
        }
        var_s0 = M2C_FIELD(arg0, s16 *, 2);
        var_v0 = var_s0 < 0x80;
        if (var_s0 < 0) {
            var_s0 = 0;
            var_v0 = 0 < 0x80;
        }
        var_a1 = var_s0;
        if (var_v0 == 0) {
            var_s0 = 0x7F;
            var_a1 = 0x7F;
        }
        func_8003B1EC(temp_a0, var_a1, var_s0);
        if (var_s0 > 0) {
            func_8003B118(M2C_FIELD(arg0, s16 *, 0), M2C_FIELD(arg0, s16 *, 4));
        }
    }
}

void func_8003F33C(s16 *arg0) {
    M2C_UNK *var_t2;
    s16 *var_t1;
    s16 var_v0;
    s32 var_t0;
    void *var_a2;
    void *var_a3;

    var_t1 = arg0;
    var_t2 = &D_8007556C;
    var_t0 = 0;
    var_a3 = &D_8007556C + 0x10;
    var_a2 = var_t1 + 8;
    var_v0 = 0 < 0xC;
    do {
        *var_t1 = var_v0;
        if (var_v0 != 0) {
            M2C_FIELD(var_a2, s32 *, 0x50) = 1;
            M2C_FIELD(var_a2, s32 *, 8) = (s32) M2C_FIELD(var_t2, s32 *, 0);
            M2C_FIELD(var_a2, s32 *, 0xC) = (s32) M2C_FIELD(var_t2, s32 *, 4);
            M2C_FIELD(var_a2, s32 *, 0x10) = (s32) M2C_FIELD(var_t2, s32 *, 8);
            M2C_FIELD(var_a2, s32 *, 0x14) = (s32) M2C_FIELD(var_t2, s32 *, 0xC);
            M2C_FIELD(var_a2, s32 *, 0x18) = 0;
            M2C_FIELD(var_a2, s32 *, 0x20) = 0;
            M2C_FIELD(var_a2, s32 *, 0x1C) = (s32) M2C_FIELD(var_a3, s32 *, -4);
            M2C_FIELD(var_a2, s32 *, 0x38) = (s32) M2C_FIELD(var_a2, s32 *, 0xC);
            M2C_FIELD(var_a2, s32 *, 0) = 0x2000;
            M2C_FIELD(var_a2, u16 *, -6) = (u16) M2C_FIELD(var_a3, u16 *, 0);
        }
        var_t0 += 1;
        var_a2 += 0x114;
        var_t1 += 0x114;
        var_a3 += 0x14;
        var_v0 = var_t0 < 0xC;
        var_t2 += 0x14;
    } while (var_v0 != 0);
}

void func_80040690(s32 arg0) {
    M2C_UNK sp18;
    s32 sp1C;
    s32 var_at;
    s32 var_at_2;
    s32 var_at_3;

    if (arg0 >= 0) {
        var_at = arg0 < 0x400;
        if (arg0 < 0x400) {
            func_8004059C(arg0, &sp1C, &sp18);
        } else {
            goto block_4;
        }
    } else {
        var_at = arg0 < 0x400;
block_4:
        if (var_at == 0) {
            var_at_2 = arg0 < 0x800;
            if (arg0 < 0x800) {
                func_8004059C(0x7FF - arg0, &sp1C, &sp18);
            } else {
                goto block_8;
            }
        } else {
            var_at_2 = arg0 < 0x800;
block_8:
            if (var_at_2 == 0) {
                var_at_3 = arg0 < 0xC00;
                if (arg0 < 0xC00) {
                    func_8004059C(arg0 - 0x800, &sp1C, &sp18);
                } else {
                    goto block_12;
                }
            } else {
                var_at_3 = arg0 < 0xC00;
block_12:
                if (var_at_3 == 0) {
                    if (arg0 < 0x1000) {
                        func_8004059C(0xFFF - arg0, &sp1C, &sp18);
                    }
                }
            }
        }
    }
}

s32 func_8004095C(s32 arg0) {
    s32 sp1C;
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a1;

    temp_v1 = 0x20 - func_80044078(arg0, arg0);
    temp_a0 = temp_v1 - 0xC;
    if (temp_v1 >= 0xC) {
        var_a1 = arg0 >> temp_a0;
    } else {
        var_a1 = arg0 << -temp_a0;
    }
    sp1C = temp_a0;
    return func_800408CC(var_a1, var_a1, temp_a0) + (temp_a0 * D_80075938);
}

s32 func_80041438(s32 *arg3) {
    M2C_UNK sp3C;
    s32 *var_s0;
    s32 temp_a0;
    s32 temp_v0;
    s32 var_s1;

    temp_v0 = func_80041528(arg3);
    var_s1 = 0;
    if (temp_v0 > 0) {
        var_s0 = arg3;
        do {
            temp_a0 = *var_s0;
            func_80043B08(temp_a0, temp_a0 + 0x18, temp_a0 + 0x14, &sp3C);
            var_s1 += 1;
            var_s0 += 4;
        } while (var_s1 < temp_v0);
    }
    return temp_v0;
}

s32 func_800414B0(s32 *arg4) {
    M2C_UNK sp44;
    s32 *var_s0;
    s32 temp_a0;
    s32 temp_v0;
    s32 var_s1;

    temp_v0 = func_800416D8(arg4);
    var_s1 = 0;
    if (temp_v0 > 0) {
        var_s0 = arg4;
        do {
            temp_a0 = *var_s0;
            func_80043B08(temp_a0, temp_a0 + 0x18, temp_a0 + 0x14, &sp44);
            var_s1 += 1;
            var_s0 += 4;
        } while (var_s1 < temp_v0);
    }
    return temp_v0;
}

void func_80042468(void *arg2, s32 arg3, s32 arg4) {
    M2C_UNK sp20;
    s32 temp_v0;
    s32 var_a3;

    if (arg4 == 0) {
        var_a3 = 0;
    } else {
        var_a3 = (s32) (arg3 << 0xC) / arg4;
    }
    func_80040DC8(0x1000 - var_a3, var_a3, arg2);
    func_80043B98(arg2, arg2 + 8, &sp20);
    temp_v0 = M2C_FIELD(arg2, s32 *, 0x10);
    M2C_FIELD(arg2, s32 *, 0x24) = (s32) ((s32) (temp_v0 * D_80077730) >> 0xC);
    M2C_FIELD(arg2, s32 *, 0x28) = (s32) ((s32) (temp_v0 * D_80077738) >> 0xC);
}

void *func_80043204(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) M2C_FIELD(arg1, s32 *, 8);
    return arg0;
}

void *func_80043228(void *arg0, void *arg1) {
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t0_3;
    s32 temp_t0_4;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t5;

    temp_t0 = M2C_FIELD(arg0, s32 *, 0);
    temp_t3 = M2C_FIELD(arg1, s32 *, 0);
    temp_t4 = M2C_FIELD(arg1, s32 *, 4);
    temp_t5 = M2C_FIELD(arg1, s32 *, 8);
    temp_t0_2 = M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((((s32) ((s16) (temp_t0 & 0xFFFF) * temp_t3) >> 0xC) & 0xFFFF) | (((s32) ((temp_t0 >> 0x10) * temp_t4) >> 0xC) << 0x10));
    temp_t0_3 = M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 4) = (s32) ((((s32) ((s16) (temp_t0_2 & 0xFFFF) * temp_t5) >> 0xC) & 0xFFFF) | (((s32) ((temp_t0_2 >> 0x10) * temp_t3) >> 0xC) << 0x10));
    temp_t0_4 = M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(arg0, s32 *, 8) = (s32) ((((s32) ((s16) (temp_t0_3 & 0xFFFF) * temp_t4) >> 0xC) & 0xFFFF) | (((s32) ((temp_t0_3 >> 0x10) * temp_t5) >> 0xC) << 0x10));
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) ((((s32) ((s16) (temp_t0_4 & 0xFFFF) * temp_t3) >> 0xC) & 0xFFFF) | (((s32) ((temp_t0_4 >> 0x10) * temp_t4) >> 0xC) << 0x10));
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) ((s32) ((s16) (M2C_FIELD(arg0, s32 *, 0x10) & 0xFFFF) * temp_t5) >> 0xC);
    return arg0;
}

void *func_8004334C(void *arg0, void *arg1) {
    s32 temp_t0;
    s32 temp_t0_2;
    s32 temp_t0_3;
    s32 temp_t0_4;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t5;

    temp_t0 = M2C_FIELD(arg0, s32 *, 0);
    temp_t3 = M2C_FIELD(arg1, s32 *, 0);
    temp_t4 = M2C_FIELD(arg1, s32 *, 4);
    temp_t5 = M2C_FIELD(arg1, s32 *, 8);
    temp_t0_2 = M2C_FIELD(arg0, s32 *, 4);
    M2C_FIELD(arg0, s32 *, 0) = (s32) ((((s32) ((s16) (temp_t0 & 0xFFFF) * temp_t3) >> 0xC) & 0xFFFF) | (((s32) ((temp_t0 >> 0x10) * temp_t3) >> 0xC) << 0x10));
    temp_t0_3 = M2C_FIELD(arg0, s32 *, 8);
    M2C_FIELD(arg0, s32 *, 4) = (s32) ((((s32) ((s16) (temp_t0_2 & 0xFFFF) * temp_t3) >> 0xC) & 0xFFFF) | (((s32) ((temp_t0_2 >> 0x10) * temp_t4) >> 0xC) << 0x10));
    temp_t0_4 = M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(arg0, s32 *, 8) = (s32) ((((s32) ((s16) (temp_t0_3 & 0xFFFF) * temp_t4) >> 0xC) & 0xFFFF) | (((s32) ((temp_t0_3 >> 0x10) * temp_t4) >> 0xC) << 0x10));
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) ((((s32) ((s16) (temp_t0_4 & 0xFFFF) * temp_t5) >> 0xC) & 0xFFFF) | (((s32) ((temp_t0_4 >> 0x10) * temp_t5) >> 0xC) << 0x10));
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) ((s32) ((s16) (M2C_FIELD(arg0, s32 *, 0x10) & 0xFFFF) * temp_t5) >> 0xC);
    return arg0;
}

void *func_80044568(void *arg0, void *arg1) {
    M2C_FIELD(arg1, s16 *, 0) = (s16) M2C_FIELD(arg0, s16 *, 0);
    M2C_FIELD(arg1, s16 *, 2) = (s16) M2C_FIELD(arg0, s16 *, 6);
    M2C_FIELD(arg1, s16 *, 4) = (s16) M2C_FIELD(arg0, s16 *, 0xC);
    M2C_FIELD(arg1, s16 *, 6) = (s16) M2C_FIELD(arg0, s16 *, 2);
    M2C_FIELD(arg1, s16 *, 8) = (s16) M2C_FIELD(arg0, s16 *, 8);
    M2C_FIELD(arg1, s16 *, 0xA) = (s16) M2C_FIELD(arg0, s16 *, 0xE);
    M2C_FIELD(arg1, s16 *, 0xC) = (s16) M2C_FIELD(arg0, s16 *, 4);
    M2C_FIELD(arg1, s16 *, 0xE) = (s16) M2C_FIELD(arg0, s16 *, 0xA);
    M2C_FIELD(arg1, s16 *, 0x10) = (s16) M2C_FIELD(arg0, s16 *, 0x10);
    return arg1;
}

void func_80044F04(s32 arg0, s32 arg1) {
    func_8003FCC0((s32) (arg0 * -0x40) / arg1);
    func_8003FCCC(0x01400000);
}

s32 func_80045334(void *arg0, M2C_UNK arg9) {
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 temp_a2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    void **var_a0;
    void **var_a1;

    sp14 = M2C_FIELD(arg0, s16 *, 0) - 0x1000;
    var_v0_2 = 0;
    sp18 = (s32) M2C_FIELD(arg0, s16 *, 2);
    var_a1 = &arg0;
    sp1C = (s32) M2C_FIELD(arg0, s16 *, 4);
    sp20 = (s32) M2C_FIELD(arg0, s16 *, 6);
    sp24 = M2C_FIELD(arg0, s16 *, 8) - 0x1000;
    sp28 = (s32) M2C_FIELD(arg0, s16 *, 0xA);
    sp2C = (s32) M2C_FIELD(arg0, s16 *, 0xC);
    sp30 = (s32) M2C_FIELD(arg0, s16 *, 0xE);
    sp34 = M2C_FIELD(arg0, s16 *, 0x10) - 0x1000;
    do {
        var_v1 = 0;
        var_a0 = var_a1;
loop_2:
        temp_a2 = M2C_FIELD(var_a0, s32 *, -0x2C);
        if (temp_a2 < 0) {
            M2C_FIELD(var_a0, s32 *, -0x2C) = (s32) -temp_a2;
        }
        var_v1 += 1;
        var_v0_2 += M2C_FIELD(var_a0, s32 *, -0x2C);
        var_a0 += 4;
        if (var_v1 != 3) {
            goto loop_2;
        }
        var_a1 += 0xC;
    } while ((u32) var_a1 < (u32) &arg9);
    var_v0 = 0;
    if (var_v0_2 < 0x14) {
        var_v0 = 1;
    }
    return var_v0;
}

void func_80045418(s32 arg0) {
    func_80049658(arg0 & 0xFFFFFF);
}

s32 func_800455F4(s32 arg0) {
    s32 temp_s0;
    s32 var_a0;
    s32 var_a0_2;

    temp_s0 = D_8007737C;
    D_8007737C = arg0;
    var_a0 = M2C_FIELD(g_gpu_device, s32 (**)(M2C_UNK), 0x30)(8);
    if (D_8007737C != 0) {
        var_a0 |= 0x80;
    }
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(s32), 0x10)(var_a0);
    if (D_80077378 == 2) {
        var_a0_2 = 0x20000504;
        if (D_8007737C != 0) {
            var_a0_2 = 0x20000501;
        }
        M2C_FIELD(g_gpu_device, M2C_UNK (**)(s32), 0x10)(var_a0_2);
    }
    return temp_s0;
}

s32 func_800457C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s3;

    temp_s3 = func_800459C0(&D_80010F20, arg0);
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(s32, s32, M2C_UNK, s32), 8)(M2C_FIELD(g_gpu_device, s32 *, 0xC), arg0, 8, ((arg3 & 0xFF) << 0x10) | ((arg2 & 0xFF) << 8) | (arg1 & 0xFF));
    return temp_s3;
}

s32 *ClearOTagR(s32 *arg0, s32 arg1) {
    s32 *temp_a0;
    s32 *var_a2;
    s32 var_a1;

    var_a1 = arg1 - 1;
    var_a2 = arg0;
    if (var_a1 != 0) {
        do {
            M2C_FIELD(var_a2, s8 *, 3) = 0;
            var_a1 -= 1;
            temp_a0 = var_a2 + 4;
            M2C_FIELD(var_a2, s32 *, 0) = (M2C_FIELD(var_a2, s32 *, 0) & 0xFF000000) | ((s32) temp_a0 & 0xFFFFFF);
            var_a2 = temp_a0;
        } while (var_a1 != 0);
    }
    *var_a2 = 0xFFFFFF;
    return var_a2;
}

s32 func_80045B40(s32 arg0) {
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(), 0x2C)();
    return arg0;
}

void func_80045B78(void *arg0) {
    if (D_80077374 != 0) {
        func_80048CCC(&D_80010F70, arg0);
    }
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(M2C_UNK), 0x3C)(0);
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(void *, u8), 0x14)(arg0 + 4, M2C_FIELD(arg0, u8 *, 3));
}

void DrawOTag(s32 arg0) {
    if (D_80077374 != 0) {
        func_80048ADC(arg0);
        return;
    }
    M2C_FIELD(g_gpu_device, M2C_UNK (**)(s32, s32, M2C_UNK), 4)(M2C_FIELD(g_gpu_device, s32 *, 0x18), arg0, 0);
}

void func_800460DC(void *arg0, M2C_UNK arg1) {
    M2C_FIELD(arg0, s8 *, 3) = 2;
    M2C_FIELD(arg0, s32 *, 4) = func_800465DC(arg1);
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

void func_80046114(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s8 *, 3) = 2;
    M2C_FIELD(arg0, s32 *, 4) = func_800465A0(M2C_FIELD(arg1, u16 *, 0), M2C_FIELD(arg1, u16 *, 2));
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

s16 func_80046660(void *arg0) {
    s16 temp_v0;
    s32 var_v1;

    temp_v0 = D_80077378 < 2;
    if (D_80077378 != 1) {
        if (temp_v0 != 0) {
            if (D_80077378 != 0) {
                return temp_v0;
            }
            return M2C_FIELD(arg0, s16 *, 0);
        }
        if (D_80077378 != 2) {
            return 2;
        }
        if (D_8007737C != 0) {
            var_v1 = (0x400 - ((s16) M2C_FIELD(arg0, s16 *, 4) / 2)) - M2C_FIELD(arg0, s16 *, 0);
        } else {
            var_v1 = (s16) M2C_FIELD(arg0, s16 *, 0) / 2;
        }
        return (s16) var_v1;
    }
    if (D_8007737C != 0) {
        return (0x400 - M2C_FIELD(arg0, s16 *, 4)) - M2C_FIELD(arg0, s16 *, 0);
    }
    return M2C_FIELD(arg0, s16 *, 0);
}

s32 func_800467B4(s32 arg0, s32 arg1) {
    s32 sp10;
    s32 temp_v1;

    sp10 = 0x800000;
    *D_800773B0 &= ~0x800;
    *D_800773B0 |= 0x08000000;
    *D_800773AC = 0;
    *D_800773A4 = arg0 + ((arg1 * 4) - 4);
    *D_800773A8 = arg1;
    *D_800773AC = 0x11000002;
    if (*D_800773AC & 0x01000000) {
loop_1:
        temp_v1 = sp10;
        sp10 = temp_v1 - 1;
        if (temp_v1 == 0) {
            func_80046738(0x01000000, D_800773B0, arg1);
            return -1;
        }
        if (!(*D_800773AC & 0x01000000)) {
            goto block_4;
        }
        goto loop_1;
    }
block_4:
    *D_800773B0 |= 0x800;
    return arg1;
}

void func_80047188(s32 arg0, M2C_UNK arg3) {
    func_80047834((D_800773B4 << 5) + &D_80077A48);
    func_80047210(arg0, (D_800773B4 << 5) + &D_80077A48, arg3);
    D_800773B4 = (D_800773B4 + 1) & 0x3F;
}

void func_80047938(s32 arg0) {
    s32 var_a1;
    u32 var_a2;
    u32 var_a3;

    if (func_80045718() != 0) {
        var_a3 = arg0 & 0xFFFF;
        var_a1 = (var_a3 >> 9) & 3;
        var_a2 = var_a3 >> 7;
    } else {
        var_a3 = arg0 & 0xFFFF;
        var_a1 = (var_a3 >> 7) & 3;
        var_a2 = var_a3 >> 5;
    }
    D_80077370(&D_80010FB8, var_a1, var_a2 & 3, (var_a3 << 6) & 0x7C0);
}

M2C_UNK *func_8004815C(s32 arg0) {
    func_80048198(&D_80078748, &D_800773BC, arg0);
    return &D_80078748;
}

M2C_UNK *func_800489EC(s32 arg0) {
    s32 temp_a2;
    s32 temp_v0;
    s32 var_v0;

    temp_a2 = arg0 & 0xFF;
    if (temp_a2 == 2) {
        return &D_80077408;
    }
    temp_v0 = temp_a2 - 0x20;
    if ((u32) ((arg0 - 0x20) & 0xFF) < 0x60U) {
        var_v0 = temp_v0 >> 2;
        if (temp_v0 < 0) {
            var_v0 = (s32) (temp_a2 - 0x1D) >> 2;
        }
        return *(&D_800768BC + (var_v0 * 4));
    }
    func_80048198(&D_800775E0, &D_8007740C, temp_a2);
    return &D_800775E0;
}

u8 func_80048A80(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_v0;

    temp_v1 = arg0 & 0xFF;
    if (temp_v1 == 2) {
        return 3U;
    }
    temp_v0 = temp_v1 - 0x20;
    if ((u32) ((arg0 - 0x20) & 0xFF) < 0x60U) {
        var_v0 = temp_v0 >> 2;
        if (temp_v0 < 0) {
            var_v0 = (s32) (temp_v1 - 0x1D) >> 2;
        }
        return *(&D_8007691C + var_v0);
    }
    return 0U;
}

void func_80048F80(void) {
    if (D_8007743C == 0) {
        D_8007743C = 1;
        func_80048FC0();
        func_800492B0();
    }
}

void func_8004901C(void) {
    D_8007743C = 0;
    func_80049580();
}

void func_80049044(s32 arg0) {
    func_800491AC(0, arg0);
}

void func_80049068(s32 arg0) {
    func_800491AC(1, arg0);
}

void func_8004908C(s32 arg0) {
    func_800491AC(2, arg0);
}

void func_800490B0(s32 arg0) {
    func_800491AC(3, arg0);
}

void func_800490D4(s32 arg0) {
    func_800491AC(4, arg0);
}

void func_800490F8(s32 arg0) {
    func_800491AC(5, arg0);
}

void func_8004911C(s32 arg0) {
    func_8004922C(0, arg0);
}

void func_80049140(s32 arg0) {
    func_8004922C(2, arg0);
}

void func_80049164(s32 arg0) {
    func_8004922C(9, arg0);
}

void func_80049188(s32 arg0) {
    func_8004922C(0xA, arg0);
}

s32 func_800495DC(s32 arg0) {
    s32 temp_s1;

    temp_s1 = D_80077454;
    if (arg0 != 0) {
        func_80049638();
    } else {
        func_800497D8();
    }
    D_80077454 = arg0;
    return temp_s1;
}

void func_8004986C(s32 arg0) {
    s16 var_s0_2;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_s0;
    s32 var_s0_3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    u8 temp_a0;
    void *temp_a1;

    func_80059014(0);
    D_80077462 = 0;
    D_800775F8 = 0;
    func_80058214(0x20, &D_80079CE8);
    D_800775F0 = 0;
    var_s0 = 0;
    var_v0 = 0 & 0xFFFF;
    do {
        *(&D_80079B20 + var_v0) = 0;
        var_s0 += 1;
        var_v0 = var_s0 & 0xFFFF;
    } while ((u32) (var_s0 & 0xFFFF) < 0x10U);
    temp_a0 = arg0 & 0xFF;
    if (temp_a0 >= 0x18U) {
        D_800775E8 = 0x18;
    } else {
        D_800775E8 = temp_a0;
    }
    var_s0_2 = 0;
    if (D_800775E8 != 0) {
        var_v1 = 0 & 0xFFFF;
        do {
            temp_v0 = var_v1 * 0x18;
            *(&D_800797DA + temp_v0) = 0x18;
            *(&D_800797D8 + temp_v0) = 0xFF;
            *(&D_800797EF + temp_v0) = 0;
            *(&D_800797DC + temp_v0) = 0;
            *(&D_800797DE + temp_v0) = 0;
            *(&D_800797E2 + temp_v0) = 0xFF;
            *(&D_800797E4 + temp_v0) = 0;
            *(&D_800797E6 + temp_v0) = 0;
            *(&D_800797E8 + temp_v0) = 0xFF;
            temp_a1 = (((var_v1 * 8) & 0xFFFF) * 2) + D_8007745C;
            M2C_FIELD(temp_a1, s16 *, 0) = 0;
            M2C_FIELD(temp_a1, s16 *, 2) = 0;
            M2C_FIELD(temp_a1, s16 *, 6) = 0x200;
            M2C_FIELD(temp_a1, s16 *, 4) = 0x1000;
            M2C_FIELD(temp_a1, s16 *, 8) = 0x80FF;
            M2C_FIELD(temp_a1, s16 *, 0xA) = 0x4000;
            D_80079BA0 = var_s0_2;
            SpuVoiceKeyOn(1, temp_a1);
            var_s0_2 += 1;
            var_v1 = var_s0_2 & 0xFFFF;
        } while ((u32) (var_s0_2 & 0xFFFF) < (u8) D_800775E8);
    }
    var_s0_3 = 0;
    var_v0_2 = 0 & 0xFFFF;
    do {
        temp_v0_2 = var_v0_2 * 8;
        *(&D_80079A18 + temp_v0_2) = 0x7F;
        *(&D_80079A1A + temp_v0_2) = 0x7F;
        *(&D_80079A1C + temp_v0_2) = 0x7F;
        *(&D_80079A1E + temp_v0_2) = 0x40;
        var_s0_3 += 1;
        var_v0_2 = var_s0_3 & 0xFFFF;
    } while ((u32) (var_s0_3 & 0xFFFF) < 0x21U);
    D_8007B190 = 0;
    D_8007B198 = 0;
    D_801E9F48 = 0;
    D_8007B1B0 = 0;
    D_8007B1D8 = 0;
    D_80079B70 = 0;
    D_80079B78 = 0x3FFF;
    D_80079B7A = 0x3FFF;
    D_80079B74 = 0;
}

s32 func_80049AF4(void) {
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_v0;
    s16 var_t1_2;
    s16 var_t5;
    s16 var_t6;
    s32 temp_a1;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_a3;
    s32 var_t2;
    s32 var_t3;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v1;
    u16 temp_t0;
    u16 var_t1;
    u16 var_t4;
    u8 var_a3_2;
    u8 var_t3_2;

    var_t6 = -1;
    var_t5 = -1;
    var_t4 = 0xFFFF;
    var_t1 = 0xFFFF;
    var_t2 = 0x63;
    var_t3 = 0x63;
    var_a3 = 0;
    if (D_800775E8 != 0) {
        var_v1 = 0 & 0xFF;
loop_2:
        temp_a1 = var_v1 * 0x18;
        if (*(&D_800797EF + temp_a1) == 0) {
            temp_t0 = *(&D_800797DE + temp_a1);
            var_v0 = var_v1;
            if (temp_t0 != 0) {
                temp_a0 = *(&D_800797EC + temp_a1);
                temp_v1 = var_t6 & 0xFFFF;
                if (temp_a0 < temp_v1) {
                    var_t4 = *(&D_800797DE + temp_a1);
                    var_t6 = temp_a0;
                    var_t2 = var_a3;
                    goto block_17;
                }
                var_v0_2 = var_a3 & 0xFF;
                if (temp_a0 == temp_v1) {
                    var_v0_2 = var_a3 & 0xFF;
                    if (temp_t0 < var_t4) {
                        var_t4 = *(&D_800797DE + temp_a1);
                        var_t2 = var_a3;
                    }
                }
                goto block_18;
            }
        } else {
            var_v0_2 = var_a3 & 0xFF;
            if ((var_t2 & 0xFF) == 0x63) {
                temp_a0_2 = *(&D_800797EC + temp_a1);
                if ((s32) D_80079B98 >= temp_a0_2) {
                    temp_v1_2 = var_t5 & 0xFFFF;
                    if (temp_a0_2 < temp_v1_2) {
                        var_t1 = *(&D_800797DE + temp_a1);
                        var_t5 = temp_a0_2;
                        goto block_16;
                    }
                    var_v0_2 = var_a3 & 0xFF;
                    if (temp_a0_2 == temp_v1_2) {
                        var_v0_2 = var_a3 & 0xFF;
                        if ((u16) *(&D_800797DE + temp_a1) < var_t1) {
                            var_t1 = *(&D_800797DE + temp_a1);
block_16:
                            var_t3 = var_a3;
                            goto block_17;
                        }
                    }
                } else {
block_17:
                    var_v0_2 = var_a3 & 0xFF;
                }
            }
block_18:
            temp_v1_3 = var_v0_2 * 0x18;
            var_a3 += 1;
            *(&D_800797DA + temp_v1_3) = *(&D_800797DA + temp_v1_3) + 1;
            var_v1 = var_a3 & 0xFF;
            if ((u32) (var_a3 & 0xFF) >= (u8) D_800775E8) {
                goto block_19;
            }
            goto loop_2;
        }
    } else {
block_19:
        temp_v1_4 = var_t2 & 0xFF;
        var_v0 = temp_v1_4;
        if (temp_v1_4 == 0x63) {
            var_v0 = var_t3 & 0xFF;
            var_t1_2 = 0;
            if (var_v0 == temp_v1_4) {
                var_t3_2 = D_800775E8;
                var_a3_2 = 0;
                if (D_800775E8 != 0) {
                    var_v0_3 = 0 & 0xFF;
                    do {
                        temp_v1_5 = var_v0_3 * 0x18;
                        if ((s32) D_80079B98 >= *(&D_800797EC + temp_v1_5)) {
                            temp_v0 = *(&D_800797DA + temp_v1_5);
                            if (var_t1_2 < temp_v0) {
                                var_t1_2 = temp_v0;
                                var_t3_2 = var_a3_2;
                            }
                        }
                        var_a3_2 += 1;
                        var_v0_3 = var_a3_2 & 0xFF;
                    } while ((u32) (var_a3_2 & 0xFF) < (u8) D_800775E8);
                }
                var_v0 = var_t3_2 & 0xFF;
            }
        }
    }
    return var_v0;
}

s32 func_8004A1D0(void) {
    s32 temp_v0;
    s32 temp_v1;
    u16 var_v1;
    u32 var_v1_2;
    u8 var_a0;

    var_a0 = D_80079B9A;
    temp_v1 = (D_80079B8A + 0x3C) - D_80079B99;
    if ((s32) var_a0 < 0) {
        var_a0 += 7;
    }
    var_v1_2 = var_a0 >> 3;
    if (var_v1_2 >= 0x10U) {
        var_v1_2 = 0xF;
    }
    var_v1 = *(&D_800769D8 + ((((temp_v1 % 12) * 0x10) + (var_v1_2 & 0xFFFF)) * 2));
    temp_v0 = (temp_v1 / 12) - 5;
    if (temp_v0 > 0) {
        var_v1 <<= temp_v0;
    } else if (temp_v0 < 0) {
        var_v1 = (u16) ((s32) (var_v1 & 0xFFFF) >> -temp_v0);
    }
    return var_v1 & 0xFFFF;
}

void func_8004A914(void) {
    s16 var_s0;
    s16 var_v0_2;
    s32 temp_a0;
    s32 var_v0;

    var_s0 = 0;
    if (D_800775E8 != 0) {
        var_v0 = 0 << 0x10;
        do {
            temp_a0 = var_v0 >> 0x10;
            var_v0_2 = var_s0 + 1;
            if (*(&D_800797EF + (temp_a0 * 0x18)) == 1) {
                func_8004A8D0(temp_a0);
                var_v0_2 = var_s0 + 1;
            }
            var_s0 = var_v0_2;
            var_v0 = var_s0 << 0x10;
        } while (var_v0_2 < (s32) D_800775E8);
    }
}

void func_8004A9A8(s32 arg0, s32 arg1) {
    func_8004A9D4(arg0 & 0xFFFF, arg1 & 0xFFFF, 0x80FF, 0x5FC8);
}

s32 func_8004AA64(s8 arg0, s16 arg1, s16 arg2, s32 arg3) {
    s16 sp10;
    s16 temp_s0;
    s32 temp_a0;
    s32 temp_s0_2;
    s32 temp_s3;
    s32 temp_v0;
    s32 var_a1;
    s32 var_lo;
    s32 var_s1;
    s32 var_s4;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v1;
    u16 var_a0;
    u8 temp_v1;
    u8 temp_v1_2;

    var_s4 = 0;
    sp10 = arg1;
    func_8004ACE4(arg1, arg2);
    M2C_FIELD(&D_80079B88, s8 *, 0) = arg0;
    var_s1 = 0;
    temp_s0 = arg3 + 0xFFC0;
    if ((u8) D_800775E8 > 0U) {
        temp_s3 = arg3 & 0xFFFF;
        var_v1 = 0 & 0xFF;
        do {
            temp_a0 = var_v1 * 0x18;
            if ((*(&D_800797E2 + temp_a0) == (s16) arg0) && (*(&D_800797EA + temp_a0) == (s16) (u16) sp10) && (*(&D_800797E6 + temp_a0) == arg2)) {
                var_a0 = *(&D_800797E0 + temp_a0);
                temp_v0 = *(&D_800797E8 + temp_a0) + (D_80079B8F * 0x10);
                if (temp_s0 > 0) {
                    temp_v1 = M2C_FIELD((((temp_v0 & 0xFFFF) << 5) + D_801733B0), u8 *, 0xD);
                    var_v0 = temp_s0 * temp_v1;
                    var_lo = (temp_s3 - 0x40) * temp_v1;
                    if (var_v0 < 0) {
                        var_v0 += 0x3F;
                    }
                    goto block_11;
                }
                var_a1 = 0;
                if (temp_s0 < 0) {
                    temp_v1_2 = M2C_FIELD((((temp_v0 & 0xFFFF) << 5) + D_801733B0), u8 *, 0xC);
                    var_v0 = temp_s0 * temp_v1_2;
                    var_lo = temp_s3 * temp_v1_2;
                    if (var_v0 < 0) {
                        var_v0 += 0x3F;
                    }
block_11:
                    var_a0 += var_v0 >> 6;
                    var_v0_2 = var_lo;
                    if (var_lo < 0) {
                        var_v0_2 = var_lo + 0x3F;
                    }
                    var_a1 = var_lo - ((var_v0_2 >> 6) << 6);
                }
                temp_s0_2 = var_s1 & 0xFF;
                M2C_FIELD((&D_80079B88 + 0xD), s16 *, 0xB) = (s16) (var_s1 & 0xFF);
                M2C_FIELD(&D_80079B88, u8 *, 0xD) = (u8) *(&D_800797E8 + (temp_s0_2 * 0x18));
                var_s4 += 1;
                M2C_FIELD(((temp_s0_2 * 0x10) + D_8007745C), s16 *, 4) = func_8004C27C(var_a0 & 0xFFFF, var_a1 & 0xFFFF);
            }
            var_s1 += 1;
            var_v1 = var_s1 & 0xFF;
        } while ((u32) (var_s1 & 0xFF) < (u8) D_800775E8);
    }
    return var_s4;
}

void func_8004B404(s16 arg0, s16 arg1, s32 arg2, u16 arg4, u16 arg5) {
    s32 var_v1;
    u16 var_a0;
    u32 temp_a0;
    u32 temp_v1;

    temp_a0 = arg4 & 0xFFFF;
    temp_v1 = arg5 & 0xFFFF;
    if (temp_a0 == temp_v1) {
        var_v1 = 0x40;
        var_a0 = arg4;
    } else if (temp_v1 < temp_a0) {
        var_a0 = arg4;
        var_v1 = (s32) (temp_v1 << 6) / (s32) temp_a0;
    } else {
        var_a0 = arg5;
        var_v1 = 0x7F - ((s32) (temp_a0 << 6) / (s32) temp_v1);
    }
    func_8004ADB8(0x20, arg0, arg1, arg2 & 0xFFFF, var_a0 & 0xFFFF, var_v1 & 0xFFFF);
}

void func_8004B4F4(s16 arg0, s16 arg1, s32 arg2) {
    func_8004B1BC(0x20, arg0, arg1, arg2 & 0xFFFF);
}

s32 func_8004B530(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    s16 var_a1;
    s16 var_v0_2;
    s32 temp_t0;
    s32 var_v0;
    void *temp_v0;

    temp_t0 = arg0 * 8;
    if (arg0 < 0x22) {
        *(&D_80079A1A + temp_t0) = arg1;
        *(&D_80079A1C + temp_t0) = arg2;
        if ((u16) *(&D_80079A1A + temp_t0) >= 0x80U) {
            *(&D_80079A1A + temp_t0) = 0x7F;
        }
        if ((u16) *(&D_80079A1C + temp_t0) >= 0x80U) {
            *(&D_80079A1C + temp_t0) = 0x7F;
        }
        var_v0 = arg0 << 0x10;
        if (arg3 == 1) {
            var_a1 = 0;
            if (D_800775E8 != 0) {
                do {
                    var_v0_2 = var_a1 + 1;
                    if (*(&D_800797E2 + (var_a1 * 0x18)) == arg0) {
                        temp_v0 = ((s32) (var_a1 << 0x13) >> 0xF) + D_8007745C;
                        M2C_FIELD(temp_v0, s16 *, 0) = (s16) ((arg1 & 0xFFFF) * 0x81);
                        M2C_FIELD(temp_v0, s16 *, 2) = (s16) ((arg2 & 0xFFFF) * 0x81);
                        var_v0_2 = var_a1 + 1;
                    }
                    var_a1 = var_v0_2;
                } while (var_v0_2 < (s32) D_800775E8);
            }
            var_v0 = arg0 << 0x10;
        }
        return var_v0 >> 0x10;
    }
    return -1;
}

s16 func_8004B688(s16 arg0, u16 *arg1, u16 *arg2) {
    s32 temp_v0;

    temp_v0 = arg0 * 8;
    if (arg0 >= 0x22) {
        return -1;
    }
    *arg1 = *(&D_80079A1A + temp_v0);
    *arg2 = *(&D_80079A1C + temp_v0);
    return arg0;
}

s16 func_8004BF4C(s32 arg0, u32 arg1, s16 arg2) {
    s16 temp_s2;
    s16 var_v0;
    s32 temp_s0;
    s32 temp_s0_2;
    u32 temp_v0;
    u32 var_s1;

    if ((u32) (arg2 & 0xFFFF) < 0x11U) {
        var_v0 = -1;
        if (*(&D_80079B20 + arg2) == 2) {
            temp_s0 = arg2 * 4;
            if (D_80077464 == 0) {
                D_80077468 = arg2;
                D_80077464 = *(&D_80079CA8 + temp_s0);
                func_80059060(0);
                func_800590B4(*(&D_80079C68 + temp_s0));
            }
            temp_s2 = D_80077468;
            var_v0 = -1;
            if (temp_s2 == arg2) {
                var_s1 = arg1;
                if ((u32) D_80077464 < var_s1) {
                    var_s1 = D_80077464;
                }
                temp_s0_2 = func_80059170(arg0, var_s1);
                func_80059014(1);
                if (temp_s0_2 != var_s1) {
                    goto block_8;
                }
                temp_v0 = D_80077464 - var_s1;
                D_80077464 = temp_v0;
                var_v0 = -2;
                if (temp_v0 == 0) {
                    D_80077464 = 0;
                    D_80077468 = -1;
                    *(&D_80079B20 + temp_s2) = 1;
                    var_v0 = temp_s2;
                }
                
                return var_v0;
            }
            
            return var_v0;
        }
        return var_v0;
    }
block_8:
    return -1;
}

s32 func_8004C870(s16 arg1, s16 arg2, s16 arg4) {
    return -((func_8004AA64(0x20, arg1, arg2, arg4) << 0x10) == 0);
}

s32 func_8004C9DC(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4, u16 arg5) {
    s32 temp_a0;
    void *temp_v1;

    if ((u32) (arg0 & 0xFFFF) < 0x18U) {
        temp_a0 = arg0 * 0x18;
        if ((*(&D_800797EA + temp_a0) == arg1) && (*(&D_800797E6 + temp_a0) == arg2) && (*(&D_800797E0 + temp_a0) == arg3)) {
            temp_v1 = (arg0 * 0x10) + D_8007745C;
            M2C_FIELD(temp_v1, u16 *, 8) = arg4;
            M2C_FIELD(temp_v1, u16 *, 0xA) = arg5;
            return 0;
        }
        
        return -1;
    }
    return -1;
}

s32 func_8004CA90(s16 arg0, void *arg1) {
    s32 var_v0;
    void *temp_v1;

    var_v0 = -1;
    if (*(&D_80079B20 + arg0) == 1) {
        temp_v1 = *(&D_80079BA8 + (arg0 * 4));
        M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD(temp_v1, s32 *, 0);
        M2C_FIELD(arg1, s32 *, 8) = (s32) M2C_FIELD(temp_v1, s32 *, 8);
        M2C_FIELD(arg1, s32 *, 4) = (s32) M2C_FIELD(temp_v1, s32 *, 4);
        M2C_FIELD(arg1, u16 *, 0x12) = (u16) M2C_FIELD(temp_v1, u16 *, 0x12);
        M2C_FIELD(arg1, u16 *, 0x14) = (u16) M2C_FIELD(temp_v1, u16 *, 0x14);
        D_80173388 = temp_v1;
        M2C_FIELD(arg1, u16 *, 0x16) = (u16) M2C_FIELD(temp_v1, u16 *, 0x16);
        M2C_FIELD(arg1, u8 *, 0x18) = (u8) M2C_FIELD(temp_v1, u8 *, 0x18);
        M2C_FIELD(arg1, u8 *, 0x19) = (u8) M2C_FIELD(D_80173388, u8 *, 0x19);
        M2C_FIELD(arg1, u8 *, 0x1A) = (u8) M2C_FIELD(D_80173388, u8 *, 0x1A);
        var_v0 = 0;
        M2C_FIELD(arg1, u8 *, 0x1B) = (u8) M2C_FIELD(D_80173388, u8 *, 0x1B);
    }
    return var_v0;
}

s32 func_8004CB74(s16 arg0, void *arg1) {
    s32 var_v0;
    void *temp_v1;

    var_v0 = -1;
    if (*(&D_80079B20 + arg0) == 1) {
        temp_v1 = *(&D_80079BA8 + (arg0 * 4));
        D_80173388 = temp_v1;
        M2C_FIELD(temp_v1, u8 *, 0x18) = (u8) M2C_FIELD(arg1, u8 *, 0x18);
        M2C_FIELD(D_80173388, u8 *, 0x19) = (u8) M2C_FIELD(arg1, u8 *, 0x19);
        M2C_FIELD(D_80173388, u8 *, 0x1A) = (u8) M2C_FIELD(arg1, u8 *, 0x1B);
        var_v0 = 0;
        M2C_FIELD(D_80173388, u8 *, 0x1B) = (u8) M2C_FIELD(arg1, u8 *, 0x1B);
    }
    return var_v0;
}

s32 func_8004CD10(s16 arg0, s16 arg1, void *arg2) {
    s32 temp_s0;

    if (*(&D_80079B20 + arg0) != 1) {
        return -1;
    }
    func_8004ACE4(arg0, arg1);
    temp_s0 = arg1 * 0x10;
    M2C_FIELD((temp_s0 + D_80173350), u8 *, 1) = (u8) M2C_FIELD(arg2, u8 *, 1);
    M2C_FIELD((temp_s0 + D_80173350), u8 *, 2) = (u8) M2C_FIELD(arg2, u8 *, 2);
    M2C_FIELD((temp_s0 + D_80173350), u8 *, 3) = (u8) M2C_FIELD(arg2, u8 *, 3);
    M2C_FIELD((temp_s0 + D_80173350), u8 *, 4) = (u8) M2C_FIELD(arg2, u8 *, 4);
    M2C_FIELD((temp_s0 + D_80173350), u16 *, 6) = (u16) M2C_FIELD(arg2, u16 *, 6);
    return 0;
}

s32 func_8004D278(s32 arg0, s16 *arg1, s16 *arg2) {
    void *temp_v0;

    if ((u32) (arg0 & 0xFFFF) >= 0x18U) {
        return -1;
    }
    temp_v0 = ((s32) (arg0 << 0x10) >> 0xC) + D_8007745C;
    *arg1 = (s16) ((s16) M2C_FIELD(temp_v0, s16 *, 0) / 129);
    *arg2 = (s16) ((s16) M2C_FIELD(temp_v0, u16 *, 2) / 129);
    return 0;
}

void func_8004D3C0(void) {
    func_80058EB8(1);
}

void func_8004D3E0(void) {
    func_80058EB8(0);
}

s16 func_8004D400(s16 arg0) {
    if ((u32) (arg0 & 0xFFFF) >= 0xAU) {
        return -1;
    }
    D_80079B70 = 1;
    D_80079B74 = (s32) arg0;
    func_80057A24(&D_80079B70);
    return arg0;
}

void func_8004D52C(s16 arg0) {
    D_80079B70 = 0x10;
    D_80079B80 = (s32) arg0;
    func_80057A24(&D_80079B70);
}

void func_8004D56C(s16 arg0) {
    D_80079B70 = 8;
    D_80079B7C = (s32) arg0;
    func_80057A24(&D_80079B70);
}

void func_8004D754(void) {
    func_8004B310();
}

void func_8004DEAC(void) {
    if ((D_8012D0C0 == 0) || (D_801D7E20 != 0)) {
        func_80049638();
        func_8004DF3C(D_80077600);
        func_8004DF1C(D_80077600);
        func_800497D8();
    }
    func_80058E58();
}

void func_8004DFC4(s32 arg0, s16 arg1, s16 arg2) {
    s32 sp10;
    s16 sp1C;
    s16 sp1E;
    s16 sp28;
    s16 sp2A;
    s16 var_a3;
    s16 var_t0;

    var_a3 = arg1;
    var_t0 = arg2;
    if (!(arg0 & 0xFF)) {
        sp10 = 0x30;
        if (arg1 >= 0x80) {
            var_a3 = 0x7F;
        }
        if (arg2 >= 0x80) {
            var_t0 = 0x7F;
        }
        sp1C = (s16) ((s32) (var_a3 * 0x7FFF) / 127);
        sp1E = (s16) ((s32) (var_t0 * 0x7FFF) / 127);
    }
    if ((arg0 & 0xFF) == 1) {
        sp10 = 0xC0;
        if (var_a3 >= 0x80) {
            var_a3 = 0x7F;
        }
        if (var_t0 >= 0x80) {
            var_t0 = 0x7F;
        }
        sp28 = (s16) ((s32) (var_a3 * 0x7FFF) / 127);
        sp2A = (s16) ((s32) (var_t0 * 0x7FFF) / 127);
    }
    func_80055E2C(0, 0x100, &sp10, var_a3);
}

void func_8004E8F0(s16 arg0, s16 arg1) {
    func_8004E91C(arg0, arg1);
}

void func_8004EADC(s16 arg0, s16 arg1) {
    s32 *temp_s1;
    s32 temp_a0_2;
    s32 temp_s2;
    s8 temp_a1;
    u8 *temp_a0;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_a1_2;
    u8 *temp_v0_7;
    u8 temp_v1_2;
    u8 var_s0;
    u8 var_s5;
    void *temp_a0_8;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v0_6;
    void *temp_v1;

    temp_s1 = (arg0 * 4) + &D_801E90E8;
    temp_s2 = arg1 * 0xA8;
    temp_v1 = temp_s2 + *temp_s1;
    temp_a0 = M2C_FIELD(temp_v1, u8 **, 4);
    M2C_FIELD(temp_v1, u8 **, 4) = (u8 *) (temp_a0 + 1);
    var_s0 = *temp_a0;
    temp_a1 = var_s0 & 0xF;
    if (var_s0 & 0x80) {
        temp_a0_2 = var_s0 & 0xF0;
        M2C_FIELD((temp_s2 + *temp_s1), s8 *, 0x12) = temp_a1;
        switch (temp_a0_2) {
        case 0x90:
            M2C_FIELD((temp_s2 + *temp_s1), s8 *, 0x11) = 0x90;
            temp_v0 = temp_s2 + *temp_s1;
            temp_a1_2 = M2C_FIELD(temp_v0, u8 **, 4);
            M2C_FIELD(temp_v0, u8 **, 4) = (u8 *) (temp_a1_2 + 1);
            temp_v0_2 = temp_s2 + *temp_s1;
            temp_a0_3 = M2C_FIELD(temp_v0_2, u8 **, 4);
            var_s0 = *temp_a1_2;
            M2C_FIELD(temp_v0_2, u8 **, 4) = (u8 *) (temp_a0_3 + 1);
            var_s5 = *temp_a0_3;
            goto block_23;
        case 0xB0:
            M2C_FIELD((temp_s2 + *temp_s1), s8 *, 0x11) = 0xB0;
            temp_v0_3 = temp_s2 + *temp_s1;
            temp_a0_4 = M2C_FIELD(temp_v0_3, u8 **, 4);
            M2C_FIELD(temp_v0_3, u8 **, 4) = (u8 *) (temp_a0_4 + 1);
            func_8004EFB8(arg0, arg1, *temp_a0_4);
            return;
        case 0xC0:
            M2C_FIELD((temp_s2 + *temp_s1), s8 *, 0x11) = 0xC0;
            temp_v0_4 = temp_s2 + *temp_s1;
            temp_a0_5 = M2C_FIELD(temp_v0_4, u8 **, 4);
            M2C_FIELD(temp_v0_4, u8 **, 4) = (u8 *) (temp_a0_5 + 1);
            func_8004EF34(arg0, arg1, *temp_a0_5);
            return;
        case 0xE0:
            M2C_FIELD((temp_s2 + *temp_s1), s8 *, 0x11) = 0xE0;
            temp_v0_5 = temp_s2 + *temp_s1;
            temp_a0_6 = M2C_FIELD(temp_v0_5, u8 **, 4);
            M2C_FIELD(temp_v0_5, u8 **, 4) = (u8 *) (temp_a0_6 + 1);
            func_80050858(arg0, arg1, *temp_a0_6);
            return;
        case 0xF0:
            M2C_FIELD((temp_s2 + *temp_s1), s8 *, 0x11) = 0xFF;
            M2C_FIELD((temp_s2 + *temp_s1), s8 *, 0x12) = temp_a1;
            temp_v0_6 = temp_s2 + *temp_s1;
            temp_a0_7 = M2C_FIELD(temp_v0_6, u8 **, 4);
            M2C_FIELD(temp_v0_6, u8 **, 4) = (u8 *) (temp_a0_7 + 1);
            func_80050918(arg0, arg1, *temp_a0_7);
            return;
        }
    } else {
        temp_a0_8 = temp_s2 + *temp_s1;
        temp_v1_2 = M2C_FIELD(temp_a0_8, u8 *, 0x11);
        switch (temp_v1_2) {
        case 0x90:
            temp_v0_7 = M2C_FIELD(temp_a0_8, u8 **, 4);
            M2C_FIELD(temp_a0_8, u8 **, 4) = (u8 *) (temp_v0_7 + 1);
            var_s5 = *temp_v0_7;
block_23:
            M2C_FIELD((temp_s2 + *temp_s1), s32 *, 0x88) = func_80050DF8(arg0, arg1);
            func_8004EE3C(arg0, arg1, var_s0, var_s5);
            return;
        case 0xB0:
            func_8004EFB8(arg0, arg1, var_s0);
            return;
        case 0xC0:
            func_8004EF34(arg0, arg1, var_s0);
            return;
        case 0xE0:
            func_80050858(arg0, arg1, var_s0);
            return;
        case 0xFF:
            func_80050918(arg0, arg1, var_s0);
            return;
        }
    }
}

void func_8004F3B8(s16 arg0, s16 arg1, s8 arg2) {
    u8 sp10;
    M2C_UNK sp20;
    s8 sp28;
    s16 sp40;
    s32 *temp_s1;
    s32 temp_s0;
    s32 var_s3;
    u8 temp_s5;
    void *temp_s0_2;
    void *temp_v0;
    void *temp_v0_2;

    temp_s1 = ((s32) (arg0 << 0x10) >> 0xE) + &D_801E90E8;
    temp_v0 = (arg1 * 0xA8) + *temp_s1;
    temp_s5 = M2C_FIELD(temp_v0, u8 *, 0x12);
    sp40 = arg1;
    func_8004CC08(M2C_FIELD(temp_v0, s16 *, 0x4A), M2C_FIELD((temp_s5 + temp_v0), u8 *, 0x2C), &sp10, arg0);
    var_s3 = 0;
    if ((s32) sp10 > 0) {
        do {
            temp_s0 = arg1 * 0xA8;
            temp_v0_2 = temp_s0 + *temp_s1;
            func_8004CDDC(M2C_FIELD(temp_v0_2, s16 *, 0x4A), M2C_FIELD((temp_v0_2 + temp_s5), u8 *, 0x2C), var_s3, &sp20);
            sp28 = arg2;
            temp_s0_2 = temp_s0 + *temp_s1;
            func_8004D018(M2C_FIELD(temp_s0_2, s16 *, 0x4A), M2C_FIELD((temp_s0_2 + temp_s5), u8 *, 0x2C), var_s3, &sp20);
            var_s3 += 1;
        } while (var_s3 < (s32) sp10);
    }
    M2C_FIELD((((s16) (u16) sp40 * 0xA8) + *(&D_801E90E8 + (arg0 * 4))), s32 *, 0x88) = func_80050DF8(arg0, (s16) (u16) sp40);
}

void func_8004F548(s16 arg0, s16 arg1, s8 arg2) {
    u8 sp10;
    M2C_UNK sp20;
    s8 sp2B;
    s16 sp40;
    s32 *temp_s1;
    s32 temp_s0;
    s32 var_s3;
    u8 temp_s5;
    void *temp_s0_2;
    void *temp_v0;
    void *temp_v0_2;

    temp_s1 = ((s32) (arg0 << 0x10) >> 0xE) + &D_801E90E8;
    temp_v0 = (arg1 * 0xA8) + *temp_s1;
    temp_s5 = M2C_FIELD(temp_v0, u8 *, 0x12);
    sp40 = arg1;
    func_8004CC08(M2C_FIELD(temp_v0, s16 *, 0x4A), M2C_FIELD((temp_s5 + temp_v0), u8 *, 0x2C), &sp10, arg0);
    var_s3 = 0;
    if ((s32) sp10 > 0) {
        do {
            temp_s0 = arg1 * 0xA8;
            temp_v0_2 = temp_s0 + *temp_s1;
            func_8004CDDC(M2C_FIELD(temp_v0_2, s16 *, 0x4A), M2C_FIELD((temp_v0_2 + temp_s5), u8 *, 0x2C), var_s3, &sp20);
            sp2B = arg2;
            temp_s0_2 = temp_s0 + *temp_s1;
            func_8004D018(M2C_FIELD(temp_s0_2, s16 *, 0x4A), M2C_FIELD((temp_s0_2 + temp_s5), u8 *, 0x2C), var_s3, &sp20);
            var_s3 += 1;
        } while (var_s3 < (s32) sp10);
    }
    M2C_FIELD((((s16) (u16) sp40 * 0xA8) + *(&D_801E90E8 + (arg0 * 4))), s32 *, 0x88) = func_80050DF8(arg0, (s16) (u16) sp40);
}

void func_8004F914(s16 arg0, s16 arg1) {
    s32 *temp_s1;
    s32 temp_s0;
    s32 temp_v1;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v1_2;

    func_8004D3E0();
    temp_s1 = (arg0 * 4) + &D_801E90E8;
    temp_v1 = *temp_s1;
    temp_s0 = arg1 * 0xA8;
    temp_v0 = temp_s0 + temp_v1;
    M2C_FIELD((temp_v1 + M2C_FIELD(temp_v0, u8 *, 0x12)), u8 *, 0x2C) = (u8) M2C_FIELD(temp_v0, u8 *, 0x12);
    M2C_FIELD((temp_s0 + *temp_s1), s8 *, 0x13) = 0;
    M2C_FIELD((temp_s0 + *temp_s1), s8 *, 0x14) = 0;
    temp_v1_2 = temp_s0 + *temp_s1;
    M2C_FIELD(((M2C_FIELD(temp_v1_2, u8 *, 0x12) * 2) + temp_v1_2), s16 *, 0x4C) = 0x7F;
    temp_v0_2 = temp_s0 + *temp_s1;
    M2C_FIELD((temp_v0_2 + M2C_FIELD(temp_v0_2, u8 *, 0x12)), s8 *, 0x17) = 0x40;
    M2C_FIELD((temp_s0 + *temp_s1), s32 *, 0x88) = func_80050DF8(arg0, arg1);
}

void func_8004FE10(s16 arg0, s16 arg1, s8 arg2) {
    s32 *temp_s1;
    s32 temp_s0;
    void *temp_v1;

    temp_s1 = (arg0 * 4) + &D_801E90E8;
    temp_s0 = arg1 * 0xA8;
    M2C_FIELD((temp_s0 + *temp_s1), s8 *, 0x13) = arg2;
    temp_v1 = temp_s0 + *temp_s1;
    M2C_FIELD(temp_v1, u8 *, 0x29) = (u8) (M2C_FIELD(temp_v1, u8 *, 0x29) + 1);
    M2C_FIELD((temp_s0 + *temp_s1), s32 *, 0x88) = func_80050DF8(arg0, arg1);
}

void func_8004FEA4(s16 arg0, s16 arg1, s8 arg2) {
    s32 *temp_s1;
    s32 temp_s0;
    void *temp_v1;

    temp_s1 = (arg0 * 4) + &D_801E90E8;
    temp_s0 = arg1 * 0xA8;
    M2C_FIELD((temp_s0 + *temp_s1), s8 *, 0x14) = arg2;
    temp_v1 = temp_s0 + *temp_s1;
    M2C_FIELD(temp_v1, u8 *, 0x29) = (u8) (M2C_FIELD(temp_v1, u8 *, 0x29) + 1);
    M2C_FIELD((temp_s0 + *temp_s1), s32 *, 0x88) = func_80050DF8(arg0, arg1);
}

void func_80050EF4(s16 arg0, s16 arg1) {
    s32 *temp_s1;
    s32 temp_s0;
    void *temp_s0_2;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;
    void *temp_v1_4;
    void *temp_v1_5;

    temp_s1 = (arg0 * 4) + &D_801E90E8;
    temp_s0 = arg1 * 0xA8;
    M2C_FIELD((temp_s0 + *temp_s1), s16 *, 0x44) = 1;
    M2C_FIELD((temp_s0 + *temp_s1), s16 *, 0x46) = 0;
    func_8004B530(arg0, 0x7F, 0x7F, arg1);
    temp_v1 = temp_s0 + *temp_s1;
    M2C_FIELD(temp_v1, s32 *, 0x90) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x90) & ~0x100);
    temp_v1_2 = temp_s0 + *temp_s1;
    M2C_FIELD(temp_v1_2, s32 *, 0x90) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0x90) & ~8);
    temp_v1_3 = temp_s0 + *temp_s1;
    M2C_FIELD(temp_v1_3, s32 *, 0x90) = (s32) (M2C_FIELD(temp_v1_3, s32 *, 0x90) & ~2);
    temp_v1_4 = temp_s0 + *temp_s1;
    M2C_FIELD(temp_v1_4, s32 *, 0x90) = (s32) (M2C_FIELD(temp_v1_4, s32 *, 0x90) & ~4);
    temp_v1_5 = temp_s0 + *temp_s1;
    M2C_FIELD(temp_v1_5, s32 *, 0x90) = (s32) (M2C_FIELD(temp_v1_5, s32 *, 0x90) & ~0x200);
    M2C_FIELD((temp_s0 + *temp_s1), s8 *, 0x2B) = 1;
    temp_s0_2 = temp_s0 + *temp_s1;
    M2C_FIELD(temp_s0_2, s32 *, 0x90) = (s32) (M2C_FIELD(temp_s0_2, s32 *, 0x90) | 1);
}

void func_80051088(void *arg0, s16 *arg1, s16 *arg2) {
    s32 temp_t1;
    s32 var_t0;

    temp_t1 = -(M2C_FIELD(arg0, s16 *, 0xC) != 0) & ~0x7FFF;
    var_t0 = temp_t1;
    if (M2C_FIELD(arg0, s16 *, 0x10) != 0) {
        var_t0 = temp_t1 | 0x4000;
    }
    *arg1 = (-(M2C_FIELD(arg0, s16 *, 0xA) != 0) & ~0x7FFF) | ((M2C_FIELD(arg0, u16 *, 0) << 8) & 0x7F00) | ((M2C_FIELD(arg0, u16 *, 2) * 0x10) & 0xF0) | (M2C_FIELD(arg0, u16 *, 4) & 0xF);
    *arg2 = var_t0 | ((M2C_FIELD(arg0, u16 *, 6) << 6) & 0x1FC0) | (M2C_FIELD(arg0, u16 *, 8) & 0x1F);
}

void func_80051688(s16 arg0, s16 arg1) {
    s32 *temp_s0;
    s32 temp_a1;
    void *temp_a1_2;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_5;
    void *temp_v1;
    void *temp_v1_2;
    void *temp_v1_3;

    func_8004B900(arg0, arg1);
    temp_s0 = (arg0 * 4) + &D_801E90E8;
    temp_a1 = arg1 * 0xA8;
    M2C_FIELD((temp_a1 + *temp_s0), s8 *, 0x2B) = 0;
    M2C_FIELD((temp_a1 + *temp_s0), s32 *, 0x80) = 0;
    temp_v0 = temp_a1 + *temp_s0;
    M2C_FIELD(temp_v0, s32 *, 0x88) = (s32) M2C_FIELD(temp_v0, s32 *, 0x7C);
    temp_v0_2 = temp_a1 + *temp_s0;
    M2C_FIELD(temp_v0_2, s32 *, 0x8C) = (s32) M2C_FIELD(temp_v0_2, s32 *, 0x84);
    temp_v0_3 = temp_a1 + *temp_s0;
    M2C_FIELD(temp_v0_3, u16 *, 0x6E) = (u16) M2C_FIELD(temp_v0_3, u16 *, 0x70);
    temp_v0_4 = temp_a1 + *temp_s0;
    M2C_FIELD(temp_v0_4, s32 *, 4) = (s32) M2C_FIELD(temp_v0_4, s32 *, 8);
    temp_v0_5 = temp_a1 + *temp_s0;
    M2C_FIELD(temp_v0_5, s32 *, 0xC) = (s32) M2C_FIELD(temp_v0_5, s32 *, 8);
    M2C_FIELD((temp_a1 + *temp_s0), s8 *, 0x27) = 0;
    temp_v1 = temp_a1 + *temp_s0;
    M2C_FIELD(temp_v1, s32 *, 0x90) = (s32) (M2C_FIELD(temp_v1, s32 *, 0x90) & ~1);
    temp_v1_2 = temp_a1 + *temp_s0;
    M2C_FIELD(temp_v1_2, s32 *, 0x90) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0x90) & ~2);
    temp_v1_3 = temp_a1 + *temp_s0;
    M2C_FIELD(temp_v1_3, s32 *, 0x90) = (s32) (M2C_FIELD(temp_v1_3, s32 *, 0x90) & ~8);
    temp_a1_2 = temp_a1 + *temp_s0;
    M2C_FIELD(temp_a1_2, s32 *, 0x90) = (s32) (M2C_FIELD(temp_a1_2, s32 *, 0x90) | 4);
}

void func_80051800(s16 arg0, s16 arg1) {
    s32 *temp_s0;
    s32 temp_v1;
    void *temp_v1_2;

    func_8004B900(arg0, arg1);
    temp_s0 = (arg0 * 4) + &D_801E90E8;
    temp_v1 = arg1 * 0xA8;
    M2C_FIELD((temp_v1 + *temp_s0), s8 *, 0x2B) = 0;
    temp_v1_2 = temp_v1 + *temp_s0;
    M2C_FIELD(temp_v1_2, s32 *, 0x90) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0x90) & ~2);
}

void func_800518E8(s32 arg0, s16 arg1) {
    s16 temp_a3;
    s32 *temp_a3_3;
    s32 *temp_t2;
    s32 temp_a2_2;
    s32 temp_t1;
    s32 var_v0_2;
    u32 temp_a3_2;
    u32 temp_t0;
    u32 temp_v1_2;
    u32 temp_v1_3;
    u32 var_a2;
    u32 var_v0;
    void *temp_a0;
    void *temp_a1;
    void *temp_a2;
    void *temp_v1;
    void *temp_v1_4;
    void *temp_v1_5;
    void *var_v1;

    temp_t2 = ((s32) (arg0 << 0x10) >> 0xE) + &D_801E90E8;
    temp_t1 = arg1 * 0xA8;
    temp_v1 = temp_t1 + *temp_t2;
    M2C_FIELD(temp_v1, s32 *, 0xA0) = (s32) (M2C_FIELD(temp_v1, s32 *, 0xA0) - 1);
    temp_a2 = temp_t1 + *temp_t2;
    temp_a3 = M2C_FIELD(temp_a2, s16 *, 0x42);
    if (temp_a3 > 0) {
        if (((u32) M2C_FIELD(temp_a2, u32 *, 0xA0) % (u32) temp_a3) == 0) {
            temp_v1_2 = M2C_FIELD(temp_a2, u32 *, 0x8C);
            temp_a3_2 = M2C_FIELD(temp_a2, u32 *, 0xA4);
            var_v0 = temp_v1_2 - 1;
            if ((temp_a3_2 < temp_v1_2) || (var_v0 = temp_v1_2 + 1, ((temp_v1_2 < temp_a3_2) != 0))) {
                M2C_FIELD(temp_a2, u32 *, 0x8C) = var_v0;
            }
            goto block_11;
        }
    } else {
        temp_v1_3 = M2C_FIELD(temp_a2, u32 *, 0x8C);
        temp_t0 = M2C_FIELD(temp_a2, u32 *, 0xA4);
        if (temp_t0 < temp_v1_3) {
            M2C_FIELD(temp_a2, u32 *, 0x8C) = (u32) (temp_a3 + temp_v1_3);
            var_v1 = temp_t1 + *temp_t2;
            var_a2 = M2C_FIELD(var_v1, u32 *, 0xA4);
            var_v0_2 = (u32) M2C_FIELD(var_v1, u32 *, 0x8C) < var_a2;
            goto block_9;
        }
        if (temp_v1_3 < temp_t0) {
            M2C_FIELD(temp_a2, u32 *, 0x8C) = (u32) (temp_v1_3 - temp_a3);
            var_v1 = temp_t1 + *temp_t2;
            var_a2 = M2C_FIELD(var_v1, u32 *, 0xA4);
            var_v0_2 = var_a2 < (u32) M2C_FIELD(var_v1, u32 *, 0x8C);
block_9:
            if (var_v0_2 != 0) {
                M2C_FIELD(var_v1, u32 *, 0x8C) = var_a2;
            }
        }
block_11:
        temp_a3_3 = ((s32) (arg0 << 0x10) >> 0xE) + &D_801E90E8;
        temp_a2_2 = arg1 * 0xA8;
        temp_a1 = temp_a2_2 + *temp_a3_3;
        M2C_FIELD(temp_a1, s16 *, 0x6E) = (s16) ((u32) (M2C_FIELD(temp_a1, s16 *, 0x48) * M2C_FIELD(temp_a1, s32 *, 0x8C) * 0xA) / (u32) (D_801D9028 * 0x3C));
        temp_v1_4 = temp_a2_2 + *temp_a3_3;
        if (M2C_FIELD(temp_v1_4, s16 *, 0x6E) <= 0) {
            M2C_FIELD(temp_v1_4, s16 *, 0x6E) = 1;
        }
        temp_a0 = temp_a2_2 + *temp_a3_3;
        if ((M2C_FIELD(temp_a0, s32 *, 0xA0) == 0) || (M2C_FIELD(temp_a0, s32 *, 0x8C) == M2C_FIELD(temp_a0, s32 *, 0xA4))) {
            M2C_FIELD(temp_a0, s32 *, 0x90) = (s32) (M2C_FIELD(temp_a0, s32 *, 0x90) & ~0x40);
            temp_v1_5 = temp_a2_2 + *temp_a3_3;
            M2C_FIELD(temp_v1_5, s32 *, 0x90) = (s32) (M2C_FIELD(temp_v1_5, s32 *, 0x90) & ~0x80);
        }
    }
}

void func_80051BC4(void) {
    func_80052854();
}

void func_80051C8C(void) {
    func_80052A98();
}

s32 func_80051E94(s32 arg0, M2C_UNK arg1) {
    s32 temp_s0;

    temp_s0 = arg0 & 0xFF;
    if (func_80051D14(temp_s0, 0) == 0) {
        return func_80052D14(temp_s0, arg1, 0, 1) == 0;
    }
    return 0;
}

void func_80052060(u8 *arg0) {
    u8 sp10;

    func_80051EF0(1, 0, &sp10);
    *arg0 = sp10;
}

void func_8005223C(s32 arg0, void *arg1) {
    s32 temp_a0;
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_lo;
    s32 temp_lo_2;

    temp_a0 = arg0 + 0x96;
    temp_hi = temp_a0 % 75;
    temp_lo = temp_a0 / 75;
    temp_hi_2 = temp_lo % 60;
    temp_lo_2 = temp_lo / 60;
    M2C_FIELD(arg1, s8 *, 2) = (s8) (((temp_hi / 10) * 0x10) + (temp_hi % 10));
    M2C_FIELD(arg1, s8 *, 1) = (s8) (((temp_hi_2 / 10) * 0x10) + (temp_hi_2 % 10));
    M2C_FIELD(arg1, s8 *, 0) = (s8) (((temp_lo_2 / 10) * 0x10) + (temp_lo_2 % 10));
}

s32 func_80052368(void *arg0) {
    u8 temp_a0;
    u8 temp_a1;
    u8 temp_a1_2;
    u8 var_v0;
    u8 var_v1;
    u8 var_v1_2;

    temp_a1 = M2C_FIELD(arg0, u8 *, 0);
    var_v1 = temp_a1;
    if ((s32) temp_a1 < 0) {
        var_v1 = temp_a1 + 0xF;
    }
    temp_a1_2 = M2C_FIELD(arg0, u8 *, 1);
    var_v0 = temp_a1_2;
    if ((s32) temp_a1_2 < 0) {
        var_v0 = temp_a1_2 + 0xF;
    }
    temp_a0 = M2C_FIELD(arg0, u8 *, 2);
    var_v1_2 = temp_a0;
    if ((s32) temp_a0 < 0) {
        var_v1_2 = temp_a0 + 0xF;
    }
    return ((((((((s32) var_v1 >> 4) * 0xA) + (temp_a1 & 0xF)) * 0x3C) + ((((s32) var_v0 >> 4) * 0xA) + (temp_a1_2 & 0xF))) * 0x4B) + ((((s32) var_v1_2 >> 4) * 0xA) + (temp_a0 & 0xF))) - 0x96;
}

void func_800524D8(void) {
    if (D_800774D4 != 0) {
        func_80052504(0);
    }
}

void D_80052820(void) {
    D_800774D4 = 1;
    func_80052504(1);
    D_800774D4 = 0;
}

s32 func_800531A8(s32 arg0, s32 arg1) {
    M2C_UNK *var_a2;

    if (*D_80077510 & 0x01000000) {
        var_a2 = &D_7FFFFF;
loop_2:
        if (var_a2 == (M2C_UNK *)-1) {
            func_80052440(0, var_a2, -1);
            return -1;
        }
        var_a2 -= 1;
        if (!(*D_80077510 & 0x01000000)) {
            goto block_6;
        }
        goto loop_2;
    }
block_6:
    *D_800774D8 = 0;
    *D_800774E4 = 0x80;
    *D_800774FC = 0x20943;
    *D_80077500 = 0x132C;
    *D_80077504 |= 0x8000;
    *D_80077510 = 0;
    *D_80077508 = arg0;
    *D_8007750C = arg1 | 0x10000;
    *D_80077510 = 0x11000000;
    return 0;
}

void func_800534D8(void) {
    func_80051BC4();
    func_80051CCC(&func_800535A0);
    func_80051CE4(&func_800535C8);
    func_80051CFC(&func_800535F0);
}

void func_80053630(void) {
    void *temp_v0;

    func_80049808();
    D_A00003E0 = &func_800536B0;
    D_A00003F0 = &func_80053700;
    D_A00003F8 = &func_8005373C;
    D_A0000414 = &func_800536D8;
    temp_v0 = &func_80053618 + 0x10;
    D_A0000454 = temp_v0;
    D_A0000488 = temp_v0;
    D_A000048C = temp_v0;
}

s32 func_80053A50(void) {
    return func_80054254(0xC) == 0;
}

s32 func_80053D10(s32 arg0, M2C_UNK arg1) {
    s32 var_s1;
    s32 var_v0;
    void *var_s0;

    var_s1 = 0;
    if (D_80077630 > 0) {
        var_s0 = &D_8007A0D0 + 0xC;
loop_2:
        if ((M2C_FIELD(var_s0, s32 *, -8) != arg0) || (var_v0 = var_s1 + 1, (func_80049708(arg1, var_s0) != 0))) {
            var_s1 += 1;
            var_s0 += 0x2C;
            if (var_s1 >= D_80077630) {
                goto block_5;
            }
            goto loop_2;
        }
    } else {
block_5:
        var_v0 = -1;
    }
    return var_v0;
}

u8 func_800540C0(void) {
    u8 sp10;

    func_80051EF0(1, 0, &sp10);
    return sp10;
}

void func_800540EC(s32 arg0, void *arg1) {
    s32 temp_a0;
    s32 temp_lo;
    s32 temp_lo_2;

    temp_lo = (s32) (arg0 + 0x96) / 4500;
    temp_lo_2 = (s32) ((arg0 + 0x96) % 4500) / 75;
    temp_a0 = ((arg0 + 0x96) % 4500) % 75;
    M2C_FIELD(arg1, s8 *, 0) = (s8) ((temp_lo % 10) + ((temp_lo / 10) * 0x10));
    M2C_FIELD(arg1, s8 *, 1) = (s8) ((temp_lo_2 % 10) + ((temp_lo_2 / 10) * 0x10));
    M2C_FIELD(arg1, s8 *, 2) = (s8) ((temp_a0 % 10) + ((temp_a0 / 10) * 0x10));
}

void func_80054584(s32 arg0, s32 arg1) {
    D_801734A0 = arg0;
    D_80077688 = arg1;
    D_800776A0 = 0;
    D_80077698 = 0;
    D_80077690 = 0;
    D_8012CDE0 = 0;
    func_8005486C(0);
    D_8012CFE8 = 0;
}

void func_8005462C(void) {
    func_80049638();
    func_80049140(0);
    func_800490B0(0);
    func_800497D8();
}

void func_800546CC(s32 arg0, s32 arg3, s32 arg4) {
    func_8005495C(1);
    D_80077670 = 0;
    D_800776C0 = arg3;
    D_80077668 = arg0 & 1;
    D_800776C8 = arg4;
}

void func_80055570(void) {
    s32 sp0;
    s32 sp4;

    sp0 = 0;
loop_2:
    if (sp0 < 0xF0) {
        sp4 *= 3;
        sp0 += 1;
        goto loop_2;
    }
}

s32 func_80055E04(s32 arg1) {
    func_800578C4();
    return arg1;
}

void func_80056854(void *arg0) {
    s32 temp_a2;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t5;
    s32 var_t3;
    s32 var_v0;
    s32 var_v1_2;
    u16 *var_t4;
    u16 var_v1;
    u32 temp_t2;
    u32 var_a1;

    temp_t1 = M2C_FIELD(arg0, s32 *, 4);
    var_t3 = 0;
    temp_t0 = temp_t1 == 0;
    temp_t5 = temp_t1 & 0x10;
    var_t4 = D_8007758C;
    temp_t2 = (u32) (M2C_FIELD(D_8007758C, u16 *, 0x1AC) & 0xE) >> 1;
    do {
        if ((1 << var_t3) & M2C_FIELD(arg0, s32 *, 0)) {
            temp_a2 = var_t3 * 8;
            if ((temp_t0 != 0) || (temp_t1 & 1)) {
                *var_t4 = M2C_FIELD(arg0, u16 *, 8);
            }
            if ((temp_t0 != 0) || (temp_t1 & 2)) {
                M2C_FIELD(&D_8007758C[temp_a2], u16 *, 2) = (u16) M2C_FIELD(arg0, u16 *, 0xA);
            }
            if ((temp_t0 != 0) || (temp_t1 & 4)) {
                M2C_FIELD(&D_8007758C[temp_a2], u16 *, 4) = (u16) M2C_FIELD(arg0, u16 *, 0x10);
            }
            if ((temp_t0 != 0) || (temp_t1 & 8)) {
                var_v0 = temp_a2 * 2;
                if (D_800776F0 == 0) {
                    var_v1 = M2C_FIELD(arg0, u16 *, 0x14);
                } else {
                    var_a1 = (u32) M2C_FIELD(arg0, u16 *, 0x14);
                    var_v1_2 = temp_t2 + 1;
                    if (temp_t2 != 0) {
                        var_v1_2 = temp_t2 + 1;
                        if ((var_a1 % temp_t2) != 0) {
                            var_a1 += temp_t2;
                        }
                    }
                    var_v1 = (u16) (var_a1 >> var_v1_2);
                    var_v0 = temp_a2 * 2;
                }
                M2C_FIELD((var_v0 + D_8007758C), u16 *, 6) = var_v1;
            }
            if ((temp_t0 != 0) || (temp_t5 != 0)) {
                M2C_FIELD(&D_8007758C[temp_a2], u16 *, 8) = (u16) M2C_FIELD(arg0, u16 *, 0x1E);
            }
            if ((temp_t0 != 0) || (temp_t5 != 0)) {
                M2C_FIELD(&D_8007758C[temp_a2], u16 *, 0xA) = (u16) M2C_FIELD(arg0, u16 *, 0x1C);
            }
            if ((temp_t0 != 0) || (temp_t1 & 0x100)) {
                M2C_FIELD(&D_8007758C[temp_a2], u16 *, 0xE) = (u16) M2C_FIELD(arg0, u16 *, 0x18);
            }
        }
        var_t3 += 1;
        var_t4 += 0x10;
    } while (var_t3 < 0x18);
}

void func_80057F18(void) {
    s32 *var_v1;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1_2;
    s32 temp_a3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_t1;
    s32 var_t1_2;
    s32 var_t1_3;
    s32 var_t1_4;
    s32 var_t1_5;
    void *temp_a1;
    void *temp_v0;
    void *var_a0;
    void *var_a0_2;
    void *var_a1;
    void *var_a3;
    void *var_t2;
    void *var_v1_2;

    var_t1 = 0;
    if (D_800775B4 >= 0) {
        var_a3 = D_80077728;
        do {
            var_a2 = var_t1 + 1;
            if (M2C_FIELD(var_a3, s32 *, 0) & 0x80000000) {
                var_v1 = (var_a2 * 8) + D_80077728;
loop_4:
                var_v1 += 8;
                if (*var_v1 == 0x2FFFFFFF) {
                    var_a2 += 1;
                    goto loop_4;
                }
                temp_a1 = (var_a2 * 8) + D_80077728;
                temp_a0 = M2C_FIELD(temp_a1, s32 *, 0);
                if ((temp_a0 & 0x80000000) && ((temp_a0 & 0x0FFFFFFF) == ((M2C_FIELD(var_a3, s32 *, 0) & 0x0FFFFFFF) + M2C_FIELD(var_a3, s32 *, 4)))) {
                    M2C_FIELD(temp_a1, s32 *, 0) = 0x2FFFFFFF;
                    M2C_FIELD(var_a3, s32 *, 4) = (s32) (M2C_FIELD(var_a3, s32 *, 4) + M2C_FIELD(temp_a1, s32 *, 4));
                } else {
                    goto block_9;
                }
            } else {
block_9:
                var_a3 += 8;
                var_t1 += 1;
            }
        } while (D_800775B4 >= var_t1);
    }
    var_t1_2 = 0;
    if (D_800775B4 >= 0) {
        var_v1_2 = D_80077728;
        do {
            var_t1_2 += 1;
            if (M2C_FIELD(var_v1_2, s32 *, 4) == 0) {
                M2C_FIELD(var_v1_2, s32 *, 0) = 0x2FFFFFFF;
            }
            var_v1_2 += 8;
        } while (D_800775B4 >= var_t1_2);
    }
    var_t1_3 = 0;
    if (D_800775B4 >= 0) {
        var_t2 = D_80077728;
loop_19:
        if (!(M2C_FIELD(var_t2, s32 *, 0) & 0x40000000)) {
            var_a2_2 = var_t1_3 + 1;
            if (D_800775B4 >= var_a2_2) {
                var_a0 = (var_a2_2 * 8) + D_80077728;
loop_22:
                temp_a1_2 = M2C_FIELD(var_a0, s32 *, 0);
                if (!(temp_a1_2 & 0x40000000)) {
                    temp_a3 = M2C_FIELD(var_t2, s32 *, 0);
                    var_a2_2 += 1;
                    if ((u32) (temp_a1_2 & 0x0FFFFFFF) < (u32) (temp_a3 & 0x0FFFFFFF)) {
                        M2C_FIELD(var_t2, s32 *, 0) = temp_a1_2;
                        temp_v1 = M2C_FIELD(var_t2, s32 *, 4);
                        M2C_FIELD(var_t2, s32 *, 4) = (s32) M2C_FIELD(var_a0, s32 *, 4);
                        M2C_FIELD(var_a0, s32 *, 0) = temp_a3;
                        M2C_FIELD(var_a0, s32 *, 4) = temp_v1;
                    }
                    var_a0 += 8;
                    if (D_800775B4 >= var_a2_2) {
                        goto loop_22;
                    }
                }
            }
            var_t1_3 += 1;
            var_t2 += 8;
            if (D_800775B4 >= var_t1_3) {
                goto loop_19;
            }
        }
    }
    var_t1_4 = 0;
    if (D_800775B4 >= 0) {
        var_a0_2 = D_80077728;
loop_29:
        temp_v1_2 = M2C_FIELD(var_a0_2, s32 *, 0);
        if (!(temp_v1_2 & 0x40000000)) {
            if (temp_v1_2 == 0x2FFFFFFF) {
                temp_v0 = (D_800775B4 * 8) + D_80077728;
                M2C_FIELD(var_a0_2, s32 *, 0) = (s32) M2C_FIELD(temp_v0, s32 *, 0);
                D_800775B4 = var_t1_4;
                M2C_FIELD(var_a0_2, s32 *, 4) = (s32) M2C_FIELD(temp_v0, s32 *, 4);
            } else {
                var_t1_4 += 1;
                var_a0_2 += 8;
                if (D_800775B4 >= var_t1_4) {
                    goto loop_29;
                }
            }
        }
    }
    var_t1_5 = D_800775B4 - 1;
    if (var_t1_5 >= 0) {
        var_a1 = (var_t1_5 * 8) + D_80077728;
loop_35:
        temp_a0_2 = M2C_FIELD(var_a1, s32 *, 0);
        if (temp_a0_2 & 0x80000000) {
            M2C_FIELD(var_a1, s32 *, 0) = (s32) ((temp_a0_2 & 0x0FFFFFFF) | 0x40000000);
            temp_v1_3 = M2C_FIELD(((D_800775B4 * 8) + D_80077728), s32 *, 4);
            D_800775B4 = var_t1_5;
            var_t1_5 -= 1;
            M2C_FIELD(var_a1, s32 *, 4) = (s32) (M2C_FIELD(var_a1, s32 *, 4) + temp_v1_3);
            var_a1 -= 8;
            if (var_t1_5 >= 0) {
                goto loop_35;
            }
        }
    }
}

s32 func_80058B48(u32 arg0) {
    s32 temp_v1;
    s32 var_v0;
    u32 temp_v1_2;
    void *var_a1;

    var_a1 = D_80077728;
loop_1:
    temp_v1 = M2C_FIELD(var_a1, s32 *, 0);
    if (temp_v1 & 0x80000000) {
block_5:
        var_a1 += 8;
        goto loop_1;
    }
    temp_v1_2 = temp_v1 & 0x0FFFFFFF;
    if (!(temp_v1 & 0x40000000)) {
        var_v0 = 1;
        if (temp_v1_2 < arg0) {
            var_v0 = 1;
            if (arg0 >= (u32) (temp_v1_2 + M2C_FIELD(var_a1, s32 *, 4))) {
                goto block_5;
            }
        }
    } else {
        var_v0 = 0;
    }
    return var_v0;
}

void func_80058BB8(s32 arg0) {
    func_80058B48(arg0 << D_80077720);
}

u32 func_80059120(u32 arg1) {
    u32 var_s0;

    var_s0 = arg1;
    if (var_s0 > 0x7F000U) {
        var_s0 = 0x7F000;
    }
    func_80055810(var_s0);
    D_8012CDA8 = 0;
    return var_s0;
}
