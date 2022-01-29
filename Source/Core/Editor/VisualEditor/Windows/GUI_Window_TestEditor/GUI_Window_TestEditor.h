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

#include <zep/mcommon/animation/timer.h>

#include <zep/filesystem.h>
#include <zep/imgui/display_imgui.h>
#include <zep/imgui/editor_imgui.h>
#include <zep/mode_standard.h>
#include <zep/mode_vim.h>
#include <zep/tab_window.h>
#include <zep/theme.h>
#include <zep/window.h>

#include <orca/mode_orca.h>
#include <repl/mode_repl.h>

#include <zep/regress.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>



/**
 * @brief This class provides the window for a test editor, which doesn't actually do anything other than let you type into it to test zep.
 * 
 */
class Window_TestEditor {

// Private Member Vars
private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Pointer to system utils struct*/

// Public Methods
public:

    /**
     * @brief Construct a new Window_TestEditor object
     * 
     * @param SystemUtils 
     */
    Window_TestEditor(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);

    /**
     * @brief Destroy the Window_TestEditor object
     * 
     */
    ~Window_TestEditor();

}