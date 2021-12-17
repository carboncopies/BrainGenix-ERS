//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides a GUI menu entry.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Menu_View.h>


// Constructor
GUI_Menu_View::GUI_Menu_View(ERS_STRUCT_SystemUtils SystemUtils) {

    // Copy In Pointer Struct
    SystemUtils_ = SystemUtils;

    // Log Initialization
    SystemUtils_.Logger_->Log("Editor Setting Up View Menu", 4);

    // Create Class Instances



}

// Destructor
GUI_Menu_View::~GUI_Menu_View() {

    // Log Destructor
    SystemUtils_.Logger_->Log("Editor Destroying View Menu", 4);

}

// Draw Function
void GUI_Menu_View::Draw() {

    // View Menu
    if (ImGui::BeginMenu("View")) {


        if (ImGui::MenuItem("Color Theme")) {
            ShowColorThemePicker_ = true;
        }

        if (ImGui::MenuItem("System Font")) {
            ShowFontPicker_ = true;
        }


    ImGui::EndMenu();
    }

}