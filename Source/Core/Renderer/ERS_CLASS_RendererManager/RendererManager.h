//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

#include <FreeImage.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <BG/Common/Logger/Logger.h>
#include <VisualRenderer.h>
#include <Camera.h>

#include <ShaderLoader.h>
#include <GUI.h>

#include <ModelWriter.h>
#include <ModelLoader.h>

#include <3DCursor.h>

#include <BG/ERS/IOSubsystem/IOData/IOData.h>
#include <SystemUtils.h>
#include <ProjectUtils.h>
#include <HumanInputDeviceUtils.h>
#include <OpenGLDefaults.h>

#include <Version.h>




/**
 * @brief This class manages all the rendering systems including the visual, auditory and other sensory rendering systems. 
 * 
 */
class RendererManager {

private:

    ERS_STRUCT_SystemUtils*           SystemUtils_  = nullptr; /**<Raw pointer to SystemUtils that is owned by the main() */
    ERS_STRUCT_ProjectUtils*          ProjectUtils_ = nullptr; /**<Copy Of Project Utils Struct*/
    ERS_STRUCT_HumanInputDeviceUtils* HIDUtils_     = nullptr; /**<Copy Of Pointer To HIDM Struct*/
    GLFWwindow*                       Window_       = nullptr; /**<GLFW Window Instance*/


    std::unique_ptr<ERS_CLASS_VisualRenderer>  VisualRenderer_; /**<Pointer To VisualRenderer Instance*/
    std::unique_ptr<ERS_CLASS_ShaderLoader>    ShaderLoader_;   /**<Pointer To Shader Loader Instnace*/
    std::shared_ptr<ERS_STRUCT_Shader>         Shader_;         /**<ERS Shader Object (Main System Shader)*/
    std::shared_ptr<GUISystem>                 GuiSystem_;      /**<Instance of GUI System*/
    std::unique_ptr<Cursors3D>                 Cursors3D_;      /**<Setup 3D Cursor Class*/
    std::unique_ptr<ERS_STRUCT_OpenGLDefaults> OpenGLDefaults_; /**<Pointer To OpenGL Default Textures/Models*/


    // Control Values
    int         WindowWidth_  = 0;       /**<GLFW Window Width Varaible*/
    int         WindowHeight_ = 0;       /**<GLFW Window Height Varaible*/
    std::string WindowTitle_;            /**<GLFW Window Title Variable*/
    bool        OffscreenRendering_ = false; /**<Run the main GLFW context as a hidden off-screen window.*/
    bool        UseEGLContext_ = false; /**<Request an EGL OpenGL context for off-screen rendering.*/
    bool        HeadlessOffscreenMode_ = false; /**<Run the renderer display-free using a standalone EGL context instead of a GLFW window.*/

    // EGL Handles Are Stored As void* So This Header Does Not Need To Include EGL Headers (CLang Format: EGLDisplay/EGLContext/EGLSurface Are All void* Typedefs)
    void*       EGLOffscreenDisplay_ = nullptr; /**<EGLDisplay Of The Display-Free Offscreen Context (HeadlessOffscreenMode_ Only)*/
    void*       EGLOffscreenConfig_  = nullptr; /**<EGLConfig Used To Create The Display-Free Offscreen Context (Passed To Worker Threads So Shared Contexts Use The Identical Config)*/
    void*       EGLOffscreenContext_ = nullptr; /**<EGLContext Of The Display-Free Offscreen Context (HeadlessOffscreenMode_ Only)*/
    void*       EGLOffscreenSurface_ = nullptr; /**<EGLSurface (Tiny Pbuffer, Or EGL_NO_SURFACE Cast) Of The Display-Free Offscreen Context (HeadlessOffscreenMode_ Only)*/
    int         OffscreenEGLDeviceIndex_ = -1; /**<Explicitly Requested EGL Device Index ('-EGLDeviceIndex' Argument Or ERS_EGL_DEVICE_INDEX Environment Variable), -1 Means Auto-Select*/


    /**
     * @brief Initialize And Create A GLFW Window
     * 
     */
    void InitializeGLFW();

    /**
     * @brief Initialize a display-free OpenGL context directly through EGL (no GLFW window). Used by '-Headless offscreen' mode.
     * Aborts ERS startup (after logging a fatal message) when no usable EGL platform or context can be obtained.
     * 
     */
    void InitializeEGLOffscreen();


    /**
     * @brief Load the editor's data such as the icons and other static images/data. Must be called after setting up an opengl context or a segfault will occur.
     * 
     */
    void LoadEditorData();

    /**
     * @brief Loads an icon and returns the path at the id. Remember to init and de-init freeimage before and after this function.
     * 
     * @param Path 
     * @return unsigned int 
     */
    unsigned int LoadEditorIcon(const char* Path);

    /**
     * @brief This function gets the current opengl error status and if there's an issue it reports it into the log.
     * 
     */
    void ReportOpenGLErrors(); 


public:

    /**
     * @brief Initializes all renderers that have been enabled in the configuration file.
     * 
     * @param SystemConfiguration 
     * @param Logger 
     * @param SystemShouldRun 
     */
    RendererManager(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_STRUCT_HumanInputDeviceUtils* HIDUtils);

    /**
     * @brief Shuts down the renderers and cleans up variables.
     * 
     */
    ~RendererManager();

    /**
     * @brief Return whether the renderer is running without a visible window.
     *
     * @return true
     * @return false
     */
    bool IsOffscreenRendering() const { return OffscreenRendering_; }

    /**
     * @brief Return whether the renderer requested an EGL context.
     *
     * @return true
     * @return false
     */
    bool IsUsingEGLContext() const { return UseEGLContext_; }

    /**
     * @brief Return whether the renderer is running display-free with a standalone EGL context ('-Headless offscreen').
     *
     * @return true
     * @return false
     */
    bool IsHeadlessOffscreen() const { return HeadlessOffscreenMode_; }

    /**
     * @brief Called by the main loop, updates all rendered outputs.
     * 
     */
    void UpdateLoop(float DeltaTime);

};
