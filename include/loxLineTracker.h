#ifndef LOX_LINE_TRACKER_H
#define LOX_LINE_TRACKER_H
#include <oneFileSTD.h>

typedef struct loxLineTracker {
    size_t size, capacity;
    int* line;
    int* bytes_per_line;
} loxLineTracker;

typedef struct Chunk Chunk;


loxLineTracker LineTracker_init();
int LineTracker_free(loxLineTracker* self);
size_t LineTracker_write(loxLineTracker* self, int line);

/// @brief fun to get line of instruction in chunk at index
/// @param chunk parent of loxLineTracker
/// @param index instruction position
/// @return line where instruction came from
int LineTracker_getLine(Chunk* chunk, size_t index);

#endif