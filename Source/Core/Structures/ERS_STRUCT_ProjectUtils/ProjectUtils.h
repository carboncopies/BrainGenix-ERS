//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory.h>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <SceneManager.h>

#include <ModelLoader.h>
#include <SceneLoader.h>
#include <ProjectLoader.h>
#include <ProjectManager.h>
#include <ProjectWriter.h>

#include <ModelImporter.h>


/**
 * @brief The System utils struct contains most project mgmt utils/classes/structs.
 * 
 */
struct ERS_STRUCT_ProjectUtils {


    std::unique_ptr<ERS_CLASS_SceneManager> SceneManager_; /**<Shared Ptr To Scene Manager*/
    std::unique_ptr<ERS_CLASS_ModelLoader> ModelLoader_; /**<Shared Ptr To Model Loader*/
    std::unique_ptr<ERS_CLASS_SceneLoader> SceneLoader_; /**<Shared Ptr To Scene Loader*/
    std::unique_ptr<ERS_CLASS_ProjectLoader> ProjectLoader_; /**<Shared Pointer To Project Loader*/
    std::unique_ptr<ERS_CLASS_ProjectManager> ProjectManager_; /**<Shared Pointer To Projet Manager Instance*/
    std::unique_ptr<ERS_CLASS_ProjectWriter> ProjectWriter_; /**<Shared Pointer to project writer instance*/
    std::unique_ptr<ERS_ModelImporter> ModelImporter_; /**<Pointer to model importer instance*/

};