//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a class to manage project loading/writing/storage functions.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2022-01-03
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <thread>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_Project.h>

#include <ERS_SceneLoader.h>
#include <ERS_SceneManager.h>
#include <ERS_ProjectLoader.h>


/**
 * @brief Project Manager Class
 * 
 */
class ERS_CLASS_ProjectManager {


private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Pointer To System Utils Struct*/
    std::shared_ptr<ERS_CLASS_ProjectLoader> ProjectLoader_; /**<Project Loader Util*/
    std::shared_ptr<ERS_CLASS_SceneManager> SceneManager_; /**<Scene Manager Class*/
    std::shared_ptr<ERS_CLASS_SceneLoader> SceneLoader_; /**<Scene Loader Instance*/

public:

    ERS_STRUCT_Project Project_; /**<Active Project Struct*/

public:

    /**
     * @brief Construct a new ers class projectmanager object
     * 
     * @param SystemUtils 
     * @param ProjectLoader 
     */
    ERS_CLASS_ProjectManager(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_CLASS_ProjectLoader> ProjectLoader, std::shared_ptr<ERS_CLASS_SceneManager> SceneManager, std::shared_ptr<ERS_CLASS_SceneLoader> SceneLoader);

    /**
     * @brief Destroy the ers class projectmanager object
     * 
     */
    ~ERS_CLASS_ProjectManager();



    /**
     * @brief Load Project From AssetID
     * 
     * @param AssetID 
     */
    void LoadProject(long AssetID);


};