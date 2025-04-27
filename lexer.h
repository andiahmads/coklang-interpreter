#ifndef LEXER_H
#define LEXER_H

#include <token.h>

typedef struct {
  char *input;
  int position;
  int readPosition;
  char ch;
} Lexer;

Token *nextToken(Lexer *l);
Lexer *newLexer(const char *input);

#endif
