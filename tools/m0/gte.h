/* The PlayStation GTE (COP2), for the recompilation harness.
 *
 * Why it is written separately
 * ----------------------------
 * qemu does not know this coprocessor: the reference that validated the 836
 * integer functions has nothing to say here. The GTE's fidelity must therefore
 * be established some other way — against a second, independent
 * implementation, written from the same hardware documentation but in another
 * language and by another route. Two transcriptions of the same specification
 * do not go wrong in the same place; it is the only check available, and it is
 * better than nothing provided one says what it is worth.
 *
 * What is implemented
 * -------------------
 * The 22 operations the Ridge Racer binary actually uses, established by
 * counting the encodings across the 948 functions — not the 40 in the
 * catalogue. The rest would raise a plain error rather than return a wrong
 * result.
 */
#ifndef GTE_H
#define GTE_H
#include "rt.h"

typedef struct {
    /* Data registers, cop2r0..cop2r31. The names are the hardware's. */
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
    /* Control registers, cop2c0..cop2c31. */
    s16 RT[9];          /* rotation matrix */
    s32 TRX, TRY, TRZ;  /* translation */
    s16 LLM[9];         /* light matrix */
    s32 RBK, GBK, BBK;  /* background colour */
    s16 LCM[9];         /* colour matrix */
    s32 RFC, GFC, BFC;  /* far colour */
    s32 OFX, OFY;       /* screen offset */
    u16 H;              /* projection distance */
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
