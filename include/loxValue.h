#ifndef LOX_VALUE_H
#define LOX_VALUE_H

#include <oneFileSTD.h>

typedef enum {
  LOX_BOOL,
  LOX_NUMBER,
  // LOX_STRING,
  LOX_NIL
} loxValueType;

typedef struct {
  loxValueType type;
  union {
    // char * string;
    bool boolean;
    double number;
  } as;
} LoxValue;

#define LOX_BOOL_VAL(value) (LoxValue){LOX_BOOL, {.boolean = value}}
#define LOX_NUMBER_VAL(value) (LoxValue){LOX_NUMBER, {.number = value}}
#define LOX_NIL_VAL (LoxValue){LOX_NIL, {.number = 0}}

// checks
#define IS_SAME_TYPE(value, loxtype) ((value).type == loxtype)

#define IS_LOX_BOOL(value) IS_SAME_TYPE(value, LOX_BOOL)
#define IS_LOX_NUMBER(value) IS_SAME_TYPE(value, LOX_NUMBER)
#define IS_LOX_NIL(value) IS_SAME_TYPE(value, LOX_NIL)

#define AS_LOX_BOOL(value) ((value).as.boolean)
#define AS_LOX_NUMBER(value) ((value).as.number)


bool LoxValue_isFalse(LoxValue self);
bool LoxValue_equals(LoxValue self, LoxValue other);


#endif