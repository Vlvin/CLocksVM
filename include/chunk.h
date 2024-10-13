#ifndef CHUNK_H
#define CHUNK_H

#include <oneFileSTD.h>
#include <loxMemory.h>
#include <value.h>

typedef enum {
    OP_CONSTANT,
    OP_RETURN
} OpCode;

typedef struct {
    size_t capacity, size;
    uint8_t *code;
    int* lines;
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
size_t Chunk_addConstant(Chunk* self, Value value);
Value Chunk_getConstant(Chunk* self, size_t index);

const size_t Chunk_size(Chunk* self);
const size_t Chunk_capacity(Chunk* self);
uint8_t * const Chunk_data(Chunk* self);

#endif