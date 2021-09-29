//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing window management.
    Additonal Notes: None
    Date Created: 2021-09-29
*/ 
 
#include <GLFW/glfw3.h>

GLFWwindow* CreateWindow(LoggerClass Logger, int WindowX, int WindowH, const char* WindowTitle = "BrainGenix-ERS") {

    // Initialize GLFW
    Logger.Log("Initializng GLFW", 4);
    glfwInit();

    // Create Window
    Logger.Log("Creating GLFW Window", 4);
    GLFWwindow* Window = glfwCreateWindow(WindowX, WindowH, WindowTitle, NULL, NULL);

    // Return Window
    return Window;
}