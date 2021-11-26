//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing the gui.
    Additonal Notes: None
    Date Created: 2021-01-25
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

// Internal Libraries (BG convention: use <> instead of "")


/**
 * @brief Implements the ERS gui system.
 * 
 */
class GUISystem {


    private:

        LoggerClass* Logger_; /**<Pointer To LoggerClass Instance*/


    public:

        /**
         * @brief Construct a new Gui System object
         * 
         * @param Logger 
         */
        GUISystem(LoggerClass* Logger);

        /**
         * @brief Destroy the Gui System object
         * 
         */
        ~GUISystem();

};
