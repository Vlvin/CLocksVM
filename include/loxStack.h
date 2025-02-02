#include <loxValueArray.h>
#include <oneFileSTD.h>

#define STACK_MAX 256
#define STACK_FAILURE 754361029
#define STACK_SUCCESS 0
#define STACK_FAILURE_VAL LOX_NUMBER_VAL(754361029)

typedef struct LoxStack {
    LoxValue data[STACK_MAX];
    LoxValue *topElement;
} LoxStack;



void LoxStack_init(LoxStack *self);
void LoxStack_reset(LoxStack* self);
void LoxStack_free(LoxStack* self);
int LoxStack_push(LoxStack* self, LoxValue value);
LoxValue LoxStack_top(LoxStack* self);
/// @return pointer to top
LoxValue *LoxStack_rtop(LoxStack* self);
LoxValue LoxStack_pop(LoxStack* self);
LoxValue LoxStack_peek(LoxStack* self, size_t distance);
size_t LoxStack_size(LoxStack* self);