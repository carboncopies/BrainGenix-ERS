//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Widget_ObjectProperties.h>


Widget_ObjectProperties::Widget_ObjectProperties(Cursors3D* Cursors3D, ERS_CLASS_SceneManager* SceneManager, ERS_STRUCT_ProjectUtils* ProjectUtils) {

    Cursors3D_ = Cursors3D;
    SceneManager_ = SceneManager;
    ProjectUtils_ = ProjectUtils;

}

Widget_ObjectProperties::~Widget_ObjectProperties() {
    
}

void Widget_ObjectProperties::Draw() {

    if (Enabled_) {
        bool Visible = ImGui::Begin("Object Properties", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(400,250), ImGuiCond_FirstUseEver);

            if (Visible) {


                // LocRotScale Properties
                if (ImGui::CollapsingHeader("Physical Parameters", ImGuiTreeNodeFlags_DefaultOpen)) {
                    ImGui::DragFloat3("Location", (float*)glm::value_ptr(Cursors3D_->Pos_), 0.05f);
                    ImGui::DragFloat3("Rotation", (float*)glm::value_ptr(Cursors3D_->Rot_), 0.05f);// FIXME: MAKE ROLL OVER TO 180 Degrees?
                    ImGui::DragFloat3("Scale", (float*)glm::value_ptr(Cursors3D_->Scale_), 0.05f, 0.0f, 65535.0f);
                }
            
                // Handle Extra Options For Lights
                unsigned long SelectedSceneObject = SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SelectedObject;
                if (SelectedSceneObject >= SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_.size()) {
                    SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SelectedObject = 0;
                    SelectedSceneObject = 0;
                }
                
                if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("PointLight")) {
                    
                    unsigned long Index = SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Index_;
                    if (ImGui::CollapsingHeader("Point Light Settings", ImGuiTreeNodeFlags_DefaultOpen)) {

                        float Color[3];
                        VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Color, Color);
                        ImGui::ColorEdit3("Color", Color);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Controls the main color of the light.");
                        FloatToVec(Color, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Color);
  

                        ImGui::DragFloat("Intensity", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Intensity, 0.01f);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Sets the brightness of the light source, increase this for a brighter light.");


                    }

                } else if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("DirectionalLight")) {
                    
                    unsigned long Index = SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Index_;
                    if (ImGui::CollapsingHeader("Directional Light Settings", ImGuiTreeNodeFlags_DefaultOpen)) {

                        float Color[3];
                        VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Color, Color);
                        ImGui::ColorEdit3("Color", Color);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Controls the main color of the light.");
                        FloatToVec(Color, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Color);


                    }

                } else if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("SpotLight")) {
                    
                    unsigned long Index = SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Index_;
                    if (ImGui::CollapsingHeader("Spot Light Settings", ImGuiTreeNodeFlags_DefaultOpen)) {

                        float Color[3];
                        VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Color, Color);
                        ImGui::ColorEdit3("Color", Color);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Controls the main color of the light.");
                        FloatToVec(Color, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Color);


                        ImGui::DragFloat("Intensity", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Intensity, 0.01f);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Sets the brightness of the light source, increase this for a brighter light.");


                        ImGui::DragFloat("Cutoff", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->CutOff, 0.01f);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Set the inner circle cutoff point. Will start to attenuate outside of this circle.");
                        ImGui::DragFloat("Outer Cutoff", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->OuterCutOff, 0.01f);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Sets the outer circle at which attenuation ends. Everything outside this circle is unaffected by the light.");

                    }

                }


                // Show Script Data
                if (ImGui::CollapsingHeader("Scripts", ImGuiTreeNodeFlags_DefaultOpen)) {

                    // Populate Script List Char Array
                    long Index = SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Index_;
                    if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("Model")) {
                        ScriptIndices_ = &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->Models[Index]->AttachedScriptIndexes_;                  
                    } else if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("PointLight")) {
                        ScriptIndices_ = &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->AttachedScriptIndexes_;     
                    } else if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("DirectionalLight")) {
                        ScriptIndices_ = &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->AttachedScriptIndexes_;     
                    } else if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("SpotLight")) {
                        ScriptIndices_ = &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->AttachedScriptIndexes_;     
                    }

                    // Draw List Box
                    if (ImGui::BeginChild("Script Controls", ImVec2(0, 200), true)) {


                        for (unsigned long i = 0; i < ScriptIndices_->size(); i++) {

                            std::string ScriptName = ProjectUtils_->ProjectManager_->Project_.Scripts[(*ScriptIndices_)[i]].Name_;
                            bool Selected = i==(unsigned long)ScriptIndex_;
                            if (ImGui::Selectable(ScriptName.c_str(), &Selected)) {
                                ScriptIndex_ = i;
                            }


                            // Context Menu
                            if (ImGui::BeginPopupContextItem()) {

                                if (ImGui::MenuItem("Remove Script")) {
                                    ScriptIndices_->erase(ScriptIndices_->begin() + i);
                                }


                            ImGui::EndPopup();
                            }


                        }


                    }
                    ImGui::EndChild();





                }





            }

        // End System Controls Window
        ImGui::End();

    }



}


void Widget_ObjectProperties::VecToFloat(glm::vec3* In, float* Out) {

    Out[0] = In->x;
    Out[1] = In->y;
    Out[2] = In->z;

}

void Widget_ObjectProperties::FloatToVec(float* In, glm::vec3* Out) {

    Out->x = In[0];
    Out->y = In[1];
    Out->z = In[2];

}