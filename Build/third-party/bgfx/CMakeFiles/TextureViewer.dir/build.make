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
include third-party/bgfx/CMakeFiles/TextureViewer.dir/depend.make

# Include the progress variables for this target.
include third-party/bgfx/CMakeFiles/TextureViewer.dir/progress.make

# Include the compile flags for this target's objects.
include third-party/bgfx/CMakeFiles/TextureViewer.dir/flags.make

third-party/bgfx/CMakeFiles/TextureViewer.dir/Src/RenderTools/TextureViewer/TextureViewer.cpp.o: third-party/bgfx/CMakeFiles/TextureViewer.dir/flags.make
third-party/bgfx/CMakeFiles/TextureViewer.dir/Src/RenderTools/TextureViewer/TextureViewer.cpp.o: ../third-party/bgfx/Src/RenderTools/TextureViewer/TextureViewer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object third-party/bgfx/CMakeFiles/TextureViewer.dir/Src/RenderTools/TextureViewer/TextureViewer.cpp.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TextureViewer.dir/Src/RenderTools/TextureViewer/TextureViewer.cpp.o -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Src/RenderTools/TextureViewer/TextureViewer.cpp

third-party/bgfx/CMakeFiles/TextureViewer.dir/Src/RenderTools/TextureViewer/TextureViewer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TextureViewer.dir/Src/RenderTools/TextureViewer/TextureViewer.cpp.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Src/RenderTools/TextureViewer/TextureViewer.cpp > CMakeFiles/TextureViewer.dir/Src/RenderTools/TextureViewer/TextureViewer.cpp.i

third-party/bgfx/CMakeFiles/TextureViewer.dir/Src/RenderTools/TextureViewer/TextureViewer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TextureViewer.dir/Src/RenderTools/TextureViewer/TextureViewer.cpp.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Src/RenderTools/TextureViewer/TextureViewer.cpp -o CMakeFiles/TextureViewer.dir/Src/RenderTools/TextureViewer/TextureViewer.cpp.s

# Object files for target TextureViewer
TextureViewer_OBJECTS = \
"CMakeFiles/TextureViewer.dir/Src/RenderTools/TextureViewer/TextureViewer.cpp.o"

# External object files for target TextureViewer
TextureViewer_EXTERNAL_OBJECTS =

third-party/bgfx/TextureViewer: third-party/bgfx/CMakeFiles/TextureViewer.dir/Src/RenderTools/TextureViewer/TextureViewer.cpp.o
third-party/bgfx/TextureViewer: third-party/bgfx/CMakeFiles/TextureViewer.dir/build.make
third-party/bgfx/TextureViewer: third-party/bgfx/Example/libexample-common.a
third-party/bgfx/TextureViewer: third-party/bgfx/libRenderCore.a
third-party/bgfx/TextureViewer: /usr/lib/x86_64-linux-gnu/libSM.so
third-party/bgfx/TextureViewer: /usr/lib/x86_64-linux-gnu/libICE.so
third-party/bgfx/TextureViewer: /usr/lib/x86_64-linux-gnu/libX11.so
third-party/bgfx/TextureViewer: /usr/lib/x86_64-linux-gnu/libXext.so
third-party/bgfx/TextureViewer: /usr/lib/x86_64-linux-gnu/libOpenGL.so
third-party/bgfx/TextureViewer: /usr/lib/x86_64-linux-gnu/libGLX.so
third-party/bgfx/TextureViewer: /usr/lib/x86_64-linux-gnu/libGLU.so
third-party/bgfx/TextureViewer: third-party/bgfx/External/bimg/libbimg.a
third-party/bgfx/TextureViewer: third-party/bgfx/External/bimg/libastc-codec.a
third-party/bgfx/TextureViewer: third-party/bgfx/External/bimg/libastc.a
third-party/bgfx/TextureViewer: third-party/bgfx/External/bimg/libedtaa3.a
third-party/bgfx/TextureViewer: third-party/bgfx/External/bimg/libetc1.a
third-party/bgfx/TextureViewer: third-party/bgfx/External/bimg/libetc2.a
third-party/bgfx/TextureViewer: third-party/bgfx/External/bimg/libiqa.a
third-party/bgfx/TextureViewer: third-party/bgfx/External/bimg/libsquish.a
third-party/bgfx/TextureViewer: third-party/bgfx/External/bimg/libnvtt.a
third-party/bgfx/TextureViewer: third-party/bgfx/External/bimg/libpvrtc.a
third-party/bgfx/TextureViewer: third-party/bgfx/External/bimg/libtinyexr.a
third-party/bgfx/TextureViewer: third-party/bgfx/Example/libdear-imgui.a
third-party/bgfx/TextureViewer: third-party/bgfx/External/bx/libbx.a
third-party/bgfx/TextureViewer: third-party/bgfx/External/meshoptimizer/libmeshoptimizer.a
third-party/bgfx/TextureViewer: third-party/bgfx/CMakeFiles/TextureViewer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TextureViewer"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TextureViewer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
third-party/bgfx/CMakeFiles/TextureViewer.dir/build: third-party/bgfx/TextureViewer

.PHONY : third-party/bgfx/CMakeFiles/TextureViewer.dir/build

third-party/bgfx/CMakeFiles/TextureViewer.dir/clean:
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx && $(CMAKE_COMMAND) -P CMakeFiles/TextureViewer.dir/cmake_clean.cmake
.PHONY : third-party/bgfx/CMakeFiles/TextureViewer.dir/clean

third-party/bgfx/CMakeFiles/TextureViewer.dir/depend:
	cd /home/tliao/Documents/BrainGenix-ERS/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tliao/Documents/BrainGenix-ERS /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx /home/tliao/Documents/BrainGenix-ERS/Build /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/CMakeFiles/TextureViewer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third-party/bgfx/CMakeFiles/TextureViewer.dir/depend

