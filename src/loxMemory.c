#include <loxMemory.h>

void *reallocate(void* data, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(data);
        /*printf("%p deallocated\n", data);*/
        return (void*)NULL;
    }
    void* result = realloc(data, newSize);
    /*if (data != NULL) {*/
    /*    printf("%p reallocated to %p", data, result);*/
    /*} else */
    /*    printf("%p allocated\n", result);*/
    return result;
}
