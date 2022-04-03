//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_SceneManager.h>
#include <ERS_STRUCT_Scene.h>
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_ProjectUtils.h>

#include <ERS_GUI_CLASS_SceneRenameModal.h>
#include <ERS_GUI_CLASS_ModelRenameModal.h>
#include <ERS_GUI_CLASS_PointLightRenameModal.h>
#include <ERS_GUI_CLASS_SpotLightRenameModal.h>
#include <ERS_GUI_CLASS_DirectionalLightRenameModal.h>
#include <ERS_GUI_CLASS_DeleteScene.h>
#include <ERS_GUI_CLASS_DeleteModel.h>

#include <ERS_GUI_FUNCTION_DuplicateScene.h>
#include <ERS_GUI_FUNCTION_DuplicateModel.h>
#include <ERS_GUI_FUNCTION_DuplicatePointLight.h>
#include <ERS_GUI_FUNCTION_DuplicateDirectionalLight.h>
#include <ERS_GUI_FUNCTION_DuplicateSpotLight.h>




/**
 * @brief Struct containing the info about an object in the scene
 * 
 */
struct ERS_STRUCT_SceneObject {

    std::string Type_; /**<Name Of The Type Of The Object*/
    std::string Label_; /**<Human Readable Name Of The Object*/
    unsigned long Index_; /**<Index in respective list (e.g. If Type Is Model, This Would Be The Index In The Model List)*/

};

/**
 * @brief Create GUI Window "Rendering Settings"
 * 
 */
class Window_SceneTree {

private:

    ERS_CLASS_SceneManager* SceneManager_; /**<Scene Manager Instance Pointer*/
    ERS_STRUCT_SystemUtils* SystemUtils_; /**<SystemUtils Pointer*/
    ERS_STRUCT_ProjectUtils* ProjectUtils_; /**<ProjectUtils Pointer*/
    bool FirstFrame_ = true; /**<Bool Indicating if It's the first frame*/

    Subwindow_SceneRenameModal* Subwindow_SceneRenameModal_; /**<Scene Rename Modal Instance*/
    Subwindow_ModelRenameModal* Subwindow_ModelRenameModal_; /**<Model Rename Modal Instance*/
    std::unique_ptr<Subwindow_PointLightRenameModal> Subwindow_PointLightRenameModal_; /**<PointLight Rename Modal Instance*/
    std::unique_ptr<Subwindow_DirectionalLightRenameModal> Subwindow_DirectionalLightRenameModal_; /**<DirectionalLight Rename Modal Instance*/
    std::unique_ptr<Subwindow_SpotLightRenameModal> Subwindow_SpotLightRenameModal_; /**<SpotLight Rename Modal Instance*/
    
    Subwindow_DeleteScene* Subwindow_DeleteScene_; /**<Scene Deletion Modal Instance*/
    Subwindow_DeleteModel* Subwindow_DeleteModel_; /**<Model Deletion Modal Instance*/

    std::vector<ERS_STRUCT_SceneObject> SceneObjects_; /**<Vector containing the type of the scene object*/

private:

    /**
     * @brief Draw A Scene Under A Tree Node
     * 
     * @param Scene 
     * @param SceneIndex
     */
    void DrawScene(ERS_STRUCT_Scene* Scene, int SceneIndex);

    /**
     * @brief Adds all models, lights, etc to the scene tree object vector.
     * 
     */
    void IndexSceneObjects(ERS_STRUCT_Scene* Scene); 


public:

    // Show/Hide Var
    bool Enabled_ = true; /**<Show/Hide Window*/

public:

    /**
     * @brief Construct a new Window_SceneTree object
     * 
     */
    Window_SceneTree(ERS_CLASS_SceneManager* SceneManager, ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils);

    /**
     * @brief Destroy the Window_SceneTree object
     * 
     */
    ~Window_SceneTree();

    /**
     * @brief Function that draws the window, should internally check if enable variable is set to true.
     * 
     */
    void Draw();

};