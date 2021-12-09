//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-07
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <3DCursor.h>

#include <ERS_STRUCT_LocRotScale.h>



/**
 * @brief Create GUI Widget "Rendering Settings"
 * 
 */
class Widget_SceneTree {

    private:

        Cursors3D *Cursors3D_; /**<Instance pointer to cursors3d class*/

    public:

        // Show/Hide Var
        bool Enabled_ = true; /**<Show/Hide Widget*/

        /**
         * @brief Construct a new Widget_SceneTree object
         * 
         */
        Widget_SceneTree(Cursors3D *Cursors3D);

        /**
         * @brief Destroy the Widget_SceneTree object
         * 
         */
        ~Widget_SceneTree();

        /**
         * @brief Function that draws the window, should internally check if enable variable is set to true.
         * 
         */
        void Draw();

};