//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for the main render loop
    Additonal Notes: None
    Date Created: 2021-09-22
*/


#include "Core/Renderer/Camera/Noclip/NoclipCameraModule.h"

void ProcessWindowInput(GLFWwindow *Window, Camera Camera) {

    float DeltaTime = 0.1;

    // Set Escape Key To Exit
    if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {        
        glfwSetWindowShouldClose(Window, true);
    }

    if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
        Camera.ProcessKeyboard(FORWARD, DeltaTime);
    if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
        Camera.ProcessKeyboard(BACKWARD, DeltaTime);
    if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
        Camera.ProcessKeyboard(LEFT, DeltaTime);
    if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
        Camera.ProcessKeyboard(RIGHT, DeltaTime);



}
