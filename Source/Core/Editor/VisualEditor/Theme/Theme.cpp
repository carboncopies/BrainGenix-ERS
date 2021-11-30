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
    ThemePath_ = ThemePath;

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

    // Clear Vectors
    ThemeNames_ = *new std::vector<std::string>;
    ThemeFiles_ = *new std::vector<YAML::Node>;

    // Create List Of Files
    for (const auto &Entry : std::filesystem::directory_iterator(std::string(ThemePath_))) {

        // Get File Path        
        std::string FilePath = Entry.path();

        // Load YAML::Node
        YAML::Node Theme = YAML::LoadFile(FilePath.c_str());
        ThemeFiles_.push_back(Theme);

        // Parse Out Name From File Path
        FilePath = FilePath.substr(strlen(ThemePath_)+1);
        FilePath = FilePath.substr(0, strlen(FilePath.c_str())-5);

        // Add To Names Vector
        ThemeNames_.push_back(FilePath);

        // Log Theme Loaded
        Logger_->Log(std::string(std::string("Loaded Theme: ") + FilePath).c_str(), 1);

    }


    // Log Number Of Themes Found
    Logger_->Log(std::string(std::string("Found ") + std::to_string(ThemeNames_.size()) + std::string(" Themes")).c_str(), 1);

    for (int i = 0; i < ThemeNames_.size(); i++) {

    }

}