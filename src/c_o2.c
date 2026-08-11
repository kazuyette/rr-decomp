/* c_o2.c -- real-C conversions from units the retail EXE compiled at
 * -O2 (instruction scheduler ON: load-delay slots get filled with
 * neighboring increments, exactly what these functions' retail bytes
 * show), same -mmips-as/ASPSX-2.2x assembly path as c_o1.c, and the
 * same tools/aspsx_epilogue_swap.py step for the framed epilogues.
 * All verified byte-exact with objdiff before their __asm__
 * transcriptions were retired (round 68).
 *
 * The by-now-established picture: the retail EXE links units built
 * with (at least) -O1, -O1 -fno-delayed-branch, -O2, GCC 2.5.7 -O2,
 * and a pre-GCC Sony toolchain -- per-file flag rules in the Makefile
 * mirror that reality one file at a time. */

/* Byte copies (memcpy shape) -- three separately-linked instances of
 * the same routine in different regions of the EXE. */
void func_80047834(unsigned char *a0, unsigned char *a1, int a2)
{
    while (a2--) {
        *a0++ = *a1++;
    }
}

void func_80053FC8(unsigned char *a0, unsigned char *a1, int a2)
{
    while (a2--) {
        *a0++ = *a1++;
    }
}

void func_800579F4(unsigned char *a0, unsigned char *a1, int a2)
{
    while (a2--) {
        *a0++ = *a1++;
    }
}

/* Word copy, forward-counting flavor. */
void func_800554BC(int *a0, int *a1, unsigned int a2)
{
    unsigned int i = 0;
    while (i < a2) {
        *a0++ = *a1++;
        i++;
    }
}

/* Sprite/rect record init: three halfword coords, the four cleared
 * fields, two cleared bytes, and the stack-passed fifth argument into
 * the +6 slot (touched FIRST in source -- retail loads it before the
 * base-pointer copy). */
void *func_80048128(unsigned short *a0, int a1, int a2, int a3, int a4)
{
    int w = a4;
    unsigned short *r = a0;
    r[0] = a1;
    r[1] = a2;
    r[2] = a3;
    r[4] = 0;
    r[5] = 0;
    r[6] = 0;
    r[7] = 0;
    ((unsigned char *)r)[0x11] = 0;
    ((unsigned char *)r)[0x10] = 0;
    r[3] = w;
    return r;
}
