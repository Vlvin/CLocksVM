#ifndef LOX_PARSER_H
#define LOX_PARSER_H

#include <loxToken.h>
#include <loxScanner.h>

typedef struct LoxCompiler LoxCompiler;
typedef struct LoxParser {
  LoxCompiler* masterCompiler;
  LoxToken previous;
  LoxToken current;
  bool hadError;
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


typedef void (*ParseFn)(LoxParser*);

typedef struct LoxParseRule {
  ParseFn prefix;
  ParseFn infix;
  LoxPrecedence precedence;
} LoxParseRule;

typedef struct LoxScanner LoxScanner;



void LoxParser_init(LoxParser* self, LoxCompiler* masterCompiler);
void LoxParser_reset(LoxParser* self);
void LoxParser_free(LoxParser* self);
void LoxParser_advance(LoxParser* self, LoxScanner *scanner);
void LoxParser_consume(LoxParser* self, LoxScanner *scanner, TokenType type, const char* error_message);
inline static LoxParseRule* LoxParser_getRule(TokenType type);

void LoxParser_expression(LoxParser* self);
void LoxParser_number(LoxParser* self);
void LoxParser_grouping(LoxParser* self);
void LoxParser_unary(LoxParser* self);
void LoxParser_binary(LoxParser* self);
void LoxParser_literal(LoxParser *self);
void LoxParser_parsePrecedence(LoxParser* self, LoxPrecedence precedance);

#endif