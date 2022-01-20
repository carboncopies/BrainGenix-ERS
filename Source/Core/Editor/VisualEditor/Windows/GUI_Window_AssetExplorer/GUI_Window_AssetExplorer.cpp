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
        ImGui::SetWindowSize(ImVec2(300,600), ImGuiCond_FirstUseEver);


        // TODO: Add "selectables" in advanced mode which list all assetids and what they do. perhaps oculd be like this: ID (One-letter-abbreviation for what it does) or an icon if we're feeling fancy
        // add the option to import assets from the explorer into the active scene
        // add the normal mode which only shows ers assets and has names rather than ids
        // add a system to have files/folder abstractions which enables the user to organize their assets under folders, implement drag/drop with this.

        if (Visible) {

            
            if (AdvancedMode_) {
            ImGui::BeginTabBar("Asset Selection Mode");

                // Model Explorer
                if (ImGui::BeginTabItem("Models")) {

                    // 

                ImGui::EndTabItem();
                }

                // "Advanced" Asset ID Viewer
                if (ImGui::BeginTabItem("Raw Asset IDs")) {

                    // Explorer Child Window
                    ImVec2 IDExplorerSize = ImVec2(ImGui::GetWindowWidth()-300, 0);
                    ImGui::BeginChild("ID Explorer Child Node", IDExplorerSize);

                        // Child Node Title
                        ImGui::Separator();
                        ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Asset ID");
                        ImGui::Separator();

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
                                LastSelectedIndex_ = i;
                            }
                        }

                    ImGui::EndChild();
                    ImGui::SameLine();
                    ImGui::BeginChild("Description Child Node");

                        // Child Node Title
                        ImGui::Separator();
                        ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Description");
                        ImGui::Separator();

                        // Add Type
                        long SelectedID = SystemUtils_->ERS_IOSubsystem_->UsedAssetIDs_[LastSelectedIndex_];
                        const char* AssetType = SystemUtils_->ERS_IOSubsystem_->AssetIndexIOManager_->AssetTypeName_[SelectedID].c_str();
                        ImGui::Text("Type: %s", AssetType);

                        // Add Dates
                        const char* AssetCreationDate = SystemUtils_->ERS_IOSubsystem_->AssetIndexIOManager_->AssetCreationDate_[SelectedID].c_str();
                        ImGui::Text("Date Created: %s", AssetCreationDate);

                        const char* AssetModificationDate = SystemUtils_->ERS_IOSubsystem_->AssetIndexIOManager_->AssetModificationDate_[SelectedID].c_str();
                        ImGui::Text("Type: %s", AssetModificationDate);


                    ImGui::EndChild();

                ImGui::EndTabItem();
                }

                // Tools bar
                if (ImGui::BeginTabItem("Tools")) {

                    // Child Window
                    ImGui::BeginChild("Asset Explorer Tools");


                    // Heading
                    ImGui::Separator();
                    ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Debugging Tools");
                    ImGui::Separator();


                    // Refresh Button
                    if (ImGui::Button("Refresh Asset Index")) {
                        SystemUtils_->ERS_IOSubsystem_->IndexUsedAssetIDs();
                    }

                    // End Child
                    ImGui::EndChild();

                ImGui::EndTabItem();
                }

            ImGui::EndTabBar();
            }


        }

    ImGui::End();
    }


}