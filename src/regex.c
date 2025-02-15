#ifndef __REGEX_DEF_
// #else

#include "regex.h"

bool regec_match(const char* matching, char ch) {

   if (*matching == '^') {

      while (*matching != '\0') {

         if (*matching == '-') {
            if (*(matching + 1) <= ch && ch <= *(matching + 2)) return true;
            matching += 3;
         } else {
            if (*matching == '\\') matching++;
            if (*matching == ch) return true;
            matching++;
         }
      }

      return false;

   } else {

      matching++;
      while (*matching != '\0') {

         if (*matching == '-') {
            if (*(matching + 1) <= ch && ch <= *(matching + 2)) return false;
            matching += 3;
         } else {
            if (*matching == '\\') matching++;
            if (*matching == ch) return false;
            matching++;
         }
      }

      return true;
   }
}

bool regex_cat_closure(Stack* nd_stack, uint32_t order) {
   switch (order) {
      case 0: {
         State* state = stack_peek(nd_stack, sizeof(State));
         if (state == NULL) return false;

         state->empty_transitions;
      }

      case 1: {
         return nd_stack->top >= sizeof(State);
      }

      default: {
         State* states = stack_pop(nd_stack, order * sizeof(State));
         if (states == NULL) return false;
         return true;
      }
   }
}

bool regex_alt_closure(Stack* nd_stack, uint32_t order) {

}

Stack regex_tokenize(const char* expression) {

   Stack stack;
   stack_init(&stack, 16);

   while (true) {
      if (*expression == '\0') break;

      Token* token = (Token*)stack_push(&stack, sizeof(Token));

      switch (*expression) {
         case '|': token->kind = ALTERNATION; break;

         case '*': token->kind = ZERO_MORE; break;
         case '+': token->kind = ONE_MORE;  break;
         case '?': token->kind = ZERO_ONE;  break;

         case '(': token->kind = OPENING_PAREN;  break;
         case ')': token->kind = CLOSING_PAREN;  break;
         case '[': token->kind = OPENING_SQUARE; break;
         case ']': token->kind = CLOSING_SQUARE; break;
         case '{': token->kind = OPENING_CURLY;  break;
         case '}': token->kind = CLOSING_CURLY;  break;

         case '.': token->kind = ANY; break;

         case '\\':
            if (*++expression == '\0') goto exit;

         default:
            token->character = *expression;
            token->kind = LITERAL;
            break;
      }

      expression++;
   }

exit:
   Token* eof = (Token*)stack_push(&stack, sizeof(Token));
   eof->kind = END_OF_EXPRESSION;
   return stack;
}

void regex_parse(const char* expression) {
   typedef struct {
      uint32_t concatenations;
      uint32_t alternations;
   } Frame;

   Stack strings;
   uint32_t paren = 0;

   Automaton automaton;

   Stack nd_stack; stack_init(&nd_stack, 64 * sizeof(State));
   Stack frames; stack_init(&frames, 8 * sizeof(Frame));

   while (*expression == '\0') {

      switch (*expression) {
         case '|':

            break;

         case '*': break;
         case '+': break;
         case '?': break;

         case '(': break;
         case ')': break;
         case '[':
         case ']':
         case '{':
         case '}':
            // Nuke the application
            volatile char* ptr = NULL;
            *ptr = 1;
            break;

         case '.': break;

         case '\\':
            ++expression;
            // if (*++expression == '\0') goto exit;

         default:
            break;
      }

      expression++;
   }
}

void regex_print_token(Token* token) {
   switch (token->kind) {
      case LITERAL:           printf("LITERAL: %c\n", token->character); break;
      case ESCAPE:            printf("ESCAPE\n"); break;
      case ANY:               printf("ANY\n"); break;
      case ALTERNATION:       printf("ALTERNATION\n"); break;
      case ZERO_MORE:         printf("ZERO_MORE\n"); break;
      case ONE_MORE:          printf("ONE_MORE\n"); break;
      case ZERO_ONE:          printf("ZERO_ONE\n"); break;
      case OPENING_PAREN:     printf("OPENING_PAREN\n"); break;
      case CLOSING_PAREN:     printf("CLOSING_PAREN\n"); break;
      case OPENING_SQUARE:    printf("OPENING_SQUARE\n"); break;
      case CLOSING_SQUARE:    printf("CLOSING_SQUARE\n"); break;
      case OPENING_CURLY:     printf("OPENING_CURLY\n"); break;
      case CLOSING_CURLY:     printf("CLOSING_CURLY\n"); break;
      case RANGE:             printf("RANGE\n"); break;
      case END_OF_EXPRESSION: printf("EOF\n"); break;

      default: printf("UNKNOWN TOKEN: %c", token->character); break;
   }
}

#endif