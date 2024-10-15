#include <oneFileSTD.h>
#include <chunk.h>
#include <debug.h>
#include <lineTracker.h>

int main() {
    Chunk chunk = Chunk_init();
    size_t constant = Chunk_addConstant(&chunk, 3.141596, 1);
    Chunk_add(&chunk, OP_RETURN, 2);
    disassembleChunk(&chunk, "main");
    Chunk_free(&chunk);
    return 0;
}