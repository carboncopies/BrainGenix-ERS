//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <SystemUtils.h>
#include <LayoutManager.h>


/**
 * @brief This class provides the "Layout" Menu In The Editor.
 *
 */
class GUI_Menu_Layout {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_ = nullptr; /**<SystemUtils Instance, Used To Get Systems From Other Classes*/
    ERS_CLASS_LayoutManager* LayoutManager_ = nullptr; /**<Layout Manager Instance*/

    bool LayoutsLoaded_ = false; /**<Tracks if layouts have been indexed during this editor session*/
    char LayoutNameBuffer_[128] = "New Layout"; /**<Input buffer used when saving a layout preset*/

    void EnsureLayoutsLoaded();
    void DrawSaveLayoutPopup();

public:

    /**
     * @brief Construct a new gui menu layout object
     *
     * @param SystemUtils
     * @param LayoutManager
     */
    GUI_Menu_Layout(ERS_STRUCT_SystemUtils* SystemUtils, ERS_CLASS_LayoutManager* LayoutManager);

    /**
     * @brief Destroy the gui menu layout object
     *
     */
    ~GUI_Menu_Layout();

    /**
     * @brief This function Draws The Layout Menu Contents.
     *
     */
    void Draw();

};
