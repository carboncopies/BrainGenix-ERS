//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Internal Libraries (BG convention: use <> instead of "")



/**
 * @brief Camera object used in the game. Provides control for the user to move the game's camera as they please.
 * 
 */
struct ERS_STRUCT_SceneCamera {

    glm::vec3 Pos_; /**<Position of the camera object*/
    glm::vec3 Rot_; /**<Rotation of the camera object*/

};