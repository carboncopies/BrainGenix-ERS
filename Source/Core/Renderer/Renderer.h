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
#include <GLFW/glfw3.h>




#include "Core/Renderer/VisualRenderer/WindowInputProcessor.h"
#include "Core/Renderer/VisualRenderer/ShaderManager.h"
#include "Core/Structures/Model/Model.h"
#include "Core/Structures/Cameras/NoClip/NoClip.h"
#include "Core/Structures/Scene/Scene.h"
#include "Core/Loader/Scene/SceneDecoder.h"

// Initialize
bool FirstMouse = true;

float LastX = 800/2.0f;
float LastY = 600/2.0f;

ERS_OBJECT_CAMERA_NOCLIP Camera_(glm::vec3(0.0f, 0.0f, 3.0f));


// INPUT CALLBACK FUNCTIONS
void FramebufferSizeCallback(GLFWwindow* /*Window*/, int Width, int Height) {

    // Update Viewport
    glViewport(0,0, Width, Height);

}

void MouseCallback(GLFWwindow* /*Window*/, double XPos, double YPos) {

    // Update Positions
    if (FirstMouse) {

        LastX = XPos;
        LastY = YPos;

        FirstMouse = false;

    }

    // Calculate Offsets
    float XOffset = XPos - LastX;
    float YOffset = YPos - LastY;

    // Update Last Positions
    LastX = XPos;
    LastY = YPos;

    // Process Camera Movement
    Camera_.ProcessMouseMovement(XOffset, YOffset);



}

void ScrollCallback(GLFWwindow* /*Window*/, double /*XOffset*/, double YOffset) {

    Camera_.ProcessMouseScroll(YOffset);

}

class Renderer {

    private:

        // Member Variables
        YAML::Node *SystemConfiguration_;
        LoggerClass *Logger_;
        ERS_OBJECT_SHADER Shader_;
        ERS_OBJECT_MODEL Model_;
        ERS_STRUCTURE_SCENE Scene_;



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
        void LoadAssets();



    public:

        void InitializeRenderer(YAML::Node *SystemConfiguration, LoggerClass *Logger);

        bool UpdateLoop();

        void CleanUp();


};


#include "Core/Renderer/Renderer.cpp"
