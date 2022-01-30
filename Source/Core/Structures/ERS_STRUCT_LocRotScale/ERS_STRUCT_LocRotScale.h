//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

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