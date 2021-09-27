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
include third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/depend.make

# Include the progress variables for this target.
include third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/progress.make

# Include the compile flags for this target's objects.
include third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/flags.make

../third-party/bgfx/Example/RenderExample/runtime/shaders/essl/fs_vt_mip.bin: ../third-party/bgfx/Example/RenderExample/40-svt/fs_vt_mip.sc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Compiling shader 40-svt/fs_vt_mip.sc for ESSL, GLSL, SPIRV"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && ../ShaderCompiler -f /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/fs_vt_mip.sc -i /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bgfx/src -o /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/shaders/essl/fs_vt_mip.bin --platform android --type fragment
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && ../ShaderCompiler -f /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/fs_vt_mip.sc -i /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bgfx/src -o /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/shaders/glsl/fs_vt_mip.bin --platform linux --type fragment --profile 120
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && ../ShaderCompiler -f /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/fs_vt_mip.sc -i /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bgfx/src -o /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/shaders/spirv/fs_vt_mip.bin --platform linux --type fragment --profile spirv

../third-party/bgfx/Example/RenderExample/runtime/shaders/glsl/fs_vt_mip.bin: ../third-party/bgfx/Example/RenderExample/runtime/shaders/essl/fs_vt_mip.bin
	@$(CMAKE_COMMAND) -E touch_nocreate ../third-party/bgfx/Example/RenderExample/runtime/shaders/glsl/fs_vt_mip.bin

../third-party/bgfx/Example/RenderExample/runtime/shaders/spirv/fs_vt_mip.bin: ../third-party/bgfx/Example/RenderExample/runtime/shaders/essl/fs_vt_mip.bin
	@$(CMAKE_COMMAND) -E touch_nocreate ../third-party/bgfx/Example/RenderExample/runtime/shaders/spirv/fs_vt_mip.bin

../third-party/bgfx/Example/RenderExample/runtime/shaders/essl/fs_vt_unlit.bin: ../third-party/bgfx/Example/RenderExample/40-svt/fs_vt_unlit.sc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Compiling shader 40-svt/fs_vt_unlit.sc for ESSL, GLSL, SPIRV"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && ../ShaderCompiler -f /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/fs_vt_unlit.sc -i /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bgfx/src -o /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/shaders/essl/fs_vt_unlit.bin --platform android --type fragment
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && ../ShaderCompiler -f /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/fs_vt_unlit.sc -i /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bgfx/src -o /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/shaders/glsl/fs_vt_unlit.bin --platform linux --type fragment --profile 120
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && ../ShaderCompiler -f /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/fs_vt_unlit.sc -i /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bgfx/src -o /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/shaders/spirv/fs_vt_unlit.bin --platform linux --type fragment --profile spirv

../third-party/bgfx/Example/RenderExample/runtime/shaders/glsl/fs_vt_unlit.bin: ../third-party/bgfx/Example/RenderExample/runtime/shaders/essl/fs_vt_unlit.bin
	@$(CMAKE_COMMAND) -E touch_nocreate ../third-party/bgfx/Example/RenderExample/runtime/shaders/glsl/fs_vt_unlit.bin

../third-party/bgfx/Example/RenderExample/runtime/shaders/spirv/fs_vt_unlit.bin: ../third-party/bgfx/Example/RenderExample/runtime/shaders/essl/fs_vt_unlit.bin
	@$(CMAKE_COMMAND) -E touch_nocreate ../third-party/bgfx/Example/RenderExample/runtime/shaders/spirv/fs_vt_unlit.bin

../third-party/bgfx/Example/RenderExample/runtime/shaders/essl/vs_vt_generic.bin: ../third-party/bgfx/Example/RenderExample/40-svt/vs_vt_generic.sc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Compiling shader 40-svt/vs_vt_generic.sc for ESSL, GLSL, SPIRV"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && ../ShaderCompiler -f /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/vs_vt_generic.sc -i /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bgfx/src -o /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/shaders/essl/vs_vt_generic.bin --platform android --type vertex
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && ../ShaderCompiler -f /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/vs_vt_generic.sc -i /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bgfx/src -o /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/shaders/glsl/vs_vt_generic.bin --platform linux --type vertex --profile 120
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && ../ShaderCompiler -f /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/vs_vt_generic.sc -i /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bgfx/src -o /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/shaders/spirv/vs_vt_generic.bin --platform linux --type vertex --profile spirv

../third-party/bgfx/Example/RenderExample/runtime/shaders/glsl/vs_vt_generic.bin: ../third-party/bgfx/Example/RenderExample/runtime/shaders/essl/vs_vt_generic.bin
	@$(CMAKE_COMMAND) -E touch_nocreate ../third-party/bgfx/Example/RenderExample/runtime/shaders/glsl/vs_vt_generic.bin

../third-party/bgfx/Example/RenderExample/runtime/shaders/spirv/vs_vt_generic.bin: ../third-party/bgfx/Example/RenderExample/runtime/shaders/essl/vs_vt_generic.bin
	@$(CMAKE_COMMAND) -E touch_nocreate ../third-party/bgfx/Example/RenderExample/runtime/shaders/spirv/vs_vt_generic.bin

third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/RenderExample/40-svt/svt.cpp.o: third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/flags.make
third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/RenderExample/40-svt/svt.cpp.o: ../third-party/bgfx/Example/RenderExample/40-svt/svt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/RenderExample/40-svt/svt.cpp.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example-40-svt.dir/RenderExample/40-svt/svt.cpp.o -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/svt.cpp

third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/RenderExample/40-svt/svt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example-40-svt.dir/RenderExample/40-svt/svt.cpp.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/svt.cpp > CMakeFiles/example-40-svt.dir/RenderExample/40-svt/svt.cpp.i

third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/RenderExample/40-svt/svt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example-40-svt.dir/RenderExample/40-svt/svt.cpp.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/svt.cpp -o CMakeFiles/example-40-svt.dir/RenderExample/40-svt/svt.cpp.s

third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/RenderExample/40-svt/vt.cpp.o: third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/flags.make
third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/RenderExample/40-svt/vt.cpp.o: ../third-party/bgfx/Example/RenderExample/40-svt/vt.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/RenderExample/40-svt/vt.cpp.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example-40-svt.dir/RenderExample/40-svt/vt.cpp.o -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/vt.cpp

third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/RenderExample/40-svt/vt.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example-40-svt.dir/RenderExample/40-svt/vt.cpp.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/vt.cpp > CMakeFiles/example-40-svt.dir/RenderExample/40-svt/vt.cpp.i

third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/RenderExample/40-svt/vt.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example-40-svt.dir/RenderExample/40-svt/vt.cpp.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/40-svt/vt.cpp -o CMakeFiles/example-40-svt.dir/RenderExample/40-svt/vt.cpp.s

# Object files for target example-40-svt
example__40__svt_OBJECTS = \
"CMakeFiles/example-40-svt.dir/RenderExample/40-svt/svt.cpp.o" \
"CMakeFiles/example-40-svt.dir/RenderExample/40-svt/vt.cpp.o"

# External object files for target example-40-svt
example__40__svt_EXTERNAL_OBJECTS =

third-party/bgfx/Example/example-40-svt: third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/RenderExample/40-svt/svt.cpp.o
third-party/bgfx/Example/example-40-svt: third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/RenderExample/40-svt/vt.cpp.o
third-party/bgfx/Example/example-40-svt: third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/build.make
third-party/bgfx/Example/example-40-svt: third-party/bgfx/Example/libexample-common.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/libRenderCore.a
third-party/bgfx/Example/example-40-svt: /usr/lib/x86_64-linux-gnu/libSM.so
third-party/bgfx/Example/example-40-svt: /usr/lib/x86_64-linux-gnu/libICE.so
third-party/bgfx/Example/example-40-svt: /usr/lib/x86_64-linux-gnu/libX11.so
third-party/bgfx/Example/example-40-svt: /usr/lib/x86_64-linux-gnu/libXext.so
third-party/bgfx/Example/example-40-svt: /usr/lib/x86_64-linux-gnu/libOpenGL.so
third-party/bgfx/Example/example-40-svt: /usr/lib/x86_64-linux-gnu/libGLX.so
third-party/bgfx/Example/example-40-svt: /usr/lib/x86_64-linux-gnu/libGLU.so
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/bimg/libbimg.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/bimg/libastc-codec.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/bimg/libastc.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/bimg/libedtaa3.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/bimg/libetc1.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/bimg/libetc2.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/bimg/libiqa.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/bimg/libsquish.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/bimg/libnvtt.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/bimg/libpvrtc.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/bimg/libtinyexr.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/Example/libdear-imgui.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/bx/libbx.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/External/meshoptimizer/libmeshoptimizer.a
third-party/bgfx/Example/example-40-svt: third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable example-40-svt"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example-40-svt.dir/link.txt --verbose=$(VERBOSE)
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && /usr/bin/cmake -E create_symlink /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/font /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example/font
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && /usr/bin/cmake -E create_symlink /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/images /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example/images
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && /usr/bin/cmake -E create_symlink /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/meshes /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example/meshes
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && /usr/bin/cmake -E create_symlink /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/shaders /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example/shaders
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && /usr/bin/cmake -E create_symlink /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/text /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example/text
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && /usr/bin/cmake -E create_symlink /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example/RenderExample/runtime/textures /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example/textures

# Rule to build all files generated by this target.
third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/build: third-party/bgfx/Example/example-40-svt

.PHONY : third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/build

third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/clean:
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example && $(CMAKE_COMMAND) -P CMakeFiles/example-40-svt.dir/cmake_clean.cmake
.PHONY : third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/clean

third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/depend: ../third-party/bgfx/Example/RenderExample/runtime/shaders/essl/fs_vt_mip.bin
third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/depend: ../third-party/bgfx/Example/RenderExample/runtime/shaders/glsl/fs_vt_mip.bin
third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/depend: ../third-party/bgfx/Example/RenderExample/runtime/shaders/spirv/fs_vt_mip.bin
third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/depend: ../third-party/bgfx/Example/RenderExample/runtime/shaders/essl/fs_vt_unlit.bin
third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/depend: ../third-party/bgfx/Example/RenderExample/runtime/shaders/glsl/fs_vt_unlit.bin
third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/depend: ../third-party/bgfx/Example/RenderExample/runtime/shaders/spirv/fs_vt_unlit.bin
third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/depend: ../third-party/bgfx/Example/RenderExample/runtime/shaders/essl/vs_vt_generic.bin
third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/depend: ../third-party/bgfx/Example/RenderExample/runtime/shaders/glsl/vs_vt_generic.bin
third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/depend: ../third-party/bgfx/Example/RenderExample/runtime/shaders/spirv/vs_vt_generic.bin
	cd /home/tliao/Documents/BrainGenix-ERS/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tliao/Documents/BrainGenix-ERS /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/Example /home/tliao/Documents/BrainGenix-ERS/Build /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third-party/bgfx/Example/CMakeFiles/example-40-svt.dir/depend

