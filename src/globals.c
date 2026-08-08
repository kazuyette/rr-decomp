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

/* Four small "set object state to preset N" setters -- same two-field shape
 * (a type/kind byte at offset 3, a companion byte at offset 7), each with
 * its own pair of constants. Likely an enum-indexed table if disassembled
 * further, but each is its own tiny function here. */
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
