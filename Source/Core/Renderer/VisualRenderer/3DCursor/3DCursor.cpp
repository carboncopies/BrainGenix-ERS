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
void Cursors3D::BeginRenderpass(float* CameraView, float* CameraProjection, float* Matrix, float CameraDistance) {

    // Copy In Values
    CameraDistance_ = CameraDistance;
    CameraProjection_ = CameraProjection;
    CameraView_ = CameraView;
    Matrix_ = Matrix;



    // Start ImGizmo Drawlist
    ImGuizmo::SetDrawlist(ImGui::GetWindowDrawList());

    // Set If Cursor Should Be Disabled
    IsCursorActive_ = ImGuizmo::IsUsing();


}

// Test func
void Cursors3D::EndRenderpass() {


    float WindowWidth = (float)ImGui::GetWindowWidth();
    float WindowHeight = (float)ImGui::GetWindowHeight();
    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, WindowWidth, WindowHeight);

   

    //ImGuizmo::DrawCubes(cameraView, cameraProjection, &objectMatrix[0][0], gizmoCount);
    ImGuizmo::Manipulate(CameraView_, CameraProjection_, mCurrentGizmoOperation, ImGuizmo::WORLD, Matrix_, NULL, NULL);
    ImGuizmo::ViewManipulate(CameraView_, CameraDistance_, ImVec2(WindowWidth + ImGui::GetWindowPos().x - 128, ImGui::GetWindowPos().y), ImVec2(128, 128), 0x10101010);


}


// Dsable Camera Movement Function
bool Cursors3D::DisableCameraMovement() {
    return !IsCursorActive_;
}