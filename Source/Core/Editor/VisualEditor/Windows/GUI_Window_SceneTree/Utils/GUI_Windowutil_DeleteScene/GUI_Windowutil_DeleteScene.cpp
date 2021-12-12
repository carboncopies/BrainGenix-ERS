//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-07
*/

#include <GUI_Windowutil_DeleteScene.h>


void GUI_Windowutil_DeleteScene(SceneManager* SceneManager, int SceneIndex) {

    // Get Current Scene
    ERS_OBJECT_SCENE NewScene = SceneManager->Scenes_[SceneIndex];

    // Update Name
    std::string CurrentName = NewScene.SceneName;
    std::string NewName = CurrentName + std::string(" - Copy");
    NewScene.SceneName = NewName;

    // Add To SceneManager
    SceneManager->Scenes_.push_back(NewScene);

}