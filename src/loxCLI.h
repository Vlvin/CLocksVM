#ifndef LOX_CLI_H
#define LOX_CLI_H

#include <loxVM.h>

void lox_Repl();
LoxResult lox_runFile(const char *filename);
char *readFile(const char *filename);

#endif
