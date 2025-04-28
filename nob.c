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

// paths
#define BUILD_FOLDER "build/"
#define SRC_FOLDER "src/"
#define TESTS_SRC_FOLDER "tests/"
#define TESTS_FOLDER "build/tests/"
#define LIB_FOLDER BUILD_FOLDER "lib/"
#define SRC_LIB_FOLDER LIB_FOLDER "src/"
// flags
#define CFLAGS "-Wall", "-I" SRC_FOLDER
#define DEBUG_FLAGS "-O0", "-ggdb", "-DDEBUG_PRINT_CODE", "-DDEBUG_TRACE"
#define RELEASE_FLAGS "-O3"

typedef enum { RELEASE = 0, DEBUG = 1 } Build_Type;
const char *lib_subpath[] = {"release/", "debug/"};
const char *lib_postfix[] = {"_Release", "_Debug"};

#define cmd_append_flags(cmd, built_type)                                      \
  do {                                                                         \
    switch (built_type) {                                                      \
    case DEBUG:                                                                \
      nob_cmd_append(cmd, DEBUG_FLAGS);                                        \
      break;                                                                   \
    case RELEASE:                                                              \
      nob_cmd_append(cmd, RELEASE_FLAGS);                                      \
      break;                                                                   \
    }                                                                          \
  } while (0)

const int SRC_LEN = strlen(SRC_FOLDER);

Nob_Procs procs = {0};

int build_library(Nob_Cmd *cmd, Nob_Procs *procs, Build_Type build_type) {
  const char *lib_path =
      nob_temp_sprintf("%s%s", SRC_LIB_FOLDER, lib_subpath[build_type]);
  if (!(nob_mkdir_if_not_exists(BUILD_FOLDER) &&
        nob_mkdir_if_not_exists(LIB_FOLDER) &&
        nob_mkdir_if_not_exists(SRC_LIB_FOLDER) &&
        nob_mkdir_if_not_exists(lib_path))) {
    nob_temp_reset();
    return 1;
  }
  cmd->count = 0;
  // Objects

  Nob_File_Paths children = {0};
  nob_read_entire_dir(SRC_FOLDER, &children);

  bool all_objects_compiled = true;

  for (uint i = 0; i < children.count; i++) {
    cmd->count = 0;
    char *filepath = nob_temp_sprintf(SRC_FOLDER "%s", children.items[i]);
    Nob_File_Type type = nob_get_file_type(filepath);

    if (type != NOB_FILE_REGULAR || !ENDS_WITH(filepath, ".c") ||
        ENDS_WITH(filepath, "main.c"))
      continue;

    int filename_size = strlen(filepath) - SRC_LEN - 2;

    char *objectpath = nob_temp_sprintf("%s%*s.o", lib_path, filename_size,
                                        filepath + SRC_LEN);

    nob_cmd_append(cmd, "cc", CFLAGS);
    cmd_append_flags(cmd, build_type);
    nob_cmd_append(cmd, "-c", filepath, "-o", objectpath);

    nob_da_append(procs, nob_cmd_run_async_and_reset(cmd));
  }
  cmd->count = 0;
  bool all_object_compiled = nob_procs_wait_and_reset(procs);
  if (!all_objects_compiled) {
    nob_log(NOB_ERROR, "Failed to compile all objects");
    nob_temp_reset();
    return 1;
  }
  // Library

  nob_cmd_append(cmd, "ar", "ruv",
                 nob_temp_sprintf("%slib" PROJECT_NAME ".a", lib_path));

  children.count = 0;
  nob_read_entire_dir(lib_path, &children);

  for (uint i = 0; i < children.count; i++) {
    char *object_path = nob_temp_sprintf("%s%s", lib_path, children.items[i]);
    Nob_File_Type type = nob_get_file_type(object_path);
    if (type != NOB_FILE_REGULAR)
      continue;
    nob_cmd_append(cmd, object_path);
  }
  nob_temp_reset();
  nob_da_append(procs, nob_cmd_run_async_and_reset(cmd));
  if (!nob_procs_wait_and_reset(procs)) {
    nob_log(NOB_ERROR, "Failed to create library");
    return 1;
  }
  return 0;
}

int build_release_library(Nob_Cmd *cmd, Nob_Procs *procs) {
  return build_library(cmd, procs, RELEASE);
}

int build_debug_library(Nob_Cmd *cmd, Nob_Procs *procs) {
  return build_library(cmd, procs, DEBUG);
}

int build_exec(Nob_Cmd *cmd, Nob_Procs *procs) {
  int ok = 0;

  if (!nob_mkdir_if_not_exists(BUILD_FOLDER))
    return 1;

  // Release
  nob_cmd_append(cmd, "cc", SRC_FOLDER "main.c", CFLAGS);
  cmd_append_flags(cmd, RELEASE);
  nob_cmd_append(cmd, "-o", BUILD_FOLDER PROJECT_NAME "_Release",
                 "-Lbuild/lib/src/release/", "-l" PROJECT_NAME);

  nob_da_append(procs, nob_cmd_run_async_and_reset(cmd));

  // Debug
  nob_cmd_append(cmd, "cc", SRC_FOLDER "main.c", CFLAGS);
  cmd_append_flags(cmd, DEBUG);
  nob_cmd_append(cmd, "-o", BUILD_FOLDER PROJECT_NAME "_Debug",
                 "-Lbuild/lib/src/debug/", "-l" PROJECT_NAME);

  nob_da_append(procs, nob_cmd_run_async_and_reset(cmd));
  if (!nob_procs_wait_and_reset(procs)) {
    nob_log(NOB_ERROR, "Failed to executables");
    ok = 1;
  }

  return ok;
}

int build_tests(Nob_Cmd *cmd, Nob_Procs *procs) {
  int ok = 0;
  cmd->count = 0;

  if (!nob_mkdir_if_not_exists(TESTS_FOLDER))
    return 1;
  Nob_File_Paths children = {0};
  nob_read_entire_dir(TESTS_SRC_FOLDER, &children);

  const int output_len = strlen(TESTS_FOLDER);

  for (uint i = 0; i < children.count; i++) {

    const char *filepath =
        nob_temp_sprintf(TESTS_SRC_FOLDER "%s", children.items[i]);
    Nob_File_Type type = nob_get_file_type(filepath);
    if (type != NOB_FILE_REGULAR)
      continue;
    const char *filepath_noext =
        nob_temp_sprintf(TESTS_FOLDER "%*.s",
                         (int)strlen(children.items[i]) - 2, children.items[i]);
    nob_cmd_append(cmd, "cc", filepath, "-L" SRC_LIB_FOLDER "release/",
                   "-l" PROJECT_NAME, CFLAGS);
    cmd_append_flags(cmd, RELEASE);
    nob_cmd_append(cmd, "-o", filepath_noext);

    nob_da_append(procs, nob_cmd_run_async_and_reset(cmd));
  }
  if (!nob_procs_wait_and_reset(procs)) {
    nob_log(NOB_ERROR, "Failed to build tests");
    ok = -1;
  }
  nob_temp_reset();
  return ok;
}

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);

  Nob_Cmd cmd = {0};
  build_release_library(&cmd, &procs);
  build_debug_library(&cmd, &procs);

  if (build_tests(&cmd, &procs) != 0)
    nob_log(NOB_ERROR, "Test build unsuccesfull");
  if (build_exec(&cmd, &procs) != 0)
    nob_log(NOB_ERROR, "Build unsuccesfull");
  nob_cmd_free(cmd);
  nob_da_free(procs);
}
