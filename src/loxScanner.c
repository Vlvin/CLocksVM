#include <loxScanner.h>
#include <oneFileSTD.h>
#include <loxToken.h>

LoxScanner LoxScanner_init(const char* source) {
    return (LoxScanner){
        source,
        source,
        1
    };
}

LoxToken LoxScanner_scanToken(LoxScanner* self) {
    self->start = self->current;
    if (LoxScanner_isAtEnd(self)) {
        return LoxToken_make(self, TOKEN_EOF);
    }

    return LoxToken_errorToken(self, "Unexpected character\n");
}


bool LoxScanner_isAtEnd(LoxScanner* self) {
    return (*(self->current) != '\0');
}

char LoxScanner_advance(LoxScanner* self) {
}

void LoxScanner_free(LoxScanner* self) {

}