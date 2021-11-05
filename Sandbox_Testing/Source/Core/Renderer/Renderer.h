//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the openGL Renderer.
    Additonal Notes: None
    Date Created: 2021-11-01
*/

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <glad/glad.h>
#include <glad.c>
#include <GLFW/glfw3.h>




#include "Core/Renderer/VisualRenderer/WindowInputProcessor.h"
#include "Core/Renderer/VisualRenderer/ShaderManager.h"
#include "Core/Renderer/VisualRenderer/TextureManager.h"
#include "Core/Renderer/VisualRenderer/Structures/Model/Model.h"
#include "Core/Loader/Decoder/Texture/Texture.h"
#include "Core/Renderer/VisualRenderer/Structures/Cameras/NoClip/NoClip.h"



void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height) {

    // Update Viewport
    glViewport(0,0, Width, Height);

}

class Renderer {

    private:

        // Member Variables
        YAML::Node *SystemConfiguration_;
        LoggerClass *Logger_;
        ERS_OBJECT_SHADER Shader_;
        ERS_OBJECT_MODEL Model_;

        ERS_OBJECT_CAMERA_NOCLIP Camera_(glm::vec3(0.0f, 0.0f, 3.0f));
        



        GLFWwindow* Window_;
        int WindowWidth_;
        int WindowHeight_;
        const char* WindowTitle_;

        int RenderWidth_;
        int RenderHeight_;

        




        // Member Functions
        void InitializeGLFW();
        void InitializeOpenGL();



    public:

        void InitializeRenderer(YAML::Node *SystemConfiguration, LoggerClass *Logger);

        bool UpdateLoop();

        void CleanUp();


};


#include "Core/Renderer/Renderer.cpp"
