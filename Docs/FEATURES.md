# Feature List

## Windows
- [Scene Tree](#scene-tree) (Allows managing the scene and objects/lights)
- [System Log](#system-log) (Shows log)
- [Asset Explorer](#asset-explorer) (Shows list of available assets)
- [Object Properties](#object-properties) (Enables user management of scene object properties)

- [Script Editor](#script-editor) (Editor for scripts)
- [Shder Editpr](#shader-editor) (Window for editing shader code (GLSL))
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
  
  
  
  
  
  
  
