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
CMAKE_SOURCE_DIR = /home/tliao/Documents/BrainGenix-ERS/OpenGL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tliao/Documents/BrainGenix-ERS/OpenGL

# Include any dependencies generated for this target.
include Libraries/glfw/examples/CMakeFiles/gears.dir/depend.make

# Include the progress variables for this target.
include Libraries/glfw/examples/CMakeFiles/gears.dir/progress.make

# Include the compile flags for this target's objects.
include Libraries/glfw/examples/CMakeFiles/gears.dir/flags.make

Libraries/glfw/examples/CMakeFiles/gears.dir/gears.c.o: Libraries/glfw/examples/CMakeFiles/gears.dir/flags.make
Libraries/glfw/examples/CMakeFiles/gears.dir/gears.c.o: Libraries/glfw/examples/gears.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/OpenGL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Libraries/glfw/examples/CMakeFiles/gears.dir/gears.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gears.dir/gears.c.o   -c /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples/gears.c

Libraries/glfw/examples/CMakeFiles/gears.dir/gears.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gears.dir/gears.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples/gears.c > CMakeFiles/gears.dir/gears.c.i

Libraries/glfw/examples/CMakeFiles/gears.dir/gears.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gears.dir/gears.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples/gears.c -o CMakeFiles/gears.dir/gears.c.s

Libraries/glfw/examples/CMakeFiles/gears.dir/__/deps/glad_gl.c.o: Libraries/glfw/examples/CMakeFiles/gears.dir/flags.make
Libraries/glfw/examples/CMakeFiles/gears.dir/__/deps/glad_gl.c.o: Libraries/glfw/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/OpenGL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object Libraries/glfw/examples/CMakeFiles/gears.dir/__/deps/glad_gl.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gears.dir/__/deps/glad_gl.c.o   -c /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/deps/glad_gl.c

Libraries/glfw/examples/CMakeFiles/gears.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gears.dir/__/deps/glad_gl.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/deps/glad_gl.c > CMakeFiles/gears.dir/__/deps/glad_gl.c.i

Libraries/glfw/examples/CMakeFiles/gears.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gears.dir/__/deps/glad_gl.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/deps/glad_gl.c -o CMakeFiles/gears.dir/__/deps/glad_gl.c.s

# Object files for target gears
gears_OBJECTS = \
"CMakeFiles/gears.dir/gears.c.o" \
"CMakeFiles/gears.dir/__/deps/glad_gl.c.o"

# External object files for target gears
gears_EXTERNAL_OBJECTS =

Libraries/glfw/examples/gears: Libraries/glfw/examples/CMakeFiles/gears.dir/gears.c.o
Libraries/glfw/examples/gears: Libraries/glfw/examples/CMakeFiles/gears.dir/__/deps/glad_gl.c.o
Libraries/glfw/examples/gears: Libraries/glfw/examples/CMakeFiles/gears.dir/build.make
Libraries/glfw/examples/gears: Libraries/glfw/src/libglfw3.a
Libraries/glfw/examples/gears: /usr/lib/x86_64-linux-gnu/libm.so
Libraries/glfw/examples/gears: /usr/lib/x86_64-linux-gnu/librt.so
Libraries/glfw/examples/gears: /usr/lib/x86_64-linux-gnu/libm.so
Libraries/glfw/examples/gears: /usr/lib/x86_64-linux-gnu/libX11.so
Libraries/glfw/examples/gears: Libraries/glfw/examples/CMakeFiles/gears.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/OpenGL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable gears"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gears.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Libraries/glfw/examples/CMakeFiles/gears.dir/build: Libraries/glfw/examples/gears

.PHONY : Libraries/glfw/examples/CMakeFiles/gears.dir/build

Libraries/glfw/examples/CMakeFiles/gears.dir/clean:
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples && $(CMAKE_COMMAND) -P CMakeFiles/gears.dir/cmake_clean.cmake
.PHONY : Libraries/glfw/examples/CMakeFiles/gears.dir/clean

Libraries/glfw/examples/CMakeFiles/gears.dir/depend:
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tliao/Documents/BrainGenix-ERS/OpenGL /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples /home/tliao/Documents/BrainGenix-ERS/OpenGL /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/examples/CMakeFiles/gears.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Libraries/glfw/examples/CMakeFiles/gears.dir/depend

