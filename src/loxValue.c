#include <loxValue.h>

bool LoxValue_isFalse(LoxValue value)
{
    switch (value.type)
    {
        case LOX_BOOL: return !AS_LOX_BOOL(value);
        case LOX_NUMBER: return AS_LOX_NUMBER(value) == 0;
        case LOX_NIL: return true;
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
    case LOX_NIL:
        return true;
    }
}