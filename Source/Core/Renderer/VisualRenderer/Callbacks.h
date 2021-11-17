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