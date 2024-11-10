#ifndef LOX_SCANNER_H
#define LOX_SCANNER_H

typedef enum LoxResult LoxResult;

LoxResult lox_Repl();
LoxResult lox_runFile(const char* filename);
char* readFile(const char* filename);

#endif