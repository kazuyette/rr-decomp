/* batch4.c -- fourth speculative batch, generated from m2c output.
 *
 * These are the functions for which m2c produced C that needs no type
 * information we do not have: no unknown-width memory accesses, no stack
 * structures, no unrecovered jump tables. 32 of the 783 remaining
 * INCLUDE_ASM functions qualify; the other 751 need a context file
 * describing the game's structs before m2c can express them at all.
 *
 * Compiled with the default flag set (-O2 -mrnames -fno-builtin
 * -fsigned-char -gcoff), the same one src/globals.c uses. Whatever does
 * not byte-match here gets sent back to INCLUDE_ASM by
 * tools/revert_failed.py, and stays in this file commented out as the
 * starting point for a retry under -O1.
 */

typedef signed char   s8;
typedef unsigned char u8;
typedef short         s16;
typedef unsigned short u16;
typedef int           s32;
typedef unsigned int  u32;

extern s32 D_80077378;
extern s32 *D_80077394;
extern s32 *D_80077398;
extern s32 *D_8007739C;
extern s32 *D_800773A0;
extern s32 *D_800773B0;
extern s32 D_8012D020;
extern s16 D_801D34F8;
extern u16 D_801D35AA;
extern s32 D_801E90E0;
extern s32 D_80077688;
extern s32 D_800776A0;
extern s32 D_801734A0;
extern s32 D_8012D0C0;
extern s32 D_801D7E20;
extern s32 D_801D9028;
extern s16 D_8007C210;
extern s32 D_8007C260;
extern s16 D_8007C32C;
extern s16 D_8007C32E;
extern s32 D_80173348;
extern s16 D_801D77B8;
extern s32 D_8012D8E0;
extern s32 D_8012D8E8;
extern s32 D_801D9030;
extern s32 D_801D9040;
extern s32 D_80077388;
extern s32 D_8007738C;
extern s32 *D_80077390;
extern s32 D_8012D080;
extern u16 D_801D35AE;
extern s32 D_80075F90;
extern s32 D_80077730;
extern s32 D_80077734;
extern s32 D_80077738;
extern s32 D_8007773C;
extern s32 D_80077740;
extern s32 D_80077744;
extern s32 D_80173140;
extern s16 D_801D354E;
extern s16 D_801D3550;
extern s16 D_801D3554;
extern s16 D_801D3556;
extern s16 D_801D355A;
extern s16 D_801D355C;
extern s16 D_801D3560;
extern s16 D_801D3562;
extern s16 D_801D356C;
extern s32 D_801D7800;
extern s32 D_801D7E38;
s32 func_800531A8();
s32 func_800497C8();
extern s32 D_801D3588;
s32 rcos(s32);
s32 func_80040690(s32);
s32 rsin_quadrant(s32);
s32 func_8003A9D8(s16);
s16 func_8003AAD8(s16);
s32 func_8003AC2C(s16);
extern s16 D_800772FC;
s32 func_80045718();
extern s32 D_801D9020;
extern s32 D_801D9058;
extern s32 D_801E90B8;
extern s32 D_801E91E8;
s32 func_80059050(s32);
extern s32 D_8012CDA8;
extern s32 D_8012CDD0;
extern s32 D_801E9228;
extern s16 D_801733B8;
extern s32 D_80173480;
extern s32 D_80173488;
extern s32 D_80173490;
extern s16 D_801D9060;
/* func_8004D388 */
s32 func_8004D388(s32 arg0) {
    s32 var_v0;

    var_v0 = -1;
    if ((u32) (arg0 & 0xFFFF) < 0x18U) {
        var_v0 = 0;
    }
    return var_v0;
}

/* func_8004D3A4 */
s32 func_8004D3A4(s32 arg0) {
    s32 var_v0;

    var_v0 = -1;
    if ((u32) (arg0 & 0xFFFF) < 0x18U) {
        var_v0 = 0;
    }
    return var_v0;
}

/* AddPrim */
void AddPrim(s32 *arg0, s32 *arg1) {
    *arg1 = (*arg1 & 0xFF000000) | (*arg0 & 0xFFFFFF);
    *arg0 = (*arg0 & 0xFF000000) | ((s32) arg1 & 0xFFFFFF);
}

/* func_80046430 */
s32 func_80046430(s32 arg0, s32 arg1, s32 arg2) {
    s32 var_v0;
    s32 var_v1;

    if (D_80077378 != 0) {
        var_v1 = 0xE1000000;
        if (arg1 != 0) {
            var_v1 = 0xE1000800;
        }
        var_v0 = arg2 & 0x27FF;
        if (arg0 != 0) {
            var_v0 |= 0x1000;
        }
    } else {
        var_v1 = 0xE1000000;
        if (arg1 != 0) {
            var_v1 = 0xE1000200;
        }
        var_v0 = arg2 & 0x1FF;
        if (arg0 != 0) {
            var_v0 |= 0x400;
        }
    }
    return var_v1 | var_v0;
}

/* func_800470D0 */
void func_800470D0(s32 arg0) {
    *D_80077394 = 0x04000002;
    *D_800773B0 |= 0x800;
    *D_80077398 = arg0;
    *D_8007739C = 0;
    *D_800773A0 = 0x01000401;
}

/* func_800177B8 */
s32 func_800177B8(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_lo;

    temp_a0 = arg0 & 0xFFF;
    var_a1 = arg1 & 0xFFF;
    temp_v1 = 0x100 - arg2;
    if (var_a1 < temp_a0) {
        var_lo = temp_a0 * temp_v1;
        if ((temp_a0 - var_a1) >= 0x801) {
            var_a1 += 0x1000;
        }
    } else {
        var_lo = temp_a0 * temp_v1;
        if ((var_a1 - temp_a0) >= 0x801) {
            var_lo = (temp_a0 + 0x1000) * temp_v1;
        }
    }
    return ((s32) (var_lo + (var_a1 * arg2)) / 256) & 0xFFF;
}

/* func_80031044 */
void func_80031044(void) {
    if ((D_8012D020 & 1) && (D_801D35AA & 0x1000)) {
        D_801D34F8 = 0x13;
    }
    if ((D_8012D020 & 0x100) && (D_801D35AA & 0x4000)) {
        D_801D34F8 = 0x13;
    }
    if ((D_8012D020 & 0x200) && (D_801D35AA & 0x8000)) {
        D_801D34F8 = 8;
    }
}

/* func_80046480 */
s32 func_80046480(s32 arg0, s16 arg1) {
    s16 var_a1;
    s16 var_a1_2;
    s16 var_v0_2;
    s16 var_v0_3;
    s32 var_v0;
    s32 var_v1;

    if (D_80077378 != 0) {
        var_a1 = arg1;
        if (arg1 >= 0) {
            if (var_a1 >= 0x400) {
                var_a1 = 0x3FF;
            }
            var_v0_2 = var_a1;
        } else {
            var_v0_2 = 0;
        }
        var_v0 = (var_v0_2 & 0xFFF) << 0xC;
        var_v1 = arg0 & 0xFFF;
    } else {
        var_a1_2 = arg1;
        if (arg1 >= 0) {
            if (var_a1_2 >= 0x200) {
                var_a1_2 = 0x1FF;
            }
            var_v0_3 = var_a1_2;
        } else {
            var_v0_3 = 0;
        }
        var_v0 = (var_v0_3 & 0x3FF) << 0xA;
        var_v1 = arg0 & 0x3FF;
    }
    return var_v0 | (var_v1 | 0xE3000000);
}

/* func_80046510 */
s32 func_80046510(s32 arg0, s16 arg1) {
    s16 var_a1;
    s16 var_a1_2;
    s16 var_v0_2;
    s16 var_v0_3;
    s32 var_v0;
    s32 var_v1;

    if (D_80077378 != 0) {
        var_a1 = arg1;
        if (arg1 >= 0) {
            if (var_a1 >= 0x400) {
                var_a1 = 0x3FF;
            }
            var_v0_2 = var_a1;
        } else {
            var_v0_2 = 0;
        }
        var_v0 = (var_v0_2 & 0xFFF) << 0xC;
        var_v1 = arg0 & 0xFFF;
    } else {
        var_a1_2 = arg1;
        if (arg1 >= 0) {
            if (var_a1_2 >= 0x200) {
                var_a1_2 = 0x1FF;
            }
            var_v0_3 = var_a1_2;
        } else {
            var_v0_3 = 0;
        }
        var_v0 = (var_v0_3 & 0x1FF) << 0xA;
        var_v1 = arg0 & 0x3FF;
    }
    return var_v0 | (var_v1 | 0xE4000000);
}

/* func_8001FBC0 */
s32 func_8001FBC0(s32 arg0, s32 arg1) {
    return ((arg0 / 30) * 0x3E8) + (((s32) ((arg0 % 30) * 0x64) / 3) + arg1);
}

/* func_8002B974 */
s32 func_8002B974(s32 arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_v0;
    s32 var_a0;

    temp_v0 = D_801E90E0 << 0x10;
    temp_a2 = D_801E90E0 << 8;
    temp_hi = (s32) (arg0 + temp_v0) % temp_a2;
    temp_hi_2 = (s32) (arg1 + temp_v0) % temp_a2;
    if (temp_hi < temp_hi_2) {
        var_a0 = temp_hi_2 - temp_hi;
    } else {
        var_a0 = temp_hi - temp_hi_2;
    }
    if ((D_801E90E0 << 7) < var_a0) {
        var_a0 = temp_a2 - var_a0;
    }
    return var_a0;
}

/* func_800548A8 */
s32 func_800548A8(s32 *arg0, u16 **arg1) {
    s32 var_v0;
    u16 *var_a3;

    var_a3 = (D_800776A0 << 5) + D_801734A0;
    if ((*var_a3 & 0xFFFF) == 1) {
        D_800776A0 = 0;
        *var_a3 = 0;
        var_a3 = (D_800776A0 << 5) + D_801734A0;
    }
    var_v0 = 1;
    if ((*var_a3 & 0xFFFF) == 2) {
        *var_a3 = 4;
        var_v0 = 0;
        *arg0 = (D_80077688 << 5) + D_801734A0 + (D_800776A0 * 0x7E0);
        *arg1 = var_a3;
    }
    return var_v0;
}

/* func_800373BC */
s32 func_800373BC(s32 arg0, s32 arg1) {
    s32 temp_a2;
    s32 temp_hi;
    s32 temp_hi_2;
    s32 temp_v0;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;

    temp_v0 = D_801E90E0 << 0x10;
    temp_a2 = D_801E90E0 << 8;
    temp_hi = (s32) (arg0 + temp_v0) % temp_a2;
    temp_hi_2 = (s32) (arg1 + temp_v0) % temp_a2;
    var_a1 = temp_hi < temp_hi_2;
    if (var_a1 != 0) {
        var_a0 = temp_hi_2 - temp_hi;
    } else {
        var_a0 = temp_hi - temp_hi_2;
    }
    if ((D_801E90E0 << 7) < var_a0) {
        var_a0 = temp_a2 - var_a0;
        var_a1 = var_a1 == 0;
    }
    var_v0 = var_a0;
    if (var_a1 == 0) {
        var_v0 = -var_v0;
    }
    return var_v0;
}

/* func_8004DB58 */
void func_8004DB58(s32 arg0) {
    if (arg0 & 0x1000) {
        D_8012D0C0 = 1;
        D_801D7E20 = arg0 & 0xFFF;
    } else {
        D_8012D0C0 = 0;
        D_801D7E20 = arg0;
    }
    if (D_801D7E20 < 4) {
        switch (D_801D7E20) {                       /* irregular */
        case 3:
            D_801D9028 = 0x78;
            return;
        case 2:
            D_801D9028 = 0xF0;
            return;
        case 1:
            /* fallthrough */
        default:
            D_801D9028 = 0x3C;
            return;
        }
    } else {
        D_801D9028 = D_801D7E20;
    }
}

/* func_80021BE0 */
void func_80021BE0(void) {
    s32 temp_a2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a1;

    temp_a2 = D_8007C210 < 3;
    var_a1 = 0x17000;
    if (temp_a2 != 0) {
        var_a1 = 0x10000;
    }
    if (D_801D77B8 == 0) {
        if (D_8007C260 >= 0x2800) {
            var_a0 = (var_a1 + 0x2800) - D_8007C260;
        } else {
            var_a0 = 0x2800 - D_8007C260;
        }
        goto block_12;
    }
    if (D_801D77B8 == 1) {
        var_a0_2 = 0xB900;
        if (temp_a2 == 0) {
            var_a0_2 = 0x12900;
        }
        if (D_8007C260 >= var_a0_2) {
            var_a0 = D_8007C260 - var_a0_2;
        } else {
            var_a0 = (var_a1 - var_a0_2) + D_8007C260;
        }
block_12:
        D_80173348 = var_a0 + ((var_a1 * D_8007C32C) - D_8007C32E);
    }
}

/* func_80012EF0 */
s32 func_80012EF0(s32 arg0) {
    s32 temp_hi;
    s32 var_v0;

    temp_hi = (s32) (arg0 + (D_801E90E0 << 0x10)) % (s32) (D_801E90E0 << 8);
    if ((temp_hi < D_8012D8E0) && (D_801D9030 < temp_hi)) {
        var_v0 = D_8012D8E0 - temp_hi;
        if ((D_8012D8E0 - 0x100) >= temp_hi) {
            if (temp_hi < (D_801D9030 + 0x100)) {
                return temp_hi - D_801D9030;
            }
            goto block_9;
        }
        /* Duplicate return node #10. Try simplifying control flow for better match */
        return var_v0;
    }
    var_v0 = temp_hi < D_8012D8E8;
    if (var_v0 != 0) {
        var_v0 = D_801D9040 < temp_hi;
        if (var_v0 != 0) {
            var_v0 = D_8012D8E8 - temp_hi;
            if ((D_8012D8E8 - 0x100) >= temp_hi) {
                var_v0 = temp_hi - D_801D9040;
                if (temp_hi >= (D_801D9040 + 0x100)) {
block_9:
                    var_v0 = 0x100;
                }
            }
        }
    }
    return var_v0;
}

/* func_8002C404 */
s32 func_8002C404(s32 arg0, s32 arg1) {
    s32 temp_a3;
    s32 temp_hi;
    s32 temp_t1;
    s32 var_a0;
    s32 var_a2;
    u32 temp_v0;

    temp_t1 = D_801E90E0 << 0x10;
    temp_a3 = D_801E90E0 << 8;
    temp_hi = (s32) (arg0 + temp_t1) % temp_a3;
    var_a2 = (s32) (arg1 + temp_t1) % temp_a3;
    var_a0 = temp_hi;
    if (var_a2 < var_a0) {
        var_a0 = var_a2;
        var_a2 = temp_hi;
    }
    if ((D_801E90E0 << 7) >= (var_a2 - var_a0)) {
        temp_v0 = var_a0 + var_a2;
        return (s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1;
    }
    return (s32) (((s32) (var_a0 + temp_a3 + var_a2) / 2) + temp_t1) % temp_a3;
}

/* func_80047508 */
s32 func_80047508(s32 arg0) {
    switch (arg0) {                                 /* irregular */
    case 0:
        *D_800773A0 = 0x401;
        *D_80077394 = 0;
block_5:
        D_8007738C = 0;
        D_80077388 = D_8007738C;
        break;
    case 1:
        *D_800773A0 = 0x401;
        *D_80077394 = 0x04000000;
        *D_80077394 = 0x02000000;
        *D_80077394 = 0x01000000;
        goto block_5;
    }
    *D_80077390 = (*D_80077394 & 0x3FFF) | 0xE1001000;
    return ((u32) *D_80077394 >> 0xC) & 1;
}

/* func_80031FD0 */
void func_80031FD0(void) {
    s32 var_v0;
    s32 var_v0_2;
    u16 var_v0_3;

    if (D_801D35AA & 0x1000) {
        var_v0 = D_8012D080 - 1;
        if (D_8012D080 > 0) {
            D_8012D080 = 0;
            var_v0 = D_8012D080 - 1;
        }
        D_8012D080 = var_v0;
    } else if (D_801D35AA & 0x4000) {
        var_v0_2 = D_8012D080 + 1;
        if (D_8012D080 < 0) {
            D_8012D080 = 0;
            var_v0_2 = D_8012D080 + 1;
        }
        D_8012D080 = var_v0_2;
    } else {
        D_8012D080 = 0;
    }
    if (D_8012D080 < -0x19) {
        if (!((D_8012D080 + 0x1A) & 3)) {
            var_v0_3 = D_801D35AE | 0x1000;
            goto block_15;
        }
    } else if ((D_8012D080 >= 0x1A) && !((D_8012D080 - 0x1A) & 3)) {
        var_v0_3 = D_801D35AE | 0x4000;
block_15:
        D_801D35AE = var_v0_3;
    }
}

/* func_800439D8 */
void func_800439D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_t0;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_at;
    s32 var_at_2;

    D_80075F90 = arg0;
    temp_t0 = arg3 << 0xC;
    var_at = arg1;
    if (arg1 < 0) {
        var_at += 1;
    }
    temp_v0 = var_at >> 1;
    D_80077734 = temp_t0 / temp_v0;
    var_at_2 = arg2;
    if (arg2 < 0) {
        var_at_2 += 1;
    }
    temp_v1 = var_at_2 >> 1;
    D_8007773C = temp_t0 / temp_v1;
    D_80077730 = (s32) (temp_v0 << 0xC) / arg3;
    D_80077738 = (s32) (temp_v1 << 0xC) / arg3;
    D_80077744 = arg4;
    D_80077740 = arg5;
}

/* func_8001AE90 */
void func_8001AE90(void) {
    s16 temp_v1;
    s32 temp_a2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v0;

    var_a0 = (((s32) D_801D7800 / 500) + (((s32) (D_80173140 * 0x78) / 256) + 0x14)) * D_801D7E38;
    if (var_a0 < 0) {
        var_a0 += 0xFF;
    }
    D_801D354E = (s16) (var_a0 >> 8);
    D_801D356C = 0;
    temp_a2 = D_80173140 * 0x1E;
    temp_v1 = ((s32) (D_801D7800 * 0x1800) / 10000) + 0x1200;
    D_801D3550 = temp_v1;
    var_v0 = temp_a2;
    if (temp_a2 < 0) {
        var_v0 = temp_a2 + 0xFF;
    }
    var_a0_2 = (((s32) D_801D7800 / 250) - ((var_v0 >> 8) - 0x23)) * D_801D7E38;
    if (var_a0_2 < 0) {
        var_a0_2 += 0xFF;
    }
    D_801D355A = (s16) (var_a0_2 >> 8);
    D_801D355C = temp_v1;
    D_801D3554 = (s16) ((s32) ((((s32) D_801D7800 / 1000) + (((s32) (D_80173140 * 0x50) / 256) + 0xA)) * D_801D7E38) / 256);
    D_801D3556 = temp_v1;
    D_801D3560 = 0;
    D_801D3562 = temp_v1;
    D_801D3560 = (s16) ((s32) ((temp_a2 / 256) * D_801D7E38) / 256);
    D_801D3562 = temp_v1;
}

/* func_80051F6C */
s32 func_80051F6C(void) {
    return func_800531A8() == 0;
}

/* func_8004C0B8 */
s16 func_8004C0B8(s16 arg0) {
    return func_80058F64(arg0);
}

/* func_80038B80 */
void func_80038B80(void) {
    D_801D3588 = func_800497C8() & 0x3FF;
}

/* func_8002BB50 */
s32 func_8002BB50(u32 arg0) {
    u32 temp_v0;

    if ((u32) (arg0 + 0x1000) < 0x2001U) {
        temp_v0 = rcos((s32) (arg0 + (arg0 >> 0x1F)) >> 1) + 0x1000;
        return (s32) (temp_v0 + (temp_v0 >> 0x1F)) >> 1;
    }
    return 0;
}

/* func_80040868 */
s32 func_80040868(s32 arg0) {
    if (arg0 < 0) {
        return -func_80040690((s32) -arg0 % 4096);
    }
    return func_80040690(arg0 % 4096);
}

/* rsin */
s32 rsin(s32 arg0) {
    if (arg0 < 0) {
        return -rsin_quadrant((s32) -arg0 % 4096);
    }
    return rsin_quadrant(arg0 % 4096);
}

/* snd_play_se */
s32 snd_play_se(s16 arg0) {
    s16 var_v0;
    s32 var_v0_2;

    var_v0 = D_800772FC;
    if (var_v0 == 0) {
        var_v0 = arg0 < 0x3A;
        if (var_v0 != 0) {
            if (arg0 < 0x11) {
                var_v0_2 = func_8003A9D8(arg0) << 0x10;
                goto block_6;
            }
            if (arg0 >= 0x1F) {
                var_v0_2 = func_8003AC2C(arg0) << 0x10;
block_6:
                return var_v0_2 >> 0x10;
            }
            var_v0 = func_8003AAD8(arg0);
            /* Duplicate return node #8. Try simplifying control flow for better match */
            return (s32) var_v0;
        }
    }
    return (s32) var_v0;
}

/* func_8004788C */
s32 func_8004788C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v1;
    s32 var_v0;
    s32 var_v1;

    temp_v1 = arg0 & 3;
    if (func_80045718() != 0) {
        var_v1 = (temp_v1 << 9) | ((arg1 & 3) << 7);
        var_v0 = (s32) (arg3 & 0x300) >> 3;
    } else {
        var_v1 = (temp_v1 << 7) | ((arg1 & 3) << 5);
        var_v0 = (s32) (arg3 & 0x100) >> 4;
    }
    return var_v1 | var_v0 | ((s32) (arg2 & 0x3FF) >> 6);
}

/* func_800377B4 */
void func_800377B4(void) {
    s32 temp_v0;

    temp_v0 = func_80037478();
    if (D_801E91E8 < temp_v0) {
        D_801D9058 = 0;
        D_801E90B8 = D_801E91E8;
        D_801D9020 = temp_v0 - D_801E91E8;
    } else if (temp_v0 < D_801E91E8) {
        D_801D9058 = 1;
        D_801E90B8 = temp_v0;
        D_801D9020 = D_801E91E8 - temp_v0;
    } else {
        D_801D9058 = -1;
    }
    D_801E91E8 = temp_v0;
}

/* func_80058F64 */
s32 func_80058F64(s32 arg0) {
    s32 var_v1;

    if ((D_8012CDD0 == 1) || (D_8012CDA8 == 1)) {
        return 1;
    }
    var_v1 = func_80059050(D_801E9228);
    if (arg0 == 1) {
        if (var_v1 == 0) {
            do {
                var_v1 = func_80059050(D_801E9228);
            } while (var_v1 == 0);
        }
        D_8012CDA8 = 1;
        return var_v1;
    }
    if (var_v1 == 1) {
        D_8012CDA8 = var_v1;
    }
    return var_v1;
}

/* func_80037478 */
s32 func_80037478(s32 arg0) {
    s32 temp_a0;
    s32 temp_s0;
    s32 temp_v1_2;
    s32 var_v0;
    s32 var_v1;
    u32 temp_v0;
    u32 temp_v1;

    if (D_801D9060 < 3) {
        return (D_801733B8 == 0) << 8;
    }
    temp_s0 = func_800373BC(D_80173480, arg0);
    temp_a0 = func_800373BC(D_80173488, arg0);
    temp_v1 = temp_s0 + 0x200;
    if (temp_v1 < 0x401U) {
        var_v0 = temp_v1 + (temp_v1 >> 0x1F);
        goto block_6;
    }
    if ((u32) (temp_a0 + 0x200) < 0x401U) {
        temp_v0 = 0x200 - temp_a0;
        var_v0 = temp_v0 + (temp_v0 >> 0x1F);
block_6:
        temp_v1_2 = var_v0 >> 1;
        var_v1 = (s32) (temp_v1_2 + ((u32) temp_v1_2 >> 0x1F)) >> 1;
    } else if (temp_s0 > 0) {
        if (D_80173490 > 0) {
            var_v1 = (temp_a0 >> 0x1F) & 0x100;
        } else {
            var_v1 = 0x100;
        }
    } else {
        var_v1 = 0;
        if (D_80173490 < 0) {
            var_v1 = (temp_a0 < 1) << 8;
        }
    }
    return var_v1;
}
