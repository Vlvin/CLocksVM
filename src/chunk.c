#include <chunk.h>
#include <oneFileSTD.h>

int Chunk_free(Chunk* chunk) {
    chunk->size = chunk->capacity = 0;
    if (chunk->code == NULL)
        return 1;
    free(chunk->code);
    chunk->code = NULL;
    return 0;
}

Chunk Chunk_init() {
    size_t default_size = 8;
    Chunk ret = {
        0, default_size, malloc(default_size)
    };
    return ret;
}

int Chunk_add(Chunk* chunk, OpCode code) {
    if (chunk->code == NULL) {
        (*chunk) = Chunk_init();
    }
    if (chunk->size == chunk->capacity) {
        chunk->code = realloc(chunk->code, chunk->capacity*2);
        chunk->capacity *= 2;
        if (chunk->code == NULL)
            return 1;
    }
    chunk->code[chunk->size] = code;
    chunk->size++;
    return 0;
}

int Chunk_pop(Chunk* chunk) {
    if (!chunk->capacity) return 1;
    chunk->size--;
    return 0;
}