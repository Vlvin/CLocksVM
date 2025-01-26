#include <oneFileSTD.h>
#include <debug.h>
#include <bitsTricks.h>
#include <loxChunk.h>
#include <loxVM.h>
#include <loxCLI.h>
#include <loxScanner.h>


int main(int argc, const char** argv) {
    switch (argc) {
        case 1:
            Lox_VM_printResult(lox_Repl());
            break;
        case 2:
            Lox_VM_printResult(lox_runFile(argv[1]));
            break;
        default:
            fprintf(stderr, "Usage: %s [path]\n", argv[0]);
            break;
    }
    return 0;

}
