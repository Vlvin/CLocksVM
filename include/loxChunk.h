#ifndef LOX_CHUNK_H
#define LOX_CHUNK_H

#include <oneFileSTD.h>
#include <loxMemory.h>
#include <loxValueArray.h>
#include <loxLineTracker.h>

typedef enum {
    // STACK VALUES
    OP_CONSTANT_LONG,
    OP_CONSTANT,
    // UNARY OPERATIONS
    OP_NEGATE, // MATH
    OP_NOT, // LOGICAL
    // BINARY MATH OPERATIONS
    OP_ADD,
    OP_SUBSTRACT,
    OP_DIVIDE,
    OP_MULTIPLY,
    // BINARY LOGICAL COMPARISON
    OP_AND,
    OP_OR,
    // BINARY MATH COMPARISON
    OP_LESS,
    OP_EQUALS,
    OP_GREATER,
    // SIMPLE
    OP_TRUE,
    OP_FALSE,
    OP_NIL,
    OP_RETURN,
    // STATEMENTS
    OP_PRINT,
} OpCode;

typedef struct Chunk {
    size_t capacity, size;
    uint8_t *code;
    LoxLineTracker tracker;
    ValueArray constants;
} Chunk;

void Chunk_init(Chunk *self);

/// @brief 
/// @param self allocated chunk
/// @return new size which is 0 on success
int Chunk_free(Chunk* self);
/// @brief 
/// @param self allocated chunk
/// @param code OpCode to add to chunk
/// @return new size
int Chunk_add(Chunk* self, OpCode code, int line);
/// @brief 
/// @param self allocated chunk
/// @param value constant to add to chunk pool
/// @return index of new constant
size_t Chunk_addConstant(Chunk* self, LoxValue value);
LoxValue Chunk_getConstant(Chunk* self, size_t index);

const size_t Chunk_size(Chunk* self);
const size_t Chunk_capacity(Chunk* self);
uint8_t * const Chunk_data(Chunk* self);

#endif
