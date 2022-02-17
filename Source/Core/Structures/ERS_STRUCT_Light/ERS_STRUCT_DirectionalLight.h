//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")


struct ERS_STRUCT_DirectionalLight {

    std::string UserDefinedName; /**Name of the light assigned by user*/
    
    float ColorRed; /**<Red Component*/
    float ColorGreen; /**<Green Component*/
    float ColorBlue; /**<Blue Component*/
    
    float PosX; /**<Position*/
    float PosY; /**<Position*/
    float PosZ; /**<Position*/

    float RotX; /**<Rotation (direction)*/
    float RotY; /**<Rotation (direction)*/
    float RotZ; /**<Rotation (direction)*/

};