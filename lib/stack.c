#ifndef __STACK_DEF_
   #include "stack.h"
#else

bool stack_init(Stack* stack, size_t size) {
   stack->capacity = size < 2 ? 2 : size;
   stack->top = 0;

   stack->frame = malloc(stack->capacity);
   return stack->frame != NULL;
}

bool stack_reserve(Stack* stack, size_t size) {
   do stack->capacity = stack_scaling_function(stack->capacity);
   while (stack->capacity < size + stack->top);
   
   void* new_pointer = realloc(stack->frame, stack->capacity);
   if (new_pointer == NULL) return false;

   stack->frame = new_pointer;
   return true;
}

bool stack_reserve_exact(Stack* stack, size_t size) {
   if (stack->top + size <= stack->capacity) return true;
   
   stack->capacity = stack->top + size;
   void* new_pointer = realloc(stack->frame, stack->capacity);
   if (new_pointer == NULL) return false;

   stack->frame = new_pointer;
   return true;
}

void* stack_push(Stack* stack, size_t size) {
   if (stack->capacity < stack->top + size) stack_reserve(stack, size);
   
   void* pointer = (void*)((uintptr_t)stack->frame + stack->top);
   stack->top += size;

   return pointer;
}

void* stack_peek(Stack* stack) {
   return (void*)((uintptr_t)stack->frame + stack->top);
}

void* stack_pop(Stack* stack, size_t size) {
   return (void*)((uintptr_t)stack->frame + stack->top);
   stack->top -= size;
}

#endif