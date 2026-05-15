//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//


#include <GUI_Window_ThemeSelector.h>


GUI_Window_ThemeSelector::GUI_Window_ThemeSelector(ERS_CLASS_ThemeManager* ThemeManager) {

    ThemeManager_ = ThemeManager;

}

GUI_Window_ThemeSelector::~GUI_Window_ThemeSelector() {

}


void GUI_Window_ThemeSelector::Draw() {

    if (Enabled_) {
    ImGuiWindowFlags Flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
    bool Visible = ImGui::Begin("Pick Color Theme", &Enabled_, Flags);

            ImGui::SetWindowSize(ImVec2(0, 0));


            if (Visible) {

                ThemeManager_->CreateThemeMenu();
                ImGui::SameLine();

                // Close Button
                if (ImGui::Button("Close")) {
                    Enabled_ = false;
                }
            

            }

    ImGui::End();
    }

}
