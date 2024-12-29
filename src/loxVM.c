#include <loxVM.h>
#include <loxMemory.h>
#include <loxCompiler.h>
#include <bitsTricks.h>
#include <debug.h>
#include <loxValue.h>
#include <loxErrors.h>

/**
 * @note
 * Please change api to 
 * LoxVM_init(LoxVM* self)
 * so we'll have no need to copy data all the time
 */
void LoxVM_init(LoxVM* self) {
    (*self) = (LoxVM){0};
    LoxStack_init(&self->stack);
}

void LoxVM_free(LoxVM* self) {
    LoxStack_free(&self->stack);
}


LoxResult _LoxVM_run(LoxVM* self, Chunk* chunk) {
    LoxStack* stack = &self->stack;

    #define READ_BYTE(vm) (*vm->instruction++)
    #define READ_CONST(vm) Chunk_getConstant(vm->chunk, READ_BYTE(vm))
    #define READ_CONST_LONG(vm) Chunk_getConstant(vm->chunk, forge_uint16((uint8_Pair){READ_BYTE(vm), READ_BYTE(vm)}))
    #define BINARY_OP(op, left_lox_type, output_lox_type) do { \
            if (!(IS_##left_lox_type(LoxStack_peek(stack, 0)) && IS_##left_lox_type(LoxStack_peek(stack, 1)))) { \
              runtimeError(self, "Runtime error %s %s", "Expected Type", # left_lox_type); \
              return LOX_INTERPRET_RUNTIME_ERROR; \
            } \
            LoxValue b = LoxStack_pop(stack); \
            LoxValue a = LoxStack_pop(stack); \
            LoxStack_push( \
              stack,  \
                output_lox_type##_VAL( \
                  AS_##left_lox_type(a) op AS_##left_lox_type(b) \
                ) \
            ); \
        } while(false);
    #define UNARY_OP(op, lox_type) do { \
            if (!IS_##lox_type(LoxStack_peek(stack, 0))) {\
              runtimeError(self, "Expected Type %s", # lox_type); \
              return LOX_INTERPRET_RUNTIME_ERROR; \
            }\
            *LoxStack_rtop(stack) = lox_type##_VAL(op AS_##lox_type(LoxStack_top(stack))); \
            } while(false);

    self->chunk = chunk;
    self->instruction = chunk->code;

    while (self->instruction < &chunk->code[chunk->size]) {
        uint8_t instruction;
        #ifdef DEBUG_TRACE
        printf("    ");
        for (LoxValue* slot = self->stack.data; slot < self->stack.topElement; slot++) {
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
                LoxValue constant = READ_CONST(self);
                LoxStack_push(stack, constant);
                break;
            }
            case OP_CONSTANT_LONG: {
                LoxValue constant = READ_CONST_LONG(self);
                LoxStack_push(stack, constant);
                break;
            }
            case OP_NEGATE:
                UNARY_OP(-, LOX_NUMBER)
                break;
            case OP_NOT:
                LoxStack_push(stack, LOX_BOOL_VAL(LoxValue_isFalse(LoxStack_pop(stack))));
                break;
            case OP_EQUALS: {
                LoxValue b = LoxStack_pop(stack);
                LoxValue a = LoxStack_pop(stack);
                LoxStack_push(stack, LOX_BOOL_VAL(LoxValue_equals(a, b)));
                break;
            }
            case OP_LESS:
                BINARY_OP(<, LOX_NUMBER, LOX_BOOL)
                break;
            case OP_GREATER: 
                BINARY_OP(>, LOX_NUMBER, LOX_BOOL)
                break;
            case OP_ADD:
                BINARY_OP(+, LOX_NUMBER, LOX_NUMBER)
                break;
            case OP_SUBSTRACT:
                BINARY_OP(-, LOX_NUMBER, LOX_NUMBER)
                break;
            case OP_MULTIPLY:
                BINARY_OP(*, LOX_NUMBER, LOX_NUMBER)
                break;
            case OP_DIVIDE:
                BINARY_OP(/, LOX_NUMBER, LOX_NUMBER)
                break;
            case OP_AND:
                BINARY_OP(&&, LOX_BOOL, LOX_BOOL)
                break;
            case OP_OR:
                BINARY_OP(||, LOX_BOOL, LOX_BOOL)
                break;
            case OP_TRUE:
                LoxStack_push(stack, LOX_BOOL_VAL(true));
                break;
            case OP_FALSE:
                LoxStack_push(stack, LOX_BOOL_VAL(false));
            case OP_NIL:
                LoxStack_push(stack, LOX_NIL_VAL);
                break;
            case OP_RETURN:
                printf("return ");
                printValue(LoxStack_pop(stack));
                printf("\n\n");
                return LOX_INTERPRET_OK;
        }
        printf("\n");
    }
    printf("\n\n");
    return LOX_INTERPRET_RUNTIME_ERROR;

    #undef READ_BYTE
    #undef READ_CONST
    #undef READ_CONST_LONG
    #undef UNARY_OP
    #undef BINARY_OP
}



LoxResult LoxVM_interpret(LoxVM* self, const char* source) {
    Chunk chunk;
    Chunk_init(&chunk);

    LoxCompiler compiler;
    LoxCompiler_init(&compiler);

    if (!LoxCompiler_compile(&compiler, source, &chunk)) {
        Chunk_free(&chunk);
        LoxCompiler_free(&compiler);
        return LOX_INTERPRET_COMPILE_ERROR;
    }

    self->chunk = &chunk;
    self->instruction = &chunk.code[0];

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