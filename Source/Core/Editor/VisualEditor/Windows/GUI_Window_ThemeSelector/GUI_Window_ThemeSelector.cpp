//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Window_ThemeSelector.h>


Window_ThemeSelector::Window_ThemeSelector(std::shared_ptr<ERS_CLASS_ThemeManager> ThemeManager) {

    // Copy Pointers
    ThemeManager_ = ThemeManager;

}

void Window_ThemeSelector::Draw() {

    // Draw Color Picker Menu
    if (Enabled_) {
        ImGuiWindowFlags Flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("Pick Color Theme", &Enabled_, Flags);

            ImGui::SetWindowSize(ImVec2(0, 0));


            // Put Radio Buttons Here
            ImGui::BeginChild("Theme Selector", ImVec2(250, 250), true);

                static int ThemeSelector = 0;
                for (int i = 0; i < ThemeManager_->ThemeNames_.size(); i++) {

                    ImGui::RadioButton(ThemeManager_->ThemeNames_[i].c_str(), &ThemeSelector, i);

                }
                

            ImGui::EndChild();


            ImGui::Separator();


            // Reload Button
            if (ImGui::Button("Reload Themes")) {
                ThemeManager_->LoadThemes();
            }
            ImGui::SameLine();

            // Apply Button
            if (ImGui::Button("Apply")) {
                ThemeManager_->ApplyThemes(ThemeSelector);
            }
            ImGui::SameLine();

            // Close Button
            if (ImGui::Button("Close")) {
                ShowColorThemePicker_ = false;
            }
            

        ImGui::End();
    }

}