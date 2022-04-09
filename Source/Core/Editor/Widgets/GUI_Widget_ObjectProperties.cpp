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
                if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("PointLight")) {
                    
                    unsigned long Index = SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Index_;
                    if (ImGui::CollapsingHeader("Point Light Settings", ImGuiTreeNodeFlags_DefaultOpen)) {

                        float DiffuseColor[3];
                        VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Diffuse, DiffuseColor);
                        ImGui::ColorEdit3("Diffuse", DiffuseColor);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Controls the main color of the light.");
                        FloatToVec(DiffuseColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Diffuse);
                        float AmbientColor[3];
                        VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Ambient, AmbientColor);
                        ImGui::ColorEdit3("Ambient", AmbientColor);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Controls any additions to the ambient color of the environment. Generally, you shouldn't do this with a point light, use a directional light whenever possible instead.");
                        FloatToVec(AmbientColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Ambient);
                        float SpecularColor[3];
                        VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Specular, SpecularColor);
                        ImGui::ColorEdit3("Specular", SpecularColor);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Controls the color of the reflection.");
                        FloatToVec(SpecularColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Specular);
                        ImGui::Separator();

                        ImGui::DragFloat("Rolloff Constant", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->RolloffConstant, 0.01f);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Sets the constant offset controlling lamp attenuation over distance. If you're trying to make the rolloff sharper, try linear or quadratic.");
                        ImGui::DragFloat("Rolloff Linear", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->RolloffLinear, 0.01f);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Component of rolloff proportional to distance from light to object. E.g. twice the distance means half the brightness.");
                        ImGui::DragFloat("Rolloff Quadratic", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->RolloffQuadratic, 0.01f);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Exponential component of rolloff. Increasing this, makes the rolloff much sharper. For a linear rolloff, use the 'Rolloff Linear' value.");

                    }

                } else if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("DirectionalLight")) {
                    
                    unsigned long Index = SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Index_;
                    if (ImGui::CollapsingHeader("Directional Light Settings", ImGuiTreeNodeFlags_DefaultOpen)) {

                        float DiffuseColor[3];
                        VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Diffuse, DiffuseColor);
                        ImGui::ColorEdit3("Diffuse", DiffuseColor);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Controls the main color of the light.");
                        FloatToVec(DiffuseColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Diffuse);
                        float AmbientColor[3];
                        VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Ambient, AmbientColor);
                        ImGui::ColorEdit3("Ambient", AmbientColor);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Controls any additions to the ambient color of the environment.");
                        FloatToVec(AmbientColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Ambient);
                        float SpecularColor[3];
                        VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Specular, SpecularColor);
                        ImGui::ColorEdit3("Specular", SpecularColor);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Controls the color of the reflection. Generally, you shouldn't do this with a directional light, use a spot or point light instead.");
                        FloatToVec(SpecularColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Specular);
                        ImGui::Separator();

                    }

                } else if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("SpotLight")) {
                    
                    unsigned long Index = SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Index_;
                    if (ImGui::CollapsingHeader("Spot Light Settings", ImGuiTreeNodeFlags_DefaultOpen)) {

                        float DiffuseColor[3];
                        VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Diffuse, DiffuseColor);
                        ImGui::ColorEdit3("Diffuse", DiffuseColor);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Controls the main color of the light.");
                        FloatToVec(DiffuseColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Diffuse);
                        float AmbientColor[3];
                        VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Ambient, AmbientColor);
                        ImGui::ColorEdit3("Ambient", AmbientColor);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Controls any additions to the ambient color of the environment. Generally, you shouldn't do this with a spot light, use a directional light whenever possible instead.");
                        FloatToVec(AmbientColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Ambient);
                        float SpecularColor[3];
                        VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Specular, SpecularColor);
                        ImGui::ColorEdit3("Specular", SpecularColor);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Controls the color of the reflection.");
                        FloatToVec(SpecularColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Specular);
                        ImGui::Separator();

                        ImGui::DragFloat("Rolloff Constant", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->RolloffConstant, 0.01f);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Sets the constant offset controlling lamp attenuation over distance. If you're trying to make the rolloff sharper, try linear or quadratic.");
                        ImGui::DragFloat("Rolloff Linear", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->RolloffLinear, 0.01f);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Component of rolloff proportional to distance from light to object. E.g. twice the distance means half the brightness.");
                        ImGui::DragFloat("Rolloff Quadratic", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->RolloffQuadratic, 0.01f);
                        ImGui::SameLine();
                        ImGui::HelpMarker("Exponential component of rolloff. Increasing this, makes the rolloff much sharper. For a linear rolloff, use the 'Rolloff Linear' value.");
                        ImGui::Separator();

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
                        ScriptIndices_ &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->Models[Index]->AttachedScriptIndexes_;                  
                    } else if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("PointLight")) {
                        ScriptIndices_ &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->AttachedScriptIndexes_;     
                    } else if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("DirectionalLight")) {
                        ScriptIndices_ &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->AttachedScriptIndexes_;     
                    } else if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("SpotLight")) {
                        ScriptIndices_ &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->AttachedScriptIndexes_;     
                    }

                    // Draw List Box
                    if (ImGui::BeginChild("Script Controls", ImVec2(0, 200), true)) {


                        for (unsigned long i = 0; i < ScriptIndices_.size(); i++) {

                            std::string ScriptName = ProjectUtils_->ProjectManager_->Project_.Scripts[ScriptIndices_[i]].Name_;
                            bool Selected = i==(unsigned long)ScriptIndex_;
                            if (ImGui::Selectable(ScriptName.c_str(), &Selected)) {
                                ScriptIndex_ = i;
                            }


                            // Context Menu
                            if (ImGui::BeginPopupContextItem()) {

                                if (ImGui::MenuItem("Remove Script")) {

                                }


                            ImGui::EndPopup();
                            }


                        }


                    ImGui::EndChild();
                    }




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