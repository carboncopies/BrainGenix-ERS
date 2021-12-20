//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <thread>
#include <string>
#include <mutex>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>

/**
 * @brief Window for the Import progress bar.
 * 
 */
class Window_ImportProgressBar {

    private:

        int CurrentAssetNumber_ = 0; /**<Set Current Number Of Asset Being Imported*/
        int TotalAssetsToImport_ = 1; /**<Set Total Number Of Assets To Import*/
        std::mutex LockViewStats_; /**<Mutex To Prevent Values Being Changed During View/Write*/

        int ConsecFinished_ = 0; /**<Set number of consec frames that job is finished*/
        int ConsecFinishedThreshold_ = 2; /**<Hide After 100 frames of finished job*/

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Pointers To System Resources*/

    public:

        bool Enabled_ = false; /**<Is Popup Enabled*/


    public:

        /**
         * @brief Construct a new Window_ImportProgressBar object
         * 
         */
        Window_ImportProgressBar(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);
        
        /**
         * @brief Destroy the Window_ImportProgressBar object
         * 
         */
        ~Window_ImportProgressBar();


        /**
         * @brief Update Total items being processed (progress bar)
         * 
         * @param Current 
         * @param Total 
         */
        void UpdateTotalItems(long Current, long Total);

        /**
         * @brief close the window a few frames after the job finishes
         * 
         * @param JobState 
         */
        void UpdateJobState(bool JobFinished);

        /**
         * @brief Draw import bar if needed (call every frame)
         * 
         */
        void Draw();

};