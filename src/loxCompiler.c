#include "loxErrors.h"
#include "loxParser.h"
#include "loxScanner.h"
#include <bitsTricks.h>
#include <loxCompiler.h>
#include <loxToken.h>
#include <stdint.h>

#ifdef DEBUG_PRINT_CODE
#include <debug.h>
#endif

void LoxCompiler_init(LoxCompiler *self) {
  LoxParser_init(&self->parser, self);
  self->localCount = 0;
  self->scopeDepth = 0;
}

bool LoxCompiler_compile(LoxCompiler *self, const char *source, Chunk *chunk) {
  LoxScanner_init(&self->scanner, source);
  self->compilingChunk = chunk;

  LoxParser_advance(&self->parser, &self->scanner);
  while (!LoxParser_match(&self->parser, &self->scanner, TOKEN_EOF))
    LoxParser_declaration(&self->parser, &self->scanner);
  /*LoxParser_expression(&self->parser);*/
  /*LoxParser_consume(&self->parser, &self->scanner, TOKEN_SEMICOLON, "Expect
   * end of expression");*/
  LoxCompiler_end(self);
  LoxScanner_free(&self->scanner);
  return !self->parser.hadError;
}

Chunk *LoxCompiler_currentChunk(LoxCompiler *self) {
  return self->compilingChunk;
}

void LoxCompiler_end(LoxCompiler *self) {
  _LoxCompiler_emitReturn(self);
#ifdef DEBUG_PRINT_CODE
  if (!self->parser.hadError)
    disassembleChunk(self->compilingChunk, "code");
#endif
}

void LoxCompiler_free(LoxCompiler *self) {
  LoxParser_free(&self->parser);
  (*self) = (LoxCompiler){0};
}

void LoxCompiler_addLocal(LoxCompiler *self, LoxToken name) {
  if (self->localCount == UINT8_COUNT) {
    errorAt(&self->parser, &self->parser.previous,
            "Too many locals in function");
    return;
  }
  LoxLocal *local = &self->locals[self->localCount++];
  local->name = name;
  local->depth = self->scopeDepth;
}

int LoxCompiler_resolveLocal(LoxCompiler *self, LoxToken *name) {
  for (int i = self->localCount - 1; i >= 0; i--) {
    LoxLocal *local = &self->locals[i];
    if (LoxToken_identifierEquals(name, &local->name))
      return i;
  }
  return -1;
}
void LoxCompiler_beginScope(LoxCompiler *self) { self->scopeDepth++; }

void LoxCompiler_endScope(LoxCompiler *self) {
  self->scopeDepth--;
  while (self->localCount >= 0 &&
         self->locals[self->localCount - 1].depth > self->scopeDepth) {
    _LoxCompiler_emitByte(self, OP_POP);
    self->localCount--;
  }
}

uint16_t LoxCompiler_makeConstant(LoxCompiler *self, LoxValue value) {
  return Chunk_addConstant(self->compilingChunk, value);
}

void _LoxCompiler_emitByte(LoxCompiler *self, uint8_t byte) {
  Chunk_add(LoxCompiler_currentChunk(self), byte, self->parser.previous.line);
}

void _LoxCompiler_emitBytes(LoxCompiler *self, int count, ...) {
  va_list args;
  va_start(args, count);
  while (count-- > 0)
    _LoxCompiler_emitByte(self, va_arg(args, int));
  va_end(args);
}

void _LoxCompiler_emitReturn(LoxCompiler *self) {
  _LoxCompiler_emitByte(self, OP_RETURN);
}

uint16_t _LoxCompiler_emitConstant(LoxCompiler *self, LoxValue value) {
  uint16_t constLocation = LoxCompiler_makeConstant(self, value);
  size_t line = self->parser.previous.line;
  if (constLocation > 255) {
    uint8_Pair operands = split_uint16(constLocation);
    _LoxCompiler_emitBytes(self, 3, OP_CONSTANT_LONG, operands.first,
                           operands.second);
  } else {
    _LoxCompiler_emitBytes(self, 2, OP_CONSTANT, (uint8_t)constLocation);
  }
  return constLocation;
}
