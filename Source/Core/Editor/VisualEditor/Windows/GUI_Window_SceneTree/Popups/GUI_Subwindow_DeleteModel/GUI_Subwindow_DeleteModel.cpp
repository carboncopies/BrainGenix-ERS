
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-07
*/

#include <GUI_Subwindow_DeleteModel.h>


Subwindow_DeleteModel::Subwindow_DeleteModel(SceneManager* SceneManager) {

    // Copy Pointer
    SceneManager_ = SceneManager;


}

Subwindow_DeleteModel::~Subwindow_DeleteModel() {

    // Hide All Popups
    bool ShowDeleteConfirm_ = false;
    bool ShowOneSceneDeleteError_ = false;

}

void Subwindow_DeleteModel::DeleteModel(int SceneIndex, int ModelIndex) {

    // Enable Firstframe
    FirstFrame_ = true;

    // Show Popup Windows
    SceneIndex_ = SceneIndex;
    ModelIndex_ = ModelIndex;
    ShowDeleteConfirm_ = true;
    
}

void Subwindow_DeleteModel::Draw() {

    // Update Window
    UpdateConfirmDeletePopup();

}

void Subwindow_DeleteModel::UpdateConfirmDeletePopup() {

    // Begin Window
    if (ShowDeleteConfirm_) {
    ImGui::Begin("Delete Model?", &ShowDeleteConfirm_, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse);

        // Grab Window Focus
        ImGui::SetWindowFocus();
        
        // Set Default Keyboard Input
        if (FirstFrame_) {
            ImGui::SetKeyboardFocusHere(0);
            FirstFrame_ = false;
        }

        // Add Confirm Message
        ImGui::SetItemDefaultFocus();
        ImGui::Text("This action will delete the selected model.");
        ImGui::Separator();

        // Confirm And Abort Buttons
        if (ImGui::Button("Confirm", ImVec2(120, 0)) || ImGui::IsKeyPressed(GLFW_KEY_ENTER)) { // If Button Pressed, Or Enter Key Pressed
            SceneManager_->Scenes_[SceneIndex_].Models.erase(SceneManager_->Scenes_[SceneIndex_].Models.begin() + ModelIndex_);
            SceneManager_->Scenes_[SceneIndex_].SelectedModel = ModelIndex_-1;
            ShowDeleteConfirm_ = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Abort", ImVec2(120, 0)) || ImGui::IsKeyPressed(GLFW_KEY_ESCAPE)) { // If Button Pressed, Or Escape Key Pressed
            ShowDeleteConfirm_ = false;
        }

    ImGui::End();


    }

}
