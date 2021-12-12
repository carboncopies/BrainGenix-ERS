//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-07
*/

#include <GUI_Subwindow_DeleteScene.h>


Subwindow_DeleteScene::Subwindow_DeleteScene(SceneManager* SceneManager) {

    // Copy Pointer
    SceneManager_ = SceneManager;


}

Subwindow_DeleteScene::~Subwindow_DeleteScene() {

    // Hide All Popups
    bool ShowDeleteConfirm_ = false;
    bool ShowOneSceneDeleteError_ = false;

}

void Subwindow_DeleteScene::DeleteScene(int SceneIndex) {

    // Delete From SceneManager
    if (SceneManager_->Scenes_.size() != 1) {
        SceneManager_->Scenes_.erase(SceneManager_->Scenes_.begin() + SceneIndex);
    }
    
}

void Subwindow_DeleteScene::Update() {

    // Update Windows
    UpdateConfirmDeletePopup();
    UpdateOneSceneDeleteErrorPopup();

}

void Subwindow_DeleteScene::UpdateConfirmDeletePopup() {

    // Begin Window
    if (UpdateConfirmDeletePopup) {
        


    }

}
