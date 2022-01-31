//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//


#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <thread>
#include <string>
#include <mutex>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>
#include <TextEditor.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_ProjectUtils.h>



/**
 * @brief This class provides the window for the shader editor.
 * 
 */
class Window_ShaderEditor {

private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<System Utils Pointer*/
    std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils_; /**<Project Utils Pointer*/
    TextEditor Editor_; /** Editor Instance*/
    int Mode_ = 0; /**<Used To Determine what shader the user is editing*/
    long SelectedShaderProgramIndex_ = 0; /**<Index of the selected shader program in the project*/

public:

    bool Enabled_ = true; /**<Enable/Disable the editor window*/

public:

    /**
     * @brief Construct a new Window_ShaderEditor object
     * 
     * @param SystemUtils 
     */
    Window_ShaderEditor(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils);

    /**
     * @brief Destroy the Window_ShaderEditor object
     * 
     */
    ~Window_ShaderEditor();

    
    /**
     * @brief Draw the window.
     * 
     */
    void Draw();

};