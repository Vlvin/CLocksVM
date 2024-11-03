#ifndef LOX_VALUE_H
#define LOX_VALUE_H

#include <oneFileSTD.h>

typedef double Value;

typedef struct ValueArray {
    size_t capacity, size;
    Value* data;
} ValueArray;


ValueArray ValueArray_init();
int ValueArray_free(ValueArray* self);
size_t ValueArray_add(ValueArray* self, Value value);


void printValue(Value value);

const size_t ValueArray_size(ValueArray* self);
const size_t ValueArray_capacity(ValueArray* self);
Value * const ValueArray_data(ValueArray* self);

#endif