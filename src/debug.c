#include <debug.h>
#include <chunk.h>
#include <value.h>
#include <lineTracker.h>
#include <bitsTricks.h>

int disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);
    for (int i = 0; i < chunk->size;) {
        i = disassembleInstruction(chunk, i, name);
    }
    return 0;
}

int disassembleInstruction(Chunk* chunk, size_t offset, const char* name) {
    printf("%04lu at %s:%d ", offset, name, LineTracker_getLine(chunk, 1+offset));
    if (
        offset > 0 &&
        LineTracker_getLine(chunk, 1+offset) == LineTracker_getLine(chunk, 1+offset-1)
    ) {
        printf("    | ");
    } else {
        printf("%4d ", LineTracker_getLine(chunk, offset));
    }
    uint8_t instruction = Chunk_data(chunk)[offset];
    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
            break;
        case OP_CONSTANT: 
            return constantInstruction("OP_CONSTANT", chunk, offset);
            break;
        case OP_CONSTANT_LONG: 
            return constantLongInstruction("OP_CONSTANT_LONG", chunk, offset);
            break;
    }
    printf("Unknown instruction at %4lu\n", offset);
    return offset+1;
}


int simpleInstruction(const char* instruction, size_t offset) {
    printf("%s\n", instruction);
    return offset+1;
}

int constantInstruction(const char* instruction, Chunk* chunk, size_t offset) {
    uint8_t index = chunk->code[offset+1];
    Value constant = ValueArray_data(&(chunk->constants))[index];
    printf("%-16s %4d '", instruction, index);
    printValue(constant);
    printf("'\n");

    return offset+2;
}

int constantLongInstruction(const char* instruction, Chunk* chunk, size_t offset) {
    uint16_t index = forge_uint16((uint8_Pair){chunk->code[offset+1], chunk->code[offset+2]});
    Value constant = ValueArray_data(&(chunk->constants))[index];
    printf("%-16s %4d '", instruction, index);
    printValue(constant);
    printf("'\n");

    return offset+3;
}