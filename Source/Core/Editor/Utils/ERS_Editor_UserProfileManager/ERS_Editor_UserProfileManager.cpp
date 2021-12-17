//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing user profile management.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-04
*/

#include <ERS_Editor_UserProfileManager.h>


// Constructor
ERS_CLASS_UserProfileManager::ERS_CLASS_UserProfileManager(std::shared_ptr<LoggerClass> Logger, const char* UserProfilePath) {

    // Copy Pointer
    Logger_ = Logger;
    UserProfilePath_ = std::string(UserProfilePath);

    // Log Init
    Logger_->Log("Initializing User Profile Manager", 5);
    LoadUserProfile();

}


// Destructor
ERS_CLASS_UserProfileManager::~ERS_CLASS_UserProfileManager() {

    // Log Destructor Call
    Logger_->Log("User Profile Destructo Called", 6);

}

// Load User Profile
void ERS_CLASS_UserProfileManager::LoadUserProfile() {

    // Log Loading
    Logger_->Log(std::string(std::string("Loading User Profile At Path: ") + UserProfilePath_).c_str(), 4);

    // Load File
    UserProfile_ = YAML::LoadFile(UserProfilePath_.c_str());

    // Decode Profile
    UserFont_ = UserProfile_["DefaultFont"].as<std::string>();
    UserFontSize_ = UserProfile_["DefaultFontSize"].as<float>();
    UserColorProfileName_ = UserProfile_["DefaultColorTheme"].as<std::string>();

}

// Return Object Functions
std::string ERS_CLASS_UserProfileManager::GetUserFont() {
    return UserFont_;
}

int ERS_CLASS_UserProfileManager::GetUserFontSize() {
    return UserFontSize_;
}

std::string ERS_CLASS_UserProfileManager::GetUserColorProfile() {
    return UserColorProfileName_;
}