/* cand_func_80012C14.c -- écrite à la main.
 *
 * Le constructeur du tableau de placements des sections de MAP.RRM. C'est la
 * fonction qui a livré la grille 32x32 d'IDX.HED ; on en connaît chaque champ,
 * ce qui est la condition où une conversion manuelle a une chance.
 *
 * Trois points de forme, chacun lu dans les instructions plutôt que deviné :
 *
 * 1. Les arrondis sont écrits en DIVISIONS, pas en décalages. Le retail fait
 *    « addiu +0x400 ; bgez ; addiu +0xBFF ; sra 11 » -- c'est la correction de
 *    biais que GCC insère lui-même pour une division signée par 0x800. L'écrire
 *    en >> 11 produirait un sra nu et raterait de trois instructions par site.
 *    Idem pour /256 sur la direction de caméra.
 *
 * 2. Les fractions de position de caméra sont lues en 16 bits non signés
 *    (lhu) sur les mots 32 bits D_801D9068/6C/70. La carte fait 32 * 2048 =
 *    65536 unités, exactement la plage d'un u16 : la partie basse EST la
 *    position dans le monde, et la soustraire de (cellule << 11) donne le
 *    décalage de la cellule par rapport à la caméra.
 *
 * 3. L'index est écrit dans le placement AVANT d'être testé, et le bit de la
 *    carte des cellules vues est posé dans le même souffle -- les deux
 *    précèdent le « si négatif, passe ». Écrire le test d'abord réordonnerait
 *    deux stores.
 */
#include "m2c_macros.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 index;
} SectionPlacement;   /* 16 octets, confirmé par le pas de 0x10 des deux boucles */

extern SectionPlacement D_801D7810[];   /* 64 entrées */
extern s32 D_801D82D8[];                /* bitmap 32 x 32 des cellules retenues */
extern s32 D_801D8354;                  /* son dernier mot, adressé comme symbole propre */
extern s16 *D_801D82D0;                 /* la table lue depuis IDX.HED */
extern s8 D_8005944C[];                 /* ordre de parcours : 16 dir x 64 (dx,dz) */
extern s32 D_801D9068;                  /* caméra X */
extern s32 D_801D906C;                  /* caméra Y */
extern s32 D_801D9070;                  /* caméra Z */
extern s32 D_801D907C;                  /* cap caméra */
extern s16 D_801E91F0[];                /* matrice de rotation courante */

s32 func_80015AAC(s32 x, s32 z);
s32 func_80015BC4(s32 x, s32 z, s32 zone);
void func_8004315C(s16 *m, s16 *v, s32 *out);

void func_80012C14(void) {
    s16 sp10[3];
    s32 sp18[3];
    s32 i;
    s32 dir;
    s32 cx;
    s32 cz;
    s32 x;
    s32 z;
    s32 zone;
    s32 idx;
    s32 *q;

    /* Le retail charge D_801D8354 -- le dernier mot du bitmap -- comme symbole
     * à part entière et descend un pointeur de quatre en quatre. Écrire
     * D_801D82D8[i] donne la même adresse mais une relocation sur la base plus
     * un déplacement de 124, ce que le retail n'a pas. */
    q = &D_801D8354;
    for (i = 0x1F; i >= 0; i--) {
        *q = 0;
        q--;
    }

    dir = (D_801D907C / 256) & 0xF;
    cx = (D_801D9068 + 0x400) / 0x800;
    cz = (D_801D9070 + 0x400) / 0x800;
    zone = func_80015AAC(cx, cz);

    /* Indexé par [i] plutôt que par un pointeur qui avance : le retail fait
     * marcher deux registres sur le tableau, un sur l'entrée et un sur son
     * champ index, ce que la réduction de force de GCC produit à partir d'un
     * indexage et pas à partir d'un seul pointeur incrémenté. */
    for (i = 0; i < 0x40; i++) {
        x = cx + D_8005944C[dir * 256 + i * 2];
        z = cz + D_8005944C[dir * 256 + i * 2 + 1];
        if ((u32) x >= 0x20U) {
            D_801D7810[i].index = -1;
            continue;
        }
        if ((u32) z >= 0x20U) {
            D_801D7810[i].index = -1;
            continue;
        }
        if (func_80015BC4(x, z, zone) == 0) {
            D_801D7810[i].index = -1;
            continue;
        }
        idx = D_801D82D0[z * 32 + 30 - x];
        D_801D7810[i].index = idx;
        D_801D82D8[z] |= 1 << x;
        if (idx < 0) {
            continue;
        }
        sp10[0] = (x << 11) - (u16) D_801D9068;
        sp10[1] = -(u16) D_801D906C;
        sp10[2] = (z << 11) - (u16) D_801D9070;
        func_8004315C(D_801E91F0, sp10, sp18);
        D_801D7810[i].x = sp18[0] << 2;
        D_801D7810[i].y = sp18[1] << 2;
        D_801D7810[i].z = sp18[2] << 2;
    }
}
