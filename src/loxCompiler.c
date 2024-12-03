#include <loxCompiler.h>
#include <loxToken.h>
#include <bitsTricks.h>
#include <stdarg.h>




inline static LoxCompiler LoxCompiler_init() {
    LoxCompiler self;
    self.parser = (LoxParser){ 0 };
    return self;
}

inline static bool LoxCompiler_compile(LoxCompiler *self, const char* source, Chunk *chunk) {
    self->scanner = LoxScanner_init(source);
    self->compilingChunk = chunk;

    LoxParser_advance(&self->parser, &self->scanner);
    LoxParser_expression(&self->parser, &self->scanner);
    LoxParser_consume(&self->parser, &self->scanner, TOKEN_EOF, "Expect end of expression");


    LoxScanner_free(&self->scanner);
    return !self->parser.hadError;
}



inline static Chunk* currentToken(LoxCompiler* self) {
    return &self->compilingChunk;
}

inline static void LoxCompiler_end(LoxCompiler* self) {
    _LoxCompiler_emitReturn(self);
}


inline static void LoxCompiler_free(LoxCompiler* self) {
    (*self) = (LoxCompiler){ 0 };
}


inline static void LoxCompiler_number(LoxCompiler* self) {
    double value = strtod(self->parser.previous.start, NULL);
    _LoxCompiler_emitConstant(self, value);
}


inline static void LoxCompiler_grouping(LoxCompiler* self) {
    LoxParser_expression(&self->parser, &self->scanner);
    LoxParser_consume(&self->parser, &self->scanner, TOKEN_RIGHT_PAREN, "Expect ')' after expression");
}
inline static void LoxCompiler_unary(LoxCompiler* self) {
    TokenType operator = self->parser.previous.type;

    _LoxCompiler_parsePrecedence(&self->parser, &self->scanner);

    switch (operator)
    {
    case TOKEN_MINUS:
        _LoxCompiler_emitByte(self, OP_NEGATE);
        break;
    case TOKEN_BANG:
        _LoxCompiler_emitByte(self, OP_NOT);
        break;
        default: return;
    }
}


inline static void LoxCompiler_binary(LoxCompiler* self) {
    TokenType operator = self->parser.previous.type;
    LoxParseRule rule = LoxCompiler_getRule(operator);
    _LoxCompiler_parsePrecedence(self, (LoxPrecedence)(rule.precedence+1));


    switch(operator) {
        case TOKEN_PLUS:
            _LoxCompiler_emitByte(self, OP_ADD);
            break;
        case TOKEN_MINUS:
            _LoxCompiler_emitByte(self, OP_SUBSTRACT);
            break;
        case TOKEN_STAR:
            _LoxCompiler_emitByte(self, OP_MULTIPLY);
            break;
        case TOKEN_SLASH:
            _LoxCompiler_emitByte(self, OP_DIVIDE);
            break;
    }
}

inline static size_t LoxCompiler_makeConstant(LoxCompiler* self, Value value) {
    return Chunk_addConstant(self->compilingChunk, value);
}


inline static void _LoxCompiler_emitByte(LoxCompiler* self, uint8_t byte) {
    Chunk_add(currentToken(self), byte, self->parser.previous.line);
}


inline static void _LoxCompiler_emitBytes(LoxCompiler* self, int count, ...) {
    va_list args;
    va_start(args, count);
        while (count-- > 0)
            _LoxCompiler_emitByte(self, va_arg(args, uint8_t));
    va_end(args);
}


inline static void _LoxCompiler_emitReturn(LoxCompiler* self) {
    _LoxCompiler_emitByte(self, OP_RETURN);
}

inline static void _LoxCompiler_emitConstant(LoxCompiler* self, Value value) {
    size_t constLocation = makeConstant(value);    
    size_t line = self->parser.previous.line;
    if (constLocation > 255) {
        uint8_Pair operands = split_uint16(constLocation);
        _LoxCompiler_emitBytes(self, 3, OP_CONSTANT_LONG, operands.first, operands.second);
    } else {
        _LoxCompiler_emitBytes(self, 2, OP_CONSTANT, (uint8_t)constLocation);
    }
}


inline static void _LoxCompiler_parsePrecedence(LoxCompiler* self, LoxPrecedence precedence) {

}