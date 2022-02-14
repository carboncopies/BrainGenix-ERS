//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")


struct ERS_STRUCT_Light {

    std::string UserDefinedName; /**Name of the light assigned by user*/
    std::string UserAdditionalNotes; /**<Any user defined additional notes*/

    std::string Type; /**<Type of light (point, area, etc.)*/

    float Intensity; /**<Brightness of the light*/

    int Red; /**<Red Component*/
    int Green; /**<Green Component*/
    int Blue; /**<Blue Component*/
    

};