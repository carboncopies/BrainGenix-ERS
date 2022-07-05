//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <thread>
#include <chrono>
#include <iostream>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_OpenGLLoggingSystem.h>

/**
 * @brief Create Hardware Information Class
 * 
 */
class ERS_CLASS_ArgumentParser {

    private:

        ERS_CLASS_LoggingSysem* Logger_; /**<Pointer To Logger, Allowing The System To List Argument Value Stuff*/

    public:

        /**
         * @brief Construct a new Hardware Information object
         * 
         * @param Logger
         */
        ERS_CLASS_ArgumentParser(ERS_CLASS_LoggingSystem* Logger);

        /**
         * @brief Destroy the Hardware Information object
         * 
         */
        ~ERS_CLASS_ArgumentParser();



};