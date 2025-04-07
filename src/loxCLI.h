#ifndef LOX_CLI_H
#define LOX_CLI_H

typedef enum LoxResult LoxResult;

LoxResult lox_Repl();
LoxResult lox_runFile(const char* filename);
char* readFile(const char* filename);

#endif