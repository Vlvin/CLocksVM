#ifndef LOX_COMPILER_H
#define LOX_COMPILER_H

#include <loxScanner.h>
#include <loxParser.h>
#include <loxChunk.h>
#include <oneFileSTD.h>



typedef struct LoxCompiler {
  LoxScanner scanner;
  LoxParser parser;
  Chunk *compilingChunk;
} LoxCompiler;


void LoxCompiler_init(LoxCompiler* self);
bool LoxCompiler_compile(LoxCompiler* self, const char* source, Chunk* chunk);
Chunk* LoxCompiler_currentChunk(LoxCompiler* self);
void LoxCompiler_end(LoxCompiler* self);
void LoxCompiler_free(LoxCompiler* self);
size_t LoxCompiler_makeConstant(LoxCompiler* self, LoxValue value);
// private:
void _LoxCompiler_emitByte(LoxCompiler* self, uint8_t byte);
void _LoxCompiler_emitBytes(LoxCompiler* self, int count, ...);
void _LoxCompiler_emitReturn(LoxCompiler* self);
void _LoxCompiler_emitConstant(LoxCompiler* self, LoxValue value);

#endif