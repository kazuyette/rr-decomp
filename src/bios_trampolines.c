/* PS1 BIOS call trampolines (A0h/B0h tables). Each jumps to a fixed
 * kernel dispatch address with the BIOS function number preloaded into
 * $t1 in the branch-delay slot -- the standard PSY-Q SDK calling
 * convention for BIOS calls (see https://psx-spx.consoledev.net/kernelbios/).
 * Not expressible as portable C (the jr never returns to a generated
 * epilogue), so these stay as raw asm blocks, same as every other
 * decomp project handles this exact pattern. TODO: map the function
 * numbers below to their real BIOS names once cross-referenced.
 *
 * Excluded on purpose: a couple of addresses in the disassembly START
 * with this same 3-instruction shape but are actually larger functions
 * with more (nominally unreachable, but still present) code after the
 * jr -- e.g. func_80049828 (0x44 bytes) and func_80053618 (0x18 bytes).
 * Those need real analysis, not a blind pattern match, so they stay as
 * raw asm for now. Verified each of the ones below against the original
 * bytes before committing -- see BUILD_NOTES.md.
 */
__asm__(
    ".global func_80049648\n"
    "func_80049648:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x36\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049658\n"
    "func_80049658:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x49\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049668\n"
    "func_80049668:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x35\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049678\n"
    "func_80049678:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x9F\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049688\n"
    "func_80049688:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x12\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049698\n"
    "func_80049698:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x44\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800496A8\n"
    "func_800496A8:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x2E\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800496B8\n"
    "func_800496B8:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x41\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800496C8\n"
    "func_800496C8:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x3F\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800496D8\n"
    "func_800496D8:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x13\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800496E8\n"
    "func_800496E8:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x1B\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800496F8\n"
    "func_800496F8:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x3\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049708\n"
    "func_80049708:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x17\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049718\n"
    "func_80049718:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x2\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049728\n"
    "func_80049728:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x4A\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049738\n"
    "func_80049738:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x19\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049748\n"
    "func_80049748:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x13\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049758\n"
    "func_80049758:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x2C\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049768\n"
    "func_80049768:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x39\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049778\n"
    "func_80049778:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x4B\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049788\n"
    "func_80049788:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x70\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049798\n"
    "func_80049798:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x43\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800497A8\n"
    "func_800497A8:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x4\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800497B8\n"
    "func_800497B8:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x34\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800497C8\n"
    "func_800497C8:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x2F\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800497E8\n"
    "func_800497E8:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x32\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800497F8\n"
    "func_800497F8:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x38\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049808\n"
    "func_80049808:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x72\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80049818\n"
    "func_80049818:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x42\n"
    ".set reorder\n"
);

__asm__(
    ".global func_8004DF1C\n"
    "func_8004DF1C:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x9\n"
    ".set reorder\n"
);

__asm__(
    ".global func_8004DF2C\n"
    "func_8004DF2C:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0xC\n"
    ".set reorder\n"
);

__asm__(
    ".global func_8004DF3C\n"
    "func_8004DF3C:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0xD\n"
    ".set reorder\n"
);

__asm__(
    ".global func_8004DF4C\n"
    "func_8004DF4C:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x6\n"
    ".set reorder\n"
);

__asm__(
    ".global func_8004DF5C\n"
    "func_8004DF5C:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x8\n"
    ".set reorder\n"
);

__asm__(
    ".global func_800534C8\n"
    "func_800534C8:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x3D\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80054244\n"
    "func_80054244:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x19\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80054254\n"
    "func_80054254:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x18\n"
    ".set reorder\n"
);

__asm__(
    ".global func_80059050\n"
    "func_80059050:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0xB\n"
    ".set reorder\n"
);
