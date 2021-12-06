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
void Cursors3D::UpdateFrame() {



    // Set If Cursor Should Be Disabled
    IsCursorActive_ = ImGuizmo::IsUsing();


    // End Guizmo
    ImGuizmo::SetDrawlist();

}


// Dsable Camera Movement Function
bool Cursors3D::DisableCameraMovement() {
    return !IsCursorActive_;
}