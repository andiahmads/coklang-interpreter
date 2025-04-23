
typedef char *TokenType;

typedef struct {
  TokenType type;
  char *literal;
} Token;

const char *ILEGAL = "ILEGAL";
const char *EOF = "EOF";

// identifier + literal
const char *IDENT = "IDENT";
const char *INT = "INT";

// operator
const char *ASSIGN = "=";
const char *PLUS = "+";

// Delimeters
const char *COMMA = ",";
const char *SEMICOLONJJ = ";";

const char *LPAREN = "(";
const char *RPAREN = ")";
const char *LBRACE = "{";
const char *RBRACE = "}";

// keyword
const char *FUNCTION = "FUNCTION";
const char *LET = "LET";
