//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides theme loading functionality..
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-29
*/

#include <Theme.h>


// ThemeManager Constructor
ThemeManager::ThemeManager(LoggerClass *Logger, const char* ThemePath) {

    // Create Local Pointers
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Theme Manager", 5);

    // Find Themes
    LoadThemes();

}

// ThemeManager Destructor
ThemeManager::~ThemeManager() {

    // Log Destructor Call
    Logger_->Log("ThemeManager Destructor Called", 6);

}

// Load Themes
void ThemeManager::LoadThemes() {

    // Create List Of Files
    std::vector<std::string> FilePaths;

    namespace FS = std::filesystem;
    for (const auto &Entry : FS::directory_iterator(std::string(ThemePath_))) {
        FilePaths.push_back(Entry.path());
    }

    for (int i = 0; i < FilePaths.size(); i++) {

        std::cout<<FilePaths[i]<<std::endl;
    }

}