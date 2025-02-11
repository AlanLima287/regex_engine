#ifndef __STACK_DEF_
   #include "stack.h"
#else

bool stack_init(Stack* stack, size_t size) {
   stack->capacity = size < 16 ? 16 : size;
   stack->top = 0;

   stack->frame = malloc(stack->capacity);
   return stack->frame != NULL;
}

bool stack_expand(Stack* stack) {
   stack->capacity += stack->capacity << 1;
   void* new_pointer = realloc(stack->frame, stack->capacity);
   if (new_pointer == NULL) return false;

   stack->frame = new_pointer;
   return true;
}

void* stack_push(Stack* stack, size_t size) {
   if (stack->capacity < stack->top + size) stack_expand(stack);
   
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