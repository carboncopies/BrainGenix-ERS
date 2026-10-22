//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <SceneManager.h>


/**
 * @brief Create GUI Window "Rendering Settings"
 * 
 */
class Subwindow_SceneCameraRenameModal {

private:

    ERS_CLASS_SceneManager* SceneManager_; /**<SceneCamera Manager Instance Pointer*/
    char SceneCameraInputName_[128] = ""; /**<Character Array To Store SceneCamera Name When Renaming*/


public:

    // Show/Hide Var
    bool Enabled_ = false; /**<Show/Hide Window*/
    bool FirstFrame_ = false; /**<Used To Run Certain Things On Window Open*/
    int SelectedSceneCamera_ = 0; /**<Indicate What Index The Selected SceneCamera Is*/
    int SelectedScene_ = 0; /**<Indicate What Index The Selected Scene Is*/

public:

    /**
     * @brief Construct a new Subwindow_SceneCameraRenameModal object
     * 
     */
    Subwindow_SceneCameraRenameModal(ERS_CLASS_SceneManager* SceneManager);

    /**
     * @brief Destroy the Subwindow_SceneCameraRenameModal object
     * 
     */
    ~Subwindow_SceneCameraRenameModal();


    /**
     * @brief Show The SceneCamera Rename Modal
     * 
     * @param SelectedScene
     * @param SelectedSceneCamera
     */
    void Activate(int SelectedScene, int SelectedSceneCamera);


    /**
     * @brief Function that draws the window, should internally check if enable variable is set to true.
     * 
     */
    void Draw();

};
