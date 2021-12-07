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
void Cursors3D::BeginRenderpass(ERS_OBJECT_CAMERA_NOCLIP *Camera, float AspectRatio) {


    // Set Camera
    Camera_ = Camera;


    glm::mat4 View = Camera_->GetViewMatrix();
    glm::mat4 Projection = glm::perspective(glm::radians(Camera_->Zoom), AspectRatio, 0.1f, 100.0f);


    std::cout<<glm::to_string(View)<<std::endl;


    float* CameraView = (float*)glm::value_ptr(View);
    float* CameraProjection = (float*)glm::value_ptr(Projection);
    float CameraDistance = glm::distance(glm::vec3(0.0f, 0.0f, 0.0f), Camera_->Position);


    // Copy In Values
    CameraDistance_ = CameraDistance;
    CameraProjection_ = CameraProjection;
    CameraView_ = CameraView;


    //ImGuizmo::SetOrthographic(true);
    //float at[] = {0.0f, 0.0f, 0.0f};
    //LookAt(CameraPosition, at, {0.0f, 1.0f, 0.0f}, CameraView_);

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

   

    //ImGuizmo::DrawCubes(CameraView_, CameraProjection_, &objectMatrix[0][0], 1);
    ImGuizmo::Manipulate(CameraView_, CameraProjection_, ImGuizmo::TRANSLATE, ImGuizmo::WORLD, &objectMatrix[0][0], NULL, NULL);
    ImGuizmo::ViewManipulate(CameraView_, CameraDistance_, ImVec2(WindowWidth + ImGui::GetWindowPos().x - 128, ImGui::GetWindowPos().y), ImVec2(128, 128), 0x10101010);


}


// Dsable Camera Movement Function
bool Cursors3D::DisableCameraMovement() {
    return !IsCursorActive_;
}