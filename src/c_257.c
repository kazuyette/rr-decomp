/* c_257.c -- real-C conversions that byte-match ONLY under GCC 2.5.7
 * at -O2 (with the same -mmips-as/ASPSX-2.2x assembly path as the
 * other c_* files): their scheduled mask/load interleaving is
 * 2.5.7's instruction scheduler, demonstrably not 2.7.2's. The
 * toolchain image now builds both compilers (see
 * docker/toolchain.Dockerfile); the Makefile points PSX_GCC257_DIR at
 * the 2.5.7 install for THIS FILE ONLY.
 *
 * This makes the per-unit picture of the retail EXE: -O1 units,
 * an -O1 -fno-delayed-branch unit, -O2 units (all GCC 2.7.x-era),
 * and at least one GCC 2.5.7 -O2 unit (this one, libgpu-flavored),
 * plus the pre-GCC Sony-library regions that stay as verbatim
 * transcriptions. Both functions verified byte-exact with objdiff
 * before their __asm__ transcriptions were retired (round 69). */

extern unsigned int *D_80077394;
extern unsigned int D_800786C0[];

/* Masked merge: keep *a0's command byte, splice in *a1's 24-bit
 * payload. */
void func_80047AB8(unsigned int *a0, unsigned int *a1)
{
    *a0 = (*a0 & 0xFF000000) | (*a1 & 0xFFFFFF);
}

/* Write the raw word through the D_80077394 port and mirror its
 * 24-bit payload into the per-command slot of D_800786C0 (indexed by
 * the command byte). */
void func_8004703C(unsigned int a0)
{
    *D_80077394 = a0;
    D_800786C0[a0 >> 24] = a0 & 0xFFFFFF;
}
