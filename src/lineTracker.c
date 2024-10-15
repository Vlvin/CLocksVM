#include <lineTracker.h>
#include <loxMemory.h>
#include <chunk.h>

LineTracker LineTracker_init() {
    LineTracker ret = {
        0, 0, NULL, NULL
    };
    return ret;
}

int LineTracker_free(LineTracker* self) {
    FREE_ARRAY(int, self->line, self->capacity);
    FREE_ARRAY(int, self->bytes_per_line, self->capacity);
    (*self) = LineTracker_init();
    return 0;
}



size_t LineTracker_write(LineTracker* self, int line) {
    if (self->size == 0 || self->line[self->size-1] != line) {
        if (self->size == self->capacity) {
            GROW_ARRAY(int, self->line, self->capacity);
            GROW_ARRAY(int, self->bytes_per_line, self->capacity);
            self->capacity = GROW_CAPACITY(self->capacity);
            if (NULL == self->line || NULL == self->bytes_per_line)
                exit(1);
        }
        self->size++;
        self->line[self->size-1] = line;
    }
    self->bytes_per_line[self->size-1]++;
    return 0;
}


int LineTracker_getLine(Chunk* chunk, size_t byte) {
    if (chunk->tracker.size == 0)
        return -1;
    size_t index = 0; 
    size_t iter = 0;
    while (iter < chunk->tracker.size && index < byte) {
        index += chunk->tracker.bytes_per_line[iter];
        iter++;
    }
    if (index >= byte)
        return chunk->tracker.line[iter-1];
    return -1;
}
