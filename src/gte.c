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

/* ---------------------------------------------------------------------
 * GTE data-register accessors, added after the control-register ones
 * above. Same rationale, same certainty: each is two or three COP2
 * instructions and the register number is written in the instruction, so
 * the identification needs no SDK -- only the documented hardware table.
 *
 * These stay as __asm__ because GCC 2.7.2 has no COP2 intrinsics; PSY-Q's
 * own headers wrapped exactly these instructions in macros for the same
 * reason. That makes this the authentic shape of the original source
 * rather than a transcription dressed up as C -- a distinction the
 * repository paid for once already, and one tools/progress.py now counts
 * separately so the figure cannot flatter itself.
 * --------------------------------------------------------------------- */

/* Writes GTE data registers IR1, IR2, IR3 (vector accumulator X). */
__asm__(
    ".global func_8003FBC8\n"
    "func_8003FBC8:\n"
    ".set noreorder\n"
    "mtc2 $a0, $9\n"
    "mtc2 $a1, $10\n"
    "mtc2 $a2, $11\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Writes GTE data register IR0 (interpolation accumulator). */
__asm__(
    ".global func_8003FBDC\n"
    "func_8003FBDC:\n"
    ".set noreorder\n"
    "mtc2 $a0, $8\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Writes GTE data registers SZ1, SZ2, SZ3 (screen Z FIFO). */
__asm__(
    ".global func_8003FC28\n"
    "func_8003FC28:\n"
    ".set noreorder\n"
    "mtc2 $a0, $17\n"
    "mtc2 $a1, $18\n"
    "mtc2 $a2, $19\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Writes GTE data registers SZ0, SZ1, SZ2, SZ3 (screen Z FIFO). */
__asm__(
    ".global func_8003FC3C\n"
    "func_8003FC3C:\n"
    ".set noreorder\n"
    "mtc2 $a0, $16\n"
    "mtc2 $a1, $17\n"
    "mtc2 $a2, $18\n"
    "mtc2 $a3, $19\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Writes GTE data registers SXY0, SXY1, SXY2 (screen XY FIFO). */
__asm__(
    ".global func_8003FC54\n"
    "func_8003FC54:\n"
    ".set noreorder\n"
    "mtc2 $a0, $12\n"
    "mtc2 $a1, $13\n"
    "mtc2 $a2, $14\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Writes GTE data registers MAC1, MAC2, MAC3 (vector X accumulator). */
__asm__(
    ".global func_8003FC7C\n"
    "func_8003FC7C:\n"
    ".set noreorder\n"
    "mtc2 $a0, $25\n"
    "mtc2 $a1, $26\n"
    "mtc2 $a2, $27\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Writes GTE data register LZCS (leading-zero count source). */
__asm__(
    ".global func_8003FC90\n"
    "func_8003FC90:\n"
    ".set noreorder\n"
    "mtc2 $a0, $30\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Reads GTE data register OTZ (average Z for the ordering table). */
__asm__(
    ".global func_8003FCD8\n"
    "func_8003FCD8:\n"
    ".set noreorder\n"
    "mfc2 $v0, $7\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Reads GTE data register IR0 (interpolation accumulator). */
__asm__(
    ".global func_8003FCE4\n"
    "func_8003FCE4:\n"
    ".set noreorder\n"
    "mfc2 $v0, $8\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Reads GTE data register MAC0 (sum-of-products accumulator). */
__asm__(
    ".global func_8003FD64\n"
    "func_8003FD64:\n"
    ".set noreorder\n"
    "mfc2 $v0, $24\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Reads GTE data register LZCR (leading-zero count result). */
__asm__(
    ".global func_8003FDB4\n"
    "func_8003FDB4:\n"
    ".set noreorder\n"
    "mfc2 $v0, $31\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);


/* ---------------------------------------------------------------------
 * The remaining control-register accessors. Seven functions, and the
 * register table they rely on was established from the code rather than
 * taken on trust: a published table fetched for this purpose turned out to
 * be wrong, expanding each matrix element into its own register where the
 * hardware packs two per 32-bit word.
 *
 * What settles it is the grouping. Registers 5-7 are written as a triple
 * and 21-23 as another, which is what a vector and a colour look like;
 * 24/25 and 26 match the comments already in this file from earlier work.
 * And the translation setter reads its source at offset 0x14 of the
 * structure it is given -- exactly where PSY-Q's MATRIX keeps the
 * translation after a 3x3 of shorts.
 * --------------------------------------------------------------------- */

/* Writes the far colour RFC/GFC/BFC (control registers 21-23), each
 * argument scaled up by four bits first. */
__asm__(
    ".global func_8003FC08\n"
    "func_8003FC08:\n"
    ".set noreorder\n"
    "sll $a0, $a0, 4\n"
    "sll $a1, $a1, 4\n"
    "sll $a2, $a2, 4\n"
    "ctc2 $a0, $21\n"
    "ctc2 $a1, $22\n"
    "ctc2 $a2, $23\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Writes rotation-matrix words 0, 2 and 4 -- the three control registers
 * that hold RT11/RT12, RT22/RT23 and RT33 -- leaving words 1 and 3
 * untouched. Not a full matrix load; naming it would mean guessing what
 * the caller intends by writing only these, so it keeps its address. */
__asm__(
    ".global func_8003FC68\n"
    "func_8003FC68:\n"
    ".set noreorder\n"
    "ctc2 $a0, $0\n"
    "ctc2 $a1, $2\n"
    "ctc2 $a2, $4\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Writes DQB (control register 28), the depth-cueing offset. */
__asm__(
    ".global func_8003FCCC\n"
    "func_8003FCCC:\n"
    ".set noreorder\n"
    "ctc2 $a0, $28\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Reads FLAG (control register 31), the GTE's calculation-error bits. */
__asm__(
    ".global func_8003FDC0\n"
    "func_8003FDC0:\n"
    ".set noreorder\n"
    "cfc2 $v0, $31\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Reads the screen offset OFX/OFY (control registers 24/25) and stores
 * each through a pointer argument, shifted down from 16.16 fixed point.
 * The counterpart of the setter above. */
__asm__(
    ".global func_8003FDCC\n"
    "func_8003FDCC:\n"
    ".set noreorder\n"
    "cfc2 $t0, $24\n"
    "cfc2 $t1, $25\n"
    "sra $t0, $t0, 16\n"
    "sra $t1, $t1, 16\n"
    "sw $t0, 0x0($a0)\n"
    "sw $t1, 0x0($a1)\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Reads H (control register 26), the projection plane distance. */
__asm__(
    ".global func_8003FDEC\n"
    "func_8003FDEC:\n"
    ".set noreorder\n"
    "cfc2 $v0, $26\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

/* Loads the translation vector from offsets 0x14/0x18/0x1C of the MATRIX
 * passed in, and writes it to TRX/TRY/TRZ (control registers 5-7). The
 * offset is a cross-check in itself: PSY-Q's MATRIX puts a 3x3 of shorts
 * first and the translation at 0x14, which is exactly where these loads
 * land. */
__asm__(
    ".global func_80043500\n"
    "func_80043500:\n"
    ".set noreorder\n"
    "lw $t0, 0x14($a0)\n"
    "lw $t1, 0x18($a0)\n"
    "lw $t2, 0x1C($a0)\n"
    "ctc2 $t0, $5\n"
    "ctc2 $t1, $6\n"
    "ctc2 $t2, $7\n"
    "jr $ra\n"
    "nop\n"
    ".set reorder\n"
);

