#ifndef __ARENA_DEF_
   #include "arena.h"
#else

bool arena_init(Arena* arena, size_t size) {
   arena->buffer = malloc(size);
   if (arena->buffer == NULL) return false;

   arena->capacity = size;
   arena->allocated = 0;
   return true;
}

void arena_clear(Arena* arena) {
   arena->allocated = 0;
}

void arena_free(Arena* arena) {
   free(arena->buffer);
   arena->buffer = NULL;
}

void* arena_alloc(Arena* arena, size_t size) {
   if (arena->allocated + size >= arena->capacity) return NULL;

   void* pointer = (void*)((uintptr_t)arena->buffer + (uintptr_t)arena->allocated);
   arena->allocated += size;

   return pointer;
}

void* arena_alloc_aligned(Arena* arena, size_t size, size_t alignment) {
   size_t padding = ((arena->allocated + alignment - 1) & -alignment) - arena->allocated;
   if (arena->allocated + padding + size >= arena->capacity) return NULL;

   void* pointer = (void*)((uintptr_t)arena->buffer + (uintptr_t)(arena->allocated + padding));
   arena->allocated += padding + size;

   return pointer;
}

#endif /* __ARENA_DEF_ */