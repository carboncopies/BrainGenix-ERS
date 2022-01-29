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



/**
 * @brief This class provides the window for a test editor, which doesn't actually do anything other than let you type into it to test zep.
 * 
 */
class Window_TestEditor {


// Private Member Vars
private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Pointer to system utils struct*/

// Public Member Vars
public:

    bool Enabled_ = true; /**<Control var for the window, enables or disables it.*/


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


    /**
     * @brief Call every frame to update the window.
     * 
     */
    void Draw();

};