//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the model manager classes.
    Documentation Status: Done
    Additonal Notes: None
    Date Created: 2021-11-21
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>


/**
 * @brief The Model Manager class Handles Rendering and Calling Loading Of Models.
 * 
 */
class ModelManager{

    private:

        // Internal Member Pointers
        LoggerClass *Logger_; /**<Pointer To Logger Instance*/




    public:

        /**
         * @brief Construct a new Model Manager object
         * 
         * @param Logger 
         */
        ModelManager(LoggerClass *Logger);
        
        /**
         * @brief Destroy the Model Manager object
         * 
         */
        ~ModelManager();

};