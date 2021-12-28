//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the renderer manager.
    Additonal Notes: None
    Date Created: 2021-11-01
*/

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
#include <LoggingSystem.h>
#include <VisualRenderer.h>
#include <IOManager.h>
#include <NoClip.h>

#include <ShaderLoader.h>
#include <Framebuffer.h>
#include <GUI.h>

#include <ERS_STRUCT_IOData.h>
#include <ERS_ModelWriter.h>
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_ModelLoader.h>

#include <3DCursor.h>



static ERS_OBJECT_CAMERA_NOCLIP Camera_(glm::vec3(0.0f, 0.0f, 3.0f));


/**
 * @brief This class manages all the rendering systems including the visual, auditory and other sensory rendering systems. 
 * 
 */
class RendererManager {

    private:

        // Member Variables
        std::shared_ptr<VisualRenderer> VisualRenderer_; /**<Pointer To VisualRenderer Instance*/
        std::shared_ptr<IOManager> IOManager_; /**<Pointer To IOManager Instance*/
        GLFWwindow* Window_; /**<GLFW Window Instance*/
        std::shared_ptr<ShaderLoader> ShaderLoader_; /**<Pointer To Shader Loader Instnace*/
        std::shared_ptr<FramebufferManager> FramebufferManager_; /**<Pointer To Framebuffer Manager Instnace*/
        ERS_OBJECT_SHADER Shader_; /**<ERS Shader Object (Main System Shader)*/
        std::shared_ptr<GUISystem> GuiSystem_; /**<Instance of GUI System*/
        std::shared_ptr<TextureLoader> TextureLoader_; /**<Pointer to Texture Loader Instance*/
        std::shared_ptr<SceneManager> SceneManager_; /**<Pointer to Scene Manager Class Instance*/
        std::shared_ptr<Cursors3D> Cursors3D_; /**<Setup 3D Cursor Class*/
        std::shared_ptr<ERS_CLASS_ModelLoader> ModelLoader_; /**ModelLoader Class*/
        
        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Copy Of Pointer Helper Struct*/

        std::chrono::high_resolution_clock Clock_; /**<High Res Clock Used For Frame Time Calcs*/

        // Control Values
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
        RendererManager(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);

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

