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
GUI_Menu_File::GUI_Menu_File(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_CLASS_SceneManager> SceneManager, std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils) {

    // Copy In Pointer Struct
    SystemUtils_ = SystemUtils;
    SceneManager_ = SceneManager;
    ProjectUtils_ = ProjectUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Editor Setting Up File Menu", 4);

    // Create Class Instances
    SceneWriter_ = std::make_unique<SceneWriter>(SystemUtils_);
    ImportAsset_ = std::make_unique<GUI_ImportAsset>(SystemUtils_);
    Window_ProjectSettings_ = std::make_unique<Window_ProjectSettings>(ProjectUtils, SystemUtils);

}

// Destructor
GUI_Menu_File::~GUI_Menu_File() {

    // Log Destructor
    SystemUtils_->Logger_->Log("Editor Destroying File Menu", 4);

}

// Draw Function
void GUI_Menu_File::Draw() {

    // File Menu
    if (ImGui::BeginMenu("File")) {

        // Project Options
        if (ImGui::MenuItem("Save Project")) {
            
        }
        if (ImGui::MenuItem("Project Settings")) {
            Window_ProjectSettings_->Enabled_ = !Window_ProjectSettings_->Enabled_;
        }
        ImGui::Separator();

        // Import Option, Disabled On Windows Due To Filesystem Issues
        if (SystemUtils_->IsLinux_) {
            if (ImGui::MenuItem("Import Model")) {
                ImportAsset_->OpenFileDialog();
            }
            ImGui::Separator();
        }

        // Save Options
        if (ImGui::MenuItem("Save Active Scene")) {
            SceneWriter_->ProcessScene(
                std::make_shared<ERS_OBJECT_SCENE>(SceneManager_->Scenes_[SceneManager_->ActiveScene_]),
                SceneManager_->Scenes_[SceneManager_->ActiveScene_].ScenePath
                );
        }
        if (ImGui::MenuItem("Save All Scenes")) {
            for (int i = 0; i < SceneManager_->Scenes_.size(); i++) {
                SceneWriter_->ProcessScene(
                    std::make_shared<ERS_OBJECT_SCENE>(SceneManager_->Scenes_[i]),
                    SceneManager_->Scenes_[i].ScenePath
                    );
            }
        }

        ImGui::Separator();

        // Exit Options
        if (ImGui::MenuItem("Exit")) {
            *SystemUtils_->SystemShouldRun_ = false;
        }

        
    ImGui::EndMenu();
    }


    // Draw Subwindows
    ImportAsset_->Draw();
    Window_ProjectSettings_->Draw();


}