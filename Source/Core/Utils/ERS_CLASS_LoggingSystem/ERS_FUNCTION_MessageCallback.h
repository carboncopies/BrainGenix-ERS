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

/**
 * @brief Used to collect messages and add them to the system log from opengl's callback system.
 * 
 */
void APIENTRY ERS_MessageCallback(GLenum GLSource, GLenum GLType, GLuint GLID, GLenum GLSeverity, GLsizei, const GLchar *GLMessage, const void *UserData)