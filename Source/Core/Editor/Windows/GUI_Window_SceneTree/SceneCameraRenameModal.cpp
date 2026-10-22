//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <SceneCameraRenameModal.h>

Subwindow_SceneCameraRenameModal::Subwindow_SceneCameraRenameModal(ERS_CLASS_SceneManager* SceneManager) {

    SceneManager_ = SceneManager;


}

Subwindow_SceneCameraRenameModal::~Subwindow_SceneCameraRenameModal() {
    
}

void Subwindow_SceneCameraRenameModal::Activate(int SceneIndex, int SceneCameraIndex) {

    SelectedScene_ = SceneIndex;
    SelectedSceneCamera_ = SceneCameraIndex;
    Enabled_ = true;
    FirstFrame_ = true;        

}

void Subwindow_SceneCameraRenameModal::Draw() {

    if (Enabled_) {
    ImGui::Begin("Rename Scene Camera", &Enabled_, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse);

        // Grab Window Focus
        ImGui::SetWindowFocus();
        
        // Set Default Keyboard Input
        if (FirstFrame_) {
            ImGui::SetKeyboardFocusHere(0);
            FirstFrame_ = false;
        }

        // Set Default Item To Type On, Add Input Box
        ImGui::SetItemDefaultFocus();
        ImGui::InputTextWithHint("Rename Scene Camera", "Enter New Scene Camera Name", SceneCameraInputName_, IM_ARRAYSIZE(SceneCameraInputName_));

        ImGui::Separator();

        // Rename And Cancel Buttons
        if (ImGui::Button("Rename", ImVec2(120, 0)) || ImGui::IsKeyPressed(GLFW_KEY_ENTER)) { // If Button Pressed, Or Enter Key Pressed
            SceneManager_->Scenes_[SelectedScene_]->SceneCameras[SelectedSceneCamera_]->UserDefinedName_ = std::string(SceneCameraInputName_);
            Enabled_ = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0)) || ImGui::IsKeyPressed(GLFW_KEY_ESCAPE)) { // If Button Pressed, Or Escape Key Pressed
            Enabled_ = false;
        }

    ImGui::End();
    }


}
