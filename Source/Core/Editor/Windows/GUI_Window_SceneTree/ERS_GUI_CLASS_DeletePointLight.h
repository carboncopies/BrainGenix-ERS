//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_SceneManager.h>
#include <ERS_STRUCT_Scene.h>

#include <ERS_Editor_3DCursor.h>


/**
 * @brief Implement Scene Deltion, Open Popup For Confirm, Error.
 * 
 */
class Subwindow_DeletePointLight {

private:

    ERS_CLASS_SceneManager* SceneManager_; /**<SceneManager Instance*/
    int SceneIndex_ = 0; /**<Scene Index Used To Remember What Scene To Delete From*/
    int PointLightIndex_ = 0; /**<Use to identify what PointLight to delete*/

    bool FirstFrame_ = false; /**<Used to grab keyboard input on first frame window is open*/

    bool ShowDeleteConfirm_ = false; /**<Confirm Deletion Of Scene*/

private:

    void UpdateConfirmDeletePopup(); /**<Function To Update Popup Deletion Window*/

public:

    /**
     * @brief Construct a new Subwindow_DeletePointLight object
     * 
     */
    Subwindow_DeletePointLight(ERS_CLASS_SceneManager* SceneManager);

    /**
     * @brief Destroy the Subwindow_DeletePointLight object
     * 
     */
    ~Subwindow_DeletePointLight();

    /**
     * @brief Called by the GUI to delete a scene.
     * 
     * @param SceneIndex 
     * @param PointLightIndex 
     */
    void DeletePointLight(int SceneIndex, int PointLightIndex);

    /**
     * @brief Update all windows created by this class. Call every frame.
     * 
     */
    void Draw();

};

 