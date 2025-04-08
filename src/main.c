#include <bitsTricks.h>
#include <debug.h>
#include <loxCLI.h>
#include <loxChunk.h>
#include <loxScanner.h>
#include <loxVM.h>
#include <oneFileSTD.h>

int main(int argc, const char **argv) {
  switch (argc) {
  case 1:
    lox_Repl();
    break;
  case 2:
    return lox_runFile(argv[1]);
    break;
  default:
    fprintf(stderr, "Usage: %s [path]\n", argv[0]);
    break;
  }
  return 0;
}
