 
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <SceneManager.h>
#include <Scene.h>

struct ERS_STRUCT_ProjectUtils;
struct ERS_STRUCT_SystemUtils;

/**
 * @brief Duplicate the scene in the project
 * 
 * @param SceneManager 
 * @param ProjectUtils
 * @param SystemUtils
 * @param SceneIndex 
 */
void GUI_Windowutil_DuplicateScene(ERS_CLASS_SceneManager* SceneManager, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_STRUCT_SystemUtils* SystemUtils, int SceneIndex);
