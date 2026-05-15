//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_File.h>
#include <EditorLocalization.h>

namespace Localization = ERS::Editor::Localization;

GUI_Menu_File::GUI_Menu_File(ERS_STRUCT_SystemUtils* SystemUtils, ERS_CLASS_SceneManager* SceneManager, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_STRUCT_Windows* Windows) {

    SystemUtils_ = SystemUtils;
    SceneManager_ = SceneManager;
    ProjectUtils_ = ProjectUtils;
    Windows_ = Windows;

    SystemUtils_->Logger_->Log("Editor Setting Up File Menu", 4);

    SceneWriter_ = std::make_unique<SceneWriter>(SystemUtils_);


}

GUI_Menu_File::~GUI_Menu_File() {

    SystemUtils_->Logger_->Log("Editor Destroying File Menu", 4);

}

void GUI_Menu_File::Draw() {

    // File Menu
    if (ImGui::BeginMenu(Localization::Get(Localization::TextID::File))) {

        ImGui::MenuItem(Localization::Get(Localization::TextID::New), "", &Windows_->GUI_Window_NewProject_->Enabled_);
        ImGui::MenuItem(Localization::Get(Localization::TextID::Open), "", &Windows_->GUI_Window_OpenProject_->Enabled_);
        ImGui::Separator();


        ImGui::Separator();
        if (ImGui::MenuItem(Localization::Get(Localization::TextID::Save))) {

            SystemUtils_->Logger_->Log("Saving Project Data", 4);
            ProjectUtils_->ProjectManager_->WriteProject(1);

            SystemUtils_->Logger_->Log("Saving All Scenes", 4);
            for (int i = 0; (long)i < (long)SceneManager_->Scenes_.size(); i++) {
                SystemUtils_->Logger_->Log(std::string("Saving Data For Scene ") + std::to_string(i), 3);
                SceneWriter_->ProcessScene(
                    SceneManager_->Scenes_[i].get(),
                    SceneManager_->Scenes_[i]->ScenePath
                    );
            }
        }

        ImGui::MenuItem(Localization::Get(Localization::TextID::ProjectSettings), "", &Windows_->GUI_Window_ProjectSettings_->Enabled_);
        ImGui::MenuItem(Localization::Get(Localization::TextID::About), "", &Windows_->GUI_Window_About_->Enabled_);

        ImGui::Separator();

        ImGui::MenuItem(Localization::Get(Localization::TextID::ImportModel), "", &Windows_->GUI_Window_ImportModel_->Enabled_);
        ImGui::MenuItem(Localization::Get(Localization::TextID::ImportModelsInDirectory), "", &Windows_->GUI_Window_ImportModelDirectory_->Enabled_);

        ImGui::Separator();

        // Exit Options
        if (ImGui::MenuItem(Localization::Get(Localization::TextID::Exit))) {
            *SystemUtils_->SystemShouldRun_ = false;
        }

        
    ImGui::EndMenu();
    }



}
