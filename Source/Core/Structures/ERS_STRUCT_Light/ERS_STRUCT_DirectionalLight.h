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
#include <ERS_STRUCT_DepthMap.h>


struct ERS_STRUCT_DirectionalLight {

    std::string UserDefinedName; /**Name of the light assigned by user*/
    
    std::vector<long> AttachedScriptIndexes_; /**<Indexes of attached scripts (index in the project struct's list of scripts)*/

    glm::vec3 Color; /**<Color of the light*/
    float Intensity; /**<Intensity of the light*/
    
    glm::vec3 Pos; /**<Position*/
    glm::vec3 Rot; /**<Rotation or Direction Of Light*/

    ERS_STRUCT_DepthMap DepthMap; /**<Contains OpenGL IDS Used To Calculate Shadows*/

    glm::mat4 LightSpaceMatrix; /**<Matrix From Light's Perspective*/

};