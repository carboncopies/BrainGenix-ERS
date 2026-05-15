//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_Settings.h>
// cppcheck-suppress missingIncludeSystem
#include <EditorLocalization.h>

namespace Localization = ERS::Editor::Localization;

GUI_Menu_Settings::GUI_Menu_Settings(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_HumanInputDeviceUtils* HIDUtils, ERS_STRUCT_Windows* Windows) {

    SystemUtils_ = SystemUtils;
    HIDUtils_ = HIDUtils;
    Windows_ = Windows;

    SystemUtils_->Logger_->Log("Editor Setting Up Settings Menu", 4);



}

GUI_Menu_Settings::~GUI_Menu_Settings() {

    SystemUtils_->Logger_->Log("Editor Destroying Settings Menu", 4);

}

void GUI_Menu_Settings::Draw() {

    // File Menu
    if (ImGui::BeginMenu(Localization::Get(Localization::TextID::Settings))) {

        // Interface Config
        ImGui::MenuItem(Localization::Get(Localization::TextID::ColorTheme), "", &Windows_->GUI_Window_ThemeSelector_->Enabled_);
        ImGui::MenuItem(Localization::Get(Localization::TextID::SystemFont), "", &Windows_->GUI_Window_FontSelector_->Enabled_);
        if (ImGui::BeginMenu(Localization::Get(Localization::TextID::Language))) {
            for (int i = 0; i < Localization::GetLanguageCount(); i++) {
                bool IsSelected = i == Localization::GetActiveLanguageIndex();
                if (ImGui::MenuItem(Localization::GetLanguageName(i), "", IsSelected)) {
                    Localization::SetActiveLanguageFromIndex(i);
                }
            }
        ImGui::EndMenu();
        }

        ImGui::Separator();
        if (ImGui::BeginMenu(Localization::Get(Localization::TextID::EditorSettings))) {
            ImGui::MenuItem(Localization::Get(Localization::TextID::EditorCameraSettings), "", &Windows_->GUI_Window_EditorCameraSettings_->Enabled_);
        ImGui::EndMenu();
        }

        ImGui::Separator();
        if (ImGui::BeginMenu(Localization::Get(Localization::TextID::EngineSettings))) {
            ImGui::MenuItem(Localization::Get(Localization::TextID::RenderingSettings), "", &Windows_->GUI_Window_RenderingSettings_->Enabled_);
            ImGui::MenuItem(Localization::Get(Localization::TextID::AssetStreamingSettings), "", &Windows_->GUI_Window_AssetStreamingSettings_->Enabled_);
        ImGui::EndMenu();
        }

        ImGui::Separator();
        if (ImGui::BeginMenu(Localization::Get(Localization::TextID::GameControllers))) {

            // Refresh
            if (ImGui::MenuItem(Localization::Get(Localization::TextID::DetectNewControllers))) {
                HIDUtils_->ControllerInputManager->DetectControllers();
            }

            // Open Settings MEnu
            ImGui::MenuItem(Localization::Get(Localization::TextID::GameControllerSettings), "", &Windows_->GUI_Window_ControllerSettings_->Enabled_);

        ImGui::EndMenu();
        }


    ImGui::EndMenu();
    }


}
