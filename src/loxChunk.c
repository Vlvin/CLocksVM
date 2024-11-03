#include <loxChunk.h>
#include <oneFileSTD.h>
#include <bitsTricks.h>

Chunk Chunk_init() {
    Chunk ret = {
        0, 
        0, 
        NULL,
        LineTracker_init(),
        ValueArray_init()
    };
    return ret;
}

int Chunk_add(Chunk* self, OpCode opcode, int line) {
    if (self->size == self->capacity) {
        GROW_ARRAY(uint8_t, self->code, self->capacity);
        self->capacity = GROW_CAPACITY(self->capacity);
        if (NULL == self->code)
            exit(1);
    }
    self->code[self->size] = opcode;
    LineTracker_write(&(self->tracker), line);
    self->size++;
    return 0;
}

int Chunk_free(Chunk* self) {
    FREE_ARRAY(uint8_t, self->code, self->capacity);
    (*self) = Chunk_init();
    ValueArray_free(&(self->constants));
    LineTracker_free(&(self->tracker));
    return 0;
}

size_t Chunk_addConstant(Chunk* self, Value value, int line) {
    size_t constLocation = ValueArray_add(&(self->constants), value);
    if (constLocation > 255) {
        Chunk_add(self, OP_CONSTANT_LONG, line);
        uint8_Pair operands = split_uint16(constLocation);
        Chunk_add(self, operands.first, line);
        Chunk_add(self, operands.second, line);
    } else {
        Chunk_add(self, OP_CONSTANT, line);
        Chunk_add(self, constLocation, line);
    }
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