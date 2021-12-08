//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the renderer manager.
    Additonal Notes: None
    Date Created: 2021-11-01
*/

#pragma once

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <VisualRenderer.h>
#include <IOManager.h>
#include <NoClip.h>

#include <ShaderLoader.h>
#include <Framebuffer.h>
#include <GUI.h>

#include <3DCursor.h>


static ERS_OBJECT_CAMERA_NOCLIP Camera_(glm::vec3(0.0f, 0.0f, 3.0f));


/**
 * @brief This class manages all the rendering systems including the visual, auditory and other sensory rendering systems. 
 * 
 */
class RendererManager {

    private:

        // Member Variables
        YAML::Node *SystemConfiguration_; /**<Pointer to the system configuration YAML::Node*/
        LoggerClass *Logger_; /**<Pointer to the logging system instance*/
        VisualRenderer *VisualRenderer_; /**<Pointer To VisualRenderer Instance*/
        IOManager *IOManager_; /**<Pointer To IOManager Instance*/
        GLFWwindow* Window_; /**<GLFW Window Instance*/
        ShaderLoader *ShaderLoader_; /**<Pointer To Shader Loader Instnace*/
        FramebufferManager *FramebufferManager_; /**<Pointer To Framebuffer Manager Instnace*/
        ERS_OBJECT_SHADER Shader_; /**<ERS Shader Object (Main System Shader)*/
        GUISystem *GuiSystem_; /**<Instance of GUI System*/
        TextureLoader *TextureLoader_; /**<Pointer to Texture Loader Instance*/
        SceneManager *SceneManager_; /**<Pointer to Scene Manager Class Instance*/
        Cursors3D *Cursors3D_; /**<Setup 3D Cursor Class*/


        // Control Values
        bool *SystemShouldRun_; /**<Control Variable Indicating System Run State */
        int WindowWidth_; /**<GLFW Window Width Varaible*/
        int WindowHeight_; /**<GLFW Window Height Varaible*/
        const char* WindowTitle_; /**GLFW Window Title Variable*/


        /**
         * @brief Initialize And Create A GLFW Window
         * 
         */
        void InitializeGLFW();


    public:

        /**
         * @brief Initializes all renderers that have been enabled in the configuration file.
         * 
         * @param SystemConfiguration 
         * @param Logger 
         * @param SystemShouldRun 
         */
        RendererManager(YAML::Node *SystemConfiguration, LoggerClass *Logger, bool *SystemShouldRun);

        /**
         * @brief Shuts down the renderers and cleans up variables.
         * 
         */
        ~RendererManager();

        /**
         * @brief Called by the main loop, updates all rendered outputs.
         * 
         */
        void UpdateLoop(float DeltaTime);




};

