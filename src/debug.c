#include <debug.h>
#include <chunk.h>

int disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);
    for (int i = 0; i < chunk->size;) {
        i = disassembleInstruction(chunk, i);
    }
    return 0;
}
int disassembleInstruction(Chunk* chunk, size_t offset) {
    printf("%04lu ", offset);
    uint8_t instruction = Chunk_data(chunk)[offset];
    switch (instruction) {
        case RETURN:
            return simpleInstruction("RETURN", offset);
        break;
    }
    printf("Unknown instruction at %4lu\n", offset);
    return offset+1;
}

int simpleInstruction(const char* instruction, size_t offset) {
    printf("%s\n", instruction);
    return offset+1;
}