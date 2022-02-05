//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <InputProcessor.h>
#include <ERS_STRUCT_Camera.h>



/**
 * @brief Struct containing a viewport that would allow the visualrender to be simplified.
 * 
 */
struct ERS_STRUCT_Viewport {


    std::string Name; /**<Name of the viewport*/
    bool WasSelected = false; /**<Indicates if the gizmo was selected last frame*/
    bool MenuEnabled = false; /**>Indicate if the menu is enabled (opened by "`")*/
    int ShaderIndex = 0; /**<Index of the shader to be used*/

    std::shared_ptr<bool> Enabled; /**<Indicates if the viewport is enabled*/
    std::shared_ptr<InputProcessor> Processor; /**<Pointer to Input Processor*/
    std::shared_ptr<ERS_STRUCT_Camera> Camera; /**<Pointer To Camera Instance*/

    unsigned int FramebufferObject; /**<FBO OpenGL ID*/
    unsigned int FramebufferColorObject; /**<FBCO OpenGL ID*/
    unsigned int RenderbufferObject; /**<RBO OpenGL ID*/

    int Width = 1; /**<Viewport Width*/
    int Height = 1; /**<Viewport Height*/



};