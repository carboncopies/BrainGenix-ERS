//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides a GUI menu entry.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Menu_Debug.h>


// Constructor
GUI_Menu_Debug::GUI_Menu_Debug(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<Cursors3D> Cursors3D, std::shared_ptr<SceneManager> SceneManager) {

    // Copy In Pointer Struct
    SystemUtils_ = SystemUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Editor Setting Up Debug Menu", 4);


}


// Destructor
GUI_Menu_Debug::~GUI_Menu_Debug() {

    // Log Destructor
    SystemUtils_->Logger_->Log("Editor Destroying Debug Menu", 4);

}


// Draw Function
void GUI_Menu_Debug::Draw() {

    // Debug Menu
    if (ImGui::BeginMenu("Debug")) {

        // Debugging Tools Menu
        ImGui::CheckBox("Show ImGui Demo Window", &ShowImGuiDemoWindow_);


    ImGui::EndMenu();
    }



}