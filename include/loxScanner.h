#ifndef LOX_SCANNER_H
#define LOX_SCANNER_H

#include <oneFileSTD.h>
#include <loxToken.h>

typedef struct LoxScanner {
    const char* start, *current;
    size_t line;
} LoxScanner;

LoxScanner LoxScanner_init(const char* source);
LoxToken LoxScanner_scanToken(LoxScanner* self);
bool LoxScanner_isAtEnd(LoxScanner* self);
char LoxScanner_advance(LoxScanner* self);
void LoxScanner_free(LoxScanner* self);

#endif