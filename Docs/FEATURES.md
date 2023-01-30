# Feature List

## Windows
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



  
  
  
  
