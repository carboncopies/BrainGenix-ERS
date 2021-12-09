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

            // Create Scene Trees
            for (int SceneIndex = 0; SceneIndex<SceneManager_->Scenes_.size(); SceneIndex++) {

                // Indictate Which Scene Is Active
                int ActiveScene = SceneManager_->ActiveScene_;
                ImGuiTreeNodeFlags NodeFlags = ImGuiTreeNodeFlags_OpenOnDoubleClick;
                if (SceneIndex == ActiveScene) {
                    NodeFlags |= ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Selected;
                }

                // Begin Tree
                const char* SceneName = SceneManager_->Scenes_[SceneIndex].SceneName.c_str();
                if (ImGui::TreeNodeEx((void*)(intptr_t)SceneIndex, NodeFlags, "%s", SceneName)) {

                    // If User Selected This Scene, Set Active Scene To This One
                    //ImGui::SameLine();
                    
                    if (ImGui::IsKeyPressed('LCONTROL') && ImGui::IsItemClicked()) {
                        SceneManager_->ActiveScene_ = SceneIndex;
                        SceneManager_->Scenes_[SceneIndex].HasSelectionChanged = true;
                    }

                    // Draw Scene
                    DrawScene(&SceneManager_->Scenes_[SceneIndex]);



                    // End Node
                    ImGui::TreePop();
                }


 

            }



            

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