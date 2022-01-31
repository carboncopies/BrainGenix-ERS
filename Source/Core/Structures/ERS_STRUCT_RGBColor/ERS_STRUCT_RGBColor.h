//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for implementing a struct to simplify includes within classes..
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-16
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory.h>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")


/**
 * @brief This class stores an rgb color value.
 * 
 */
struct ERS_STRUCT_RGBColor {

    int Red; /**<Red Component*/
    int Green; /**<Green Component*/
    int Blue; /**<Blue Component*/


};