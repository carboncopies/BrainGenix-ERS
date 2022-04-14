//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_InputProcessor.h>
#include <ERS_CLASS_Grid.h>
#include <ERS_CLASS_LightIconRenderer.h>

#include <ERS_STRUCT_Camera.h>


/**
 * @brief Struct containing a viewport that would allow the visualrender to be simplified.
 * 
 */
struct ERS_STRUCT_Viewport {


    std::string Name; /**<Name of the viewport*/
    bool WasSelected = false; /**<Indicates if the gizmo was selected last frame*/
    bool MenuEnabled = true; /**<Indicate if the menu is enabled (opened by "`")*/
    bool GizmoEnabled = true; /**<Toggle On/Off The 3D Gizmo*/
    bool ShowCube = true; /**<Enable/Disable The Viewport Cube*/
    bool GridEnabled = true; /**<Enable/Disable The Viewport's Background Grid*/
    bool LightICons = true; /**<Draw or don't draw the light icons*/
    bool GammaCorrection = true; /**<Enable/disable gamma correction*/
    int ShaderIndex = 0; /**<Index of the shader to be used*/

    std::unique_ptr<bool> Enabled; /**<Indicates if the viewport is enabled*/
    std::unique_ptr<ERS_CLASS_InputProcessor> Processor; /**<Pointer to Input Processor*/
    std::unique_ptr<ERS_CLASS_Grid> Grid; /**<Pointer to grid instance*/
    std::unique_ptr<ERS_CLASS_LightIconRenderer> LightIconRenderer; /**<Light Icon Renderer Instance*/
    std::unique_ptr<ERS_STRUCT_Camera> Camera; /**<Pointer To Camera Instance*/

    unsigned int FramebufferObject; /**<FBO OpenGL ID*/
    unsigned int FramebufferColorObject; /**<FBCO OpenGL ID*/
    unsigned int RenderbufferObject; /**<RBO OpenGL ID*/

    int Width = 1; /**<Viewport Width*/
    int Height = 1; /**<Viewport Height*/

};