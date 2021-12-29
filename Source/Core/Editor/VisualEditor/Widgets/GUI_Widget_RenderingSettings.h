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
#include <ERS_STRUCT_SystemUtils.h>



/**
 * @brief Create GUI Widget "Rendering Settings"
 * 
 */
class Widget_RenderingSettings {

    private:

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<System Utils Pointer*/

        ImVec4 ClearColor_ = ImVec4(0.2f, 0.2f, 0.2f, 1.0f); /**<Background Clearing Color */
        bool OpenGLDrawLines_ = false; /**<Default Rendering Mode */


    public:

        // Show/Hide Var
        bool Enabled_ = true; /**<Show/Hide Widget*/


        /**
         * @brief Construct a new Widget_RenderingSettings object
         * 
         * @param SystemUtils 
         */
        Widget_RenderingSettings(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);

        /**
         * @brief Destroy the Widget_RenderingSettings object
         * 
         */
        ~Widget_RenderingSettings();


        /**
         * @brief Function that draws the window, should internally check if enable variable is set to true.
         * 
         */
        void Draw();

};