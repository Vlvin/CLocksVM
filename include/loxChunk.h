#ifndef LOX_CHUNK_H
#define LOX_CHUNK_H

#include <oneFileSTD.h>
#include <loxMemory.h>
#include <loxValue.h>
#include <lineTracker.h>

typedef enum {
    // STACK VARIABLES
    OP_CONSTANT_LONG,
    OP_CONSTANT,
    // UNARY
    OP_NEGATE,
    OP_NOT,
    // BINARY
    OP_ADD,
    OP_SUBSTRACT,
    OP_DIVIDE,
    OP_MULTIPLY,
    OP_AND,
    OP_OR,
    // SIMPLE
    OP_RETURN
} OpCode;

typedef struct Chunk {
    size_t capacity, size;
    uint8_t *code;
    LineTracker tracker;
    ValueArray constants;
} Chunk;

Chunk Chunk_init();

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
size_t Chunk_addConstant(Chunk* self, Value value, int line);
Value Chunk_getConstant(Chunk* self, size_t index);

const size_t Chunk_size(Chunk* self);
const size_t Chunk_capacity(Chunk* self);
uint8_t * const Chunk_data(Chunk* self);

#endif