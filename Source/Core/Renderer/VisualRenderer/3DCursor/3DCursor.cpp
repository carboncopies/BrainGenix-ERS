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


// Set LocRotScale
void Cursors3D::SetLocRotScale(ERS_STRUCT_LocRotScale LocRotScale) {


    // Create Floats
    float ObjectTranslation_[3];
    float ObjectRotation_[3];
    float ObjectScale_[3];

    // Assign Value To Floats
    ObjectScale_[0] = LocRotScale.ScaleX;
    ObjectScale_[1] = LocRotScale.ScaleY;
    ObjectScale_[2] = LocRotScale.ScaleZ;
    ObjectRotation_[0] = LocRotScale.RotX;
    ObjectRotation_[1] = LocRotScale.RotY;
    ObjectRotation_[2] = LocRotScale.RotZ;
    ObjectTranslation_[0] = LocRotScale.PosX;
    ObjectTranslation_[1] = LocRotScale.PosY;
    ObjectTranslation_[2] = LocRotScale.PosZ;

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


    // Push To Gizmo
    //ImGuizmo::RecomposeMatrixFromComponents(ObjectTranslation_, ObjectRotation_, ObjectScale_, Matrix_[16]);

}



// Check if Structs Are Equal
bool Cursors3D::IsLocRotScaleEqual(ERS_STRUCT_LocRotScale LRS1, ERS_STRUCT_LocRotScale LRS2) {

    // Check If Equal
    bool PosEqual2 = ((LRS1.PosX == LRS2.PosX) && (LRS1.PosY == LRS2.PosY) && (LRS1.PosZ == LRS2.PosZ));
    bool RotEqual2 = ((LRS1.RotX == LRS2.RotX) && (LRS1.RotY == LRS2.RotY) && (LRS1.RotZ == LRS2.RotZ));
    bool ScaleEqual2 = ((LRS1.ScaleX == LRS2.ScaleX) && (LRS1.ScaleY == LRS2.ScaleY) && (LRS1.ScaleZ == LRS2.ScaleZ));
    if (PosEqual2 && RotEqual2 && ScaleEqual2) {
        return false;
    } else {
        return true;
    }


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
    float ObjectTranslation_[3];
    float ObjectRotation_[3];
    float ObjectScale_[3];

    ImGuizmo::DecomposeMatrixToComponents(Matrix_[16], ObjectTranslation_, ObjectRotation_, ObjectScale_);
        // Force Scale To 1,1,1
        // if (FirstFrame_) {
        //     ObjectScale_[0] = 1.0f;
        //     ObjectScale_[1] = 1.0f;
        //     ObjectScale_[2] = 1.0f;
        //     ObjectRotation_[0] = 0.0f;
        //     ObjectRotation_[1] = 0.0f;
        //     ObjectRotation_[2] = 0.0f;
        //     ObjectTranslation_[0] = 0.0f;
        //     ObjectTranslation_[1] = 0.0f;
        //     ObjectTranslation_[2] = 0.0f;
            
        //     FirstFrame_ = false;
        // }

        // Check If Someone Else Is Setting Pos
        bool PosEqual = ((ObjectTranslation_[0]== LastPos_.PosX) && (ObjectTranslation_[1] == LastPos_.PosY) && (ObjectTranslation_[2] == LastPos_.PosZ));
        bool RotEqual = ((ObjectRotation_[0] == LastPos_.RotX) && (ObjectRotation_[1] == LastPos_.RotY) && (ObjectRotation_[2] == LastPos_.RotZ));
        bool ScaleEqual = ((ObjectScale_[0] == LastPos_.ScaleX) && (ObjectScale_[1] == LastPos_.ScaleY) && (ObjectScale_[2] == LastPos_.ScaleZ));
        bool IsEqual = (PosEqual && RotEqual && ScaleEqual);
        if (!IsEqual) {

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

            HasObjectChanged_ = true;

            
        } else if (IsLocRotScaleEqual(CurrentPos_, LastPos_)) {

            // Assign Value To Floats
            ObjectScale_[0] = CurrentPos_.ScaleX;
            ObjectScale_[1] = CurrentPos_.ScaleY;
            ObjectScale_[2] = CurrentPos_.ScaleZ;
            ObjectRotation_[0] = CurrentPos_.RotX;
            ObjectRotation_[1] = CurrentPos_.RotY;
            ObjectRotation_[2] = CurrentPos_.RotZ;
            ObjectTranslation_[0] = CurrentPos_.PosX;
            ObjectTranslation_[1] = CurrentPos_.PosY;
            ObjectTranslation_[2] = CurrentPos_.PosZ;

            HasObjectChanged_ = true;


        }



    ImGuizmo::RecomposeMatrixFromComponents(ObjectTranslation_, ObjectRotation_, ObjectScale_, Matrix_[16]);

    // Update Last Pos
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

// Get LocRotScalePtr
ERS_STRUCT_LocRotScale* Cursors3D::GetLocRotScalePtr() {
    return &CurrentPos_;
}

// End Render Pass
void Cursors3D::EndRenderpass() {


    float WindowWidth = (float)ImGui::GetWindowWidth();
    float WindowHeight = (float)ImGui::GetWindowHeight();
    ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, WindowWidth, WindowHeight);

   
    ImGuizmo::Manipulate(CameraView_, CameraProjection_, CurrentGizmoOperation_, ImGuizmo::LOCAL, Matrix_[16], NULL, NULL);
    ImGuizmo::ViewManipulate(CameraView_, CameraDistance_, ImVec2(WindowWidth + ImGui::GetWindowPos().x - 256, ImGui::GetWindowPos().y), ImVec2(256, 256), 0x00000000);


}


// Dsable Camera Movement Function
bool Cursors3D::DisableCameraMovement() {
    return IsCursorActive_;
}