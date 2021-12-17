//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides a GUI menu entry.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Menu_File.h>


// Constructor
GUI_Menu_File::GUI_Menu_File(ERS_STRUCT_SystemUtils SystemUtils, std::shared_ptr<SceneManager> SceneManager) {

    // Copy In Pointer Struct
    SystemUtils_ = SystemUtils;
    SceneManager_ = SceneManager;

    // Log Initialization
    SystemUtils_.Logger_->Log("Editor Setting Up File Menu", 4);

    // Create Class Instances
    SceneWriter_ = std::make_unique<SceneWriter>(SystemUtils_.Logger_);



}

// Destructor
GUI_Menu_File::~GUI_Menu_File() {

    // Log Destructor
    SystemUtils_.Logger_->Log("Editor Destroying File Menu", 4);

}

// Draw Function
void GUI_Menu_File::Draw() {

    // File Menu
    if (ImGui::BeginMenu("File")) {

        if (ImGui::MenuItem("Save Active Scene")) {
            SceneWriter_->ProcessScene(SceneManager_->Scenes_[SceneManager_->ActiveScene_], SceneManager_->Scenes_[SceneManager_->ActiveScene_].ScenePath.c_str());
        }

        if (ImGui::MenuItem("Save All")) {

            for (int i = 0; i < SceneManager_->Scenes_.size(); i++) {
                SceneWriter_->ProcessScene(SceneManager_->Scenes_[i], SceneManager_->Scenes_[i].ScenePath.c_str());
            }

        }

        ImGui::Separator();

        if (ImGui::MenuItem("Exit")) {
            *SystemUtils_.SystemShouldRun_ = false;
        }

        
    ImGui::EndMenu();
    }

}