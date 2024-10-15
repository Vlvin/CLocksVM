#ifndef LINE_TRACKER_H
#define LINE_TRACKER_H
#include <oneFileSTD.h>

typedef struct LineTracker {
    size_t size, capacity;
    int* line;
    int* bytes_per_line;
} LineTracker;

typedef struct Chunk Chunk;


LineTracker LineTracker_init();
int LineTracker_free(LineTracker* self);
size_t LineTracker_write(LineTracker* self, int line);

/// @brief fun to get line of instruction in chunk at index
/// @param chunk parent of LineTracker
/// @param index instruction position
/// @return line where instruction came from
int LineTracker_getLine(Chunk* chunk, size_t index);

#endif