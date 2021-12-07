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
void Cursors3D::BeginRenderpass(ERS_OBJECT_CAMERA_NOCLIP *Camera, float* CameraView, float* CameraProjection) {

    // Copy In Values
    Camera_ = Camera;
    CameraDistance_ = glm::distance(glm::vec3(0.0f, 0.0f, 0.0f), Camera_->Position);;
    CameraProjection_ = CameraProjection;
    CameraView_ = CameraView;

    // Set Gizmo Mode
    if (ImGui::IsWindowHovered()) {
        if (ImGui::IsKeyPressed(71)) {
            mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
        } else if (ImGui::IsKeyPressed(82)) {
            mCurrentGizmoOperation = ImGuizmo::ROTATE;
        } else if (ImGui::IsKeyPressed(83)) {
            mCurrentGizmoOperation = ImGuizmo::SCALE;
        }
    }

    float matrixTranslation[3], matrixRotation[3], matrixScale[3];
    ImGuizmo::DecomposeMatrixToComponents(Matrix_[16], matrixTranslation, matrixRotation, matrixScale);
    ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, Matrix_[16]);
    std::cout<<matrixTranslation[0]<<std::endl;


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

   
    ImGuizmo::Manipulate(CameraView_, CameraProjection_, mCurrentGizmoOperation, ImGuizmo::WORLD, Matrix_[16], NULL, NULL);
    ImGuizmo::ViewManipulate(CameraView_, CameraDistance_, ImVec2(WindowWidth + ImGui::GetWindowPos().x - 256, ImGui::GetWindowPos().y), ImVec2(256, 256), 0x00000000);


}


// Dsable Camera Movement Function
bool Cursors3D::DisableCameraMovement() {
    return IsCursorActive_;
}