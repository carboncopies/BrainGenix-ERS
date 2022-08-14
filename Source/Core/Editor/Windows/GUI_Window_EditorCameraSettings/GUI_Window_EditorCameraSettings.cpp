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
            ImGuiTabBarFlags Flags = ImGuiTabBarFlags_FittingPolicyScroll | ImGuiTabBarFlags_NoCloseWithMiddleMouseButton | ImGuiTabBarFlags_TabListPopupButton;
            if (ImGui::BeginTabBar("Viewports", Flags)) {

                if (ImGui::BeginCombo("Viewport")) {
                    for (unsigned int i = 0; i < VisualRenderer_->Viewports_.size(); i++) {
                        bool IsSelected = SelectedViewportIndex_ == i;
                        if (ImGui::Selectable(VisualRenderer_->Viewports_[i]->Name.c_str(), &IsSelected)) {
                            SelectedViewportIndex_ = i;
                        }
                    }
                ImGui::EndCombo();
                }

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::Text("%s", VisualRenderer_->Viewports_[SelectedViewportIndex_]->Name.c_str());


            ImGui::EndTabBar();
            }

        }



    // End System Controls Window
    ImGui::End();

    }



}