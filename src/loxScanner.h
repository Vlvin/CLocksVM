#ifndef LOX_SCANNER_H
#define LOX_SCANNER_H

#include "loxToken.h"
#include <oneFileSTD.h>

typedef struct LoxToken LoxToken;

typedef struct LoxScanner {
  const char *start, *current;
  size_t line;
} LoxScanner;

/// @brief LoxScanner constructor
/// @param source lox source code
/// @return Self@LoxScanner
void LoxScanner_init(LoxScanner *self, const char *source);
/// @brief scans next token of lox source
/// @return scanned token
LoxToken LoxScanner_scanToken(LoxScanner *self);
/// @brief compares char in source under "cursor" with expected
bool LoxScanner_match(LoxScanner *self, const char expected);
/// @brief tells whether "cursor" is at the end of lox source code
bool LoxScanner_isAtEnd(LoxScanner *self);
/// @brief move "cursor" at the next position
/// @return char at "cursor" position before move
char LoxScanner_advance(LoxScanner *self);
/// @return char at "cursor" position
char LoxScanner_peek(LoxScanner *self);
/// @return char at next position
char LoxScanner_peekNext(LoxScanner *self);
void LoxScanner_skipWhiteSpaces(LoxScanner *self);

// LoxToken LoxScanner_stringInterpolation(LoxScanner* self);
LoxToken LoxScanner_string(LoxScanner *self);
LoxToken LoxScanner_number(LoxScanner *self);
LoxToken LoxScanner_identifier(LoxScanner *self);
LoxToken LoxScanner_makeToken(LoxScanner *self, TokenType type);

LoxToken LoxScanner_errorToken(LoxScanner *self, const char *message);

TokenType LoxScanner_identifierType(LoxScanner *self);

/// @brief LoxScanner destructor
void LoxScanner_free(LoxScanner *self);

#endif
