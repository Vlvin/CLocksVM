#include <loxCompiler.h>
#include <loxScanner.h>
#include <loxToken.h>

int loxCompiler_compile(const char* source) {
    LoxScanner scanner = LoxScanner_init(source);
    size_t line = -1;

    while (true) {
        LoxToken token = LoxScanner_scanToken(&scanner);
        if (token.line != line) {
            printf("%4d ", token.line);
            line = token.line;
        } else {
            printf("   | ");
        }

        printf("%2d %.*s", token.type, token.size, token.start);

        if (token.type == TOKEN_EOF)
            break;
    }


    LoxScanner_free(&scanner);
    return 0;

}