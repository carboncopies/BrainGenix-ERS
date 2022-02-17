//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_Debug.h>


// Constructor
GUI_Menu_Debug::GUI_Menu_Debug(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Editor Setting Up Debug Menu", 4);

    SystemUtils_->Logger_->Log("Reading Configuration File For 'ShowEditorDebugMenu' Parameter", 1);
    DebugMenuEnabled_ = (*SystemUtils_->LocalSystemConfiguration_)["ShowEditorDebugMenu"].as<bool>();

    // Setup Window Instances
    SystemUtils_->Logger_->Log("Initialiizng Debug Menu Window Instances", 5);
    TestEditor_ = std::make_unique<Window_TestEditor>(SystemUtils_);

}


// Destructor
GUI_Menu_Debug::~GUI_Menu_Debug() {

    // Log Destructor
    SystemUtils_->Logger_->Log("Editor Destroying Debug Menu", 4);

}


// Draw Function
void GUI_Menu_Debug::Draw() {

    // If Enabled
    if (DebugMenuEnabled_) {

        // Debug Menu
        if (ImGui::BeginMenu("Debug")) {

            std::cout<<"Test1\n";

            // Debugging Tools Menu
            if (ImGui::MenuItem("ImGui Demo Window")) {
                ShowImGuiDemoWindow_ = !ShowImGuiDemoWindow_;
            }
            std::cout<<"Test2\n";

            // Test Editor
            if (ImGui::MenuItem("Test Editor Window")) {
                TestEditor_->Enabled_ = !TestEditor_->Enabled_;
            }

            std::cout<<"Test3\n";

        ImGui::EndMenu();
        }


        // Show Demo Window If Enabled
        if (ShowImGuiDemoWindow_) {
            ImGui::ShowDemoWindow(&ShowImGuiDemoWindow_);
        }

    }


    // Draw Windows
    TestEditor_->Draw();


}