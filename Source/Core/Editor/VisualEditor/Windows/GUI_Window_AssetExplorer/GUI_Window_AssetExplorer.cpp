//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Window_AssetExplorer.h>


// Constructor
Window_AssetExplorer::Window_AssetExplorer(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy System Utils Pointer Struct
    SystemUtils_ = SystemUtils;

    // Log Init
    SystemUtils_->Logger_->Log("Initializing GUI_Window_AssetExplorer", 5);

}

// Destructor
Window_AssetExplorer::~Window_AssetExplorer() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("GUI_Window_AssetExplorer Destructor Called", 6);


}


// Draw Window
void Window_AssetExplorer::Draw() {

    if (Enabled_) {
    bool Visible = ImGui::Begin("Asset Explorer", &Enabled_);

        // Set Default Window Size
        ImGui::SetWindowSize(ImVec2(300,0), ImGuiCond_FirstUseEver);


        // TODO: Add "selectables" in advanced mode which list all assetids and what they do. perhaps oculd be like this: ID (One-letter-abbreviation for what it does) or an icon if we're feeling fancy
        // add the option to import assets from the explorer into the active scene
        // add the normal mode which only shows ers assets and has names rather than ids
        // add a system to have files/folder abstractions which enables the user to organize their assets under folders, implement drag/drop with this.

        if (Visible) {

            
            if (AdvancedMode_) {
            ImGui::BeginChild("Asset Data Child");
            ImGui::BeginTabBar("Asset Selection Mode");

                // "Advanced" Asset ID Viewer
                if (ImGui::BeginTabItem("Raw Asset IDs")) {

                    // Update Asset ID Selection List
                    int ListLengthDelta = SystemUtils_->ERS_IOSubsystem_->UsedAssetIDs_.size() - AssetIDSelectionList_.size();
                    if (ListLengthDelta > 0) {
                        for (int i = 0; i < ListLengthDelta; i++) {
                            AssetIDSelectionList_.push_back(false);
                        }
                    } else if (ListLengthDelta < 0) {
                        for (int i = 0; i < abs(ListLengthDelta); i++) {
                            AssetIDSelectionList_.pop_back();
                        }
                    }

                    // Iterate Through All Indexed Assets, List In Child Window
                    for (int i = 0; i < SystemUtils_->ERS_IOSubsystem_->UsedAssetIDs_.size(); i++) {
                        bool ItemSelected = ImGui::Selectable(std::to_string(SystemUtils_->ERS_IOSubsystem_->UsedAssetIDs_[i]).c_str(), AssetIDSelectionList_[i]);
                        if (ItemSelected) {
                            AssetIDSelectionList_[i] = !AssetIDSelectionList_[i];
                        }
                    }

                ImGui::EndTabItem();
                }

            ImGui::EndTabBar();
            ImGui::EndChild();
            }


        }

    ImGui::End();
    }


}