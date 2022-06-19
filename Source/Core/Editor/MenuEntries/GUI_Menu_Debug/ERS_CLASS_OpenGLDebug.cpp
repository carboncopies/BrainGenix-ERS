//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_OpenGLDebug.h>


ERS_CLASS_OpenGLDebug::ERS_CLASS_OpenGLDebug(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;


    SystemUtils_->Logger_->Log("Initializing OpenGL Debug Menu GUI Subsystem", 5);


    ERS_CLASS_OpenGLLoggingSystem_ = std::make_unique<ERS_CLASS_OpenGLLoggingSystem>(SystemUtils_->Logger_);


}

ERS_CLASS_OpenGLDebug::~ERS_CLASS_OpenGLDebug() {

    SystemUtils_->Logger_->Log("OpenGL Debug Menu GUI Subsystem Destructor Invoked", 6);

}

void ERS_CLASS_OpenGLDebug::DrawMenu() {

    if (ImGui::MenuItem("Debugging Enabled", "", &DebugEnabled_)) {
        if (DebugEnabled_) {
            SystemUtils_->Logger_->Log("Enabling OpenGL Debugging Output", 5);
            glEnable(GL_DEBUG_OUTPUT);
        } else {
            SystemUtils_->Logger_->Log("Disabling OpenGL Debugging Output", 5);
            glDisable(GL_DEBUG_OUTPUT);
        }
    }

}