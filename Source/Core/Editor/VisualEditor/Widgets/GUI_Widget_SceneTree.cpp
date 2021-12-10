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

                    // Begin Tree
                    if (ImGui::TreeNodeEx((void*)(intptr_t)SceneIndex, NodeFlags, "%s", SceneName)) {

                        DrawScene(&SceneManager_->Scenes_[SceneIndex]);

                        ImGui::TreePop();
                    }

                    // Context Menu
                    if (ImGui::BeginPopup("Tree Item Popup Context")) {
                        bool x= false;
                        ImGui::MenuItem("foo", "", &x);

                        ImGui::EndPopup();
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