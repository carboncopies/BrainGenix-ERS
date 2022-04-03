//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Widget_ObjectProperties.h>


Widget_ObjectProperties::Widget_ObjectProperties(Cursors3D* Cursors3D, ERS_CLASS_SceneManager* SceneManager) {

    Cursors3D_ = Cursors3D;
    SceneManager_ = SceneManager;

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
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Separator();
                ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Physical Parameters");
                ImGui::Separator();
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::DragFloat3("Location", (float*)glm::value_ptr(Cursors3D_->Pos_), 0.05f);
                ImGui::DragFloat3("Rotation", (float*)glm::value_ptr(Cursors3D_->Rot_), 0.05f);// FIXME: MAKE ROLL OVER TO 180 Degrees?
                ImGui::DragFloat3("Scale", (float*)glm::value_ptr(Cursors3D_->Scale_), 0.05f, 0.0f, 65535.0f);

            
                // Handle Extra Options For Lights
                unsigned long SelectedSceneObject = SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SelectedObject;
                if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("PointLight")) {
                    
                    unsigned long Index = SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Index_;
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Point Light Settings");
                    ImGui::Separator();
                    ImGui::Spacing();
                    ImGui::Spacing();

                    float DiffuseColor[3];
                    VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Diffuse, DiffuseColor);
                    ImGui::ColorEdit3("Diffuse", DiffuseColor);
                    ImGui::HelpMarker("Controls the main color of the light.");
                    FloatToVec(DiffuseColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Diffuse);
                    float AmbientColor[3];
                    VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Ambient, AmbientColor);
                    ImGui::ColorEdit3("Ambient", AmbientColor);
                    ImGui::HelpMarker("Controls any additions to the ambient color of the environment. Generally, you shouldn't do this with a point light, use a directional light whenever possible instead.");
                    FloatToVec(AmbientColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Ambient);
                    float SpecularColor[3];
                    VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Specular, SpecularColor);
                    ImGui::ColorEdit3("Specular", SpecularColor);
                    FloatToVec(SpecularColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Specular);
                    ImGui::Separator();

                    ImGui::DragFloat("Rolloff Constant", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->RolloffConstant, 0.01f);
                    ImGui::DragFloat("Rolloff Linear", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->RolloffLinear, 0.01f);
                    ImGui::DragFloat("Rolloff Quadratic", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->RolloffQuadratic, 0.01f);

                } else if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("DirectionalLight")) {
                    
                    unsigned long Index = SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Index_;
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Directional Light Settings");
                    ImGui::Separator();
                    ImGui::Spacing();
                    ImGui::Spacing();

                    float DiffuseColor[3];
                    VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Diffuse, DiffuseColor);
                    ImGui::ColorEdit3("Diffuse", DiffuseColor);
                    FloatToVec(DiffuseColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Diffuse);
                    float AmbientColor[3];
                    VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Ambient, AmbientColor);
                    ImGui::ColorEdit3("Ambient", AmbientColor);
                    FloatToVec(AmbientColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Ambient);
                    float SpecularColor[3];
                    VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Specular, SpecularColor);
                    ImGui::ColorEdit3("Specular", SpecularColor);
                    FloatToVec(SpecularColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->DirectionalLights[Index]->Specular);
                    ImGui::Separator();

                } else if (SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Type_ == std::string("SpotLight")) {
                    
                    unsigned long Index = SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SceneObjects_[SelectedSceneObject].Index_;
                    ImGui::Spacing();
                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Spot Light Settings");
                    ImGui::Separator();
                    ImGui::Spacing();
                    ImGui::Spacing();

                    float DiffuseColor[3];
                    VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Diffuse, DiffuseColor);
                    ImGui::ColorEdit3("Diffuse", DiffuseColor);
                    FloatToVec(DiffuseColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Diffuse);
                    float AmbientColor[3];
                    VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Ambient, AmbientColor);
                    ImGui::ColorEdit3("Ambient", AmbientColor);
                    FloatToVec(AmbientColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Ambient);
                    float SpecularColor[3];
                    VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Specular, SpecularColor);
                    ImGui::ColorEdit3("Specular", SpecularColor);
                    FloatToVec(SpecularColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->Specular);
                    ImGui::Separator();

                    ImGui::DragFloat("Rolloff Constant", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->RolloffConstant, 0.01f);
                    ImGui::DragFloat("Rolloff Linear", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->RolloffLinear, 0.01f);
                    ImGui::DragFloat("Rolloff Quadratic", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->RolloffQuadratic, 0.01f);
                    ImGui::Separator();

                    ImGui::DragFloat("Cutoff", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->CutOff, 0.01f);
                    ImGui::DragFloat("Outer Cutoff", &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->SpotLights[Index]->OuterCutOff, 0.01f);


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