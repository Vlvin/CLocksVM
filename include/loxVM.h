#ifndef LOX_VIRTUAL_MACHINE_H
#define LOX_VIRTUAL_MACHINE_H

#include <loxChunk.h>
#include <loxStack.h>

typedef struct {
    Chunk* chunk;
    uint8_t* instruction;
    LoxStack stack;
} LoxVM;

typedef enum LoxResult {
    LOX_INTERPRET_OK,
    LOX_INTERPRET_COMPILE_ERROR,
    LOX_INTERPRET_RUNTIME_ERROR,
} LoxResult;

void Lox_VM_printResult(LoxResult result);

void LoxVM_init(LoxVM* self);
void LoxVM_free(LoxVM* self);

LoxResult LoxVM_interpret(LoxVM* self, const char* source);
LoxResult _LoxVM_run(LoxVM* self, Chunk* chunk);


#endif