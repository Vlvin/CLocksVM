#include <loxMemory.h>

void *reallocate(void* data, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(data);
        return (void*)NULL;
    }
    void* result = realloc(data, newSize);
    return result;
}