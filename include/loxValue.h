#ifndef LOX_VALUE_H
#define LOX_VALUE_H

#include <oneFileSTD.h>

typedef struct LoxObject LoxObject;
typedef struct LoxString LoxString;

typedef enum { LOX_BOOL, LOX_NIL, LOX_NUMBER, LOX_OBJECT } loxValueType;

typedef struct LoxValue {
  loxValueType type;
  union {
    // char * string;
    bool boolean;
    double number;
    LoxObject *object;
  } as;
} LoxValue;

#define LOX_BOOL_VAL(bool)                                                     \
  (LoxValue) {                                                                 \
    LOX_BOOL, { .boolean = bool }                                              \
  }
#define LOX_NUMBER_VAL(num)                                                    \
  (LoxValue) {                                                                 \
    LOX_NUMBER, { .number = num }                                              \
  }
#define LOX_OBJECT_VAL(obj)                                                    \
  (LoxValue) {                                                                 \
    LOX_OBJECT, { .object = (LoxObject *)obj }                                 \
  }
#define LOX_NIL_VAL                                                            \
  (LoxValue) { LOX_NIL, {.number = 0} }

// checks
#define IS_SAME_TYPE(value, loxtype) ((value).type == loxtype)

#define IS_LOX_BOOL(value) IS_SAME_TYPE(value, LOX_BOOL)
#define IS_LOX_NUMBER(value) IS_SAME_TYPE(value, LOX_NUMBER)
#define IS_LOX_OBJECT(value) IS_SAME_TYPE(value, LOX_OBJECT)
#define IS_LOX_NIL(value) IS_SAME_TYPE(value, LOX_NIL)

#define AS_LOX_BOOL(value) ((value).as.boolean)
#define AS_LOX_NUMBER(value) ((value).as.number)
#define AS_LOX_OBJECT(value) ((value).as.object)

bool LoxValue_isFalse(LoxValue self);
bool LoxValue_equals(LoxValue self, LoxValue other);
void printValue(LoxValue value);

#endif
