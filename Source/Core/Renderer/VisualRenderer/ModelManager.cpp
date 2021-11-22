//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the model manager classes.
    Documentation Status: Done
    Additonal Notes: None
    Date Created: 2021-11-21
*/

#include <ModelManager.h>


// Constructor For ModelManager Class
ModelManager::ModelManager(LoggerClass *Logger) {

    // Copy To Local Pointer
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing ModelManager Instance", 5);

}


// Destructor For ModelManager Class
ModelManager::~ModelManager() {

    // Log Destructor Call
    Logger_->Log("Destructor Called For ModelManager Class", 6);

}