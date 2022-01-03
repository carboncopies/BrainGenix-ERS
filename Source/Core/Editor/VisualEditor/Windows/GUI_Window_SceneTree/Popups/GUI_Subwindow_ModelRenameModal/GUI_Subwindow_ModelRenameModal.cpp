//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-07
*/

#include <GUI_Subwindow_ModelRenameModal.h>

// Constructor
Subwindow_ModelRenameModal::Subwindow_ModelRenameModal(std::shared_ptr<ERS_CLASS_SceneManager> SceneManager) {

    // Update Ptr
    SceneManager_ = SceneManager;


}

// Destructor
Subwindow_ModelRenameModal::~Subwindow_ModelRenameModal() {
    
}

// Define Activation Function
void Subwindow_ModelRenameModal::Activate(int SceneIndex, int ModelIndex) {

    // Activate
    SelectedScene_ = SceneIndex;
    SelectedModel_ = ModelIndex;
    Enabled_ = true;
    FirstFrame_ = true;        

}

// Define Draw Function
void Subwindow_ModelRenameModal::Draw() {

    // Draw Rename Model Window
    if (Enabled_) {
    ImGui::Begin("Rename Model", &Enabled_, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse);

        // Grab Window Focus
        ImGui::SetWindowFocus();
        
        // Set Default Keyboard Input
        if (FirstFrame_) {
            ImGui::SetKeyboardFocusHere(0);
            FirstFrame_ = false;
        }

        // Set Default Item To Type On, Add Input Box
        ImGui::SetItemDefaultFocus();
        ImGui::InputTextWithHint("Rename Model", "Enter New Model Name", ModelInputName_, IM_ARRAYSIZE(ModelInputName_));

        ImGui::Separator();

        // Rename And Cancel Buttons
        if (ImGui::Button("Rename", ImVec2(120, 0)) || ImGui::IsKeyPressed(GLFW_KEY_ENTER)) { // If Button Pressed, Or Enter Key Pressed
            SceneManager_->Scenes_[SelectedScene_].Models[SelectedModel_]->Name = std::string(ModelInputName_);
            Enabled_ = false;
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0)) || ImGui::IsKeyPressed(GLFW_KEY_ESCAPE)) { // If Button Pressed, Or Escape Key Pressed
            Enabled_ = false;
        }

    ImGui::End();
    }


}
