//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing GLAD Function Pointers.
    Additonal Notes: None
    Date Created: 2021-09-21
*/  

#include <stdlib.h>



void GLADInitialization(LoggerClass LoggingSystem) {

    // Log GLAD Start //
    LoggingSystem.Log("Initializing GLAD Subsystem", 4);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LoggingSystem.Log("Failed to initialize GLAD, System Exiting", 9);
        exit(-1);
    }

    // Log Initialization Successfull //
    LoggingSystem.Log("GLAD Subsystem Initialization Successfull", 3);
    return;
}