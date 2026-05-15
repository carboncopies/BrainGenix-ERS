//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>


struct ERS_STRUCT_AudioSource {

    std::string UserDefinedName = "New Audio Source"; /**<Name displayed in the editor scene tree*/
    long AudioAssetID = -1; /**<Asset ID of the source audio clip, or -1 when not assigned*/

    glm::vec3 Pos = glm::vec3(0.0f); /**<Position of the source in the scene*/
    glm::vec3 Rot = glm::vec3(0.0f); /**<Orientation reserved for directional audio emitters*/

    float Gain = 1.0f; /**<Playback gain multiplier*/
    float MaxDistance = 20.0f; /**<Distance after which this source is inaudible*/

    bool Looping = false; /**<Whether the source should loop during playback*/
    bool Autoplay = false; /**<Whether the source should begin playback when the scene starts*/

    std::vector<long> AttachedScriptIndexes_; /**<Indexes of attached scripts*/

};
