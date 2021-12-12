 
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
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <SceneManager.h>
#include <Scene.h>


/**
 * @brief Implement Scene Deltion, Open Popup For Confirm, Error.
 * 
 */
class Subwindow_DeleteScene {

    // Private Vars
    private:

        SceneManager* SceneManager_; /**<SceneManager Instance*/
        int SceneIndex_ = 0; /**<SceneIndex Used To Remember What Scene To Delete*/

        bool FirstFrame_ = false; /**<Used to grab keyboard input on first frame window is open*/

        bool ShowDeleteConfirm_ = false; /**<Confirm Deletion Of Scene*/
        bool ShowOneSceneDeleteError_ = false; /**<Error popup that shows when one scene is remaining, (Can't have no scenes)*/

    // Private Functions
    private:

        void UpdateConfirmDeletePopup(); /**<Function To Update Popup Deletion Window*/
        void UpdateOneSceneDeleteErrorPopup(); /**<Last scene deletion error popup*/

    public:

        /**
         * @brief Construct a new Subwindow_DeleteScene object
         * 
         */
        Subwindow_DeleteScene(SceneManager* SceneManager);

        /**
         * @brief Destroy the Subwindow_DeleteScene object
         * 
         */
        ~Subwindow_DeleteScene();

        /**
         * @brief Called by the GUI to delete a scene.
         * 
         * @param SceneIndex 
         */
        void DeleteScene(int SceneIndex);

        /**
         * @brief Update all windows created by this class. Call every frame.
         * 
         */
        void Update();

};
