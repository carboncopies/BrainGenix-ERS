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
        SelectedViewportIndex_ = std::min((int)VisualRenderer_->Viewports_.size() - 1, SelectedViewportIndex_);


        if (Visible) {

            // Show Information About Every Viewport
            if (ImGui::BeginCombo("Viewport", VisualRenderer_->Viewports_[SelectedViewportIndex_]->Name.c_str())) {
                for (unsigned int i = 0; i < VisualRenderer_->Viewports_.size(); i++) {
                    bool IsSelected = SelectedViewportIndex_ == (int)i;
                    if (ImGui::Selectable(VisualRenderer_->Viewports_[i]->Name.c_str(), &IsSelected)) {
                        SelectedViewportIndex_ = i;
                    }
                }
            ImGui::EndCombo();
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();


            ERS_STRUCT_Viewport* Viewport =  VisualRenderer_->Viewports_[i].get();     

            // Movement Speed Controls
            float MinSpeed, MaxSpeed, CurrentSpeed;
            Viewport->Processor->GetMovementSpeedBoundries(MinSpeed, MaxSpeed);
            Viewport->Processor->GetMovementSpeed(CurrentSpeed);
            ImGui::DragFloat("Movement Speed", &CurrentSpeed);
            ImGui::DragFloat("Minimum Speed", &MinSpeed);
            ImGui::DragFloat("Maximum Speed", &MaxSpeed);
            Viewport->Processor->SetMovementSpeed(CurrentSpeed);
            Viewport->Processor->SetMovementSpeedBoundries(MinSpeed, MaxSpeed);
            


        }



    // End System Controls Window
    ImGui::End();

    }



}