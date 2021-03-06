//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <memory>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

#include <imgui.h>

#include <ImGuiFileDialog.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_Editor_ImportAsset.h>
#include <GUI_Window_ImportProgressBar.h>


/**
 * @brief This class provides the GUI to the import asset option within the file menu.
 *
 */
class GUI_ImportAsset {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<used to get access to system utilites like IOmanager, logger, etc.*/
    std::unique_ptr<GUI_Window_ImportProgressBar> GUI_Window_ImportProgressBar_; /**<Pointer To Window Import Progres Bar*/
    std::unique_ptr<ERS_CLASS_ImportAsset> AssetImportBackend_; /**<Backend used to handle actual importing, threads, etc.*/

public:

    /**
     * @brief Construct a new gui importasset object.
     * 
     * @param SystemUtils 
     */
    GUI_ImportAsset(ERS_STRUCT_SystemUtils* SystemUtils);

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


    /**
     * @brief Open File Dialog
     * 
     */
    void OpenFileDialog();

};