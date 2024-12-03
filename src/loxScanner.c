#include <loxScanner.h>
#include <oneFileSTD.h>
#include <loxToken.h>


// helpers
static inline bool isAlpha(const char ch) {
    return (
        (
            'a' <= ch &&
            'z' >= ch
        ) || (
            'A' <= ch &&
            'Z' >= ch
        ) || (
            '_' == ch
        )
    );
}
static inline bool isDigit(const char ch) {
    return (
        '0' <= ch &&
        '9' >= ch
    );
}
static inline bool isAlphaNumeric(const char ch) {
    return ( isAlpha(ch) || isDigit(ch) );
}

LoxScanner LoxScanner_init(const char* source) {
    return (LoxScanner){
        source,
        source,
        1
    };
}

LoxToken LoxScanner_scanToken(LoxScanner* self) {
    LoxScanner_skipWhiteSpaces(self);
    self->start = self->current;
    if (LoxScanner_isAtEnd(self)) {
        return LoxScanner_makeToken(self, TOKEN_EOF);
    }

    char c = LoxScanner_advance(self);

    switch (c) {
        case '{':
            return LoxScanner_makeToken(self, TOKEN_LEFT_BRACE);
        case '}':
            return LoxScanner_makeToken(self, TOKEN_RIGHT_BRACE);
        case '(':
            return LoxScanner_makeToken(self, TOKEN_LEFT_PAREN);
        case ')':
            return LoxScanner_makeToken(self, TOKEN_RIGHT_PAREN);
        case ';':
            return LoxScanner_makeToken(self, TOKEN_SEMICOLON);
        case '.':
            return LoxScanner_makeToken(self, TOKEN_DOT);
        case ',':
            return LoxScanner_makeToken(self, TOKEN_COMMA);
        case '-':
            return LoxScanner_makeToken(self, TOKEN_MINUS);
        case '+':
            return LoxScanner_makeToken(self, TOKEN_PLUS);
        case '*':
            return LoxScanner_makeToken(self, TOKEN_STAR);
        case '!':
            return LoxScanner_makeToken(self, 
                LoxScanner_match(self, '=') ? TOKEN_BANG_EQUAL : TOKEN_BANG
            );
        case '=':
            return LoxScanner_makeToken(self, 
                LoxScanner_match(self, '=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL
            );
        case '<':
            return LoxScanner_makeToken(self, 
                LoxScanner_match(self, '=') ? TOKEN_LESS_EQUAL : TOKEN_EQUAL
            );
        case '>':
            return LoxScanner_makeToken(self, 
                LoxScanner_match(self, '=') ? TOKEN_GREATER_EQUAL : TOKEN_EQUAL
            );
        case '/':
            return LoxScanner_makeToken(self, TOKEN_SLASH);
        case '\'':
        case '"':
            return LoxScanner_string(self);
    }

    if (isDigit(c)) 
        return LoxScanner_number(self);
    if (isAlpha(c)) 
        return LoxScanner_identifier(self);

    return LoxScanner_errorToken(self, "Unexpected character\n");
}




bool LoxScanner_match(LoxScanner* self, const char expected) {
    if (LoxScanner_isAtEnd(self) || *(self->current) != expected) 
        return false;

    self->current++;
    return true;
}

bool LoxScanner_isAtEnd(LoxScanner* self) {
    return (*(self->current) == '\0');
}

char LoxScanner_advance(LoxScanner* self) {
    return (*(self->current++));
}

char LoxScanner_peek(LoxScanner* self) {
    return (*(self->current));
}

char LoxScanner_peekNext(LoxScanner* self) {
    if (LoxScanner_isAtEnd(self))
        return '\0';
    return (*(self->current+1));
}

void LoxScanner_skipWhiteSpaces(LoxScanner* self) {
    while (true) {
        char c = LoxScanner_peek(self);

        switch (c) {
            case '/':
                if (LoxScanner_peekNext(self) == '/') {
                    while (LoxScanner_peek(self) != '\n' && !LoxScanner_isAtEnd(self))
                        LoxScanner_advance(self);
                } else 
                    return;
                break;
            case ' ':
            case '\r':
            case '\t':
                LoxScanner_advance(self);
                break;
            case '\n':
                self->line++;
                LoxScanner_advance(self);
                break;
                break;
            default:
                return;
        }
    }
}


LoxToken LoxScanner_stringInterpolation(LoxScanner* self) {
    while (LoxScanner_peek(self) != '}' && !LoxScanner_isAtEnd(self)) {
        if (LoxScanner_peek(self) == '\n') 
            self->line++;
        LoxScanner_advance(self);
    }
}

LoxToken LoxScanner_string(LoxScanner* self) {
    while (LoxScanner_peek(self) != '"' && !LoxScanner_isAtEnd(self)) {
        if (LoxScanner_peek(self) == '\n') 
            self->line++;
        LoxScanner_advance(self);
    }

    if (LoxScanner_isAtEnd(self))
        return LoxScanner_errorToken(self, "Unterminated string");

    LoxScanner_advance(self);
    return LoxScanner_makeToken(self, TOKEN_STRING);
}

LoxToken LoxScanner_number(LoxScanner* self) {
    while (isDigit(LoxScanner_peek(self)))
        LoxScanner_advance(self);
    if (LoxScanner_peek(self) == '.' && isDigit(LoxScanner_peekNext(self))) {
        LoxScanner_advance(self);
        while (isDigit(LoxScanner_peek(self)))
            LoxScanner_advance(self);
    }
    return LoxScanner_makeToken(self, TOKEN_NUMBER);
}

LoxToken LoxScanner_identifier(LoxScanner* self) {
    while (isAlphaNumeric(LoxScanner_peek(self)))
        LoxScanner_advance(self);
    return LoxScanner_makeToken(self, LoxScanner_identifierType(self));
}

LoxToken LoxScanner_makeToken(LoxScanner *self, TokenType type) {
    return LoxToken_init(
        type,
        self->line,
        self->start,
        (size_t)(self->current - self->start)
    );  
}

LoxToken LoxScanner_errorToken(LoxScanner *self, const char* message) {
    return LoxToken_init(
        TOKEN_ERROR,
        self->line,
        message,
        strlen(message)
    );    
}

TokenType checkKeyword(LoxScanner* self, int offset, const char* rest, TokenType type) {
    (memcmp(rest, self->start+offset, strlen(rest)) == 0) ? type : TOKEN_IDENTIFIER;
}

TokenType LoxScanner_identifierType(LoxScanner* self) {
    switch (self->start[0]) {
        case 'a': return checkKeyword(self, 1, "nd", TOKEN_AND);
        case 'c': return checkKeyword(self, 1, "lass", TOKEN_CLASS);
        case 'e': return checkKeyword(self, 1, "lse", TOKEN_ELSE);
        case 'i': return checkKeyword(self, 1, "f", TOKEN_IF);
        case 'n': return checkKeyword(self, 1, "il", TOKEN_NIL);
        case 'o': return checkKeyword(self, 1, "r", TOKEN_OR);
        case 'p': return checkKeyword(self, 1, "rint", TOKEN_PRINT);
        case 'r': return checkKeyword(self, 1, "eturn", TOKEN_RETURN);
        case 's': return checkKeyword(self, 1, "uper", TOKEN_SUPER);
        case 'v': return checkKeyword(self, 1, "ar", TOKEN_VAR);
        case 'w': return checkKeyword(self, 1, "hile", TOKEN_WHILE);
        case 'f': 
            if (self->current - self->start > 1)
                switch (self->start[0]) {
                    case 'a': return checkKeyword(self, 2, "lse", TOKEN_FALSE);
                    case 'o': return checkKeyword(self, 2, "r", TOKEN_FOR);
                    case 'u': return checkKeyword(self, 2, "n", TOKEN_FUN);
                }
            break;
        case 't': 
            if (self->current - self->start > 1)
                switch (self->start[0]) {
                    case 'r': return checkKeyword(self, 2, "ue", TOKEN_TRUE);
                    case 'h': return checkKeyword(self, 2, "is", TOKEN_THIS);
                }
            break;
    }
    return TOKEN_IDENTIFIER;
}


void LoxScanner_free(LoxScanner* self) {
}