//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Window_ImportProgressBar.h>


// Constructor
Window_ImportProgressBar::Window_ImportProgressBar(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy System Utils Pointer Struct
    SystemUtils_ = SystemUtils;

}

// Destructor
Window_ImportProgressBar::~Window_ImportProgressBar() {

}


// Update Item Stats
void Window_ImportProgressBar::UpdateSubitems(long Imported, long Total) {

}

// Update Total Model Stats
void Window_ImportProgressBar::UpdateTotalItems(long Current, long Total) {

}

// Draw Window
void Window_ImportProgressBar::Draw() {


    if (Enabled_) {
    ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    ImGui::Begin("Import Status", &Enabled_, WindowFlags);

        // Set Window Size
        ImGui::SetWindowSize(ImVec2(300,0));

        // Set Window Position
        ImVec2 WindowSize = ImGui::GetWindowSize();
        ImVec2 WindowPos = ImVec2(SystemUtils_->RenderWidth_ - WindowSize.x, SystemUtils_->RenderHeight_ - WindowSize.y);
        ImGui::SetWindowPos(WindowPos);

        // Calculate Stats
        LockViewStats_.lock();
        float TotalProgresBarFraction = CurrentAssetNumber_ / TotalAssetsToImport_;
        float ItemProgressBarFraction = SubItemsImported_ / SubItemsToImport_;
        LockViewStats_.unlock();

        // Draw Total Progres Bar
        ImGui::Text("Overall Progress");
        ImGui::ProgressBar(TotalProgresBarFraction);

        ImGui::Text("Item Progress");
        ImGui::ProgressBar(ItemProgressBarFraction);


    ImGui::End();
    }


}