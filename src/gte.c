/* GTE (Geometry Transformation Engine, COP2) control-register helpers.
 *
 * These are one or two COP2 instructions each -- standard PSY-Q SDK style
 * thin wrappers around ctc2/cfc2/mtc2/mfc2 (SetGeomScreen/SetGeomOffset-
 * style setters, and a leading-zero-count trick via LZCS/LZCR, GTE
 * registers 30/31). Old GCC 2.7.2 doesn't have COP2 intrinsics, and the
 * exact register/opcode encoding matters for a byte-exact match, so these
 * are written as top-level __asm__ blocks rather than C, the same
 * technique used for the BIOS trampolines in bios_trampolines.c. Verified
 * byte-exact against the target object with objdiff-cli.
 */

/* Sets GTE control register 26 (H, projection plane distance). */
__asm__(
    ".global func_8003FCB4\n"
    "func_8003FCB4:\n"
    ".set noreorder\n"
    "ctc2 $a0, $26\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Sets GTE control register 27 (DQA, depth cueing coefficient). */
__asm__(
    ".global func_8003FCC0\n"
    "func_8003FCC0:\n"
    ".set noreorder\n"
    "ctc2 $a0, $27\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Sets GTE control registers 24/25 (OFX/OFY, screen offset), each taking
 * a 16.16 fixed-point argument shifted up from an integer input. */
__asm__(
    ".global func_8003FC9C\n"
    "func_8003FC9C:\n"
    ".set noreorder\n"
    "sll $a0, $a0, 16\n"
    "sll $a1, $a1, 16\n"
    "ctc2 $a0, $24\n"
    "ctc2 $a1, $25\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Negates GTE control register 5 (BK/leftover-vector component) in place. */
__asm__(
    ".global func_80043794\n"
    "func_80043794:\n"
    ".set noreorder\n"
    "cfc2 $t0, $5\n"
    "nop\n"
    "neg $t0, $t0\n"
    "ctc2 $t0, $5\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Leading-zero-count trick: writing a value to GTE data register 30 (LZCS)
 * makes register 31 (LZCR) return its leading-zero (or leading-one, for
 * negative input) count -- a fast hardware CLZ used for fixed-point
 * normalization. */
__asm__(
    ".global func_80044078\n"
    "func_80044078:\n"
    ".set noreorder\n"
    "mtc2 $a0, $30\n"
    "nop\n"
    "nop\n"
    "mfc2 $v0, $31\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);
