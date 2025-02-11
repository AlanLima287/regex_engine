#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
   void* buffer;
   size_t allocated;
   size_t capacity;
} Arena;

bool create_arena(Arena*, size_t);
inline void clear_arena(Arena*);
inline void delete_arena(Arena*);

void* arena_allocate(Arena*, size_t);
void* arena_allocate_aligned(Arena*, size_t, size_t);

#define __ARENA_DEF_
   #include "arena.c"
#undef __ARENA_DEF_