# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gus/dev/DSA/vector

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gus/dev/DSA/vector/build

# Include any dependencies generated for this target.
include CMakeFiles/b_array_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/b_array_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/b_array_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/b_array_test.dir/flags.make

CMakeFiles/b_array_test.dir/codegen:
.PHONY : CMakeFiles/b_array_test.dir/codegen

CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.o: CMakeFiles/b_array_test.dir/flags.make
CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.o: /home/gus/dev/DSA/vector/tests/unit/b_array_test.c
CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.o: CMakeFiles/b_array_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/gus/dev/DSA/vector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.o -MF CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.o.d -o CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.o -c /home/gus/dev/DSA/vector/tests/unit/b_array_test.c

CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gus/dev/DSA/vector/tests/unit/b_array_test.c > CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.i

CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gus/dev/DSA/vector/tests/unit/b_array_test.c -o CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.s

# Object files for target b_array_test
b_array_test_OBJECTS = \
"CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.o"

# External object files for target b_array_test
b_array_test_EXTERNAL_OBJECTS =

b_array_test: CMakeFiles/b_array_test.dir/tests/unit/b_array_test.c.o
b_array_test: CMakeFiles/b_array_test.dir/build.make
b_array_test: CMakeFiles/b_array_test.dir/compiler_depend.ts
b_array_test: libcds.a
b_array_test: /usr/lib/libcunit.so
b_array_test: CMakeFiles/b_array_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/gus/dev/DSA/vector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable b_array_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/b_array_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/b_array_test.dir/build: b_array_test
.PHONY : CMakeFiles/b_array_test.dir/build

CMakeFiles/b_array_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/b_array_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/b_array_test.dir/clean

CMakeFiles/b_array_test.dir/depend:
	cd /home/gus/dev/DSA/vector/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gus/dev/DSA/vector /home/gus/dev/DSA/vector /home/gus/dev/DSA/vector/build /home/gus/dev/DSA/vector/build /home/gus/dev/DSA/vector/build/CMakeFiles/b_array_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/b_array_test.dir/depend

