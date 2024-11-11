#ifndef LOX_TOKEN_H
#define LOX_TOKEN_H

#include <oneFileSTD.h>

typedef struct LoxScanner LoxScanner;

typedef enum {
  // Single-character tokens.
  TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN, TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE, // Single-character tokens.
  TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS, TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR, // Single-character tokens.
  TOKEN_MOD, // Single-character tokens.

  // One or two character tokens.
  TOKEN_BANG, TOKEN_BANG_EQUAL,  // One or two character tokens.
  TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,  // One or two character tokens.
  TOKEN_GREATER, TOKEN_GREATER_EQUAL,  // One or two character tokens.
  TOKEN_LESS, TOKEN_LESS_EQUAL,  // One or two character tokens.

  // Literals.
  TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER, // Literals.

  // Keywords.
  TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, 
  TOKEN_FALSE, TOKEN_FUN, TOKEN_FOR, 
  TOKEN_IF, TOKEN_NIL, TOKEN_OR, TOKEN_CONST, // Keywords.
  TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, 
  TOKEN_THIS, TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE, 
  TOKEN_STATIC, TOKEN_INCLUDE, // Keywords.

  TOKEN_ERROR, TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    size_t line;
    const char* start;
    size_t size;
} LoxToken;

LoxToken LoxToken_init(
    TokenType type, 
    size_t line, 
    const char* start,
    size_t size
);


#endif