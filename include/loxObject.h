#ifndef LOX_OBJECT_H
#define LOX_OBJECT_H

#include <oneFileSTD.h>
#include <loxValue.h>

typedef enum {
    LOX_OBJECT_STRING = 0
} LoxObject_t;

typedef struct LoxObject {
    LoxObject_t type;
} LoxObject;


#define LOX_OBJECT_TYPE(value) (AS_LOX_OBJECT(value)->type)

typedef struct LoxString {
    LoxObject object;
    size_t size;
    char* bytes;
} LoxString;

#define AS_LOX_STRING(value) ((LoxString*)AS_LOX_OBJECT(value))
#define AS_LOX_CSTRING(value) (AS_LOX_STRING(value)->bytes)
#define ALLOCATE_OBJECT(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType);

bool isObjType(LoxValue, LoxObject_t);
LoxString* copyString(const char* begin, const char* end);
LoxString* allocateString(char* heapBytes, size_t size);
LoxObject* allocateObject(size_t size, LoxObject_t type);

bool LoxObject_equals(LoxValue self, LoxValue other);
void printObject(LoxValue value);

#endif