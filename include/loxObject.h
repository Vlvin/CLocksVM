#ifndef LOX_OBJECT_H
#define LOX_OBJECT_H

#include <oneFileSTD.h>
#include <loxValue.h>
#include <stdint.h>


typedef struct LoxVM LoxVM;


typedef enum {
    LOX_OBJECT_STRING = 0
} LoxObject_t;

typedef struct LoxObject {
    LoxObject_t type;
    LoxObject* next;
} LoxObject;


#define LOX_OBJECT_TYPE(value) (AS_LOX_OBJECT(value)->type)

typedef struct LoxString {
    LoxObject object;
    size_t size;
    char* bytes;
    uint32_t hash;
} LoxString;

#define AS_LOX_STRING(value) ((LoxString*)AS_LOX_OBJECT(value))
#define AS_LOX_CSTRING(value) (AS_LOX_STRING(value)->bytes)
#define ALLOCATE_OBJECT(vm, type, objectType) \
    (type*)allocateObject(vm, sizeof(type), objectType);

bool isObjType(LoxValue, LoxObject_t);
uint32_t hashString(const char* str, size_t length);
LoxString* copyString(LoxVM* vm, const char* begin, const char* end);
LoxString* allocateString(LoxVM* vm, char* heapBytes, size_t size, uint32_t hashCode);
LoxString* LoxString_concatenate(LoxVM* vm, LoxValue self, LoxValue other);

LoxObject* allocateObject(LoxVM* vm, size_t size, LoxObject_t type);
LoxObject* LoxObject_add(LoxVM* vm, LoxValue self, LoxValue other);
void LoxObject_free(LoxObject* self);



bool LoxObject_equals(LoxValue self, LoxValue other);
void printObject(LoxValue value);

#endif
