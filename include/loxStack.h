#include <loxValue.h>
#include <oneFileSTD.h>

#define STACK_MAX 256
#define STACK_FAILURE 192993123
#define STACK_SUCCESS 0

typedef struct LoxStack {
    Value data[STACK_MAX];
    Value *topElement;
} LoxStack;



LoxStack LoxStack_init();
void LoxStack_reset(LoxStack* self);
void LoxStack_free(LoxStack* self);
int LoxStack_push(LoxStack* self, Value value);
Value LoxStack_top(LoxStack* self);
Value LoxStack_pop(LoxStack* self);
size_t LoxStack_size(LoxStack* self);