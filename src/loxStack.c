#include <loxValueArray.h>
#include <loxStack.h>
#include <loxMemory.h>
#include <oneFileSTD.h>


void LoxStack_init(LoxStack *self) {
    LoxStack_reset(self);
}


void LoxStack_reset(LoxStack* self) {
    *self = (LoxStack){0};
}

void LoxStack_free(LoxStack* self) {
    LoxStack_reset(self);
}

int LoxStack_push(LoxStack* self, LoxValue value) {
    if (LoxStack_size(self) >= STACK_MAX) {
        return STACK_FAILURE;
    }
    if (self->topElement == NULL)
        self->topElement = &self->data[0];

    *self->topElement = value;
    self->topElement = &self->topElement[1];
    return STACK_SUCCESS;
}

LoxValue LoxStack_top(LoxStack* self) {
    if (self->topElement == NULL) {
        return STACK_FAILURE_VAL;
    }
    return self->topElement[-1];
}

LoxValue *LoxStack_rtop(LoxStack* self) {
    if (self->topElement == NULL) {
        return NULL;
    }
    return self->topElement-1; // pointer arithmetics
}

LoxValue LoxStack_pop(LoxStack* self) {
    LoxValue top = LoxStack_top(self);
    if (self->topElement != &self->data[0])
        self->topElement = &self->topElement[-1];
    else 
        self->topElement = NULL;
    return top;
}

size_t LoxStack_size(LoxStack* self) {
    if (self->topElement == NULL) {
        return 0ul;
    }
    return self->topElement - &self->data[0];
}

LoxValue LoxStack_peek(LoxStack* self, size_t distance) {
  return self->topElement[-1 - distance];
}