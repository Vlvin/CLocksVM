#include "loxCompiler.h"
#include "loxErrors.h"
#include <loxMemory.h>
#include <loxObject.h>
#include <loxVM.h>
#include <stdint.h>

bool isObjType(LoxValue value, LoxObjectType type) {
  return (IS_LOX_OBJECT(value) && LOX_OBJECT_TYPE(value) == type);
}

LoxString *copyString(LoxVM *vm, const char *begin, size_t size) {
  uint32_t hash = hashString(begin, size);
  LoxString *interned = LoxHashMap_findString(&vm->strings, begin, size, hash);
  if (interned != NULL) {
    return interned;
  }
  char *heapBytes = ALLOCATE(char, size + 1);
  memcpy(heapBytes, begin, size);
  heapBytes[size] = '\0';

  return allocateString(vm, heapBytes, size, hash);
}

LoxString *allocateString(LoxVM *vm, char *heapBytes, size_t size,
                          uint32_t hashCode) {
  LoxString *result = ALLOCATE_OBJECT(vm, LoxString, LOX_OBJECT_STRING);
  result->size = size;
  result->bytes = heapBytes;
  result->hash = hashCode;
  LoxHashMap_set(&vm->strings, result, LOX_NIL_VAL);
  return result;
}

uint32_t hashString(const char *const str, size_t length) {
  uint32_t hash = 919381917u;
  for (int i = 0; i < length; i++) {
    hash ^= (size_t)str[i];
    hash *= 12345678;
  }
  return hash;
}

LoxObject *allocateObject(LoxVM *vm, size_t size, LoxObjectType type) {
  LoxObject *object = ALLOCATE(LoxObject, size);
  object->type = type;
  object->next = vm->objects;
  vm->objects = object;
  return object;
}

LoxString *LoxString_concatenate(LoxVM *vm, LoxValue self, LoxValue other) {
  size_t size = AS_LOX_STRING(self)->size + AS_LOX_STRING(other)->size;
  LoxString *result = allocateString(vm, ALLOCATE(char, size + 1), size, -1);
  strcpy(result->bytes, AS_LOX_CSTRING(self));
  strcat(result->bytes, AS_LOX_CSTRING(other));
  result->hash = hashString(result->bytes, result->size);
  return result;
}

void LoxObject_free(LoxObject *self) {
  switch (self->type) {
  case LOX_OBJECT_STRING: {
    LoxString *self_str = (LoxString *)self;
    FREE_ARRAY(char, self_str->bytes, self_str->size);
    FREE(LoxString, self);
    break;
  }
  case LOX_OBJECT_FUNCTION: {
    LoxFunction *self_fun = (LoxFunction *)self;
    Chunk_free(&self_fun->chunk);
    FREE(LoxFunction, self);
    break;
  }
  }
}

LoxObject *LoxObject_add(LoxVM *vm, LoxValue self, LoxValue other) {
  if (LOX_OBJECT_TYPE(self) != LOX_OBJECT_TYPE(other)) {
    return NULL;
  }
  switch (LOX_OBJECT_TYPE(self)) {
  case LOX_OBJECT_STRING:
    return (LoxObject *)LoxString_concatenate(vm, self, other);
    break;
  default: // only if value is not of math type
    return NULL;
  }
}

bool LoxObject_equals(LoxValue self, LoxValue other) {
  if (!(LOX_OBJECT_TYPE(self) == LOX_OBJECT_TYPE(other)))
    return false;

  switch (LOX_OBJECT_TYPE(self)) {
  case LOX_OBJECT_STRING: {
    return AS_LOX_STRING(self) == AS_LOX_STRING(other);
  } // strings compared by reference cause of string interning
  default:
    return AS_LOX_OBJECT(self) ==
           AS_LOX_OBJECT(other); // unknown objects compared by reference
  }
}

void printObject(LoxValue value) {
  switch (LOX_OBJECT_TYPE(value)) {
  case LOX_OBJECT_STRING:
    printf("%s", AS_LOX_CSTRING(value));
    break;
  case LOX_OBJECT_FUNCTION:
    LoxFunction_print(AS_LOX_FUNCTION(value));
    break;
  default:
    printf("<Object at %p>", AS_LOX_OBJECT(value));
    break;
  }
}

LoxFunction *LoxFunction_new(LoxScopeType scope_type) {
  LoxFunction *self = ALLOCATE_OBJECT(&vm, LoxFunction, LOX_OBJECT_FUNCTION);
  self->arity = 0;
  self->name = NULL;
  self->type = scope_type;
  Chunk_init(&self->chunk);
  return self;
}
bool LoxFunction_call(LoxFunction *self, LoxVM *vm, int argCount) {
  if (self->arity != argCount) {
    runtimeError(vm, "Expected %ud arguments, but got %d", self->arity,
                 argCount);
    return false;
  }
  LoxCallFrame *frame = &vm->frames[vm->frameCount++];
  frame->function = self;
  frame->instruction = self->chunk.code;
  frame->slots = vm->stack.topElement - argCount - 1;
  return true;
}

void LoxFunction_print(LoxFunction *self) {
  if (self->type == LOX_TYPE_TOP_LEVEL) {
    printf("<script %*s>", self->name->size, self->name->bytes);
    return;
  }
  printf("<fn %*s>", self->name->size, self->name->bytes);
}

LoxString *LoxFunction_toString(LoxVM *vm, LoxFunction *self) {
  size_t size = self->name->size + 5;
  char result[size];
  sprintf(result, "<fn %s>", self->name->bytes);
  return copyString(vm, result, strlen(result));
}
