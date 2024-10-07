#ifndef CHUNK_H
#define CHUNK_H

#include <oneFileSTD.h>

typedef enum {
    ADD,
    SUBSTRACT,
    MULTIPLY,
    DIVIDE,
    LOOKUP_VARIABLE,
    ASSIGN,
    RETURN
} OpCode;

typedef struct {
    size_t size;
    size_t capacity;
    uint8_t *code;
} Chunk;

Chunk Chunk_init();
int Chunk_free(Chunk* chunk);

int Chunk_add(Chunk* chunk, OpCode code);
int Chunk_pop(Chunk* chunk);

#endif