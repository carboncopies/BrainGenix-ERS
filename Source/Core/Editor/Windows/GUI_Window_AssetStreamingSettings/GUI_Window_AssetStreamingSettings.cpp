//======================================================================//
// This file is part of the BrainGenix-ERS Environment AssetStreaming System //
//======================================================================//

#include <GUI_Window_AssetStreamingSettings.h>

GUI_Window_AssetStreamingSettings::GUI_Window_AssetStreamingSettings(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing AssetStreaming Settings GUI_Window", 5);

    // Setup Default Values For Input Fields

}

GUI_Window_AssetStreamingSettings::~GUI_Window_AssetStreamingSettings() {

}

void GUI_Window_AssetStreamingSettings::Draw() {

    if (Enabled_) {
        bool Visible = ImGui::Begin("AssetStreaming Settings", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(400,250), ImGuiCond_FirstUseEver);


            if (Visible) {

                // Get Rendering Settings

                // AssetStreaming Background Clear Color
                ImGui::ColorEdit4("Background Clear Color", (float*)&ClearColor_);
                ImGui::NewLine();


            }



        // End System Controls Window
        ImGui::End();

    }

    glClearColor(ClearColor_.x, ClearColor_.y, ClearColor_.z, ClearColor_.w);

}