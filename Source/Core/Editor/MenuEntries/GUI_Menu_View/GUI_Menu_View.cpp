//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_View.h>


GUI_Menu_View::GUI_Menu_View(ERS_STRUCT_SystemUtils* SystemUtils, std::shared_ptr<ERS_CLASS_ThemeManager> ThemeManager, std::shared_ptr<ERS_CLASS_FontManager> FontManager) {

    SystemUtils_ = SystemUtils;
    ThemeManager_ = ThemeManager;
    FontManager_ = FontManager;
    SystemUtils_->Logger_->Log("Editor Setting Up View Menu", 4);

    Window_ThemeSelector_ = std::make_unique<Window_ThemeSelector>(ThemeManager_); 
    Window_About_ = std::make_unique<Window_About>(SystemUtils_);


}

GUI_Menu_View::~GUI_Menu_View() {

    SystemUtils_->Logger_->Log("Editor Destroying View Menu", 4);

}

void GUI_Menu_View::Draw() {

    // View Menu
    if (ImGui::BeginMenu("View")) {


        if (ImGui::MenuItem("Color Theme")) {
            Window_ThemeSelector_->Enabled_ = true;
        }

        if (ImGui::MenuItem("System Font")) {
            ShowFontPicker_ = true;
        }

        ImGui::Separator();

        if (ImGui::MenuItem("About")) {
            Window_About_->Enabled_ = true;
        }


    ImGui::EndMenu();
    }


    // Draw Windows
    Window_ThemeSelector_->Draw();
    Window_About_->Draw();
    FontManager_->FontSelectorWindow(&ShowFontPicker_);

}