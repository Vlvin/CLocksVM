#include "loxObject.h"
#include <loxMemory.h>
#include <loxScanner.h>
#include <loxToken.h>
#include <loxVM.h>
#include <loxValue.h>

LoxToken LoxToken_create(TokenType type, size_t line, const char *start,
                         size_t size) {
  return (LoxToken){type, line, start, size};
}

LoxValue LoxToken_toString(LoxToken self) {
  return LOX_OBJECT_VAL(copyString(&vm, self.start, self.size));
}
