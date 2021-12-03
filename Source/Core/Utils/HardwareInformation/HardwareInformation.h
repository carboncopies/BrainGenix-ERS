//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for implementing hardware information collection.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-01-25
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <infoware/cpu.hpp>
#include <infoware/version.hpp>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>

/**
 * @brief Create Hardware Information Class
 * 
 */
class HardwareInformation {

    private:

        LoggerClass *LoggingSystem_; /**<Instance Of Logging System*/

    public:

        /**
         * @brief Construct a new Hardware Information object
         * 
         * @param Logger 
         */
        HardwareInformation(LoggerClass *Logger);

        /**
         * @brief Destroy the Hardware Information object
         * 
         */
        ~HardwareInformation();



};