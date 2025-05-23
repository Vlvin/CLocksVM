#include <bitsTricks.h>
#include <debug.h>
#include <loxChunk.h>
#include <loxValueArray.h>
#include <stdint.h>

int disassembleChunk(Chunk *chunk, const char *name) {
  printf("== %s ==\n", name);
  for (int i = 0; i < chunk->size;) {
    i = disassembleInstruction(chunk, i, name);
  }
  return 0;
}

int disassembleInstruction(Chunk *chunk, size_t offset, const char *name) {
  printf("%04lu at %s:%d ", offset, name,
         LineTracker_getLine(chunk, 1 + offset));
  if (offset > 0 && LineTracker_getLine(chunk, 1 + offset) ==
                        LineTracker_getLine(chunk, 1 + offset - 1)) {
    printf("    | ");
  } else {
    printf("%4d ", LineTracker_getLine(chunk, offset));
  }
  uint8_t instruction = Chunk_data(chunk)[offset];
#define CASE_SIMPLE(INSTRUCTION)                                               \
  case INSTRUCTION:                                                            \
    return simpleInstruction(#INSTRUCTION, offset);

#define CASE_BYTE(INSTRUCTION)                                                 \
  case INSTRUCTION:                                                            \
    return byteInstruction(#INSTRUCTION, chunk, offset);

#define CASE_CONST(INSTRUCTION)                                                \
  case INSTRUCTION:                                                            \
    return constantInstruction(#INSTRUCTION, chunk, offset);

#define CASE_CONST_LONG(INSTRUCTION)                                           \
  case INSTRUCTION:                                                            \
    return constantLongInstruction(#INSTRUCTION, chunk, offset);

#define CASE_JMP(INSTRUCTION, SIGN)                                            \
  case INSTRUCTION:                                                            \
    return jumpInstruction(#INSTRUCTION, SIGN, chunk, offset);

  switch (instruction) {
    CASE_SIMPLE(OP_RETURN)
    break;
    CASE_SIMPLE(OP_NEGATE)
    break;
    CASE_SIMPLE(OP_ADD)
    break;
    CASE_SIMPLE(OP_SUBSTRACT)
    break;
    CASE_SIMPLE(OP_MULTIPLY)
    break;
    CASE_SIMPLE(OP_DIVIDE)
    break;
    CASE_SIMPLE(OP_NOT)
    break;
    CASE_SIMPLE(OP_AND)
    break;
    CASE_SIMPLE(OP_OR)
    break;
    CASE_SIMPLE(OP_TRUE)
    break;
    CASE_SIMPLE(OP_FALSE)
    break;
    CASE_SIMPLE(OP_NIL)
    break;
    CASE_SIMPLE(OP_EQUALS)
    break;
    CASE_SIMPLE(OP_GREATER)
    break;
    CASE_SIMPLE(OP_LESS)
    break;
    CASE_SIMPLE(OP_PRINT)
    break;
    CASE_SIMPLE(OP_POP)
    break;
    CASE_CONST(OP_CONSTANT)
    break;
    CASE_CONST(OP_DEFINE_GLOBAL)
    break;
    CASE_CONST(OP_GET_GLOBAL)
    break;
    CASE_CONST(OP_SET_GLOBAL)
    break;
    CASE_BYTE(OP_GET_LOCAL)
    break;
    CASE_BYTE(OP_SET_LOCAL)
    break;
    CASE_CONST_LONG(OP_CONSTANT_LONG)
    break;
    CASE_CONST_LONG(OP_DEFINE_GLOBAL_LONG)
    break;
    CASE_CONST_LONG(OP_GET_GLOBAL_LONG)
    break;
    CASE_CONST_LONG(OP_SET_GLOBAL_LONG)
    break;
    CASE_JMP(OP_JUMP_IF_FALSE, 1)
    break;
    CASE_JMP(OP_JUMP, 1)
    break;
    CASE_JMP(OP_LOOP, 0)
    break;
  }

#undef CASE_SIMPLE
#undef CASE_BYTE
#undef CASE_CONST
#undef CASE_CONST_LONG
  printf("Unknown instruction at %4lu\n", offset);
  return offset + 1;
}

int simpleInstruction(const char *instruction, size_t offset) {
  printf("%s\n", instruction);
  return offset + 1;
}

int byteInstruction(const char *instruction, Chunk *chunk, size_t offset) {
  uint8_t slot = chunk->code[offset + 1];
  printf("%-16s %4d\n", instruction, slot);
  return offset + 2;
}

int constantInstruction(const char *instruction, Chunk *chunk, size_t offset) {
  uint8_t index = chunk->code[offset + 1];
  LoxValue constant = ValueArray_data(&(chunk->constants))[index];
  printf("%-16s %4d '", instruction, index);
  printValue(constant);
  printf("'\n");

  return offset + 2;
}

int constantLongInstruction(const char *instruction, Chunk *chunk,
                            size_t offset) {
  uint16_t index = forge_uint16(
      (uint8_Pair){chunk->code[offset + 1], chunk->code[offset + 2]});
  LoxValue constant = ValueArray_data(&(chunk->constants))[index];
  printf("%-16s %4d '", instruction, index);
  printValue(constant);
  printf("'\n");

  return offset + 3;
}

int jumpInstruction(const char *instruction, int sign, Chunk *chunk,
                    size_t offset) {
  uint16_t jump = forge_uint16(
      (uint8_Pair){chunk->code[offset + 1], chunk->code[offset + 2]});
  printf("%-16s %4zu -> %zu\n", instruction, offset, offset + 3 + sign * jump);
  return offset + 3;
}
