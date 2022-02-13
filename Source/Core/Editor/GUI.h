//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>

#include <implot.h>


#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <ImGuizmo.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>
#include <ERS_CLASS_VisualRenderer.h>

#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_ProjectUtils.h>
#include <ERS_STRUCT_HumanInputDeviceUtils.h>

#include <ERS_Editor_FontManager.h>
#include <ERS_Editor_ThemeManager.h>
#include <ERS_Editor_UserProfileManager.h>

#include <ERS_SceneManager.h>
#include <ERS_Editor_3DCursor.h>

#include <GUI_Menu_File.h>
#include <GUI_Menu_View.h>
#include <GUI_Menu_Window.h>
#include <GUI_Menu_Debug.h>
#include <GUI_Menu_Settings.h>





/**
 * @brief Implements the ERS gui system.
 * 
 */
class GUISystem {


private:

    GLFWwindow* Window_; /**<Pointer to window instance*/
    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Structure Containing Pointers To System Utilities*/
    std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils_; /**ProjectUtils Struct Pointer*/

    std::shared_ptr<ERS_CLASS_FontManager> FontManager_; /**<Pointer To FontManager Instance*/
    std::shared_ptr<ERS_CLASS_UserProfileManager> UserProfileManager_; /**<Pointer To User Profile Manager Instance*/
    std::shared_ptr<Cursors3D> Cursors3D_; /**<Pointer to Cursors3D Instance*/
    std::shared_ptr<ERS_CLASS_SceneManager> SceneManager_; /**<Scene Manager Instance Pointer*/
    std::shared_ptr<ERS_CLASS_VisualRenderer> VisualRenderer_; /**<Pointer to visual renderer for viewport modification*/
    std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils_; /**<Pointer To Human Device Utils Struct*/

public:

    std::shared_ptr<ERS_CLASS_ThemeManager> ThemeManager_; /**<Pointer To ThemeManager Instance*/

    // Menu Items
    std::unique_ptr<GUI_Menu_File> Menu_File_; /**<Editor Menu Entry*/
    std::unique_ptr<GUI_Menu_View> Menu_View_; /**<Editor Menu Entry*/
    std::unique_ptr<GUI_Menu_Window> Menu_Window_; /**<Editor Menu Entry*/
    std::unique_ptr<GUI_Menu_Debug> Menu_Debug_; /**<Editor Menu Entry*/
    std::unique_ptr<GUI_Menu_Settings> Menu_Settings_; /**<Editor Menu Entry*/


    /**
     * @brief Construct a new Gui System object
     * 
     * @param Logger 
     */
    GUISystem(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils,
    GLFWwindow* Window,
    std::shared_ptr<Cursors3D> Cursors3D,
    std::shared_ptr<ERS_CLASS_SceneManager> SceneManager,
    std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils,
    std::shared_ptr<ERS_CLASS_VisualRenderer> VisualRendererInstance,
    std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils
    );

    /**
     * @brief Destroy the Gui System object
     * 
     */
    ~GUISystem();


    /**
     * @brief Generate Frame REMEMBER TO CALL UPDATE FRAME AFTER THE CLEAR CALL.
     * 
     */
    void UpdateGUI();

    /**
     * @brief Update Frame, make sure you've called updategui.
     * 
     */
    void UpdateFrame();
    
    /**
     * @brief Use this for functions/widgets/windows that need to be updated after the main rendering takes place.
     * 
     */
    void DeferredFrameUpdate();
};
