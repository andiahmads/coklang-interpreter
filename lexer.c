#include "token.h"
#include <lexer.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Membaca karakter berikutnya
void readChar(Lexer *l) {
  if (l->readPosition >= strlen(l->input)) {
    l->ch = 0;
  } else {
    l->ch = l->input[l->readPosition];
  }
  l->position = l->readPosition;
  l->readPosition++;
}

// Membuat lexer baru
Lexer *newLexer(const char *input) {
  Lexer *l = (Lexer *)malloc(sizeof(Lexer));
  if (!l) {
    printf("Memory allocation failed for Lexer\n");
    return NULL;
  }
  l->input = strdup(input);
  if (!l->input) {
    printf("Memory allocation failed for input\n");
    free(l);
    return NULL;
  }
  l->position = 0;
  l->readPosition = 0;
  l->ch = 0;
  readChar(l);
  return l;
}

bool isLetter(unsigned char ch) {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || (ch == '_');
}

char *readIdentifier(Lexer *l) {
  int position = l->position;
  while (isLetter(l->ch)) { // Dukung angka dalam identifier
    readChar(l);
  }
  int length = l->position - position;
  char *identifier = malloc(length + 1);
  if (!identifier) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  strncpy(identifier, l->input + position, length);
  identifier[length] = '\0';
  return identifier;
}

typedef struct {
  const char *key;
  TokenType value;
} KeywordEntry;

// Array statis untuk keywords
static const KeywordEntry keywords[] = {
    {"fn", FUNCTION}, {"let", LET},   {"true", TRUE},     {"false", FALSE},
    {"if", IF},       {"else", ELSE}, {"return", RETURN},

};
static const int keywords_count = sizeof(keywords) / sizeof(keywords[0]);

// Mencari TokenType berdasarkan identifier
TokenType LookupIdent(const char *ident) {
  if (ident == NULL) {
    return IDENT;
  }
  for (int i = 0; i < keywords_count; i++) {
    if (strcmp(ident, keywords[i].key) == 0) {
      return keywords[i].value;
    }
  }
  return IDENT;
}

bool isDigitx(unsigned char ch) { return '0' <= ch && ch <= '9'; }

char *readNumber(Lexer *l) {
  int position = l->position;
  while (isDigitx(l->ch)) {
    readChar(l);
  }
  int length = l->position - position;
  char *number = malloc(length + 1);
  if (!number) {
    printf("Memory allocation failed\n");
    exit(1);
  }
  strncpy(number, l->input + position, length);
  number[length] = '\0';
  return number;
}

// Fungsi peekChar (dari konversi sebelumnya) digunakan untuk melihat karakter
// berikutnya tanpa memajukan posisi:
// Jika karakter berikutnya (dari peekChar) adalah =, maka ini adalah token ==:
// Simpan karakter saat ini (ch = l->ch, yaitu =).
// Maju ke karakter berikutnya (readChar(l)), sehingga l->ch menjadi =.
// Alokasi memori untuk literal (3 byte: 2 untuk ==, 1 untuk \0).
// Simpan "==" ke tok->literal.
char peekChar(Lexer *l) {
  if (l->readPosition >= strlen(l->input)) {
    return 0;
  } else {
    return l->input[l->readPosition];
  }
}

Token *nextToken(Lexer *l) {
  Token *tok = (Token *)malloc(sizeof(Token));
  if (!tok) {
    printf("Memory allocation failed for Token\n");
    exit(1);
  }
  tok->literal = NULL; // Alokasi dilakukan per case

  while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
    readChar(l);
  }

  switch (l->ch) {
  case '=':
    if (peekChar(l) == '=') {
      char ch = l->ch;
      readChar(l);
      tok->type = EQ;
      tok->literal = (char *)malloc(3 * sizeof(char));
      if (!tok->literal) {
        printf("Memory allocation failed for literal\n");
        free(tok);
        exit(1);
      }

      tok->literal[0] = ch;
      tok->literal[1] = l->ch;
      tok->literal[2] = '\0';
    } else {
      tok->type = ASSIGN;
      tok->literal = (char *)malloc(2 * sizeof(char));
      if (!tok->literal) {
        printf("Memory allocation failed for literal\n");
        free(tok);
        exit(1);
      }

      tok->literal[0] = l->ch;
      tok->literal[1] = '\0';
    }
    readChar(l);
    break;

  case '+':
    tok->type = PLUS;
    tok->literal = (char *)malloc(2 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    readChar(l);
    break;

  case '-':
    tok->type = MINUS;
    tok->literal = (char *)malloc(2 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    readChar(l);
    break;

  case '!':
    if (peekChar(l) == '=') {
      char ch = l->ch;
      readChar(l);
      tok->type = NOT_EQ;
      tok->literal = (char *)malloc(3 * sizeof(char));
      if (!tok->literal) {
        printf("Memory allocation failed for literal\n");
        free(tok);
        return NULL;
      }
      tok->literal[0] = ch;
      tok->literal[1] = l->ch;
      tok->literal[2] = '\0';
    } else {
      tok->type = BANG;
      tok->literal = (char *)malloc(2 * sizeof(char));
      if (!tok->literal) {
        printf("Memory allocation failed for literal\n");
        free(tok);
        return NULL;
      }
      tok->literal[0] = l->ch;
      tok->literal[1] = '\0';
    }
    readChar(l);
    break;

  case '*':
    tok->type = ASTERISK;
    tok->literal = (char *)malloc(2 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    readChar(l);
    break;

  case '/':
    tok->type = SLASH;
    tok->literal = (char *)malloc(2 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    readChar(l);
    break;

  case ';':
    tok->type = SEMICOLON;
    tok->literal = (char *)malloc(2 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    readChar(l);
    break;

  case '(':
    tok->type = LPAREN;
    tok->literal = (char *)malloc(2 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    readChar(l);
    break;

  case ')':
    tok->type = RPAREN;
    tok->literal = (char *)malloc(2 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    readChar(l);
    break;

  case ',':
    tok->type = COMMA;
    tok->literal = (char *)malloc(2 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    readChar(l);
    break;

  case '{':
    tok->type = LBRACE;
    tok->literal = (char *)malloc(2 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    readChar(l);
    break;

  case '}':
    tok->type = RBRACE;
    tok->literal = (char *)malloc(2 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    readChar(l);
    break;

  case '<':
    tok->type = LT;
    tok->literal = (char *)malloc(2 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    readChar(l);
    break;

  case '>':
    tok->type = GT;
    tok->literal = (char *)malloc(2 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = l->ch;
    tok->literal[1] = '\0';
    readChar(l);
    break;

  case 0:
    tok->type = TOKEN_EOF;
    tok->literal = (char *)malloc(1 * sizeof(char));
    if (!tok->literal) {
      printf("Memory allocation failed for literal\n");
      free(tok);
      return NULL;
    }
    tok->literal[0] = '\0';
    break;

  default:
    if (isLetter(l->ch)) {
      tok->literal = readIdentifier(l);
      if (!tok->literal) {
        printf("readIdentifier failed\n");
        free(tok);
        return NULL;
      }
      tok->type = LookupIdent(tok->literal);
      // readChar sudah dipanggil di readIdentifier
    } else if (isDigitx(l->ch)) {
      tok->type = INT;
      tok->literal = readNumber(l);
      if (!tok->literal) {
        printf("readNumber failed\n");
        free(tok);
        return NULL;
      }
      // readChar sudah dipanggil di readNumber
    } else {
      tok->type = ILLEGAL;
      tok->literal = (char *)malloc(2 * sizeof(char));
      if (!tok->literal) {
        printf("Memory allocation failed for literal\n");
        free(tok);
        return NULL;
      }
      tok->literal[0] = l->ch;
      tok->literal[1] = '\0';
      readChar(l);
    }
    break;
  }

  return tok;
}

typedef struct {
  TokenType expectedType;
  char *expectedLiteral;
} TestCase;

void testNextToken(char *input) {
  TestCase tests[] = {{LET, "let"},       {IDENT, "five"},  {ASSIGN, "="},
                      {INT, "5"},         {SEMICOLON, ";"}, {LET, "let"},
                      {IDENT, "ten"},     {ASSIGN, "="},    {INT, "10"},
                      {SEMICOLON, ";"},   {LET, "let"},     {IDENT, "add"},
                      {ASSIGN, "="},      {FUNCTION, "fn"}, {LPAREN, "("},
                      {IDENT, "x"},       {COMMA, ","},     {IDENT, "y"},
                      {RPAREN, ")"},      {LBRACE, "{"},    {IDENT, "x"},
                      {PLUS, "+"},        {IDENT, "y"},     {SEMICOLON, ";"},
                      {RBRACE, "}"},      {LET, "let"},     {IDENT, "result"},
                      {ASSIGN, "="},      {IDENT, "add"},   {LPAREN, "("},
                      {IDENT, "five"},    {COMMA, ","},     {IDENT, "ten"},
                      {RPAREN, ")"},      {SEMICOLON, ";"}, {BANG, "!"},
                      {MINUS, "-"},       {SLASH, "/"},     {ASTERISK, "*"},
                      {INT, "5"},         {SEMICOLON, ";"}, {INT, "5"},
                      {LT, "<"},          {INT, "10"},      {GT, ">"},
                      {INT, "5"},         {SEMICOLON, ";"}, {IF, "if"},
                      {LPAREN, "("},      {INT, "5"},       {LT, "<"},
                      {INT, "10"},        {RPAREN, ")"},    {LBRACE, "{"},
                      {RETURN, "return"}, {TRUE, "true"},   {SEMICOLON, ";"},
                      {RBRACE, "}"},      {ELSE, "else"},   {LBRACE, "{"},
                      {RETURN, "return"}, {FALSE, "false"}, {SEMICOLON, ";"},
                      {RBRACE, "}"},      {INT, "10"},      {EQ, "=="},
                      {INT, "10"},        {SEMICOLON, ";"}, {INT, "10"},

                      {NOT_EQ, "!="},     {INT, "9"},       {SEMICOLON, ";"},

                      {TOKEN_EOF, ""}

  };
  Lexer *l = newLexer(input);
  for (int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
    Token *tok = nextToken(l);
    if (strcmp(tok->type, tests[i].expectedType) != 0) {
      printf("tests[%d] - tokentype wrong. expected='%s', got='%s'\n", i,
             tests[i].expectedType, tok->type);
      exit(1);
    }
    if (strcmp(tok->literal, tests[i].expectedLiteral) != 0) {
      printf("tests[%d] - literal wrong. expected='%s', got='%s'\n", i,
             tests[i].expectedLiteral, tok->literal);
      exit(1);
    }
    free(tok->literal);
    free(tok);
  }
  free(l);
  printf("all tests passed\n");
}

int has_cok_extension(const char *filename) {
  const char *ext = strrchr(filename, '.');
  return (ext && strcmp(ext, ".cok") == 0);
}

int runLexer() {
  char *filelocation = "./cok-lang/example5.cok";
  if (!has_cok_extension(filelocation)) {
    printf("Hanya file dengan ekstensi .cok yang diizinkan\n");
    return 1;
  }

  FILE *file = fopen(filelocation, "r");
  if (!file) {
    perror("Gagal membuka file");
    return 1;
  }

  // Baca file ke dalam string
  char *input = malloc(1);
  if (!input) {
    printf("Memory allocation failed for input\n");
    fclose(file);
    return 1;
  }
  input[0] = '\0';
  size_t total_length = 0;

  char line[256];
  while (fgets(line, sizeof(line), file)) {
    size_t line_len = strlen(line);
    char *new_input = realloc(input, total_length + line_len + 1);
    if (!new_input) {
      printf("Memory reallocation failed\n");
      free(input);
      fclose(file);
      return 1;
    }
    input = new_input;
    strcpy(input + total_length, line);
    total_length += line_len;
  }
  fclose(file);

  printf("input file: %s\n", input);
  testNextToken(input);
  free(input);
  return 0;
}
