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



class Window_ShaderEditor {

private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<System Utils Pointer*/

public:

    /**
     * @brief Construct a new Window_ShaderEditor object
     * 
     * @param SystemUtils 
     */
    Window_ShaderEditor(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);

    /**
     * @brief Destroy the Window_ShaderEditor object
     * 
     */
    ~Window_ShaderEditor();

}