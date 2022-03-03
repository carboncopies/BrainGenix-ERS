//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_Editor_3DCursor.h>


Cursors3D::Cursors3D() {

}

Cursors3D::~Cursors3D() {


}


void Cursors3D::SetLocRotScale(glm::vec3 Pos, glm::vec3 Rot, glm::vec3 Scale) {
    Pos_ = Pos;
    Rot_ = Rot;
    Scale_ = Scale;
}



void Cursors3D::Draw(ERS_STRUCT_Camera* Camera, bool IsCameraMoving, bool ShowCube, bool ShowCursor) {

    Camera_ = Camera;
    glm::mat4 Projection = Camera_->GetProjectionMatrix();
    glm::mat4 View = Camera_->GetViewMatrix();

    // Set Gizmo Mode
    if (ImGui::IsWindowHovered() && !IsCameraMoving) {
        if (ImGui::IsKeyPressed(71)) {
            CurrentGizmoOperation_ = ImGuizmo::TRANSLATE;
        } else if (ImGui::IsKeyPressed(82)) {
            CurrentGizmoOperation_ = ImGuizmo::ROTATE;
        } else if (ImGui::IsKeyPressed(83)) {
            CurrentGizmoOperation_ = ImGuizmo::SCALE;
        }
    }

    float WindowWidth = (float)ImGui::GetWindowWidth();
    float WindowHeight = (float)ImGui::GetWindowHeight();
    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, WindowWidth, WindowHeight);
    ImGuizmo::SetDrawlist(ImGui::GetWindowDrawList());

    if (ShowCube) {
        ImGuizmo::ViewManipulate((float*)glm::value_ptr(View), 5.0f, ImVec2(WindowWidth + ImGui::GetWindowPos().x - 128, ImGui::GetWindowPos().y), ImVec2(128, 128), 0x00000000);
    }


    float TmpMatrix[16];
    ImGuizmo::RecomposeMatrixFromComponents((float*)glm::value_ptr(Pos_), (float*)glm::value_ptr(Rot_), (float*)glm::value_ptr(Scale_), TmpMatrix);

    if (ShowCursor) {
        ImGuizmo::Manipulate((float*)glm::value_ptr(View), (float*)glm::value_ptr(Projection), CurrentGizmoOperation_, ImGuizmo::MODE::WORLD, TmpMatrix);
    }

    // Quaternions? 
    // Identity matrix?
    // https://www.mathworks.com/help/fusion/ref/quaternion.transpose.html

    // If Using Gizmo
    if (ImGuizmo::IsUsing()) {
        
        float TmpTranslation[3];
        float TmpRotation[3];
        float TmpScale[3];
        ImGuizmo::DecomposeMatrixToComponents(TmpMatrix, TmpTranslation, TmpRotation, TmpScale);

        if (CurrentGizmoOperation_ == ImGuizmo::OPERATION::TRANSLATE) {
            Pos_ = glm::vec3(TmpTranslation[0], TmpTranslation[1], TmpTranslation[2]);
        } else if (CurrentGizmoOperation_ == ImGuizmo::OPERATION::ROTATE) {
            Rot_ = glm::vec3(TmpRotation[0], TmpRotation[1], TmpRotation[2]);
        } else if (CurrentGizmoOperation_ == ImGuizmo::OPERATION::SCALE) {
            Scale_ = glm::vec3(TmpScale[0], TmpScale[1], TmpScale[2]);
        }

    }


    //ImGuizmo::DecomposeMatrixToComponents(Matrix_[16], ObjectTranslation_, ObjectRotation_, ObjectScale_);
    //ImGui::InputFloat3("Translate", ObjectTranslation_);
    //ImGui::InputFloat3("Rotate", ObjectRotation_);
    //ImGui::InputFloat3("Scale", ObjectScale_);
    //ImGuizmo::RecomposeMatrixFromComponents(ObjectTranslation_, ObjectRotation_, ObjectScale_, Matrix_[16]);










}


bool Cursors3D::IsUsing() {
    return ImGuizmo::IsUsing();
}

bool Cursors3D::IsHovered() {
    return ImGuizmo::IsOver();
}