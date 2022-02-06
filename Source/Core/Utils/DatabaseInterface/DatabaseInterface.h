//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>


/**
 * @brief System to Interface With the ERS Database In An Abstract Manner.
 * 
 */
class DatabaseInterface {


    private:


        std::shared_ptr<ERS_CLASS_LoggingSystem> Logger_; /**<Pointer to Instance Of ERS_CLASS_LoggingSystem */


    public:

        /**
         * @brief Construct a new Database Interface object
         * 
         * @param Logger 
         */
        DatabaseInterface(std::shared_ptr<ERS_CLASS_LoggingSystem> Logger);

        /**
         * @brief Destroy the Database Interface object
         * 
         */
        ~DatabaseInterface();


};