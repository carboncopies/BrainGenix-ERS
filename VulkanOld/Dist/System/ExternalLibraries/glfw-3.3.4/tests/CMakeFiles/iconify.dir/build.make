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
include System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/depend.make

# Include the progress variables for this target.
include System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/progress.make

# Include the compile flags for this target's objects.
include System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/flags.make

System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/iconify.c.o: System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/flags.make
System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/iconify.c.o: ../System/ExternalLibraries/glfw-3.3.4/tests/iconify.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/iconify.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iconify.dir/iconify.c.o   -c /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/tests/iconify.c

System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/iconify.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/iconify.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/tests/iconify.c > CMakeFiles/iconify.dir/iconify.c.i

System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/iconify.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/iconify.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/tests/iconify.c -o CMakeFiles/iconify.dir/iconify.c.s

System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/flags.make
System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o: ../System/ExternalLibraries/glfw-3.3.4/deps/getopt.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iconify.dir/__/deps/getopt.c.o   -c /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/getopt.c

System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/getopt.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/getopt.c > CMakeFiles/iconify.dir/__/deps/getopt.c.i

System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/getopt.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/getopt.c -o CMakeFiles/iconify.dir/__/deps/getopt.c.s

System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o: System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/flags.make
System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o: ../System/ExternalLibraries/glfw-3.3.4/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iconify.dir/__/deps/glad_gl.c.o   -c /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/glad_gl.c

System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/glad_gl.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/glad_gl.c > CMakeFiles/iconify.dir/__/deps/glad_gl.c.i

System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/glad_gl.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/deps/glad_gl.c -o CMakeFiles/iconify.dir/__/deps/glad_gl.c.s

# Object files for target iconify
iconify_OBJECTS = \
"CMakeFiles/iconify.dir/iconify.c.o" \
"CMakeFiles/iconify.dir/__/deps/getopt.c.o" \
"CMakeFiles/iconify.dir/__/deps/glad_gl.c.o"

# External object files for target iconify
iconify_EXTERNAL_OBJECTS =

System/ExternalLibraries/glfw-3.3.4/tests/iconify: System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/iconify.c.o
System/ExternalLibraries/glfw-3.3.4/tests/iconify: System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.o
System/ExternalLibraries/glfw-3.3.4/tests/iconify: System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.o
System/ExternalLibraries/glfw-3.3.4/tests/iconify: System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/build.make
System/ExternalLibraries/glfw-3.3.4/tests/iconify: System/ExternalLibraries/glfw-3.3.4/src/libglfw3.a
System/ExternalLibraries/glfw-3.3.4/tests/iconify: /usr/lib/x86_64-linux-gnu/libm.so
System/ExternalLibraries/glfw-3.3.4/tests/iconify: /usr/lib/x86_64-linux-gnu/librt.so
System/ExternalLibraries/glfw-3.3.4/tests/iconify: /usr/lib/x86_64-linux-gnu/libm.so
System/ExternalLibraries/glfw-3.3.4/tests/iconify: /usr/lib/x86_64-linux-gnu/libX11.so
System/ExternalLibraries/glfw-3.3.4/tests/iconify: System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable iconify"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iconify.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/build: System/ExternalLibraries/glfw-3.3.4/tests/iconify

.PHONY : System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/build

System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/clean:
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests && $(CMAKE_COMMAND) -P CMakeFiles/iconify.dir/cmake_clean.cmake
.PHONY : System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/clean

System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/depend:
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tliao/Documents/BrainGenix-ERS/Vulkan /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/glfw-3.3.4/tests /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : System/ExternalLibraries/glfw-3.3.4/tests/CMakeFiles/iconify.dir/depend

