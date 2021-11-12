//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the window input processor.
    Additonal Notes: None
    Date Created: 2021-11-02
*/

#pragma once

#include "Core/Management/LoggingSystem.h"
#include "Core/Structures/Cameras/NoClip/NoClip.h"

void ProcessInput(GLFWwindow* Window, LoggerClass *Logger_, ERS_OBJECT_CAMERA_NOCLIP *Camera, float DeltaTime);
