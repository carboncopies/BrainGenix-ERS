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
include Libraries/glfw/tests/CMakeFiles/gamma.dir/depend.make

# Include the progress variables for this target.
include Libraries/glfw/tests/CMakeFiles/gamma.dir/progress.make

# Include the compile flags for this target's objects.
include Libraries/glfw/tests/CMakeFiles/gamma.dir/flags.make

Libraries/glfw/tests/CMakeFiles/gamma.dir/gamma.c.o: Libraries/glfw/tests/CMakeFiles/gamma.dir/flags.make
Libraries/glfw/tests/CMakeFiles/gamma.dir/gamma.c.o: Libraries/glfw/tests/gamma.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/OpenGL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Libraries/glfw/tests/CMakeFiles/gamma.dir/gamma.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gamma.dir/gamma.c.o   -c /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests/gamma.c

Libraries/glfw/tests/CMakeFiles/gamma.dir/gamma.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gamma.dir/gamma.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests/gamma.c > CMakeFiles/gamma.dir/gamma.c.i

Libraries/glfw/tests/CMakeFiles/gamma.dir/gamma.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gamma.dir/gamma.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests/gamma.c -o CMakeFiles/gamma.dir/gamma.c.s

Libraries/glfw/tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o: Libraries/glfw/tests/CMakeFiles/gamma.dir/flags.make
Libraries/glfw/tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o: Libraries/glfw/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/OpenGL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object Libraries/glfw/tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gamma.dir/__/deps/glad_gl.c.o   -c /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/deps/glad_gl.c

Libraries/glfw/tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gamma.dir/__/deps/glad_gl.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/deps/glad_gl.c > CMakeFiles/gamma.dir/__/deps/glad_gl.c.i

Libraries/glfw/tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gamma.dir/__/deps/glad_gl.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/deps/glad_gl.c -o CMakeFiles/gamma.dir/__/deps/glad_gl.c.s

# Object files for target gamma
gamma_OBJECTS = \
"CMakeFiles/gamma.dir/gamma.c.o" \
"CMakeFiles/gamma.dir/__/deps/glad_gl.c.o"

# External object files for target gamma
gamma_EXTERNAL_OBJECTS =

Libraries/glfw/tests/gamma: Libraries/glfw/tests/CMakeFiles/gamma.dir/gamma.c.o
Libraries/glfw/tests/gamma: Libraries/glfw/tests/CMakeFiles/gamma.dir/__/deps/glad_gl.c.o
Libraries/glfw/tests/gamma: Libraries/glfw/tests/CMakeFiles/gamma.dir/build.make
Libraries/glfw/tests/gamma: Libraries/glfw/src/libglfw3.a
Libraries/glfw/tests/gamma: /usr/lib/x86_64-linux-gnu/libm.so
Libraries/glfw/tests/gamma: /usr/lib/x86_64-linux-gnu/librt.so
Libraries/glfw/tests/gamma: /usr/lib/x86_64-linux-gnu/libm.so
Libraries/glfw/tests/gamma: /usr/lib/x86_64-linux-gnu/libX11.so
Libraries/glfw/tests/gamma: Libraries/glfw/tests/CMakeFiles/gamma.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/OpenGL/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable gamma"
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gamma.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Libraries/glfw/tests/CMakeFiles/gamma.dir/build: Libraries/glfw/tests/gamma

.PHONY : Libraries/glfw/tests/CMakeFiles/gamma.dir/build

Libraries/glfw/tests/CMakeFiles/gamma.dir/clean:
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/gamma.dir/cmake_clean.cmake
.PHONY : Libraries/glfw/tests/CMakeFiles/gamma.dir/clean

Libraries/glfw/tests/CMakeFiles/gamma.dir/depend:
	cd /home/tliao/Documents/BrainGenix-ERS/OpenGL && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tliao/Documents/BrainGenix-ERS/OpenGL /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests /home/tliao/Documents/BrainGenix-ERS/OpenGL /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests /home/tliao/Documents/BrainGenix-ERS/OpenGL/Libraries/glfw/tests/CMakeFiles/gamma.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Libraries/glfw/tests/CMakeFiles/gamma.dir/depend

