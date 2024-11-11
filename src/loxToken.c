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
