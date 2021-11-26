//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a function to draw a grid when the editor is enabled.
    Additonal Notes: None
    Date Created: 2021-01-25
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

// Internal Libraries (BG convention: use <> instead of "")


/**
 * @brief This function draws a grid on the screen with the given size and scale.
 * 
 * @param UnitSize Size of each "Cell" in the grid.
 * @param GridSize Number of cells across the grid (edge to edge).
 * @param GridPosX X position of grid.
 * @param GridPosY Y position of grid.
 * @param GridPosZ Z position of grid.
 */
void DrawGrid(float UnitSize = 1.0f, int GridSize = 10, float GridPosX = 0.0f, float GridPosY = 0.0f, float GridPosZ = 0.0f);