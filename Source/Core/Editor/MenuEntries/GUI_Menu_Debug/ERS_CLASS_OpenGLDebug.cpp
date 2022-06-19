//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_OpenGLDebug.h>


ERS_CLASS_OpenGLDebug::ERS_CLASS_OpenGLDebug(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;


    SystemUtils_->Logger->Log("Initializing OpenGL Debug Menu GUI Subsystem", 5);

    // Set Default Settings
    glDisable(GL_DEBUG_OUTPUT);

}

ERS_CLASS_OpenGLDebug::~ERS_CLASS_OpenGLDebug() {

    SystemUtils->Logger->Log("OpenGL Debug Menu GUI Subsystem Destructor Invoked", 6);

}

