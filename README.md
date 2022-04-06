![Build](https://github.com/carboncopies/BrainGenix-ERS/actions/workflows/cmake.yml/badge.svg)

# About

BrainGenix Environment Rendering System (ERS) aims to be a distributed multi-GPU rendering system to implement virtual body and environment simulation functionality. ERS will perform sensory translation to convert simulated sensory data into action potentials that can be sent directly to the emulation. ERS is designed to be used in conjunction with other BrainGenix systems, but can also be used as a standalone game engine. 

# Build Instructions

## Linux:

  It's pretty easy to build on linux and has been tested with Debian/Ubuntu to work. This is the primary development platform used, and such tends to work the best. 
  
  Simply enter the `Tools` directory and run `sudo bash Install-Linux.sh` followed by `bash Build.sh 4`. The build command can be adjusted to fit the number of cpu cores that your system has by changing the argument. If you don't know how many CPU cores your system has, just leave the command as is. If something isn't working quite right for you, you can try cleaning the build with `bash Clean.sh`.

  If some packages are missing on your distro, you'll have to substitute with whatever your distro uses. We try to include as many possible packages in our codebase as possible, but this isn't always possible or practical.


## Windows:

  Since we don't develop on Windows, builds aren't guarenteed to work. With that said, they *should* work most of the time. 
  

  - Open Visual Stuido 2019 (Has to be this version)
  - Clone the repository but note that you'll probably have to put it into a root level directory on your disk. This is because Microsoft has imposed a 260 character file name limit in their compiler. 
  - Open the CMakeLists.txt file, and generate the configuration
  - Put your build config into debug/release based on what you're doing
  - Set target to BrainGenix-ERS.exe
  - Hit `Build`


# Keybinds

  ## Editor Viewport

    "[lmb]" - (When Hovering Gizmo) - Move Gizmo
    "[left shift]" - (When Gizmo Active) - Move Camera While Moving Gizmo
    "[s]" - Set Gizmo To Scale
    "[g]" - Set Gizmo To Translate
    "[r]" - Set Gizmo To Rotate


    "[lmb]" - (When Not Hovering Gizmo) - Enter Camera Movement Mode (hold button)
    "[lmb] + [w]" - Move Camera Forward
    "[lmb] + [a]" - Move Camera Left
    "[lmb] + [s]" - Move Camera Backward
    "[lmb] + [d]" - Move Camera Right
    "[lmb] + [left shift]" - Move Camera Down
    "[lmb] + [space]" - Move Camera Up

    "[lmb] + [scroll wheel]" - Adjust Camera Movement

    "[`]" - Toggle Viewport Controls On/Off

# Scripting API

  The ERS scripting api uses the Python programming language to provide control over models, lights and more. Scripts can be "attached" to an object to allow for programatic control over it's attributes. Plese see the following API reference for more information.
  
  ## System Variables (provided to all scripts)
    "GameTime" - Number of seconds since the start of the game.
    "SystemTime" - Unix epoch as reported by the system.
    
  ## Model Variables
    "ModelPosX" - X Position of the model
    "ModelPosY" - Y Position of the model
    "ModelPosZ" - Z Position of the model
    "ModelRotX" - X Rotation of the model
    "ModelRotY" - Y Rotation of the model
    "ModelRotZ" - Z Rotation of the model
    "ModelScaleX" - X Scale of the model
    "ModelScaleY" - Y Scale of the model
    "ModelScaleZ" - Z Scale of the model
    "ModelEnabled" - Enable/Disable rendering of the model
