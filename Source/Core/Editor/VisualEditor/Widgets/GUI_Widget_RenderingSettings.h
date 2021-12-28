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


/**
 * @brief Create GUI Widget "Rendering Settings"
 * 
 */
class Widget_RenderingSettings {

    private:

        ImVec4 ClearColor_ = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); /**<Background Clearing Color */
        bool OpenGLDrawLines_ = false; /**<Default Rendering Mode */
        bool HasFramerateChanged_ = true; /**<Update framerate when true, ignore when false*/
        int TargetFrameRate_ = 60; /**<The target framerate for the system*/

    public:

        // Show/Hide Var
        bool Enabled_ = true; /**<Show/Hide Widget*/


        /**
         * @brief Function that draws the window, should internally check if enable variable is set to true.
         * 
         */
        void Draw();

};