// This is your build script. You only need to "bootstrap" it once with `cc -o
// nob nob.c` (you can call it whatever actually) or `cl nob.c` on MSVC and
// thanks to NOB_GO_REBUILD_URSELF (see below). After that every time you run
// the `nob` executable if it detects that you modifed nob.c it will rebuild
// itself automatically

// nob.h is an stb-style library
// https://github.com/nothings/stb/blob/master/docs/stb_howto.txt What that
// means is that it's a single file that acts both like .c and .h files, but by
// default when you include it, it acts only as .h. To make it include
// implementations of the functions you must define NOB_IMPLEMENTATION macro.
// This is done to give you full control over where the implementations go.
#include <string.h>
#define NOB_IMPLEMENTATION

// Always keep a copy of nob.h in your repo. One of my main pet peeves with
// build systems like CMake and Autotools is that the codebases that use them
// naturally rot. That is if you do not actively update your build scripts, they
// may not work with the latest version of the build tools. Here we basically
// include the entirety of the source code of the tool along with the code base.
// It will never get outdated.
//
// (In these examples we actually symlinking nob.h, but this is to keep nob.h-s
// synced among all the examples)
#include "nob.h"

// TODO: add more comments in here

///// Memory tracking ///////////////////////////////////////////////////////
typedef struct LinkedList LinkedList;
struct LinkedList {
  void *element;
  LinkedList *next;
};
LinkedList initial = {0};
LinkedList *allocated = &initial;

#define ALLOCATE(size)                                                         \
  do {                                                                         \
    LinkedList *node = (LinkedList *)malloc(sizeof(LinkedList));               \
    node->next = allocated;                                                    \
    node->element = (void *)malloc(size);                                      \
    allocated = node;                                                          \
  } while (0)

#define FREE()                                                                 \
  do {                                                                         \
    if (allocated == NULL)                                                     \
      break;                                                                   \
    LinkedList *cur = allocated;                                               \
    LinkedList *next = allocated;                                              \
    while (cur->next != NULL) {                                                \
      next = cur->next;                                                        \
      if (cur->element != NULL)                                                \
        free(cur->element);                                                    \
      free(cur);                                                               \
      cur = next;                                                              \
    }                                                                          \
  } while (0)

void *allocate(uint size) {
  ALLOCATE(size);
  return allocated->element;
}

///// Memory tracking end ////////////////////////////////////////////////////

///// String collection ////////////////////////////////////////////////////
#define ENDS_WITH(str, postfix)                                                \
  (strlen(str) >= strlen(postfix) &&                                           \
   strcmp((str) + strlen(str) - strlen(postfix), (postfix)) == 0)

int find_last(const char *const hay, char needle) {
  for (int i = strlen(hay); i > -1; i--) {
    if (hay[i] == needle)
      return i;
  }
  return -1;
}

///// String collection end ////////////////////////////////////////////////////

#define PROJECT_NAME "CLocksCompiler"

#define BUILD_FOLDER "build/"
#define SRC_FOLDER "src/"
#define LIB_FOLDER BUILD_FOLDER "lib/"
#define SRC_LIB_FOLDER LIB_FOLDER "src/"
#define CFLAGS "-Wall", "-I" SRC_FOLDER
#define DEBUG_FLAGS "-O0", "-ggdb", "-DDEBUG_PRINT_CODE", "-DDEBUG_TRACE"
#define RELEASE_FLAGS "-O3"
#define TESTS_SRC_FOLDER "tests/"
#define TESTS_FOLDER "build/tests/"

int build_release_library(Nob_Cmd *cmd) {
  const char *lib_path = SRC_LIB_FOLDER "release/";
  if (!(nob_mkdir_if_not_exists(BUILD_FOLDER) &&
        nob_mkdir_if_not_exists(LIB_FOLDER) &&
        nob_mkdir_if_not_exists(SRC_LIB_FOLDER) &&
        nob_mkdir_if_not_exists(lib_path)))
    return 1;
  cmd->count = 0;
  // Objects

  Nob_File_Paths children = {0};
  nob_read_entire_dir(SRC_FOLDER, &children);

  char filepath[64] = {0};
  int srclen = strlen(SRC_FOLDER);
  char objectpath[64] = {0};
  int srcliblen = strlen(lib_path);

  bool all_objects_compiled = true;

  for (uint i = 0; i < children.count; i++) {
    cmd->count = 0;
    strcpy(filepath, SRC_FOLDER);
    strcpy(objectpath, lib_path);
    nob_cmd_append(cmd, "cc", CFLAGS, RELEASE_FLAGS);
    strcpy(filepath + srclen, children.items[i]);
    Nob_File_Type type = nob_get_file_type(filepath);

    if (type != NOB_FILE_REGULAR || !ENDS_WITH(filepath, ".c") ||
        ENDS_WITH(filepath, "main.c"))
      continue;

    int fn_size = strlen(filepath) - srclen - 2;
    strncat(objectpath, filepath + srclen, fn_size);
    strcat(objectpath, ".o");

    nob_log(NOB_INFO, "compiling %s to %s", filepath, objectpath);
    nob_cmd_append(cmd, "-c", filepath, "-o", objectpath);

    if (!nob_cmd_run_sync_and_reset(cmd)) {
      nob_log(NOB_ERROR, "Failed to compile");
      all_objects_compiled = false;
    }
  }
  cmd->count = 0;
  if (!all_objects_compiled) {
    nob_log(NOB_ERROR, "Failed to compile all objects");
    return 1;
  }
  // Library

  nob_cmd_append(cmd, "ar", "ruv",
                 SRC_LIB_FOLDER "release/"
                                "lib" PROJECT_NAME ".a");

  children.count = 0;
  nob_read_entire_dir(lib_path, &children);

  for (uint i = 0; i < children.count; i++) {

    char *buff = (char *)allocate(srcliblen + strlen(children.items[i]) + 1);
    buff[0] = '\0';
    strcat(buff, lib_path);
    strcat(buff, children.items[i]);
    Nob_File_Type type = nob_get_file_type(buff);
    if (type != NOB_FILE_REGULAR)
      continue;
    nob_log(NOB_INFO, "Discovered object %s", buff);
    nob_cmd_append(cmd, buff);
  }
  if (!nob_cmd_run_sync_and_reset(cmd)) {
    nob_log(NOB_ERROR, "Failed to build static library %s%s", lib_path,
            "lib" PROJECT_NAME ".a");
    return 1;
  }
  return 0;
}

int build_debug_library(Nob_Cmd *cmd) {
  const char *lib_path = SRC_LIB_FOLDER "debug/";
  if (!(nob_mkdir_if_not_exists(BUILD_FOLDER) &&
        nob_mkdir_if_not_exists(LIB_FOLDER) &&
        nob_mkdir_if_not_exists(SRC_LIB_FOLDER) &&
        nob_mkdir_if_not_exists(lib_path)))
    return 1;
  cmd->count = 0;
  // Objects

  Nob_File_Paths children = {0};
  nob_read_entire_dir(SRC_FOLDER, &children);

  char filepath[64] = SRC_FOLDER;
  int srclen = strlen(SRC_FOLDER);
  char objectpath[64] = {0};
  int srcliblen = strlen(lib_path);

  bool all_objects_compiled = true;

  for (uint i = 0; i < children.count; i++) {
    cmd->count = 0;
    strcpy(filepath, SRC_FOLDER);
    strcpy(objectpath, lib_path);
    nob_cmd_append(cmd, "cc", CFLAGS, DEBUG_FLAGS);
    strcpy(filepath + srclen, children.items[i]);
    Nob_File_Type type = nob_get_file_type(filepath);

    if (type != NOB_FILE_REGULAR || !ENDS_WITH(filepath, ".c") ||
        ENDS_WITH(filepath, "main.c"))
      continue;

    int fn_size = strlen(filepath) - srclen - 2;
    strncat(objectpath, filepath + srclen, fn_size);
    strcat(objectpath, ".o");

    nob_log(NOB_INFO, "compiling %s to %s", filepath, objectpath);
    nob_cmd_append(cmd, "-c", filepath, "-o", objectpath);

    if (!nob_cmd_run_sync_and_reset(cmd)) {
      nob_log(NOB_ERROR, "Failed to compile");
      all_objects_compiled = false;
    }
  }
  cmd->count = 0;
  if (!all_objects_compiled) {
    nob_log(NOB_ERROR, "Failed to compile all objects");
    return 1;
  }
  // Library

  nob_cmd_append(cmd, "ar", "ruv",
                 SRC_LIB_FOLDER "debug/"
                                "lib" PROJECT_NAME ".a");

  children.count = 0;
  nob_read_entire_dir(lib_path, &children);

  for (uint i = 0; i < children.count; i++) {

    char *buff = (char *)allocate(srcliblen + strlen(children.items[i]) + 1);
    buff[0] = '\0';
    strcat(buff, lib_path);
    strcat(buff, children.items[i]);
    Nob_File_Type type = nob_get_file_type(buff);
    if (type != NOB_FILE_REGULAR)
      continue;
    nob_log(NOB_INFO, "Discovered object %s", buff);
    nob_cmd_append(cmd, buff);
  }
  if (!nob_cmd_run_sync_and_reset(cmd)) {
    nob_log(NOB_ERROR, "Failed to build static library %s%s", lib_path,
            "lib" PROJECT_NAME ".a");
    return 1;
  }
  return 0;
}

int build(Nob_Cmd *cmd) {

  if (!nob_mkdir_if_not_exists(BUILD_FOLDER))
    return 1;

  // Release
  nob_cmd_append(cmd, "cc", SRC_FOLDER "main.c", CFLAGS, RELEASE_FLAGS, "-o",
                 BUILD_FOLDER PROJECT_NAME "_Release",
                 "-Lbuild/lib/src/release/", "-l" PROJECT_NAME);

  if (!nob_cmd_run_sync_and_reset(cmd))
    return 1;

  // Debug
  nob_cmd_append(cmd, "cc", SRC_FOLDER "main.c", CFLAGS, DEBUG_FLAGS, "-o",
                 BUILD_FOLDER PROJECT_NAME "_Debug", "-Lbuild/lib/src/debug/",
                 "-l" PROJECT_NAME);
  if (!nob_cmd_run_sync_and_reset(cmd))
    return 1;
  return 0;
}

int build_tests(Nob_Cmd *cmd) {
  int ok = 0;
  cmd->count = 0;

  if (!nob_mkdir_if_not_exists(TESTS_FOLDER))
    return 1;
  Nob_File_Paths children = {0};
  nob_read_entire_dir(TESTS_SRC_FOLDER, &children);

  char filepath[64] = "";
  strcat(filepath, TESTS_SRC_FOLDER);
  int testslen = strlen(TESTS_SRC_FOLDER);

  char filepath_noext[64] = TESTS_FOLDER;
  int output_len = strlen(TESTS_FOLDER);
  nob_log(NOB_INFO, "outlen filepath = %s with size %d", filepath_noext,
          output_len);

  for (uint i = 0; i < children.count; i++) {

    filepath[testslen] = '\0';
    strcat(filepath, children.items[i]);
    Nob_File_Type type = nob_get_file_type(filepath);
    if (type != NOB_FILE_REGULAR)
      continue;
    filepath_noext[output_len] = '\0';
    strcat(filepath_noext, children.items[i]);
    filepath_noext[strlen(filepath_noext) - 2] = '\0';
    nob_log(NOB_INFO, "Discovered test %s", filepath);
    nob_cmd_append(cmd, "cc", filepath, "-L" SRC_LIB_FOLDER "release/",
                   "-l" PROJECT_NAME, CFLAGS, RELEASE_FLAGS, "-o",
                   filepath_noext);
    if (!nob_cmd_run_sync_and_reset(cmd)) {
      nob_log(NOB_ERROR, "Failed to build test %s",
              filepath_noext + output_len);
      ok = -1;
    }
  }
  return ok;
}

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);

  Nob_Cmd cmd = {0};
  build_release_library(&cmd);
  build_debug_library(&cmd);

  if (build_tests(&cmd) != 0)
    nob_log(NOB_ERROR, "Test build unsuccesfull");
  // if (build(&cmd) != 0)
  //   nob_log(NOB_ERROR, "Build unsuccesfull");
  FREE();
  nob_cmd_free(cmd);
}
