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

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <ShaderManager.h>
#include <WindowInputProcessor.h>
#include <Callbacks.h>
#include <DataBuffer.h>
#include <Model.h>
#include <NoClip.h>
#include <Scene.h>







/**
 * @brief This class manages all the rendering systems including the visual, auditory and other sensory rendering systems. 
 * 
 */
class RendererManager {

    private:






        // Member Functions
        void InitializeGLFW();
        void InitializeOpenGL();



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
        void UpdateLoop();




};

