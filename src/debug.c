#include <debug.h>
#include <chunk.h>

static const char* TokenNames[] = {
    "ADD",
    "SUBSTRACT",
    "MULTIPLY",
    "DIVIDE",
    "LOOKUP_VARIABLE",
    "ASSIGN",
    "RETURN"
};

int disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);
    for (int i = 0; i < chunk->size;) {
        i = disassembleInstruction(chunk, i);
    }
}
int disassembleInstruction(Chunk* chunk, size_t offset) {
    printf("%04d ", offset);
    uint8_t instruction = chunk->code[offset];
    switch (instruction) {
        case RETURN:
            return simpleInstruction("RETURN", offset);
        break;
    }
    printf("Unknown instruction at %d\n", offset);
    return offset+1;
}

int simpleInstruction(const char* instruction, size_t offset) {
    printf("%s\n", instruction);
    return offset+1;
}