/* Small state-flag / trivial-wrapper functions, grouped here because each
 * is a couple of instructions touching module-level globals rather than
 * belonging to one clearly-named subsystem file yet. Verified byte-exact
 * against the target object with objdiff-cli before being added here. */

extern int D_8007C518;
extern int D_801E90B0;
extern int D_8012D900;
extern int D_801D7E78;
extern short D_8007729E;
extern signed char D_800772A0;
extern signed char D_80173440;
extern int *D_80077394;
extern int D_801D7E40;
extern int D_801E9170;
extern int D_801D7600;
extern signed char D_801D35C0;
extern signed char D_801D35C1;
extern signed char D_801D35C2;
extern signed char D_801D35C3;
extern short D_800775F8;
extern int D_8012CDA8;
extern int D_8007C268;
extern int D_8007C270;
extern int D_80077374;
extern int D_80077378;
extern int D_80077380;
extern int D_80077474;
extern int D_80076E04;
extern short D_80077460;
extern short D_80077462;
extern short D_80079B74;

extern void func_80032A54(void);

/* Zeroes two globals -- looks like a "reset" step for some subsystem whose
 * other half is func_8001CDA8 below. */
void func_8001CD90(void) {
    D_8007C518 = 0;
    D_801E90B0 = 0;
}

/* Companion to func_8001CD90: sets the same D_801E90B0 global to a fixed
 * value (0x78 = 120), likely a timeout/countdown reload. */
void func_8001CDA8(void) {
    D_801E90B0 = 0x78;
}

/* Thin wrapper: calls func_80032A54 for its side effects and always
 * returns 0. */
int func_80032DF8(void) {
    func_80032A54();
    return 0;
}

/* Another two-global reset, same shape as func_8001CD90 but different
 * globals -- likely a sibling subsystem's init/reset routine. */
void func_80032E18(void) {
    D_8012D900 = 0;
    D_801D7E78 = 0;
}

/* Single-field setter: stores its argument into a module-level short. */
void func_8003A1AC(short a0) {
    D_8007729E = a0;
}

/* Sets a small state machine back to its "idle" value: flag byte cleared,
 * companion byte set to 1. */
void func_8003A65C(void) {
    D_80173440 = 1;
    D_800772A0 = 0;
}

/* Absolute difference of two values. */
int func_80021FA4(int a0, int a1) {
    return (a1 < a0) ? (a0 - a1) : (a1 - a0);
}

/* Dereferences a module-level pointer variable. */
int func_8004713C(void) {
    return *D_80077394;
}

/* "Set and return old value" accessors -- same shape, three different
 * globals, likely per-object/per-channel state slots. */
int func_80051CCC(int a0) {
    int old = D_801D7E40;
    D_801D7E40 = a0;
    return old;
}

int func_80051CE4(int a0) {
    int old = D_801E9170;
    D_801E9170 = a0;
    return old;
}

int func_80051CFC(int a0) {
    int old = D_801D7600;
    D_801D7600 = a0;
    return old;
}

/* Stores four byte arguments into four consecutive globals -- likely
 * unpacking a small struct/tuple (e.g. RGBA-ish config) field by field. */
void func_80039D88(signed char a0, signed char a1, signed char a2, signed char a3) {
    D_801D35C0 = a0;
    D_801D35C1 = a1;
    D_801D35C2 = a2;
    D_801D35C3 = a3;
}

/* Toggles a flag bit (0x2) in a byte field at offset 7 of some struct,
 * based on the boolean argument. */
void func_80047AF8(unsigned char *a0, int a1) {
    if (a1) {
        a0[7] |= 2;
    } else {
        a0[7] &= 0xFD;
    }
}

/* Fixed-size (8-byte) memcpy, guarded by a null-destination check. */
void func_80052410(char *a0, char *a1) {
    int v1;
    if (a0 == 0) return;
    v1 = 7;
    do {
        *a0++ = *a1++;
    } while (v1-- != 0);
}

/* Minimal circular distance between two values on a 0x1000-unit wraparound
 * scale (the game's standard angle/position wrap unit) -- same body used
 * at two call sites (func_80019C6C and func_80038264). */
int func_80019C6C(int a0, int a1) {
    int v1 = a0 & 0xFFF;
    int b  = a1 & 0xFFF;
    int d = (v1 < b) ? (b - v1) : (v1 - b);
    if (d >= 0x801) {
        d = 0x1000 - d;
    }
    return d;
}

int func_80038264(int a0, int a1) {
    int v1 = a0 & 0xFFF;
    int b  = a1 & 0xFFF;
    int d = (v1 < b) ? (b - v1) : (v1 - b);
    if (d >= 0x801) {
        d = 0x1000 - d;
    }
    return d;
}

/* libgpu primitive initialisers: store the packet length at byte 3 of the
 * tag and the GPU command code at byte 7 -- PSY-Q's setlen()/setcode() pair,
 * i.e. the SetPolyF3 / SetSprt / SetTile family. Nineteen of them sit
 * consecutively at 0x80047B48..0x80047CB0; the four below were converted
 * first, the rest follow at the end of this file.
 *
 * The (len, code) pairs are ground truth, read from the disassembly. The
 * PSY-Q names in the trailing comments are inferred from the codes and want
 * checking against libgpu's headers before anything gets renamed in
 * symbol_addrs.txt -- the line and tile codes are easy to get backwards. */
void func_80047B98(unsigned char *a0) {
    a0[3] = 5;
    a0[7] = 0x28;
}

void func_80047BAC(unsigned char *a0) {
    a0[3] = 9;
    a0[7] = 0x2C;
}

void func_80047BC0(unsigned char *a0) {
    a0[3] = 8;
    a0[7] = 0x38;
}

void func_80047BD4(unsigned char *a0) {
    a0[3] = 0xC;
    a0[7] = 0x3C;
}

/* Sets a fixed mode/state value (2) into a module-level short. */
void func_8004A4B8(void) {
    D_800775F8 = 2;
}

/* Selects between two fixed states depending on whether the argument is 1. */
void func_80059014(int a0) {
    if (a0 == 1) {
        D_8012CDA8 = 0;
    } else {
        D_8012CDA8 = 1;
    }
}

/* Range check: true if a0[1] and a0[3] both fall within +-0x40 of two
 * separate reference globals (likely a camera/culling-box style test). */
int func_800397A4(int *a0) {
    int result = 0;
    if (D_8007C268 - 0x40 < a0[1] && a0[1] < D_8007C268 + 0x40) {
        if (D_8007C270 - 0x40 < a0[3]) {
            result = a0[3] < D_8007C270 + 0x40;
        }
    }
    return result;
}

/* The four functions below are logically simple (a chained pointer store,
 * a 16-byte struct copy + counter decrement, five global stores, and a
 * bitfield-packing store), but old GCC 2.7.2 -O2 never reproduces their
 * exact instruction order/register allocation from natural C source: it
 * reorders independent stores by grouping same-shape immediate loads
 * together, picks different scratch registers for a struct copy, and
 * CSEs a repeated `& 0x8000` mask into a shared register where the
 * original PSY-Q output just re-issued andi twice. Written as raw
 * __asm__ (transcribed straight from the target disassembly) instead of
 * fighting the scheduler -- verified byte-exact with objdiff-cli. */

/* Points two globals at the same static buffer, resets three counters --
 * likely a "next free slot" / list-head reinit. */
__asm__(
    ".global func_80037FD0\n"
    "func_80037FD0:\n"
    ".set noreorder\n"
    "lui $v0, %hi(D_800747FC)\n"
    "addiu $v0, $v0, %lo(D_800747FC)\n"
    "lui $at, %hi(D_801D80AC)\n"
    "sw $v0, %lo(D_801D80AC)($at)\n"
    "lui $at, %hi(D_801D80A8)\n"
    "sw $v0, %lo(D_801D80A8)($at)\n"
    "addiu $v0, $zero, -1\n"
    "lui $at, %hi(D_801D80B0)\n"
    "sh $v0, %lo(D_801D80B0)($at)\n"
    "lui $at, %hi(D_801D811C)\n"
    "sw $zero, %lo(D_801D811C)($at)\n"
    "ori $v0, $zero, 1\n"
    "lui $at, %hi(D_801D8120)\n"
    "sw $v0, %lo(D_801D8120)($at)\n"
    "lui $at, %hi(D_8012CDE8)\n"
    "sw $zero, %lo(D_8012CDE8)($at)\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Copies a fixed 16-byte record from one global buffer to another, then
 * decrements a companion counter by 0x3C (60) -- looks like popping a
 * fixed-size entry off some queue/ring while advancing a byte cursor. */
__asm__(
    ".global func_8002CDBC\n"
    "func_8002CDBC:\n"
    ".set noreorder\n"
    "lui $a1, %hi(D_8007C268)\n"
    "addiu $a1, $a1, %lo(D_8007C268)\n"
    "lui $a0, %hi(D_801E90D0)\n"
    "addiu $a0, $a0, %lo(D_801E90D0)\n"
    "lw $v0, 0x0($a1)\n"
    "lw $v1, 0x4($a1)\n"
    "sw $v0, 0x0($a0)\n"
    "sw $v1, 0x4($a0)\n"
    "lw $v0, 0x8($a1)\n"
    "lw $v1, 0xC($a1)\n"
    "sw $v0, 0x8($a0)\n"
    "sw $v1, 0xC($a0)\n"
    "lui $v0, %hi(D_801E90D4)\n"
    "lw $v0, %lo(D_801E90D4)($v0)\n"
    "nop\n"
    "addiu $v0, $v0, -0x3C\n"
    "lui $at, %hi(D_801E90D4)\n"
    "sw $v0, %lo(D_801E90D4)($at)\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Five-global reset/init routine: sets a mode word, stashes the argument
 * pointer, zeroes a flag, sets a countdown to -0x20, and sets another
 * mode word to 4. */
__asm__(
    ".global func_80015CD4\n"
    "func_80015CD4:\n"
    ".set noreorder\n"
    "ori $v0, $zero, 0xF000\n"
    "lui $at, %hi(D_801733A0)\n"
    "sw $v0, %lo(D_801733A0)($at)\n"
    "lui $at, %hi(D_801D82D0)\n"
    "sw $a0, %lo(D_801D82D0)($at)\n"
    "lui $at, %hi(D_801D7620)\n"
    "sw $zero, %lo(D_801D7620)($at)\n"
    "addiu $v0, $zero, -0x20\n"
    "lui $at, %hi(D_8007C208)\n"
    "sw $v0, %lo(D_8007C208)($at)\n"
    "ori $v0, $zero, 4\n"
    "lui $at, %hi(D_801D82C8)\n"
    "sw $v0, %lo(D_801D82C8)($at)\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Packs two 16-bit inputs into 9 bitfields of a destination struct --
 * sign bits, a couple of flag bits, and split high/mid/low nibbles of
 * each input, PSY-Q SDK style (looks like a fixed-point vector -> GPU
 * primitive packing routine). */
__asm__(
    ".global func_8005102C\n"
    "func_8005102C:\n"
    ".set noreorder\n"
    "andi $v0, $a0, 0x8000\n"
    "sh $v0, 0xA($a2)\n"
    "andi $v0, $a1, 0x8000\n"
    "sh $v0, 0xC($a2)\n"
    "andi $v0, $a1, 0x4000\n"
    "sh $v0, 0x10($a2)\n"
    "andi $v0, $a1, 0x20\n"
    "sh $v0, 0xE($a2)\n"
    "andi $v1, $a0, 0xFFFF\n"
    "srl $v0, $v1, 8\n"
    "andi $v0, $v0, 0x7F\n"
    "sh $v0, 0x0($a2)\n"
    "srl $v1, $v1, 4\n"
    "andi $v1, $v1, 0xF\n"
    "sh $v1, 0x2($a2)\n"
    "andi $a0, $a0, 0xF\n"
    "sh $a0, 0x4($a2)\n"
    "srl $v0, $a1, 6\n"
    "andi $v0, $v0, 0x7F\n"
    "sh $v0, 0x6($a2)\n"
    "andi $a1, $a1, 0x1F\n"
    "jr $ra\n"
    "sh $a1, 0x8($a2)\n"
    ".set reorder\n"
);

/* Remainder of the libgpu primitive initialiser family (see the note above
 * func_80047B98). Same shape and same flags as the four already converted,
 * which is why they belong in this file rather than c_o2.c. */
void func_80047B48(unsigned char *a0) {
    a0[3] = 4;
    a0[7] = 0x20;
}

void func_80047B5C(unsigned char *a0) {
    a0[3] = 7;
    a0[7] = 0x24;
}

void func_80047B70(unsigned char *a0) {
    a0[3] = 6;
    a0[7] = 0x30;
}

void func_80047B84(unsigned char *a0) {
    a0[3] = 9;
    a0[7] = 0x34;
}

void func_80047BE8(unsigned char *a0) {
    a0[3] = 3;
    a0[7] = 0x74;
}

void func_80047BFC(unsigned char *a0) {
    a0[3] = 3;
    a0[7] = 0x7C;
}

void func_80047C10(unsigned char *a0) {
    a0[3] = 4;
    a0[7] = 0x64;
}

void func_80047C24(unsigned char *a0) {
    a0[3] = 2;
    a0[7] = 0x68;
}

void func_80047C38(unsigned char *a0) {
    a0[3] = 2;
    a0[7] = 0x70;
}

void func_80047C4C(unsigned char *a0) {
    a0[3] = 2;
    a0[7] = 0x78;
}

void func_80047C60(unsigned char *a0) {
    a0[3] = 3;
    a0[7] = 0x60;
}

void func_80047C74(unsigned char *a0) {
    a0[3] = 3;
    a0[7] = 0x02;
}

void func_80047C88(unsigned char *a0) {
    a0[3] = 3;
    a0[7] = 0x40;
}

void func_80047C9C(unsigned char *a0) {
    a0[3] = 4;
    a0[7] = 0x50;
}

void func_80047CB0(unsigned char *a0) {
    a0[3] = 5;
    a0[7] = 0x48;
}

/* ------------------------------------------------------------------ */
/* Second batch of trivial accessors, same shapes as the ones already   */
/* converted above -- plain stores, plain loads, set-and-return-old,    */
/* and two constant returns. Nothing here is inferred: each is a        */
/* one-to-one transcription of four or five instructions.               */
/* ------------------------------------------------------------------ */

/* Halfword stores, companions to func_8003A1AC. */
void func_8004984C(void) {
    D_80077460 = 0;
}

void func_8004985C(short a0) {
    D_80077462 = a0;
}

void func_8004A4CC(void) {
    D_800775F8 = 0;
}

/* Word store. */
void func_800534B8(int a0) {
    D_80076E04 = a0;
}

/* "Set and return old value", same shape as func_80051CCC and friends. */
int func_80045738(int a0) {
    int old = D_80077380;
    D_80077380 = a0;
    return old;
}

int func_80051BE4(int a0) {
    int old = D_80077474;
    D_80077474 = a0;
    return old;
}

/* Plain getters. */
int func_80045718(void) {
    return D_80077378;
}

int func_80045728(void) {
    return D_80077374;
}

short func_8004D460(void) {
    return D_80079B74;
}

/* Constant returns -- capability/version stubs, most likely. */
int func_80055800(void) {
    return 3;
}

int func_80055808(void) {
    return 1;
}
