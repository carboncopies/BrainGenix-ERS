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
include third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/depend.make

# Include the progress variables for this target.
include third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/progress.make

# Include the compile flags for this target's objects.
include third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/flags.make

third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/main/imports.c.o: third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/flags.make
third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/main/imports.c.o: ../third-party/bgfx/External/glsl-optimizer/src/mesa/main/imports.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/main/imports.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mesa.dir/src/mesa/main/imports.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/mesa/main/imports.c

third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/main/imports.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mesa.dir/src/mesa/main/imports.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/mesa/main/imports.c > CMakeFiles/mesa.dir/src/mesa/main/imports.c.i

third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/main/imports.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mesa.dir/src/mesa/main/imports.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/mesa/main/imports.c -o CMakeFiles/mesa.dir/src/mesa/main/imports.c.s

third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/program/prog_hash_table.c.o: third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/flags.make
third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/program/prog_hash_table.c.o: ../third-party/bgfx/External/glsl-optimizer/src/mesa/program/prog_hash_table.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/program/prog_hash_table.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mesa.dir/src/mesa/program/prog_hash_table.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/mesa/program/prog_hash_table.c

third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/program/prog_hash_table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mesa.dir/src/mesa/program/prog_hash_table.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/mesa/program/prog_hash_table.c > CMakeFiles/mesa.dir/src/mesa/program/prog_hash_table.c.i

third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/program/prog_hash_table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mesa.dir/src/mesa/program/prog_hash_table.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/mesa/program/prog_hash_table.c -o CMakeFiles/mesa.dir/src/mesa/program/prog_hash_table.c.s

third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/program/symbol_table.c.o: third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/flags.make
third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/program/symbol_table.c.o: ../third-party/bgfx/External/glsl-optimizer/src/mesa/program/symbol_table.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/program/symbol_table.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mesa.dir/src/mesa/program/symbol_table.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/mesa/program/symbol_table.c

third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/program/symbol_table.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mesa.dir/src/mesa/program/symbol_table.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/mesa/program/symbol_table.c > CMakeFiles/mesa.dir/src/mesa/program/symbol_table.c.i

third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/program/symbol_table.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mesa.dir/src/mesa/program/symbol_table.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer/src/mesa/program/symbol_table.c -o CMakeFiles/mesa.dir/src/mesa/program/symbol_table.c.s

# Object files for target mesa
mesa_OBJECTS = \
"CMakeFiles/mesa.dir/src/mesa/main/imports.c.o" \
"CMakeFiles/mesa.dir/src/mesa/program/prog_hash_table.c.o" \
"CMakeFiles/mesa.dir/src/mesa/program/symbol_table.c.o"

# External object files for target mesa
mesa_EXTERNAL_OBJECTS =

third-party/bgfx/External/glsl-optimizer/libmesa.a: third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/main/imports.c.o
third-party/bgfx/External/glsl-optimizer/libmesa.a: third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/program/prog_hash_table.c.o
third-party/bgfx/External/glsl-optimizer/libmesa.a: third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/src/mesa/program/symbol_table.c.o
third-party/bgfx/External/glsl-optimizer/libmesa.a: third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/build.make
third-party/bgfx/External/glsl-optimizer/libmesa.a: third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C static library libmesa.a"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && $(CMAKE_COMMAND) -P CMakeFiles/mesa.dir/cmake_clean_target.cmake
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mesa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/build: third-party/bgfx/External/glsl-optimizer/libmesa.a

.PHONY : third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/build

third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/clean:
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer && $(CMAKE_COMMAND) -P CMakeFiles/mesa.dir/cmake_clean.cmake
.PHONY : third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/clean

third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/depend:
	cd /home/tliao/Documents/BrainGenix-ERS/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tliao/Documents/BrainGenix-ERS /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/glsl-optimizer /home/tliao/Documents/BrainGenix-ERS/Build /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third-party/bgfx/External/glsl-optimizer/CMakeFiles/mesa.dir/depend

