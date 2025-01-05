#include <loxObject.h>
#include <loxMemory.h>



bool isObjType(LoxValue value, LoxObject_t type) {
    return (
        IS_LOX_OBJECT(value) &&
        LOX_OBJECT_TYPE(value) == type
    );
}


LoxString *copyString(const char* begin, const char* end) {
    const size_t size = end - begin;
    char* heapBytes = ALLOCATE(char, size + 1);
    memcpy(heapBytes, begin, size);
    heapBytes[size] = '\0';
    return allocateString(heapBytes, size);
}


LoxString* allocateString(char* heapBytes, size_t size) {
    LoxString* result = ALLOCATE_OBJECT(LoxString, LOX_OBJECT_STRING);
    result->size = size;
    result->bytes = heapBytes;
    return result;
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
        printf(AS_LOX_CSTRING(value));
        break;
    default:
        printf("<Object ar %p>", AS_LOX_OBJECT(value));
        break;
    }
}