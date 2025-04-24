
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *input;
  int position;
  int readPosition;
  char ch;

} Lexer;

// membaca karakter berikutnya
void readChar(Lexer *l) {
  if (l->readPosition >= strlen(l->input)) {
    l->ch = 0;
  } else {
    l->ch = l->input[l->readPosition];
  }
  l->position = l->readPosition;

  l->readPosition++;
}

// membuat lexer baru
Lexer *newLexer(char *input) {
  Lexer *l = (Lexer *)malloc(sizeof(Lexer));
  l->input = input;
  l->position = 0;
  l->readPosition = 0;
  l->ch = 0;

  // baca karakter
  // Jika input adalah "=+" dan readPosition adalah 0, maka l->ch = '='.
  // if (l->readPosition < strlen(l->input)) {
  //   l->ch = l->input[l->readPosition];
  // } else {
  //   l->ch = 0;
  // }
  // l->position = l->readPosition;
  // l->readPosition++;
  readChar(l);

  return l;
}

Token *nextToken(Lexer *l) {
  Token *tok = (Token *)malloc(sizeof(Token));
  tok->literal = (char *)malloc(
      2 * sizeof(char)); // Untuk menyimpan 1 karakter + null terminator

  // Lewati whitespace (jika ada)
  while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
    readChar(l);
  }
  switch (l->ch) {
  case '=':
    tok->type = ASSIGN;
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    break;

  case ';':
    tok->type = SEMICOLON;
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    break;

  case '(':
    tok->type = LPAREN;
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    break;

  case ')':
    tok->type = RPAREN;
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    break;
  case ',':
    tok->type = COMMA;
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    break;
  case '+':
    tok->type = PLUS;
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    break;
  case '{':
    tok->type = LBRACE;
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    break;
  case '}':
    tok->type = RBRACE;
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    break;
  case 0:
    tok->type = EOF_TOK;
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    break;
  default:
    tok->type = ILEGAL;
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    break;
  }

  readChar(l);
  return tok;
}

typedef struct {
  TokenType expectedType;
  char *expectedLiteral;

} TestCase;

// TestCase
void testNextToken(char *input) {
  // char *input = "=+(){},;";
  TestCase tests[] = {
      {ASSIGN, "="}, {PLUS, "+"},      {LPAREN, "("},
      {RPAREN, ")"}, {LBRACE, "{"},    {RBRACE, "}"},
      {COMMA, ","},  {SEMICOLON, ";"}, {EOF_TOK, ""},

  };

  Lexer *l = newLexer(input);
  for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
    Token *tok = nextToken(l);

    // periksa tipe token
    if (strcmp(tok->type, tests[i].expectedType) != 0) {
      printf("tests [%d]-tokentype wrong. expected= '%s', got= '%s'\n", i,
             tests[i].expectedType, tok->type);
      exit(1);
    }

    if (strcmp(tok->literal, tests[i].expectedLiteral) != 0) {
      printf("tests [%d]-literal wrong. expected= '%s', got= '%s'\n", i,
             tests[i].expectedLiteral, tok->literal);
      exit(1);
    }

    free(tok->literal);
    free(tok);
  }

  free(l);
  printf("all test passed \n");
}

int has_cok_extention(const char *filename) {
  const char *ext = strrchr(filename, '.');
  return (ext && strcmp(ext, ".cok") == 0);
}

int main() {
  char *filelocation = "./cok-lang/example1.cok";
  if (!has_cok_extention(filelocation)) {
    printf("hanya file dengan ekstensi .cok yang diizinkan\n");
    return 1;
  }

  FILE *file = fopen(filelocation, "r");
  if (!file) {
    perror("gagal membuka file");
    return 1;
  }

  char line[256];
  char *input = malloc(1);
  input[0] = '\n';

  size_t total_length = 0;

  while (fgets(line, sizeof(line), file)) {
    size_t line_len = strlen(line);
    total_length += line_len;
    input = realloc(input, total_length + 1);
    strcat(input, line);
  }
  testNextToken(input);
  fclose(file);
  free(input);

  return 0;
}
