#include <loxErrors.h>
#include <loxParser.h>
#include <loxToken.h>

void errorAtCurrent(LoxParser* parser, const char *message) {
  return errorAt(parser, &parser->previous, message);
}


void errorAt(LoxParser* parser, LoxToken* token, const char *message) {
  fprintf(stderr, "Error in %s at line %d", "module", token->line);

  if (token->type == TOKEN_EOF) {
    fprintf(stderr, " at end");
  } else if (token->type == TOKEN_ERROR) {
    // do nothing
  } else {
    fprintf(stderr, " at '%.*s'", token->size, token->start);
  }

  fprintf(stderr, " : %s\n", message);
  parser->hadError = true;
}
