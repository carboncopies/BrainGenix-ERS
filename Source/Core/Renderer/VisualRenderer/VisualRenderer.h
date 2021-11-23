//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the visual renderer.
    Additonal Notes: None
    Date Created: 2021-11-20
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
#include <Model.h>
#include <NoClip.h>
#include <TextureLoader.h>
#include <ModelLoader.h>
#include <ModelManager.h>
#include <SceneLoader.h>


class VisualRenderer {

    private:

        // Member Variables
        YAML::Node *SystemConfiguration_; /**<Pointer to the system configuration YAML::Node*/
        LoggerClass *Logger_; /**<Pointer to the logging system instance*/

        // MOVE TO ASSET LOADER CLASS LATER:
        TextureLoader *TextureLoader_; /**<Pointer to Texture Loader Instance*/

        // ModelManager Class
        ModelManager *ModelManager_; /**<Pointer to Model Manager Class Instance*/

        // Control Values
        bool *SystemShouldRun_;


        ERS_OBJECT_SHADER Shader_;
        ERS_OBJECT_SCENE Scene_;




        GLFWwindow* Window_;
        int WindowWidth_;
        int WindowHeight_;
        const char* WindowTitle_;

        int RenderWidth_;
        int RenderHeight_;

        
        // Timing
        float DeltaTime = 0.0f;
        float LastFrame = 0.0f;

        // Internal Functions
        void InitializeGLFW();
        void InitializeOpenGL();

    public:

        // Constructor
        VisualRenderer(YAML::Node *SystemConfiguration, LoggerClass *Logger, bool *SystemShouldRun);


        // Destructor
        ~VisualRenderer();

        // Update Loop Func
        void UpdateLoop();

        

};
