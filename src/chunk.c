#include <chunk.h>
#include <oneFileSTD.h>

Chunk Chunk_init() {
    Chunk ret = {
        0, 
        0, 
        NULL,
        NULL,
        ValueArray_init()
    };
    return ret;
}

int Chunk_add(Chunk* self, OpCode opcode, int line) {
    if (self->size == self->capacity) {
        GROW_ARRAY(uint8_t, self->code, self->capacity);
        GROW_ARRAY(int, self->lines, self->capacity);
        self->capacity = GROW_CAPACITY(self->capacity);
        if (NULL == self->code)
            exit(1);
    }
    self->code[self->size] = opcode;
    self->lines[self->size] = line;
    self->size++;
    return 0;
}

int Chunk_free(Chunk* self) {
    FREE_ARRAY(uint8_t, self->code, self->capacity);
    FREE_ARRAY(int, self->lines, self->capacity);
    (*self) = Chunk_init();
    ValueArray_free(&(self->constants));
    return 0;
}

size_t Chunk_addConstant(Chunk* self, Value value) {
    size_t constLocation = ValueArray_add(&(self->constants), value);
    return constLocation;
}

Value Chunk_getConstant(Chunk* self, size_t index) {
    return ValueArray_data(&(self->constants))[index];
}

const size_t Chunk_size(Chunk* self) {
    return self->size;
}
const size_t Chunk_capacity(Chunk* self) {
    return self->capacity;
}
uint8_t *const Chunk_data(Chunk* self) {
    return self->code;
}