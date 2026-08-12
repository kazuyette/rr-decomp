/* c_o1.c -- real-C conversions that byte-match under the ORIGINAL
 * compiler settings discovered in round 67: GCC at -O1 with -mmips-as
 * (cc1 emits assembler MACRO forms -- `sb $zero,SYM`, `lw $2,SYM($4)`,
 * one-insn `li` -- and does NOT run the instruction scheduler), then
 * maspsx in --aspsx-version 2.21 mode, whose ASPSX-2.2x macro
 * expansion (lui $at / addiu $at,%lo / addu / op 0($at)) is exactly
 * the addressing shape the retail binary shows. This repo's
 * historical -O2 -mgas flags split %hi/%lo in cc1 and schedule
 * instructions, which is measurably NOT what the retail EXE contains.
 *
 * The Makefile compiles and assembles THIS FILE ONLY with that combo
 * (see the c_o1 target-specific rules); everything previously matched
 * keeps its original flags, so this file lands with zero regressions.
 * Every function here was verified byte-exact (objdiff 100.0) against
 * the retail PSX.EXE before its __asm__ transcription was retired.
 *
 * Bonus finding, same round: func_80047AB8 byte-matches ONLY under
 * GCC 2.5.7 at -O2 -- its scheduled mask/load interleaving is
 * 2.5.7's scheduler, not 2.7.2's (landed in c_257.c once the
 * toolchain grew a second compiler, round 69). And three functions (func_8004D388 / func_8004D3A4 /
 * func_80043204, all in Sony-library regions of the EXE) match NO
 * available GCC at any flag set: their branch-preserving 0/-1
 * select into the argument register and $t0-$t2 block-copy with a
 * trailing return move are signatures of the pre-GCC-era toolchain
 * Sony built its launch-window libraries with. Those stay as
 * verbatim transcriptions, same category as the GTE accessors. */

extern unsigned char D_800772A0;
extern unsigned char D_80173440;
extern unsigned char D_801734A8;
extern unsigned char D_801D7E50;
extern unsigned char D_800775E8;
extern short *D_8007758C;
extern short D_801D77EE;
extern int D_8007469C[];
extern int D_800786C0[];
extern int D_801E90E8[];

/* --- GPU packet field helpers (0x47xxx: the libgpu-style region) --- */

/* Force the 24-bit payload of the word at *p to all-ones, keeping the
 * top (command) byte. */
void func_80047AE0(unsigned int *a0)
{
    *a0 |= 0xFFFFFF;
}

/* 24-bit payload | high command bit / all-ones test (the xor+sltiu
 * equality idiom is GCC's own codegen). */
int func_80047A08(unsigned int *a0)
{
    return (*a0 & 0xFFFFFF) | 0x80000000;
}

int func_80047A24(unsigned int *a0)
{
    return (*a0 & 0xFFFFFF) == 0xFFFFFF;
}

/* Primitive initializers: length byte at +3, command code at +7,
 * 0x55555555 pattern word at the per-code payload offset. */
void func_80047CC4(unsigned char *a0)
{
    a0[3] = 7;
    a0[7] = 0x58;
    *(unsigned int *)(a0 + 0x1C) = 0x55555555;
}

void func_80047CE4(unsigned char *a0)
{
    a0[3] = 6;
    a0[7] = 0x4C;
    *(unsigned int *)(a0 + 0x18) = 0x55555555;
}

void func_80047D04(unsigned char *a0)
{
    a0[3] = 9;
    a0[7] = 0x5C;
    *(unsigned int *)(a0 + 0x24) = 0x55555555;
}

/* Table lookup fused with a tag: entry | (index << 24). The load
 * lands in a temp FIRST (source order matters for the -O1 delay-slot
 * fill: the shift ends up in the load-delay/branch-delay position
 * exactly as retail). */
int func_80047074(int a0)
{
    int t = D_800786C0[a0];
    return (a0 << 24) | t;
}

/* --- game-state setters (0x3Axxx family) -- all VOID: the li $v0,1
 * visible before the second store in the retail bytes is the store
 * VALUE being materialized, not a return value (writing these as
 * `return 1` adds a duplicated li in the jr delay slot that retail
 * does not have -- found the hard way, round 67). --- */

void func_8003A1BC(void)
{
    D_800772A0 = 0;
    D_80173440 = 1;
}

void func_8003A588(void)
{
    D_801734A8 = 0;
    D_800772A0 = 1;
}

void func_8003A5E4(void)
{
    D_801D7E50 = 0;
    D_800772A0 = 2;
}

void func_8003A640(void)
{
    D_801D7E50 = 0;
    D_800772A0 = 3;
}

/* Plain table read -- cc1 emits the `lw $2,D_8007469C($4)` macro form
 * and ASPSX 2.2x expands it with the addiu-$at shape. */
int func_80030F14(int a0)
{
    return D_8007469C[a0];
}

/* Clear the 8-halfword block ENDING at D_801D77EE, walking backwards
 * (counter initialized before the pointer -- that source order is
 * what puts the loop counter in $v1 like retail). */
void func_80030DBC(void)
{
    int i = 7;
    short *p = &D_801D77EE;
    do {
        *p-- = 0;
        i--;
    } while (i >= 0);
}

/* --- sound/slot helpers --- */

/* Halfword poke through the D_8007758C pointer; always returns 0. */
int func_8005761C(int a0, int a1)
{
    D_8007758C[a0] = a1;
    return 0;
}

/* Clamped byte setter: values 0..0x18 latch into D_800775E8 and echo
 * back via a reload (as retail does); anything else returns 0xFF. */
int func_8004D72C(unsigned char a0)
{
    if (a0 < 0x19) {
        D_800775E8 = a0;
        return D_800775E8;
    }
    return 0xFF;
}

/* Set bit 2 in the word at +0x90 of the object the D_801E90E8 table
 * points at for this (signed 16-bit) slot index. */
void func_8005160C(short a0)
{
    int *p = (int *)D_801E90E8[a0];
    p[36] |= 4;
}


/* ------- round 68 additions (same O1/ASPSX-2.2x combo, now with the
 * tools/aspsx_epilogue_swap.py step: framed functions' `addu $sp / j`
 * epilogues get the stack restore swapped into the jump delay slot,
 * which is what the real ASPSX reorderer did and maspsx does not) --- */

extern unsigned int *D_80077394;
extern unsigned int *D_80077390;
extern short D_80079A1A[];
extern short D_80079A1C[];
extern int D_80076C0C[];
extern int D_80076C80[];
extern int D_8007746C;
extern int D_801D7F58;

/* Write the tagged word through the D_80077394 port, read the reply
 * payload back through D_80077390. */
int func_80047154(unsigned int a0)
{
    *D_80077394 = a0 | 0x10000000;
    return *D_80077390 & 0xFFFFFF;
}

/* Bounded reads into the 8-byte-stride D_80079A18 record table (the
 * +2/+4 fields via their own symbols); -1 when out of range. The
 * `int i = a0` promotion is what keeps the sign-extension in the
 * argument register like retail. */
int func_8004B898(short a0)
{
    int i = a0;
    if (i < 0x22) {
        return *(short *)((unsigned char *)D_80079A1A + (i << 3));
    }
    return -1;
}

int func_8004B8CC(short a0)
{
    int i = a0;
    if (i < 0x22) {
        return *(short *)((unsigned char *)D_80079A1C + (i << 3));
    }
    return -1;
}

/* Bounded table getters falling back to the shared default slot; the
 * inverted `>=` test is what produces retail's beqz layout. */
int func_80051BFC(unsigned int a0)
{
    a0 &= 0xFF;
    if (a0 >= 0x1C) {
        return (int)&D_8007746C;
    }
    return D_80076C0C[a0];
}

int func_80051C34(unsigned int a0)
{
    a0 &= 0xFF;
    if (a0 >= 0x7) {
        return (int)&D_8007746C;
    }
    return D_80076C80[a0];
}

/* Byte fill (memset shape); the bare sp,-8 frame is cc1's own doing
 * for this loop form, matched as-is. */
void func_80047864(unsigned char *a0, unsigned char a1, int a2)
{
    while (a2--) {
        *a0++ = a1;
    }
}

/* Count the non-empty slots of the 6-entry, 0x38-stride table at
 * D_801D7F58 (statement order inside the do-loop matters: decrement,
 * advance, then accumulate -- that is retail's emission order). */
int func_80039CD0(void)
{
    unsigned char *p = (unsigned char *)&D_801D7F58;
    int n = 0;
    int i = 5;
    do {
        int v = *(int *)p;
        i--;
        p += 0x38;
        n += v != 0;
    } while (i >= 0);
    return n;
}

/* Reads the D_80173440 flag through a frame the original allocated
 * for a since-compiled-out local (24 bytes of dead stack, faithfully
 * reproduced by the unused buffer). */
int func_8003A198(void)
{
    unsigned char buf[24];
    return D_80173440;
}

/* ------- round 70 addition (same O1/ASPSX-2.2x combo) --- */

extern unsigned char D_800797EF[];
extern unsigned char D_800797DC[];
extern void *D_8007745C;

/* Clear the (a0&0xFF)-th 24-byte-stride "reserved" slot: its status
 * byte in D_800797EF, its halfword tag in D_800797DC, and the two
 * halfword fields at +0x194/+0x196 of the object *D_8007745C points
 * at. The D_8007745C load has to happen BEFORE the D_800797DC store
 * in source order -- that's what puts it in $v1 like retail instead
 * of getting re-loaded after. */
void func_8004A8D0(int a0)
{
    int idx = (a0 & 0xFF) * 24;
    unsigned char *p;
    D_800797EF[idx] = 0;
    p = (unsigned char *)D_8007745C;
    *(unsigned short *)(D_800797DC + idx) = 0;
    *(unsigned short *)(p + 0x194) = 0;
    *(unsigned short *)(p + 0x196) = 0;
}

/* ------- round 71 addition (same O1/ASPSX-2.2x combo) --- */

/* Same D_801E90E8[a0] + a1*168-stride object family as func_8005160C /
 * func_8005163C: clear the "active" byte at +0x2B and clear bit 0x100
 * of the flags word at +0x90. The two field accesses each re-index
 * D_801E90E8[a0] from scratch (matches retail's redundant reload); the
 * FIRST access needs the base pointer named as a local (loaded before
 * the stride's `+a1` finishes, landing in $v0 like retail) while the
 * second is a fresh inline expression -- mixing the two forms is what
 * reproduces the exact instruction order. */
void func_8005188C(short a0, short a1)
{
    int v1;
    int *p;
    v1 = a1 * 20;
    p = (int *)D_801E90E8[a0];
    *(unsigned char *)((unsigned char *)p + (v1 + a1) * 8 + 0x2B) = 0;
    *(unsigned int *)((unsigned char *)D_801E90E8[a0] + (v1 + a1) * 8 + 0x90) &= ~0x100;
}

/* ------- round 72 addition (same O1/ASPSX-2.2x combo) --- */

/* Pure delay/timing loop: counts up by 3 from 0 to 0x1770 (6000) in a
 * do-while (the do-while shape is what materializes the "overshoot
 * subtract 3 back off" instruction retail has after the loop exits --
 * a plain while/for form folds the init to a single `li` and drops
 * the trailing correction instead). No side effects; the count itself
 * is dead once the loop exits, so this is a CPU-cycle spin-wait. */
void func_8004DC18(void)
{
    int v1 = 0;
    do {
        v1 += 3;
    } while (v1 < 0x1770);
}

/* ------- round 73 addition (same O1/ASPSX-2.2x combo) --- */

extern short D_801D7778[];
extern short D_800742D8[];
extern short D_80074298[];

/* Interleaved 8-halfword copy: two source tables indexed by a0*16 and
 * a1*16 (16-byte-stride records) are copied in lockstep into the two
 * halves of the 8-halfword scratch buffer D_801D7778 (dst0) / +0x10
 * (dst1). The base-address loads for src0/src1 have to happen as
 * their OWN statements (named `base0`/`base1`) BEFORE combining with
 * the `*16` index -- same "load the dependency before finishing the
 * scaled add" shape as func_8004A8D0/func_8005188C -- and the loop
 * counter increment has to be written INLINE right after advancing
 * src0 (not left as the for-loop's own post-body increment), which
 * is what reproduces retail's exact interleaving of the two stores'
 * pointer bookkeeping. */
void func_8002E6A8(int a0, int a1)
{
    int i;
    short *dst0;
    short *dst1;
    char *base1;
    char *base0;
    short *src1;
    short *src0;
    short v0;
    i = 0;
    dst0 = D_801D7778;
    dst1 = (short *)((char *)dst0 + 0x10);
    base1 = (char *)D_800742D8;
    src1 = (short *)(base1 + a1 * 16);
    base0 = (char *)D_80074298;
    src0 = (short *)(base0 + a0 * 16);
    while (i < 8) {
        v0 = *src0;
        *dst0 = v0;
        v0 = *src1;
        src0++;
        i++;
        src1++;
        dst0++;
        *dst1 = v0;
        dst1++;
    }
}

/* ------- round 74 addition (same O1/ASPSX-2.2x combo) --- */
/* nested double do-while: outer 2 iterations (a0 = 0, 1), inner 256
 * iterations counting down (v1: 0xFF -> 0), filling a 0x100-byte block
 * of D_801D7C10 with the current a0 value. Same "delay loop" family as
 * func_8004DC18 (round 72): do-while with a separate zero-init statement
 * reproduces retail's post-loop compensating decrement in the delay
 * slot, and it nests cleanly for the outer counter too. */
extern unsigned char D_801D7C10[];
extern int D_801D9058;
void func_8003776C(void)
{
    int a0;
    int v1;
    unsigned char *v0;
    unsigned char *a1;
    a0 = 0;
    a1 = D_801D7C10;
    do {
        v1 = 0xFF;
        v0 = a1 + 0xFF;
        do {
            *v0 = a0;
            v1--;
            v0--;
        } while (v1 >= 0);
        a0++;
        a1 += 0x100;
    } while (a0 < 2);
    D_801D9058 = -1;
}

/* ------- round 75 addition (same O1/ASPSX-2.2x combo) --- */
/* two independent countdown-zeroing loops over D_800797A0 (7 words) and
 * D_800797D0 (11 words), plus two dependent-global clears up front.
 * D_8007744C's store is placed AFTER computing v1/a0 for the first loop
 * in the C source, but its POINTER LOAD happens first -- naming the
 * loaded pointer explicitly (`p = D_8007744C;`) lets the compiler emit
 * the lui/lw early while deferring the actual `sw` until after the loop
 * setup, matching retail's "load container pointer before the store
 * that uses the other indexed variable" ordering (same recipe as the
 * D_801E90E8[a0]+stride family). */
extern short *D_80077444;
extern int *D_8007744C;
extern int D_800797A0[];
extern int D_800797D0[];
void func_80049580(void)
{
    int v1;
    int *a0;
    int *v0;
    int *p;
    *D_80077444 = 0;
    p = D_8007744C;
    v1 = 6;
    a0 = D_800797A0;
    *p = 0;
    do {
        *a0 = 0;
        v1--;
        a0--;
    } while (v1 >= 0);
    v1 = 10;
    v0 = D_800797D0;
    do {
        *v0 = 0;
        v1--;
        v0--;
    } while (v1 >= 0);
}


/* round 81 -- 92-byte struct copy from a fixed global template
 * (D_80078248) into the caller-provided buffer, returned unchanged.
    * A plain word-copy loop never reached the register pressure retail
 * shows (8 scratch registers live at once, including a forced reuse
 * of $a0); writing it as a whole-struct assignment let cc1 -O1
    * generate the same 4-word-unrolled loop + 3-word remainder retail
 * has, first try. */
   typedef struct { int w[23]; } S_80045D04;
extern S_80045D04 D_80078248;

void *func_80045D04(void *a0)
{
       *(S_80045D04 *)a0 = D_80078248;
    return a0;
}
