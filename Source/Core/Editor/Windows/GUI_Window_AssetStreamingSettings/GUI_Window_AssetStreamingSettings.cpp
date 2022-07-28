//======================================================================//
// This file is part of the BrainGenix-ERS Environment AssetStreaming System //
//======================================================================//

#include <GUI_Window_AssetStreamingSettings.h>

GUI_Window_AssetStreamingSettings::GUI_Window_AssetStreamingSettings(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    ModelLoader_ = ProjectUtils_->ModelLoader_.get();
    SystemUtils_->Logger_->Log("Initializing AssetStreaming Settings GUI_Window", 5);

}

GUI_Window_AssetStreamingSettings::~GUI_Window_AssetStreamingSettings() {

}

void GUI_Window_AssetStreamingSettings::Draw() {

    if (Enabled_) {
        bool Visible = ImGui::Begin("AssetStreaming Settings", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(400,250), ImGuiCond_FirstUseEver);


            if (Visible) {

                ImGui::DragFloat("VRAM Cutoff", &ModelLoader_->AssetStreamingManager_->R)


            }



        // End System Controls Window
        ImGui::End();

    }

}