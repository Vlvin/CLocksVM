#ifndef LOX_PARSER_H
#define LOX_PARSER_H

#include <loxScanner.h>
#include <loxToken.h>

typedef struct LoxCompiler LoxCompiler;
typedef struct LoxParser {
  LoxCompiler *masterCompiler;
  LoxToken previous;
  LoxToken current;
  bool hadError;
  bool panicMode;
} LoxParser;

typedef enum {
  PREC_NONE,
  PREC_ASSIGNMENT,
  PREC_OR,
  PREC_AND,
  PREC_EQUALITY,
  PREC_TERM,
  PREC_FACTOR,
  PREC_UNARY,
  PREC_CALL,
  PREC_PRIMARY
} LoxPrecedence;

typedef void (*ParseFn)(LoxParser *);

typedef struct LoxParseRule {
  ParseFn prefix;
  ParseFn infix;
  LoxPrecedence precedence;
} LoxParseRule;

typedef struct LoxScanner LoxScanner;

void LoxParser_init(LoxParser *self, LoxCompiler *masterCompiler);
void LoxParser_reset(LoxParser *self);
void LoxParser_free(LoxParser *self);
void LoxParser_advance(LoxParser *self, LoxScanner *scanner);
void LoxParser_consume(LoxParser *self, LoxScanner *scanner, TokenType type,
                       const char *error_message);
bool LoxParser_check(LoxParser *self, TokenType type);
bool LoxParser_match(LoxParser *self, LoxScanner *scanner, TokenType type);
inline static LoxParseRule *LoxParser_getRule(TokenType type);

uint16_t LoxParser_parseVariable(LoxParser *self, LoxScanner *scanner,
                                 const char *errorMessage);
void LoxParser_defineVariable(LoxParser *self, uint16_t name);
void LoxParser_syncronize(LoxParser *self, LoxScanner *scanner);
void LoxParser_declaration(LoxParser *self, LoxScanner *scanner);
void LoxParser_statement(LoxParser *self, LoxScanner *scanner);
// expressions
void LoxParser_expression(LoxParser *self);
void LoxParser_string(LoxParser *self);
void LoxParser_number(LoxParser *self);
void LoxParser_grouping(LoxParser *self);
void LoxParser_unary(LoxParser *self);
void LoxParser_binary(LoxParser *self);
void LoxParser_literal(LoxParser *self);
void LoxParser_parsePrecedence(LoxParser *self, LoxPrecedence precedance);
// statements
void LoxParser_printStatement(LoxParser *self, LoxScanner *scanner);
void LoxParser_expressionStatement(LoxParser *self, LoxScanner *scanner);
void LoxParser_varDeclaration(LoxParser *self, LoxScanner *scanner);
#endif
