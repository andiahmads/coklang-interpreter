#ifndef TOKEN_H
#define TOKEN_H

typedef char *TokenType;
typedef struct {
  TokenType type;
  char *literal;

} Token;

#define FUNCTION "FUNCTION"
#define LET "LET"
#define IDENT "IDENT"
#define ILLEGAL "ILLEGAL"
#define TOKEN_EOF "EOF" // Ganti EOF menjadi TOKEN_EOF
#define INT "INT"
#define ASSIGN "="
#define PLUS "+"
#define COMMA ","
#define SEMICOLON ";"
#define LPAREN "("
#define RPAREN ")"
#define LBRACE "{"
#define RBRACE "}"

// const char *ILEGAL = "ILEGAL";
// const char *EOF_TOK = "EOF";
//
// // identifier + literal
// const char *IDENT = "IDENT";
// const char *INT = "INT";
//
// // operator
// const char *ASSIGN = "=";
// const char *PLUS = "+";
//
// // Delimeters
// const char *COMMA = ",";
// const char *SEMICOLON = ";";
//
// const char *LPAREN = "(";
// const char *RPAREN = ")";
// const char *LBRACE = "{";
// const char *RBRACE = "}";
//
// // keyword
// const char *FUNCTION = "FUNCTION";
// const char *LET = "LET";

#endif // !TOKEN_H
