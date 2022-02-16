//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//


#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <thread>
#include <string>
#include <mutex>
#include <sstream>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>
#include <TextEditor.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_ProjectUtils.h>
#include <ERS_STRUCT_Shader.h>
#include <ERS_STRUCT_ShaderProgramAssetIDs.h>

#include <ERS_CLASS_ShaderLoader.h>

#include <ERS_CLASS_VisualRenderer.h>






/**
 * @brief This class provides the window for the shader editor.
 * 
 */
class Window_ShaderEditor {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<System Utils Pointer*/
    std::shared_ptr<ERS_CLASS_VisualRenderer> VisualRenderer_; /**<Shared Pointer To Visual Renderer*/
    std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils_; /**<Project Utils Pointer*/
    std::shared_ptr<ERS_CLASS_ShaderLoader> ShaderLoader_; /**<Pointer To Shader Loader Instnace*/
    std::vector<std::shared_ptr<TextEditor>> Editors_; /**<List of editors, one for each type of shader*/
    std::shared_ptr<TextEditor> Editor_; /** Editor Instance*/
    int Mode_ = 0; /**<Used To Determine what shader the user is editing*/
    long SelectedShaderProgramIndex_ = 0; /**<Index of the selected shader program in the project*/
    std::string LastFrameText_; /**Set The Last Text Shown In The Editor*/
    std::shared_ptr<ERS_STRUCT_Shader> LivePreviewShader_; /**<Current live preview shader*/
    bool LastEnabledState_ = false; /**<Last State From Last Frame*/
    int LivePreviewShaderIndex_; /**<Index of Live Preview Shader*/


private:

    /**
     * @brief Reloads the text from the selected asset id and shader program
     * 
     */
    void ReloadEditorText();

    /**
     * @brief Save the shader to asset data.
     * 
     */
    void SaveShader(std::string ShaderText, long AssetID);

    /**
     * @brief Draws the main editor window
     * 
     */
    void DrawEditorWindow();

    /**
     * @brief Draws the shader tools window
     * 
     */
    void DrawToolsWindow();


public:

    bool Enabled_ = true; /**<Enable/Disable the editor window*/

public:

    /**
     * @brief Construct a new Window_ShaderEditor object
     * 
     * @param SystemUtils 
     */
    Window_ShaderEditor(ERS_STRUCT_SystemUtils* SystemUtils, std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils, std::shared_ptr<ERS_CLASS_VisualRenderer> VisualRenderer);

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