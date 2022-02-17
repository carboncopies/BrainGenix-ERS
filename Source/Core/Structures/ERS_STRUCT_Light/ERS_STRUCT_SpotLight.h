//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")


struct ERS_STRUCT_SpotLight {

    std::string UserDefinedName; /**Name of the light assigned by user*/
    
    float RolloffConstant; /**<Rolloff constant*/
    float RolloffLinear; /**<Rolloff constant*/
    float RolloffQuadratic; /**<Rolloff constant*/
    

    float CutOff; /**<CutOff angle For Spotlight (inner)*/
    float OuterCutOff; /**<CutOff angleFor Spotlight (outer)*/
    
    
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