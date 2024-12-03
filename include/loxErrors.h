#ifndef LOX_ERRORS_H
#define LOX_ERRORS_H

typedef struct LoxParser LoxParser;
typedef struct LoxToken LoxToken;

void errorAtCurrent(LoxParser* parser, const char *message);
void errorAt(LoxParser* parser, LoxToken* token, const char *message);

#endif