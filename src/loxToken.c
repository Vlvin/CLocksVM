#include <loxToken.h>
#include <loxScanner.h>

LoxToken LoxToken_init(
    TokenType type, 
    size_t line, 
    const char* start,
    size_t size
) {
    return (LoxToken) {
        type,
        line,
        start,
        size
    };
}


LoxToken LoxToken_make(LoxScanner *scanner, TokenType type) {
    return LoxToken_init(
        type,
        scanner->line,
        scanner->start,
        (size_t)(scanner->current - scanner->start)
    );  
}

LoxToken LoxToken_errorToken(LoxScanner *scanner, const char* message) {
    return LoxToken_init(
        TOKEN_ERROR,
        scanner->line,
        message,
        strlen(message)
    );    
}