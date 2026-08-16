/* Le GTE (COP2) du PlayStation, pour le banc de recompilation.
 *
 * Pourquoi il est écrit à part
 * ----------------------------
 * qemu ne connaît pas ce coprocesseur : la référence qui a validé les 836
 * fonctions entières ne peut rien dire ici. La fidélité du GTE doit donc être
 * établie autrement — contre une seconde implémentation indépendante, écrite
 * à partir de la même documentation matérielle mais dans un autre langage et
 * par un autre chemin. Deux transcriptions d'une même spécification ne se
 * trompent pas au même endroit ; c'est le seul contrôle disponible, et il vaut
 * mieux que rien pourvu qu'on dise ce qu'il vaut.
 *
 * Ce qui est implémenté
 * ---------------------
 * Les 22 opérations que le binaire de Ridge Racer utilise réellement, relevées
 * en comptant les encodages dans les 948 fonctions — pas les 40 du catalogue.
 * Le reste lèverait une erreur franche plutôt que de rendre un résultat faux.
 */
#ifndef GTE_H
#define GTE_H
#include "rt.h"

typedef struct {
    /* Registres de données, cop2r0..cop2r31. Les noms sont ceux du matériel. */
    s16 VX0, VY0, VZ0, VX1, VY1, VZ1, VX2, VY2, VZ2;
    u32 RGBC;
    u16 OTZ;
    s16 IR0, IR1, IR2, IR3;
    s16 SX0, SY0, SX1, SY1, SX2, SY2;
    u16 SZ0, SZ1, SZ2, SZ3;
    u32 RGB0, RGB1, RGB2;
    s32 RES1;
    s32 MAC0, MAC1, MAC2, MAC3;
    u32 IRGB, ORGB;
    s32 LZCS;
    s32 LZCR;
    /* Registres de contrôle, cop2c0..cop2c31. */
    s16 RT[9];          /* matrice de rotation */
    s32 TRX, TRY, TRZ;  /* translation */
    s16 LLM[9];         /* matrice de lumière */
    s32 RBK, GBK, BBK;  /* couleur de fond */
    s16 LCM[9];         /* matrice de couleur */
    s32 RFC, GFC, BFC;  /* couleur lointaine */
    s32 OFX, OFY;       /* décalage écran */
    u16 H;              /* distance de projection */
    s16 DQA;
    s32 DQB;
    s16 ZSF3, ZSF4;
    u32 FLAG;
} GTE;

extern GTE gte;

void gte_write_data(int reg, u32 v);
u32 gte_read_data(int reg);
void gte_write_ctrl(int reg, u32 v);
u32 gte_read_ctrl(int reg);
void gte_command(u32 code);

#endif
