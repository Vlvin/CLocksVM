#include <value.h>
#include <loxMemory.h>

ValueArray ValueArray_init() {
    ValueArray ret = {
        0, 0, NULL
    };
    return ret;
}

int ValueArray_free(ValueArray* self) {
    self->data = reallocate(self->data, self->capacity, 0);
    (*self) = ValueArray_init();
    return 0;
}

size_t ValueArray_add(ValueArray* self, Value value) {
    if (ValueArray_size(self) == ValueArray_capacity(self)) {
        int newCapacity = ValueArray_capacity(self) * 2;
        if (ValueArray_capacity(self) < 8) {
            newCapacity = 8;
        }
        self->data = reallocate(self->data, self->capacity, newCapacity);
        self->capacity = newCapacity;
        if (NULL == ValueArray_data(self))
            exit(1);
    }
    ValueArray_data(self)[self->size] = value;
    size_t valuePosition = ValueArray_size(self);
    self->size++;
    return valuePosition;
}


void printValue(Value value) {
    printf("%g", value);
}

const size_t ValueArray_size(ValueArray* self) {
    return self->size;
}

const size_t ValueArray_capacity(ValueArray* self) {
    return self->capacity;
}

Value * const ValueArray_data(ValueArray* self) {
    return self->data;
}