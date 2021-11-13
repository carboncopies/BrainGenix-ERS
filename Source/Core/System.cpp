//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file handles initailization and loading of all other ERS systems.
    Additonal Notes: None
    Date Created: 2021-11-12
*/

#include "Core/System.h"


// Constructor
sERSSubSystem::sERSSubSystem(LoggerClass *Logger) {

    // Start Initialization
    Logger->Log("Initializing Main Subsystem", 6);

    // Copy Pointer
    *Logger_ = Logger;

    // Finish Initialization
    Logger_.Log("Initialized Main Subsystem", 5);

}