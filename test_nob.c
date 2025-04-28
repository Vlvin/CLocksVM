
#define NOB_IMPLEMENTATION
#include "nob.h"

int main() {
  for (int i = 0; i < 10000; i++) {
    printf("%p\n", nob_temp_alloc(1000));
    nob_temp_reset();
  }
}
