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

typedef unsigned long long mword;

#define SHIFT 6 // (sizeof(mword) >= 4 ? ((sizeof(mword) >> 2) + 4) : (sizeof(mword) + 2))
#define POWER (1ull << SHIFT)
#define MASK  (POWER - 1)

#define size(length) ((length + MASK) >> SHIFT)

#if __has_include("intrin.h")

#include <intrin.h>
#ifdef __INTRIN_H_

bool getbit  (mword* base, uint64_t pos) { return _bittest64(base + (pos >> SHIFT), pos & MASK); }
bool flipbit (mword* base, uint64_t pos) { return _bittestandcomplement64(base + (pos >> SHIFT), pos & MASK); }
bool setbit_0(mword* base, uint64_t pos) { return _bittestandreset64(base + (pos >> SHIFT), pos & MASK); }
bool setbit_1(mword* base, uint64_t pos) { return _bittestandset64(base + (pos >> SHIFT), pos & MASK); }
bool setbit_v(mword* base, uint64_t pos, bool bit_value) { return bit_value ? setbit_1(base, pos) : setbit_0(base, pos); }

#endif

#else

bool getbit(mword* base, uint64_t pos) {
   return (base[pos >> SHIFT] >> (pos & MASK)) & 1;
   // return base[pos >> SHIFT] & (1 << (pos & MASK));
}

bool flipbit(mword* base, uint64_t pos) {
   mword* word = base + (pos >> SHIFT);
   uint64_t offset = 1ull << (pos & MASK);

   bool bit = *word & offset;
   *word ^= offset;

   return bit;
}

bool setbit_0(mword* base, uint64_t pos) {
   mword* word = base + (pos >> SHIFT);
   uint64_t offset = 1ull << (pos & MASK);

   bool bit = *word & offset;
   *word &= ~offset;

   return bit;
}

bool setbit_1(mword* base, uint64_t pos) {
   mword* word = base + (pos >> SHIFT);
   uint64_t offset = 1ull << (pos & MASK);

   bool bit = *word & offset;
   *word |= offset;

   return bit;
}


bool setbit_v(mword* base, uint64_t pos, bool bit_value) {
   mword* word = base + (pos >> SHIFT);
   uint64_t offset = 1ull << (pos & MASK);

   bool bit = *word & offset;
   if (bit_value) *word |= offset;
   else *word &= ~offset;

   return bit;
}

#endif

#undef size

uint64_t size(uint64_t length) { return ((length + MASK) >> SHIFT); }

#undef SHIFT
#undef POWER
#undef MASK