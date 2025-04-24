#ifndef BITS_TRICKS_H
#define BITS_TRICKS_H

#include <oneFileSTD.h>

typedef struct {
  uint8_t first, second;
} uint8_Pair;

uint8_Pair split_uint16(uint16_t value);
uint16_t forge_uint16(uint8_Pair pair);

#endif
