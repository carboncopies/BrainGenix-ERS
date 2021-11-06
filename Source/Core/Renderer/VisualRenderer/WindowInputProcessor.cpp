//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the window input processor.
    Additonal Notes: None
    Date Created: 2021-11-02
*/



void ProcessInput(GLFWwindow* Window, LoggerClass *Logger_, ERS_OBJECT_CAMERA_NOCLIP *Camera, float DeltaTime) {

    if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        Logger_->Log("Window Shutdown Invoked By Keyboard [ESC]", 2);
        glfwSetWindowShouldClose(Window, true);
    }

    if (glfwGetKey(Window, GLFW_KEY_W) == GLFW_PRESS)
        Camera->ProcessKeyboard(FORWARD, DeltaTime);
    if (glfwGetKey(Window, GLFW_KEY_S) == GLFW_PRESS)
        Camera->ProcessKeyboard(BACKWARD, DeltaTime);
    if (glfwGetKey(Window, GLFW_KEY_A) == GLFW_PRESS)
        Camera->ProcessKeyboard(LEFT, DeltaTime);
    if (glfwGetKey(Window, GLFW_KEY_D) == GLFW_PRESS)
        Camera->ProcessKeyboard(RIGHT, DeltaTime);

}



