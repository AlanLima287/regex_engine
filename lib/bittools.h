#pragma once

/*
* Author
*    Alan Lima (https://github.com/AlanLima287/)
*
* BitTools
*    It's a not precompiled C++ library with wrapper function
*    for especific assembly instructions (BT, BTC, BTR, BTS)
*    or its behavior
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#if __has_include("intrin.h")
   #include <intrin.h>
#endif

typedef unsigned long long mword;

#define SHIFT 6 // (sizeof(mword) >= 4 ? ((sizeof(mword) >> 2) + 4) : (sizeof(mword) + 2))
#define POWER (1ull << SHIFT)
#define MASK  (POWER - 1)

#define size(length) ((length + MASK) >> SHIFT)

bool getbit  (mword*, uint64_t);
bool flipbit (mword*, uint64_t);
bool setbit_0(mword*, uint64_t);
bool setbit_1(mword*, uint64_t);
bool setbit  (mword*, uint64_t, bool);

#define __BITTOOLS_DEF_
   #include "bittools.c"
#undef __BITTOOLS_DEF_

#undef SHIFT
#undef POWER
#undef MASK
#undef size