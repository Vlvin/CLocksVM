
#include <loxScanner.h>
#include <loxParser.h>


inline static void LoxParser_advance(LoxParser* self, LoxScanner *scanner) {
  self->previous = self->current;

  while (true) {
    self->current = LoxScanner_scanToken(scanner);

    if (self->current.type != TOKEN_ERROR) break;

    errorAtCurrent(self->current.start);
  }

  
}
int LoxParser_expression(LoxParser* self, LoxScanner *scanner) {
  LoxParser_parsePrecedance(self, scanner, PREC_ASSIGNMENT);
}
int LoxParser_consume(LoxParser* self, LoxScanner *scanner, TokenType type, const char* error_message) {

}
