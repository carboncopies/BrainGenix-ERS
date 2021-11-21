//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the renderer manager.
    Additonal Notes: None
    Date Created: 2021-11-01
*/

#include "RendererManager.h"




// RendererManager Constructor
RendererManager::RendererManager(YAML::Node *SystemConfiguration, LoggerClass *Logger, bool *SystemShouldRun) {

    // Create Pointers
    Logger->Log("Populating RendererManager Member Pointers", 5);
    SystemConfiguration_ = SystemConfiguration;
    Logger_ = Logger;
    SystemShouldRun_ = SystemShouldRun;

    // Instantiate Renderers
    Logger_->Log("Instantiating Renderers", 5);
    //VisualRenderer_(SystemConfiguration, Logger, SystemShouldRun);


}

// RendererManager Destructor
RendererManager::~RendererManager() {

    // Log Destructor Call
    Logger_->Log("RendererManager Destructor Called", 6);

}



void RendererManager::UpdateLoop() { 

    // Call Updates
    VisualRenderer_.UpdateLoop();


}




