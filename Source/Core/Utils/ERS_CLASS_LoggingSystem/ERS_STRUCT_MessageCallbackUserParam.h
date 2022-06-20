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
#include <ERS_CLASS_LoggingSystem.h>
#include <ERS_CLASS_OpenGLLoggingSystem.h>

struct ERS_STRUCT_MessageCallbackParam {

    ERS_CLASS_LoggingSystem* Logger_;
    ERS_CLASS_OpenGLLoggingSystem* OpenGLLoggingSystem_;

};