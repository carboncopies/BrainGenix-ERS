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
CMAKE_SOURCE_DIR = /home/tliao/Documents/BrainGenix-ERS/Vulkan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist

# Include any dependencies generated for this target.
include System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/depend.make

# Include the progress variables for this target.
include System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/progress.make

# Include the compile flags for this target's objects.
include System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/flags.make

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/particles.c.o: System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/flags.make
System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/particles.c.o: ../System/ExternalLibraries/glfw-3.3.4/examples/particles.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/particles.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/particles.dir/particles.c.o   -c /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/examples/particles.c

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/particles.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/particles.dir/particles.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/examples/particles.c > CMakeFiles/particles.dir/particles.c.i

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/particles.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/particles.dir/particles.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/examples/particles.c -o CMakeFiles/particles.dir/particles.c.s

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.o: System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/flags.make
System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.o: ../System/ExternalLibraries/glfw-3.3.4/deps/tinycthread.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/particles.dir/__/deps/tinycthread.c.o   -c /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/tinycthread.c

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/particles.dir/__/deps/tinycthread.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/tinycthread.c > CMakeFiles/particles.dir/__/deps/tinycthread.c.i

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/particles.dir/__/deps/tinycthread.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/tinycthread.c -o CMakeFiles/particles.dir/__/deps/tinycthread.c.s

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/getopt.c.o: System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/flags.make
System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/getopt.c.o: ../System/ExternalLibraries/glfw-3.3.4/deps/getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/getopt.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/particles.dir/__/deps/getopt.c.o   -c /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/getopt.c

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/particles.dir/__/deps/getopt.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/getopt.c > CMakeFiles/particles.dir/__/deps/getopt.c.i

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/particles.dir/__/deps/getopt.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/getopt.c -o CMakeFiles/particles.dir/__/deps/getopt.c.s

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/glad_gl.c.o: System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/flags.make
System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/glad_gl.c.o: ../System/ExternalLibraries/glfw-3.3.4/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/glad_gl.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/particles.dir/__/deps/glad_gl.c.o   -c /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/glad_gl.c

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/particles.dir/__/deps/glad_gl.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/glad_gl.c > CMakeFiles/particles.dir/__/deps/glad_gl.c.i

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/particles.dir/__/deps/glad_gl.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/glad_gl.c -o CMakeFiles/particles.dir/__/deps/glad_gl.c.s

# Object files for target particles
particles_OBJECTS = \
"CMakeFiles/particles.dir/particles.c.o" \
"CMakeFiles/particles.dir/__/deps/tinycthread.c.o" \
"CMakeFiles/particles.dir/__/deps/getopt.c.o" \
"CMakeFiles/particles.dir/__/deps/glad_gl.c.o"

# External object files for target particles
particles_EXTERNAL_OBJECTS =

System/ExternalLibraries/glfw-3.3.4/examples/particles: System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/particles.c.o
System/ExternalLibraries/glfw-3.3.4/examples/particles: System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/tinycthread.c.o
System/ExternalLibraries/glfw-3.3.4/examples/particles: System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/getopt.c.o
System/ExternalLibraries/glfw-3.3.4/examples/particles: System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/__/deps/glad_gl.c.o
System/ExternalLibraries/glfw-3.3.4/examples/particles: System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/build.make
System/ExternalLibraries/glfw-3.3.4/examples/particles: System/ExternalLibraries/glfw-3.3.4/src/libglfw3.a
System/ExternalLibraries/glfw-3.3.4/examples/particles: /usr/lib/x86_64-linux-gnu/libm.so
System/ExternalLibraries/glfw-3.3.4/examples/particles: /usr/lib/x86_64-linux-gnu/librt.so
System/ExternalLibraries/glfw-3.3.4/examples/particles: /usr/lib/x86_64-linux-gnu/libX11.so
System/ExternalLibraries/glfw-3.3.4/examples/particles: System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking C executable particles"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/particles.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/build: System/ExternalLibraries/glfw-3.3.4/examples/particles

.PHONY : System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/build

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/clean:
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples && $(CMAKE_COMMAND) -P CMakeFiles/particles.dir/cmake_clean.cmake
.PHONY : System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/clean

System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/depend:
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tliao/Documents/BrainGenix-ERS/Vulkan /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/examples /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : System/ExternalLibraries/glfw-3.3.4/examples/CMakeFiles/particles.dir/depend

