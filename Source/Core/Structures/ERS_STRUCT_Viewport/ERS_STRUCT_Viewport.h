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
#include <NoClip.h>



/**
 * @brief Struct containing a viewport that would allow the visualrender to be simplified.
 * 
 */
struct ERS_STRUCT_Viewport {


    std::string Name; /**<Name of the viewport*/
    bool WasSelected; /**<Indicates if the gizmo was selected last frame*/
    int ShaderIndex; /**<Index of the shader to be used*/

    std::shared_ptr<bool> Enabled; /**<Indicates if the viewport is enabled*/
    std::shared_ptr<InputProcessor> Processor; /**<Pointer to Input Processor*/
    std::shared_ptr<ERS_OBJECT_CAMERA_NOCLIP> Camera; /**<Pointer To Camera Instance*/

    unsigned int FramebufferObject; /**<FBO OpenGL ID*/
    unsigned int FramebufferColorObject; /**<FBCO OpenGL ID*/
    unsigned int RenderbufferObject; /**<RBO OpenGL ID*/

    int Width; /**<Viewport Width*/
    int Height; /**<Viewport Height*/



};