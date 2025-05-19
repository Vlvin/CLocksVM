#ifndef LOX_OBJECT_H
#define LOX_OBJECT_H

#include "loxChunk.h"
#include "loxCompiler.h"
#include <loxValue.h>
#include <oneFileSTD.h>
#include <stdint.h>

typedef struct LoxVM LoxVM;

// Object

typedef enum { LOX_OBJECT_STRING = 0, LOX_OBJECT_FUNCTION } LoxObjectType;

typedef struct LoxObject {
  LoxObjectType type;
  LoxObject *next;
} LoxObject;

#define LOX_OBJECT_TYPE(value) (AS_LOX_OBJECT(value)->type)

bool isObjType(LoxValue, LoxObjectType);
LoxObject *allocateObject(LoxVM *vm, size_t size, LoxObjectType type);
void LoxObject_free(LoxObject *self);
bool LoxObject_equals(LoxValue self, LoxValue other);
void printObject(LoxValue value);

// Generic
LoxObject *LoxObject_add(LoxVM *vm, LoxValue self, LoxValue other);

// String

typedef struct LoxString {
  LoxObject object;
  int size;
  char *bytes;
  size_t hash;
} LoxString;

#define AS_LOX_STRING(value) ((LoxString *)AS_LOX_OBJECT(value))
#define AS_LOX_CSTRING(value) (AS_LOX_STRING(value)->bytes)
#define ALLOCATE_OBJECT(vm, type, objectType)                                  \
  (type *)allocateObject(vm, sizeof(type), objectType);

uint32_t hashString(const char *str, size_t length);
LoxString *copyString(LoxVM *vm, const char *begin, size_t size);
LoxString *allocateString(LoxVM *vm, char *heapBytes, size_t size,
                          uint32_t hashCode);
LoxString *LoxString_concatenate(LoxVM *vm, LoxValue self, LoxValue other);

// Function

typedef struct LoxFunction {
  LoxObject object;
  uint arity;
  Chunk chunk;
  LoxString *name;
  LoxScopeType type;
} LoxFunction;
#define AS_LOX_FUNCTION(value) ((LoxFunction *)AS_LOX_OBJECT(value))

LoxFunction *LoxFunction_new(LoxScopeType scope_type);

void LoxFunction_print(LoxFunction *self);

LoxString *LoxFunction_toString(LoxVM *vm, LoxFunction *self);

#endif
