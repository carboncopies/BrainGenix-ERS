//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing user profile management.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-04
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>


/**
 * @brief 
 * 
 */
class UserProfileManager {


    private:

        LoggerClass *Logger_; /**<LoggerClass Instance Pointer*/

    public:

        /**
         * @brief Construct a new User Profile Manager object
         * 
         * @param Logger 
         */
        UserProfileManager(LoggerClass *Logger);

        /**
         * @brief Destroy the User Profile Manager object
         * 
         */
        ~UserProfileManager();


};