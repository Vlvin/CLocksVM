#include <loxMemory.h>
#include <loxChunk.h>

void LineTracker_init(LoxLineTracker* self) {
    (*self) = (LoxLineTracker){0};
}

int LineTracker_free(LoxLineTracker* self) {
    FREE_ARRAY(int, self->line, self->capacity);
    FREE_ARRAY(int, self->bytes_per_line, self->capacity);
    LineTracker_init(self);
    return 0;
}



size_t LineTracker_write(LoxLineTracker* self, int line) {
    if (self->size == 0 || self->line[self->size-1] != line) {
        if (self->size == self->capacity) {
            GROW_ARRAY(int, self->line, self->capacity);
            GROW_ARRAY(int, self->bytes_per_line, self->capacity);
            self->capacity = GROW_CAPACITY(self->capacity);
            if (NULL == self->line || NULL == self->bytes_per_line) {
                exit(1);
            }
        }
        self->size++;
    }
    self->line[self->size-1] = line;
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
