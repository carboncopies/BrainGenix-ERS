//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>

// Internal Libraries (BG convention: use <> instead of "")


struct ERS_STRUCT_PointLight {

    std::string UserDefinedName; /**Name of the light assigned by user*/
    
    float RolloffConstant; /**<Rolloff constant*/
    float RolloffLinear; /**<Rolloff constant*/
    float RolloffQuadratic; /**<Rolloff constant*/


    glm::vec3 Ambient; /**<Ambient color of the light*/
    glm::vec3 Diffuse; /**<Ambient color of the light*/
    glm::vec3 Specular; /**<Ambient color of the light*/

    glm::vec3 Pos; /**<Position*/

};