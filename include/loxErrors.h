#ifndef LOX_ERRORS_H
#define LOX_ERRORS_H

typedef struct LoxParser LoxParser;
typedef struct LoxToken LoxToken;

inline static void errorAtCurrent(LoxParser* parser, const char *message);
inline static void errorAt(LoxParser* parser, LoxToken* token, const char *message);

#endif