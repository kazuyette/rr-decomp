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
 * jr -- e.g. ReturnFromException (0x44 bytes) and DeliverEvent (0x18 bytes).
 * Those need real analysis, not a blind pattern match, so they stay as
 * raw asm for now. Verified each of the ones below against the original
 * bytes before committing -- see BUILD_NOTES.md.
 */
__asm__(
    ".global bios_close\n"
    "bios_close:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x36\n"
    ".set reorder\n"
);

__asm__(
    ".global GPU_cw\n"
    "GPU_cw:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x49\n"
    ".set reorder\n"
);

__asm__(
    ".global bios_write\n"
    "bios_write:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x35\n"
    ".set reorder\n"
);

__asm__(
    ".global SetMem\n"
    "SetMem:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x9F\n"
    ".set reorder\n"
);

__asm__(
    ".global InitPAD2\n"
    "InitPAD2:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x12\n"
    ".set reorder\n"
);

__asm__(
    ".global bios_rename\n"
    "bios_rename:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x44\n"
    ".set reorder\n"
);

__asm__(
    ".global memchr\n"
    "memchr:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x2E\n"
    ".set reorder\n"
);

__asm__(
    ".global bios_format\n"
    "bios_format:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x41\n"
    ".set reorder\n"
);

__asm__(
    ".global printf\n"
    "printf:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x3F\n"
    ".set reorder\n"
);

__asm__(
    ".global setjmp\n"
    "setjmp:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x13\n"
    ".set reorder\n"
);

__asm__(
    ".global strlen\n"
    "strlen:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x1B\n"
    ".set reorder\n"
);

__asm__(
    ".global get_timer\n"
    "get_timer:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x3\n"
    ".set reorder\n"
);

__asm__(
    ".global strcmp\n"
    "strcmp:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x17\n"
    ".set reorder\n"
);

__asm__(
    ".global init_timer\n"
    "init_timer:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x2\n"
    ".set reorder\n"
);

__asm__(
    ".global InitCARD2\n"
    "InitCARD2:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x4A\n"
    ".set reorder\n"
);

__asm__(
    ".global HookEntryInt\n"
    "HookEntryInt:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x19\n"
    ".set reorder\n"
);

__asm__(
    ".global StartPAD2\n"
    "StartPAD2:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x13\n"
    ".set reorder\n"
);

__asm__(
    ".global memmove\n"
    "memmove:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x2C\n"
    ".set reorder\n"
);

__asm__(
    ".global InitHeap\n"
    "InitHeap:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x39\n"
    ".set reorder\n"
);

__asm__(
    ".global StartCARD2\n"
    "StartCARD2:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x4B\n"
    ".set reorder\n"
);

__asm__(
    ".global _bu_init\n"
    "_bu_init:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x70\n"
    ".set reorder\n"
);

__asm__(
    ".global nextfile\n"
    "nextfile:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x43\n"
    ".set reorder\n"
);

__asm__(
    ".global enable_timer_irq\n"
    "enable_timer_irq:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x4\n"
    ".set reorder\n"
);

__asm__(
    ".global bios_read\n"
    "bios_read:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x34\n"
    ".set reorder\n"
);

__asm__(
    ".global rand\n"
    "rand:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x2F\n"
    ".set reorder\n"
);

__asm__(
    ".global bios_open\n"
    "bios_open:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x32\n"
    ".set reorder\n"
);

__asm__(
    ".global bios_exit\n"
    "bios_exit:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x38\n"
    ".set reorder\n"
);

__asm__(
    ".global _96_remove\n"
    "_96_remove:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x72\n"
    ".set reorder\n"
);

__asm__(
    ".global firstfile2\n"
    "firstfile2:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x42\n"
    ".set reorder\n"
);

__asm__(
    ".global CloseEvent\n"
    "CloseEvent:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x9\n"
    ".set reorder\n"
);

__asm__(
    ".global EnableEvent\n"
    "EnableEvent:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0xC\n"
    ".set reorder\n"
);

__asm__(
    ".global DisableEvent\n"
    "DisableEvent:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0xD\n"
    ".set reorder\n"
);

__asm__(
    ".global restart_timer\n"
    "restart_timer:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x6\n"
    ".set reorder\n"
);

__asm__(
    ".global OpenEvent\n"
    "OpenEvent:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x8\n"
    ".set reorder\n"
);

__asm__(
    ".global putchar\n"
    "putchar:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x3D\n"
    ".set reorder\n"
);

__asm__(
    ".global strcpy\n"
    "strcpy:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x19\n"
    ".set reorder\n"
);

__asm__(
    ".global strncmp\n"
    "strncmp:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xA0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0x18\n"
    ".set reorder\n"
);

__asm__(
    ".global TestEvent\n"
    "TestEvent:\n"
    ".set noreorder\n"
    "addiu $t2, $zero, 0xB0\n"
    "jr $t2\n"
    "addiu $t1, $zero, 0xB\n"
    ".set reorder\n"
);
