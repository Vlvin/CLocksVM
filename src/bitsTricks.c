#include <bitsTricks.h>



uint8_Pair split_uint16(uint16_t value) {
    uint8_Pair result = {
        0, 0
    };
    for (int i = 0; i < 8; i++) {
        result.first <<= 1;
        result.first += (value >> i)&1;
    }
    for (int i = 8; i < 16; i++) {
        result.second <<= 1;
        result.second += (value >> i)&1;
    }
    return result;
}

uint16_t forge_uint16(uint8_Pair pair) {
    return ((uint16_t)pair.first << 8) | pair.second;
}
