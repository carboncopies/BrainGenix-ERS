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
#include <SceneManager.h>

#include <Scene.h>
#include <SystemUtils.h>
#include <ProjectUtils.h>
#include <SceneObject.h>
#include <3DCursor.h>

#include <SceneRenameModal.h>
#include <ModelRenameModal.h>
#include <PointLightRenameModal.h>
#include <SpotLightRenameModal.h>
#include <DirectionalLightRenameModal.h>

#include <DeleteScene.h>
#include <DeleteModel.h>
#include <DeletePointLight.h>
#include <DeleteDirectionalLight.h>
#include <DeleteSpotLight.h>

#include <ModelReplaceModal.h>

#include <DuplicateScene.h>
#include <DuplicateModel.h>
#include <DuplicatePointLight.h>
#include <DuplicateDirectionalLight.h>
#include <DuplicateSpotLight.h>



/**
 * @brief Create GUI Window "Rendering Settings"
 * 
 */
class GUI_Window_SceneTree {

private:

    ERS_CLASS_SceneManager* SceneManager_; /**<Scene Manager Instance Pointer*/
    ERS_STRUCT_SystemUtils* SystemUtils_; /**<SystemUtils Pointer*/
    ERS_STRUCT_ProjectUtils* ProjectUtils_; /**<ProjectUtils Pointer*/
    Cursors3D* Cursors3D_; /**<Pointer to Cursors3D Instance*/
    bool FirstFrame_ = true; /**<Bool Indicating if It's the first frame*/




    std::unique_ptr<Subwindow_SceneRenameModal> Subwindow_SceneRenameModal_; /**<Scene Rename Modal Instance*/
    std::unique_ptr<Subwindow_ModelRenameModal> Subwindow_ModelRenameModal_; /**<Model Rename Modal Instance*/
    std::unique_ptr<Subwindow_PointLightRenameModal> Subwindow_PointLightRenameModal_; /**<PointLight Rename Modal Instance*/
    std::unique_ptr<Subwindow_DirectionalLightRenameModal> Subwindow_DirectionalLightRenameModal_; /**<DirectionalLight Rename Modal Instance*/
    std::unique_ptr<Subwindow_SpotLightRenameModal> Subwindow_SpotLightRenameModal_; /**<SpotLight Rename Modal Instance*/
    
    std::unique_ptr<Subwindow_ModelReplaceModal> Subwindow_ModelReplaceModal_; /**<Window with functions to replace all existing instances of a model with another one*/

    std::unique_ptr<Subwindow_DeleteScene> Subwindow_DeleteScene_; /**<Scene Deletion Modal Instance*/
    std::unique_ptr<Subwindow_DeleteModel> Subwindow_DeleteModel_; /**<Model Deletion Modal Instance*/
    std::unique_ptr<Subwindow_DeletePointLight> Subwindow_DeletePointLight_; /**<PointLight Delete Subwindow*/
    std::unique_ptr<Subwindow_DeleteDirectionalLight> Subwindow_DeleteDirectionalLight_; /**<DirectionalLight Delete Subwindow*/
    std::unique_ptr<Subwindow_DeleteSpotLight> Subwindow_DeleteSpotLight_; /**<SpotLight Delete Subwindow*/
    



private:

    /**
     * @brief Draw A Scene Under A Tree Node
     * 
     * @param Scene 
     * @param SceneIndex
     */
    void DrawScene(ERS_STRUCT_Scene* Scene, int SceneIndex);




public:

    // Show/Hide Var
    bool Enabled_ = true; /**<Show/Hide Window*/

public:

    /**
     * @brief Construct a new Window_SceneTree object
     * 
     */
    GUI_Window_SceneTree(ERS_CLASS_SceneManager* SceneManager, ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, Cursors3D* Cursors3D);

    /**
     * @brief Destroy the Window_SceneTree object
     * 
     */
    ~GUI_Window_SceneTree();

    /**
     * @brief Function that draws the window, should internally check if enable variable is set to true.
     * 
     */
    void Draw();

};