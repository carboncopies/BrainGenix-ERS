# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tliao/Documents/BrainGenix-ERS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tliao/Documents/BrainGenix-ERS/Build

# Include any dependencies generated for this target.
include third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/depend.make

# Include the progress variables for this target.
include third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/progress.make

# Include the compile flags for this target's objects.
include third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/flags.make

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-lex.c.o: third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/flags.make
third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-lex.c.o: ../third-party/bgfx/External/glsl-optimizer/src/glsl/glcpp/glcpp-lex.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-lex.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-lex.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/glsl/glcpp/glcpp-lex.c

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-lex.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-lex.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/glsl/glcpp/glcpp-lex.c > CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-lex.c.i

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-lex.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-lex.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/glsl/glcpp/glcpp-lex.c -o CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-lex.c.s

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-parse.c.o: third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/flags.make
third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-parse.c.o: ../third-party/bgfx/External/glsl-optimizer/src/glsl/glcpp/glcpp-parse.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-parse.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-parse.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/glsl/glcpp/glcpp-parse.c

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-parse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-parse.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/glsl/glcpp/glcpp-parse.c > CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-parse.c.i

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-parse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-parse.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/glsl/glcpp/glcpp-parse.c -o CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-parse.c.s

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/pp.c.o: third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/flags.make
third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/pp.c.o: ../third-party/bgfx/External/glsl-optimizer/src/glsl/glcpp/pp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/pp.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glcpp.dir/src/glsl/glcpp/pp.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/glsl/glcpp/pp.c

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/pp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glcpp.dir/src/glsl/glcpp/pp.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/glsl/glcpp/pp.c > CMakeFiles/glcpp.dir/src/glsl/glcpp/pp.c.i

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/pp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glcpp.dir/src/glsl/glcpp/pp.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/glsl/glcpp/pp.c -o CMakeFiles/glcpp.dir/src/glsl/glcpp/pp.c.s

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/util/hash_table.c.o: third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/flags.make
third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/util/hash_table.c.o: ../third-party/bgfx/External/glsl-optimizer/src/util/hash_table.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/util/hash_table.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glcpp.dir/src/util/hash_table.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/util/hash_table.c

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/util/hash_table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glcpp.dir/src/util/hash_table.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/util/hash_table.c > CMakeFiles/glcpp.dir/src/util/hash_table.c.i

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/util/hash_table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glcpp.dir/src/util/hash_table.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/util/hash_table.c -o CMakeFiles/glcpp.dir/src/util/hash_table.c.s

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/util/ralloc.c.o: third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/flags.make
third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/util/ralloc.c.o: ../third-party/bgfx/External/glsl-optimizer/src/util/ralloc.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/util/ralloc.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glcpp.dir/src/util/ralloc.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/util/ralloc.c

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/util/ralloc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glcpp.dir/src/util/ralloc.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/util/ralloc.c > CMakeFiles/glcpp.dir/src/util/ralloc.c.i

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/util/ralloc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glcpp.dir/src/util/ralloc.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/util/ralloc.c -o CMakeFiles/glcpp.dir/src/util/ralloc.c.s

# Object files for target glcpp
glcpp_OBJECTS = \
"CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-lex.c.o" \
"CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-parse.c.o" \
"CMakeFiles/glcpp.dir/src/glsl/glcpp/pp.c.o" \
"CMakeFiles/glcpp.dir/src/util/hash_table.c.o" \
"CMakeFiles/glcpp.dir/src/util/ralloc.c.o"

# External object files for target glcpp
glcpp_EXTERNAL_OBJECTS =

third-party/bgfx/External/glsl-optimizer/libglcpp.a: third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-lex.c.o
third-party/bgfx/External/glsl-optimizer/libglcpp.a: third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/glcpp-parse.c.o
third-party/bgfx/External/glsl-optimizer/libglcpp.a: third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/glsl/glcpp/pp.c.o
third-party/bgfx/External/glsl-optimizer/libglcpp.a: third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/util/hash_table.c.o
third-party/bgfx/External/glsl-optimizer/libglcpp.a: third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/src/util/ralloc.c.o
third-party/bgfx/External/glsl-optimizer/libglcpp.a: third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/build.make
third-party/bgfx/External/glsl-optimizer/libglcpp.a: third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C static library libglcpp.a"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && $(CMAKE_COMMAND) -P CMakeFiles/glcpp.dir/cmake_clean_target.cmake
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glcpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/build: third-party/bgfx/External/glsl-optimizer/libglcpp.a

.PHONY : third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/build

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/clean:
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && $(CMAKE_COMMAND) -P CMakeFiles/glcpp.dir/cmake_clean.cmake
.PHONY : third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/clean

third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/depend:
	cd /home/tliao/Documents/BrainGenix-ERS/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tliao/Documents/BrainGenix-ERS /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer /home/tliao/Documents/BrainGenix-ERS/Build /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third-party/bgfx/External/glsl-optimizer/CMakeFiles/glcpp.dir/depend

