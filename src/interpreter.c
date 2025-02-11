#ifndef __REGEX_INTERPRETER_DEF_
   #include "interpreter.h"
#else

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

Stack regex_tokenize(const char* expression) {

   Stack stack;
   stack_init(&stack, 0);

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

Stack regex_parse(Token* token) {

}

#endif