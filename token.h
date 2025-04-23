#ifndef TOKEN_H
#define TOKEN_H

typedef char *TokenType;
typedef struct {
  TokenType type;
  char *literal;

} Token;

const char *ILEGAL = "ILEGAL";
const char *EOF_TOK = "EOF";

// identifier + literal
const char *IDENT = "IDENT";
const char *INT = "INT";

// operator
const char *ASSIGN = "=";
const char *PLUS = "+";

// Delimeters
const char *COMMA = ",";
const char *SEMICOLON = ";";

const char *LPAREN = "(";
const char *RPAREN = ")";
const char *LBRACE = "{";
const char *RBRACE = "}";

// keyword
const char *FUNCTION = "FUNCTION";
const char *LET = "LET";

#endif // !TOKEN_H
