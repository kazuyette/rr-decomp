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
