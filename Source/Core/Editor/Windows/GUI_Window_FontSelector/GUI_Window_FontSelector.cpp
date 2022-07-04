//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//


#include <GUI_Window_FontSelector.h>


GUI_Window_FontSelector::GUI_Window_FontSelector(ERS_CLASS_FontManager* FontManager) {

    FontManager_ = FontManager;

}

GUI_Window_FontSelector::~GUI_Window_FontSelector() {

}


void GUI_Window_FontSelector::Draw() {

    if (Enabled_) {
    ImGuiWindowFlags Flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse;
    bool Visible = ImGui::Begin("Pick Color Font", &Enabled_, Flags);

            ImGui::SetWindowSize(ImVec2(0, 0));


            if (Visible) {

                // Put Radio Buttons Here
                ImGui::BeginChild("Font Selector", ImVec2(250, 250), true);

                    static int FontSelector = 0;
                    for (int i = 0; (long)i < (long)FontManager_->FontNames_.size(); i++) {

                        ImGui::RadioButton(FontManager_->FontNames_[i].c_str(), &FontSelector, i);

                    }
                    

                ImGui::EndChild();


                ImGui::Separator();


                // Reload Button
                if (ImGui::Button("Reload Fonts")) {
                    FontManager_->LoadFonts();
                }
                ImGui::SameLine();

                // Apply Button
                if (ImGui::Button("Apply")) {
                    FontManager_->ApplyFonts(FontSelector);
                }
                ImGui::SameLine();

                // Close Button
                if (ImGui::Button("Close")) {
                    Enabled_ = false;
                }
            

            }

    ImGui::End();
    }

}