#ifndef LOX_COMPILER_H
#define LOX_COMPILER_H

#include <loxChunk.h>
#include <loxParser.h>
#include <loxScanner.h>
#include <oneFileSTD.h>

typedef struct LoxCompiler {
  LoxScanner scanner;
  LoxParser parser;
  Chunk *compilingChunk;
} LoxCompiler;


inline static LoxCompiler LoxCompiler_init();
inline static bool LoxCompiler_compile(LoxCompiler* self, const char* source, Chunk* chunk);
inline static Chunk* currentToken(LoxCompiler* self);
inline static void LoxCompiler_end(LoxCompiler* self);
inline static void LoxCompiler_free(LoxCompiler* self);
inline static void LoxCompiler_number(LoxCompiler* self);
inline static void LoxCompiler_grouping(LoxCompiler* self);
inline static void LoxCompiler_unary(LoxCompiler* self);
inline static void LoxCompiler_binary(LoxCompiler* self);
inline static size_t LoxCompiler_makeConstant(LoxCompiler* self, Value value);
// private:
inline static void _LoxCompiler_emitByte(LoxCompiler* self, uint8_t byte);
inline static void _LoxCompiler_emitBytes(LoxCompiler* self, int count, ...);
inline static void _LoxCompiler_emitReturn(LoxCompiler* self);
inline static void _LoxCompiler_emitConstant(LoxCompiler* self, Value value);
inline static void _LoxCompiler_parsePrecedence(LoxCompiler* self, LoxPrecedence precedance);

#endif