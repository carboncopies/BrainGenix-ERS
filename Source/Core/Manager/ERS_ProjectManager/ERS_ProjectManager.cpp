//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a class to manage project loading/writing/storage functions.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2022-01-03
*/

#include <ERS_ProjectManager.h>


// Constructor
ERS_CLASS_ProjectManager::ERS_CLASS_ProjectManager(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_CLASS_ProjectLoader> ProjectLoader, std::shared_ptr<ERS_CLASS_SceneManager> SceneManager, std::shared_ptr<ERS_CLASS_SceneLoader> SceneLoader) {

    // Copy Pointers
    SystemUtils_ = SystemUtils;
    ProjectLoader_ = ProjectLoader;
    SceneManager_ = SceneManager;
    SceneLoader_ = SceneLoader;

    // Log Initialization
    SystemUtils_->Logger_->Log("Initializing ERS Project Manager", 5);



    // Load Default Project
    LoadProject(0);

}

// Destructor
ERS_CLASS_ProjectManager::~ERS_CLASS_ProjectManager() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("ERS Project Manager Destructor Called", 6);

}


// Load Project
void ERS_CLASS_ProjectManager::LoadProject(long AssetID) {

    // Load Into Project Struct
    Project_ = ProjectLoader_->LoadProject(AssetID);

    // Load Default Scene
    

}