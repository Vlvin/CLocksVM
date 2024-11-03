#ifndef LOX_MEMORY_H
#define LOX_MEMORY_H

#include <oneFileSTD.h>

// this fun is here for debug purpose
void* reallocate(void* data, size_t oldSize, size_t newSize);

#define FREE_ARRAY(type, array, oldSize) \
    array = reallocate(array, oldSize*sizeof(type), 0)

#define GROW_ARRAY(type, array, oldSize) \
    array = reallocate(array, oldSize*sizeof(type), GROW_CAPACITY(oldSize)*sizeof(type))

#define GROW_CAPACITY(oldSize) \
    ((oldSize < 8) ? 8 : (oldSize*2))

#endif