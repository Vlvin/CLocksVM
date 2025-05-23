#include "loxChunk.h"
#include <bitsTricks.h>
#include <debug.h>
#include <loxCompiler.h>
#include <loxErrors.h>
#include <loxMemory.h>
#include <loxObject.h>
#include <loxVM.h>
#include <loxValue.h>

LoxVM vm;

/**
 * @note
 * Please change api to
 * LoxVM_init(LoxVM* self)
 * so we'll have no need to copy data all the time
 */
void LoxVM_init(LoxVM *self) {
  (*self) = (LoxVM){0};
  LoxStack_init(&self->stack);
  LoxHashMap_init(&self->strings);
  LoxHashMap_init(&self->globals);

  self->objects = NULL;
}

void LoxVM_free(LoxVM *self) {
  LoxStack_free(&self->stack);
  LoxHashMap_free(&self->strings);
  LoxHashMap_free(&self->globals);
  LoxVM_freeObjects(self);
}

void LoxVM_freeObjects(LoxVM *self) {
  LoxObject *cur = NULL;
  LoxObject *next = self->objects;
  self->objects = NULL;
  while (next != NULL) {
    cur = next;
    next = next->next;
    LoxObject_free(cur);
  }
}

LoxResult _LoxVM_run(LoxVM *self) {
  LoxStack *stack = &self->stack;
  LoxCallFrame *frame = &self->frames[self->frameCount - 1];

  Chunk *chunk = &frame->function->chunk;

#define GET_FRAME(vm) (frame)

#define READ_BYTE(vm) (*(GET_FRAME(vm))->instruction++)
#define READ_SHORT(vm)                                                         \
  (forge_uint16((uint8_Pair){*(GET_FRAME(vm))->instruction++,                  \
                             *(GET_FRAME(vm))->instruction++}))
#define READ_CONST(vm)                                                         \
  Chunk_getConstant(&GET_FRAME(vm)->function->chunk, READ_BYTE((vm)))
#define READ_CONST_LONG(vm)                                                    \
  Chunk_getConstant(                                                           \
      &GET_FRAME(vm)->function->chunk,                                         \
      forge_uint16((uint8_Pair){READ_BYTE((vm)), READ_BYTE((vm))}))
#define BINARY_OP(op, left_lox_type, output_lox_type)                          \
  do {                                                                         \
    if (!(IS_##left_lox_type(LoxStack_peek(stack, 0)) &&                       \
          IS_##left_lox_type(LoxStack_peek(stack, 1)))) {                      \
      runtimeError(self, "Expected Type %s", #left_lox_type);                  \
      return LOX_INTERPRET_RUNTIME_ERROR;                                      \
    }                                                                          \
    LoxValue b = LoxStack_pop(stack);                                          \
    LoxValue a = LoxStack_pop(stack);                                          \
    LoxStack_push(stack, output_lox_type##_VAL(AS_##left_lox_type(a)           \
                                                   op AS_##left_lox_type(b))); \
  } while (false);
#define UNARY_OP(op, lox_type)                                                 \
  do {                                                                         \
    if (!IS_##lox_type(LoxStack_peek(stack, 0))) {                             \
      runtimeError(self, "Expected Type %s", #lox_type);                       \
      return LOX_INTERPRET_RUNTIME_ERROR;                                      \
    }                                                                          \
    *LoxStack_rtop(stack) =                                                    \
        lox_type##_VAL(op AS_##lox_type(LoxStack_top(stack)));                 \
  } while (false);

  // frame->instruction = chunk->code;
  // self->chunk = chunk;
  // self->instruction = chunk->code;

  while (frame->instruction < &chunk->code[chunk->size]) {
    uint8_t instruction;
#ifdef DEBUG_TRACE
    LoxStack_print(stack);
    disassembleInstruction(
        chunk,
        (int)(self->frames[self->frameCount - 1].instruction - chunk->code),
        "LoxRun");
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
    case OP_ADD: {
      if (IS_LOX_OBJECT(LoxStack_peek(stack, 0)) &&
          IS_LOX_OBJECT(LoxStack_peek(stack, 1))) {
        LoxValue b = LoxStack_pop(stack);
        LoxValue a = LoxStack_pop(stack);
        LoxStack_push(stack, LOX_OBJECT_VAL(LoxObject_add(self, a, b)));
      } else if (IS_LOX_NUMBER(LoxStack_peek(stack, 0)) &&
                 IS_LOX_NUMBER(LoxStack_peek(stack, 1))) {
        LoxValue b = LoxStack_pop(stack);
        LoxValue a = LoxStack_pop(stack);
        LoxStack_push(stack,
                      LOX_NUMBER_VAL(AS_LOX_NUMBER(a) + AS_LOX_NUMBER(b)));
      } else {
        runtimeError(
            self,
            "Operands must be of equal types (two numbers, two objects, etc.)");
        return LOX_INTERPRET_RUNTIME_ERROR;
      }
      break;
    }
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
      break;
    case OP_NIL:
      LoxStack_push(stack, LOX_NIL_VAL);
      break;
    case OP_PRINT:
      printValue(LoxStack_pop(stack));
      printf("\n");
      break;
    case OP_POP:
      LoxStack_pop(stack);
      break;
    case OP_DEFINE_GLOBAL: {
      LoxString *name = AS_LOX_STRING(READ_CONST(&vm));
      LoxHashMap_set(&self->globals, name, LoxStack_peek(stack, 0));
      LoxStack_pop(stack);
      break;
    }
    case OP_DEFINE_GLOBAL_LONG: {
      LoxString *name = AS_LOX_STRING(READ_CONST_LONG(&vm));
      LoxHashMap_set(&self->globals, name, LoxStack_peek(stack, 0));
      LoxStack_pop(stack);
      break;
    }
    case OP_GET_GLOBAL: {
      LoxString *name = AS_LOX_STRING(READ_CONST(&vm));
      LoxValue value;
      if (!LoxHashMap_get(&self->globals, name, &value)) { // does not exist
        runtimeError(&vm, "Undefined variable %s\n", AS_LOX_CSTRING(value));
        return LOX_INTERPRET_RUNTIME_ERROR;
      }
      LoxStack_push(stack, value);
      break;
    }
    case OP_GET_GLOBAL_LONG: {
      LoxString *name = AS_LOX_STRING(READ_CONST_LONG(&vm));
      LoxValue value;
      if (!LoxHashMap_get(&self->globals, name, &value)) { // does not exist
        runtimeError(&vm, "Undefined variable %s\n", AS_LOX_CSTRING(value));
        return LOX_INTERPRET_RUNTIME_ERROR;
      }
      LoxStack_push(stack, value);
      break;
    }
    case OP_GET_LOCAL: {
      uint8_t slot = READ_BYTE(&vm);
      LoxStack_push(stack, frame->slots[slot]);
      break;
    }
    case OP_SET_GLOBAL: {
      LoxString *name = AS_LOX_STRING(READ_CONST(&vm));
      if (!LoxHashMap_set(&self->globals, name,
                          LoxStack_peek(stack, 0))) { // does not exist
        LoxHashMap_delete(&self->globals, name);
        runtimeError(self, "Undefined variable %s\n", name->bytes);
        return LOX_INTERPRET_RUNTIME_ERROR;
      }
      break;
    }
    case OP_SET_GLOBAL_LONG: {
      LoxString *name = AS_LOX_STRING(READ_CONST_LONG(&vm));
      if (!LoxHashMap_set(&self->globals, name,
                          LoxStack_peek(stack, 0))) { // does not exist
        LoxHashMap_delete(&self->globals, name);
        runtimeError(self, "Undefined variable %s\n", name->bytes);
        return LOX_INTERPRET_RUNTIME_ERROR;
      }
      break;
    }
    case OP_SET_LOCAL: {
      uint8_t slot = READ_BYTE(&vm);
      frame->slots[slot] = LoxStack_peek(stack, 0);
      break;
    }
    case OP_JUMP_IF_FALSE: {
      uint16_t offset = READ_SHORT(&vm);

      // branchless :))
      frame->instruction += offset * LoxValue_isFalse(LoxStack_peek(stack, 0));
      break;
    }
    case OP_JUMP: {
      uint16_t offset = READ_SHORT(&vm);
      frame->instruction += offset;
      break;
    }
    case OP_LOOP: {
      uint16_t offset = READ_SHORT(&vm);
      frame->instruction -= offset;
      break;
    }
    case OP_RETURN:
      return LOX_INTERPRET_OK;
    }
  }
  return LOX_INTERPRET_RUNTIME_ERROR;

#undef READ_BYTE
#undef READ_SHORT
#undef READ_CONST
#undef READ_CONST_LONG
#undef UNARY_OP
#undef BINARY_OP
}

LoxResult LoxVM_interpret(LoxVM *self, const char *source) {

  LoxCompiler compiler;
  LoxCompiler_init(&compiler, NULL, LOX_TYPE_TOP_LEVEL);

  LoxFunction *function = LoxCompiler_compile(&compiler, source);

  if (!function) {
    LoxCompiler_free(&compiler);
    return LOX_INTERPRET_COMPILE_ERROR;
  }

  LoxStack_push(&self->stack, LOX_OBJECT_VAL(function));
  LoxCallFrame *frame = &self->frames[self->frameCount++];

  // self->chunk = chunk;
  // self->instruction = &chunk->code[0];
  frame->function = function;
  frame->instruction = frame->function->chunk.code;
  frame->slots = self->stack.data;

  LoxResult result = _LoxVM_run(self);

  LoxCompiler_free(&compiler);
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
