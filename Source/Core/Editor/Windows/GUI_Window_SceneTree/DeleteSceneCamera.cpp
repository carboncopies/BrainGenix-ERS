
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <DeleteSceneCamera.h>


Subwindow_DeleteSceneCamera::Subwindow_DeleteSceneCamera(ERS_CLASS_SceneManager* SceneManager, Cursors3D* Cursor) {

    SceneManager_ = SceneManager;
    Cursor_ = Cursor;


}

Subwindow_DeleteSceneCamera::~Subwindow_DeleteSceneCamera() {

}

void Subwindow_DeleteSceneCamera::DeleteSceneCamera(int SceneIndex, int SceneCameraIndex) {

    FirstFrame_ = true;

    // Show Popup Windows
    SceneIndex_ = SceneIndex;
    SceneCameraIndex_ = SceneCameraIndex;
    ShowDeleteConfirm_ = true;
    
}

void Subwindow_DeleteSceneCamera::Draw() {

    UpdateConfirmDeletePopup();

}

void Subwindow_DeleteSceneCamera::UpdateConfirmDeletePopup() {

    if (ShowDeleteConfirm_) {
    ImGui::Begin("Delete Scene Camera?", &ShowDeleteConfirm_, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse);

        // Grab Window Focus
        ImGui::SetWindowFocus();
        
        // Set Default Keyboard Input
        if (FirstFrame_) {
            ImGui::SetKeyboardFocusHere(0);
            FirstFrame_ = false;
        }

        // Add Confirm Message
        ImGui::SetItemDefaultFocus();
        ImGui::Text("This action will delete the selected Scene Camera.");
        ImGui::Separator();

        // Confirm And Abort Buttons
        if (ImGui::Button("Confirm", ImVec2(120, 0)) || ImGui::IsKeyPressed(GLFW_KEY_ENTER)) { // If Button Pressed, Or Enter Key Pressed
            SceneManager_->Scenes_[SceneIndex_]->SceneCameras.erase(SceneManager_->Scenes_[SceneIndex_]->SceneCameras.begin() + SceneCameraIndex_);
            ShowDeleteConfirm_ = false;
            SceneManager_->Scenes_[SceneManager_->ActiveScene_]->HasSelectionChanged = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Abort", ImVec2(120, 0)) || ImGui::IsKeyPressed(GLFW_KEY_ESCAPE)) { // If Button Pressed, Or Escape Key Pressed
            ShowDeleteConfirm_ = false;
        }

    ImGui::End();


    }

}
