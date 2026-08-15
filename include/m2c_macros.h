/* Types and macros used by the m2c-generated units (src/b5_*.c).
 *
 * m2c emits M2C_FIELD for a memory access through a pointer whose struct
 * type we have not reconstructed yet. The macro expands to the same load
 * or store the original struct member access compiled to, so a function
 * written this way can still byte-match; it is simply unreadable until
 * the struct is named. Replacing these with real field names is a
 * readability pass, not a matching one.
 */
#ifndef M2C_MACROS_H
#define M2C_MACROS_H

typedef signed char    s8;
typedef unsigned char  u8;
typedef short          s16;
typedef unsigned short u16;
typedef int            s32;
typedef unsigned int   u32;

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

#endif
