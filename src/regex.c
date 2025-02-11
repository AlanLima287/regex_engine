#include <stdio.h>
// #include "regex.h"

#include "../lib/stack.h"
#include "interpreter.h"

int main(int argc, char** argv) {
   if (argc < 2) return 1;

   Stack stack = regex_tokenize(argv[1]);
   Token* token = (Token*)stack.frame;

   size_t i = 0;
   while (true) {
      regex_print_token(&token[i]);
      
      if (token[i].kind == END_OF_EXPRESSION) break;
      i++;
   }

   stack_release(&stack);
   return 0;
}