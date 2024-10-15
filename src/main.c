#include <oneFileSTD.h>
#include <chunk.h>
#include <debug.h>
#include <lineTracker.h>

int main() {
    Chunk chunk = Chunk_init();
    size_t constant = Chunk_addConstant(&chunk, 3.141596);
    Chunk_add(&chunk, OP_CONSTANT, 3);
    Chunk_add(&chunk, constant, 2);
    Chunk_add(&chunk, OP_RETURN, 1);
    disassembleChunk(&chunk, "main");
    printf("%d\n", LineTracker_getLine(&chunk, 3));
    Chunk_free(&chunk);
    return 0;
}