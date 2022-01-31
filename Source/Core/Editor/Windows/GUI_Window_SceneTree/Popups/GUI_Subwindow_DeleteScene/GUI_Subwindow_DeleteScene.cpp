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


Subwindow_DeleteScene::Subwindow_DeleteScene(std::shared_ptr<ERS_CLASS_SceneManager> SceneManager) {

    // Copy Pointer
    SceneManager_ = SceneManager;


}

Subwindow_DeleteScene::~Subwindow_DeleteScene() {

    // Hide All Popups
    bool ShowDeleteConfirm_ = false;
    bool ShowOneSceneDeleteError_ = false;

}

void Subwindow_DeleteScene::DeleteScene(int SceneIndex) {

    // Enable Firstframe
    FirstFrame_ = true;

    // Show Popup Windows
    if (SceneManager_->Scenes_.size() != 1) {
        SceneIndex_ = SceneIndex;
        ShowDeleteConfirm_ = true;
    } else {
        ShowOneSceneDeleteError_ = true;
    }

    
}

void Subwindow_DeleteScene::Draw() {

    // Update Windows
    UpdateConfirmDeletePopup();
    UpdateOneSceneDeleteErrorPopup();

}

void Subwindow_DeleteScene::UpdateConfirmDeletePopup() {

    // Begin Window
    if (ShowDeleteConfirm_) {
    ImGui::Begin("Delete Scene?", &ShowDeleteConfirm_, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse);

        // Grab Window Focus
        ImGui::SetWindowFocus();
        
        // Set Default Keyboard Input
        if (FirstFrame_) {
            ImGui::SetKeyboardFocusHere(0);
            FirstFrame_ = false;
        }

        // Add Confirm Message
        ImGui::SetItemDefaultFocus();
        ImGui::Text("This action will delete the selected scene.");
        ImGui::Separator();

        // Confirm And Abort Buttons
        if (ImGui::Button("Confirm", ImVec2(120, 0)) || ImGui::IsKeyPressed(GLFW_KEY_ENTER)) { // If Button Pressed, Or Enter Key Pressed
            if (SceneManager_->Scenes_.size() != 1) {
                SceneManager_->Scenes_.erase(SceneManager_->Scenes_.begin() + SceneIndex_);
            }
            ShowDeleteConfirm_ = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Abort", ImVec2(120, 0)) || ImGui::IsKeyPressed(GLFW_KEY_ESCAPE)) { // If Button Pressed, Or Escape Key Pressed
            ShowDeleteConfirm_ = false;
        }

    ImGui::End();


    }

}


void Subwindow_DeleteScene::UpdateOneSceneDeleteErrorPopup() {

    // Begin Popup
    if (ShowOneSceneDeleteError_) {
    ImGui::Begin("Error", &ShowOneSceneDeleteError_, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse);

        // Grab Window Focus
        ImGui::SetWindowFocus();
        
        // Set Default Keyboard Input
        if (FirstFrame_) {
            ImGui::SetKeyboardFocusHere(0);
            FirstFrame_ = false;
        }

        // Add Message
        ImGui::SetItemDefaultFocus();
        ImGui::Text("You must have at least one scene.");
        ImGui::Separator();

        // Close Button
        if (ImGui::Button("Close", ImVec2(120, 0)) || ImGui::IsKeyPressed(GLFW_KEY_ESCAPE) || ImGui::IsKeyPressed(GLFW_KEY_ENTER)) { // If Button Pressed, Or Enter/Escape Key Pressed
            ShowOneSceneDeleteError_ = false;
        }

    ImGui::End();
    }

}
