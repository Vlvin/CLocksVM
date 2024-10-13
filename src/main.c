#include <oneFileSTD.h>
#include <chunk.h>
#include <debug.h>

int main() {
    Chunk chunk = Chunk_init();
    size_t constant = Chunk_addConstant(&chunk, 3.141596);
    Chunk_add(&chunk, OP_CONSTANT, 123);
    Chunk_add(&chunk, constant, 123);
    Chunk_add(&chunk, OP_RETURN, 123);
    disassembleChunk(&chunk, "main");
    Chunk_free(&chunk);
    return 0;
}