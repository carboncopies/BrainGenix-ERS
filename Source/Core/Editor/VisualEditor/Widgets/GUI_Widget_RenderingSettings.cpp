//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-02
*/

#include <GUI_Widget_RenderingSettings.h>

// Constructor
Widget_RenderingSettings::Widget_RenderingSettings(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy System Utils
    SystemUtils_ = SystemUtils;

    // Log Init
    SystemUtils_->Logger_->Log("Initializing Rendering Settings Widget", 5);

}

// Destructor
Widget_RenderingSettings::~Widget_RenderingSettings() {

}

// Define Draw Function
void Widget_RenderingSettings::Draw() {

    // If Window Drawing Enabled
    if (Enabled_) {
        bool Visible = ImGui::Begin("Rendering Settings", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(400,250), ImGuiCond_FirstUseEver);


            if (Visible) {

                // Wireframe Rendering Mode
                ImGui::Checkbox("Wireframe Rendering Mode", &OpenGLDrawLines_);
                ImGui::NewLine();

                // Rendering Background Clear Color
                ImGui::ColorEdit4("Background Clear Color", (float*)&ClearColor_);
                ImGui::NewLine();


                // Framerate Settings
                ImGui::Separator();
                ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 1.0f), "Framerate Settings:");

                // Framerate Cap (Linux Only, Windows Doesn't work for whatever reason)
                if (false) {

                    int OldFrameRate = SystemUtils_->FramerateManager_->TargetFrameRate_;
                    ImGui::SliderInt("Target Framerate", &SystemUtils_->FramerateManager_->TargetFrameRate_, 10, 100);
                    if (OldFrameRate != SystemUtils_->FramerateManager_->TargetFrameRate_) {
                        SystemUtils_->FramerateManager_->SetTargetFramerate(SystemUtils_->FramerateManager_->TargetFrameRate_);
                    }

                    // Unlock FPS
                    ImGui::Checkbox("Unlock Framerate", &SystemUtils_->FramerateManager_->UnlockFramerate_);

                    // Sync To Monitor
                    ImGui::SameLine();
                    ImGui::Checkbox("Sync To Monitor", &SystemUtils_->FramerateManager_->SyncToMonitor_);

                } else {

                    bool UnlockFR = SystemUtils_->FramerateManager_->UnlockFramerate_;
                    bool SyncFR = SystemUtils_->FramerateManager_->SyncToMonitor_;

                    UnlockFR = ImGui::RadioButton("Unlock Framerate", UnlockFR);
                    ImGui::SameLine();
                    SyncFR = ImGui::RadioButton("Sync To Monitor", SyncFR);


                    if (UnlockFR) {
                        SyncFR = false;
                    } else if (SyncFR) {
                        UnlockFR = false;
                    }
                    
                    std::cout<<UnlockFR<<SyncFR<<std::endl;

                    SystemUtils_->FramerateManager_->UnlockFramerate_ = UnlockFR;
                    SystemUtils_->FramerateManager_->SyncToMonitor_ = SyncFR;

                }

            }



        // End System Controls Window
        ImGui::End();

    }

    // Update OpenGL Settings
    if (OpenGLDrawLines_) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glClearColor(ClearColor_.x, ClearColor_.y, ClearColor_.z, ClearColor_.w);


}