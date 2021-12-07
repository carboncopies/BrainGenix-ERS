//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for creating and managing 3d cursors.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-01
*/

#include <3DCursor.h>


// 3D Cursor Constructor
Cursors3D::Cursors3D() {

}

// 3D Cursor Destructor
Cursors3D::~Cursors3D() {

}

// Cursor Update Frame Function
void Cursors3D::BeginRenderpass(ERS_OBJECT_CAMERA_NOCLIP *Camera, float* CameraView, float* CameraProjection, bool IsCameraMoving) {

    // Copy In Values
    Camera_ = Camera;
    CameraDistance_ = glm::distance(glm::vec3(0.0f, 0.0f, 0.0f), Camera_->Position);;
    CameraProjection_ = CameraProjection;
    CameraView_ = CameraView;

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

    // Get Object Translation
    float ObjectTranslation_[3], ObjectRotation_[3], ObjectScale_[3];
    ImGuizmo::DecomposeMatrixToComponents(Matrix_[16], ObjectTranslation_, ObjectRotation_, ObjectScale_);

    // Update Current LocRotScale
    CurrentPos_.PosX = ObjectTranslation_[0];
    CurrentPos_.PosY = ObjectTranslation_[1];
    CurrentPos_.PosZ = ObjectTranslation_[2];

    CurrentPos_.RotX = ObjectRotation_[0];
    CurrentPos_.RotY = ObjectRotation_[1];
    CurrentPos_.RotZ = ObjectRotation_[2];

    CurrentPos_.ScaleX = ObjectScale_[0];
    CurrentPos_.ScaleY = ObjectScale_[1];
    CurrentPos_.ScaleZ = ObjectScale_[2];
    

    ImGuizmo::RecomposeMatrixFromComponents(ObjectTranslation_, ObjectRotation_, ObjectScale_, Matrix_[16]);

    // Check If Update Needed
    bool PosEqual = ((LastPos_.PosX == CurrentPos_.PosX) && (LastPos_.PosY == CurrentPos_.PosY) && (LastPos_.PosZ == CurrentPos_.PosZ));
    bool RotEqual = ((LastPos_.RotX == CurrentPos_.RotX) && (LastPos_.RotY == CurrentPos_.RotY) && (LastPos_.RotZ == CurrentPos_.RotZ));
    bool ScaleEqual = ((LastPos_.ScaleX == CurrentPos_.ScaleX) && (LastPos_.ScaleY == CurrentPos_.ScaleY) && (LastPos_.ScaleZ == CurrentPos_.ScaleZ));
    std::cout<<PosEqual<<RotEqual<<ScaleEqual<<std::endl;
    if (PosEqual && RotEqual && ScaleEqual) {
        HasObjectChanged_ = false;
    } else {
        HasObjectChanged_ = true;
    }
    LastPos_ = CurrentPos_;

    // Start ImGizmo Drawlist
    ImGuizmo::SetDrawlist(ImGui::GetWindowDrawList());

    // Set If Cursor Should Be Disabled
    IsCursorActive_ = ImGuizmo::IsUsing();


}


// Check If LocRotScale Has Changed
bool Cursors3D::HasLocRotScaleChanged() {
    return HasObjectChanged_;
}

// Get LocRotScale
ERS_STRUCT_LocRotScale Cursors3D::GetLocRotScale() {
    return CurrentPos_;
}

// End Render Pass
void Cursors3D::EndRenderpass() {


    float WindowWidth = (float)ImGui::GetWindowWidth();
    float WindowHeight = (float)ImGui::GetWindowHeight();
    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, WindowWidth, WindowHeight);

   
    ImGuizmo::Manipulate(CameraView_, CameraProjection_, CurrentGizmoOperation_, ImGuizmo::WORLD, Matrix_[16], NULL, NULL);
    ImGuizmo::ViewManipulate(CameraView_, CameraDistance_, ImVec2(WindowWidth + ImGui::GetWindowPos().x - 256, ImGui::GetWindowPos().y), ImVec2(256, 256), 0x00000000);


}


// Dsable Camera Movement Function
bool Cursors3D::DisableCameraMovement() {
    return IsCursorActive_;
}