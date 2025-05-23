#ifndef DEBUG_H
#define DEBUG_H
#include <loxChunk.h>
#include <oneFileSTD.h>

int disassembleChunk(Chunk *chunk, const char *name);
int disassembleInstruction(Chunk *chunk, size_t offset, const char *name);

int byteInstruction(const char *instruction, Chunk *chunk, size_t offset);
int simpleInstruction(const char *instruction, size_t offset);
int constantInstruction(const char *instruction, Chunk *chunk, size_t offset);
int constantLongInstruction(const char *instruction, Chunk *chunk,
                            size_t offset);
int jumpInstruction(const char *instruction, int sign, Chunk *chunk,
                    size_t offset);

#endif
