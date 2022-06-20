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

    // Turn Off Output As Callback Relies On PointerS Owned By This Class, Causing A Segfault If Not Disabled Here
    glDisable(GL_DEBUG_OUTPUT);

}

void ERS_CLASS_OpenGLLoggingSystem::SetCollectionStatus(bool Status) {

    // If Enabled, Setup Logging
    if (Status) {
        Logger_->Log("Enabling OpenGL Debug Output", 5);
        glEnable(GL_DEBUG_OUTPUT);
        Logger_->Log("Registering OpenGL Message Callback", 4);
        UserParam_.Logger_ = (void*)Logger_;
        UserParam_.OpenGLLoggingSystem_ = (void*)this;
        glDebugMessageCallback(ERS_MessageCallback, &UserParam_);
        Logger_->Log("Done Registering OpenGL Message Callback", 3);

        Logger_->Log("Inserting Test Message", 3);
        std::string DebugMessage = "Debug Messages Are Now Enabled And Working Properly";
        glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_OTHER, 0, GL_DEBUG_SEVERITY_NOTIFICATION, DebugMessage.size(), DebugMessage.c_str());

    } else {
        Logger_->Log("Disabling OpenGL Debug Output", 5);
        glDisable(GL_DEBUG_OUTPUT);
    }

}