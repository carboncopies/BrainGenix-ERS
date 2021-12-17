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
Window_ImportProgressBar::Window_ImportProgressBar() {

}

// Destructor
Window_ImportProgressBar::~Window_ImportProgressBar() {

}


// Update Item Stats
void Window_ImportProgressBar::UpdateSubitems(long Imported, long Total, std::string CurrentName) {

}

// Update Total Model Stats
void Window_ImportProgressBar::UpdateTotalItems(long Current, long Total) {

}

// Draw Window
void Window_ImportProgressBar::Draw() {

    if (Enabled_) {
    ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoScrollbar;
    ImGui::Begin("Import Status", &Enabled_, WindowFlags);

        ImGui::SetWindowSize(ImVec2(0,0));

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