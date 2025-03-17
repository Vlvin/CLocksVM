#include <loxMemory.h>
#include <loxValueArray.h>

void ValueArray_init(ValueArray *self) { (*self) = (ValueArray){0, 0, NULL}; }

int ValueArray_free(ValueArray *self) {
  FREE_ARRAY(LoxValue, self->data, self->capacity);
  ValueArray_init(self);
  return 0;
}

uint16_t ValueArray_add(ValueArray *self, LoxValue value) {
  if (self->size == self->capacity) {
    GROW_ARRAY(LoxValue, self->data, self->capacity);
    self->capacity = GROW_CAPACITY(self->capacity);
    if (NULL == (self->data)) {
      exit(1);
    }
  }
  self->data[self->size] = value;
  uint16_t valuePosition = self->size;
  self->size++;
  return valuePosition;
}

const size_t ValueArray_size(ValueArray *self) { return self->size; }

const size_t ValueArray_capacity(ValueArray *self) { return self->capacity; }

LoxValue *const ValueArray_data(ValueArray *self) { return self->data; }
