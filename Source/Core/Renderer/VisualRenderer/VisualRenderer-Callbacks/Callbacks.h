//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the visual renderer callback functions.
    Documentation Status: Done
    Additonal Notes: None
    Date Created: 2021-11-16
*/

#pragma once

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <NoClip.h>





// Initialize {FIXME LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!}
static bool FirstMouse = true;

static float LastX = 800/2.0f;
static float LastY = 600/2.0f;

static ERS_OBJECT_CAMERA_NOCLIP Camera_(glm::vec3(0.0f, 0.0f, 3.0f));



/**
 * @brief This callback function is used to update the size of the window when a resize event is called.
 * 
 */
static void FramebufferSizeCallback(GLFWwindow* /*Window*/, int Width, int Height);


/**
 * @brief This function is called when a mouse input needs to be processed.
 * 
 */
static void MouseCallback(GLFWwindow* /*Window*/, double XPos, double YPos);

/**
 * @brief This callback processes scroll wheel input.
 * 
 */
static void ScrollCallback(GLFWwindow* /*Window*/, double /*XOffset*/, double YOffset);