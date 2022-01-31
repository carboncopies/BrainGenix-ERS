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
Widget_ObjectProperties::Widget_ObjectProperties(std::shared_ptr<Cursors3D> Cursors3D) {

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
        bool Visible = ImGui::Begin("Object Properties", &Enabled_);

            // Set Initial Window Size
            ImGui::SetWindowSize(ImVec2(400,250), ImGuiCond_FirstUseEver);

            if (Visible) {


                // LocRotScale Properties
                ImGui::DragFloat3("Location", (float*)glm::value_ptr(Cursors3D_->Pos_), 0.05f);
                ImGui::DragFloat3("Rotation", (float*)glm::value_ptr(Cursors3D_->Rot_), 0.05f);// FIXME: MAKE ROLL OVER TO 180 Degrees?
                ImGui::DragFloat3("Scale", (float*)glm::value_ptr(Cursors3D_->Scale_), 0.05f, 0.0f, 65535.0f);

            
            }

        // End System Controls Window
        ImGui::End();

    }



}