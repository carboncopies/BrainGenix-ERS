![Build](https://github.com/carboncopies/BrainGenix-ERS/actions/workflows/cmake.yml/badge.svg)


![Image](https://user-images.githubusercontent.com/49183477/193433511-1276948e-29e8-43d0-8c5e-8f87e097fec9.png)



# Build Instructions

## Linux:

  It's pretty easy to build on linux and has been tested with Debian/Ubuntu to work. This is the primary development platform used, and such tends to work the best. 
  
  Simply enter the `Tools` directory and run `sudo bash Install.sh` followed by `bash Build.sh 4`. The build command can be adjusted to fit the number of cpu cores that your system has by changing the argument. If you don't know how many CPU cores your system has, just leave the command as is. If something isn't working quite right for you, you can try cleaning the build with `bash Clean.sh`.

  If some packages are missing on your distro, you'll have to substitute with whatever your distro uses. We try to include as many packages in our codebase as possible via superbuilds, but this isn't always possible or practical.


## Windows:

  Since we don't develop on Windows, builds aren't guarenteed to work. With that said, they *should* work most of the time.   
  
  **Note: Having windows set to a non english language seems to break includes for some reason.** We really wish that this wasn't an issue but it seems to be a problem for whatever reason. Apologies for the inconvenience.

  - Open Visual Stuido 2019 (Has to be this version)
  - Install python 3.9.5 (needed to link with the interpreter, embeddable version already included in project tree, also restart your machine after installing to avoid issues) (If just installing, make sure to restart after to make it show up in visual studio)
  - Clone the repository but note that you'll probably have to put it into a root level directory on your disk. This is because Microsoft has imposed a 260 character file name limit in their compiler. 
  - Open the CMakeLists.txt file, and generate the configuration
  - Put your build config into "Release", currently debug doesn't work for some reason.
  - Set target to BrainGenix-ERS.exe
  - Hit `Build`
  
  If you encounter issues finding the python libraries after you've installed them, try clearing your cmake cache.

## Mac:
  
  - NOTE: You must have a version of OSX that is greater than 10.15.0 as the <filesystem> header is broken on earlier versions of the OS.
  
  - Install one of the following:
    - [Ubuntu](https://ubuntu.com/download)
    - [Debian](https://www.debian.org/distrib/)
    - [Fedora](https://getfedora.org/workstation/download/)
  - Follow Linux build instructions

# Keybinds

  ## Editor Viewport

    "[lmb]" - (When Hovering Gizmo) - Move Gizmo
    "[left shift]" - (When Gizmo Active) - Move Camera While Moving Gizmo
    "[esc]" - (When Gizmo Active) - Abort Current Movement
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
    "PosX" - X Position of the model
    "PosY" - Y Position of the model
    "PosZ" - Z Position of the model
    "RotX" - X Rotation of the model
    "RotY" - Y Rotation of the model
    "RotZ" - Z Rotation of the model
    "ScaleX" - X Scale of the model
    "ScaleY" - Y Scale of the model
    "ScaleZ" - Z Scale of the model
    "Enabled" - Enable/Disable rendering of the model

  ## Point Light Variables
    "PosX" - X Position of the light
    "PosY" - Y Position of the light
    "PosZ" - Z Position of the light
    "ColorR" - Red component of Color(from scale of 0 to 1)
    "ColorG" - Green component of color (from scale of 0 to 1)
    "ColorB" - Blue component of color (from scale of 0 to 1)
    "Intensity" - brighness of the light (float)
    "MaxDistance" - maximum distance of the light after which the scene will not be affected (float)
    "RolloffConstant" - Constant component of light rolloff (float)
    "RolloffLinear" - Linear component of light rolloff (float)
    "RolloffQuadratic" - Quadratic component of light rolloff (float)
    
  ## Directional Light Variables
    "DirectionalLightPosX" - X Position of the light
    "DirectionalLightPosY" - Y Position of the light
    "DirectionalLightPosZ" - Z Position of the light
    "DirectionalLightRotX" - X Rotation of the light
    "DirectionalLightRotY" - Y Rotation of the light
    "DirectionalLightRotZ" - Z Rotation of the light
    "DirectionalLightIntensity" - brighness of the light (float)
    "DirectionalLightMaxDistance" - maximum distance of the light after which the scene will not be affected (float)
    "DirectionalLightColorR" - Red component of color (from scale of 0 to 1)
    "DirectionalLightColorG" - Green component of color (from scale of 0 to 1)
    "DirectionalLightColorB" - Blue component of color (from scale of 0 to 1)

  ## Spot Light Variables
    "PosX" - X Position of the light
    "PosY" - Y Position of the light
    "PosZ" - Z Position of the light
    "RotX" - X Rotation of the light
    "RotY" - Y Rotation of the light
    "RotZ" - Z Rotation of the light
    "ColorR" - Red component of color (from scale of 0 to 1)
    "ColorG" - Green component of color (from scale of 0 to 1)
    "ColorB" - Blue component of color (from scale of 0 to 1)
    "Intensity" - brighness of the light (float)
    "MaxDistance" - maximum distance of the light after which the scene will not be affected (float)
    "Cutoff" - Angle of area affected in degrees (float)
    "Rolloff" - Rolloff angle in degrees (float)

  ## Camera Variables
    "PosX" - X Position of the camera
    "PosY" - Y Position of the camera
    "PosZ" - Z Position of the camera
    "RotX" - X Rotation of the camera
    "RotY" - Y Rotation of the camera
    "RotZ" - Z Rotation of the camera
    "ScaleX" - X Scale of the camera
    "ScaleY" - Y Scale of the camera
    "ScaleZ" - Z Scale of the camera
    
