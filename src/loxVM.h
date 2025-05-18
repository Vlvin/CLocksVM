#ifndef LOX_VIRTUAL_MACHINE_H
#define LOX_VIRTUAL_MACHINE_H

#include <loxChunk.h>
#include <loxHashMap.h>
#include <loxStack.h>
#include <oneFileSTD.h>

typedef struct LoxVM {
  LoxCallFrame frames[FRAMES_COUNT];
  size_t frameCount;
  LoxStack stack;
  LoxHashMap strings;
  LoxObject *objects;
  LoxHashMap globals;
} LoxVM;

extern LoxVM vm;

typedef enum LoxResult {
  LOX_INTERPRET_OK,
  LOX_INTERPRET_COMPILE_ERROR,
  LOX_INTERPRET_RUNTIME_ERROR,
} LoxResult;

void Lox_VM_printResult(LoxResult result);

void LoxVM_init(LoxVM *self);
void LoxVM_free(LoxVM *self);
void LoxVM_freeObjects(LoxVM *self);

LoxResult LoxVM_interpret(LoxVM *self, const char *source);
LoxResult _LoxVM_run(LoxVM *self);

#endif
