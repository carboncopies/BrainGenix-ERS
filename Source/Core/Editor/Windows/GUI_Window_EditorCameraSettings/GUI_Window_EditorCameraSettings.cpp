//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_EditorCameraSettings.h>

GUI_Window_EditorCameraSettings::GUI_Window_EditorCameraSettings(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing EditorCamera Settings GUI_Window", 5);

    // Setup Default Values For Input Fields
    SystemUtils_->Logger_->Log("Setting Up Default Renderer Setting Input Fields", 3);

    SystemUtils_->Logger_->Log("Copying Shadow Map Resolution", 2);
    ERS_STRUCT_RendererSettings* Settings = SystemUtils_->RendererSettings_.get();
    DepthMapResolution_ = Settings->ShadowMapX_;


    if (Settings->ShadowFilteringType_ == ERS::Renderer::ERS_SHADOW_FILTERING_DISABLED) {
        SelectedShadowFiltering_ = 0;
    } else if (Settings->ShadowFilteringType_ == ERS::Renderer::ERS_SHADOW_FILTERING_PCF) {
        SelectedShadowFiltering_ = 1;
    } else if (Settings->ShadowFilteringType_ == ERS::Renderer::ERS_SHADOW_FILTERING_POISSON_SAMPLING) {
        SelectedShadowFiltering_ = 2;
    } else if (Settings->ShadowFilteringType_ == ERS::Renderer::ERS_SHADOW_FILTERING_STRATIFIED_POISSON_SAMPLING) {
        SelectedShadowFiltering_ = 3;
    }

    if (Settings->ShadowUpdateMode_ == ERS::Renderer::ERS_SHADOW_UPDATE_MODE_DISABLED) {
        SelectedShadowUpdates_ = 0;
    } else if (Settings->ShadowUpdateMode_ == ERS::Renderer::ERS_SHADOW_UPDATE_MODE_RANDOM) {
        SelectedShadowUpdates_ = 1;
    } else if (Settings->ShadowUpdateMode_ == ERS::Renderer::ERS_SHADOW_UPDATE_MODE_CONSECUTIVE) {
        SelectedShadowUpdates_ = 2;
    } else if (Settings->ShadowUpdateMode_ == ERS::Renderer::ERS_SHADOW_UPDATE_MODE_DISTANCE_PRIORITIZED) {
        SelectedShadowUpdates_ = 3;
    } else if (Settings->ShadowUpdateMode_ == ERS::Renderer::ERS_SHADOW_UPDATE_MODE_ALL) {
        SelectedShadowUpdates_ = 4;
    }


}

GUI_Window_EditorCameraSettings::~GUI_Window_EditorCameraSettings() {

}

void GUI_Window_EditorCameraSettings::Draw() {

    if (Enabled_) {
        bool Visible = ImGui::Begin("EditorCamera Settings", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(400,250), ImGuiCond_FirstUseEver);


            if (Visible) {

                // Handle Modifications To Renderer Settings
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
                

            }



        // End System Controls Window
        ImGui::End();

    }



}