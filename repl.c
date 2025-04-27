#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROMPT ">> "
#define MAX_LINE 1024

void start(FILE *in, FILE *out) {
  char line[MAX_LINE];
  while (1) {
    fprintf(out, "%s", PROMPT);
    fflush(out);
    if (fgets(line, MAX_LINE, in) == NULL) {
      break;
    }
    line[strcspn(line, "\n")] = '\0';
    printf("Processing line: %s\n", line);
    Lexer *l = newLexer(line);
    if (!l) {
      fprintf(out, "Gagal membuat lexer\n");
      continue;
    }
    Token *tok;
    while (1) {
      tok = nextToken(l);
      if (!tok) {
        fprintf(out, "Gagal membuat token\n");
        break;
      }
      // printf("Token: %p, Type: %s, Literal: %s\n", (void *)tok, tok->type,
      //        tok->literal ? tok->literal : "");
      if (tok->type == TOKEN_EOF) {
        break;
      }
      fprintf(out, "{Type:%s Literal:%s}\n", tok->type,
              tok->literal ? tok->literal : "");
      if (tok->literal) {
        free(tok->literal);
        tok->literal = NULL;
      }
      free(tok);
    }
    if (tok) {
      printf("EOF token: %p, Type: %s, Literal: %s\n", (void *)tok, tok->type,
             tok->literal ? tok->literal : "");
      if (tok->literal) {
        free(tok->literal);
      }
      free(tok);
    }
    if (l->input) {
      free(l->input);
      l->input = NULL;
    }
    printf("Freeing lexer: %p\n", (void *)l);
    free(l);
  }
}
