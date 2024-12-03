#include <loxMemory.h>

void *reallocate(void* data, size_t oldSize, size_t newSize) {
    if (data == NULL)
        return (void*)NULL;
    if (newSize == 0) {
        free(data);
        return (void*)NULL;
    }
    void* result = realloc(data, newSize);
    return result;
}