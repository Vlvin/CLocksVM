#include <oneFileSTD.h>
#include <chunk.h>
#include <debug.h>

int main() {
    Chunk chunk = Chunk_init();
    Chunk_add(&chunk, RETURN);
    disassembleChunk(&chunk, "main");
    Chunk_free(&chunk);
    return 0;
}