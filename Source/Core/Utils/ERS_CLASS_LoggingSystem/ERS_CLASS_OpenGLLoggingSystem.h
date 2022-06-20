//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <iostream>
#include <vector>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>
#include <ERS_STRUCT_OpenGLLogItem.h>
#include <ERS_STRUCT_MessageCallbackUserParam.h>

//std::vector<std::string> OpenGLLogs_; /**List of messages as collected by the opengl logging system*/

//void APIENTRY ERS_MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, const void *data);



/**
 * @brief This Class Provides A System To Get OpenGL Context Issues as well as debug other things related to opengl.
 * 
 */
class ERS_CLASS_OpenGLLoggingSystem {

private:

    ERS_CLASS_LoggingSystem* Logger_; /**<Class to prettyify the opengl logs once they're extracted*/
    ERS_STRUCT_MessageCallbackParam UserParam_; /**<Used In Debug Callback*/




public:

    std::vector<ERS_STRUCT_OpenGLLogItem> LogItems_; /**<List of log items as gotten from the opengl system*/
    std::mutex LogItemMutex_; /**<Mutex To Enxure Thread Safety For The Log Items Vector*/


    /**
     * @brief Construct a new ers class openglloggingsystem object
     * 
     * @param Logger 
     */
    ERS_CLASS_OpenGLLoggingSystem(ERS_CLASS_LoggingSystem* Logger);

    /**
     * @brief Destroy the ers class openglloggingsystem object
     * 
     */
    ~ERS_CLASS_OpenGLLoggingSystem();


    /**
     * @brief Use This To Enable Or Disable Collection of Logs From OpenGL
     * 
     * @param Status 
     */
    void SetCollectionStatus(bool Status);

};