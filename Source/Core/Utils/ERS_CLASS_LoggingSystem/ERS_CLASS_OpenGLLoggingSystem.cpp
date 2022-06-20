//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_OpenGLLoggingSystem.h>


// Callback function for printing debug statements
void APIENTRY ERS_MessageCallback(GLenum GLSource, GLenum GLType, GLuint id, GLenum GLSeverity, GLsizei length, const GLchar *msg, const void *data) {


    ERS_STRUCT_MessageCallbackParam* UserParamStruct = (ERS_STRUCT_MessageCallbackParam*)data;
    ERS_CLASS_LoggingSystem* Logger = (ERS_CLASS_LoggingSystem*)UserParamStruct->Logger_;
    ERS_CLASS_OpenGLLoggingSystem* OpenGLLoggingSystem = (ERS_CLASS_OpenGLLoggingSystem*)UserParamStruct->OpenGLLoggingSystem_;


    std::string Source;
    std::string Type;
    std::string Severity;


    switch (GLSource) {
        case GL_DEBUG_SOURCE_API:
        Source = "API";
        break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        Source = "WINDOW SYSTEM";
        break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
        Source = "SHADER COMPILER";
        break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
        Source = "THIRD PARTY";
        break;

        case GL_DEBUG_SOURCE_APPLICATION:
        Source = "APPLICATION";
        break;

        case GL_DEBUG_SOURCE_OTHER:
        Source = "UNKNOWN";
        break;

        default:
        Source = "UNKNOWN";
        break;
    }

    switch (GLType) {
        case GL_DEBUG_TYPE_ERROR:
        Type = "ERROR";
        break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        Type = "DEPRECATED BEHAVIOR";
        break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        Type = "UDEFINED BEHAVIOR";
        break;

        case GL_DEBUG_TYPE_PORTABILITY:
        Type = "PORTABILITY";
        break;

        case GL_DEBUG_TYPE_PERFORMANCE:
        Type = "PERFORMANCE";
        break;

        case GL_DEBUG_TYPE_OTHER:
        Type = "OTHER";
        break;

        case GL_DEBUG_TYPE_MARKER:
        Type = "MARKER";
        break;

        default:
        Type = "UNKNOWN";
        break;
    }

    switch (GLSeverity) {
        case GL_DEBUG_SEVERITY_HIGH:
        Severity= "HIGH";
        break;

        case GL_DEBUG_SEVERITY_MEDIUM:
        Severity= "MEDIUM";
        break;

        case GL_DEBUG_SEVERITY_LOW:
        Severity= "LOW";
        break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
        Severity= "NOTIFICATION";
        break;

        default:
        Severity= "UNKNOWN";
        break;
    }

    // printf("%d: %s of %s severity, raised from %s: %s\n",
    //         id, _type, _severity, _source, msg);

    std::string Message = std::to_string(id) + std::string(msg);

    Logger->Log(Message, 5);
}



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