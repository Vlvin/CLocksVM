#include "loxErrors.h"
#include "loxObject.h"
#include "loxParser.h"
#include "loxScanner.h"
#include <bitsTricks.h>
#include <loxCompiler.h>
#include <loxToken.h>
#include <stdint.h>

#ifdef DEBUG_PRINT_CODE
#include <debug.h>
#endif

void LoxCompiler_init(LoxCompiler *self, LoxCompiler *parent,
                      LoxScopeType scope_type) {
  if (parent != NULL) {
    self->parser = parent->parser;
    self->scanner = parent->scanner;
  }
  self->localCount = 0;
  self->scopeDepth = 0;
  self->function = NULL;

  self->parent = parent;
  self->function = LoxFunction_new(scope_type);

  if (scope_type == LOX_TYPE_TOP_LEVEL) {
    // pass script file name
    // assign it to function name
    // or else
    if (parent != NULL) { // import script; -> function->name == "script";
      self->function->name = copyString(&vm, parent->parser->previous.start,
                                        parent->parser->previous.size);
    } else { // main script
      self->function->name = copyString(&vm, "__main__", 8);
    }
  } else {
    assert(parent != NULL);
    self->function->name = copyString(&vm, parent->parser->previous.start,
                                      parent->parser->previous.size);
  }

  LoxLocal *local = &self->locals[self->localCount++];
  local->depth = 0;
  local->name.start = "";
  local->name.size = 0;
}

LoxFunction *LoxCompiler_compile(LoxCompiler *self, const char *source) {
  LoxScanner scanner;
  LoxParser parser;
  self->scanner = &scanner;
  self->parser = &parser;

  LoxScanner_init(self->scanner, source);
  LoxParser_init(self->parser, self);

  LoxParser_advance(self->parser, self->scanner);
  while (!LoxParser_match(self->parser, self->scanner, TOKEN_EOF))
    LoxParser_declaration(self->parser, self->scanner, self);
  /*LoxParser_expression(self->parser);*/
  /*LoxParser_consume(self->parser, self->scanner, TOKEN_SEMICOLON, "Expect
   * end of expression");*/
  LoxFunction *function = LoxCompiler_end(self);
  LoxScanner_free(self->scanner);
  return self->parser->hadError ? NULL : function;
}

Chunk *LoxCompiler_currentChunk(LoxCompiler *self) {
  return &self->function->chunk;
}

LoxFunction *LoxCompiler_end(LoxCompiler *self) {
  _LoxCompiler_emitReturn(self);
  LoxFunction *function = self->function;

#ifdef DEBUG_PRINT_CODE
  if (!self->parser->hadError)
    disassembleChunk(&self->function->chunk, function->name != NULL
                                                 ? function->name->bytes
                                                 : "<script>");
#endif
  return function;
}

void LoxCompiler_free(LoxCompiler *self) {
  LoxParser_free(self->parser);
  // LoxObject_free((LoxObject *)self->function);
  (*self) = (LoxCompiler){0};
}

void LoxCompiler_addLocal(LoxCompiler *self, LoxToken name) {
  if (self->localCount == UINT8_COUNT) {
    errorAt(self->parser, &self->parser->previous,
            "Too many locals in function");
    return;
  }
  LoxLocal *local = &self->locals[self->localCount++];
  local->name = name;
  local->depth = -1;
}

void LoxCompiler_function(LoxCompiler *self, LoxScopeType scope_type) {
  LoxCompiler compiler;
  LoxCompiler_init(&compiler, self, scope_type);
  LoxCompiler_beginScope(self);
  // name(arg1, arg2) { body }
  //     ^
  LoxParser_consume(compiler.parser, compiler.scanner, TOKEN_LEFT_PAREN,
                    "Expected '(' after function name");
  if (!LoxParser_check(compiler.parser, TOKEN_RIGHT_PAREN)) {

    // name(arg1, arg2) { body }
    //      ^^^
    do {
      compiler.function->arity++;
      if (compiler.function->arity > 255) {
        errorAtCurrent(
            compiler.parser,
            "Too many arguments in function declaration. 255 is top limit");
      }
      uint16_t argument =
          LoxParser_parseVariable(compiler.parser, compiler.scanner, &compiler,
                                  "Expected parameter name");
      LoxParser_defineVariable(compiler.parser, &compiler, argument);

      // name(arg1, arg2) { body }
      //          ^
    } while (LoxParser_match(compiler.parser, compiler.scanner, TOKEN_COMMA));
  }

  // name(arg1, arg2) { body }
  //                ^
  LoxParser_consume(compiler.parser, compiler.scanner, TOKEN_RIGHT_PAREN,
                    "Expected ')' after function params");
  // name(arg1, arg2) { body }
  //                  ^
  LoxParser_consume(compiler.parser, compiler.scanner, TOKEN_LEFT_BRACE,
                    "Expected '{' before function name");
  // name(arg1, arg2) { body }
  //                    ^^^^
  LoxParser_blockStatement(compiler.parser, compiler.scanner,
                           &compiler); // already comsumes '}'
  // name(arg1, arg2) { body } EOL
  //                           ^^^
  LoxFunction *function = LoxCompiler_end(&compiler);
  _LoxCompiler_emitBytes(
      self, 2, OP_CONSTANT,
      LoxCompiler_makeConstant(self, LOX_OBJECT_VAL(function)));
  LoxCompiler_endScope(self);
}

void LoxCompiler_markInitialized(LoxCompiler *self) {
  if (self->scopeDepth == 0)
    return;
  self->locals[self->localCount - 1].depth = self->scopeDepth;
}

int LoxCompiler_resolveLocal(LoxCompiler *self, LoxToken *name) {
  bool met_uninitialized_self = false;
  for (int i = self->localCount - 1; i >= 0; i--) {
    LoxLocal *local = &self->locals[i];
    if (LoxToken_identifierEquals(name, &local->name)) {
      if (local->depth == -1) {
        met_uninitialized_self = true;
        continue;
      }
      return i;
    }
  }
  if (met_uninitialized_self)
    errorAt(self->parser, &self->parser->previous,
            "Can't read variable in it's own initializer");
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
  return Chunk_addConstant(&self->function->chunk, value);
}

void LoxCompiler_patchJump(LoxCompiler *self, int offset) {
  int jump = LoxCompiler_currentChunk(self)->size - offset - 2;
  if (jump > UINT16_MAX) {
    errorAt(self->parser, &self->parser->previous, "Too much to jump");
  }
  uint8_Pair jumpPair = split_uint16(jump);
  *(&LoxCompiler_currentChunk(self)->code[offset]) = jumpPair.first;
  *(&LoxCompiler_currentChunk(self)->code[offset + 1]) = jumpPair.second;
}

void _LoxCompiler_emitByte(LoxCompiler *self, uint8_t byte) {
  Chunk_add(LoxCompiler_currentChunk(self), byte, self->parser->previous.line);
}

void LoxCompiler_emitLoop(LoxCompiler *self, int loopStart) {

  _LoxCompiler_emitByte(self, OP_LOOP);
  int offset = LoxCompiler_currentChunk(self)->size - loopStart + 2;
  if (offset > UINT16_MAX) {
    errorAt(self->parser, &self->parser->previous, "Too big loop size");
  }
  uint8_Pair index = split_uint16(offset);
  _LoxCompiler_emitBytes(self, 2, index.first, index.second);
}

int LoxCompiler_emitJump(LoxCompiler *self, uint8_t instruction) {
  _LoxCompiler_emitBytes(self, 3, instruction, 0xff, 0xff);
  return LoxCompiler_currentChunk(self)->size - 2;
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
  // size_t line = self->parser.previous.line;
  if (constLocation > 255) {
    uint8_Pair operands = split_uint16(constLocation);
    _LoxCompiler_emitBytes(self, 3, OP_CONSTANT_LONG, operands.first,
                           operands.second);
  } else {
    _LoxCompiler_emitBytes(self, 2, OP_CONSTANT, (uint8_t)constLocation);
  }
  return constLocation;
}
