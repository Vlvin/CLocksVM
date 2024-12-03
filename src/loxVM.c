#include <loxVM.h>
#include <loxMemory.h>
#include <loxCompiler.h>
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
    LoxStack* stack = &self->stack;
    #define READ_BYTE(vm) (*vm->instruction++)
    #define READ_CONST(vm) Chunk_getConstant(vm->chunk, READ_BYTE(vm))
    #define READ_CONST_LONG(vm) Chunk_getConstant(vm->chunk, forge_uint16((uint8_Pair){READ_BYTE(vm), READ_BYTE(vm)}))
    #define BINARY_OP(op) do { \
            Value b = LoxStack_pop(stack); \
            Value a = LoxStack_pop(stack); \
            Value result = (a op b); \
            LoxStack_push(stack, result); \
            printValue(LoxStack_top(stack)); \
        } while(false);
    #define UNARY_OP(op) do { \
            Value* value = LoxStack_rtop(stack); \
            *value = op LoxStack_top(stack); \
            printValue(LoxStack_top(stack)); \
        } while(false);

    self->chunk = chunk;
    self->instruction = chunk->code;

    while (self->instruction < &chunk->code[chunk->size]) {
        uint8_t instruction;
        #ifdef DEBUG_TRACE
        printf("stack L-R   ");
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

        printf("Expression result ");
        switch (instruction = READ_BYTE(self)) {
            case OP_CONSTANT: {
                Value constant = READ_CONST(self);
                LoxStack_push(stack, constant);
                printValue(LoxStack_top(stack));
                break;
            }
            case OP_CONSTANT_LONG: {
                Value constant = READ_CONST_LONG(self);
                LoxStack_push(stack, constant);
                printValue(LoxStack_top(stack));
                break;
            }
            case OP_NEGATE:
                UNARY_OP(-)
                break;
            case OP_NOT:
                UNARY_OP(!)
                break;
            case OP_ADD:
                BINARY_OP(+)
                break;
            case OP_SUBSTRACT:
                BINARY_OP(-)
                break;
            case OP_MULTIPLY:
                BINARY_OP(*)
                break;
            case OP_DIVIDE:
                BINARY_OP(/)
                break;
            case OP_AND:
                BINARY_OP(&&)
                break;
            case OP_OR:
                BINARY_OP(||)
                break;
            case OP_RETURN:
                printf("return ");
                printValue(LoxStack_pop(stack));
                printf("\n\n");
                return LOX_INTERPRET_OK;
        }
        printf("\n\n");
    }
    return LOX_INTERPRET_RUNTIME_ERROR;

    #undef READ_BYTE
    #undef READ_CONST
    #undef READ_CONST_LONG
    #undef UNARY_OP
    #undef BINARY_OP
}



LoxResult LoxVM_interpret(LoxVM* self, const char* source) {
    Chunk chunk = Chunk_init();

    LoxCompiler compiler = LoxCompiler_init();

    if (!LoxCompiler_compile(&compiler, source, &chunk)) {
        Chunk_free(&chunk);
        LoxCompiler_free(&compiler);
        return LOX_INTERPRET_COMPILE_ERROR;
    }

    self->chunk = &chunk;
    self->instruction = chunk.code[0];

    LoxResult result = _LoxVM_run(self, &chunk);
    return result;
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