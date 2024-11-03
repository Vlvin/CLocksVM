#include <oneFileSTD.h>
#include <loxChunk.h>
#include <debug.h>
#include <bitsTricks.h>
#include <lineTracker.h>
#include <loxVM.h>


int main() {
    // our Virtual Machine
    LoxVM loxVM = LoxVM_init();
    // current chunc of code
    Chunk chunk = Chunk_init();
    Chunk_addConstant(&chunk, 3.141596, 1);
    Chunk_add(&chunk, OP_RETURN, 2);

    LoxResult exitCode = LoxVM_interpret(&loxVM, &chunk);
    // disassembleChunk(&chunk, "main");

    Lox_VM_printResult(exitCode);
    Chunk_free(&chunk);
    LoxVM_free(&loxVM);
    return 0;
}