//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the project loader.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-30
*/

#include <ProjectLoader.h>


// Constructor
ProjectLoader::ProjectLoader(LoggerClass *Logger) {

    // Create Local Pointer
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Project Loader", 5);

}

// Destructor
ProjectLoader::~ProjectLoader() {

    // Log Destructor Call
    Logger_->Log("ProjectLoader Destructor Called", 6);

}


