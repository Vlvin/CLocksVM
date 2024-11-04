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
    // 4 - 3 * -2 without
    // OP_NEGATE
    Chunk_addConstant(&chunk, 4, 1);
    
    Chunk_addConstant(&chunk, 3, 1);

    Chunk_addConstant(&chunk, 0, 1);
    Chunk_addConstant(&chunk, 2, 1);
    Chunk_add(&chunk, OP_SUBSTRACT, 1); // 0 - 2 = -2

    Chunk_add(&chunk, OP_MULTIPLY, 1); // 3 * -2 = -6


    Chunk_add(&chunk, OP_SUBSTRACT, 1); // 4 - -6 = 10
    Chunk_add(&chunk, OP_RETURN, 2);



    LoxResult exitCode = LoxVM_interpret(&loxVM, &chunk);
    Lox_VM_printResult(exitCode);
    Chunk_free(&chunk);

    // OP_SUBSTRACT
    Chunk_addConstant(&chunk, 4, 1);

    Chunk_addConstant(&chunk, 3, 1);

    Chunk_addConstant(&chunk, 2, 1);
    Chunk_add(&chunk, OP_NEGATE, 1); // -2

    Chunk_add(&chunk, OP_MULTIPLY, 1); // 3 * -2 = -6

    Chunk_add(&chunk, OP_NEGATE, 1); // --6 = 6


    Chunk_add(&chunk, OP_ADD, 1); // 4 + 6 = 10
    Chunk_add(&chunk, OP_RETURN, 2);

    exitCode = LoxVM_interpret(&loxVM, &chunk);
    // disassembleChunk(&chunk, "main");

    Lox_VM_printResult(exitCode);
    Chunk_free(&chunk);
    LoxVM_free(&loxVM);
    return 0;
}