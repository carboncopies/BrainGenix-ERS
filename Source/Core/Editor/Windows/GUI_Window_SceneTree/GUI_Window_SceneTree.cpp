//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Window_SceneTree.h>

Window_SceneTree::Window_SceneTree(ERS_CLASS_SceneManager* SceneManager, ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, Cursors3D* Cursors3D) {

    SceneManager_ = SceneManager;
    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    Cursors3D_ = Cursors3D;
    SystemUtils_->Logger_->Log("Initializing ERS GUI Window_SceneTree", 4);

    Subwindow_SceneRenameModal_ = std::make_unique<Subwindow_SceneRenameModal>(SceneManager_);
    Subwindow_ModelRenameModal_ = std::make_unique<Subwindow_ModelRenameModal>(SceneManager_);
    Subwindow_PointLightRenameModal_ = std::make_unique<Subwindow_PointLightRenameModal>(SceneManager_);
    Subwindow_DirectionalLightRenameModal_ = std::make_unique<Subwindow_DirectionalLightRenameModal>(SceneManager_);
    Subwindow_SpotLightRenameModal_ = std::make_unique<Subwindow_SpotLightRenameModal>(SceneManager_);

    Subwindow_ModelReplaceModal_ = std::make_unique<Subwindow_ModelReplaceModal>(SceneManager_);
    
    Subwindow_DeleteScene_ = std::make_unique<Subwindow_DeleteScene>(SceneManager_, Cursors3D_);
    Subwindow_DeleteModel_ = std::make_unique<Subwindow_DeleteModel>(SceneManager_, Cursors3D_);
    Subwindow_DeletePointLight_ = std::make_unique<Subwindow_DeletePointLight>(SceneManager_, Cursors3D_);
    Subwindow_DeleteDirectionalLight_ = std::make_unique<Subwindow_DeleteDirectionalLight>(SceneManager_, Cursors3D_);
    Subwindow_DeleteSpotLight_ = std::make_unique<Subwindow_DeleteSpotLight>(SceneManager_, Cursors3D_);

    SystemUtils_->Logger_->Log("Finished Initializing ERS GUI Window_SceneTree", 5);

}

Window_SceneTree::~Window_SceneTree() {


}

void Window_SceneTree::Draw() {


    if (Enabled_) {
    bool Visible = ImGui::Begin("Scene Tree", &Enabled_);

        // Set Initial Window Size
        ImGui::SetWindowSize(ImVec2(400,250), ImGuiCond_FirstUseEver);


        if (Visible) {

            // Initialize Vars
            int ActiveScene = SceneManager_->ActiveScene_;
            
            // Convert Vector to Array
            if (ImGui::BeginCombo("Active Scene", SceneManager_->Scenes_[ActiveScene]->SceneName.c_str())) {

                for (int i = 0; (long)i < (long)SceneManager_->Scenes_.size(); i++) {

                    // Setup Selector
                    bool Selector = false;
                    if (i == SceneManager_->ActiveScene_) {
                        Selector = true;
                    }

                    // Create Selectable Item
                    ImGui::Selectable(SceneManager_->Scenes_[i]->SceneName.c_str(), &Selector);

                    // If Item Selected, Update Scene To Current Index
                    if (Selector) {
                        SceneManager_->ActiveScene_ = i;
                        SceneManager_->Scenes_[i]->HasSelectionChanged = true;
                    }
                }

            ImGui::EndCombo();
            }

            // Active Scene Dropdown
            ImGui::Separator();




            // Draw Selector In Child Frame
            if (ImGui::BeginChild("Tree Selector")) {


                // Create Scene Trees
                for (int SceneIndex = 0; (long)SceneIndex < (long)SceneManager_->Scenes_.size(); SceneIndex++) {

                    // Setup Tree Flags
                    ImGuiTreeNodeFlags NodeFlags = ImGuiTreeNodeFlags_OpenOnArrow;
                    if (SceneIndex == ActiveScene) {
                        NodeFlags |= ImGuiTreeNodeFlags_Selected;
                        NodeFlags |= ImGuiTreeNodeFlags_DefaultOpen;
                    }

                    // Get Tree Metadata
                    const char* SceneName = SceneManager_->Scenes_[SceneIndex]->SceneName.c_str();
                    //const char* PopupName = std::string(std::string("SceneTreePopupMenu_") + std::to_string(SceneIndex)).c_str();


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

                        DrawScene(SceneManager_->Scenes_[SceneIndex].get(), SceneIndex);

                        ImGui::TreePop();
                    }
                }
            }



        ImGui::EndChild();
        }
        


        // Drag/Drop Target
        long PayloadID;
        if (ImGui::BeginDragDropTarget()) {

            if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("PAYLOAD_ASSET_MODEL_ID")) {
                memcpy(&PayloadID, Payload->Data, sizeof(long));
                SystemUtils_->Logger_->Log(std::string(std::string("Window_SceneTree Recieved Drag Drop Payload 'PAYLOAD_ASSET_MODEL_ID' With Value '") + std::to_string(PayloadID) + std::string("'")).c_str(), 0);
                ERS_STRUCT_Scene* Scene = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get();
                ProjectUtils_->SceneLoader_->AddModel(Scene, PayloadID);
            }

        ImGui::EndDragDropTarget();
        }





    // End System Controls Window
    ImGui::End();
    }


    // Draw Popup Modals
    Subwindow_SceneRenameModal_->Draw();
    Subwindow_ModelRenameModal_->Draw();
    Subwindow_PointLightRenameModal_->Draw();
    Subwindow_DirectionalLightRenameModal_->Draw();
    Subwindow_SpotLightRenameModal_->Draw();
    Subwindow_DeleteScene_->Draw();
    Subwindow_DeleteModel_->Draw();
    Subwindow_DeletePointLight_->Draw();
    Subwindow_DeleteDirectionalLight_->Draw();
    Subwindow_DeleteSpotLight_->Draw();
    Subwindow_ModelReplaceModal_->Draw();

}


void Window_SceneTree::DrawScene(ERS_STRUCT_Scene* Scene, int SceneIndex) {

    // Get Selected Item
    int SelectedSceneObjectIndex = Scene->SelectedObject;


    // Draw Model Entries
    if (ImGui::TreeNodeEx("Models", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_OpenOnArrow)) {

        for (unsigned int i = 0; i < Scene->Models.size(); i++) {


        // Get Name Of Object
        const char* ObjectName = Scene->SceneObjects_[i].Label_.c_str();

        // Setup Node Flags
        ImGuiTreeNodeFlags TreeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        if ((unsigned long)SelectedSceneObjectIndex == i) {
            TreeFlags |= ImGuiTreeNodeFlags_Selected;
        }

        // Create Tree Node
        ImGui::TreeNodeEx((void*)(intptr_t)i, TreeFlags, "%s", ObjectName);


        // If User Clicks Node, Update Object Index
        if (ImGui::IsItemClicked()) {
            Scene->SelectedObject = i;
            Scene->HasSelectionChanged = true;
        }



        }

    ImGui::TreePop();
    }
    


    // Iterate Through Scene Objects
    for (unsigned long i = 0; i < Scene->SceneObjects_.size(); i++) {

        // Get Name Of Object
        const char* ObjectName = Scene->SceneObjects_[i].Label_.c_str();

        // Setup Node Flags
        ImGuiTreeNodeFlags TreeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        if ((unsigned long)SelectedSceneObjectIndex == i) {
            TreeFlags |= ImGuiTreeNodeFlags_Selected;
        }

        // Create Tree Node
        ImGui::TreeNodeEx((void*)(intptr_t)i, TreeFlags, "%s", ObjectName);


        // If User Clicks Node, Update Object Index
        if (ImGui::IsItemClicked()) {
            Scene->SelectedObject = i;
            Scene->HasSelectionChanged = true;
        }




        // Handle Drag/Drops
        if (Scene->SceneObjects_[i].Type_ == std::string("Model")) {

            long Index = Scene->SceneObjects_[i].Index_;

            // Drag/Drop Target
            long PayloadID;
            if (ImGui::BeginDragDropTarget()) {

                if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("PAYLOAD_ASSET_SCRIPT_ID")) {
                    memcpy(&PayloadID, Payload->Data, sizeof(long));
                    SystemUtils_->Logger_->Log(std::string("Window_SceneTree Recieved Drag Drop Payload 'PAYLOAD_ASSET_SCRIPT_ID' With Value '") + std::to_string(PayloadID) + std::string("'"), 0);
                    
                    // Check If Already In Vector
                    bool Contains = false; 
                    for (unsigned long x = 0; x < Scene->Models[Index]->AttachedScriptIndexes_.size(); x++) {
                        if (PayloadID ==  Scene->Models[Index]->AttachedScriptIndexes_[x]) {
                            SystemUtils_->Logger_->Log(std::string("Window_SceneTree Error Assigning Payload 'PAYLOAD_ASSET_SCRIPT_ID' To 'Model', Already Attached").c_str(), 0);
                            Contains = true;
                            break;
                        }
                    }

                    if (!Contains) {
                        Scene->Models[Index]->AttachedScriptIndexes_.push_back(PayloadID);
                    }
                }

            ImGui::EndDragDropTarget();
            }



        } else if (Scene->SceneObjects_[i].Type_ == std::string("PointLight")) {

            long Index = Scene->SceneObjects_[i].Index_;

            // Drag/Drop Target
            long PayloadID;
            if (ImGui::BeginDragDropTarget()) {

                if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("PAYLOAD_ASSET_SCRIPT_ID")) {
                    memcpy(&PayloadID, Payload->Data, sizeof(long));
                    SystemUtils_->Logger_->Log(std::string("Window_SceneTree Recieved Drag Drop Payload 'PAYLOAD_ASSET_SCRIPT_ID' With Value '") + std::to_string(PayloadID) + std::string("'"), 0);
                    
                    // Check If Already In Vector
                    bool Contains = false; 
                    for (unsigned long x = 0; x < Scene->PointLights[Index]->AttachedScriptIndexes_.size(); x++) {
                        if (PayloadID ==  Scene->PointLights[Index]->AttachedScriptIndexes_[x]) {
                            SystemUtils_->Logger_->Log(std::string("Window_SceneTree Error Assigning Payload 'PAYLOAD_ASSET_SCRIPT_ID' To 'PointLight', Already Attached").c_str(), 0);
                            Contains = true;
                            break;
                        }
                    }

                    if (!Contains) {
                        Scene->PointLights[Index]->AttachedScriptIndexes_.push_back(PayloadID);
                    }
                }

            ImGui::EndDragDropTarget();
            }



        } else if (Scene->SceneObjects_[i].Type_ == std::string("DirectionalLight")) {

            long Index = Scene->SceneObjects_[i].Index_;

            // Drag/Drop Target
            long PayloadID;
            if (ImGui::BeginDragDropTarget()) {

                if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("PAYLOAD_ASSET_SCRIPT_ID")) {
                    memcpy(&PayloadID, Payload->Data, sizeof(long));
                    SystemUtils_->Logger_->Log(std::string("Window_SceneTree Recieved Drag Drop Payload 'PAYLOAD_ASSET_SCRIPT_ID' With Value '") + std::to_string(PayloadID) + std::string("'"), 0);
                    
                    // Check If Already In Vector
                    bool Contains = false; 
                    for (unsigned long x = 0; x < Scene->DirectionalLights[Index]->AttachedScriptIndexes_.size(); x++) {
                        if (PayloadID ==  Scene->DirectionalLights[Index]->AttachedScriptIndexes_[x]) {
                            SystemUtils_->Logger_->Log(std::string("Window_SceneTree Error Assigning Payload 'PAYLOAD_ASSET_SCRIPT_ID' To 'DirectionalLight', Already Attached").c_str(), 0);
                            Contains = true;
                            break;
                        }
                    }

                    if (!Contains) {
                        Scene->DirectionalLights[Index]->AttachedScriptIndexes_.push_back(PayloadID);
                    }
                }

            ImGui::EndDragDropTarget();
            }



        } else if (Scene->SceneObjects_[i].Type_ == std::string("SpotLight")) {

            long Index = Scene->SceneObjects_[i].Index_;

            // Drag/Drop Target
            long PayloadID;
            if (ImGui::BeginDragDropTarget()) {

                if (const ImGuiPayload* Payload = ImGui::AcceptDragDropPayload("PAYLOAD_ASSET_SCRIPT_ID")) {
                    memcpy(&PayloadID, Payload->Data, sizeof(long));
                    SystemUtils_->Logger_->Log(std::string("Window_SceneTree Recieved Drag Drop Payload 'PAYLOAD_ASSET_SCRIPT_ID' With Value '") + std::to_string(PayloadID) + std::string("'"), 0);
                    
                    // Check If Already In Vector
                    bool Contains = false; 
                    for (unsigned long x = 0; x < Scene->SpotLights[Index]->AttachedScriptIndexes_.size(); x++) {
                        if (PayloadID ==  Scene->SpotLights[Index]->AttachedScriptIndexes_[x]) {
                            SystemUtils_->Logger_->Log(std::string("Window_SceneTree Error Assigning Payload 'PAYLOAD_ASSET_SCRIPT_ID' To 'SpotLight', Already Attached").c_str(), 0);
                            Contains = true;
                            break;
                        }
                    }

                    if (!Contains) {
                        Scene->SpotLights[Index]->AttachedScriptIndexes_.push_back(PayloadID);
                    }
                }

            ImGui::EndDragDropTarget();
            }



        }





        // Context Menu
        if (ImGui::BeginPopupContextItem()) {

            if (Scene->SceneObjects_[i].Type_ == std::string("Model")) {
                if (ImGui::MenuItem("Rename")) {
                    Subwindow_ModelRenameModal_->Activate(SceneIndex, Scene->SceneObjects_[i].Index_);
                } if (ImGui::MenuItem("Duplicate")) {
                    GUI_Windowutil_DuplicateModel(SceneManager_, SceneIndex, Scene->SceneObjects_[i].Index_);
                } if (ImGui::MenuItem("Replace All Instances")) {
                    Subwindow_ModelReplaceModal_->Activate(SceneIndex, Scene->SceneObjects_[i].Index_);
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Delete")) {
                    Subwindow_DeleteModel_->DeleteModel(SceneIndex, Scene->SceneObjects_[i].Index_);
                }

            } else if (Scene->SceneObjects_[i].Type_ == std::string("PointLight")) {
                if (ImGui::MenuItem("Rename")) {
                    Subwindow_PointLightRenameModal_->Activate(SceneIndex, Scene->SceneObjects_[i].Index_);
                }
                if (ImGui::MenuItem("Duplicate")) {
                    GUI_Windowutil_DuplicatePointLight(SceneManager_, SceneIndex, Scene->SceneObjects_[i].Index_);
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Delete")) {
                    Subwindow_DeletePointLight_->DeletePointLight(SceneIndex, Scene->SceneObjects_[i].Index_);
                }

            } else if (Scene->SceneObjects_[i].Type_ == std::string("DirectionalLight")) {
                if (ImGui::MenuItem("Rename")) {
                    Subwindow_DirectionalLightRenameModal_->Activate(SceneIndex, Scene->SceneObjects_[i].Index_);
                }
                if (ImGui::MenuItem("Duplicate")) {
                    GUI_Windowutil_DuplicateDirectionalLight(SceneManager_, SceneIndex, Scene->SceneObjects_[i].Index_);
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Delete")) {
                    Subwindow_DeleteDirectionalLight_->DeleteDirectionalLight(SceneIndex, Scene->SceneObjects_[i].Index_);
                }

            } else if (Scene->SceneObjects_[i].Type_ == std::string("SpotLight")) {
                if (ImGui::MenuItem("Rename")) {
                    Subwindow_SpotLightRenameModal_->Activate(SceneIndex, Scene->SceneObjects_[i].Index_);
                }
                if (ImGui::MenuItem("Duplicate")) {
                    GUI_Windowutil_DuplicateSpotLight(SceneManager_, SceneIndex, Scene->SceneObjects_[i].Index_);
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Delete")) {
                    Subwindow_DeleteSpotLight_->DeleteSpotLight(SceneIndex, Scene->SceneObjects_[i].Index_);
                }
            }


        ImGui::EndPopup();
        }


    }


}

