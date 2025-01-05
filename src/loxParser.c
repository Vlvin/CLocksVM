
#include <loxScanner.h>
#include <loxParser.h>
#include <loxChunk.h>
#include <loxObject.h>
#include <loxErrors.h>
#include <loxCompiler.h>
static LoxParseRule rules[] = {
    [TOKEN_LEFT_PAREN]    = {LoxParser_grouping, NULL,             PREC_NONE},
    [TOKEN_RIGHT_PAREN]   = {NULL,               NULL,             PREC_NONE},
    [TOKEN_LEFT_BRACE]    = {NULL,               NULL,             PREC_NONE},
    [TOKEN_RIGHT_BRACE]   = {NULL,               NULL,             PREC_NONE},
    [TOKEN_COMMA]         = {NULL,               NULL,             PREC_NONE},
    [TOKEN_DOT]           = {NULL,               NULL,             PREC_NONE},
    [TOKEN_MINUS]         = {LoxParser_unary,    LoxParser_binary, PREC_TERM},
    [TOKEN_PLUS]          = {NULL,               LoxParser_binary, PREC_TERM},
    [TOKEN_SEMICOLON]     = {NULL,               NULL,             PREC_NONE},
    [TOKEN_SLASH]         = {NULL,               LoxParser_binary, PREC_FACTOR},
    [TOKEN_STAR]          = {NULL,               LoxParser_binary, PREC_FACTOR},
    [TOKEN_MOD]           = {NULL,               NULL,             PREC_NONE},
    [TOKEN_BANG]          = {LoxParser_unary,    NULL,             PREC_NONE},
    [TOKEN_EQUAL]         = {NULL,               NULL,             PREC_NONE},
    [TOKEN_BANG_EQUAL]    = {NULL,               LoxParser_binary, PREC_EQUALITY},
    [TOKEN_EQUAL_EQUAL]   = {NULL,               LoxParser_binary, PREC_EQUALITY},
    [TOKEN_GREATER]       = {NULL,               LoxParser_binary, PREC_EQUALITY},
    [TOKEN_GREATER_EQUAL] = {NULL,               LoxParser_binary, PREC_EQUALITY},
    [TOKEN_LESS]          = {NULL,               LoxParser_binary, PREC_EQUALITY},
    [TOKEN_LESS_EQUAL]    = {NULL,               LoxParser_binary, PREC_EQUALITY},
    [TOKEN_IDENTIFIER]    = {NULL,               NULL,             PREC_NONE},
    [TOKEN_STRING]        = {LoxParser_string,   NULL,             PREC_NONE},
    [TOKEN_NUMBER]        = {LoxParser_number,   NULL,             PREC_NONE},
    [TOKEN_AND]           = {NULL,               NULL,             PREC_NONE},
    [TOKEN_CLASS]         = {NULL,               NULL,             PREC_NONE},
    [TOKEN_ELSE]          = {NULL,               NULL,             PREC_NONE},
    [TOKEN_FUN]           = {NULL,               NULL,             PREC_NONE},
    [TOKEN_FOR]           = {NULL,               NULL,             PREC_NONE},
    [TOKEN_IF]            = {NULL,               NULL,             PREC_NONE},
    [TOKEN_FALSE]         = {LoxParser_literal,  NULL,             PREC_NONE},
    [TOKEN_TRUE]          = {LoxParser_literal,  NULL,             PREC_NONE},
    [TOKEN_NIL]           = {LoxParser_literal,  NULL,             PREC_NONE},
    [TOKEN_OR]            = {NULL,               NULL,             PREC_NONE},
    [TOKEN_CONST]         = {NULL,               NULL,             PREC_NONE},
    [TOKEN_PRINT]         = {NULL,               NULL,             PREC_NONE},
    [TOKEN_RETURN]        = {NULL,               NULL,             PREC_NONE},
    [TOKEN_SUPER]         = {NULL,               NULL,             PREC_NONE},
    [TOKEN_THIS]          = {NULL,               NULL,             PREC_NONE},
    [TOKEN_VAR]           = {NULL,               NULL,             PREC_NONE},
    [TOKEN_WHILE]         = {NULL,               NULL,             PREC_NONE},
    [TOKEN_STATIC]        = {NULL,               NULL,             PREC_NONE},
    [TOKEN_INCLUDE]       = {NULL,               NULL,             PREC_NONE},
    [TOKEN_ERROR]         = {NULL,               NULL,             PREC_NONE},
    [TOKEN_EOF]           = {NULL,               NULL,             PREC_NONE},
};

void LoxParser_init(LoxParser *self, LoxCompiler *masterCompiler)
{
  LoxParser_reset(self);
  self->masterCompiler = masterCompiler;
}
void LoxParser_reset(LoxParser *self)
{
  (*self) = (LoxParser){0};
}
void LoxParser_free(LoxParser *self)
{
  LoxParser_reset(self);
}


void LoxParser_advance(LoxParser *self, LoxScanner *scanner)
{
  self->previous = self->current;

  while (true)
  {
    self->current = LoxScanner_scanToken(scanner);

    if (self->current.type != TOKEN_ERROR)
      break;

    errorAtCurrent(self, "Expected expression");
  }
}

void LoxParser_consume(LoxParser *self, LoxScanner *scanner, TokenType type, const char *error_message)
{
  if (self->current.type != type)
  {
    self->hadError = true;
    errorAtCurrent(self, error_message);
  }
  LoxParser_advance(self, scanner);
}

void LoxParser_expression(LoxParser *self)
{
  LoxParser_parsePrecedence(self, PREC_ASSIGNMENT);
}

void LoxParser_string(LoxParser *self)
{
  _LoxCompiler_emitConstant(self->masterCompiler,
    LOX_OBJECT_VAL( // for " at start      and for " at the end
      copyString(self->previous.start + 1, self->previous.start + self->previous.size - 1)
    )
  );
}

void LoxParser_number(LoxParser *self)
{
  double value = strtod(self->previous.start, NULL);
  _LoxCompiler_emitConstant(self->masterCompiler, LOX_NUMBER_VAL(value));
}


void LoxParser_grouping(LoxParser *self)
{
  LoxParser_expression(self);
  LoxParser_consume(self, &self->masterCompiler->scanner, TOKEN_RIGHT_PAREN, "Expect ')' after expression");
}
void LoxParser_unary(LoxParser *self)
{
  TokenType operator= self->previous.type;

  LoxParseRule *rule = LoxParser_getRule(operator);
  LoxParser_parsePrecedence(self, (LoxPrecedence)(rule->precedence + 1));

  LoxCompiler *compiler = self->masterCompiler;
  switch (operator)
  {
  case TOKEN_MINUS:
    _LoxCompiler_emitByte(compiler, OP_NEGATE);
    break;
  case TOKEN_BANG:
    _LoxCompiler_emitByte(compiler, OP_NOT);
    break;
  default:
    return;
  }
}

inline static LoxParseRule *LoxParser_getRule(TokenType type)
{
  return &rules[type];
}

void LoxParser_binary(LoxParser *self)
{
  TokenType operator= self->previous.type;
  LoxParseRule *rule = LoxParser_getRule(operator);
  LoxParser_parsePrecedence(self, (LoxPrecedence)(rule->precedence + 1));

  LoxCompiler *compiler = self->masterCompiler;

  switch (operator)
  {
  case TOKEN_PLUS:
    _LoxCompiler_emitByte(compiler, OP_ADD);
    break;
  case TOKEN_MINUS:
    _LoxCompiler_emitByte(compiler, OP_SUBSTRACT);
    break;
  case TOKEN_STAR:
    _LoxCompiler_emitByte(compiler, OP_MULTIPLY);
    break;
  case TOKEN_SLASH:
    _LoxCompiler_emitByte(compiler, OP_DIVIDE);
    break;
  case TOKEN_BANG_EQUAL:
    _LoxCompiler_emitBytes(self->masterCompiler, 2, OP_EQUALS, OP_NOT);
    break;
  case TOKEN_EQUAL_EQUAL:
    _LoxCompiler_emitByte(self->masterCompiler, OP_EQUALS);
    break;
  case TOKEN_GREATER:
    _LoxCompiler_emitByte(self->masterCompiler, OP_GREATER);
    break;
  case TOKEN_GREATER_EQUAL:
    _LoxCompiler_emitBytes(self->masterCompiler, 2, OP_LESS, OP_NOT);
    break;
  case TOKEN_LESS:
    _LoxCompiler_emitByte(self->masterCompiler, OP_LESS);
    break;
  case TOKEN_LESS_EQUAL:
    _LoxCompiler_emitBytes(self->masterCompiler, 2, OP_GREATER, OP_NOT);
    break;
  }
}

void LoxParser_literal(LoxParser *self)
{
  switch (self->previous.type)
  {
    case TOKEN_TRUE:
      _LoxCompiler_emitByte(self->masterCompiler, OP_TRUE);
      break;
    case TOKEN_FALSE:
      _LoxCompiler_emitByte(self->masterCompiler, OP_FALSE);
      break;
    case TOKEN_NIL:
      _LoxCompiler_emitByte(self->masterCompiler, OP_NIL);
      break;
    default: return;
  }
}

void LoxParser_parsePrecedence(LoxParser *self, LoxPrecedence precedence)
{
  LoxParser_advance(self, &self->masterCompiler->scanner);
  ParseFn prefixRule = LoxParser_getRule(self->previous.type)->prefix;
  if (prefixRule == NULL)
  {
    errorAtCurrent(self, "Expected expression");
    return;
  }

  prefixRule(self);

  while (precedence <= LoxParser_getRule(self->current.type)->precedence)
  {
    LoxParser_advance(self, &self->masterCompiler->scanner);
    ParseFn infixRule = LoxParser_getRule(self->previous.type)->infix;
    if (infixRule != NULL)
      infixRule(self);
  }
}