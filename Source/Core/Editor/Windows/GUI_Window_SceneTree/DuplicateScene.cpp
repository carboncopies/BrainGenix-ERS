//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <DuplicateScene.h>
#include <ProjectUtils.h>
#include <SystemUtils.h>


void GUI_Windowutil_DuplicateScene(ERS_CLASS_SceneManager* SceneManager, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_STRUCT_SystemUtils* SystemUtils, int SceneIndex) {

    // Get Current Scene
    ERS_STRUCT_Scene NewScene = *SceneManager->Scenes_[SceneIndex].get();

    // Update Metadata
    std::string CurrentName = NewScene.SceneName;
    std::string NewName = CurrentName + std::string(" - Copy");
    NewScene.SceneName = NewName;
    NewScene.ScenePath = SystemUtils->ERS_IOSubsystem_->AllocateAssetID();
    ProjectUtils->ProjectManager_->Project_.SceneIDs.push_back(NewScene.ScenePath);

    // Add To SceneManager
    SceneManager->Scenes_.push_back(std::make_unique<ERS_STRUCT_Scene>(NewScene));

}
