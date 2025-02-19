#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
   void* buffer;
   size_t allocated;
   size_t capacity;
} Arena;

bool arena_init(Arena*, size_t);
inline void arena_clear(Arena*);
inline void arena_free(Arena*);

void* arena_alloc(Arena*, size_t);
void* arena_alloc_aligned(Arena*, size_t, size_t);

#define __ARENA_DEF_
   #include "arena.c"
#undef __ARENA_DEF_