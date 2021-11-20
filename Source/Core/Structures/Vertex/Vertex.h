//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSVerex Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/

#pragma once

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>

#define MAX_BONE_INFLUENCE 4


struct ERS_OBJECT_VERTEX {

    // Set Metadata
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;

    int BoneIDs[MAX_BONE_INFLUENCE];
    float Weights[MAX_BONE_INFLUENCE];


    // Set Helper Vars
    bool _HasInitialized = false;


    // Define Helper Functions
    void Initialize() {
        _HasInitialized = true;
    }

    bool IsInitialized() {
        return _HasInitialized;
    }


};