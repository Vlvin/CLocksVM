#include <debug.h>
#include <chunk.h>
#include <value.h>

int disassembleChunk(Chunk* chunk, const char* name) {
    printf("== %s ==\n", name);
    for (int i = 0; i < chunk->size;) {
        i = disassembleInstruction(chunk, i);
    }
    return 0;
}

int disassembleInstruction(Chunk* chunk, size_t offset) {
    printf("%04lu ", offset);
    if (
        offset > 0 &&
        chunk->lines[offset] == chunk->lines[offset-1]
    ) {
        printf("    | ");
    } else {
        printf("%4d ", chunk->lines[offset]);
    }
    uint8_t instruction = Chunk_data(chunk)[offset];
    switch (instruction) {
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
            break;
        case OP_CONSTANT: 
            return constantInstruction("OP_CONSTANT", chunk, offset);
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