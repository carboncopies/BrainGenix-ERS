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
include third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/depend.make

# Include the progress variables for this target.
include third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/progress.make

# Include the compile flags for this target's objects.
include third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/flags.make

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/convolve.c.o: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/flags.make
third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/convolve.c.o: ../third-party/bgfx/External/bimg/3rdparty/iqa/source/convolve.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/convolve.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iqa.dir/3rdparty/iqa/source/convolve.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/convolve.c

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/convolve.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iqa.dir/3rdparty/iqa/source/convolve.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/convolve.c > CMakeFiles/iqa.dir/3rdparty/iqa/source/convolve.c.i

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/convolve.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iqa.dir/3rdparty/iqa/source/convolve.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/convolve.c -o CMakeFiles/iqa.dir/3rdparty/iqa/source/convolve.c.s

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/decimate.c.o: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/flags.make
third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/decimate.c.o: ../third-party/bgfx/External/bimg/3rdparty/iqa/source/decimate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/decimate.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iqa.dir/3rdparty/iqa/source/decimate.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/decimate.c

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/decimate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iqa.dir/3rdparty/iqa/source/decimate.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/decimate.c > CMakeFiles/iqa.dir/3rdparty/iqa/source/decimate.c.i

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/decimate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iqa.dir/3rdparty/iqa/source/decimate.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/decimate.c -o CMakeFiles/iqa.dir/3rdparty/iqa/source/decimate.c.s

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/math_utils.c.o: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/flags.make
third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/math_utils.c.o: ../third-party/bgfx/External/bimg/3rdparty/iqa/source/math_utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/math_utils.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iqa.dir/3rdparty/iqa/source/math_utils.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/math_utils.c

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/math_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iqa.dir/3rdparty/iqa/source/math_utils.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/math_utils.c > CMakeFiles/iqa.dir/3rdparty/iqa/source/math_utils.c.i

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/math_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iqa.dir/3rdparty/iqa/source/math_utils.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/math_utils.c -o CMakeFiles/iqa.dir/3rdparty/iqa/source/math_utils.c.s

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/ms_ssim.c.o: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/flags.make
third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/ms_ssim.c.o: ../third-party/bgfx/External/bimg/3rdparty/iqa/source/ms_ssim.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/ms_ssim.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iqa.dir/3rdparty/iqa/source/ms_ssim.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/ms_ssim.c

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/ms_ssim.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iqa.dir/3rdparty/iqa/source/ms_ssim.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/ms_ssim.c > CMakeFiles/iqa.dir/3rdparty/iqa/source/ms_ssim.c.i

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/ms_ssim.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iqa.dir/3rdparty/iqa/source/ms_ssim.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/ms_ssim.c -o CMakeFiles/iqa.dir/3rdparty/iqa/source/ms_ssim.c.s

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/mse.c.o: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/flags.make
third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/mse.c.o: ../third-party/bgfx/External/bimg/3rdparty/iqa/source/mse.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/mse.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iqa.dir/3rdparty/iqa/source/mse.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/mse.c

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/mse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iqa.dir/3rdparty/iqa/source/mse.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/mse.c > CMakeFiles/iqa.dir/3rdparty/iqa/source/mse.c.i

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/mse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iqa.dir/3rdparty/iqa/source/mse.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/mse.c -o CMakeFiles/iqa.dir/3rdparty/iqa/source/mse.c.s

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/psnr.c.o: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/flags.make
third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/psnr.c.o: ../third-party/bgfx/External/bimg/3rdparty/iqa/source/psnr.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/psnr.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iqa.dir/3rdparty/iqa/source/psnr.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/psnr.c

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/psnr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iqa.dir/3rdparty/iqa/source/psnr.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/psnr.c > CMakeFiles/iqa.dir/3rdparty/iqa/source/psnr.c.i

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/psnr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iqa.dir/3rdparty/iqa/source/psnr.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/psnr.c -o CMakeFiles/iqa.dir/3rdparty/iqa/source/psnr.c.s

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/ssim.c.o: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/flags.make
third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/ssim.c.o: ../third-party/bgfx/External/bimg/3rdparty/iqa/source/ssim.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/ssim.c.o"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/iqa.dir/3rdparty/iqa/source/ssim.c.o   -c /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/ssim.c

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/ssim.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iqa.dir/3rdparty/iqa/source/ssim.c.i"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/ssim.c > CMakeFiles/iqa.dir/3rdparty/iqa/source/ssim.c.i

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/ssim.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iqa.dir/3rdparty/iqa/source/ssim.c.s"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg/3rdparty/iqa/source/ssim.c -o CMakeFiles/iqa.dir/3rdparty/iqa/source/ssim.c.s

# Object files for target iqa
iqa_OBJECTS = \
"CMakeFiles/iqa.dir/3rdparty/iqa/source/convolve.c.o" \
"CMakeFiles/iqa.dir/3rdparty/iqa/source/decimate.c.o" \
"CMakeFiles/iqa.dir/3rdparty/iqa/source/math_utils.c.o" \
"CMakeFiles/iqa.dir/3rdparty/iqa/source/ms_ssim.c.o" \
"CMakeFiles/iqa.dir/3rdparty/iqa/source/mse.c.o" \
"CMakeFiles/iqa.dir/3rdparty/iqa/source/psnr.c.o" \
"CMakeFiles/iqa.dir/3rdparty/iqa/source/ssim.c.o"

# External object files for target iqa
iqa_EXTERNAL_OBJECTS =

third-party/bgfx/External/bimg/libiqa.a: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/convolve.c.o
third-party/bgfx/External/bimg/libiqa.a: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/decimate.c.o
third-party/bgfx/External/bimg/libiqa.a: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/math_utils.c.o
third-party/bgfx/External/bimg/libiqa.a: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/ms_ssim.c.o
third-party/bgfx/External/bimg/libiqa.a: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/mse.c.o
third-party/bgfx/External/bimg/libiqa.a: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/psnr.c.o
third-party/bgfx/External/bimg/libiqa.a: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/3rdparty/iqa/source/ssim.c.o
third-party/bgfx/External/bimg/libiqa.a: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/build.make
third-party/bgfx/External/bimg/libiqa.a: third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tliao/Documents/BrainGenix-ERS/Build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking C static library libiqa.a"
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && $(CMAKE_COMMAND) -P CMakeFiles/iqa.dir/cmake_clean_target.cmake
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iqa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/build: third-party/bgfx/External/bimg/libiqa.a

.PHONY : third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/build

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/clean:
	cd /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg && $(CMAKE_COMMAND) -P CMakeFiles/iqa.dir/cmake_clean.cmake
.PHONY : third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/clean

third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/depend:
	cd /home/tliao/Documents/BrainGenix-ERS/Build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tliao/Documents/BrainGenix-ERS /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External/bimg /home/tliao/Documents/BrainGenix-ERS/Build /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg /home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : third-party/bgfx/External/bimg/CMakeFiles/iqa.dir/depend

