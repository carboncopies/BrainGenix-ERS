//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ProjectManager.h>


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

    // Apply Saved Renderer Settings
    // Budgets Of 0 Indicate The Hardware-Detected Budgets Already Set By The Resource Monitor Should Be Kept
    SystemUtils_->Logger_->Log("Applying Project Renderer Settings", 4);
    ERS_STRUCT_RendererSettings* SavedSettings = &Project_.RendererSettings;
    ERS_STRUCT_RendererSettings* LiveSettings = SystemUtils_->RendererSettings_.get();

    LiveSettings->ShadowMapX_ = SavedSettings->ShadowMapX_;
    LiveSettings->ShadowMapY_ = SavedSettings->ShadowMapY_;
    LiveSettings->ShadowMapCubemapX_ = SavedSettings->ShadowMapCubemapX_;
    LiveSettings->ShadowMapCubemapY_ = SavedSettings->ShadowMapCubemapY_;
    LiveSettings->ShadowFilteringType_ = SavedSettings->ShadowFilteringType_;
    LiveSettings->ShadowUpdateMode_ = SavedSettings->ShadowUpdateMode_;
    LiveSettings->MaxShadowUpdatesPerFrame_ = SavedSettings->MaxShadowUpdatesPerFrame_;
    LiveSettings->ShadowFilterKernelSize_ = SavedSettings->ShadowFilterKernelSize_;
    LiveSettings->RefreshStaticShadowMaps_ = SavedSettings->RefreshStaticShadowMaps_;
    LiveSettings->MotionBlurEnabled_ = SavedSettings->MotionBlurEnabled_;
    LiveSettings->MotionBlurStrength_ = SavedSettings->MotionBlurStrength_;
    LiveSettings->MotionBlurReferenceFrameRate_ = SavedSettings->MotionBlurReferenceFrameRate_;
    LiveSettings->MotionBlurMaxBlend_ = SavedSettings->MotionBlurMaxBlend_;
    if (SavedSettings->VRAMBudget_ != 0) {
        LiveSettings->VRAMBudget_ = SavedSettings->VRAMBudget_;
    }
    if (SavedSettings->RAMBudget_ != 0) {
        LiveSettings->RAMBudget_ = SavedSettings->RAMBudget_;
    }
    LiveSettings->WarningLowRAMBytes = SavedSettings->WarningLowRAMBytes;
    LiveSettings->CriticalLowRAMBytes = SavedSettings->CriticalLowRAMBytes;
    LiveSettings->FatalLowRAMBytes = SavedSettings->FatalLowRAMBytes;
    LiveSettings->TerminateLowRAMBytes = SavedSettings->TerminateLowRAMBytes;
    LiveSettings->WarningLowVRAMBytes = SavedSettings->WarningLowVRAMBytes;
    LiveSettings->CriticalLowVRAMBytes = SavedSettings->CriticalLowVRAMBytes;
    LiveSettings->FatalLowVRAMBytes = SavedSettings->FatalLowVRAMBytes;
    LiveSettings->TerminateLowVRAMBytes = SavedSettings->TerminateLowVRAMBytes;

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
        Project_.ControllerSettings.push_back(Settings);
    }

    // Handle The Defaut Scene
    if (Project_.SceneIDs.size() > 0) {

        // Load Default Scene If Applicable
        SystemUtils_->Logger_->Log(std::string(std::string("Loading Project Default Scene With ID ") + std::to_string(Project_.SceneIDs[Project_.DefaultScene])).c_str(), 5);
        for (unsigned int i = 0; i < Project_.SceneIDs.size(); i++) {
            SceneManager_->AddScene(SceneLoader_->ProcessScene(Project_.SceneIDs[i]));
        }
        SceneManager_->SetActiveScene(Project_.DefaultScene);

    } else {

        // Create Blank Scene For The System
        ERS_STRUCT_Scene NewScene;
        NewScene.ScenePath = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
        NewScene.SceneName = "Untitled Scene";
        NewScene.IsSceneLoaded = true;
        NewScene.SceneFormatVersion = 1;
        
        Project_.SceneIDs.push_back(NewScene.ScenePath);
        SceneManager_->AddScene(NewScene);

    }

}


void ERS_CLASS_ProjectManager::WriteProject(long AssetID) {

    // Sync Live Renderer Settings Into Project Struct
    Project_.RendererSettings = *SystemUtils_->RendererSettings_;

    // Get Project Pointer. Write Project
    ERS_STRUCT_Project* ProjectPtr = &Project_;
    ProjectWriter_->SaveProject(ProjectPtr, AssetID);

}