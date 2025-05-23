#ifndef LOX_PARSER_H
#define LOX_PARSER_H

#include <loxScanner.h>
#include <loxToken.h>

typedef struct LoxCompiler LoxCompiler;
typedef struct LoxParser {
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

typedef void (*ParseFn)(LoxParser *self, LoxCompiler *compiler, bool canAssign);

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
LoxParseRule *LoxParser_getRule(TokenType type);

uint16_t LoxParser_parseVariable(LoxParser *self, LoxScanner *scanner,
                                 LoxCompiler *compiler,
                                 const char *errorMessage);
void LoxParser_defineVariable(LoxParser *self, LoxCompiler *compiler,
                              uint16_t name);
void LoxParser_declareVariable(LoxParser *self, LoxScanner *scanner,
                               LoxCompiler *compiler);

void LoxParser_namedVariable(LoxParser *self, LoxCompiler *compiler,
                             LoxToken name, bool canAssign);
void LoxParser_syncronize(LoxParser *self, LoxScanner *scanner);
void LoxParser_declaration(LoxParser *self, LoxScanner *scanner,
                           LoxCompiler *compiler);
void LoxParser_statement(LoxParser *self, LoxScanner *scanner,
                         LoxCompiler *compiler);
// expressions
void LoxParser_expression(LoxParser *self, LoxCompiler *compiler);
void LoxParser_string(LoxParser *self, LoxCompiler *compiler, bool canAssign);
void LoxParser_number(LoxParser *self, LoxCompiler *compiler, bool canAssign);
void LoxParser_grouping(LoxParser *self, LoxCompiler *compiler, bool canAssign);
void LoxParser_unary(LoxParser *self, LoxCompiler *compiler, bool canAssign);
void LoxParser_binary(LoxParser *self, LoxCompiler *compiler, bool canAssign);
void LoxParser_literal(LoxParser *self, LoxCompiler *compiler, bool canAssign);
void LoxParser_variable(LoxParser *self, LoxCompiler *compiler, bool canAssign);
void LoxParser_and(LoxParser *self, LoxCompiler *compiler, bool canAssign);
void LoxParser_or(LoxParser *self, LoxCompiler *compiler, bool canAssign);
void LoxParser_parsePrecedence(LoxParser *self, LoxCompiler *compiler,
                               LoxPrecedence precedance);
// statements
void LoxParser_ifStatement(LoxParser *self, LoxScanner *scanner,
                           LoxCompiler *compiler);
void LoxParser_whileStatement(LoxParser *self, LoxScanner *scanner,
                              LoxCompiler *compiler);
void LoxParser_forStatement(LoxParser *self, LoxScanner *scanner,
                            LoxCompiler *compiler);
void LoxParser_printStatement(LoxParser *self, LoxScanner *scanner,
                              LoxCompiler *compiler);
void LoxParser_blockStatement(LoxParser *self, LoxScanner *scanner,
                              LoxCompiler *compiler);
void LoxParser_expressionStatement(LoxParser *self, LoxScanner *scanner,
                                   LoxCompiler *compiler);
void LoxParser_varDeclaration(LoxParser *self, LoxScanner *scanner,
                              LoxCompiler *compiler);
void LoxParser_funDeclaration(LoxParser *self, LoxScanner *scanner,
                              LoxCompiler *compiler);
#endif
