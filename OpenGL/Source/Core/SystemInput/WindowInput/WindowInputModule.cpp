//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for the main render loop
    Additonal Notes: None
    Date Created: 2021-09-22
*/


#include "Core/Renderer/Camera/Noclip/NoclipCameraModule.h"


class WindowInputClass {

    // Declare Variables
    float ScreenWidth;
    float ScreenHeight;
    GLFWwindow *Window;
    Camera CameraInstance;
    
    float lastX;
    float lastY;
    
    float x,y;

    // Initialization Parameters
    bool firstMouse = true;


    public:

        WindowInputClass(float ScreenWidthInput, float ScreenHeightInput, GLFWwindow *WindowInput, Camera CameraInput) {

            // Define Variables
            ScreenWidth = ScreenWidthInput;
            ScreenHeight = ScreenHeightInput;

            Window = WindowInput;
            CameraInstance = CameraInput;

            
            // Set Mouse Window Definitions
            lastX = ScreenWidth / 2.0f;
            lastY = ScreenHeight / 2.0f;



        }

        void ProcessKeyboardWindowInput(float DeltaTime) {

            // Set Escape Key To Exit
            if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {        
                glfwSetWindowShouldClose(Window, true);
            }

            if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS) 
                CameraInstance.ProcessKeyboard("FORWARD", DeltaTime);
            if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
                CameraInstance.ProcessKeyboard("BACKWARD", DeltaTime);
            if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
                CameraInstance.ProcessKeyboard("LEFT", DeltaTime);
            if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
                CameraInstance.ProcessKeyboard("RIGHT", DeltaTime);

        }
        

        //glfw: whenever the mouse moves, this callback is called
        //-------------------------------------------------------
        void ProcessMouseButtonWindowInput(GLFWwindow* Window, double xpos, double ypos)
        {
            if (firstMouse)
            {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

            lastX = xpos;
            lastY = ypos;

            CameraInstance.ProcessMouseMovement(xoffset, yoffset);
        }



        //glfw: whenever the mouse scroll wheel scrolls, this callback is called
        //----------------------------------------------------------------------
        void ProcessMouseScrollWindowInput(GLFWwindow* window, double xoffset, double yoffset)
        {
            CameraInstance.ProcessMouseScroll(yoffset);
        }


};