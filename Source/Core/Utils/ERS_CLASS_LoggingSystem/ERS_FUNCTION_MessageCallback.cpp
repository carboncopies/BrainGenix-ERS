//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_MessageCallback.h>



// Callback function for printing debug statements
void APIENTRY ERS_MessageCallback(GLenum GLSource, GLenum GLType, GLuint GLID, GLenum GLSeverity, GLsizei, const GLchar *GLMessage, const void *UserData) {

    // Get System Pointers From User Data Void Ptr
    ERS_STRUCT_MessageCallbackParam* UserParamStruct = (ERS_STRUCT_MessageCallbackParam*)UserData;
    ERS_CLASS_LoggingSystem* Logger = (ERS_CLASS_LoggingSystem*)UserParamStruct->Logger_;
    ERS_CLASS_OpenGLLoggingSystem* OpenGLLoggingSystem = (ERS_CLASS_OpenGLLoggingSystem*)UserParamStruct->OpenGLLoggingSystem_;

    // Convert GL Enum To Readable Strings
    std::string Source;
    std::string Type;
    std::string Severity;
    int LogLevel;

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
        LogLevel = 10;
        break;

        case GL_DEBUG_SEVERITY_MEDIUM:
        Severity= "MEDIUM";
        LogLevel = 9;
        break;

        case GL_DEBUG_SEVERITY_LOW:
        Severity= "LOW";
        LogLevel = 8;
        break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
        Severity= "NOTIFICATION";
        LogLevel = 5;
        break;

        default:
        Severity= "UNKNOWN";
        LogLevel = 7;
        break;
    }


    // Generate Log Message
    std::string Message = "["+ std::to_string(GLID) + "] ["
     + std::string(Source) + "] [" + std::string(Type) + "] ["
     + std::string(Severity) + "] " + std::string(GLMessage);

    Logger->Log(Message, LogLevel);

    
    // Create Struct
    ERS_STRUCT_OpenGLLogItem Item;
    Item.Message_ = std::string(GLMessage);
    Item.ID_ = GLID;
    Item.Severity_ = GLSeverity;
    Item.Source_ = GLSource;
    Item.Type_ = GLType;

    // Append To List
    std::unique_lock<std::mutex> Lock =  std::unique_lock<std::mutex>(OpenGLLoggingSystem->LogItemMutex_);
    OpenGLLoggingSystem->LogItems_.push_back(Item);

}