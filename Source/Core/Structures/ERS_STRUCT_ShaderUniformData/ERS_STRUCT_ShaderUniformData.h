// ToDO: then add to project struct, then update project loader/writer with this info. Then check trello board for other related tasks like live ediitng.


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


/**
 * @brief Struct for storing shader uniform data
 * 
 */
struct ERS_STRUCT_ShaderUniformDataDirectionalLight {

    glm::vec3 Direction_;
    glm::vec3 Color_;
    float Intensity_;
    float MaxDistance_;
    bool CastsShadows_;
    int DepthMapIndex_;
    glm::mat4 LightSpaceMatrix_;

}



/**
 * @brief Struct for storing shader uniform data
 * 
 */
struct ERS_STRUCT_ShaderUniformData {

    // Shader Data
    float Time_;
    float FrameTime_;
    int FrameNumber_;
    glm::vec2 ViewportRes_;
    glm::vec3 CameraPosition_;


    int NumberDirectionalLights_;


}