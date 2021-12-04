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
UserProfileManager::UserProfileManager(LoggerClass *Logger) {

    // Copy Pointer
    Logger_ = Logger;

    // Log Init
    Logger_->Log("Initializing User Profile Manager", 5);

}


// Destructor
UserProfileManager::~UserProfileManager() {

    // Log Destructor Call
    Logger_->Log("User Profile Destructo Called", 6);

}