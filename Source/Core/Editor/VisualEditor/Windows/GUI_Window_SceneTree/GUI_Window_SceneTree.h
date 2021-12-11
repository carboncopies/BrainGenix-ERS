//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
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
#include <SceneManager.h>
#include <Scene.h>


/**
 * @brief Create GUI Window "Rendering Settings"
 * 
 */
class Window_SceneTree {

    private:

        SceneManager* SceneManager_; /**<Scene Manager Instance Pointer*/
        bool FirstFrame_ = true; /**<Bool Indicating if It's the first frame*/

        char SceneInputName_[128] = ""; /**<Character Array To Store Scene Name When Renaming*/

    private:

        /**
         * @brief Draw A Scene Under A Tree Node
         * 
         * @param Scene 
         */
        void DrawScene(ERS_OBJECT_SCENE* Scene);



    public:

        // Show/Hide Var
        bool Enabled_ = true; /**<Show/Hide Window*/

    public:

        /**
         * @brief Construct a new Window_SceneTree object
         * 
         */
        Window_SceneTree(SceneManager* SceneManager);

        /**
         * @brief Destroy the Window_SceneTree object
         * 
         */
        ~Window_SceneTree();

        /**
         * @brief Function that draws the window, should internally check if enable variable is set to true.
         * 
         */
        void Draw();

};