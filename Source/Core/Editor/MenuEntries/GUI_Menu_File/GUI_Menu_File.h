//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

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
#include <ERS_CLASS_LoggingSystem.h>
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_ProjectUtils.h>
#include <ERS_ProjectLoader.h>

#include <GUI_ImportAsset.h>

#include <ERS_SceneWriter.h>
#include <ERS_SceneManager.h>

#include <GUI_Window_ProjectSettings.h>
#include <GUI_Window_ShaderEditor.h>

#include <ERS_CLASS_VisualRenderer.h>


/**
 * @brief This class provides the "File" Menu In The Editor.
 * 
 */
class GUI_Menu_File {

private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<SystemUtils Instance, Used To Get Systems From Other Classes*/
    std::shared_ptr<ERS_CLASS_VisualRenderer> VisualRenderer_; /**<shared pointer to visual renderer*/
    std::unique_ptr<SceneWriter> SceneWriter_; /**<Scene Writer Instance Pointer*/
    std::shared_ptr<ERS_CLASS_SceneManager> SceneManager_; /**<Scene Manager Instance Pointer*/
    std::unique_ptr<GUI_ImportAsset> ImportAsset_; /**<Pointer To Asset Importer System*/
    std::unique_ptr<Window_ProjectSettings> Window_ProjectSettings_; /**<Project Settings Window*/
    std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils_; /**<Pointer To Project Utils Instance*/
    std::unique_ptr<Window_ShaderEditor> ShaderEditor_; /**<Pointer To Shader Editor Window Instance*/


public:


    /**
     * @brief Construct a new gui menu file object
     * 
     * @param SystemUtils 
     */
    GUI_Menu_File(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_CLASS_SceneManager> SceneManager, std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils, std::shared_ptr<ERS_CLASS_VisualRenderer> VisualRenderer);


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