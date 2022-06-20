//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <iostream>
#include <vector>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")


/**
 * @brief Simple struct used to pass in user parameters to the callback function.
 * 
 */
struct ERS_STRUCT_MessageCallbackParam {

    void* Logger_;
    void* OpenGLLoggingSystem_;

    int* MinLogLevel;

};