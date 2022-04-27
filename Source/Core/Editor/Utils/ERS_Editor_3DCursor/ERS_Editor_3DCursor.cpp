//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_Editor_3DCursor.h>


Cursors3D::Cursors3D() {

}

Cursors3D::~Cursors3D() {


}


void Cursors3D::SetLocRotScale(glm::vec3 Pos, glm::vec3 Rot, glm::vec3 Scale, bool HasRotation, bool HasScale) {
    Pos_ = Pos;
    if (HasRotation) {
        Rot_ = Rot;
    }
    if (HasScale) {
        Scale_ = Scale;
    }

    EnableRotation_ = HasRotation;
    EnableScale_ = HasScale;

    if (CurrentGizmoOperation_ == ImGuizmo::ROTATE && !EnableRotation_) {
        CurrentGizmoOperation_ = ImGuizmo::TRANSLATE;
    }
    if (CurrentGizmoOperation_ == ImGuizmo::SCALE && !EnableScale_) {
        CurrentGizmoOperation_ = ImGuizmo::TRANSLATE;
    }
    

}



void Cursors3D::Draw(ERS_STRUCT_Camera* Camera, bool IsCameraMoving, bool ShowCube, bool ShowCursor) {

    Camera_ = Camera;
    glm::mat4 Projection = Camera_->GetProjectionMatrix();
    glm::mat4 View = Camera_->GetViewMatrix();
    LastFrameActiveState_ = ImGuizmo::IsUsing();



    // Set Gizmo Mode
    if (ImGui::IsWindowHovered() && !IsCameraMoving) {
        if (ImGui::IsKeyPressed(71)) {
            CurrentGizmoOperation_ = ImGuizmo::TRANSLATE;
        } else if (ImGui::IsKeyPressed(82) && EnableRotation_) {
            CurrentGizmoOperation_ = ImGuizmo::ROTATE;
        } else if (ImGui::IsKeyPressed(83) && EnableScale_) {
            CurrentGizmoOperation_ = ImGuizmo::SCALE;
        }
    
        // World / Local Space
        if (ImGui::IsKeyPressed(81)) { // User Pressed 'Q' Key
            GizmoMode_ = ImGuizmo::MODE::WORLD;
        } else if (ImGui::IsKeyPressed(69)) { // User Pressed 'E' Key
            GizmoMode_ = ImGuizmo::MODE::LOCAL;
        }
    
    }

    float WindowWidth = (float)ImGui::GetWindowWidth();
    float WindowHeight = (float)ImGui::GetWindowHeight();
    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, WindowWidth, WindowHeight);
    ImGuizmo::SetDrawlist(ImGui::GetWindowDrawList());

    if (ShowCube) {
        ImGuizmo::ViewManipulate((float*)glm::value_ptr(View), 5.0f, ImVec2(WindowWidth + ImGui::GetWindowPos().x - 128, ImGui::GetWindowPos().y), ImVec2(128, 128), 0x00000000);
    }


    /*
    NOTE:
    The variables Pos_, Rot_, and Scale_ are the object's loc rot and scale.
    We use GLM internally, however they're converted to float* for ImGuizmo and back at the end.
    */


    // Set Gizmo LocRotScale To Object LocRotScale
    float TmpMatrix[16];
    glm::vec3 GizmoInputRot = glm::vec3(0);
    ImGuizmo::RecomposeMatrixFromComponents((float*)glm::value_ptr(Pos_), (float*)glm::value_ptr(GizmoInputRot), (float*)glm::value_ptr(Scale_), TmpMatrix);


    // Only Draw When ShowCursor Is True, Otherwise Don't Draw
    if (ShowCursor) {
        ImGuizmo::Manipulate((float*)glm::value_ptr(View), (float*)glm::value_ptr(Projection), CurrentGizmoOperation_, GizmoMode_, TmpMatrix);
    }


    // If Using Gizmo, Update Object LocRotScale
    if (ImGuizmo::IsUsing()) {
        
        float TmpTranslation[3];
        float TmpRotation[3];
        float TmpScale[3];
        ImGuizmo::DecomposeMatrixToComponents(TmpMatrix, TmpTranslation, TmpRotation, TmpScale);

        if (CurrentGizmoOperation_ == ImGuizmo::OPERATION::TRANSLATE) {
            Pos_ = glm::vec3(TmpTranslation[0], TmpTranslation[1], TmpTranslation[2]);
        } else if (CurrentGizmoOperation_ == ImGuizmo::OPERATION::ROTATE) {
            Rot_ += glm::vec3(TmpRotation[0], TmpRotation[1], TmpRotation[2]);
            Rot_ = glm::mod(Rot_, 360.0f);
        } else if (CurrentGizmoOperation_ == ImGuizmo::OPERATION::SCALE) {
            Scale_ = glm::vec3(TmpScale[0], TmpScale[1], TmpScale[2]);
        }

    }


}


bool Cursors3D::IsUsing() {
    return ImGuizmo::IsUsing();
}

bool Cursors3D::IsHovered() {
    return ImGuizmo::IsOver();
}

bool Cursors3D::HasStateChanged() {
    return LastFrameActiveState_ == ImGuizmo::IsUsing();
}