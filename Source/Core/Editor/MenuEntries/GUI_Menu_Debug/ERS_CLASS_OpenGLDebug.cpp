//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_OpenGLDebug.h>


ERS_CLASS_OpenGLDebug::ERS_CLASS_OpenGLDebug(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;


    SystemUtils_->Logger_->Log("Initializing OpenGL Debug Menu GUI Subsystem", 5);


    ERS_CLASS_OpenGLLoggingSystem_ = std::make_unique<ERS_CLASS_OpenGLLoggingSystem>(SystemUtils_->Logger_.get());


}

ERS_CLASS_OpenGLDebug::~ERS_CLASS_OpenGLDebug() {

    SystemUtils_->Logger_->Log("OpenGL Debug Menu GUI Subsystem Destructor Invoked", 6);

}

void ERS_CLASS_OpenGLDebug::DrawMenu() {

    if (ImGui::MenuItem("Debugging Enabled", "", &DebugEnabled_)) {
        ERS_CLASS_OpenGLLoggingSystem_->SetCollectionStatus(DebugEnabled_);
    }

    ImGui::Separator();

    // Source Submenu
    if (ImGui::BeginMenu("GL Sources")) {

        if (ImGui::MenuItem("GL_DEBUG_SOURCE_API", "", &ERS_CLASS_OpenGLLoggingSystem_->LogSourceApi_)) {
            ERS_CLASS_OpenGLLoggingSystem_->SetCollectionStatus(DebugEnabled_);
        }
        if (ImGui::MenuItem("GL_DEBUG_SOURCE_WINDOW_SYSTEM", "", &ERS_CLASS_OpenGLLoggingSystem_->LogSourceWindowSystem_)) {
            ERS_CLASS_OpenGLLoggingSystem_->SetCollectionStatus(DebugEnabled_);
        }
        if (ImGui::MenuItem("GL_DEBUG_SOURCE_SHADER_COMPILER", "", &ERS_CLASS_OpenGLLoggingSystem_->LogSourceShaderCompiler_)) {
            ERS_CLASS_OpenGLLoggingSystem_->SetCollectionStatus(DebugEnabled_);
        }
        if (ImGui::MenuItem("GL_DEBUG_SOURCE_THIRD_PARTY", "", &ERS_CLASS_OpenGLLoggingSystem_->LogSourceThirdParty_)) {
            ERS_CLASS_OpenGLLoggingSystem_->SetCollectionStatus(DebugEnabled_);
        }
        if (ImGui::MenuItem("GL_DEBUG_SOURCE_APPLICATION", "", &ERS_CLASS_OpenGLLoggingSystem_->LogSourceApplication_)) {
            ERS_CLASS_OpenGLLoggingSystem_->SetCollectionStatus(DebugEnabled_);
        }
        if (ImGui::MenuItem("GL_DEBUG_SOURCE_OTHER", "", &ERS_CLASS_OpenGLLoggingSystem_->LogSourceOther_)) {
            ERS_CLASS_OpenGLLoggingSystem_->SetCollectionStatus(DebugEnabled_);
        }
    
    ImGui::EndMenu();
    }

    // Type Submenu
    if (ImGui::BeginMenu("GL Types")) {

        

    ImGui::EndMenu();
    }

}