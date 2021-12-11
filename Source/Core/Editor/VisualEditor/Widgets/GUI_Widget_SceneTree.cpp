//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-07
*/

#include <GUI_Widget_SceneTree.h>

// Constructor
Widget_SceneTree::Widget_SceneTree(SceneManager* SceneManager) {

    // Update Ptr
    SceneManager_ = SceneManager;


}

// Destructor
Widget_SceneTree::~Widget_SceneTree() {
    
}

// Define Draw Function
void Widget_SceneTree::Draw() {


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

                        // Rename Scene
                        if (ImGui::MenuItem("Rename")) {
                            ImGui::OpenPopup("Rename Scene");
                            std::cout<<"Enabling Popup\n";
                        }

                    ImGui::EndPopup();
                    }

ImGui::OpenPopup("Rename Scene");

                    if (ImGui::BeginPopupModal("Rename Scene", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                        std::cout<<"Opening Popup\n";
                        ImGui::SetItemDefaultFocus();
                        ImGui::InputTextWithHint("Rename Scene", "Enter New Scene Name", SceneInputName_, IM_ARRAYSIZE(SceneInputName_));

                        ImGui::Separator();

                        if (ImGui::Button("Rename", ImVec2(120, 0))) {
                            SceneManager_->Scenes_[SceneIndex].SceneName = std::string(SceneInputName_);
                            ImGui::CloseCurrentPopup();
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                            ImGui::CloseCurrentPopup();
                        }

                        ImGui::EndPopup();
                    }





                    if (TreeNode) {

                        DrawScene(&SceneManager_->Scenes_[SceneIndex]);

                        ImGui::TreePop();
                    }



                }

            ImGui::EndChild();
            }

        ImGui::ShowDemoWindow();

            

        // End System Controls Window
        ImGui::End();

    }



}


// Draw Contents Of Scene To Scene Tree Widget Tree Node
void Widget_SceneTree::DrawScene(ERS_OBJECT_SCENE* Scene) {

    // Get Selected Item
    int SelectedSceneObjectIndex = Scene->SelectedModel;

    // Iterate Through Scene Objects
    for (int ObjectIndex = 0; ObjectIndex < Scene->Models.size(); ObjectIndex++) {

        // Get Name Of Object
        const char* ObjectName = Scene->Models[ObjectIndex].Name.c_str();

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


    }


}