//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_ProjectManager.h>


ERS_CLASS_ProjectManager::ERS_CLASS_ProjectManager(ERS_STRUCT_SystemUtils* SystemUtils, ERS_CLASS_ProjectLoader* ProjectLoader, ERS_CLASS_ProjectWriter* ProjectWriter, ERS_CLASS_SceneManager* SceneManager, ERS_CLASS_SceneLoader* SceneLoader) {

    SystemUtils_ = SystemUtils;
    ProjectLoader_ = ProjectLoader;
    SceneManager_ = SceneManager;
    SceneLoader_ = SceneLoader;
    ProjectWriter_ = ProjectWriter;

    SystemUtils_->Logger_->Log("Initializing ERS Project Manager", 5);

    ControllerSettingsLoader_ = std::make_unique<ERS_CLASS_ControllerSettingsLoader>(SystemUtils_);

    LoadProject(1);

}

ERS_CLASS_ProjectManager::~ERS_CLASS_ProjectManager() {

    SystemUtils_->Logger_->Log("ERS Project Manager Destructor Called", 6);

}


void ERS_CLASS_ProjectManager::LoadProject(long AssetID) {

    // Load Into Project Struct
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Project With ID ") + std::to_string(AssetID)).c_str(), 5);
    Project_ = ProjectLoader_->LoadProject(AssetID);

    // Load Controller Settings
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Project Game Controller Settings")).c_str(), 5);
    for (int i = 0; (long)i < (long)Project_.GameControllerSettingsIDs.size(); i++) {

        // Log Loading
        SystemUtils_->Logger_->Log(std::string(std::string("Loading Project Controller Settings With ID ") + std::to_string(Project_.GameControllerSettingsIDs[i])).c_str(), 5);

        // Load Settings
        long ID = Project_.GameControllerSettingsIDs[i];
        ERS_STRUCT_ControllerSettings Settings = ERS_STRUCT_ControllerSettings();
        ControllerSettingsLoader_->LoadControllerSettings(&Settings, ID);

        // Add To Settings List
        Project_.ControllerSettings->push_back(Settings);
    }

    // Load Default Scene
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Project Default Scene With ID ") + std::to_string(Project_.SceneIDs[Project_.DefaultScene])).c_str(), 5);
    SceneManager_->AddScene(SceneLoader_->ProcessScene(Project_.SceneIDs[Project_.DefaultScene]));
    SceneManager_->SetActiveScene(Project_.DefaultScene);

}


void ERS_CLASS_ProjectManager::WriteProject(long AssetID) {

    // Get Project Pointer. Write Project
    ERS_STRUCT_Project* ProjectPtr = &Project_;
    ProjectWriter_->SaveProject(ProjectPtr, AssetID);

}