#ifndef LOX_ERRORS_H
#define LOX_ERRORS_H
#include <loxVM.h>

typedef struct LoxParser LoxParser;
typedef struct LoxToken LoxToken;

void runtimeError(LoxVM *vm, const char *format, ...);

void errorAtCurrent(LoxParser *parser, const char *message);
void errorAt(LoxParser *parser, LoxToken *token, const char *message);

#endif
