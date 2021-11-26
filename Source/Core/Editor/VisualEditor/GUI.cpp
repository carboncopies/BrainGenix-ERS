//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing the gui.
    Additonal Notes: None
    Date Created: 2021-01-25
*/

#include <GUI.h>

GUISystem::GUISystem(LoggerClass* Logger) {

    // Create Local Pointer
    Logger_ = Logger;

    // Initialize ImGui
    Logger_->Log("Initializing DearImGui GUI Library", 5);

    IMGUI_CHECKVERSION();
    //ImGui::CreateContext();  


}