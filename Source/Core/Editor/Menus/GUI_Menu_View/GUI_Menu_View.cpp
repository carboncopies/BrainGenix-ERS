//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_View.h>


GUI_Menu_View::GUI_Menu_View(ERS_STRUCT_SystemUtils* SystemUtils, ERS_CLASS_ThemeManager* ThemeManager, ERS_CLASS_FontManager* FontManager, ERS_STRUCT_Windows* Windows) {

    SystemUtils_ = SystemUtils;
    ThemeManager_ = ThemeManager;
    FontManager_ = FontManager;
    SystemUtils_->Logger_->Log("Editor Setting Up View Menu", 4);

    GUI_GUI_Window_About_ = std::make_unique<GUI_Window_About>(SystemUtils_);


}

GUI_Menu_View::~GUI_Menu_View() {

    SystemUtils_->Logger_->Log("Editor Destroying View Menu", 4);

}

void GUI_Menu_View::Draw() {

    // View Menu
    if (ImGui::BeginMenu("View")) {


        if (ImGui::MenuItem("Color Theme")) {
            GUI_Window_ThemeSelector_->Enabled_ = true;
        }

        if (ImGui::MenuItem("System Font")) {
            ShowFontPicker_ = true;
        }

        ImGui::Separator();

        if (ImGui::MenuItem("About")) {
            GUI_GUI_Window_About_->Enabled_ = true;
        }


    ImGui::EndMenu();
    }


    // Draw Windows
    GUI_Window_ThemeSelector_->Draw();
    GUI_GUI_Window_About_->Draw();
    FontManager_->FontSelectorWindow(&ShowFontPicker_);

}