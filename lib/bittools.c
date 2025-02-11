#ifndef __BITTOOLS_DEF_
   #include "bittools.h"
#else

#ifdef __INTRIN_H_

bool getbit  (mword* base, uint64_t pos) { return _bittest64(base + (pos >> SHIFT), pos & MASK); }
bool flipbit (mword* base, uint64_t pos) { return _bittestandcomplement64(base + (pos >> SHIFT), pos & MASK); }
bool setbit_0(mword* base, uint64_t pos) { return _bittestandreset64(base + (pos >> SHIFT), pos & MASK); }
bool setbit_1(mword* base, uint64_t pos) { return _bittestandset64(base + (pos >> SHIFT), pos & MASK); }
bool setbit  (mword* base, uint64_t pos, bool bit_value) { return bit_value ? setbit_1(base, pos) : setbit_0(base, pos); }

#else

bool getbit(mword* base, uint64_t pos) {
   return (base[pos >> SHIFT] >> (pos & MASK)) & 1;
   // return base[pos >> SHIFT] & (1 << (pos & MASK));
}

bool flipbit(mword* base, uint64_t pos) {
   mword* word = base + (pos >> SHIFT);
   int64_t offset = 1 << (pos & MASK);

   bool bit = *word & offset;
   *word ^= offset;

   return bit;
}

bool setbit_0(mword* base, uint64_t pos) {
   mword* word = base + (pos >> SHIFT);
   int64_t offset = 1 << (pos & MASK);

   bool bit = *word & offset;
   *word &= ~offset;

   return bit;
}

bool setbit_1(mword* base, uint64_t pos) {
   mword* word = base + (pos >> SHIFT);
   int64_t offset = 1 << (pos & MASK);

   bool bit = *word & offset;
   *word |= offset;

   return bit;
}


bool setbit(mword* base, uint64_t pos, bool bit_value) {
   mword* word = base + (pos >> SHIFT);
   int64_t offset = 1 << (pos & MASK);

   bool bit = *word & offset;
   if (bit_value) *word |= offset;
   else *word &= ~offset;

   return bit;
}

#endif

#endif /* __BITTOOLS_DEF_ */