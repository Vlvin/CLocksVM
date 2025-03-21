#include <bitsTricks.h>
#include <loxChunk.h>
#include <oneFileSTD.h>

void Chunk_init(Chunk *self) {
  *self = (Chunk){0};
  ValueArray_init(&self->constants);
  LineTracker_init(&self->tracker);
}

int Chunk_add(Chunk *self, OpCode opcode, int line) {
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

int Chunk_free(Chunk *self) {
  FREE_ARRAY(uint8_t, self->code, self->capacity);
  Chunk_init(self);
  ValueArray_free(&(self->constants));
  LineTracker_free(&(self->tracker));
  return 0;
}

uint16_t Chunk_addConstant(Chunk *self, LoxValue value) {
  uint16_t constLocation = ValueArray_add(&(self->constants), value);
  return constLocation;
}

LoxValue Chunk_getConstant(Chunk *self, size_t index) {
  return ValueArray_data(&(self->constants))[index];
}

const size_t Chunk_size(Chunk *self) { return self->size; }
const size_t Chunk_capacity(Chunk *self) { return self->capacity; }
uint8_t *const Chunk_data(Chunk *self) { return self->code; }
