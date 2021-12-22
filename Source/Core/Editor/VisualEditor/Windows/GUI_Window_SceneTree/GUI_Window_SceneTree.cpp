//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-07
*/

#include <GUI_Window_SceneTree.h>

// Constructor
Window_SceneTree::Window_SceneTree(std::shared_ptr<SceneManager> SceneManager) {

    // Update Ptr
    SceneManager_ = SceneManager;

    // Setup Subwindows
    Subwindow_SceneRenameModal_ = new Subwindow_SceneRenameModal(SceneManager_);
    Subwindow_ModelRenameModal_ = new Subwindow_ModelRenameModal(SceneManager_);
    Subwindow_DeleteScene_ = new Subwindow_DeleteScene(SceneManager_);
    Subwindow_DeleteModel_ = new Subwindow_DeleteModel(SceneManager_);

}

// Destructor
Window_SceneTree::~Window_SceneTree() {

    // Cleanup Instances
    Subwindow_SceneRenameModal_->~Subwindow_SceneRenameModal();
    Subwindow_ModelRenameModal_->~Subwindow_ModelRenameModal();
    Subwindow_DeleteScene_->~Subwindow_DeleteScene();
    Subwindow_DeleteModel_->~Subwindow_DeleteModel();

}

// Define Draw Function
void Window_SceneTree::Draw() {

    // Draw Popup Modals
    Subwindow_SceneRenameModal_->Draw();
    Subwindow_ModelRenameModal_->Draw();
    Subwindow_DeleteScene_->Draw();
    Subwindow_DeleteModel_->Draw();


    // If Window Drawing Enabled
    if (Enabled_) {
        ImGui::Begin("Scene Tree", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(400,250), ImGuiCond_FirstUseEver);


            // Initialize Vars
            int ActiveScene = SceneManager_->ActiveScene_;
            
            // Convert Vector to Array
            if (ImGui::BeginCombo("Active Scene", SceneManager_->Scenes_[ActiveScene].SceneName.c_str())) {

                for (int i = 0; i < SceneManager_->Scenes_.size(); i++) {

                    // Setup Selector
                    bool Selector = false;
                    if (i == SceneManager_->ActiveScene_) {
                        Selector = true;
                    }

                    // Create Selectable Item
                    ImGui::Selectable(SceneManager_->Scenes_[i].SceneName.c_str(), &Selector);

                    // If Item Selected, Update Scene To Current Index
                    if (Selector) {
                        SceneManager_->ActiveScene_ = i;
                        SceneManager_->Scenes_[i].HasSelectionChanged = true;
                    }
                }

            ImGui::EndCombo();
            }

            // Active Scene Dropdown
            ImGui::Separator();



            // Draw Selector In Child Frame
            if (ImGui::BeginChild("Tree Selector")) {

                // Create Scene Trees
                for (int SceneIndex = 0; SceneIndex<SceneManager_->Scenes_.size(); SceneIndex++) {

                    // Setup Tree Flags
                    ImGuiTreeNodeFlags NodeFlags = ImGuiTreeNodeFlags_OpenOnArrow;
                    if (SceneIndex == ActiveScene) {
                        NodeFlags |= ImGuiTreeNodeFlags_Selected;
                    }

                    // Get Tree Metadata
                    const char* SceneName = SceneManager_->Scenes_[SceneIndex].SceneName.c_str();
                    const char* PopupName = std::string(std::string("SceneTreePopupMenu_") + std::to_string(SceneIndex)).c_str();


                    // Begin Tree
                    bool TreeNode = ImGui::TreeNodeEx((void*)(intptr_t)SceneIndex, NodeFlags, "%s", SceneName);

                    // Context Menu
                    if (ImGui::BeginPopupContextItem()) {

                        // Menu Items
                        if (ImGui::MenuItem("Rename")) {
                            Subwindow_SceneRenameModal_->Activate(SceneIndex);
                        } if (ImGui::MenuItem("Duplicate")) {
                            GUI_Windowutil_DuplicateScene(SceneManager_, SceneIndex); // FIXME: Will need to update how scenes are saved, as right now these will overwrite other scenes when saved. (Solution could be a scenes folder?)
                        }


                        ImGui::Separator();

                        if (ImGui::MenuItem("Delete")) {
                            Subwindow_DeleteScene_->DeleteScene(SceneIndex);
                        }


                    ImGui::EndPopup();
                    }



                    if (TreeNode) {

                        DrawScene(&SceneManager_->Scenes_[SceneIndex], SceneIndex);

                        ImGui::TreePop();
                    }



                }

            ImGui::EndChild();
            }


            

        // End System Controls Window
        ImGui::End();

    }



}


// Draw Contents Of Scene To Scene Tree Window Tree Node
void Window_SceneTree::DrawScene(ERS_OBJECT_SCENE* Scene, int SceneIndex) {

    // Get Selected Item
    int SelectedSceneObjectIndex = Scene->SelectedModel;

    // Iterate Through Scene Objects
    for (int ObjectIndex = 0; ObjectIndex < Scene->Models.size(); ObjectIndex++) {

        // Get Name Of Object
        const char* ObjectName = Scene->Models[ObjectIndex]->Name.c_str();

        // Setup Node Flags
        ImGuiTreeNodeFlags TreeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        if (SelectedSceneObjectIndex == ObjectIndex) {
            TreeFlags |= ImGuiTreeNodeFlags_Selected;
        }

        // Create Tree Node
        ImGui::TreeNodeEx((void*)(intptr_t)ObjectIndex, TreeFlags, "%s", ObjectName);

        // If User Clicks Node, Update Object Index
        if (ImGui::IsItemClicked()) {
            Scene->SelectedModel = ObjectIndex;
            Scene->HasSelectionChanged = true;
        }




        // Context Menu
        if (ImGui::BeginPopupContextItem()) {

            // Rename Model
            if (ImGui::MenuItem("Rename")) {
                Subwindow_ModelRenameModal_->Activate(SceneIndex, ObjectIndex);

            } if (ImGui::MenuItem("Duplicate")) {
                GUI_Windowutil_DuplicateModel(SceneManager_, SceneIndex, ObjectIndex);

            }


            ImGui::Separator();

            if (ImGui::MenuItem("Delete")) {
                Subwindow_DeleteModel_->DeleteModel(SceneIndex, ObjectIndex);
            }



        ImGui::EndPopup();
        }


    }


}