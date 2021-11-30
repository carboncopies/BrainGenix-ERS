//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides font loading/selecting functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-30
*/

#include <FontManager.h>


// FontManager Constructor
FontManager::FontManager(LoggerClass *Logger, const char* FontsDirPath) {

    // Create Pointers
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Font Manager", 5);

    // Copy Vars
    FontsDirectoryPath_ = FontsDirPath;

}

// FontManager Destructor
FontManager::~FontManager() {
    
}