//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides asset import functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-18
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <memory>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>


/**
 * @brief This class provides the GUI to the import asset option within the file menu.
 *
 */
class GUI_ImportAsset {

    private:

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<used to get access to system utilites like IOmanager, logger, etc.*/

    public:

        /**
         * @brief Construct a new gui importasset object.
         * 
         * @param SystemUtils 
         */
        GUI_ImportAsset(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);

        /**
         * @brief Destroy the gui importasset object.
         * 
         */
        ~GUI_ImportAsset();

        /**
         * @brief Update Any Windows
         * 
         */
        void Draw();


};