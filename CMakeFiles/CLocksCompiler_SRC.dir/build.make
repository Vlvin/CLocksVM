# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /nix/store/38cffsqqx823crf1i4bcf6zz1qz1hgpd-cmake-3.30.5/bin/cmake

# The command to remove a file.
RM = /nix/store/38cffsqqx823crf1i4bcf6zz1qz1hgpd-cmake-3.30.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vlvin/Code/C/CLocksVM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vlvin/Code/C/CLocksVM

# Include any dependencies generated for this target.
include CMakeFiles/CLocksCompiler_SRC.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/CLocksCompiler_SRC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CLocksCompiler_SRC.dir/flags.make

CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.o: src/bitsTricks.c
CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.o -c /home/vlvin/Code/C/CLocksVM/src/bitsTricks.c

CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/bitsTricks.c > CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/bitsTricks.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.o: src/debug.c
CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.o -c /home/vlvin/Code/C/CLocksVM/src/debug.c

CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/debug.c > CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/debug.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.o: src/loxChunk.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxChunk.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxChunk.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxChunk.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.o: src/loxObject.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxObject.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxObject.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxObject.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.o: src/loxCLI.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxCLI.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxCLI.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxCLI.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.o: src/loxCompiler.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxCompiler.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxCompiler.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxCompiler.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.o: src/loxErrors.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxErrors.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxErrors.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxErrors.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.o: src/loxLineTracker.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxLineTracker.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxLineTracker.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxLineTracker.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.o: src/loxMemory.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxMemory.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxMemory.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxMemory.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.o: src/loxParser.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxParser.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxParser.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxParser.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.o: src/loxScanner.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxScanner.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxScanner.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxScanner.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.o: src/loxStack.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxStack.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxStack.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxStack.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.o: src/loxToken.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxToken.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxToken.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxToken.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.o: src/loxValue.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxValue.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxValue.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxValue.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.o: src/loxValueArray.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxValueArray.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxValueArray.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxValueArray.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.s

CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.o: CMakeFiles/CLocksCompiler_SRC.dir/flags.make
CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.o: src/loxVM.c
CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.o: CMakeFiles/CLocksCompiler_SRC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building C object CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.o"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.o -MF CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.o.d -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.o -c /home/vlvin/Code/C/CLocksVM/src/loxVM.c

CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.i"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/vlvin/Code/C/CLocksVM/src/loxVM.c > CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.i

CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.s"
	/run/current-system/sw/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/vlvin/Code/C/CLocksVM/src/loxVM.c -o CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.s

# Object files for target CLocksCompiler_SRC
CLocksCompiler_SRC_OBJECTS = \
"CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.o" \
"CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.o"

# External object files for target CLocksCompiler_SRC
CLocksCompiler_SRC_EXTERNAL_OBJECTS =

libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/bitsTricks.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/debug.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxChunk.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxObject.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxCLI.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxCompiler.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxErrors.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxLineTracker.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxMemory.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxParser.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxScanner.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxStack.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxToken.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxValue.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxValueArray.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/src/loxVM.c.o
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/build.make
libCLocksCompiler_SRC.a: CMakeFiles/CLocksCompiler_SRC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/vlvin/Code/C/CLocksVM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Linking C static library libCLocksCompiler_SRC.a"
	$(CMAKE_COMMAND) -P CMakeFiles/CLocksCompiler_SRC.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CLocksCompiler_SRC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CLocksCompiler_SRC.dir/build: libCLocksCompiler_SRC.a
.PHONY : CMakeFiles/CLocksCompiler_SRC.dir/build

CMakeFiles/CLocksCompiler_SRC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CLocksCompiler_SRC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CLocksCompiler_SRC.dir/clean

CMakeFiles/CLocksCompiler_SRC.dir/depend:
	cd /home/vlvin/Code/C/CLocksVM && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vlvin/Code/C/CLocksVM /home/vlvin/Code/C/CLocksVM /home/vlvin/Code/C/CLocksVM /home/vlvin/Code/C/CLocksVM /home/vlvin/Code/C/CLocksVM/CMakeFiles/CLocksCompiler_SRC.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/CLocksCompiler_SRC.dir/depend

