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
#include <DepthMap.h>


struct ERS_STRUCT_PointLight {

    std::string UserDefinedName; /**Name of the light assigned by user*/
    
    float Intensity; /**<Intensity of the light*/
    float MaxDistance; /**<Distance After Which This Light No Longer Affects The Scene*/

    std::vector<long> AttachedScriptIndexes_; /**<Indexes of attached scripts (index in the project struct's list of scripts)*/

    glm::vec3 Color; /**<Color of the light*/

    glm::vec3 Pos; /**<Position*/

    ERS_STRUCT_DepthMap DepthMap; /**<Contains OpenGL IDS Used To Calculate Shadows*/

    bool CastsShadows_ = true; /*<Enable or disable shadows being cast from this light*/

};