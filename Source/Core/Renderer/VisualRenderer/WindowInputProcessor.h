//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the window input processor.
    Additonal Notes: None
    Date Created: 2021-11-02
*/

#pragma once

#include "LoggingSystem.h"
#include "NoClip.h"


#include <GLFW/glfw3.h>

void ProcessInput(GLFWwindow* Window, LoggerClass *Logger_, ERS_OBJECT_CAMERA_NOCLIP *Camera, float DeltaTime);
