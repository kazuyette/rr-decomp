/* common.h -- umbrella header included by every splat-generated translation
 * unit. splat writes `#include "common.h"` at the top of each `c` subsegment,
 * so this file has to exist; project-wide types and declarations belong here
 * as the decompilation grows.
 */
#ifndef COMMON_H
#define COMMON_H

/* Make INCLUDE_ASM pull in macro.inc rather than labels.inc.
 *
 * The two differ on one thing that matters here: labels.inc declares jlabel
 * (a label referenced by a jumptable) with visibility=local, macro.inc with
 * visibility=global. Local is wrong for this binary -- the jumptables live in
 * .rodata, in a different object, and reference these labels by name:
 * asm/data/800.rodata.s is full of `.word .L80015040` and friends, 475 of
 * them pointing into func_80055E2C alone. A local label cannot satisfy that
 * reference, so the final link would fail to resolve it.
 *
 * It also makes the two sides of tools/verify.py comparable: with labels.inc
 * the assembler resolved intra-function jumps immediately while the target
 * object left a relocation, and six functions reported a mismatch that was
 * only ever a difference in how the same jump was expressed.
 */
#define INCLUDE_ASM_USE_MACRO_INC 1

#include "include_asm.h"

#endif /* COMMON_H */
