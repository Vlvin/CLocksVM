#include "loxToken.h"
#include <bitsTricks.h>
#include <loxChunk.h>
#include <loxCompiler.h>
#include <loxErrors.h>
#include <loxObject.h>
#include <loxParser.h>
#include <loxScanner.h>
#include <stdint.h>

#define EMIT_LONG_FORK(compiler, OP, bytes)                                    \
  if ((bytes < 256)) {                                                         \
    _LoxCompiler_emitBytes(compiler, 2, OP, (uint8_t)bytes);                   \
  } else {                                                                     \
    uint8_Pair index = split_uint16(bytes);                                    \
    _LoxCompiler_emitBytes(compiler, 3, OP##_LONG, index.first, index.second); \
  }

static LoxParseRule rules[] = {
    [TOKEN_LEFT_PAREN] = {LoxParser_grouping, NULL, PREC_NONE},
    [TOKEN_RIGHT_PAREN] = {NULL, NULL, PREC_NONE},
    [TOKEN_LEFT_BRACE] = {NULL, NULL, PREC_NONE},
    [TOKEN_RIGHT_BRACE] = {NULL, NULL, PREC_NONE},
    [TOKEN_COMMA] = {NULL, NULL, PREC_NONE},
    [TOKEN_DOT] = {NULL, NULL, PREC_NONE},
    [TOKEN_MINUS] = {LoxParser_unary, LoxParser_binary, PREC_TERM},
    [TOKEN_PLUS] = {NULL, LoxParser_binary, PREC_TERM},
    [TOKEN_SEMICOLON] = {NULL, NULL, PREC_NONE},
    [TOKEN_SLASH] = {NULL, LoxParser_binary, PREC_FACTOR},
    [TOKEN_STAR] = {NULL, LoxParser_binary, PREC_FACTOR},
    [TOKEN_MOD] = {NULL, NULL, PREC_NONE},
    [TOKEN_BANG] = {LoxParser_unary, NULL, PREC_NONE},
    [TOKEN_EQUAL] = {NULL, NULL, PREC_NONE},
    [TOKEN_BANG_EQUAL] = {NULL, LoxParser_binary, PREC_EQUALITY},
    [TOKEN_EQUAL_EQUAL] = {NULL, LoxParser_binary, PREC_EQUALITY},
    [TOKEN_GREATER] = {NULL, LoxParser_binary, PREC_EQUALITY},
    [TOKEN_GREATER_EQUAL] = {NULL, LoxParser_binary, PREC_EQUALITY},
    [TOKEN_LESS] = {NULL, LoxParser_binary, PREC_EQUALITY},
    [TOKEN_LESS_EQUAL] = {NULL, LoxParser_binary, PREC_EQUALITY},
    [TOKEN_IDENTIFIER] = {LoxParser_variable, NULL, PREC_NONE},
    [TOKEN_STRING] = {LoxParser_string, NULL, PREC_NONE},
    [TOKEN_NUMBER] = {LoxParser_number, NULL, PREC_NONE},
    [TOKEN_AND] = {NULL, LoxParser_and, PREC_AND},
    [TOKEN_CLASS] = {NULL, NULL, PREC_NONE},
    [TOKEN_ELSE] = {NULL, NULL, PREC_NONE},
    [TOKEN_FUN] = {NULL, NULL, PREC_NONE},
    [TOKEN_FOR] = {NULL, NULL, PREC_NONE},
    [TOKEN_IF] = {NULL, NULL, PREC_NONE},
    [TOKEN_FALSE] = {LoxParser_literal, NULL, PREC_NONE},
    [TOKEN_TRUE] = {LoxParser_literal, NULL, PREC_NONE},
    [TOKEN_NIL] = {LoxParser_literal, NULL, PREC_NONE},
    [TOKEN_OR] = {NULL, LoxParser_or, PREC_OR},
    [TOKEN_CONST] = {NULL, NULL, PREC_NONE},
    [TOKEN_PRINT] = {NULL, NULL, PREC_NONE},
    [TOKEN_RETURN] = {NULL, NULL, PREC_NONE},
    [TOKEN_SUPER] = {NULL, NULL, PREC_NONE},
    [TOKEN_THIS] = {NULL, NULL, PREC_NONE},
    [TOKEN_VAR] = {NULL, NULL, PREC_NONE},
    [TOKEN_WHILE] = {NULL, NULL, PREC_NONE},
    [TOKEN_STATIC] = {NULL, NULL, PREC_NONE},
    [TOKEN_INCLUDE] = {NULL, NULL, PREC_NONE},
    [TOKEN_ERROR] = {NULL, NULL, PREC_NONE},
    [TOKEN_EOF] = {NULL, NULL, PREC_NONE},
};

void LoxParser_init(LoxParser *self, LoxCompiler *masterCompiler) {
  LoxParser_reset(self);
}
void LoxParser_reset(LoxParser *self) { (*self) = (LoxParser){0}; }
void LoxParser_free(LoxParser *self) { LoxParser_reset(self); }

bool LoxParser_check(LoxParser *self, TokenType type) {
  return self->current.type == type;
}
void LoxParser_advance(LoxParser *self, LoxScanner *scanner) {
  self->previous = self->current;

  while (true) {
    self->current = LoxScanner_scanToken(scanner);

    if (self->current.type != TOKEN_ERROR)
      break;

    errorAtCurrent(self, "Expected expression");
  }
}

void LoxParser_consume(LoxParser *self, LoxScanner *scanner, TokenType type,
                       const char *error_message) {
  if (self->current.type != type) {
    self->hadError = true;
    errorAtCurrent(self, error_message);
  }
  LoxParser_advance(self, scanner);
}

void LoxParser_statement(LoxParser *self, LoxScanner *scanner,
                         LoxCompiler *compiler) {
  if (LoxParser_match(self, scanner, TOKEN_LEFT_BRACE)) {
    LoxCompiler_beginScope(compiler);
    LoxParser_blockStatement(self, scanner, compiler);
    LoxCompiler_endScope(compiler);
  } else if (LoxParser_match(self, scanner, TOKEN_PRINT)) {
    LoxParser_printStatement(self, scanner, compiler);
  } else if (LoxParser_match(self, scanner, TOKEN_FOR)) {
    LoxParser_forStatement(self, scanner, compiler);
  } else if (LoxParser_match(self, scanner, TOKEN_IF)) {
    LoxParser_ifStatement(self, scanner, compiler);
  } else if (LoxParser_match(self, scanner, TOKEN_WHILE)) {
    LoxParser_whileStatement(self, scanner, compiler);
  } else {
    LoxParser_expressionStatement(self, scanner, compiler);
  }
}

void LoxParser_expressionStatement(LoxParser *self, LoxScanner *scanner,
                                   LoxCompiler *compiler) {
  LoxParser_expression(self, compiler);
  LoxParser_consume(self, scanner, TOKEN_SEMICOLON,
                    "Expected ';' at the end of the expression");
  _LoxCompiler_emitByte(compiler, OP_POP);
}

void LoxParser_blockStatement(LoxParser *self, LoxScanner *scanner,
                              LoxCompiler *compiler) {
  while (!LoxParser_check(self, TOKEN_RIGHT_BRACE) &&
         !LoxParser_check(self, TOKEN_EOF)) {
    LoxParser_declaration(self, scanner, compiler);
  }
  LoxParser_consume(self, scanner, TOKEN_RIGHT_BRACE,
                    "Expected '}' after block");
}

void LoxParser_printStatement(LoxParser *self, LoxScanner *scanner,
                              LoxCompiler *compiler) {
  LoxParser_expression(self, compiler);
  LoxParser_consume(self, scanner, TOKEN_SEMICOLON,
                    "Expected ';' at the end of statement");
  _LoxCompiler_emitByte(compiler, OP_PRINT);
}

void LoxParser_whileStatement(LoxParser *self, LoxScanner *scanner,
                              LoxCompiler *compiler) {
  int loopStart = LoxCompiler_currentChunk(compiler)->size;
  // while
  // condition
  LoxParser_expression(self, compiler);

  int exitJump = LoxCompiler_emitJump(compiler, OP_JUMP_IF_FALSE);
  _LoxCompiler_emitByte(compiler, OP_POP);

  // { statements }
  LoxParser_consume(self, scanner, TOKEN_LEFT_BRACE,
                    "Expected '{' before if block");
  LoxParser_blockStatement(self, scanner, compiler);

  LoxCompiler_emitLoop(compiler, loopStart);
  LoxCompiler_patchJump(compiler, exitJump);
  _LoxCompiler_emitByte(compiler, OP_POP);
}

void LoxParser_forStatement(LoxParser *self, LoxScanner *scanner,
                            LoxCompiler *compiler) {
  LoxCompiler_beginScope(compiler);
  bool hadParen = LoxParser_match(self, scanner, TOKEN_LEFT_PAREN);
  // optional var declaration
  if (LoxParser_match(self, scanner, TOKEN_SEMICOLON)) {
    // nothing
  } else if (LoxParser_match(self, scanner, TOKEN_VAR)) {
    LoxParser_varDeclaration(self, scanner, compiler);
  } else {
    LoxParser_expression(self, compiler);
  }
  int loopStartJmp = LoxCompiler_currentChunk(compiler)->size;
  int exitJump = -1;
  // optional condition (default true)
  if (!LoxParser_match(self, scanner, TOKEN_SEMICOLON)) {
    // nothing
    LoxParser_expression(self, compiler);
    LoxParser_consume(self, scanner, TOKEN_SEMICOLON,
                      "Expect ';' after for loop condition");

    exitJump = LoxCompiler_emitJump(compiler, OP_JUMP_IF_FALSE);
    _LoxCompiler_emitByte(compiler, OP_POP); // condition
  }
  // optional increment statement
  if (!(hadParen && LoxParser_match(self, scanner, TOKEN_RIGHT_PAREN)) &&
      !LoxParser_check(self, TOKEN_LEFT_BRACE)) {
    int bodyJump = LoxCompiler_emitJump(compiler, OP_JUMP);
    int incJump = LoxCompiler_currentChunk(compiler)->size;
    // inc
    LoxParser_expression(self, compiler);
    bool closedParen = LoxParser_match(self, scanner, TOKEN_RIGHT_PAREN);
    if (hadParen != closedParen) {
      errorAt(self, &self->previous, "Mismatching parens around for loop");
    }
    LoxCompiler_emitLoop(compiler, loopStartJmp);
    loopStartJmp = incJump;
    // inc end
    LoxCompiler_patchJump(compiler, bodyJump);
  }

  // body
  LoxParser_consume(self, scanner, TOKEN_LEFT_BRACE,
                    "Expect '{' before for loop body");
  LoxParser_blockStatement(self, scanner, compiler);

  LoxCompiler_emitLoop(compiler, loopStartJmp);
  if (exitJump != -1) {
    LoxCompiler_patchJump(compiler, exitJump);
    _LoxCompiler_emitByte(compiler, OP_POP); // condition
  }
  LoxCompiler_endScope(compiler);
}

void LoxParser_ifStatement(LoxParser *self, LoxScanner *scanner,
                           LoxCompiler *compiler) {

  // if
  // statement
  LoxParser_expression(self, compiler);

  int thenJump = LoxCompiler_emitJump(compiler, OP_JUMP_IF_FALSE);
  _LoxCompiler_emitByte(compiler, OP_POP);

  // { then statements }
  LoxParser_consume(self, scanner, TOKEN_LEFT_BRACE,
                    "Expected '{' before if block");
  LoxParser_blockStatement(self, scanner, compiler);

  int elseJump = LoxCompiler_emitJump(compiler, OP_JUMP);
  LoxCompiler_patchJump(compiler, thenJump);
  _LoxCompiler_emitByte(compiler, OP_POP);
  if (LoxParser_match(self, scanner, TOKEN_ELSE)) {
    // { else statement }
    LoxParser_consume(self, scanner, TOKEN_LEFT_BRACE,
                      "Expected '{' before else block");
    LoxParser_blockStatement(self, scanner, compiler);
  }
  LoxCompiler_patchJump(compiler, elseJump);
}

bool LoxParser_match(LoxParser *self, LoxScanner *scanner, TokenType type) {
  if (!LoxParser_check(self, type))
    return false;
  LoxParser_advance(self, scanner);
  return true;
}

void LoxParser_varDeclaration(LoxParser *self, LoxScanner *scanner,
                              LoxCompiler *compiler) {
  uint16_t name = LoxParser_parseVariable(self, scanner, compiler,
                                          "Expected variable name.");
  if (LoxParser_match(self, scanner, TOKEN_EQUAL)) {
    LoxParser_expression(self, compiler);
  } else {
    _LoxCompiler_emitByte(compiler, TOKEN_NIL);
  }
  LoxParser_consume(self, scanner, TOKEN_SEMICOLON,
                    "Expected ';' after variable declaration");

  LoxParser_defineVariable(self, compiler, name);
}

void LoxParser_funDeclaration(LoxParser *self, LoxScanner *scanner,
                              LoxCompiler *compiler) {
  uint8_t name = LoxParser_parseVariable(self, scanner, compiler,
                                         "Expected function name");
  LoxCompiler_markInitialized(compiler);
  LoxCompiler_function(compiler, LOX_TYPE_FUNCTION);
  LoxParser_defineVariable(self, compiler, name);
}

void LoxParser_declareVariable(LoxParser *self, LoxScanner *scanner,
                               LoxCompiler *compiler) {
  if (compiler->scopeDepth == 0)
    return;

  LoxToken *name = &self->previous;
  for (int i = compiler->localCount - 1; i >= 0; i--) {
    LoxLocal *local = &compiler->locals[i];
    if (local->depth != -1 && local->depth < compiler->scopeDepth) {
      break;
    }
    if (LoxToken_identifierEquals(name, &local->name)) {
      errorAt(self, &self->previous, "Already defined in this scope");
    }
  }
  LoxCompiler_addLocal(compiler, *name);
}
void LoxParser_defineVariable(LoxParser *self, LoxCompiler *compiler,
                              uint16_t name) {
  if (compiler->scopeDepth > 0) {
    LoxCompiler_markInitialized(compiler);
    return;
  }
  EMIT_LONG_FORK(compiler, OP_DEFINE_GLOBAL, name);
}

void LoxParser_namedVariable(LoxParser *self, LoxCompiler *compiler,
                             LoxToken name, bool canAssign) {
  LoxValue variableName = LoxToken_toString(self->previous);

  enum { LOCAL, GLOBAL } setOp, getOp;
  int arg = LoxCompiler_resolveLocal(compiler, &name);
  if (arg != -1) {
    getOp = LOCAL;
    setOp = LOCAL;
  } else {
    arg = LoxCompiler_makeConstant(compiler, variableName);
    getOp = GLOBAL;
    setOp = GLOBAL;
  }
  if (canAssign && LoxParser_match(self, compiler->scanner, TOKEN_EQUAL)) {
    LoxParser_expression(self, compiler);
    if (setOp == LOCAL) {
      _LoxCompiler_emitBytes(compiler, 2, OP_SET_LOCAL, (uint8_t)arg);
    } else {
      EMIT_LONG_FORK(compiler, OP_SET_GLOBAL, arg);
    }
  } else {
    if (getOp == LOCAL) {
      _LoxCompiler_emitBytes(compiler, 2, OP_GET_LOCAL, (uint8_t)arg);
    } else {
      EMIT_LONG_FORK(compiler, OP_GET_GLOBAL, arg);
    }
  }
}

uint16_t LoxParser_parseVariable(LoxParser *self, LoxScanner *scanner,
                                 LoxCompiler *compiler,
                                 const char *errorMessage) {
  LoxParser_consume(self, scanner, TOKEN_IDENTIFIER, errorMessage);
  LoxParser_declareVariable(self, scanner, compiler);
  if (compiler->scopeDepth > 0)
    return 0;
  LoxValue variableName = LoxToken_toString(self->previous);
  uint16_t variableNameIndex = LoxCompiler_makeConstant(compiler, variableName);
  return variableNameIndex;
}

void LoxParser_declaration(LoxParser *self, LoxScanner *scanner,
                           LoxCompiler *compiler) {
  if (LoxParser_match(self, scanner, TOKEN_VAR)) {
    LoxParser_varDeclaration(self, scanner, compiler);
  } else if (LoxParser_match(self, scanner, TOKEN_FUN)) {
    LoxParser_funDeclaration(self, scanner, compiler);
  } else {
    LoxParser_statement(self, scanner, compiler);
  }
  if (self->panicMode)
    LoxParser_syncronize(self, scanner);
}

void LoxParser_syncronize(LoxParser *self, LoxScanner *scanner) {
  self->panicMode = false;
  while (self->current.type != TOKEN_EOF) {
#define PASS
    switch (self->current.type) {
    case TOKEN_CLASS:
    case TOKEN_FUN:
    case TOKEN_VAR:
    case TOKEN_IF:
    case TOKEN_FOR:
    case TOKEN_WHILE:
    case TOKEN_PRINT:
    case TOKEN_RETURN:
      return;
    default:
      PASS;
    }
    LoxParser_advance(self, scanner);
  }
}

void LoxParser_expression(LoxParser *self, LoxCompiler *compiler) {
  LoxParser_parsePrecedence(self, compiler, PREC_ASSIGNMENT);
}

void LoxParser_string(LoxParser *self, LoxCompiler *compiler, bool canAssign) {
  _LoxCompiler_emitConstant(
      compiler,
      LOX_OBJECT_VAL( // for " at start      and for " at the end
          copyString(&vm, self->previous.start + 1, self->previous.size - 2)));
}

void LoxParser_number(LoxParser *self, LoxCompiler *compiler, bool canAssign) {
  double value = strtod(self->previous.start, NULL);
  _LoxCompiler_emitConstant(compiler, LOX_NUMBER_VAL(value));
}

void LoxParser_grouping(LoxParser *self, LoxCompiler *compiler,
                        bool canAssign) {
  LoxParser_expression(self, compiler);
  LoxParser_consume(self, compiler->scanner, TOKEN_RIGHT_PAREN,
                    "Expect ')' after expression");
}
void LoxParser_unary(LoxParser *self, LoxCompiler *compiler, bool canAssign) {
  TokenType operator= self->previous.type;

  LoxParseRule *rule = LoxParser_getRule(operator);
  LoxParser_parsePrecedence(self, compiler,
                            (LoxPrecedence)(rule->precedence + 1));

  switch (operator) {
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

LoxParseRule *LoxParser_getRule(TokenType type) { return &rules[type]; }

void LoxParser_or(LoxParser *self, LoxCompiler *compiler, bool canAssign) {
  int elseJump = LoxCompiler_emitJump(compiler, OP_JUMP_IF_FALSE);
  int endJump = LoxCompiler_emitJump(compiler, OP_JUMP);

  LoxCompiler_patchJump(compiler, elseJump);
  _LoxCompiler_emitByte(compiler, OP_POP);

  LoxParser_parsePrecedence(self, compiler, PREC_AND);
  LoxCompiler_patchJump(compiler, endJump);
}

void LoxParser_and(LoxParser *self, LoxCompiler *compiler, bool canAssign) {
  int shortPath = LoxCompiler_emitJump(compiler, OP_JUMP_IF_FALSE);

  _LoxCompiler_emitByte(compiler, OP_POP);
  LoxParser_parsePrecedence(self, compiler, PREC_AND);

  LoxCompiler_patchJump(compiler, shortPath);
}

void LoxParser_variable(LoxParser *self, LoxCompiler *compiler,
                        bool canAssign) {
  LoxParser_namedVariable(self, compiler, self->previous, canAssign);
}

void LoxParser_binary(LoxParser *self, LoxCompiler *compiler, bool canAssign) {
  TokenType operator= self->previous.type;
  LoxParseRule *rule = LoxParser_getRule(operator);
  LoxParser_parsePrecedence(self, compiler,
                            (LoxPrecedence)(rule->precedence + 1));

  switch (operator) {
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
    _LoxCompiler_emitBytes(compiler, 2, OP_EQUALS, OP_NOT);
    break;
  case TOKEN_EQUAL_EQUAL:
    _LoxCompiler_emitByte(compiler, OP_EQUALS);
    break;
  case TOKEN_GREATER:
    _LoxCompiler_emitByte(compiler, OP_GREATER);
    break;
  case TOKEN_GREATER_EQUAL:
    _LoxCompiler_emitBytes(compiler, 2, OP_LESS, OP_NOT);
    break;
  case TOKEN_LESS:
    _LoxCompiler_emitByte(compiler, OP_LESS);
    break;
  case TOKEN_LESS_EQUAL:
    _LoxCompiler_emitBytes(compiler, 2, OP_GREATER, OP_NOT);
    break;
  }
}

void LoxParser_literal(LoxParser *self, LoxCompiler *compiler, bool canAssign) {
  switch (self->previous.type) {
  case TOKEN_TRUE:
    _LoxCompiler_emitByte(compiler, OP_TRUE);
    break;
  case TOKEN_FALSE:
    _LoxCompiler_emitByte(compiler, OP_FALSE);
    break;
  case TOKEN_NIL:
    _LoxCompiler_emitByte(compiler, OP_NIL);
    break;
  default:
    return;
  }
}

void LoxParser_parsePrecedence(LoxParser *self, LoxCompiler *compiler,
                               LoxPrecedence precedence) {
  LoxParser_advance(self, compiler->scanner);
  ParseFn prefixRule = LoxParser_getRule(self->previous.type)->prefix;
  if (prefixRule == NULL) {
    errorAtCurrent(self, "Expected expression");
    return;
  }
  bool canAssign = precedence <= PREC_ASSIGNMENT;
  prefixRule(self, compiler, canAssign);

  while (precedence <= LoxParser_getRule(self->current.type)->precedence) {
    LoxParser_advance(self, compiler->scanner);
    ParseFn infixRule = LoxParser_getRule(self->previous.type)->infix;
    if (infixRule != NULL)
      infixRule(self, compiler, canAssign);
  }
}
