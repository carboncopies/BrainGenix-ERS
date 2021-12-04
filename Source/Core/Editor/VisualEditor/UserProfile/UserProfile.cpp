//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing user profile management.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-04
*/

#include <UserProfile.h>


// Constructor
UserProfileManager::UserProfileManager(LoggerClass *Logger, const char* UserProfilePath) {

    // Copy Pointer
    Logger_ = Logger;
    UserProfilePath_ = std::string(UserProfilePath);

    // Log Init
    Logger_->Log("Initializing User Profile Manager", 5);

}


// Destructor
UserProfileManager::~UserProfileManager() {

    // Log Destructor Call
    Logger_->Log("User Profile Destructo Called", 6);

}

// Load User Profile
void UserProfileManager::LoadUserProfile() {

    // Log Loading
    Logger_->Log(std::string(std::string("Loading User Profile At Path: ") + UserProfilePath_).c_str(), 4);

    // Load File
    UserProfile_ = YAML::LoadFile(UserProfilePath_.c_str());

    // Decode Profile
    UserFont_ = UserProfile_["DefaultFont"].as<std::string>();
    UserFontSize_ = UserProfile_["DefaultFontSize"].as<float>();
    UserColorProfileName_ = UserProfile_["DefaultColorTheme"].as<std::string>();

}