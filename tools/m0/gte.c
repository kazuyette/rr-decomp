/* Le GTE du PlayStation. Voir gte.h pour la portée et la méthode de contrôle. */
#include "gte.h"

GTE gte;

/* ------------------------------------------------------------------ drapeaux
 *
 * Le registre FLAG accumule les débordements et les saturations. Son bit 31
 * est un résumé : il vaut 1 si l'un des bits 30..23 ou 18..13 est posé. Le
 * code du jeu le lit rarement, mais une saturation mal placée change le
 * résultat visible, donc autant la modéliser complètement plutôt que de la
 * découvrir plus tard sur une image tordue. */
#define F_MAC1_POS (1u << 30)
#define F_MAC2_POS (1u << 29)
#define F_MAC3_POS (1u << 28)
#define F_MAC1_NEG (1u << 27)
#define F_MAC2_NEG (1u << 26)
#define F_MAC3_NEG (1u << 25)
#define F_IR1      (1u << 24)
#define F_IR2      (1u << 23)
#define F_IR3      (1u << 22)
#define F_R        (1u << 21)
#define F_G        (1u << 20)
#define F_B        (1u << 19)
#define F_SZ3      (1u << 18)
#define F_DIV      (1u << 17)
#define F_MAC0_POS (1u << 16)
#define F_MAC0_NEG (1u << 15)
#define F_SX2      (1u << 14)
#define F_SY2      (1u << 13)
#define F_IR0      (1u << 12)

static void flag_end(void)
{
    if (gte.FLAG & 0x7F87E000u) gte.FLAG |= 0x80000000u;
}

/* Les MAC1-3 sont des accumulateurs 44 bits : au-delà, le débordement est
 * signalé mais la valeur conservée est tronquée à 32 bits. */
static s32 mac123(int n, s64 v)
{
    if (v >= (s64)1 << 43) gte.FLAG |= F_MAC1_POS >> (n - 1);
    if (v < -((s64)1 << 43)) gte.FLAG |= F_MAC1_NEG >> (n - 1);
    return (s32)v;
}

static s32 mac0(s64 v)
{
    if (v > (s64)0x7FFFFFFF) gte.FLAG |= F_MAC0_POS;
    if (v < -(s64)0x80000000) gte.FLAG |= F_MAC0_NEG;
    return (s32)v;
}

static s16 sat_ir(int n, s32 v, int lm)
{
    s32 lo = lm ? 0 : -0x8000;
    if (v > 0x7FFF) { gte.FLAG |= F_IR1 >> (n - 1); return 0x7FFF; }
    if (v < lo)     { gte.FLAG |= F_IR1 >> (n - 1); return (s16)lo; }
    return (s16)v;
}

static s16 sat_ir0(s32 v)
{
    if (v > 0x1000) { gte.FLAG |= F_IR0; return 0x1000; }
    if (v < 0)      { gte.FLAG |= F_IR0; return 0; }
    return (s16)v;
}

static u8 sat_col(int n, s32 v)
{
    if (v > 0xFF) { gte.FLAG |= F_R >> (n - 1); return 0xFF; }
    if (v < 0)    { gte.FLAG |= F_R >> (n - 1); return 0; }
    return (u8)v;
}

static u16 sat_sz3(s32 v)
{
    if (v > 0xFFFF) { gte.FLAG |= F_SZ3; return 0xFFFF; }
    if (v < 0)      { gte.FLAG |= F_SZ3; return 0; }
    return (u16)v;
}

static s16 sat_sxy(int y, s32 v)
{
    if (v > 0x3FF)  { gte.FLAG |= y ? F_SY2 : F_SX2; return 0x3FF; }
    if (v < -0x400) { gte.FLAG |= y ? F_SY2 : F_SX2; return -0x400; }
    return (s16)v;
}

/* ------------------------------------------------------------------ division
 *
 * La projection divise H par SZ3. Le matériel n'a pas de diviseur : il utilise
 * une table de 257 entrées et deux itérations de Newton-Raphson. Reproduire ce
 * chemin exactement importe -- une division juste au sens mathématique donnerait
 * des coordonnées écran différentes de un ou deux, visibles sur les arêtes. */
static u8 unr_table[257];
static int unr_ready;

static void unr_init(void)
{
    int i;
    for (i = 0; i <= 256; i++) {
        s32 v = (0x40000 / (i + 0x100) + 1) / 2 - 0x101;
        unr_table[i] = (u8)(v < 0 ? 0 : (v > 0xFF ? 0xFF : v));
    }
    unr_ready = 1;
}

static u32 gte_divide(u16 h, u16 sz3)
{
    u32 n, d, u, z;
    if (!unr_ready) unr_init();
    if (h >= sz3 * 2) { gte.FLAG |= F_DIV; return 0x1FFFF; }
    for (z = 0; z < 16 && !((sz3 << z) & 0x8000); z++) { }
    n = (u32)h << z;
    d = (u32)sz3 << z;
    u = unr_table[(d - 0x7FC0) >> 7] + 0x101;
    d = ((0x2000080 - (d * u)) >> 8);
    d = ((0x0000080 + (d * u)) >> 8);
    n = (u32)(((u64)n * d + 0x8000) >> 16);
    return n > 0x1FFFF ? 0x1FFFF : n;
}

/* -------------------------------------------------------------------- accès */
void gte_write_data(int reg, u32 v)
{
    s16 lo = (s16)(v & 0xFFFF), hi = (s16)(v >> 16);
    switch (reg) {
    case 0:  gte.VX0 = lo; gte.VY0 = hi; break;
    case 1:  gte.VZ0 = lo; break;
    case 2:  gte.VX1 = lo; gte.VY1 = hi; break;
    case 3:  gte.VZ1 = lo; break;
    case 4:  gte.VX2 = lo; gte.VY2 = hi; break;
    case 5:  gte.VZ2 = lo; break;
    case 6:  gte.RGBC = v; break;
    case 7:  gte.OTZ = (u16)v; break;
    case 8:  gte.IR0 = lo; break;
    case 9:  gte.IR1 = lo; break;
    case 10: gte.IR2 = lo; break;
    case 11: gte.IR3 = lo; break;
    case 12: gte.SX0 = lo; gte.SY0 = hi; break;
    case 13: gte.SX1 = lo; gte.SY1 = hi; break;
    case 14: gte.SX2 = lo; gte.SY2 = hi; break;
    /* SXYP : écrire pousse la pile des coordonnées écran. */
    case 15: gte.SX0 = gte.SX1; gte.SY0 = gte.SY1;
             gte.SX1 = gte.SX2; gte.SY1 = gte.SY2;
             gte.SX2 = lo;      gte.SY2 = hi; break;
    case 16: gte.SZ0 = (u16)v; break;
    case 17: gte.SZ1 = (u16)v; break;
    case 18: gte.SZ2 = (u16)v; break;
    case 19: gte.SZ3 = (u16)v; break;
    case 20: gte.RGB0 = v; break;
    case 21: gte.RGB1 = v; break;
    case 22: gte.RGB2 = v; break;
    case 23: gte.RES1 = (s32)v; break;
    case 24: gte.MAC0 = (s32)v; break;
    case 25: gte.MAC1 = (s32)v; break;
    case 26: gte.MAC2 = (s32)v; break;
    case 27: gte.MAC3 = (s32)v; break;
    /* IRGB : écrire dépaquette une couleur 5-5-5 dans IR1-3, à l'échelle x16. */
    case 28: gte.IRGB = v & 0x7FFF;
             gte.IR1 = (s16)((v & 0x1F) << 7);
             gte.IR2 = (s16)(((v >> 5) & 0x1F) << 7);
             gte.IR3 = (s16)(((v >> 10) & 0x1F) << 7);
             break;
    case 29: break;   /* ORGB est en lecture seule */
    case 30: {
        u32 x = (u32)v, m = (v & 0x80000000u) ? ~x : x;
        int c = 0;
        gte.LZCS = (s32)v;
        while (c < 32 && !(m & 0x80000000u)) { c++; m <<= 1; }
        gte.LZCR = (v == 0 || v == 0xFFFFFFFFu) ? 32 : c;
        break;
    }
    case 31: break;   /* LZCR est en lecture seule */
    default: break;
    }
}

u32 gte_read_data(int reg)
{
    switch (reg) {
    case 0:  return (u16)gte.VX0 | ((u32)(u16)gte.VY0 << 16);
    case 1:  return (u32)(s32)gte.VZ0;
    case 2:  return (u16)gte.VX1 | ((u32)(u16)gte.VY1 << 16);
    case 3:  return (u32)(s32)gte.VZ1;
    case 4:  return (u16)gte.VX2 | ((u32)(u16)gte.VY2 << 16);
    case 5:  return (u32)(s32)gte.VZ2;
    case 6:  return gte.RGBC;
    case 7:  return gte.OTZ;
    case 8:  return (u32)(s32)gte.IR0;
    case 9:  return (u32)(s32)gte.IR1;
    case 10: return (u32)(s32)gte.IR2;
    case 11: return (u32)(s32)gte.IR3;
    case 12: return (u16)gte.SX0 | ((u32)(u16)gte.SY0 << 16);
    case 13: return (u16)gte.SX1 | ((u32)(u16)gte.SY1 << 16);
    case 14:
    case 15: return (u16)gte.SX2 | ((u32)(u16)gte.SY2 << 16);
    case 16: return gte.SZ0;
    case 17: return gte.SZ1;
    case 18: return gte.SZ2;
    case 19: return gte.SZ3;
    case 20: return gte.RGB0;
    case 21: return gte.RGB1;
    case 22: return gte.RGB2;
    case 23: return (u32)gte.RES1;
    case 24: return (u32)gte.MAC0;
    case 25: return (u32)gte.MAC1;
    case 26: return (u32)gte.MAC2;
    case 27: return (u32)gte.MAC3;
    case 28:
    case 29: {
        /* ORGB : IR1-3 ramenés à 5 bits, saturés, relus comme une couleur. */
        s32 r = gte.IR1 / 128, g = gte.IR2 / 128, b = gte.IR3 / 128;
        r = r < 0 ? 0 : (r > 31 ? 31 : r);
        g = g < 0 ? 0 : (g > 31 ? 31 : g);
        b = b < 0 ? 0 : (b > 31 ? 31 : b);
        return (u32)(r | (g << 5) | (b << 10));
    }
    case 30: return (u32)gte.LZCS;
    case 31: return (u32)gte.LZCR;
    default: return 0;
    }
}

void gte_write_ctrl(int reg, u32 v)
{
    s16 lo = (s16)(v & 0xFFFF), hi = (s16)(v >> 16);
    if (reg < 5) { gte.RT[reg * 2] = lo; if (reg * 2 + 1 < 9) gte.RT[reg * 2 + 1] = hi; return; }
    if (reg >= 8 && reg < 13) { int i = (reg - 8) * 2; gte.LLM[i] = lo; if (i + 1 < 9) gte.LLM[i + 1] = hi; return; }
    if (reg >= 16 && reg < 21) { int i = (reg - 16) * 2; gte.LCM[i] = lo; if (i + 1 < 9) gte.LCM[i + 1] = hi; return; }
    switch (reg) {
    case 5:  gte.TRX = (s32)v; break;
    case 6:  gte.TRY = (s32)v; break;
    case 7:  gte.TRZ = (s32)v; break;
    case 13: gte.RBK = (s32)v; break;
    case 14: gte.GBK = (s32)v; break;
    case 15: gte.BBK = (s32)v; break;
    case 21: gte.RFC = (s32)v; break;
    case 22: gte.GFC = (s32)v; break;
    case 23: gte.BFC = (s32)v; break;
    case 24: gte.OFX = (s32)v; break;
    case 25: gte.OFY = (s32)v; break;
    case 26: gte.H = (u16)v; break;
    case 27: gte.DQA = lo; break;
    case 28: gte.DQB = (s32)v; break;
    case 29: gte.ZSF3 = lo; break;
    case 30: gte.ZSF4 = lo; break;
    case 31: gte.FLAG = v & 0x7FFFF000u; flag_end(); break;
    default: break;
    }
}

u32 gte_read_ctrl(int reg)
{
    if (reg < 5) {
        u32 a = (u16)gte.RT[reg * 2];
        u32 b = (reg * 2 + 1 < 9) ? (u32)(u16)gte.RT[reg * 2 + 1] : 0;
        return (reg == 4) ? (u32)(s32)gte.RT[8] : (a | (b << 16));
    }
    if (reg >= 8 && reg < 13) {
        int i = (reg - 8) * 2;
        if (reg == 12) return (u32)(s32)gte.LLM[8];
        return (u32)(u16)gte.LLM[i] | ((u32)(u16)gte.LLM[i + 1] << 16);
    }
    if (reg >= 16 && reg < 21) {
        int i = (reg - 16) * 2;
        if (reg == 20) return (u32)(s32)gte.LCM[8];
        return (u32)(u16)gte.LCM[i] | ((u32)(u16)gte.LCM[i + 1] << 16);
    }
    switch (reg) {
    case 5:  return (u32)gte.TRX;
    case 6:  return (u32)gte.TRY;
    case 7:  return (u32)gte.TRZ;
    case 13: return (u32)gte.RBK;
    case 14: return (u32)gte.GBK;
    case 15: return (u32)gte.BBK;
    case 21: return (u32)gte.RFC;
    case 22: return (u32)gte.GFC;
    case 23: return (u32)gte.BFC;
    case 24: return (u32)gte.OFX;
    case 25: return (u32)gte.OFY;
    case 26: return (u32)(s32)(s16)gte.H;   /* relu signé : bizarrerie du matériel */
    case 27: return (u32)(s32)gte.DQA;
    case 28: return (u32)gte.DQB;
    case 29: return (u32)(s32)gte.ZSF3;
    case 30: return (u32)(s32)gte.ZSF4;
    case 31: return gte.FLAG;
    default: return 0;
    }
}

/* ------------------------------------------------------------------ commandes */
static void push_sz(u16 z)
{
    gte.SZ0 = gte.SZ1; gte.SZ1 = gte.SZ2; gte.SZ2 = gte.SZ3; gte.SZ3 = z;
}

static void push_sxy(s16 x, s16 y)
{
    gte.SX0 = gte.SX1; gte.SY0 = gte.SY1;
    gte.SX1 = gte.SX2; gte.SY1 = gte.SY2;
    gte.SX2 = x;       gte.SY2 = y;
}

static void push_rgb(u8 r, u8 g, u8 b)
{
    gte.RGB0 = gte.RGB1; gte.RGB1 = gte.RGB2;
    gte.RGB2 = (u32)r | ((u32)g << 8) | ((u32)b << 16) | (gte.RGBC & 0xFF000000u);
}

static void rtp(s16 vx, s16 vy, s16 vz, int sf, int lm, int last)
{
    int s = sf ? 12 : 0;
    s64 x = (s64)gte.TRX * 0x1000 + (s64)gte.RT[0] * vx + (s64)gte.RT[1] * vy + (s64)gte.RT[2] * vz;
    s64 y = (s64)gte.TRY * 0x1000 + (s64)gte.RT[3] * vx + (s64)gte.RT[4] * vy + (s64)gte.RT[5] * vz;
    s64 z = (s64)gte.TRZ * 0x1000 + (s64)gte.RT[6] * vx + (s64)gte.RT[7] * vy + (s64)gte.RT[8] * vz;
    s32 m1 = mac123(1, x >> s), m2 = mac123(2, y >> s), m3 = mac123(3, z >> s);
    u32 h_sz3;
    s64 sx, sy;
    gte.MAC1 = m1; gte.MAC2 = m2; gte.MAC3 = m3;
    gte.IR1 = sat_ir(1, m1, lm);
    gte.IR2 = sat_ir(2, m2, lm);
    /* IR3 sature sur la valeur non décalée pour le drapeau, sur la décalée pour
       la valeur -- une irrégularité du matériel, pas une coquille. */
    {
        s32 unshifted = (s32)(z >> 12);
        if (unshifted < -0x8000 || unshifted > 0x7FFF) gte.FLAG |= F_IR3;
        gte.IR3 = (s16)(m3 > 0x7FFF ? 0x7FFF : (m3 < (lm ? 0 : -0x8000) ? (lm ? 0 : -0x8000) : m3));
    }
    push_sz(sat_sz3((s32)(z >> 12)));
    h_sz3 = gte_divide(gte.H, gte.SZ3);
    sx = ((s64)h_sz3 * gte.IR1 + gte.OFX);
    sy = ((s64)h_sz3 * gte.IR2 + gte.OFY);
    gte.MAC0 = mac0(sx);
    push_sxy(sat_sxy(0, (s32)(sx >> 16)), sat_sxy(1, (s32)(sy >> 16)));
    gte.MAC0 = mac0(sy);
    if (last) {
        s64 dq = (s64)h_sz3 * gte.DQA + gte.DQB;
        gte.MAC0 = mac0(dq);
        gte.IR0 = sat_ir0((s32)(dq >> 12));
    }
}

/* Produit matrice x vecteur générique, partagé par mvmva et la famille des
   calculs d'éclairage. */
static void mat_vec(const s16 *m, s16 vx, s16 vy, s16 vz,
                    s32 t0, s32 t1, s32 t2, int sf, int lm)
{
    int s = sf ? 12 : 0;
    s64 x = (s64)t0 * 0x1000 + (s64)m[0] * vx + (s64)m[1] * vy + (s64)m[2] * vz;
    s64 y = (s64)t1 * 0x1000 + (s64)m[3] * vx + (s64)m[4] * vy + (s64)m[5] * vz;
    s64 z = (s64)t2 * 0x1000 + (s64)m[6] * vx + (s64)m[7] * vy + (s64)m[8] * vz;
    gte.MAC1 = mac123(1, x >> s);
    gte.MAC2 = mac123(2, y >> s);
    gte.MAC3 = mac123(3, z >> s);
    gte.IR1 = sat_ir(1, gte.MAC1, lm);
    gte.IR2 = sat_ir(2, gte.MAC2, lm);
    gte.IR3 = sat_ir(3, gte.MAC3, lm);
}

static void interp_far(int sf, int lm, s32 r, s32 g, s32 b)
{
    /* MAC <- MAC + IR0 * (FC - MAC), a l'echelle du materiel.
     *
     * La specification dit : IR = ((FC SHL 12) - MAC) SAR (sf*12), puis
     * MAC = (IR * IR0 + MAC) SAR (sf*12). Le MAC de depart n'est PAS redecale.
     * Ma premiere version le decalait de sf*12 des deux cotes, ce qui donnait
     * des couleurs saturees a blanc sur toute la brume -- une erreur qu'aucun
     * test d'invariant n'aurait vue, et que la seconde transcription en Python
     * a attrapee au premier etat tire.
     */
    int s = sf ? 12 : 0;
    s32 mac[3];
    s32 in[3];
    int i;
    in[0] = r; in[1] = g; in[2] = b;
    {
        s32 fc[3];
        fc[0] = gte.RFC; fc[1] = gte.GFC; fc[2] = gte.BFC;
        for (i = 0; i < 3; i++) {
            s64 d = ((s64)fc[i] << 12) - (s64)in[i];
            s32 ir = sat_ir(i + 1, (s32)(d >> s), 0);
            mac[i] = mac123(i + 1, ((s64)ir * gte.IR0 + (s64)in[i]) >> s);
        }
    }
    gte.MAC1 = mac[0]; gte.MAC2 = mac[1]; gte.MAC3 = mac[2];
    gte.IR1 = sat_ir(1, mac[0], lm);
    gte.IR2 = sat_ir(2, mac[1], lm);
    gte.IR3 = sat_ir(3, mac[2], lm);
    push_rgb(sat_col(1, mac[0] >> 4), sat_col(2, mac[1] >> 4), sat_col(3, mac[2] >> 4));
}

static void light_color(s16 vx, s16 vy, s16 vz, int sf, int lm, int use_rgb, int fog)
{
    int s = sf ? 12 : 0;
    s32 r, g, b;
    mat_vec(gte.LLM, vx, vy, vz, 0, 0, 0, sf, lm);
    mat_vec(gte.LCM, gte.IR1, gte.IR2, gte.IR3, gte.RBK, gte.GBK, gte.BBK, sf, lm);

    if (!use_rgb) {
        /* NCS et NCT : le MAC issu de la seconde matrice EST le resultat.
         * Ma premiere version le recalculait depuis IR, ce qui le divisait par
         * 256 quand sf valait 1 -- des couleurs presque noires, plausibles a
         * l'oeil et fausses. Trouve par la seconde transcription, comme la
         * brume. */
        push_rgb(sat_col(1, gte.MAC1 >> 4), sat_col(2, gte.MAC2 >> 4),
                 sat_col(3, gte.MAC3 >> 4));
        return;
    }

    r = (s32)((gte.RGBC & 0xFF) * gte.IR1) << 4;
    g = (s32)(((gte.RGBC >> 8) & 0xFF) * gte.IR2) << 4;
    b = (s32)(((gte.RGBC >> 16) & 0xFF) * gte.IR3) << 4;
    if (fog) {
        interp_far(sf, lm, r, g, b);
        return;
    }
    gte.MAC1 = mac123(1, (s64)r >> s);
    gte.MAC2 = mac123(2, (s64)g >> s);
    gte.MAC3 = mac123(3, (s64)b >> s);
    gte.IR1 = sat_ir(1, gte.MAC1, lm);
    gte.IR2 = sat_ir(2, gte.MAC2, lm);
    gte.IR3 = sat_ir(3, gte.MAC3, lm);
    push_rgb(sat_col(1, gte.MAC1 >> 4), sat_col(2, gte.MAC2 >> 4),
             sat_col(3, gte.MAC3 >> 4));
}

void gte_command(u32 code)
{
    int fn = code & 0x3F;
    int sf = (code >> 19) & 1;
    int lm = (code >> 10) & 1;
    int s = sf ? 12 : 0;
    gte.FLAG = 0;
    switch (fn) {
    case 0x01: rtp(gte.VX0, gte.VY0, gte.VZ0, sf, lm, 1); break;
    case 0x30:
        rtp(gte.VX0, gte.VY0, gte.VZ0, sf, lm, 0);
        rtp(gte.VX1, gte.VY1, gte.VZ1, sf, lm, 0);
        rtp(gte.VX2, gte.VY2, gte.VZ2, sf, lm, 1);
        break;
    case 0x06:
        gte.MAC0 = mac0((s64)gte.SX0 * (gte.SY1 - gte.SY2)
                        + (s64)gte.SX1 * (gte.SY2 - gte.SY0)
                        + (s64)gte.SX2 * (gte.SY0 - gte.SY1));
        break;
    case 0x2D:
        gte.MAC0 = mac0((s64)gte.ZSF3 * (gte.SZ1 + gte.SZ2 + gte.SZ3));
        gte.OTZ = sat_sz3(gte.MAC0 >> 12);
        break;
    case 0x2E:
        gte.MAC0 = mac0((s64)gte.ZSF4 * (gte.SZ0 + gte.SZ1 + gte.SZ2 + gte.SZ3));
        gte.OTZ = sat_sz3(gte.MAC0 >> 12);
        break;
    case 0x12: {
        int mx = (code >> 17) & 3, vx = (code >> 15) & 3, cv = (code >> 13) & 3;
        const s16 *m = (mx == 0) ? gte.RT : (mx == 1) ? gte.LLM : gte.LCM;
        s16 a, b2, c;
        s32 t0 = 0, t1 = 0, t2 = 0;
        if (vx == 0) { a = gte.VX0; b2 = gte.VY0; c = gte.VZ0; }
        else if (vx == 1) { a = gte.VX1; b2 = gte.VY1; c = gte.VZ1; }
        else if (vx == 2) { a = gte.VX2; b2 = gte.VY2; c = gte.VZ2; }
        else { a = gte.IR1; b2 = gte.IR2; c = gte.IR3; }
        if (cv == 0) { t0 = gte.TRX; t1 = gte.TRY; t2 = gte.TRZ; }
        else if (cv == 1) { t0 = gte.RBK; t1 = gte.GBK; t2 = gte.BBK; }
        else if (cv == 2) { t0 = gte.RFC; t1 = gte.GFC; t2 = gte.BFC; }
        mat_vec(m, a, b2, c, t0, t1, t2, sf, lm);
        break;
    }
    case 0x0C:   /* op : produit vectoriel de (RT11,RT22,RT33) et IR1-3 */
        gte.MAC1 = mac123(1, ((s64)gte.RT[4] * gte.IR3 - (s64)gte.RT[8] * gte.IR2) >> s);
        gte.MAC2 = mac123(2, ((s64)gte.RT[8] * gte.IR1 - (s64)gte.RT[0] * gte.IR3) >> s);
        gte.MAC3 = mac123(3, ((s64)gte.RT[0] * gte.IR2 - (s64)gte.RT[4] * gte.IR1) >> s);
        gte.IR1 = sat_ir(1, gte.MAC1, lm);
        gte.IR2 = sat_ir(2, gte.MAC2, lm);
        gte.IR3 = sat_ir(3, gte.MAC3, lm);
        break;
    case 0x28:   /* sqr */
        gte.MAC1 = mac123(1, ((s64)gte.IR1 * gte.IR1) >> s);
        gte.MAC2 = mac123(2, ((s64)gte.IR2 * gte.IR2) >> s);
        gte.MAC3 = mac123(3, ((s64)gte.IR3 * gte.IR3) >> s);
        gte.IR1 = sat_ir(1, gte.MAC1, lm);
        gte.IR2 = sat_ir(2, gte.MAC2, lm);
        gte.IR3 = sat_ir(3, gte.MAC3, lm);
        break;
    case 0x3D:   /* gpf : IR0 * IR1-3 */
        gte.MAC1 = mac123(1, ((s64)gte.IR0 * gte.IR1) >> s);
        gte.MAC2 = mac123(2, ((s64)gte.IR0 * gte.IR2) >> s);
        gte.MAC3 = mac123(3, ((s64)gte.IR0 * gte.IR3) >> s);
        goto store_rgb;
    case 0x3E:   /* gpl : MAC + IR0 * IR1-3 */
        gte.MAC1 = mac123(1, (((s64)gte.MAC1 << s) + (s64)gte.IR0 * gte.IR1) >> s);
        gte.MAC2 = mac123(2, (((s64)gte.MAC2 << s) + (s64)gte.IR0 * gte.IR2) >> s);
        gte.MAC3 = mac123(3, (((s64)gte.MAC3 << s) + (s64)gte.IR0 * gte.IR3) >> s);
        goto store_rgb;
    store_rgb:
        gte.IR1 = sat_ir(1, gte.MAC1, lm);
        gte.IR2 = sat_ir(2, gte.MAC2, lm);
        gte.IR3 = sat_ir(3, gte.MAC3, lm);
        push_rgb(sat_col(1, gte.MAC1 >> 4), sat_col(2, gte.MAC2 >> 4), sat_col(3, gte.MAC3 >> 4));
        break;
    case 0x10:   /* dpcs : brume sur RGBC */
        interp_far(sf, lm, (s32)(gte.RGBC & 0xFF) << 16,
                   (s32)((gte.RGBC >> 8) & 0xFF) << 16,
                   (s32)((gte.RGBC >> 16) & 0xFF) << 16);
        break;
    case 0x2A:   /* dpct : trois fois, sur la pile de couleurs */
        { int i; for (i = 0; i < 3; i++)
            interp_far(sf, lm, (s32)(gte.RGB0 & 0xFF) << 16,
                       (s32)((gte.RGB0 >> 8) & 0xFF) << 16,
                       (s32)((gte.RGB0 >> 16) & 0xFF) << 16); }
        break;
    case 0x11:   /* intpl : brume sur IR1-3 */
        interp_far(sf, lm, (s32)gte.IR1 << 12, (s32)gte.IR2 << 12, (s32)gte.IR3 << 12);
        break;
    case 0x29:   /* dcpl : brume sur RGBC * IR */
        interp_far(sf, lm,
                   (s32)((gte.RGBC & 0xFF) * gte.IR1) << 4,
                   (s32)(((gte.RGBC >> 8) & 0xFF) * gte.IR2) << 4,
                   (s32)(((gte.RGBC >> 16) & 0xFF) * gte.IR3) << 4);
        break;
    case 0x14:   /* cdp */
        mat_vec(gte.LCM, gte.IR1, gte.IR2, gte.IR3, gte.RBK, gte.GBK, gte.BBK, sf, lm);
        interp_far(sf, lm,
                   (s32)((gte.RGBC & 0xFF) * gte.IR1) << 4,
                   (s32)(((gte.RGBC >> 8) & 0xFF) * gte.IR2) << 4,
                   (s32)(((gte.RGBC >> 16) & 0xFF) * gte.IR3) << 4);
        break;
    case 0x1C:   /* cc */
        mat_vec(gte.LCM, gte.IR1, gte.IR2, gte.IR3, gte.RBK, gte.GBK, gte.BBK, sf, lm);
        gte.MAC1 = mac123(1, (s64)((gte.RGBC & 0xFF) * gte.IR1) << 4 >> s);
        gte.MAC2 = mac123(2, (s64)(((gte.RGBC >> 8) & 0xFF) * gte.IR2) << 4 >> s);
        gte.MAC3 = mac123(3, (s64)(((gte.RGBC >> 16) & 0xFF) * gte.IR3) << 4 >> s);
        goto store_rgb;
    case 0x1E: light_color(gte.VX0, gte.VY0, gte.VZ0, sf, lm, 0, 0); break;
    case 0x20:
        light_color(gte.VX0, gte.VY0, gte.VZ0, sf, lm, 0, 0);
        light_color(gte.VX1, gte.VY1, gte.VZ1, sf, lm, 0, 0);
        light_color(gte.VX2, gte.VY2, gte.VZ2, sf, lm, 0, 0);
        break;
    case 0x1B: light_color(gte.VX0, gte.VY0, gte.VZ0, sf, lm, 1, 0); break;
    case 0x3F:
        light_color(gte.VX0, gte.VY0, gte.VZ0, sf, lm, 1, 0);
        light_color(gte.VX1, gte.VY1, gte.VZ1, sf, lm, 1, 0);
        light_color(gte.VX2, gte.VY2, gte.VZ2, sf, lm, 1, 0);
        break;
    case 0x13: light_color(gte.VX0, gte.VY0, gte.VZ0, sf, lm, 1, 1); break;
    case 0x16:
        light_color(gte.VX0, gte.VY0, gte.VZ0, sf, lm, 1, 1);
        light_color(gte.VX1, gte.VY1, gte.VZ1, sf, lm, 1, 1);
        light_color(gte.VX2, gte.VY2, gte.VZ2, sf, lm, 1, 1);
        break;
    default: break;
    }
    flag_end();
}
