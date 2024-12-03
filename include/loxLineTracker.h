#ifndef LOX_LINE_TRACKER_H
#define LOX_LINE_TRACKER_H
#include <oneFileSTD.h>

typedef struct LoxLineTracker {
    size_t size, capacity;
    int* line;
    int* bytes_per_line;
} LoxLineTracker;

typedef struct Chunk Chunk;


void LineTracker_init(LoxLineTracker* self);
int LineTracker_free(LoxLineTracker* self);
size_t LineTracker_write(LoxLineTracker* self, int line);

/// @brief fun to get line of instruction in chunk at index
/// @param chunk parent of LoxLineTracker
/// @param index instruction position
/// @return line where instruction came from
int LineTracker_getLine(Chunk* chunk, size_t index);

#endif