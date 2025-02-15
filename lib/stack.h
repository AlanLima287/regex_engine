#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Stack {
   void* frame;
   size_t capacity;
   size_t top;
} Stack;

// #define stack_scaling_function(capacity) floor(capacity * 1.5)
#define stack_scaling_function(capacity) (capacity + (capacity << 1))

/* Initializes the stack.
 * @param  stack: a pointer to a stack structure
 * @param  size:  the amount of bytes to be preallocated, if <16, then 16 bytes will be allocated
 * @return        returns `true` on success, `false` otherwise
 */
bool stack_init(Stack* stack, size_t size);

/* Reverse space for new elements at the top of the stack
 * @param  stack: a pointer to a stack structure
 * @param  size:  at least the amount of bytes to be reserved for the stack
 * @return        returns `true` on success, `false` otherwise
*/
bool stack_reserve(Stack* stack, size_t size);

/* Reverse space for exacly `size` new elements at the top of the stack
 * @param  stack: a pointer to a stack structure
 * @param  size:  the amount of bytes to be reserved for the stack
 * @return        returns `true` on success, `false` otherwise
*/
bool stack_reserve_exact(Stack* stack, size_t size);

/* Clears the stack, by setting the top back to zero.
 * @param  stack: a pointer to a stack structure
*/
void stack_clear(Stack* stack) {
   stack->top = 0;
}

/* Releases the stack pointer, actions on the stack from here on are undefined.
 * @param  stack: a pointer to a stack structure
*/
void stack_free(Stack* stack) {
   free(stack->frame);
}

/* Pushes a new area at the top of the stack
 * @param  stack: a pointer to a stack structure
 * @param  size:  the amount of bytes to be allocated on the stack
 * @return        returns a pointer to the start of the pushed area
*/
void* stack_push(Stack* stack, size_t size);

/* Peeks at the top of the stack
* @param  stack: a pointer to a stack structure
* @return        returns a pointer to the area at the top of the stack
*/
void* stack_peek(Stack* stack);

/* Pops off the top of the stack
 * @param  stack: a pointer to a stack structure
 * @param  size:  the amount of bytes to be deallocated on the stack
 * @return        returns a pointer to the area at the top of the stack
*/
void* stack_pop(Stack* stack, size_t size);

#define __STACK_DEF_
   #include "stack.c"
#undef __STACK_DEF_