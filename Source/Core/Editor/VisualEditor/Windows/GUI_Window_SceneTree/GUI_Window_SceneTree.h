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

#include <GUI_Subwindow_SceneRenameModal.h>
#include <GUI_Subwindow_ModelRenameModal.h>
#include <GUI_Subwindow_DeleteScene.h>
#include <GUI_Subwindow_DeleteModel.h>

#include <GUI_Windowutil_DuplicateScene.h>
#include <GUI_Windowutil_DuplicateModel.h>

/**
 * @brief Create GUI Window "Rendering Settings"
 * 
 */
class Window_SceneTree {

    private:

        std::shared_ptr<SceneManager> SceneManager_; /**<Scene Manager Instance Pointer*/
        bool FirstFrame_ = true; /**<Bool Indicating if It's the first frame*/

        Subwindow_SceneRenameModal* Subwindow_SceneRenameModal_; /**<Scene Rename Modal Instance*/
        Subwindow_ModelRenameModal* Subwindow_ModelRenameModal_; /**<Model Rename Modal Instance*/
        Subwindow_DeleteScene* Subwindow_DeleteScene_; /**<Scene Deletion Modal Instance*/
        Subwindow_DeleteModel* Subwindow_DeleteModel_; /**<Model Deletion Modal Instance*/

    private:

        /**
         * @brief Draw A Scene Under A Tree Node
         * 
         * @param Scene 
         * @param SceneIndex
         */
        void DrawScene(std::shared_ptr<ERS_OBJECT_SCENE> Scene, int SceneIndex);



    public:

        // Show/Hide Var
        bool Enabled_ = true; /**<Show/Hide Window*/

    public:

        /**
         * @brief Construct a new Window_SceneTree object
         * 
         */
        Window_SceneTree(std::shared_ptr<SceneManager> SceneManager);

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