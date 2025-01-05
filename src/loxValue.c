#include <loxValue.h>
#include <loxObject.h>

bool LoxValue_isFalse(LoxValue value)
{
    switch (value.type)
    {
    case LOX_BOOL:
        return !AS_LOX_BOOL(value);
    case LOX_NUMBER:
        return AS_LOX_NUMBER(value) == 0;
    case LOX_OBJECT:
        return AS_LOX_OBJECT(value) == 0;
    case LOX_NIL:
        return true;
    }
    return false; // Unreachable
}

bool LoxValue_equals(LoxValue self, LoxValue other)
{
    if (self.type != other.type)
        return false;
    switch (self.type)
    {
    case LOX_BOOL:
        return AS_LOX_BOOL(self) == AS_LOX_BOOL(other);
    case LOX_NUMBER:
        return AS_LOX_NUMBER(self) == AS_LOX_NUMBER(other);
    case LOX_OBJECT:
        return LoxObject_equals(self, other);
    case LOX_NIL:
        return true;
    }
}

void printValue(LoxValue value)
{
    switch (value.type)
    {
    case LOX_BOOL:
        printf(AS_LOX_BOOL(value) ? "true" : "false");
        break;
    case LOX_NUMBER:
        printf("%g", AS_LOX_NUMBER(value));
        break;
    case LOX_NIL:
        printf("nil");
        break;
    case LOX_OBJECT:
        printObject(value);
        break;
    default:
        break;
    }
}