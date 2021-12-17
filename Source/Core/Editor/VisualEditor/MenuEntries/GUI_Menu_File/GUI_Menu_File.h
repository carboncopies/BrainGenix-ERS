//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides a GUI menu entry.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <iostream>
#include <filesystem>
#include <string>
#include <memory>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <ERS_STRUCT_SystemUtils.h>

#include <SceneWriter.h>
#include <SceneManager.h>




/**
 * @brief This class provides the "File" Menu In The Editor.
 * 
 */
class GUI_Menu_File {

    // Member Vars
    private:

        ERS_STRUCT_SystemUtils SystemUtils_; /**<SystemUtils Instance, Used To Get Systems From Other Classes*/
        std::unique_ptr<SceneWriter> SceneWriter_; /**<Scene Writer Instance Pointer*/
        std::shared_ptr<SceneManager> SceneManager_; /**<Scene Manager Instance Pointer*/


    // Member Functions
    public:


        /**
         * @brief Construct a new gui menu file object
         * 
         * @param SystemUtils 
         */
        GUI_Menu_File(ERS_STRUCT_SystemUtils SystemUtils);


        /**
         * @brief Destroy the gui menu file object
         * 
         */
        ~GUI_Menu_File();


        /**
         * @brief This function Draws The File Menu Contents.
         * 
         */
        void Draw();


};