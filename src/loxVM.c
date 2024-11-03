#include <loxVM.h>
#include <loxMemory.h>
#include <loxMemory.h>
#include <bitsTricks.h>
#include <debug.h>

/**
 * @note
 * Please change api to 
 * LoxVM_init(LoxVM*)
 * so we'll have no need to copy data all the time
 */
LoxVM LoxVM_init() {
    LoxVM self = {0};
    self.stack = LoxStack_init();
    return self;
}

void LoxVM_free(LoxVM* self) {
    LoxStack_free(&self->stack);
}


LoxResult _LoxVM_run(LoxVM* self, Chunk* chunk) {
    #define READ_BYTE(vm) (*vm->instruction++)
    #define READ_CONST(vm) Chunk_getConstant(vm->chunk, READ_BYTE(vm))
    #define READ_CONST_LONG(vm) Chunk_getConstant(vm->chunk, forge_uint16((uint8_Pair){READ_BYTE(vm), READ_BYTE(vm)}))

    while (self->instruction < &chunk->code[chunk->size]) {
        uint8_t instruction;
        #ifdef DEBUG_TRACE
        printf("        ");
        for (Value* slot = self->stack.data; slot < self->stack.topElement; slot++) {
            printf("[ ");
            printValue(*slot);
            printf(" ]");
        }
        printf("\n");
        disassembleInstruction(
            chunk,
            (int)(self->instruction - chunk->code),
            "LoxRun"
        );
        #endif
        switch (instruction = READ_BYTE(self)) {
            case OP_CONSTANT: {
                Value constant = READ_CONST(self);
                LoxStack_push(&self->stack, constant);
                printValue(constant);
                printf("\n");
                break;
            }
            case OP_CONSTANT_LONG: {
                Value constant = READ_CONST_LONG(self);
                LoxStack_push(&self->stack, constant);
                printValue(constant);
                printf("\n");
                break;
            }
            case OP_RETURN:
                printf("return ");
                printValue(LoxStack_pop(&self->stack));
                printf("\n");
                return LOX_INTERPRET_OK;
        }
    }
    return LOX_INTERPRET_RUNTIME_ERROR;

    #undef READ_BYTE
    #undef READ_CONST
    #undef READ_CONST_LONG
}


LoxResult LoxVM_interpret(LoxVM* self, Chunk* chunk) {
    self->chunk = chunk;
    self->instruction = chunk->code;
    return _LoxVM_run(self, chunk);
}



void Lox_VM_printResult(LoxResult result) {
    switch (result) {
        case LOX_INTERPRET_OK:
            printf("LOX_INTERPRET_OK\n");
            break;
        case LOX_INTERPRET_COMPILE_ERROR:
            printf("LOX_INTERPRET_COMPILE_ERROR\n");
            break;
        case LOX_INTERPRET_RUNTIME_ERROR:
            printf("LOX_INTERPRET_RUNTIME_ERROR\n");
            break;
    }
}