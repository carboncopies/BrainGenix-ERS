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
include third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/depend.make

# Include the progress variables for this target.
include third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/progress.make

# Include the compile flags for this target's objects.
include third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/flags.make

third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/3rdparty/etc1/etc1.cpp.o: third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/flags.make
third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/3rdparty/etc1/etc1.cpp.o: ../third-party/bgfx/External/bimg/3rdparty/etc1/etc1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/3rdparty/etc1/etc1.cpp.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/etc1.dir/3rdparty/etc1/etc1.cpp.o -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/etc1/etc1.cpp

third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/3rdparty/etc1/etc1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/etc1.dir/3rdparty/etc1/etc1.cpp.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/etc1/etc1.cpp > CMakeFiles/etc1.dir/3rdparty/etc1/etc1.cpp.i

third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/3rdparty/etc1/etc1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/etc1.dir/3rdparty/etc1/etc1.cpp.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/etc1/etc1.cpp -o CMakeFiles/etc1.dir/3rdparty/etc1/etc1.cpp.s

# Object files for target etc1
etc1_OBJECTS = \
"CMakeFiles/etc1.dir/3rdparty/etc1/etc1.cpp.o"

# External object files for target etc1
etc1_EXTERNAL_OBJECTS =

third-party/bgfx/External/bimg/libetc1.a: third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/3rdparty/etc1/etc1.cpp.o
third-party/bgfx/External/bimg/libetc1.a: third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/build.make
third-party/bgfx/External/bimg/libetc1.a: third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libetc1.a"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && $(CMAKE_COMMAND) -P CMakeFiles/etc1.dir/cmake_clean_target.cmake
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/etc1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/build: third-party/bgfx/External/bimg/libetc1.a

.PHONY : third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/build

third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/clean:
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && $(CMAKE_COMMAND) -P CMakeFiles/etc1.dir/cmake_clean.cmake
.PHONY : third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/clean

third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/depend:
	cd /home/tliao/Documents/BrainGenix-ERS/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tliao/Documents/BrainGenix-ERS /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg /home/tliao/Documents/BrainGenix-ERS/Build /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third-party/bgfx/External/bimg/CMakeFiles/etc1.dir/depend

