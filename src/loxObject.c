#include <loxObject.h>
#include <loxMemory.h>
#include <stdint.h>



bool isObjType(LoxValue value, LoxObject_t type) {
    return (
        IS_LOX_OBJECT(value) &&
        LOX_OBJECT_TYPE(value) == type
    );
}


LoxString *copyString(const char* begin, const char* end) {
    size_t size = end - begin;
    char* heapBytes = ALLOCATE(char, size + 1);
    memcpy(heapBytes, begin, size);
    heapBytes[size] = '\0';
    uint32_t hash = hashString(heapBytes, size);
    return allocateString(heapBytes, size, hash);
}


LoxString* allocateString(char* heapBytes, size_t size, uint32_t hashCode) {
    LoxString* result = ALLOCATE_OBJECT(LoxString, LOX_OBJECT_STRING);
    result->size = size;
    result->bytes = heapBytes;
    result->hash = hashCode;
    return result;
}

uint32_t hashString(const char* const str, size_t length) {
  uint32_t hash = 919381917u;
  for (int i = 0; i < length; i++) {
    hash ^= (uint32_t)str[i];
    hash *= 12345678;
  }
  return hash;
}


LoxObject* allocateObject(size_t size, LoxObject_t type) {
    LoxObject* object = ALLOCATE(LoxObject, size);
    object->type = type;
    return object;
}


bool LoxObject_equals(LoxValue self, LoxValue other) {
    if (!(LOX_OBJECT_TYPE(self) == LOX_OBJECT_TYPE(other)))
        return false;

    switch (LOX_OBJECT_TYPE(self)) {
        case LOX_OBJECT_STRING: {
            LoxString* a = AS_LOX_STRING(self);
            LoxString* b = AS_LOX_STRING(other);
            if (a->size != b->size)
                return false;
            return memcmp(a->bytes, b->bytes, a->size) == 0;
        } // strings compared by value
        default:
            return AS_LOX_OBJECT(self) == AS_LOX_OBJECT(other); // unknown objects compared by reference
    }
}


void printObject(LoxValue value) {
    switch (LOX_OBJECT_TYPE(value))
    {
    case LOX_OBJECT_STRING:
        printf("%s", AS_LOX_CSTRING(value));
        break;
    default:
        printf("<Object at %p>", AS_LOX_OBJECT(value));
        break;
    }
}
