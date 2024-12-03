#ifndef LOX_PARSER_H
#define LOX_PARSER_H

#include <loxToken.h>

typedef struct LoxParser {
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

typedef struct {
  LoxPrecedence precedence;
} LoxParseRule;
typedef struct LoxScanner LoxScanner;



inline static void LoxParser_advance(LoxParser* self, LoxScanner *scanner);
inline static int LoxParser_expression(LoxParser* self, LoxScanner *scanner);
inline static int LoxParser_consume(LoxParser* self, LoxScanner *scanner, TokenType type, const char* error_message);

#endif