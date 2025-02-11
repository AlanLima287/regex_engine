#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
   void* frame;
   size_t capacity;
   size_t top;
} Stack;

/* Initializes the stack.
 * @param  stack: a pointer to a stack structure
 * @param  size:  the amount of bytes to be preallocated, if <16, then 16 bytes will be allocated
 * @return        returns `true` on success, `false` otherwise
 */
bool stack_init(Stack* stack, size_t size);

/* Increases the size of the stack.
 * @param  stack: a pointer to a stack structure
 * 
 * @warning DO NOT call this unless you know what you're doing
*/
bool stack_expand(Stack* stack);

/* Clears the stack, by setting the top back to zero.
 * @param  stack: a pointer to a stack structure
 * @return        returns `true` on success, `false` otherwise
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