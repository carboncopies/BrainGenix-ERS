//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_File.h>


GUI_Menu_File::GUI_Menu_File(ERS_STRUCT_SystemUtils* SystemUtils, ERS_CLASS_SceneManager* SceneManager, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_CLASS_VisualRenderer* VisualRenderer) {

    SystemUtils_ = SystemUtils;
    SceneManager_ = SceneManager;
    ProjectUtils_ = ProjectUtils;
    VisualRenderer_ = VisualRenderer;
    SystemUtils_->Logger_->Log("Editor Setting Up File Menu", 4);

    SceneWriter_ = std::make_unique<SceneWriter>(SystemUtils_);
    ImportAsset_ = std::make_unique<GUI_ImportAsset>(SystemUtils_);
    ShaderEditor_ = std::make_unique<Window_ShaderEditor>(SystemUtils_, ProjectUtils_, VisualRenderer_);
    Window_ProjectSettings_ = std::make_unique<Window_ProjectSettings>(ProjectUtils, SystemUtils);

}

GUI_Menu_File::~GUI_Menu_File() {

    SystemUtils_->Logger_->Log("Editor Destroying File Menu", 4);

}

void GUI_Menu_File::Draw() {

    // File Menu
    if (ImGui::BeginMenu("File")) {

        // Project Options
        if (ImGui::MenuItem("Save Project")) {
            ProjectUtils_->ProjectManager_->WriteProject(1);
        }
        if (ImGui::MenuItem("Project Settings")) {
            Window_ProjectSettings_->Enabled_ = !Window_ProjectSettings_->Enabled_;
        }
        ImGui::Separator();

        if (ImGui::MenuItem("Import Model")) {
            ImportAsset_->OpenFileDialog();
        }
        ImGui::Separator();


        // Shader Editor
        if (ImGui::MenuItem("Shader Editor")) {
            ShaderEditor_->Enabled_ = !ShaderEditor_->Enabled_;
        }
        ImGui::Separator();

        // Save Options
        if (ImGui::MenuItem("Save Active Scene")) {
            SceneWriter_->ProcessScene(
                SceneManager_->Scenes_[SceneManager_->ActiveScene_].get(),
                SceneManager_->Scenes_[SceneManager_->ActiveScene_]->ScenePath
                );
        }
        if (ImGui::MenuItem("Save All Scenes")) {
            for (int i = 0; (long)i < (long)SceneManager_->Scenes_.size(); i++) {
                SceneWriter_->ProcessScene(
                    SceneManager_->Scenes_[i].get(),
                    SceneManager_->Scenes_[i]->ScenePath
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
    ShaderEditor_->Draw();


}