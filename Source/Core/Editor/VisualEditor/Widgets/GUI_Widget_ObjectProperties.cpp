//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-02
*/

#include <GUI_Widget_ObjectProperties.h>

// Constructor
Widget_ObjectProperties::Widget_ObjectProperties(Cursors3D *Cursors3D) {

    // Update Ptr
    Cursors3D_ = Cursors3D;

}

// Destructor
Widget_ObjectProperties::~Widget_ObjectProperties() {
    
}

// Define Draw Function
void Widget_ObjectProperties::Draw() {

    // If Window Drawing Enabled
    if (Enabled_) {
        ImGui::Begin("Object Properties", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(400,250), ImGuiCond_FirstUseEver);

            // Get Struct Ptr, Setup Slides
            ERS_STRUCT_LocRotScale *LocRotScale = Cursors3D_->GetLocRotScalePtr();

            float Location_[3] = {LocRotScale->PosX, LocRotScale->PosY, LocRotScale->PosZ};
            float Rotation_[3] = {LocRotScale->RotX, LocRotScale->RotY, LocRotScale->RotZ};
            float Scale_[3] = {LocRotScale->ScaleX, LocRotScale->ScaleY, LocRotScale->ScaleZ};
            
            // LocRotScale Properties
            ImGui::DragFloat3("Location", Location_);
            ImGui::DragFloat3("Rotation", Rotation_);
            ImGui::DragFloat3("Scale", Scale_, 0.05f, 0.0f, 65535.0f);

            // Update Struct
            LocRotScale->PosX = Location_[0];
            LocRotScale->PosY = Location_[1];
            LocRotScale->PosZ = Location_[2];
            
            LocRotScale->RotX = Rotation_[0];
            LocRotScale->RotY = Rotation_[1];
            LocRotScale->RotZ = Rotation_[2];
            
            LocRotScale->ScaleX = Scale_[0];
            LocRotScale->ScaleY = Scale_[1];
            LocRotScale->ScaleZ = Scale_[2];
            
            // Update Position
            Cursors3D_->SetLocRotScale(*LocRotScale);
            

        // End System Controls Window
        ImGui::End();

    }



}