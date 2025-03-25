#ifndef LOX_COMPILER_H
#define LOX_COMPILER_H

#include "loxToken.h"
#include <loxChunk.h>
#include <loxParser.h>
#include <loxScanner.h>
#include <oneFileSTD.h>
#include <stdint.h>

#define UINT8_COUNT (UINT8_MAX + 1)

typedef struct LoxLocal {
  LoxToken name;
  int depth;
} LoxLocal;

typedef struct LoxCompiler {
  LoxScanner scanner;
  LoxParser parser;
  Chunk *compilingChunk;
  LoxLocal locals[UINT8_COUNT];
  int localCount;
  int scopeDepth;
} LoxCompiler;

void LoxCompiler_init(LoxCompiler *self);
bool LoxCompiler_compile(LoxCompiler *self, const char *source, Chunk *chunk);
Chunk *LoxCompiler_currentChunk(LoxCompiler *self);
void LoxCompiler_end(LoxCompiler *self);
void LoxCompiler_free(LoxCompiler *self);
uint16_t LoxCompiler_makeConstant(LoxCompiler *self, LoxValue value);
void LoxCompiler_beginScope(LoxCompiler *self);
void LoxCompiler_endScope(LoxCompiler *self);
void LoxCompiler_addLocal(LoxCompiler *self, LoxToken name);
void LoxCompiler_markInitialized(LoxCompiler *self);
int LoxCompiler_resolveLocal(LoxCompiler *self, LoxToken *name);
// private:
void _LoxCompiler_emitByte(LoxCompiler *self, uint8_t byte);
void _LoxCompiler_emitBytes(LoxCompiler *self, int count, ...);
void _LoxCompiler_emitReturn(LoxCompiler *self);
uint16_t _LoxCompiler_emitConstant(LoxCompiler *self, LoxValue value);

#endif
