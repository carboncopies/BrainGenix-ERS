//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the window input processor.
    Additonal Notes: None
    Date Created: 2021-11-02
*/

#pragma once

void ProcessInput(GLFWwindow* Window, LoggerClass *Logger_, ERS_OBJECT_CAMERA_NOCLIP *Camera, float DeltaTime);

#include "Core/Renderer/VisualRenderer/WindowInputProcessor.cpp"