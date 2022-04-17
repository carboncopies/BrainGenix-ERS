//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>

// Internal Libraries (BG convention: use <> instead of "")


struct ERS_STRUCT_DirectionalLight {

    std::string UserDefinedName; /**Name of the light assigned by user*/
    
    std::vector<long> AttachedScriptIndexes_; /**<Indexes of attached scripts (index in the project struct's list of scripts)*/

    glm::vec3 Color; /**<Color of the light*/
    
    glm::vec3 Pos; /**<Position*/
    glm::vec3 Rot; /**<Rotation or Direction Of Light*/

};