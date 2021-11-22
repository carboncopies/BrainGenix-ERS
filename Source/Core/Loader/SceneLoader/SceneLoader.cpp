//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the scene loader class.
    Documentation Status: Done
    Additonal Notes: None
    Date Created: 2021-11-22
*/

#include <SceneLoader.h>

// SceneLoader Constructor
SceneLoader::SceneLoader(LoggerClass *Logger) {

    // Create Local Pointer
    Logger_ = Logger;

    // Log Initializaton Start
    Logger_->Log("Initializing SceneLoader Subsystem", 5);

}

// SceneLoader Destructor
SceneLoader::~SceneLoader() {

    // Log Destructor Call
    Logger_->Log("SceneLoader Destructor Called", 6);

}