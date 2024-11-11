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


        (token.type == TOKEN_EOF) ?
            printf("%2d \n", token.type) : // EOF is invisible for human eye
            printf("%2d '%.*s'\n", token.type, token.size, token.start);

        if (token.type == TOKEN_EOF)
            break;
    }


    LoxScanner_free(&scanner);
    return 0;

}