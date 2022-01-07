![Build](https://github.com/carboncopies/BrainGenix-ERS/actions/workflows/CMake/badge.svg)

# Build Instructions

## Linux:

  It's pretty easy to build on linux and has been tested with Debian/Ubuntu to work. This is the primary development platform used, and such tends to work the best. 
  
  Simply enter the `Tools` directory and run `sudo bash Install.sh` followed by `bash Build-CMake.sh`. If you're recompiling and your cmake cache has been created, you can simply run `bash Build.sh` to just rebuild what's needed.

  If some packages are missing on your distro, you'll have to substitute with whatever your distro uses. We try to include as many possible packages in our codebase as possible, but this isn't always possible or practical.


## Windows:

  Since we don't develop on Windows, builds aren't guarenteed to work. With that said, they *should* work most of the time. 
  

  - Open Visual Stuido 2019 (Has to be this version)
  - Clone the repository but note that you'll probably have to put it into a root level directory on your disk. This is because Microsoft has imposed a 260 character file name limit in their compiler. 
  - Open the CMakeLists.txt file, and generate the configuration
  - Put your build config into debug/release based on what you're doing
  - Set target to BrainGenix-ERS.exe
  - Hit `Build`
