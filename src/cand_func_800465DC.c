#include "m2c_macros.h"



s32 func_800465DC(void *arg0) {
    u32 sp0;
    u32 sp4;
    s32 sp8;
    s32 spC;
    s32 temp_a2;
    s32 temp_v1;
    u32 temp_a1;
    u32 temp_v0;

    if (arg0 == NULL) {
        return 0;
    }
    temp_a1 = (u8) M2C_FIELD(arg0, u8 *, 0) >> 3;
    sp0 = temp_a1;
    temp_a2 = (s32) (-M2C_FIELD(arg0, s16 *, 4) & 0xFF) >> 3;
    sp8 = temp_a2;
    temp_v0 = (u8) M2C_FIELD(arg0, u8 *, 2) >> 3;
    sp4 = temp_v0;
    temp_v1 = (s32) (-M2C_FIELD(arg0, s16 *, 6) & 0xFF) >> 3;
    spC = temp_v1;
    return (temp_v0 << 0xF) | ((temp_a1 << 0xA) | 0xE2000000) | (temp_v1 << 5) | temp_a2;
}
