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

/* Sets GTE control registers 13/14/15 (RT/IR rotation-matrix related
 * fixed-point components), each shifted up from an integer argument. Same
 * shape as func_8003FC9C above, one more register. */
__asm__(
    ".global func_8003FBE8\n"
    "func_8003FBE8:\n"
    ".set noreorder\n"
    "sll $a0, $a0, 4\n"
    "sll $a1, $a1, 4\n"
    "sll $a2, $a2, 4\n"
    "ctc2 $a0, $13\n"
    "ctc2 $a1, $14\n"
    "ctc2 $a2, $15\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Three near-identical 5-word matrix loaders: reads a 5-word (20-byte)
 * struct from memory and writes it straight into a bank of 5 consecutive
 * GTE control registers (0-4, 8-12, 16-20 respectively) -- these are the
 * three rotation-matrix row/column banks (RT, plus two more, PSY-Q style
 * SetRotMatrix-ish helpers), byte-exact register-for-register copies. */
__asm__(
    ".global func_80043470\n"
    "func_80043470:\n"
    ".set noreorder\n"
    "lw $t0, 0x0($a0)\n"
    "lw $t1, 0x4($a0)\n"
    "lw $t2, 0x8($a0)\n"
    "lw $t3, 0xC($a0)\n"
    "lw $t4, 0x10($a0)\n"
    "ctc2 $t0, $0\n"
    "ctc2 $t1, $1\n"
    "ctc2 $t2, $2\n"
    "ctc2 $t3, $3\n"
    "ctc2 $t4, $4\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800434A0\n"
    "func_800434A0:\n"
    ".set noreorder\n"
    "lw $t0, 0x0($a0)\n"
    "lw $t1, 0x4($a0)\n"
    "lw $t2, 0x8($a0)\n"
    "lw $t3, 0xC($a0)\n"
    "lw $t4, 0x10($a0)\n"
    "ctc2 $t0, $8\n"
    "ctc2 $t1, $9\n"
    "ctc2 $t2, $10\n"
    "ctc2 $t3, $11\n"
    "ctc2 $t4, $12\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800434D0\n"
    "func_800434D0:\n"
    ".set noreorder\n"
    "lw $t0, 0x0($a0)\n"
    "lw $t1, 0x4($a0)\n"
    "lw $t2, 0x8($a0)\n"
    "lw $t3, 0xC($a0)\n"
    "lw $t4, 0x10($a0)\n"
    "ctc2 $t0, $16\n"
    "ctc2 $t1, $17\n"
    "ctc2 $t2, $18\n"
    "ctc2 $t3, $19\n"
    "ctc2 $t4, $20\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);
