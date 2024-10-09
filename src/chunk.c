#include <chunk.h>
#include <oneFileSTD.h>

int Chunk_free(Chunk* chunk) {
    // LIST_FREE(chunk); // for dynamicArray.h template impl
    chunk->size = chunk->capacity = 0;
    if (NULL == Chunk_data(chunk))
        return 1;
    free(chunk->data);
    chunk->data = NULL;
    return 0;
}

Chunk Chunk_init() {
    // return (Chunk)LIST_INIT(uint8_t); // for dynamicArray.h template impl
    const size_t default_size = 8;
    Chunk ret = {
        0, default_size, malloc(default_size)
    };
    return ret;
    
}

int Chunk_add(Chunk* chunk, OpCode code) {
    // LIST_PUSH(uint8_t, code, chunk); // for dynamicArray.h template impl
    if (NULL == Chunk_data(chunk)) {
        (*chunk) = Chunk_init();
    }
    if (Chunk_size(chunk) == Chunk_capacity(chunk)) {
        chunk->data = realloc(chunk->data, Chunk_capacity(chunk)*2);
        chunk->capacity *= 2;
        if (NULL == Chunk_data(chunk))
            return 1;
    }
    Chunk_data(chunk)[chunk->size] = code;
    chunk->size++;
    return 0;
}

int Chunk_pop(Chunk* chunk) {
    // LIST_POP(uint8_t, chunk); // for dynamicArray.h template impl
    if (!Chunk_capacity(chunk)) 
        return 1;
    chunk->size--;
    return 0;
}


const size_t Chunk_size(Chunk* chunk) {
    return chunk->size;
}
const size_t Chunk_capacity(Chunk* chunk) {
    return chunk->capacity;
}
uint8_t *const Chunk_data(Chunk* chunk) {
    return chunk->data;
}