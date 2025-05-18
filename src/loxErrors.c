#include <loxErrors.h>
#include <loxParser.h>
#include <loxToken.h>
#include <loxVM.h>
#include <oneFileSTD.h>

void runtimeError(LoxVM *vm, const char *format, ...) {
  va_list args;
  va_start(args, format);
  fprintf(stderr, format, args);
  va_end(args);
  fputc('\n', stderr);

  LoxCallFrame *frame = &vm->frames[vm->frameCount - 1];

  size_t instruction = frame->instruction - frame->function->chunk.code - 1;
  int line = LineTracker_getLine(&frame->function->chunk, instruction);
  fprintf(stderr, "in %s at line %d\n", "module", line);
  LoxStack_reset(&vm->stack);
}

void errorAtCurrent(LoxParser *parser, const char *message) {
  return errorAt(parser, &parser->previous, message);
}

void errorAt(LoxParser *parser, LoxToken *token, const char *message) {
  fprintf(stderr, "Error in %s at line %lu", "module", token->line);

  if (token->type == TOKEN_EOF) {
    fprintf(stderr, " at end");
  } else if (token->type == TOKEN_ERROR) {
    // do nothing
  } else {
    fprintf(stderr, " at '%.*s'", (int)(token->size), token->start);
  }

  fprintf(stderr, " : %s\n", message);
  parser->hadError = true;
}
