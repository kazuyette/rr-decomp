/* c_o1_ndb.c -- real-C conversions whose retail bytes show the jr
 * delay slot left UNFILLED after a store (`sw / jr / nop` instead of
 * cc1's usual `jr / sw`): the unit they came from was compiled with
 * the delayed-branch pass off (-fno-delayed-branch), everything else
 * identical to c_o1.c's -O1/ASPSX-2.2x combo. See that file's header
 * for the full flag story; the Makefile gives THIS file the extra
 * flag. Both functions verified byte-exact with objdiff before their
 * __asm__ transcriptions were retired (round 68). */

extern unsigned int *D_800775A4;

/* Rewrite the command nibble of the word the D_800775A4 pointer
 * targets: keep 0xF0FFFFFF, set command 0x22 / 0x20. */
void func_80055510(void)
{
    unsigned int *p = D_800775A4;
    *p = (*p & 0xF0FFFFFF) | 0x22000000;
}

void func_80055540(void)
{
    unsigned int *p = D_800775A4;
    *p = (*p & 0xF0FFFFFF) | 0x20000000;
}
