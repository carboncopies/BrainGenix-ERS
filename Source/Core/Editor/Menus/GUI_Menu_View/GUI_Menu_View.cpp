//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_View.h>


GUI_Menu_View::GUI_Menu_View(ERS_STRUCT_SystemUtils* SystemUtils, ERS_CLASS_FontManager* FontManager, ERS_STRUCT_Windows* Windows) {

    SystemUtils_ = SystemUtils;
    FontManager_ = FontManager;
    Windows_ = Windows;
    SystemUtils_->Logger_->Log("Editor Setting Up View Menu", 4);



}

GUI_Menu_View::~GUI_Menu_View() {

    SystemUtils_->Logger_->Log("Editor Destroying View Menu", 4);

}

void GUI_Menu_View::Draw() {

    // View Menu
    if (ImGui::BeginMenu("View")) {




    ImGui::EndMenu();
    }



}