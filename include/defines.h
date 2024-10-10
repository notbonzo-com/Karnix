#ifndef _DEFINES_H
#define _DEFINES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef float f32;
typedef double f64;

typedef char b8;
typedef short b16;
typedef int b32;

#define STATIC_ASSERT static_assert

STATIC_ASSERT(sizeof(u8) == 1, "u8 must be 1 byte");
STATIC_ASSERT(sizeof(u16) == 2, "u16 must be 2 bytes");
STATIC_ASSERT(sizeof(u32) == 4, "u32 must be 4 bytes");
STATIC_ASSERT(sizeof(u64) == 8, "u64 must be 8 bytes");
STATIC_ASSERT(sizeof(s8) == 1, "s8 must be 1 byte");
STATIC_ASSERT(sizeof(s16) == 2, "s16 must be 2 bytes");
STATIC_ASSERT(sizeof(s32) == 4, "s32 must be 4 bytes");
STATIC_ASSERT(sizeof(s64) == 8, "s64 must be 8 bytes");
STATIC_ASSERT(sizeof(f32) == 4, "f32 must be 4 bytes");
STATIC_ASSERT(sizeof(f64) == 8, "f64 must be 8 bytes");
STATIC_ASSERT(sizeof(b8) == 1, "b8 must be 1 byte");
STATIC_ASSERT(sizeof(b32) == 4, "b32 must be 4 bytes");

#if !defined(false) && !defined(true) && !defined(nullptr)
#define true 1
#define false 0
#define nullptr ((void*)0)
#endif

#endif // _DEFINES_H