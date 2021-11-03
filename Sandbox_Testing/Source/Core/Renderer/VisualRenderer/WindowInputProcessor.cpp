//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the window input processor.
    Additonal Notes: None
    Date Created: 2021-11-02
*/

#include "Core/Renderer/VisualRenderer/WindowInputProcessor.h"

void ProcessInput(GLFWwindow* Window, LoggerClass *Logger_) {

    if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        Logger_->Log("Window Shutdown Invoked By Keyboard [ESC]", 2);
        glfwSetWindowShouldClose(Window, true);
    }

}
