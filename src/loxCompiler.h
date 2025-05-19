#ifndef LOX_COMPILER_H
#define LOX_COMPILER_H

#include "loxToken.h"
#include <loxChunk.h>
#include <loxParser.h>
#include <loxScanner.h>
#include <oneFileSTD.h>
#include <stdint.h>

#define UINT8_COUNT (UINT8_MAX + 1)

typedef struct LoxFunction LoxFunction;

typedef enum LoxScopeType {
  LOX_TYPE_FUNCTION,
  LOX_TYPE_TOP_LEVEL,
} LoxScopeType;

typedef struct LoxLocal {
  LoxToken name;
  int depth;
} LoxLocal;

typedef struct LoxCompiler LoxCompiler;

typedef struct LoxCompiler {
  LoxCompiler *parent;
  LoxScanner *scanner;
  LoxParser *parser;
  LoxFunction *function;
  LoxLocal locals[UINT8_COUNT];
  int localCount;
  int scopeDepth;
} LoxCompiler;

void LoxCompiler_init(LoxCompiler *self, LoxCompiler *parent,
                      LoxScopeType scope);
LoxFunction *LoxCompiler_compile(LoxCompiler *self, const char *source);
Chunk *LoxCompiler_currentChunk(LoxCompiler *self);
LoxFunction *LoxCompiler_end(LoxCompiler *self);
void LoxCompiler_free(LoxCompiler *self);
uint16_t LoxCompiler_makeConstant(LoxCompiler *self, LoxValue value);
void LoxCompiler_beginScope(LoxCompiler *self);
void LoxCompiler_endScope(LoxCompiler *self);
void LoxCompiler_addLocal(LoxCompiler *self, LoxToken name);
void LoxCompiler_markInitialized(LoxCompiler *self);
void LoxCompiler_function(LoxCompiler *self, LoxScopeType scope_type);
int LoxCompiler_resolveLocal(LoxCompiler *self, LoxToken *name);
// private:
void _LoxCompiler_emitByte(LoxCompiler *self, uint8_t instruction);
int LoxCompiler_emitJump(LoxCompiler *self, uint8_t instruction);
void LoxCompiler_emitLoop(LoxCompiler *self, int loopStart);
void _LoxCompiler_emitBytes(LoxCompiler *self, int count, ...);
void _LoxCompiler_emitReturn(LoxCompiler *self);
uint16_t _LoxCompiler_emitConstant(LoxCompiler *self, LoxValue value);
void LoxCompiler_patchJump(LoxCompiler *self, int offset);

#endif
