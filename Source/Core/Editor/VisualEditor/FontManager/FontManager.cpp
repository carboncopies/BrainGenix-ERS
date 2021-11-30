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
    
    // Log Destructor Call
    Logger_->Log("Font Manager Destructor Called", 6);

}

// Check String Endings (From: https://stackoverflow.com/questions/874134/find-out-if-string-ends-with-another-string-in-c)
bool FontManager::EndsWith(const std::string& Input, const std::string& Ending) {
    if (Ending.size() > Input.size()) return false;
    return std::equal(Input.begin() + Input.size() - Ending.size(), Input.end(), Ending.begin());
}

// Index Fonts Function
void FontManager::IndexFonts() {

    // Get List Of Files At Path
    for (const auto &Entry : std::filesystem::recursive_directory_iterator(std::string(FontsDirectoryPath_))) {

        // Get File Path        
        std::string FilePath{Entry.path().u8string()};

        // Check Extension
        if ((EndsWith(FilePath, ".ttf")) || (EndsWith(FilePath, ".otf"))) {

            // Strip File Extension
            

        }

}