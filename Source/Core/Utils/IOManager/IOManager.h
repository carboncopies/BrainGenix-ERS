//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides IOManager functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-29
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>



/**
 * @brief The IOManager Class Gets All User Input And Provides It To The Rest Of The System
 * 
 */
class IOManager {

    private:


        LoggerClass *Logger_ /**<Logging System Instance Pointer*/


    public:

        /**
         * @brief Construct a new IOManager object
         * 
         * @param Logger 
         */
        IOManager(LoggerClass *Logger);

        /**
         * @brief Destroy the IOManager object
         * 
         */
        ~IOManager();


        /**
         * @brief Update the input for this frame.
         * 
         * @param DeltaTime 
         */
        void UpdateFrame(float DeltaTime);

};