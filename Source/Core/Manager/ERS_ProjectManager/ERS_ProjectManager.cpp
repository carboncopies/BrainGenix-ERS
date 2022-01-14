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
ERS_CLASS_ProjectManager::ERS_CLASS_ProjectManager(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_CLASS_ProjectLoader> ProjectLoader, std::shared_ptr<ERS_CLASS_ProjectWriter> ProjectWriter, std::shared_ptr<ERS_CLASS_SceneManager> SceneManager, std::shared_ptr<ERS_CLASS_SceneLoader> SceneLoader) {

    // Copy Pointers
    SystemUtils_ = SystemUtils;
    ProjectLoader_ = ProjectLoader;
    SceneManager_ = SceneManager;
    SceneLoader_ = SceneLoader;
    ProjectWriter_ = ProjectWriter;

    // Log Initialization
    SystemUtils_->Logger_->Log("Initializing ERS Project Manager", 5);

    // Setup Controller Settings Loader
    ControllerSettingsLoader_ = std::make_unique<ERS_CLASS_ControllerSettingsLoader>(SystemUtils_);

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
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Project With ID ") + std::to_string(AssetID)).c_str(), 5);
    Project_ = ProjectLoader_->LoadProject(AssetID);

    // Load Controller Settings
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Project Game Controller Settings")).c_str(), 5);
    for (int i = 0; i < Project_.GameControllerSettingsIDs.size(); i++) {

        // Log Loading
        SystemUtils_->Logger_->Log(std::string(std::string("Loading Project Controller Settings With ID ") + std::to_string(Project_.GameControllerSettingsIDs[i])).c_str(), 5);

        // Load Settings
        long ID = Project_.GameControllerSettingsIDs[i];
        std::shared_ptr<ERS_STRUCT_ControllerSettings> Settings = std::make_shared<ERS_STRUCT_ControllerSettings>();
        ControllerSettingsLoader_->LoadControllerSettings(Settings, ID);

        // Add To Settings List
        Project_.ControllerSettings.push_back(Settings);
    }

    // Load Default Scene
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Project Default Scene With ID ") + std::to_string(Project_.SceneIDs[Project_.DefaultScene])).c_str(), 5);
    SceneManager_->AddScene(SceneLoader_->ProcessScene(Project_.SceneIDs[Project_.DefaultScene]));
    SceneManager_->SetActiveScene(0);

}


// Write Project
void ERS_CLASS_ProjectManager::WriteProject(long AssetID) {

    // Get Project Pointer. Write Project
    std::shared_ptr<ERS_STRUCT_Project> ProjectPtr = std::make_shared<ERS_STRUCT_Project>(Project_);
    ProjectWriter_->SaveProject(ProjectPtr, AssetID);

}