//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a simple class to interface with the ERS Databse schema.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-01-27
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>


/**
 * @brief System to Interface With the ERS Database In An Abstract Manner.
 * 
 */
class DatabaseInterface {


    private:


        LoggerClass *Logger_; /**<Pointer to Instance Of LoggerClass */


    public:

        /**
         * @brief Construct a new Database Interface object
         * 
         * @param Logger 
         */
        DatabaseInterface(LoggerClass *Logger);

        /**
         * @brief Destroy the Database Interface object
         * 
         */
        ~DatabaseInterface();


};