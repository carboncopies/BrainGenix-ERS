//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for creating and managing the framebuffer.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-28
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>


/**
 * @brief Class to create/renderto/destruy framebuffer object.
 * 
 */
class FramebufferManager {


    private:


        LoggerClass *Logger_; /**<Pointer to instance of Logger Class*/


    public:

        /**
         * @brief Construct a new Framebuffer Manager object.
         * 
         * @param Logger 
         */
        FramebufferManager(LoggerClass *Logger);

        /**
         * @brief Destroy the Framebuffer Manager object.
         * 
         */
        ~FramebufferManager();


};