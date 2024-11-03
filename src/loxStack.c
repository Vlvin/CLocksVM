#include <loxValue.h>
#include <loxStack.h>
#include <loxMemory.h>
#include <oneFileSTD.h>


LoxStack LoxStack_init() {
    LoxStack self;
    LoxStack_reset(&self);
    return self;
}


void LoxStack_reset(LoxStack* self) {
    *self = (LoxStack){0};
    self->topElement = NULL;
}

void LoxStack_free(LoxStack* self) {
    LoxStack_reset(self);
}

int LoxStack_push(LoxStack* self, Value value) {
    if (LoxStack_size(self) >= STACK_MAX) {
        return STACK_FAILURE;
    }
    if (self->topElement == NULL)
        self->topElement = &self->data[0];

    *self->topElement = value;
    self->topElement = &self->topElement[1];
    return STACK_SUCCESS;
}

Value LoxStack_top(LoxStack* self) {
    if (self->topElement == NULL) {
        return STACK_FAILURE;
    }
    return self->topElement[-1];
}

Value LoxStack_pop(LoxStack* self) {
    Value top = LoxStack_top(self);
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