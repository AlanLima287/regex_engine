#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// #include "../lib/bittools.h"
// #include "../lib/arena.h"
#include "../lib/stack.h"

typedef enum {
   LITERAL,
   ESCAPE,
   ANY,

   ALTERNATION,

   ZERO_MORE,
   ONE_MORE,
   ZERO_ONE,

   OPENING_PAREN,
   CLOSING_PAREN,
   OPENING_SQUARE,
   CLOSING_SQUARE,
   OPENING_CURLY,
   CLOSING_CURLY,

   RANGE,

   END_OF_EXPRESSION = -1,
} TokenKind;

typedef struct {
   TokenKind kind;
   char character;
} Token;

void regex_print_token(Token* token);

Stack regex_tokenize(const char* expression);
Stack regex_parse(Stack* stack);

#define __REGEX_INTERPRETER_DEF_
   #include "interpreter.c"
#undef __REGEX_INTERPRETER_DEF_
