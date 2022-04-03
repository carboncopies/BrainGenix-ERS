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
#include <ERS_Editor_3DCursor.h>

#include <ERS_STRUCT_LocRotScale.h>

#include <ERS_SceneManager.h>



/**
 * @brief Create GUI Widget "Rendering Settings"
 * 
 */
class Widget_ObjectProperties {

private:

    Cursors3D* Cursors3D_; /**<Instance pointer to cursors3d class*/
    ERS_CLASS_SceneManager* SceneManager_; /**<Pointer To Scene Manager Instance*/

    float PointLightDiffuse_[3]; /**<Color Of Point Diffuse Lighting*/
    float PointLightAmbient_[3]; /**<Color Of Point Ambient Lighting*/


    /**
     * @brief Converts From A Vec To A Float*
     * 
     * @param In 
     * @param Out 
     */
    void VecToFloat(glm::vec3& In, float* Out);

    /**
     * @brief Converts from A Float* To A Vec
     * 
     * @param In 
     * @param Out 
     */
    void FloatToVec(float* In, glm::vec3* Out);


public:

    // Show/Hide Var
    bool Enabled_ = true; /**<Show/Hide Widget*/

    /**
     * @brief Construct a new Widget_ObjectProperties object
     * 
     */
    Widget_ObjectProperties(Cursors3D* Cursors3D, ERS_CLASS_SceneManager* SceneManager);

    /**
     * @brief Destroy the Widget_ObjectProperties object
     * 
     */
    ~Widget_ObjectProperties();

    /**
     * @brief Function that draws the window, should internally check if enable variable is set to true.
     * 
     */
    void Draw();

};