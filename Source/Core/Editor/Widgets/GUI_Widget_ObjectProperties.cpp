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
                    FloatToVec(DiffuseColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Diffuse);

                    float AmbientColor[3];
                    VecToFloat(&SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Diffuse, AmbientColor);
                    ImGui::ColorEdit3("Ambient", AmbientColor);
                    FloatToVec(AmbientColor, &SceneManager_->Scenes_[SceneManager_->ActiveScene_]->PointLights[Index]->Diffuse);


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