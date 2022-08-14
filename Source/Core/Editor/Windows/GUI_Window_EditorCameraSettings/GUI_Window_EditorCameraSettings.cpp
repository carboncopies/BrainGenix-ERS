//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_EditorCameraSettings.h>

GUI_Window_EditorCameraSettings::GUI_Window_EditorCameraSettings(ERS_STRUCT_SystemUtils* SystemUtils, ERS_CLASS_VisualRenderer* VisualRenderer) {

    SystemUtils_    = SystemUtils;
    VisualRenderer_ = VisualRenderer;
    SystemUtils_->Logger_->Log("Initializing Editor Camera Settings GUI_Window", 5);


}

GUI_Window_EditorCameraSettings::~GUI_Window_EditorCameraSettings() {

}

void GUI_Window_EditorCameraSettings::Draw() {

    if (Enabled_) {
        bool Visible = ImGui::Begin("Editor Camera Settings", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(400,250), ImGuiCond_FirstUseEver);

            // Limit Index
            SelectedViewportIndex_ = std::max((int)VisualRenderer_->Viewports_.size() - 1, SelectedViewportIndex_);


            if (Visible) {

                // Show Information About Every Viewport
                ImGuiTabBarFlags Flags = ImGuiTabBarFlags_FittingPolicyScroll;
                if (ImGui::BeginTabBar("Viewports", Flags)) {

                    for (unsigned int i = 0; i < VisualRenderer_->Viewports_.size(); i++) {

                        std::string Name = VisualRenderer_->Viewports_[i]->Name;
                        bool TabSelected = SelectedViewportIndex_ == (int)i;
                        bool TabStatus = ImGui::BeginTabItem(Name.c_str(), &TabSelected);
                        if (TabStatus) {
                            SelectedViewportIndex_ = i;
                        }

                        if (TabSelected) {
                            ImGui::Text(VisualRenderer_->Viewports_[i]->Name.c_str());


                        }
                        ImGui::EndTabItem();
                        
                    

                    }

                ImGui::EndTabBar();
                }

            }



        // End System Controls Window
        ImGui::End();

    }



}