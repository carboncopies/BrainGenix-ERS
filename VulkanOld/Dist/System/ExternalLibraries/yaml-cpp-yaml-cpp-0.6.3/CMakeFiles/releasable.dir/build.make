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

# Utility rule file for releasable.

# Include the progress variables for this target.
include System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3/CMakeFiles/releasable.dir/progress.make

System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3/CMakeFiles/releasable:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Adjusting settings for release compilation"
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3 && /usr/bin/make clean
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3 && /usr/bin/cmake -DCMAKE_BUILD_TYPE=Release /home/tliao/Documents/BrainGenix-ERS/Vulkan

releasable: System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3/CMakeFiles/releasable
releasable: System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3/CMakeFiles/releasable.dir/build.make

.PHONY : releasable

# Rule to build all files generated by this target.
System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3/CMakeFiles/releasable.dir/build: releasable

.PHONY : System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3/CMakeFiles/releasable.dir/build

System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3/CMakeFiles/releasable.dir/clean:
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3 && $(CMAKE_COMMAND) -P CMakeFiles/releasable.dir/cmake_clean.cmake
.PHONY : System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3/CMakeFiles/releasable.dir/clean

System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3/CMakeFiles/releasable.dir/depend:
	cd /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tliao/Documents/BrainGenix-ERS/Vulkan /home/tliao/Documents/BrainGenix-ERS/Vulkan/System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3 /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3 /home/tliao/Documents/BrainGenix-ERS/Vulkan/Dist/System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3/CMakeFiles/releasable.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3/CMakeFiles/releasable.dir/depend

