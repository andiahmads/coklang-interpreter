#ifndef TOKEN_H
#define TOKEN_H

typedef char *TokenType;
typedef struct {
  TokenType type;
  char *literal;

} Token;

// keyword
#define FUNCTION "FUNCTION"
#define LET "LET"
#define TRUE "TRUE"
#define FALSE "FALSE"
#define IF "IF"
#define ELSE "IF"
#define RETURN "RETURN"

#define IDENT "IDENT"
#define ILLEGAL "ILLEGAL"
#define TOKEN_EOF "EOF" // Ganti EOF menjadi TOKEN_EOF
#define INT "INT"

// operator
#define ASSIGN "="
#define PLUS "+"
#define MINUS "-"
#define BANG "!"
#define ASTERISK "*"
#define SLASH "/"

#define COMMA ","
#define SEMICOLON ";"
#define LPAREN "("
#define RPAREN ")"
#define LBRACE "{"
#define RBRACE "}"
#define LT "<"
#define GT ">"

#endif // !TOKEN_H
