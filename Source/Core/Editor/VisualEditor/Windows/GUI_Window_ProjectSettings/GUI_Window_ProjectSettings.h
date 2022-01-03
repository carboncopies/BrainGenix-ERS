//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2022-01-03
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <string>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_ProjectUtils.h>
#include <ERS_STRUCT_SystemUtils.h>



class Window_ProjectSettings {

private:

    char ProjectNameBuffer[512]; /** Project Name Buffer*/
    char ProjectCreationDateBuffer[64]; /** Project Creation Date*/
    char ProjectModificationDateBuffer[64]; /** Project Modification Date*/
    

    std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils_; /**<Pointer To Project Utils Instance*/
    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<System Utils Struct Pointer*/

public:

    bool Enabled_ = true; /**<Is Window Shown Or Hidden*/

public:

    /**
     * @brief Construct a new Window_ProjectSettings object
     * 
     * @param ProjectUtils 
     * @param SystemUtils 
     */
    Window_ProjectSettings(std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils, std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);

    /**
     * @brief Destroy the Window_ProjectSettings object
     * 
     */
    ~Window_ProjectSettings();


    /**
     * @brief Draw the window, call this every frame.
     * 
     */
    void Draw();

};