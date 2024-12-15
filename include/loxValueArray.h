#ifndef LOX_VALUE_ARRAY_H
#define LOX_VALUE_ARRAY_H

#include <oneFileSTD.h>
#include <loxValue.h>


typedef struct ValueArray {
    size_t capacity, size;
    LoxValue* data;
} ValueArray;


void ValueArray_init(ValueArray* self);
int ValueArray_free(ValueArray* self);
size_t ValueArray_add(ValueArray* self, LoxValue value);


void printValue(LoxValue value);

const size_t ValueArray_size(ValueArray* self);
const size_t ValueArray_capacity(ValueArray* self);
LoxValue * const ValueArray_data(ValueArray* self);

#endif