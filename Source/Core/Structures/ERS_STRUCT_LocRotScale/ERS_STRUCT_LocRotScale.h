//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for implementing the hardware information structure.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-07
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")



/**
 * @brief Stores Location, Rotation, Scale data in struct.
 * 
 */
struct ERS_STRUCT_LocRotScale {

    // Position
    float PosX;
    float PosY;
    float PosZ;

    // Rotation
    float RotX;
    float RotY;
    float RotZ;

    // Scale
    float ScaleX;
    float ScaleY;
    float ScaleZ;

};