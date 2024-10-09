#ifndef CHUNK_H
#define CHUNK_H

#include <oneFileSTD.h>
#include <dynamicArray.h>

typedef enum {
    RETURN
} OpCode;

typedef LIST(uint8_t) Chunk;

Chunk Chunk_init();
int Chunk_free(Chunk* chunk);

int Chunk_add(Chunk* chunk, OpCode code);
int Chunk_pop(Chunk* chunk);

const size_t Chunk_size(Chunk* chunk);
const size_t Chunk_capacity(Chunk* chunk);
uint8_t * const Chunk_data(Chunk* chunk);

#endif