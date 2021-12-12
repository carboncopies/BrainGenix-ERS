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

    // Delete From SceneManager
    SceneManager->Scenes_.erase(SceneManager->Scenes_.begin() + SceneIndex);

}