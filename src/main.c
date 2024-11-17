#include <oneFileSTD.h>
#include <debug.h>
#include <bitsTricks.h>
#include <loxChunk.h>
#include <loxVM.h>
#include <loxCLI.h>
#include <loxScanner.h>


int main(int argc, const char** argv) {
    // switch (argc) {
    //     case 1:
    //         lox_Repl();
    //         break;
    //     case 2:
    //         lox_runFile(argv[1]);
    //         break;
    //     default:
    //         fprintf(stderr, "Usage: %s [path]\n", argv[0]);
    //         break;
    // }
    // return 0;
    LoxVM vm = LoxVM_init();

    Chunk chunk = Chunk_init();

    Chunk_addConstant(&chunk, 12, 1);
    for (size_t i = 1; i<102400; i++)
        Chunk_add(&chunk, OP_NOT, 1);

    vm.chunk = &chunk;

    LoxResult result = _LoxVM_run(&vm, &chunk);


    Lox_VM_printResult(result);
    Chunk_free(&chunk);
    LoxVM_free(&vm);


}