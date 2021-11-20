//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the window input processor.
    Additonal Notes: None
    Date Created: 2021-11-02
*/

#pragma once

// Third-Party Libraries (BG convention: use <> instead of "")
#include <GLFW/glfw3.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <NoClip.h>


void ProcessInput(GLFWwindow* Window, LoggerClass *Logger_, ERS_OBJECT_CAMERA_NOCLIP *Camera, float DeltaTime);
