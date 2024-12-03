#include <loxToken.h>
#include <loxScanner.h>
#include <loxMemory.h>

LoxToken LoxToken_create(
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