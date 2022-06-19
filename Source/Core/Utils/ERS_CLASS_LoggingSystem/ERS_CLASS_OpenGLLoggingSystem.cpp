//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_OpenGLLoggingSystem.h>


ERS_CLASS_OpenGLLoggingSystem::ERS_CLASS_OpenGLLoggingSystem(ERS_CLASS_LoggingSystem* Logger) {

    Logger_ = Logger;

    Logger_->Log("Initializing OpenGL Log Collection Subsystem", 5);
    glDisable(GL_DEBUG_OUTPUT);

}

ERS_CLASS_OpenGLLoggingSystem::~ERS_CLASS_OpenGLLoggingSystem() {

    Logger_->Log("OpenGL Log Collection Subsystem Destructor Called", 6);

}

void ERS_CLASS_OpenGLLoggingSystem::SetCollectionStatus(bool Status) {

    // If Enabled, Setup Logging
    if (Status) {
        Logger_->Log("Enabling OpenGL Debug Output", 5);
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GLDebugMessageCallback, NULL);
    } else {
        Logger_->Log("Disabling OpenGL Debug Output", 5);
        glDisable(GL_DEBUG_OUTPUT);
    }

}