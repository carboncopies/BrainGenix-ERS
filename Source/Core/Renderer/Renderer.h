//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the openGL Renderer.
    Additonal Notes: None
    Date Created: 2021-11-01
*/

#pragma once


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include "Core/Loader/BGAsset/BGAssetLoader.h"
#include "Core/Structures/DataBuffer/DataBuffer.h"
#include "Core/Renderer/VisualRenderer/WindowInputProcessor.h"
#include "Core/Renderer/VisualRenderer/ShaderManager.h"
#include "../Structures/Model/Model.h"
#include "../Structures/Cameras/NoClip/NoClip.h"
#include "../Structures/Scene/Scene.h"
#include "../Loader/Scene/SceneDecoder.h"
#include "../Management/LoggingSystem.h"

// Initialize
static bool FirstMouse = true;

static float LastX = 800/2.0f;
static float LastY = 600/2.0f;

static ERS_OBJECT_CAMERA_NOCLIP Camera_(glm::vec3(0.0f, 0.0f, 3.0f));



/**
 * @brief This class manages all the rendering systems including the visual, auditory and other sensory rendering systems. 
 * 
 */
class Renderer {

    private:

        // Member Variables
        YAML::Node *SystemConfiguration_;
        LoggerClass *Logger_;
        AssetLoader *AssetLoader_;

        // Control Values
        bool *SystemShouldRun_;


        ERS_OBJECT_SHADER Shader_;
        ERS_OBJECT_MODEL Model_;




        GLFWwindow* Window_;
        int WindowWidth_;
        int WindowHeight_;
        const char* WindowTitle_;

        int RenderWidth_;
        int RenderHeight_;

        
        // Timing
        float DeltaTime = 0.0f;
        float LastFrame = 0.0f;




        // Member Functions
        void InitializeGLFW();
        void InitializeOpenGL();



    public:

        void InitializeRenderer(YAML::Node *SystemConfiguration, LoggerClass *Logger, bool *SystemShouldRun, AssetLoader *AssetLoader);
        void UpdateLoop();
        void CleanUp();


};



