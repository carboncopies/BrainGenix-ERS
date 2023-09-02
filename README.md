![Build](https://gitlab.braingenix.org/carboncopies/BrainGenix-ERS/badges/master/pipeline.svg?ignore_skipped=true)


![Image](https://user-images.githubusercontent.com/49183477/193433511-1276948e-29e8-43d0-8c5e-8f87e097fec9.png)





# Feature List

Here's a (mostly) up to date list of the currently implemented features.

## Editor Windows
- [Scene Tree](#scene-tree) (Allows managing the scene and objects/lights)
- [System Log](#system-log) (Shows log)
- [Asset Explorer](#asset-explorer) (Shows list of available assets)
- [Object Properties](#object-properties) (Enables user management of scene object properties)
- [Script Editor](#script-editor) (Editor for scripts)
- [Shder Editor](#shader-editor) (Window for editing shader code (GLSL))
- [Color Theme Selector](#color-theme-selector) (Tool to pick color theme for the editor)
- [System Fornt Selector](#system-font-selector) (Tool to select the font used by the editor)
- [Editor Camera Settings](#editor-camera-settings) (Window to select editor camera settings)
- [Rendering Settings](#rendering-settings) (Window to set rendering parameters)
- [Asset Streaming Settings](#asset-streaming-settings) (Window to select the asset streaming settings)
- [Game Controller Settings](#game-controller-settings) (Window to configure the game controller)
- [Viewport Menu](#viewport-menu) (Viewport configuration settings)

### Framerate Monitoring Tools
- Framerate graph (automatically adjusts axes)
- Framerate plot (simpler graph)
- Framerate histogram (even simpler)
- Frame latency graph (Shows lag spikes well)

### System Resource Monitoring Tools
- RAM Graph (Displays free memory in the system)

### Viewports
- Multiple Viewports (Use add viewport button in menu)
- Closing Viewports (Use remove viewport or close viewport with x in window)

### Scene Tree
- Pick active scene
- Select Models with model selector
- Select Lights with light selector
- Select Cameras with camera selector

### System Log
- Lock To bottom (disabling allows you to scroll back in history)
- Clear (empty the log window)
- Restore (restore hidden input)
- Min Log Level Slider (hides log level items below setting)

### Asset Explorer
- Model tab (shows available models to put in scene tree)
- Script tab (shows scripts that can be attached to objects in the scene tree)
- Raw assset IDs tab (shows asset ids in file system)
- Tools tab
- Refresh asset index
- Repair asset index

### Object Properties
- Adjust physical parameters (Position, Rotation, Scale)

Depending on the type of object selected, the window will display different properties:
  #### Model Settings
    - Casts Dynamic Shadows (Enable or disable casting of non-prebaked shadows)
    - Casts Static Shadows (Enable or disable casting of prebaked shadows (doens't do anything yet; prebaked shadows dont exist yet))
    - Receive Shadows (Allow or disallow the object to have shadows cast on it)
    - Treat missing textures as transparent (useful for things with glass on them like clocks or windows, will fix broken textures caused on the glass)
    - Render Model (show/hide this model)
    
    - Minimum LOD (set the lower limit on the level of detail for this model)
    - Maximum LOD (Set the upper limit on the level of detail for this model)
    
    - Object specific shader (allows the user to set a different shader for this model only, picks from dropdown of shaders)
 
  #### Point Light Settings
    - Color picker (light color)
    - Intensity (brightness)
    - Maximum Distance this light will have an effect at
    - Cast shadows (allow this light to cast shadows on objects)
    
  #### Spot Light Settings
    - Color picker (light color)
    - Intensity (brightness)
    - Maximum Distance this light will have an effect at
    - Cutoff Angle (set the outer angle of light attenuation)
    - Rolloff Angle (set the inner angle for light attenuation)
    - Cast shadows (allow this light to cast shadows on objects)
 
  #### Directional Light Settings
    - Color picker (light color)
    - Intensity (brightness)
    - Maximum Distance this light will have an effect at
    - Cast shadows (allow this light to cast shadows on objects)
  
  #### Camera Settings
    - Active Camera (determines what camera is the current active camera)
    - FOV (Set field of view)
    - Near Clip Plane (Set min distance for something to be visible)
    - Far Clip Plane (Set max distance for something to be visible)
    - Asset Streaming Priority (Set priority for this camera to get assets loaded)
    - Enforce Aspect Ratio (forces the camera's aspect ratio to be used, will cause distortion or letterboxing)
    
 #### Scripts
  - Show list of attached scripts to this object
  
 
### Script Editor
- Menu to control editing environment (file, edit, view, etc.)
- Script Tools window to see output from script (errors, etc.)

### Shader Editor
- Mode menu to control type of shader being edited (vertex, fragment, compute, geometry, etc.)
- Text editor to actually edit shader
- Compiler log to show errors generated when using said shader

### Color Theme Selector
- Selection Menu To adjust the way the editor looks
- Apply and reload buttons for applying the theme and reloading themes from disk
- Close button

### System Font Selector
- Selection menu to pick the font for the editor
- Font size slider to adjust font size
- Apply and reload buttons

### Editor Camera Settings
- Viewport Selector (all viewports are independent of eachother)
- Movement speed controls (min/max/current speed) (Note that using the scroll wheel can adjust movement speed)
- Mouse Settings (constrain pitch at -90,90, Mouse sensitivity)
- Location/Rotation Settings (can manually set position and rotation through text input boxes)
- Camera Settings (Near/Far clip, FOV)

### Rendering Settings
- Wireframe mode (only draws outline of polygons)
- Background color (sets the blank bkg color)
- Framerate settings (adjust framerate target, unlock, sync to monitor, etc.)
- Shadow Map settings (resoluton, updates, filter kernel siez, filtering mode, update mode)

### Asset Streaming Settings
- Ram/VRAM cutoff (max distance from camera/viewport after which the textures are at min lod)
- Had quadratic scaling (use quadratic scaling to calc target texture lod)
- Min LOD
- Max LOD
- Max Texture Resolution (pixels)
- VRAM/RAM Budget (target usage in MiB of the system)
- Ram/VRAM warning threshold (min amount of free mem before warning is shown)
- Texture loading threads (number of threads to use for texture loading, is autodetected)
- Texture streaming threads (number of threads to use for tex streaming, is autoset at 1)
- Queue size limit (max size of the queue to load)
- Prevent Duplicate Entry (prevent same model being added to queue twice)
- Queue prioritization (allow inserting into the queue depending on priority)
- Purge Ram/Vram/All (allow the user to force reload textures to various parts of the system)

### Game Controller Settings
- Seems to crash so don't use this for now i guess...

### Viewport Menu
- Controls menu (enable or disable text overlays for various stats, icons, etc.)
- Shader Menu (Set global default shader (can be overridden with model's object specific shader property)
- Grid parameters (set scale, line thickness, colors, etc.)
- Add Menu (add lights, script, scene, camera, etc.)
- Grid Snapping Menu (adjust grid snapping for translation, rotation and scale)
- Run Menu (Allows the user to start or stop scripts/game (can be done with f5 and escape as well)
- Bounding Box Menu (adjust bounding box parameters, depth test, wireframe, mode, etc.)
- Note: Use "`" to toggle this menu on or off



# Build Instructions (For Users)

## Linux:

  It's pretty easy to build on Linux and has been tested with Debian/Ubuntu distros to work. This is the primary development platform used, and therefore tends to work the best. 
  
  Simply enter the `Tools` directory and run `sudo bash Setup.sh` followed by `bash Build.sh [number_of_threads]`. The build command can be adjusted to fit the number of cpu cores that your system has by changing the argument. **If you don't know how many CPU cores your system has, 4 is a good bet.** If you have issues building (machine hanging/freezing or other memory related issues) try lowering this number. ERS can take a *lot* of memory to build, so make sure to lower the number of threads if needed.
  
  If something isn't working quite right for you, you can try cleaning the build with `bash Clean.sh`.

  If some packages are missing on your distro, you'll have to substitute with whatever your distro uses. We try to include as many packages in our codebase as possible via superbuilds, but this isn't always possible or practical.


## Windows:

  At this time, we're not working on native Windows builds since we are working on cross-compiling for Windows platforms from Linux. This will allow us to simplify our build infrastructure significantly. Therefore, ***the following section is out of date and may not work!***


  Since we don't develop on Windows, builds aren't guarenteed to work. With that said, they *should* work most of the time.   
  
  **Note: Having windows set to a non english language seems to break C++ includes for some reason.** We really wish that this wasn't an issue but it seems to be a problem for whatever reason (thanks Microsoft!). Apologies for the inconvenience.

  - Open Visual Stuido 2019 (Has to be this version)
  - Install python 3.9.5 (needed to link with the interpreter, embeddable version already included in project tree, also restart your machine after installing to avoid issues) (If just installing, make sure to restart after to make it show up in visual studio)
  - Clone the repository but note that you'll probably have to put it into a root level directory on your disk. This is because Microsoft has imposed a 260 character file name limit in their compiler. 
  - Open the CMakeLists.txt file, and generate the configuration
  - Put your build config into "Release", currently debug doesn't work for some reason.
  - Set target to BrainGenix-ERS.exe
  - Hit `Build`
  
  If you encounter issues finding the python libraries after you've installed them, try clearing your cmake cache.

## Mac:
  
  - Install one of the following:
    - [Debian](https://www.debian.org/distrib/)
    - [Ubuntu](https://ubuntu.com/download)
  - Follow Linux build instructions


# Development Environment Setup (For Developers)

 - *Step One: Platform*  
We do our development here on Linux based systems, (preferably Debian or Ubuntu).
Please ensure that you have a machine with either (Debian 11 or 12) or (Ubuntu 22.04) installed. A VM may work for all projects except ERS as that requires GPU acceleration (unless you have a VM with GPU passthrough).
Other linux distros may work, but the dependencies may need to be figured out manually (feel free to update the relevant Setup.sh script in the Tools directory though!)
Windows and OSX platforms are not supported and may fail to build.  

 - *Step Two: Cloning and Setting Up*  
For this part, ensure that you have git installed on your machine. This can be installed with `sudo apt install git` on debian distros.
Now, clone the repo for the BG project you’re trying to build. Since the URL is different for every project, it’s not shown here but this would follow the format `git clone [url to project]`. Make sure to change directory `cd` into the place you want to clone the repo. Usually this is your Documents directory but can be whatever you want.
Next, we’ll want to set up the needed dependencies. To do so, simply cd into the Tools directory in the repo. Now, just run `Setup.sh` - note that this will need root privileges to install the needed packages on your system. This will also bootstrap vcpkg which allows us to simplify our build system significantly.  

 - *Step Three: Compiling and Testing*  
Now that we have everything setup, we’re ready to compile the project. This is done with the Build.sh script, simply run this script (keep in mind that you can and probably should pass in an argument with the number of threads to use). If your machine runs out of memory while compiling, simply reduce the number of threads to use while compiling. It’s recommended that you have at least 32gb of memory when compiling - and if not, reduce the number of threads.
Finally we can test that the compiled executable works by running `./Run.sh`. This will run whatever binary was produced for testing.  


Done! You've now successfully setup your build environment. At this point, just install or tweak things how you like and you're all set.


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
    
