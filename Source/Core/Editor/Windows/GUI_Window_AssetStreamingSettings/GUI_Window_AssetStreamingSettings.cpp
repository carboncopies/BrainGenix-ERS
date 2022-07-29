//======================================================================//
// This file is part of the BrainGenix-ERS Environment AssetStreaming System //
//======================================================================//

#include <GUI_Window_AssetStreamingSettings.h>

GUI_Window_AssetStreamingSettings::GUI_Window_AssetStreamingSettings(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    ModelLoader_ = ProjectUtils_->ModelLoader_.get();
    SystemUtils_->Logger_->Log("Initializing AssetStreaming Settings GUI_Window", 5);

    // Copy In Default Parameters
    TextureStreamingThreads_ = ModelLoader_->AssetStreamingManager_->AsyncTextureUpdater_->GetNumThreads();
    TextureStreamingQueueLimit_ = ModelLoader_->AssetStreamingManager_->AsyncTextureUpdater_->GetQueueLimit();

    MaxThreads_ = std::thread::hardware_concurrency();

}

GUI_Window_AssetStreamingSettings::~GUI_Window_AssetStreamingSettings() {

}

void GUI_Window_AssetStreamingSettings::Draw() {

    if (Enabled_) {
        bool Visible = ImGui::Begin("Asset Streaming Settings", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(400,250), ImGuiCond_FirstUseEver);


            if (Visible) {

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Texture Streaming");
                ImGui::Separator();
                ImGui::Spacing();


                ImGui::DragFloat("VRAM Cutoff", &ModelLoader_->AssetStreamingManager_->DistanceCutoffVRAM_, 0.01f, 0.0f, 999.0f);
                ImGui::DragFloat("RAM Cutoff", &ModelLoader_->AssetStreamingManager_->DistanceCutoffRAM_, 0.01f, 0.0f, 999.0f);

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                ImGui::SliderInt("Texture Streaming Threads", &TextureStreamingThreads_, 1, MaxThreads_);
                ImGui::SliderInt("Queue Limit", &TextureStreamingQueueLimit_, 1, MaxThreads_ * 25);

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();
                if (ImGui::Button("Apply")) {

                    // Update Queue Info
                    ModelLoader_->AssetStreamingManager_->AsyncTextureUpdater_->SetQueueLimit(TextureStreamingQueueLimit_);

                    // Update Threads
                    int LastThreadCount = ModelLoader_->AssetStreamingManager_->AsyncTextureUpdater_->GetNumThreads();
                    if (LastThreadCount != TextureStreamingThreads_) {
                        ModelLoader_->AssetStreamingManager_->AsyncTextureUpdater_->SetNumThreads(TextureStreamingThreads_);
                        ModelLoader_->AssetStreamingManager_->AsyncTextureUpdater_->TeardownThreads();
                        ModelLoader_->AssetStreamingManager_->AsyncTextureUpdater_->SetupThreads();
                    }
                }


            }



        // End System Controls Window
        ImGui::End();

    }

}