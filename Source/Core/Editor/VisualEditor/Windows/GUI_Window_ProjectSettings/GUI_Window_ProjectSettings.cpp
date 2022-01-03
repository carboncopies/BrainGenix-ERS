//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2022-01-03
*/

#include <GUI_Window_ProjectSettings.h>


// Constructor
Window_ProjectSettings::Window_ProjectSettings(std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils, std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy Pointers
    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Initializing ERS GUI Window Project Settings", 5);

}

// Destructor
Window_ProjectSettings::~Window_ProjectSettings() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("ERS Window Project Settings Destructor Called", 6);

}