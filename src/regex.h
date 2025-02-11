#include <stdbool.h>
#include <stdint.h>

#include "../lib/bittools.h"
#include "../lib/arena.h"

typedef bool(*match_t)(char);
typedef size_t index_t;

typedef struct {
   match_t match;
   index_t state;
} Transition;

typedef struct {
   index_t* empty_transitions;
   Transition* transitions;
} State;

typedef struct {
   State* states;
   mword bitmap;
} Automaton;