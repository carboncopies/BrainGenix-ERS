//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-02
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <3DCursor.h>

/**
 * @brief Create GUI Widget "Rendering Settings"
 * 
 */
class Widget_ObjectProperties {

    private:

        

    public:

        // Show/Hide Var
        bool Enabled_ = true; /**<Show/Hide Widget*/

        /**
         * @brief Construct a new Widget_ObjectProperties object
         * 
         */
        Widget_ObjectProperties();

        /**
         * @brief Function that draws the window, should internally check if enable variable is set to true.
         * 
         */
        void Draw();

};