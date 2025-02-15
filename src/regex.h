#include <stdbool.h>
#include <stdint.h>

// #include "../lib/arena.h"
#include "../lib/bittools.h"
#include "../lib/stack.h"

typedef size_t index_t;

typedef struct {
   char* match;
   index_t state;
} Transition;

typedef struct {
   Stack empty_transitions;
   Stack transitions;
} State;

typedef struct {
   Stack states;
   mword* bitmap[2];
} Automaton;

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

bool match(const char* matching, char ch);

Stack regex_tokenize(const char* expression);
void regex_parse(Token* tokens);

#define __REGEX_DEF_
   #include "regex.c"
#undef __REGEX_DEF_