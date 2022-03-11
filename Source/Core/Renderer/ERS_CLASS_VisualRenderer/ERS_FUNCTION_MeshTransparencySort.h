//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <iostream>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>
#include <ERS_CLASS_ShaderLoader.h>
#include <ERS_CLASS_InputProcessor.h>
#include <ERS_CLASS_Framebuffer.h>
#include <ERS_CLASS_Grid.h>
#include <ERS_CLASS_LightIconRenderer.h>

#include <ERS_SceneManager.h>
#include <ERS_SceneLoader.h>

#include <ERS_Editor_3DCursor.h>

#include <ERS_STRUCT_LocRotScale.h>
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_Viewport.h>
#include <ERS_STRUCT_Shader.h>
#include <ERS_STRUCT_Model.h>
#include <ERS_STRUCT_Camera.h>
#include <ERS_STRUCT_OpenGLDefaults.h>